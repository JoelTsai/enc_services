/*******************************************************************************
 * Filename    : fwinterf.h
 * Description : Firmware interface header file
 *               It provides the constant definitions, data structures and
 *               related functional routines of the firmware interface.
 * Created on  : 01/29/03
 * CVS Version : $Id: fwinterf.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_FIRMWAREINTERFACE_H__
#define __PI_FIRMWAREINTERFACE_H__

/* --- standard C lib header files ----------------------------------------- */
#include <signal.h>

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"
#include "i2types.h"
#include "internalmic.h"
/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

#define FI_EVENT_NOTIFICATION_NONE		0
#define FI_EVENT_NOTIFICATION_SIGNAL	1
#define FI_EVENT_NOTIFICATION_BLOCK		2

typedef void firmware_interface_t;

typedef struct
{
    u8 * fip_pu8FilePath;        /* file path to the driver node */
#ifndef PLATFORM_64BIT_SUPPORT
	u8 * fip_pu8Padding;		/* padding */
#endif
#ifndef SINGLE_ERROR_HANDLER
    error_handler_t * fip_pehErrorHandler;
#ifndef PLATFORM_64BIT_SUPPORT
	u8 * fip_pu8Padding1;		/* padding */
#endif
#endif
	u8 fip_u8EventNotificationMethod;
		/* FI_EVENT_NOTIFICATION_NONE/SIGNAL/BLOCK */
	boolean_t fip_bEnableFbFc;	/* to enable FB FC support in the FW Interface */
	u8 fip_u8Reserved[46];		/* reserved for future use */
} firmware_interface_param_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: createFirmwareInterface 
* Description: create a firmware interface object according to the param.
* Parameters:    
*       [in/out] ppfi, the pointer to the firmware interface object to be 
*           created and returned.
*   	[in] pfip, the pointer to the parameters of the firmware interface.
* Return: The possible values are:
*       PIERR_NO_ERROR - succeed,  the object is created.
*   	PIERR_OUT_OF_MEMORY - failed, the object is not created.
* Remarks: none.     
****************************************************************************/
u32 createFirmwareInterface(firmware_interface_t ** ppfi, 
    firmware_interface_param_t * pfip);

/**************************************************************************
* Function Name: destroyFirmwareInterface 
* Description: destroy the specified firmware interface.
* Parameters:    
*       [in/out] ppfi, the pointer to the firmware interface object to be 
*   	    destroyed. After destruction, it will be set to NULL.
* Return: PIERR_NO_ERROR, succeed; otherwise, fail.
* Remarks: createFirmwareInterface should be called successfully before this 
*       func is called.     
****************************************************************************/
u32 destroyFirmwareInterface(firmware_interface_t ** ppfi);

/**************************************************************************
* Function Name: isFirmwareInterfaceOpened 
* Description: check whether the firmware interface has been opened.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
* Return: PIERR_NO_ERROR, succeed; otherwise, fail.
* Remarks: createFirmwareInterface should be called successfully before this 
*       func is called.     
****************************************************************************/
boolean_t isFirmwareInterfaceOpened(firmware_interface_t * pfi);

/**************************************************************************
* Function Name: openFirmwareInterface 
* Description: open the firmware interface.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object to be opened.
* Return: PIERR_NO_ERROR, succeed; otherwise, fail.
* Remarks: createFirmwareInterface should be called successfully before this
*       func is called. If the interface is not opened, it will return without 
*       an error.     
****************************************************************************/
u32 openFirmwareInterface(firmware_interface_t * pfi);

/**************************************************************************
* Function Name: closeFirmwareInterface 
* Description: close the firmware interface.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object to be closed.
* Return: PIERR_NO_ERROR, succeed; otherwise, fail.
* Remarks: createFirmwareInterface should be called successfully before this
*       func is called. If the interface is not opened, it will return without 
*       an error.     
****************************************************************************/
u32 closeFirmwareInterface(firmware_interface_t * pfi);

