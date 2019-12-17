/*---------------------------------------------------------------------------**
**          Filename    : pMic.cpp                                           **
**          Description : send mic command functions                         **
**          Created on  :2019/09/19                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/


// pMic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <string.h>
#include <corecrt_malloc.h>
#include <synchapi.h>
#ifdef WIN32
#define __attribute__(__X__)
#endif
#include <stdio.h>
#include "devioctl.h"
#include "ntddscsi.h"
#include "sw_common\spti.h"
#include "sw_common\pibasic.h"
#include "fw_include\mic.h"
#include "sw_common\micext.h"
#include "sw_common\reqdef.h"
#include "sw_common\errcode.h"

extern "C"
{

#define MAX_SENSE_BUFFER 64
#define MIC_IOCTL_HEADER_SIZE (sizeof(MicIoctl_t) - 4)
#define FASTTRAK_IOCTL_SIGNATURE1   0x54534146
#define FASTTRAK_IOCTL_SIGNATURE2   0x4b415254
#define IOCTL_FASTTRAK_GETVERSION   0x00000001   
	
	u16 gMaxPDsSupported = 0, gMaxArraysSupported = 0, gMaxLDsSupported = 0, gIsSX8350 = 0, gFeatureBitLunCloning = 0;
	int  ret, GlobalMaxRetries = 99;
	
	/* set these two variables when discover device.  use them in sendCommand() */
	static HANDLE hScsiDevice = INVALID_HANDLE_VALUE;
	static unsigned uConsoleID = 0;

	typedef enum
	{
		I2B_API_RET_SUCCESS = 0x00,
		I2B_API_RET_PARAM_ERR = 0x01,
		I2B_API_RET_LOGIN_ERR = 0x02,
		I2B_API_RET_CREATE_ERR = 0x03,
		I2B_API_RET_I2API_ERR = 0x04,
		I2B_API_RET_MEMALLOC_ERR = 0x05,
		I2B_API_RET_UNSUPPORTED = 0x06,

		I2B_API_RET_UNKNOWN = 0xFF
	}I2B_API_RET_E;

	typedef struct
	{
		union
		{
			SCSI_PASS_THROUGH mi_sptCmd;
			SCSI_PASS_THROUGH_DIRECT mi_sptdCmdDirect;
		} mi_uCmd;
		u32 mi_u32Padding;
		u8 mi_u8SenseBuffer[MAX_SENSE_BUFFER];
		u32 mi_u32Reserved;
		u8 mi_u8DataBuffer[4];
	} MicIoctl_t;

	typedef struct tagIOCTL_DRIVERVERSION_FRAME
	{
		ULONG Major;
		ULONG Minor;
		ULONG Oem;
		ULONG BuildNo;
		ULONG Signature[2];
		UCHAR ConsoleID;
		UCHAR HostNumber;   /* Linux driver only */
		UCHAR bReserved[2];
		ULONG Reserved[3];
	} IOCTL_DRIVERVERSION_FRAME, *PIOCTL_DRIVERVERSION_FRAME;

	typedef struct {
		SRB_IO_CONTROL SrbCtrl;
		IOCTL_DRIVERVERSION_FRAME Version;
	} hba_req_driver_version_t;

	typedef struct req_data_phydrv_info
	{
		DataBufferHeader_t rdpi_dbhHeader;
	} req_data_phydrv_info_t;



	/* Hard Disk Drive info struct
	 */
	typedef struct
	{
		unsigned int        NumOfPD;                /* Tota Number of Physical Drive  */
		unsigned short     	PDId;       			/* Flat ID                        */
		unsigned short      drvType;    			/* Drive Type SAS or SATA         */
		unsigned long long 	confCapacity;   		/* configurable capacity          */
		unsigned short     	enclosureId;
		unsigned short     	slotId;
	//	unsigned char       HDDTempWarThreshold;    /* PD temperature warning thershould */
	//	unsigned char       HDDTempCriThreshold;    /* PD temperature warning thershould */
		unsigned char       temperature;            /* PD temperature                 */
		//unsigned char       TempStatusFlag;         /* PD temperature status          */

#define PD_TEMPERATURE_STS_NORMAL           0x00
#define PD_TEMPERATURE_STS_OVER_WARNING     0x01
#define PD_TEMPERATURE_STS_OVER_CRITICAL    0x02

		unsigned char       controllerId;           /* PD belong to controller Id     */
	}
	pMicHddInfo_t;

	

	__declspec(dllexport) void DisplayHelloFromDLL()
	{
		printf("Hello from DLL !\n");
	}
	void decodePDflags(u32 _flags)
	{
		//configuration
		switch (_flags & 0xFF)
		{
		case 0x00:  break;  //printf("unconfigured"); break;
		case 0x01:  printf("configured"); break;
		case 0x02:  printf("globlSpare"); break;
		case 0x03:  printf("dedctSpare"); break;
		case 0x04:  printf("dedctSpare"); break;
		default:    printf("CONFIG 0x%X UNKNOWN", _flags & 0xFF); break;
		}

		//state
		if ((_flags & 0xFF) != 0)
		{
			switch ((_flags >> 24) & 0xFF)
			{
			case 0x00: printf(", dead"); break;
			case 0x01: printf(", online"); break;
			case 0x02: printf(", missing"); break;
			case 0x08: printf(", regen"); break;
			default:   printf(", STATE 0x%X UNKNOWN", (_flags >> 24) & 0xFF); break;
			}
		}

		//condition
		switch ((_flags >> 16) & 0xFF)
		{
		case 0x00: break; //printf(" no state,"); break;
		case 0x02: printf(", pfa"); break;
		case 0x04: printf(", forced"); break;
		case 0x08: printf(", tempDead"); break;
		case 0x10: printf(", tempSpare"); break;
		case 0x20: printf(", present"); break;
		case 0x40: printf(", accessable"); break;
		case 0x60: printf(", present/accessable"); break;
		default:   printf(", CONDITION 0x%X UNKNOWN", (_flags >> 16) & 0xFF); break;
		}

		//operation
		switch ((_flags >> 8) & 0xFF)
		{
		case 0x00:  break; //printf(" idle"); break;
		case 0x02:  printf(", mp pending"); break;
		case 0x03:  printf(", mp complete"); break;
		case 0x05:  printf(", mp active"); break;
		default:    printf(", OPERATION 0x%X UNKNOWN", (_flags >> 8) & 0xFF); break;
		}

		fflush(stdout);
	}

	static u32 _checkBufferData(const u8 * pu8Buffer, const u32 u32Length)
	{
		u32 u32Ret = PIERR_NO_ERROR;
		DataBufferHeader_t * pmicHeader = NULL;

		if (pu8Buffer == NULL)
		{
			u32Ret = PIERR_INVALID_PARAM;
		}
		else
		{
			if (u32Length < sizeof(DataBufferHeader_t))
			{
				u32Ret = PIERR_INVALID_DATA;
			}
			else
			{
				pmicHeader = (DataBufferHeader_t *)pu8Buffer;
				if (u32Length < (sizeof(DataBufferHeader_t) +
					pmicHeader->dbh_NextTransferOffset))
				{
					u32Ret = PIERR_INVALID_DATA;
				}
			}
		}

		return u32Ret;
	}


	u32 decod_getBufferCountPhyDrvInfo(const u8 * pu8Buffer,
		const u32 u32Length, u32 * pu32Count)
	{
		u32 u32Ret = PIERR_NO_ERROR;
		u16 * pu16PageCode = NULL;
		u16 * pu16PageLength = NULL;
		req_data_phydrv_info_t * prdpi = NULL;
		u16 * pu16Id = NULL;
		u32 u32Index = 0, u32Count = 0, u32Size;
		u16 u16LastId = 0xFFFF;

		u32Ret = _checkBufferData(pu8Buffer, u32Length);

		if (u32Ret == PIERR_NO_ERROR)
		{
			prdpi = (req_data_phydrv_info_t *)pu8Buffer;
			u32Size = sizeof(DataBufferHeader_t) + prdpi->rdpi_dbhHeader.dbh_NextTransferOffset;

			u32Index = sizeof(DataBufferHeader_t);
			u32Count = 0;
			u16LastId = 0xFFFF;
			while (u32Index < u32Size)
			{
				pu16PageCode = (u16 *)(pu8Buffer + u32Index);
				pu16PageLength = (u16 *)(pu8Buffer + u32Index + 2);
				pu16Id = (u16 *)(pu8Buffer + u32Index + 2 + 2);
				u32Index += *pu16PageLength + 2 + 2;

				if (u32Index <= u32Size)
				{
					if (*pu16Id != u16LastId)
					{
						u16LastId = *pu16Id;
						u32Count++;
					} /* if */
				}
			}

			if (u32Ret == PIERR_NO_ERROR)
			{
				*pu32Count = u32Count;
			}
		}

		return u32Ret;
	}

	static u8 _translateDataDir(u8 u8DataDir)
	{
		u8 u8WinDataDir = 0;

		switch (u8DataDir)
		{
		case PMIC_DATA_NONE:
			/* treat it as DATA_IN, but to make sure the Data Transfer Length is 0 */
			u8WinDataDir = SCSI_IOCTL_DATA_IN;
			break;

		case PMIC_DATA_IN:
			u8WinDataDir = SCSI_IOCTL_DATA_OUT;
			break;

		case PMIC_DATA_OUT:
			u8WinDataDir = SCSI_IOCTL_DATA_IN;
			break;

		default:
			u8WinDataDir = 0xFF;
			break;
		}

		return  u8WinDataDir;
	}
	static u16 _swapWord(u16 u16Word)
	{
		u16 u16Ret;

		u16Ret = ((u16Word & 0xff00) >> 8) + ((u16Word & 0x00ff) << 8);

		return u16Ret;
	}

	__declspec(dllexport) u32 _ib_sendSCSIPassThruDirect(HANDLE dhDeviceHandle,
		u8 u8Path, u8 u8Target, u8 u8Lun,
		MicIoctl_t * pmicIoctl,
		u8 * pu8CDB, u8 u8CDBLength, u8 u8DataDir,
		u32 u32DataLength, u32 * pu32DataReturned,
		u32 u32Timeout)
	{
		u32 u32Ret = 0;
		BOOL bRet = TRUE;
		//u32 u32BufferSize = MIC_IOCTL_HEADER_SIZE + u32DataLength;
		u32 u32BufferSize = MIC_IOCTL_HEADER_SIZE; //MIC_IOCTL_HEADER_SIZE + u32DataLength;
		u32 u32Returned = 0;
		u8 u8WinDataDir = _translateDataDir(u8DataDir);

		if (u8WinDataDir == 0xFF)
		{
			u32Ret = -1;
			return u32Ret;
		}

		//logInfoMsg(peh, "_sendSCSIPassThruDirect() %x", pmicIoctl);
		memset(pmicIoctl, 0, MIC_IOCTL_HEADER_SIZE);

		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.Length = (USHORT)sizeof(SCSI_PASS_THROUGH_DIRECT);
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.PathId = u8Path;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.TargetId = u8Target;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.Lun = u8Lun;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.CdbLength = u8CDBLength;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.SenseInfoLength = MAX_SENSE_BUFFER;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.DataIn = u8WinDataDir;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.DataTransferLength = u32DataLength;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.TimeOutValue = u32Timeout;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.DataBuffer = pmicIoctl->mi_u8DataBuffer;
		pmicIoctl->mi_uCmd.mi_sptdCmdDirect.SenseInfoOffset = (ULONG)&((MicIoctl_t*)0)->mi_u8SenseBuffer;

		memcpy(pmicIoctl->mi_uCmd.mi_sptdCmdDirect.Cdb, pu8CDB, u8CDBLength);

		//logDataMsg(peh, (u8 *)pmicIoctl, u32BufferSize, 
		//        "DeviceIoControl SPTD Cmd: (data length %d)",
		//        u32DataLength);

		bRet = DeviceIoControl(dhDeviceHandle, IOCTL_SCSI_PASS_THROUGH_DIRECT,
			pmicIoctl, u32BufferSize,
			pmicIoctl, u32BufferSize,
			(LPDWORD)&u32Returned, NULL);

		if (bRet == FALSE)
		{
			u32Ret = -1;
			printf("bRet == FALSE !\n");
		}
		else
		{
			/* TBD - find out what are the SCSI Status */
			if (pmicIoctl->mi_uCmd.mi_sptdCmdDirect.ScsiStatus != 0)
			{
				//logDataMsg(peh, pmicIoctl->mi_u8SenseBuffer, 
				//        pmicIoctl->mi_uCmd.mi_sptdCmdDirect.SenseInfoLength,
				//        "_sendSCSIPassThruDirect(), scsi status %d (0x%X) sense data:",
				//        pmicIoctl->mi_uCmd.mi_sptdCmdDirect.ScsiStatus,
				//        pmicIoctl->mi_uCmd.mi_sptdCmdDirect.ScsiStatus);
				u32Ret = formPMICErrorCode((u8)(pmicIoctl->mi_uCmd.mi_sptdCmdDirect.ScsiStatus),
					pmicIoctl->mi_u8SenseBuffer, pmicIoctl->mi_uCmd.mi_sptdCmdDirect.SenseInfoLength);
			}
			else
			{
				//            *pu32DataReturned = u32Returned;
				*pu32DataReturned = pmicIoctl->mi_uCmd.mi_sptdCmdDirect.DataTransferLength;
			}
		}

		return u32Ret;
	}
	static u32 testMicRequest(HANDLE dhDeviceHandle, u8 u8Path, u8 u8Target, u8 u8Lun)
	{
		u32 u32Ret = 0;
		u32 u32DataSize = sizeof(micControllerInfoPage0_t) + sizeof(DataBufferHeader_t);
		u32 u32DataReturned = 0;
		u16 u16CurrentCtrlId = 0;
		u8  u8CDB[I2IPC_REQ_PARAMSIZE_FWBYPASS_IOCTL] = { 0 };
		micCtlGetInfoCmd_t *pMicCmd = (micCtlGetInfoCmd_t *)u8CDB;
		u8 *pmicIoctl = NULL;

		pmicIoctl = (u8 *)malloc(65536 + sizeof(MicIoctl_t));
		if (pmicIoctl == NULL)
		{
			u32Ret = PIERR_OUT_OF_MEMORY;
		}

		if (u32Ret == PIERR_NO_ERROR)
		{
			memset(pmicIoctl, 0, 65536 + sizeof(MicIoctl_t));
			memset(u8CDB, 0, I2IPC_REQ_PARAMSIZE_FWBYPASS_IOCTL);
			pMicCmd->gci_ScsiOpCode = PMIC_MGT_CMD;
			pMicCmd->gci_MicSignature = PMIC_SIGNATURE;
			pMicCmd->gci_MicOpCode = _swapWord(PMIC_CONTROLLER_GET_INFO);
			pMicCmd->gci_ControllerID = _swapWord(u16CurrentCtrlId);
			pMicCmd->gci_CodePage = CTRL_PAGE_RAID;
			pMicCmd->gci_ControllerCount = 1;
			pMicCmd->gci_TransferLength = _swapWord((u16)(u32DataSize));

			u32Ret = _ib_sendSCSIPassThruDirect(dhDeviceHandle, u8Path, u8Target, u8Lun,
				(MicIoctl_t *)pmicIoctl, u8CDB, 16, PMIC_DATA_OUT,
				u32DataSize, &u32DataReturned, 10);
		}

		if (pmicIoctl)
			free(pmicIoctl);

		return u32Ret;
	}
	BOOL check_scsi(int port, u32 pConsoleId)
	{
		HANDLE hScsi = NULL;
		char devicename[256] = { 0 };
		hba_req_driver_version_t driverVersion = { 0 };
		BOOL bRet = FALSE;
		u32 u32Returned = 0;

		if (&pConsoleId == NULL)
			return FALSE;

		sprintf_s(devicename, "\\\\.\\scsi%d:", port);
		//printf("devicename=%s !\n", devicename);
		hScsi = CreateFile(devicename,
			GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

		if (hScsi == INVALID_HANDLE_VALUE)
		{
			//printf("BBBBB!\n");
			return FALSE;
		}

		memset(&driverVersion, 0, sizeof(hba_req_driver_version_t));
		driverVersion.SrbCtrl.ControlCode = IOCTL_FASTTRAK_GETVERSION;
		driverVersion.SrbCtrl.Length = sizeof(IOCTL_DRIVERVERSION_FRAME);
		driverVersion.SrbCtrl.HeaderLength = sizeof(SRB_IO_CONTROL);
		((u32 *)(driverVersion.SrbCtrl.Signature))[0] = FASTTRAK_IOCTL_SIGNATURE1;
		((u32 *)(driverVersion.SrbCtrl.Signature))[1] = FASTTRAK_IOCTL_SIGNATURE2;
		driverVersion.SrbCtrl.ReturnCode = 0xFFFFFFFF;
		driverVersion.SrbCtrl.Timeout = 10;

		bRet = DeviceIoControl(hScsi,
			IOCTL_SCSI_MINIPORT,
			&driverVersion, sizeof(hba_req_driver_version_t),
			&driverVersion, sizeof(hba_req_driver_version_t),
			(LPDWORD)&u32Returned, NULL);

		if (!bRet || (testMicRequest(hScsi, 0, driverVersion.Version.ConsoleID, 0) != PIERR_NO_ERROR))
		{
			//printf("inherer!\n");
			CloseHandle(hScsi);
			return FALSE;
		}

#ifdef DEBUG
		printf("Found device version %d.%d.%d.%d on port %d\n",
			driverVersion.Version.Major,
			driverVersion.Version.Minor,
			driverVersion.Version.Oem,
			driverVersion.Version.BuildNo,
			port
		);
#endif

		if (pConsoleId != NULL)
		{
			pConsoleId = driverVersion.Version.ConsoleID;
		}

		hScsiDevice = hScsi;
		uConsoleID = driverVersion.Version.ConsoleID;

		return TRUE;
	}

	__declspec(dllexport) BOOL discover()
	{
		int i = 0;
		//printf("Hello from discover (NULLL)!\n");
		u32 pPortId=0;
		u32 pConsoleId=0;
		if (!&pPortId) return FALSE;
		if (!&pConsoleId) return FALSE;

		for (i = 0; i < 16; i++)
		{
			if (check_scsi(i, pConsoleId) == TRUE)
			{
				pPortId = i;
				//printf("Hello from TRUE !\n");
				return TRUE;
			}
		}
		printf("Hello from FALSE !\n");
		return FALSE;
	}

	u32 sendCommand(u8* pCmd, u8 u8DataDirection, u8 * pu8DataBuf, u32 u32DataBufLen)
	{
		u32 u32Ret = 0;
		MicCmd_t * pMicCmd = (MicCmd_t*)pCmd;
		DataBufferHeader_t * pmicHeader = NULL;
		int nRet = 0;
		u32 u32DataReturned = 0;
		MicIoctl_t * pmicIoctl = NULL;

		if (u32Ret == 0)
		{
			//TODO:
			pmicIoctl = (MicIoctl_t*)malloc(65536 + sizeof(MicIoctl_t));

			if (u8DataDirection == PMIC_DATA_OUT)
			{
				if (u32DataBufLen > 0)
					memset(pmicIoctl->mi_u8DataBuffer, 0, u32DataBufLen);
			}

			if (u8DataDirection == PMIC_DATA_IN)
			{
				if (u32DataBufLen > 0)
					memcpy(pmicIoctl->mi_u8DataBuffer, pu8DataBuf, u32DataBufLen);
			}

			pMicCmd->mc_ScsiOpCode = PMIC_MGT_CMD;
			pMicCmd->mc_MicSignature = PMIC_SIGNATURE;

			memset(pmicIoctl->mi_u8SenseBuffer, 0, MAX_SENSE_BUFFER);

			u32Ret = _ib_sendSCSIPassThruDirect(hScsiDevice,
				0, uConsoleID, 0,
				(MicIoctl_t*)pmicIoctl, (u8*)pMicCmd, 16, u8DataDirection,
				u32DataBufLen, &u32DataReturned, 10);
			//printf("sendCommand =%d !\n", u32Ret);
			if (u32Ret == 0)
			{
				if (u8DataDirection == PMIC_DATA_OUT)
				{
					memcpy(pu8DataBuf, pmicIoctl->mi_u8DataBuffer, u32DataBufLen);
				}
			}
			free(pmicIoctl);
		}

		return u32Ret;
	}

	__declspec(dllexport) void SetEventMic(u16 ClassEventID, u16 CodeEventID, u16 DeviceID, u8 *ExtraLog)
	{
		u8 pData[PMIC_MAX_DATA_XFER_SIZE];
		u32 u32Ret;
		u32 data_size = 0;

		micEventGetSettingsCmd_t MicCmd;
		DataBufferHeader_t *pmicHeader = NULL;
		Event_t *event = NULL;
		discover();
		data_size = 0;
		data_size = sizeof(DataBufferHeader_t) + sizeof(Event_t);

		memset(pData, 0, PMIC_MAX_DATA_XFER_SIZE);
		memset(&MicCmd, 0, sizeof(micEventGetSettingsCmd_t));
		MicCmd.egs_MicOpCode = _swapWord(PMIC_EVENT_POST_SW_EVENT);
		MicCmd.egs_TransferLength = _swapWord((u16)(data_size));

		pmicHeader = (DataBufferHeader_t *)pData;
		pmicHeader->dbh_TotalDataSize = sizeof(Event_t);
		pmicHeader->dbh_NextTransferOffset = sizeof(Event_t);

		event = (Event_t *)(pData + sizeof(DataBufferHeader_t));

		event->evt_EventId.ei_EventId.ei_ClassId = ClassEventID;
		event->evt_EventId.ei_EventId.ei_EventCode = CodeEventID;
		event->evt_DeviceId = DeviceID;
		memcpy(event->evt_EventInfo, ExtraLog, 32);

		u32Ret = sendCommand((u8 *)&MicCmd, PMIC_DATA_IN, pData, data_size);
		printf("SetEventMic =%d !\n", u32Ret);
	}

	static void * Malloc(size_t size)
	{
		void * ret;

		ret = malloc(size);

		if (ret == NULL)
		{
			printf("malloc( size %d ) failed - (%d) \n", size, errno);
			fflush(stdout);
			return ret;
		}
		return ret;
	}

	__declspec(dllexport) s32 PhysicalDriveInfo(pMicHddInfo_t *outdata , unsigned in_BufLen,u16 NumOfHDSlots)
	{
		//DataBufferHeader_t *Header;
		u8 *pPureData, *pDataBuffer;

		micPDGetInfoCmd_t Cmd;

		micPDInfoPage0_t *pHddInfo;
		gMaxPDsSupported = NumOfHDSlots;
		u16 TransferLength = 65535;

		u32 numOfRecords;


		if (NULL == outdata)
			return (I2B_API_RET_PARAM_ERR);
		

		/* Check the input buffer size */
		if (in_BufLen < (gMaxPDsSupported * sizeof(pMicHddInfo_t)))
			return I2B_API_RET_PARAM_ERR;




		discover();
		//printf("sizeof(pDataBuffer)=  %d\n", sizeof(pDataBuffer));
		pDataBuffer = (u8 * )Malloc(TransferLength);
		//printf("sizeof(Malloc(TransferLength)=  %d\n", Malloc(TransferLength));
		memset(&Cmd, 0, 16);
		Cmd.pgi_ScsiOpCode = PMIC_MGT_CMD;
		Cmd.pgi_MicSignature = PMIC_SIGNATURE;
		Cmd.pgi_MicOpCode = _swapWord(PMIC_PHYSICAL_DRIVE_GET_INFORMATION);
		Cmd.pgi_PDFlatId = 0;
		Cmd.pgi_CodePage = 0xff;
		Cmd.pgi_TransferLength = _swapWord(TransferLength);
		Cmd.pgi_PDCount = gMaxPDsSupported > 255 ? 255 : gMaxPDsSupported;
#ifndef WIN32
		ret = sendCommand((u8*)&Cmd, PMIC_DATA_OUT, pDataBuffer, TransferLength, &gLunpath);
#else
		ret = sendCommand((u8 *)&Cmd, PMIC_DATA_OUT, pDataBuffer, TransferLength);
#endif
		if (ret != PMIC_GOOD)
		{
			printf("Command status=%d\n", ret);
			fflush(stdout);
			return ret;
		}

		//Header = (DataBufferHeader_t *)pDataBuffer;
		//numOfRecords = Header->dbh_TotalDataSize / sizeof(micPDInfoPage0_t);
		pPureData = (u8*)(pDataBuffer + sizeof(DataBufferHeader_t));
		


		decod_getBufferCountPhyDrvInfo((u8 *)pDataBuffer, TransferLength, & numOfRecords);
		
		//memset(outdata, 0, numOfRecords * sizeof(int));
		//printf("numOfRecords=%d\n", numOfRecords);

		for (u16 i = 0; i < numOfRecords; i++)
		{
			
			pHddInfo = (micPDInfoPage0_t *)pPureData;
			//printf("Asked for FlatID %d\n", pHddInfo->pdi_FlatId+1);
			//printf("pdi_DriveTemperature= %d\n", pHddInfo->pdi_DriveTemperature);




			outdata[i].NumOfPD= numOfRecords;
			outdata[i].PDId = pHddInfo->pdi_FlatId + 1;
			outdata[i].drvType = pHddInfo->pdi_DriveType;
			outdata[i].confCapacity = pHddInfo->pdi_ConfigurableSize * pHddInfo->pdi_BlockSize;
			outdata[i].enclosureId = pHddInfo->pdi_EnclosureId + 1;
			outdata[i].slotId = pHddInfo->pdi_SlotId;
			//outdata[i].HDDTempWarThreshold;    
			//outdata[i].HDDTempCriThreshold;    
			outdata[i].temperature = pHddInfo->pdi_DriveTemperature;;
			//outdata[i].TempStatusFlag;         
			outdata[i].controllerId = pHddInfo->pdi_EnclosureId + 1;;
                

			pPureData += (sizeof(micPDInfoPage0_t) + sizeof(micPDInfoPage1_t));
		}
		
		if (pDataBuffer)
			free(pDataBuffer);
		return ret;
	}


	DWORD CreateNWait(HANDLE test_event)
	{
		do {
			printf("WaitForSingleObject init\n");
			WaitForSingleObject(
				test_event,
				10000
			);
			printf("WaitForSingleObject done\n");
			//TODO
		} while (true);

		return 0;
	}

	/*__declspec(dllexport) void test()
	{
		HANDLE test_event;
		printf("CreateEventA IN\n");
		test_event = CreateEventA(NULL, 0, 0, "a");

		DWORD ThreadID;
		printf("create hThread in\n");
		HANDLE hThread = CreateThread(NULL,
			0,
			CreateNWait,
			test_event,
			0,
			&ThreadID);
		printf("test_event=%d\n", &test_event);
		printf("create hThread out\n");
		CloseHandle(hThread);

	}*/

	__declspec(dllexport) HANDLE Get_event()
	{
		HANDLE eve;
		eve = CreateEventA(NULL, 0, 0, "a");
		return eve;

	}






}

u32 formPMICErrorCode(u8 u8CompStatus, u8 * pu8Sense, u32 u32SenseLen)
{
	u32 u32ErrorCode = 0;
	u32 u32SenseKey = 0, u32Asc = 0, u32Ascq = 0;

	if (u8CompStatus != PMIC_GOOD)
	{
		if (u32SenseLen >= 3)
		{
			u32SenseKey = (u32)(pu8Sense[2] & 0x0f);
			u32SenseKey = u32SenseKey << 24;
		}

		if (u32SenseLen >= 14)
		{
			u32Asc = (u32)pu8Sense[12];
			u32Ascq = (u32)pu8Sense[13];
			u32Asc = u32Asc << 16;
			u32Ascq = u32Ascq << 8;
		}

		u32ErrorCode = 0x40000000 | u32SenseKey | u32Asc | u32Ascq | u8CompStatus;
	}

	return u32ErrorCode;
}