/**************************************************************************
* Function Name: sendCommand 
* Description: send a command to the firmware. It will not return until the
*       command completes or a failure occurs.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u8Mic, the MIC command CDB.
*       [in] u8DataDirection, the data I/O direction. It can be 
*           PMIC_DATA_OUT or PMIC_DATA_IN
*       [in/out] pu8DataBuf, the input/output data buffer, depending on the
*           data direction specified in u8DataDirection.
*       [in] u32DataBufLen, the length of the input data, or the expected
*           length of the output data.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 sendCommand(firmware_interface_t * pfi, MicCmd_t * pMicCmd, u8 u8DataDirection, 
    u8 * pu8DataBuf, u32 u32DataBufLen);

/**************************************************************************
* Function Name: fi_getSubsysInfo
* Description: Get the subsystem Information.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in/out] pmicSubsysInfo, the pointer to buffer to retrieve subsystem information .
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 fi_getSubsysInfo(firmware_interface_t * pfi, micSubsystemInfo_t * pmicSubsysInfo);

/**************************************************************************
* Function Name: fi_getCurrentControllerInfo
* Description: Get current controller information.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in/out] pcciCurrentCtrlInfo, the pointer to buffer to retrieve current controller information.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 fi_getCurrentControllerInfo(firmware_interface_t * pfi, current_controller_info_t * pcciCurrentCtrlInfo);

/**************************************************************************
* Function Name: fi_getControllerInfo
* Description: Get Controller Information of the specified controller and the specified page code.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u16CtrlId, the controller Id.
*		[in] u8PageCode, the controller info page code.
*		[in/out] pu8Buffer, the pointer to the buffer to retireive controller information. The buffer will be returned with the mic data buffer header and the ctrl info together. The caller must make sure the buffer size is big enough, otherwise it may cause memory corruption.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 fi_getControllerInfo(firmware_interface_t * pfi, const u16 u16CtrlId, const u8 u8PageCode, u8 * pu8Buffer);

/**************************************************************************
* Function Name: fi_getControllerSettings
* Description: Get Controller Settings of the specified controller and the specified page code.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u16CtrlId, the controller Id.
*		[in] u8PageCode, the controller info page code.
*		[in/out] pu8Buffer, the pointer to the buffer to retireive controller settings. The data will be returned with mic data buffer header and the settings together. The caller must make sure the buffer is big enough, otherwise it may cause memory corruption.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 fi_getControllerSettings(firmware_interface_t * pfi, const u16 u16CtrlId, const u8 u8PageCode, u8 * pu8Buffer);

/**************************************************************************
* Function Name: fi_getControllerInfoPage0
* Description: Get Controller Information Page 0 of the specified ontroller
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u16CtrlId, the controller Id.
*		[in/out] pu8*CtrlInfo, the pointer to the buffer to retireive controller information
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 fi_getControllerInfoPage0(firmware_interface_t * pfi, const u16 u16CtrlId, micControllerInfoPage0_t * pmicCtrlInfo);

/**************************************************************************
* Function Name: fi_waitForEvent
* Description: Wait for next event.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: 
*       1. createFirmwareInterface and openFirmwareInterface should be called 
*          successfully before this func is called.
*       2. FI_EVENT_NOTIFICATION_BLOCK must be specified during createFirmwareInterface, otherwise, this funciton will return PIERR_PROGRAM_ERROR.
****************************************************************************/
u32 fi_eventBlock(firmware_interface_t * pfi);

/**************************************************************************
* Function Name: fi_shutdown
* Description: shutdown or restart subsyste/controller.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*		[in] u8ShutdownType, the shutdown type: SHUTDOWN or RESTART
*		[in] u16CtrlId, the ID controller to shtudown. 0xFF stands for subsystem.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: 
*       1. createFirmwareInterface and openFirmwareInterface should be called 
*          successfully before this func is called.
*       2. FI_EVENT_NOTIFICATION_BLOCK must be specified during createFirmwareInterface, otherwise, this funciton will return PIERR_PROGRAM_ERROR.
****************************************************************************/
u32 fi_shutdown(firmware_interface_t * pfi, const u8 u8ShutdownType, const u16 u16CtrlId);

u32 fi_getDateAndTime(firmware_interface_t * pfi, req_param_device_ids_t * pParam,
    req_data_time_t * pData, u32 u32DataSize);

u32 fi_setDateAndTime(firmware_interface_t * pfi, req_param_device_ids_t * pParam,
    req_data_time_t * pData, u32 u32DataSize);

u32 fi_upsCacheTrigger(firmware_interface_t * pfi, req_data_ups_cache_trigger_t * pData, u32 u32DataSize);

/**************************************************************************
* Function Name: acquireFwLock 
* Description: acquire the firmware lock
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u32LockPeriod, the period to hold the f/w lock, in seconds
*       [out] pu8LockKey, when successful, the lock key will be returned here
*       [out] pu64ExpireTime, the expiration time of the f/w lock to be returned
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 acquireFwLock(firmware_interface_t * pfi, u32 u32LockPeriod, u8 * pu8LockKey, 
    u64 * pu64ExpireTime);

/**************************************************************************
* Function Name: renewFwLock 
* Description: renew the fw lock for more time. The lock should be pre-acquired
*       by calling acquireFwLock.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u32ExtendedPeriod, the extended time to lock the f/w, in seconds
*       [in] u8LockKey, the pre acquired lock key
*       [out] pu64ExpireTime, the new expiration time of the f/w lock
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 renewFwLock(firmware_interface_t * pfi, u32 u32ExtendedPeriod, u8 u8LockKey, 
    u64 * pu64ExpireTime);

/**************************************************************************
* Function Name: checkFwLock 
* Description: check the fw lock.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u8LockKey, the lock key to be checked
*       [out] pu64ExpireTime, the expiration time of the lock, if it is valid
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_NOT_LOCKED: the lock key is not valid
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 checkFwLock(firmware_interface_t * pfi, u8 u8LockKey, u64 * pu64ExpireTime);

/**************************************************************************
* Function Name: releaseFwLock 
* Description: release the fw lock.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u8LockKey, the lock key to be released
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 releaseFwLock(firmware_interface_t * pfi, u8 u8LockKey);

/**************************************************************************
* Function Name: forceReleaseFwLock 
* Description: force to release fw lock.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_PMIC_ERRORs: the command completed with an f/w error.
* Remarks: createFirmwareInterface and openFirmwareInterface should be called 
*       successfully before this func is called.     
****************************************************************************/
u32 forceReleaseFwLock(firmware_interface_t * pfi);

/**************************************************************************
* Function Name: getEvents 
* Description: get the events form RAM. It retrieves the specified count of 
*       events starting from the given event sequence number. If the specified
*       events does not exist, it always returns the next existing events.
*       If there are not any next events, the function will return an error
*       code of PIERR_NOT_FOUND;
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] u16SeqNo, the event sequence number
*       [in/out] u16Count, the event count to get and the actual count of 
*           retrieved events
*       [out] pu8Buf, the pointer to the buffer where the events will be returned
*       [in] u32BufSize, the size of the buffer
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
*       PIERR_NOT_FOUND: no more events;
* Remarks: There are two ways to retrieve real time events (in RAM) from f/w. 
*       One is thru IOCTL, the other is through memory map. The current 
*       implementation does it thru memory map.
****************************************************************************/
u32 getEvents(firmware_interface_t * pfi, u16 u16SeqNo, u16 * pu16Count, 
    u8 * pu8Buf, u32 u32BufSize);
    
/**************************************************************************
* Function Name: getFirstEvents 
* Description: get the first logged events form RAM. Always return the oldest
*       events in the buffer
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in/out] u16Count, the event count to get and the actual count of 
*           retrieved events
*       [out] pu8Buf, the pointer to the buffer where the events will be returned
*       [in] u32BufSize, the size of the buffer
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
* Remarks: There are two ways to retrieve real time events (in RAM) from f/w. 
*       One is thru IOCTL, the other is through memory map. The current 
*       implementation does it thru memory map.
****************************************************************************/
u32 getFirstEvents(firmware_interface_t * pfi, u16 * pu16Count, u8 * pu8Buf, u32 u32BufSize);

/**************************************************************************
* Function Name: getLastEvents 
* Description: get the last logged events posted to the event buffer.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in/out] u16Count, the event count to get and the actual count of 
*           retrieved events
*       [out] pu8Buf, the pointer to the buffer where the events will be returned
*       [in] u32BufSize, the size of the buffer
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
* Remarks: There are two ways to retrieve real time events (in RAM) from f/w. 
*       One is thru MIC Command Interface, the other is through memory map. 
*       The current implementation does it thru memory map.
****************************************************************************/
u32 getLastEvents(firmware_interface_t * pfi, u16 * pu16Count, u8 * pu8Buf, u32 u32BufSize);
u32 getEventStats(firmware_interface_t * pfi, u8 * pu8Buf, u32 u32BufSize );
/**************************************************************************
* Function Name: registerFwEventNotification 
* Description: register for the firmware event notification.
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [in] pfuncHandler, the notification handler.
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_FW_NOT_FOUND: f/w is not available
* Remarks: None.
****************************************************************************/
u32 registerFwEventNotification(firmware_interface_t * pfi, void (* pfuncHandler)(int));


u32 setEvents(firmware_interface_t * pfi, u16 u16Count, u8 * pu8Buf, u32 bufSize);
u32 getEventsInfo(firmware_interface_t * pfi, u8 * pu8Data, u16 size);


/**************************************************************************
* Function Name: swapWord 
* Description: swap the upper and lower bytes of the word.
* Parameters:    
*       [in] u16Word, the word to be swapped
* Return: the result of the swapping
* Remarks: None.
****************************************************************************/
u16 swapWord(u16 u16Word);

/**************************************************************************
* Function Name: swapDWord 
* Description: swap the upper and lower bytes of the double word.
* Parameters:    
*       [in] u32DWord, the double word to be swapped
* Return: the result of the swapping
* Remarks: None.
****************************************************************************/
u32 swapDWord(u32 u32Word);

/**************************************************************************
 * Function Name: getPasswordJumperStatus
 * Description: get the status of password jumper
 * Parameters:
 *       [in] pfi, the pointer to the firmware interface object.
 *       [out] pu8Data, the pointer to the buffer where the status will be returned
 *       [in] u16Size, the size of the buffer
 * Return: The funciton completion error code.
 *       PIERR_NO_ERROR: the command completed without an error;
 *       PIERR_OPERATION_FAIL: ioctl failure;
 * Remarks: None.
 ****************************************************************************/
u32 getPasswordJumperStatus(firmware_interface_t * pfi, u8 * pu8Data, u16 u16Size);

/**************************************************************************
 * Function Name: clearPasswordJumperStatus
 * Description: clear the status of password jumper
 * Parameters:
 *       [in] pfi, the pointer to the firmware interface object.
 *       [in] pu8Data, data passed to firmware
 * Return: The funciton completion error code.
 *       PIERR_NO_ERROR: the command completed without an error;
 *       PIERR_FW_NOT_FOUND: f/w is not available
 * Remarks: None.
 ****************************************************************************/
u32 clearPasswordJumperStatus(firmware_interface_t * pfi, u8 * pu8Data);

/**************************************************************************
* Function Name: fi_getFeatureBits
* Description: get feature bits
*       [in] pfi, the pointer to the firmware interface object.
*       [in] pFb, data for feature bits
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_FW_NOT_FOUND: f/w is not available
* Remarks: None.
****************************************************************************/
u32 fi_getFeatureBits(firmware_interface_t * pfi, feature_bits_t * pFb);

#ifdef DUAL_SYNC_SUPPORT
/**************************************************************************
* Function Name: fi_getFwFlashNvramData 
* Description: get the flash setting stored in NVRAM
* Parameters:    
*       [in] pfi, the pointer to the firmware interface object.
*       [out] pFlashSetting, the pointer to the buffer where the setting will be returned
* Return: The funciton completion error code. 
*       PIERR_NO_ERROR: the command completed without an error;
*       PIERR_OPERATION_FAIL: ioctl failure;
* Remarks: 
****************************************************************************/
u32 fi_getFwFlashNvramData(firmware_interface_t * pfi, micCtrlFWFlashSettings_t * pFlashSetting);
#endif
u32 fi_setCtrlSetting(firmware_interface_t * pfi, boolean_t bIsCacheEnable);
u32 fi_setPhyDrvSetting(firmware_interface_t * pfi, boolean_t bIsCacheEnable);
u32 fi_getiSCSIPortal(firmware_interface_t * pfi, u8 * pu8Buffer);
#endif /*__PI_FIRMWAREINTERFACE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: fwinterf.h,v $
 * Revision 1.3.36.4  2010/01/19 08:00:48  xinw
 * add fi_getiSCSIPortal
 *
 * Revision 1.3.36.3  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.3.36.2  2009/04/21 05:59:24  xinw
 * add set pd,ctrl setting
 *
 * Revision 1.3.36.1  2009/03/23 11:48:56  xinw
 * add ups support
 *
 * Revision 1.3  2007/05/14 21:11:02  danielz
 * new function fi_getFwFlashNvramData()
 *
 * Revision 1.2  2007/05/04 18:36:12  danielz
 * new function fi_getFeatureBits()
 *
 * Revision 1.1  2006/09/11 02:05:59  weny
 * making fwinterf a common library
 *
 * Revision 1.25  2006/06/08 18:21:37  xinw
 * add event blocking
 *
 * Revision 1.24  2006/04/15 19:03:35  xinw
 * add dual shutdown
 *
 * Revision 1.23  2006/04/10 03:41:01  danielz
 * Support for "password jumper"
 *
 * Revision 1.22  2006/04/07 01:47:38  xinw
 * add getThisCtrlInfo function
 *
 * Revision 1.21  2006/04/06 22:24:46  xinw
 * improve dual controller sync
 *
 * Revision 1.20  2006/04/06 03:00:55  xinw
 * modify shutdown conflict
 *
 * Revision 1.19  2006/04/01 03:36:33  debinc
 * support dual controller shutdown
 *
 * Revision 1.18  2004/12/09 22:45:39  debinc
 * implement getEventStats for RAM in s/w
 *
 * Revision 1.17  2004/10/27 18:57:54  debinc
 * shutdown command support
 *
 * Revision 1.16  2004/04/29 01:05:45  debinc
 * separate bga scheduler to a standalone daemon
 *
 * Revision 1.15  2004/03/26 22:55:45  debinc
 * Add function of getAllSpareId
 *
 * Revision 1.14  2004/03/16 21:37:05  debinc
 * Modify getIpAddr
 *
 * Revision 1.13  2004/03/15 22:21:42  debinc
 * Add getEvensInfo mic command
 *
 * Revision 1.12  2004/03/11 00:06:18  debinc
 * supprt 3 batter related mic command
 *
 * Revision 1.11  2004/02/12 03:48:43  debinc
 * support for event customization export/import
 *
 * Revision 1.10  2004/01/30 03:47:39  weny
 * add force unlock and verify lock
 *
 * Revision 1.9  2003/12/03 22:25:42  debinc
 * add get subsystem info cmd
 *
 * Revision 1.8  2003/09/13 00:35:09  weny
 * config lock support
 *
 * Revision 1.7  2003/06/28 05:49:59  weny
 * add bga scheduler support
 *
 * Revision 1.6  2003/06/12 02:36:50  weny
 * change some function prototypes.
 *
 * Revision 1.5  2003/05/17 03:06:30  weny
 * To support Event Discovery/Notification
 *
 * Revision 1.4  2003/04/02 00:17:14  weny
 * 1. add some routines for config lock - need implementation in the future
 * 2. make it conformant to the coding standard
 *
 * Revision 1.3  2003/03/13 00:03:47  weny
 * change the sendCommand prototype again.
 *
 * Revision 1.2  2003/03/11 23:58:20  weny
 * Change the prototype of sendCommand()
 *
 * Revision 1.1  2003/03/06 01:17:57  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
