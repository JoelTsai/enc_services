/*******************************************************************************
 * Filename    : dtdecode.h
 * Description : Data Decoder header file
 *               * decode the data structures of MIC interface and I2 Client API.
 * Created on  : 03/20/2003
 * CVS Version : $Id: dtdecode.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003 ~ 2005
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_DATADECODER_H__
#define __PI_DATADECODER_H__

/* --- standard C lib header files ----------------------------------------- */
#include <time.h>

#undef DECODE_API
#undef DECODE_CALL
#ifdef WINDOWS
    #include "windows.h"
	#if defined(PROMISE_DECODE_DLL)
		#define DECODE_API  __declspec(dllexport)
		#define DECODE_CALL
	#else
		//#define PROMISEAPI  __declspec(dllimport)
		#define DECODE_API
		#define DECODE_CALL __cdecl
	#endif
#else
	#define DECODE_API
	#define DECODE_CALL
#endif

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "i2types.h"
#include "i2typesob.h"
#include "bgaschd.h"

/* --- constant definitions ------------------------------------------------ */

#define OPSTATUS_UNKNOWN    0
#define OPSTATUS_OTHER      1
#define OPSTATUS_OK         2
#define OPSTATUS_DEGRADED   3
#define OPSTATUS_STRESSED   4
#define OPSTATUS_PFA        5
#define OPSTATUS_ERROR      6
#define OPSTATUS_FATAL      7
#define OPSTATUS_STARTING   8
#define OPSTATUS_STOPPING   9
#define OPSTATUS_STOPPED    10
#define OPSTATUS_INSERVICE  11
#define OPSTATUS_NOCONTACT  12
#define OPSTATUS_LOSTCOMM   13
#define OPSTATUS_ABORTED    14
#define OPSTATUS_DORMANT    15
#define OPSTATUS_SUPENTITYERR   16
#define OPSTATUS_COMPLETED  17
/* reserved for CIM */
#define CIM_OPSTATUS_VENDOR_RESERVE 0x8000

#define PROMISE_OPSTATUS_START  CIM_OPSTATUS_VENDOR_RESERVE

/* physical drive op status */
#define OPSTATUS_PHYDRV     (PROMISE_OPSTATUS_START+0)
#define OPSTATUS_DEAD       (OPSTATUS_PHYDRV+0)
#define OPSTATUS_MISSING    (OPSTATUS_PHYDRV+1)
#define OPSTATUS_FORCED_ONLINE  (OPSTATUS_PHYDRV+2) 
#define OPSTATUS_FORCED_OFFLINE (OPSTATUS_PHYDRV+3)
#define OPSTATUS_TEMP_OFFLINE   (OPSTATUS_PHYDRV+4)
#define OPSTATUS_REBUILDING     (OPSTATUS_PHYDRV+5)
#define OPSTATUS_MPRUNNING      (OPSTATUS_PHYDRV+6)
#define OPSTATUS_ACCESSIBLE     (OPSTATUS_PHYDRV+7)
#define OPSTATUS_NOT_ACCESSIBLE (OPSTATUS_PHYDRV+8)
#define OPSTATUS_NOT_PRESENT    (OPSTATUS_PHYDRV+9)
#define OPSTATUS_MIGRATING      (OPSTATUS_PHYDRV+10)
#define OPSTATUS_TRANSITIONING  (OPSTATUS_PHYDRV+11)
#define OPSTATUS_PDMRUNNING     (OPSTATUS_PHYDRV+12)
#define OPSTATUS_STALE          (OPSTATUS_PHYDRV+13)
#define OPSTATUS_SPARECHECKING  (OPSTATUS_PHYDRV+14)

/* logical drive op status */
#define OPSTATUS_LOGDRV         (PROMISE_OPSTATUS_START+50)
#define OPSTATUS_CRITICAL       (OPSTATUS_LOGDRV+0)
#define OPSTATUS_OFFLINE        (OPSTATUS_LOGDRV+1)
#define OPSTATUS_INITIALIZING   (OPSTATUS_LOGDRV+2)
#define OPSTATUS_SYNCHRONIZING  (OPSTATUS_LOGDRV+3)
#define OPSTATUS_REDCHECKING    (OPSTATUS_LOGDRV+4)

/* Disk Array op status */
#define OPSTATUS_DISKARRAY      (PROMISE_OPSTATUS_START+100)
#define OPSTATUS_INCOMPLETE     (OPSTATUS_DISKARRAY+0)
#define OPSTATUS_MISSING_PD     (OPSTATUS_DISKARRAY+1)
#define OPSTATUS_MISSING_WATERMARK   (OPSTATUS_DISKARRAY+2)
#define OPSTATUS_MIGRATION_SUSPENDED (OPSTATUS_DISKARRAY+3)  /* disk array and logical drive activity status */
#define OPSTATUS_MIGRATION_ABORTED   (OPSTATUS_DISKARRAY+4)  /* disk array and logical drive activity status */
#define OPSTATUS_TRANSPORT_READY     (OPSTATUS_DISKARRAY+5)  /* disk array is transport ready */

/* Ctrl op status */
#define OPSTATUS_CTRL           (PROMISE_OPSTATUS_START+150)
#define OPSTATUS_ORPHAN_WATERMARK   (OPSTATUS_CTRL+0) /* ctrl condition status */
#define OPSTATUS_BGA_RUNNING    (OPSTATUS_CTRL+1)     /* ctrl activity status */
#define OPSTATUS_MAINTENANCE    (OPSTATUS_CTRL+2)
#define OPSTATUS_DEVICE_NOT_ACCESSIBLE   (OPSTATUS_CTRL+3)
#define OPSTATUS_SHUTDOWN       (OPSTATUS_CTRL+4)

#define OPSTATUS_NA             0xFFFF

#define MAX_TIME_SERVER_NAME_LENGTH 64

/* --- data structures ----------------------------------------------------- */

/* 
 * The free fragments of a disk array. It have the info about the starting 
 * address and the size of each of the fragment. Assuming that the fragments
 * are located at the same place and have the same size on each of the physical
 * drives of the disk array.
 * A disk array can have up to MAX_LOGDRV_PER_POOL free fragments.
 */
#define MIN_FRAGMENT_SIZE (4*1024*1024) /* 4MB - the max stripe size */

#define SAS_TOPOLOGY_CONNECTION_VALID           0
#define SAS_TOPOLOGY_CONNECTION_INVALID         1
#define SAS_TOPOLOGY_CONNECTION_UNKNOWN         2
#define SAS_TOPOLOGY_CONNECTION_NOTCONNECTED    3

#define FRU_CTRL_LOCATABLE          0x1
#define FRU_ENCLOSURE_LOCATABLE     0x2
#define FRU_PSU_LOCATABLE           0x4
#define FRU_COOLINGUNIT_LOCATABLE   0x8

typedef struct
{
    u32 daff_u32Count;
    u32 daff_u32Reserved;
    struct
    {
        u64 daff_u64Addr; /* starting address, in bytes */
        u64 daff_u64Size; /* in bytes */
    } daff_fragments[MAX_LOGDRV_PER_ARRAY]; 
} disk_array_free_fragment_t;

typedef struct
{
    u8 stc_u8ConnectionStatus;
    
    u8 stc_u8EnclosureId;
    u8 stc_u8ExpanderId;
    u8 stc_u8PortId;
    
    u8 stc_u8ConnectedEnclosureType;
    u8 stc_u8ConnectedEnclosureId;
    u8 stc_u8ConnectedExpanderId;
    u8 stc_u8ConnectedPortId;

    u8 stc_u8NumPhy;

    u8 stc_reserved[7];
} sas_topology_connection_t;

typedef struct
{
    u8 stei_u8EnclosureId;
    u8 stei_u8EnclosureType; // virtual or physical ( following fileds exists only if physical
    u8 stei_reserved[6];
    
    u8 stei_EnclosureWWN[WWN_BYTES]; //From the inquiry info page 83H.
    u8 stei_EnclosureManufactureString[MAX_VENDORID+MAX_PRODUCTID]; // both vendor and product asci values
    
} sas_topology_enclosure_info_t;

typedef struct
{
    u8 esr_u8EnclWarningMin;
    u8 esr_u8EnclWarningMax;
    u8 esr_u8EnclCriticalMin;
    u8 esr_u8EnclCriticalMax;
    u8 esr_u8CtrlWarningMin;
    u8 esr_u8CtrlWarningMax;
    u8 esr_u8CtrlCriticalMin;
    u8 esr_u8CtrlCriticalMax;
    u8 esr_u8reserved[64];
} encltemperature_setting_range_t;
/* --- functional routines ------------------------------------------------- */
#define IS_SINGLE_CTRL(fb) \
( \
  !(fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIE) && \
  !(fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIX) && \
  !(fb.fb_u32HAFeaturesMask & PI_HAFM_HA_SUPPORTED) \
)

#define IS_DUAL_CTRL(fb) \
( \
  !(fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIE) && \
  !(fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIX) && \
  (fb.fb_u32HAFeaturesMask & PI_HAFM_HA_SUPPORTED) \
)

#define IS_HBA(fb) \
( \
  (fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIE) || \
  (fb.fb_u32HostInterface & PI_FB_HOST_INTERFACE_PCIX) \
)


/* --- general ----------------------------------------------------------- */
/***************************************************************************
* Function Name: decod_getStringSMTPAuthentication
* Description: get the smtp authentication method
* Parameters:
*       [in] u8Method, the method
* Return: the string of the method. Either "Plain" or "Login".
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringSMTPAuthentication(const u8 u8Method);

/***************************************************************************
* Function Name: decod_getStringUserPrivilege
* Description: get the User Privilege string
* Parameters:
*       [in] u8OpUserPrivilege
* Return: The User Privilege string
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringUserPrivilege(const u8 u8UserPrivilege);
/***************************************************************************
* Function Name: decod_getStringDaemonStatus 
* Description: get the string of daemon status and startup type
* Parameters: [in] status/type
* Return: the string of status/type 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringDaemonStatus(const u8 u8DaemonStatus);
DECODE_API const char * DECODE_CALL decod_getStringDaemonStartupType(const u8 u8DaemonStartupType);

DECODE_API void DECODE_CALL decod_getStringSATAFRUInfo(char * pstrInfo, 
    const u8 * pu8Info, const u32 u32Length);

/***************************************************************************
* Function Name: decod_getStringNotApplicable 
* Description: get the string of not applicable "N/A".
* Parameters: none.
* Return: the string of not applicable. 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringNotApplicable();
DECODE_API const char * DECODE_CALL decod_getStringNotSupported();

/***************************************************************************
* Function Name: decod_getStringWWN 
* Description: get the string of WWN in the format of "xxxx-xxxx-xxxx-xxxx". 
*       The MSB is at the beginning and the LSB is at the end.
* Parameters:    
*       [out] pstrWWN, the string buffer where the WWN string will return
*       [in] pu8WWN, the pointer to the WWN array
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringWWN(char * pstrWWN, const u8 * pu8WWN);

/***************************************************************************
* Function Name: DECODE_CALL decod_getStringAlias
* Description: get the string of Alias
* Parameters:
*       [out] pstrAlias, the string buffer where the alias string will return
*       [in] pu8Alias, the pointer to the alias array
* Return: None.
* Remarks: This function does not check the size of the string buffer.
*       please make sure it is big enough to avoid memory access violation.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringAlias(char * pstrAlias, const u8 *pu8Alias, u32 u32Length);
DECODE_API u32 DECODE_CALL decod_validateStringAlias(u8 * pstrAlias);
DECODE_API u32 DECODE_CALL decod_validateStringUsername(u8 * pstrUsername);
/***************************************************************************
* Function Name: decod_getStringIPAddress 
* Description: get the string of IP Address according to the IP address type
* Parameters:    
*       [out] pstrIPAddr, the string buffer where the IP address string will return
*       [in] u8IPAddrType, the ip address type.
*       [in] pu8IPAddr, the ip addr info
* Return: PIERR_NO_ERROR, PIERR_INVALID_IP_ADDR_TYPE. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_retrieveIPAddress(const char * pIPString, u8 u8IPType, u8 * pu8Value);
DECODE_API u32 DECODE_CALL decod_retrieveMACAddress(const char * pMACString, u8 * pu8Value);
DECODE_API u32 DECODE_CALL decod_validateIPAddress(const char * pIPString, u8 u8IPType);
DECODE_API u32 DECODE_CALL decod_getStringIPAddress(char * pstrIPAddr,
    const u8 u8IPAddrType, const u8 * pu8IPAddr);
DECODE_API u32 DECODE_CALL decod_retrieveDate(char * pDateString, int * pYear, int * pMonth, int * pDay);
DECODE_API u32 DECODE_CALL decod_retrieveTime(char * pTimeString, int * pHour, int * pMin, int * pSec);

/***************************************************************************
* Function Name: decod_getStringMACAddress 
* Description: get the string of MAC Address 
* Parameters:    
*       [out] pstrMACAddr, the string buffer where the MAC address string will return
*       [in] pu8MACAddr, the MAC addr info
* Return: PIERR_NO_ERROR
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getStringMACAddress(char * pstrMACAddr, const u8 * pu8MACAddr);

/***************************************************************************
* Function Name: decod_getStringCustName 
* Description: get the string of customer name.
* Parameters:    
*       [out] pstrCustName, the string buffer where the customer name 
*           string will return
*       [in] pu8Custname, the pointer to the customer name in SATA FRU format
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringCustName(char * pstrCustName, const u8 * pu8CustName);

/***************************************************************************
* Function Name: decod_getStringCustModel 
* Description: get the string of customer model.
* Parameters:    
*       [out] pstrCustModel, the string buffer where the customer model 
*           string will return
*       [in] pu8CustModel, the pointer to the customer model in SATA FRU 
*           format
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringCustModel(char * pstrCustModel, const u8 * pu8CustModel);

/***************************************************************************
* Function Name: decod_getStringCustPartNo 
* Description: get the string of customer part number.
* Parameters:    
*       [out] pstrCustPartNo, the string buffer where the customer part no 
*           string will return
*       [in] pu8CustPartNo, the pointer to the customer part no in SATA FRU
*           format
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringCustPartNo(char * pstrCustPartNo, const u8 * pu8CustPartNo);

/***************************************************************************
* Function Name: decod_getStringCustSerialNo 
* Description: get the string of customer serial number.
* Parameters:    
*       [out] pstrCustSerialNo, the string buffer where the customer serial 
*           number string will return
*       [in] pu8CustSerialNo, the pointer to the customer serial no in SATA
*           FRU format 
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringCustSerialNo(char * pstrCustSerialNo, const u8 * pu8CustSerialNo);

/***************************************************************************
* Function Name: decod_getStringCustRev 
* Description: get the string of customer Revision.
* Parameters:    
*       [out] pstrCustRev, the string buffer where the customer revision 
*           number string will return
*       [in] pu8CustRev, the pointer to the customer revision in SATA FRU 
*           format 
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringCustRev(char * pstrCustRev, const u8 * pu8CustRev);

/***************************************************************************
* Function Name: decod_getStringDate 
* Description: get the string of date in the format of "<month> <day>, <year>". 
* Parameters:    
*       [out] pstrDate, the string buffer where the date string will return
*       [in] u8Month, the month of the year
*       [in] u8Day, the day of the month
*       [in] u16Year, the year
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringDate(char * pstrDate, const u8 u8Month, 
    const u8 u8Day, const u16 u16Year);

/***************************************************************************
* Function Name: decod_getStringTime 
* Description: get the string of time in the format of 
*       "hh:mm:ss <month> <day>, <year>". 
* Parameters:    
*       [out] pstrTime, the string buffer where the time string will return
*       [in] tTime, the time
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getStringTime(char * pstrTime, const time_t tTime);

DECODE_API u32 DECODE_CALL decod_getStringLocalTime(char * pstrTime, const time_t tTime);

/***************************************************************************
* Function Name: decod_getStringTimePeriod 
* Description: get the string of time period in the format of 
*       "[# hr] [# min] [# sec]"
* Parameters:    
*       [out] pstrTime, the string buffer where the period string will return
*       [in] u32Period, the time
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringTimePeriod(char * pstrTime, const u32 u32Period);

/***************************************************************************
* Function Name: decod_getStringOpStatus 
* Description: get the operational status string 
* Parameters:    
*       [in] u16OpStatus, the operational status code.
* Return: The operational status string 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringOpStatus(const u16 u16OpStatus);


/***************************************************************************
* Function Name: decod_getStringMemoryType 
* Description: get the memory type string 
* Parameters:    
*       [in] u8Type, the memory type code
* Return: The memory type string 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringMemoryType(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringFlashType(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringNvramType(const u8 u8Type);

/***************************************************************************
* Function Name: decod_getStringMemoryECCType 
* Description: get the memory ECC type string 
* Parameters:    
*       [in] u8Type, the memory type code
* Return: the memory ECC type string 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringMemoryECCType(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringMasterMode(const u8 u8Mode);
DECODE_API const char * DECODE_CALL decod_getStringActiveMode(const u8 u8Mode);

/***************************************************************************
* Function Name: decod_getStringSize 
* Description: get the size string in GB, MB, KB and B. The size string will
*       be the format of "xxxx.xxGB|MB|KB|B" 
* Parameters:    
*       [out] pstrSize, the size string to be returned;
*       [in] u64Size, the size in bytes
* Return: none. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringSize(char * pstrSize, const u64 u64Size);
/***************************************************************************
* Function Name: decod_getStringSize1000Based
* Description: get the size string based 1000 in GB, MB, KB and B. The size string will
*       be the format of "<xxxx|xxxx.x|xxxx.xx><TB|GB|MB|KB|B>"
* Parameters:
*       [out] pstrSize, the size string to be returned;
*       [in] u64Size, the size in bytes
* Return: none.
* Remarks: This function does not check the size of the string buffer.
*       please make sure it is big enough to avoid memory access violation.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringSize1000Based(char * pstrSize, const u64 u64Size);
/***************************************************************************
* Function Name: decod_getStringSizeMax
* Description: get the size string in GB, MB, KB and B. The size string will
*       be the format of "xxxx.xxGB|MB|KB|B" 
* Parameters:    
*       [out] pstrSize, the size string to be returned;
*       [in] u64Size, the size in bytes
* Return: none. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringSizeMax (char * pstrSize, const u64 u64Size);

/***************************************************************************
* Function Name: decod_getSize 
* Description: get the size accordign to the size stirng. The size string will
*       be the format of "xxxx.xxGB|MB|KB|B" 
* Parameters:    
*       [in] pstrSize, the size string;
*       [out] pu64Size, the size in bytes to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed. 
* Remarks: none.   
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getSize(const char * pstrSize, u64 * pu64Size);

/***************************************************************************
* Function Name: decod_getStringFwRevision 
* Description: get the firmware revision string in the format of "#.##-##". 
* Parameters:    
*       [out] pstrRevision, the size string to be returned;
*       [in] u8Major, the major version number;
*       [in] u8Minor, the minor version number;
*       [in] u8BuildNo, the build number;
* Return: none. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringFwRevision(char * pstrRevision, const u8 u8Major, 
    const u8 u8Minor, const u32 u32OEMCode, const u8 u8BuildNo);


DECODE_API const char * DECODE_CALL decod_getStringFeaturePort(const u32 u32Port);
DECODE_API const char * DECODE_CALL decod_getStringSlavePort(const u32 u32Port);
DECODE_API const char * DECODE_CALL decod_getStringFeatureLag(const u32 u32lag);



/***************************************************************************
* Function Name: decod_getStringFeatureEnable 
* Description: get the enable/disable status of a feature 
* Parameters:    
*       [in] u8Enable, the enable status
* Return: the string of the feature status. Either "Enabled" or "Disabled".
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringFeatureEnable(const u8 u8Enable);

/***************************************************************************
* Function Name: decod_getStringFeatureSupport 
* Description: get the string of whether a feature is supported or not
* Parameters:    
*       [in] u8Support, the status of support
* Return: the string of the feature support status. Either "Yes" or "No".
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringFeatureSupport(const u8 u8Support);
    
/* --- subsystem --------------------------------------------------------- */
/***************************************************************************
* Function Name: decod_getStringSubsysInterConnectType 
* Description: get the string of the inter-enclosure connection type of the
*       subsystem. The max string length is 32.
* Parameters:    
*       [out] pstrType, the string buffer where the type string will return
*       [in] u8Type, the type code
* Return: None. 
* Remarks: This function does not check the size of the string buffer. 
*       please make sure it is big enough to avoid memory access violation.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringSubsysInterConnectType(char * pstrType, const u8 u8Type);

/* --- controller -------------------------------------------------------- */
/***************************************************************************
* Function Name: decod_getBufferCountCtrlInfo
* Description: get the count of controller(s) that the controller info buffer
*       contains.
* Parameters:    
*       [in] pu8Buffer, the pointer to a controller info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [out] pu32Count, the count of controller(s) to be returned.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_ctrl_info_t type.  
*       Assuming that the page(s) in the buffer is in the ascending order of
*       the controller id and the page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountCtrlInfo(const u8 * pu8Buffer, const u32 u32Length, u32 * pu32Count);

DECODE_API u32 DECODE_CALL decod_getBufferCountCtrlSettings(const u8 * pu8Buffer, const u32 u32Length, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_locateBufferCtrlInfo
* Description: locate the beginning of the specified page of the specified
*       controller in the controller info data buffer. If the page of the 
*       specified controller does not exist, locate the next available one.
* Parameters:    
*       [in] pu8Buffer, the pointer to a controller info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the id of the controller;
*       [in] u16PageCode, the page code;
*       [out] ppPage, the pointer to the beginning of the page will be 
*           returned here.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_ctrl_info_t type.
*       Assuming that the page(s) in the buffer is in the ascending order of
*       the controller id and the page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferCtrlInfo(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppPage);

DECODE_API u32 DECODE_CALL decod_locateBufferCtrlSettings(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppPage);

/***************************************************************************
* Function Name: decod_locateBufferCtrlInfoPrecise
* Description: locate the beginning of the specified page of the specified
*       controller in the controller info data buffer. If the page of the 
*       specified controller does not exist, return PIERR_NOT_FOUND.
* Parameters:    
*       [in] pu8Buffer, the pointer to a controller info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the id of the controller;
*       [in] u16PageCode, the page code;
*       [out] ppPage, the pointer to the beginning of the page will be 
*           returned here.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_ctrl_info_t type.
*       Assuming that the page(s) in the buffer is in the ascending order of
*       the controller id and the page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferCtrlInfoPrecise(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppPage);

DECODE_API void DECODE_CALL decod_getCtrlOpStatus(const micControllerInfoPage0_t * pmicCtrl, u16 * pu16OpStatus);
DECODE_API void DECODE_CALL decod_getCtrlOpStatusEx(const micControllerInfoPage0_t * pmicCtrl, u16 u16OpStatus[], u32 * pu32StatusCount);
DECODE_API void DECODE_CALL decod_getStringCtrlOpStatus(char *pstrStatus, const micControllerInfoPage0_t * pmicCtrl);
DECODE_API void DECODE_CALL decod_getStringCtrlOpStatusEx(char *pstrStatus, const micControllerInfoPage0_t * pmicCtrl);

DECODE_API void DECODE_CALL decod_getCtrlOverallRaidStatus(const micControllerInfoPage0_t * pmicCtrl, u16 * pu16OpStatus);
DECODE_API void DECODE_CALL decod_getCtrlOverallRaidStatusEx(const micControllerInfoPage0_t * pmicCtrl, 
    u16 u16OpStatus[], u32 * pu32StatusCount);
DECODE_API void DECODE_CALL decod_getStringCtrlOverallRaidStatus(char * pstrStatus, 
    const micControllerInfoPage0_t * pmicCtrl);

/***************************************************************************
* Function Name: decod_getStringCtrlCmdProtocol 
* Description: get controller supported SCSI command protocal name.
* Parameters:    
*       [in] u8Protocol, the protocol code
* Return: the name of the protocol. 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringCtrlCmdProtocol(const u8 u8Protocol);

/***************************************************************************
* Function Name: decod_getStringCtrlCacheLineSize 
* Description: get controller cache line size string in "xxxxMB" or "xxxxKB".
* Parameters:    
*       [in] u8CacheLineSize, the code of cache line size
* Return: the cache line size string. 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringCtrlCacheLineSize(const u8 u8CacheLineSize);

DECODE_API u32 DECODE_CALL decod_getCtrlCoercionMethod(const char * pstrMethod, u8 * pu8Value);
DECODE_API const char * DECODE_CALL decod_getStringCtrlCoercionMethod(u8 u8Mode);

DECODE_API const char * DECODE_CALL decod_getStringMigrationStorage(u8 u8Storage);
DECODE_API u32 DECODE_CALL decod_getMigrationStorage(const char * pstrStorage, u8 * pu8Storage);

/***************************************************************************
* Function Name: decod_getStringDebugLevel
* Description: get the string of the controller debug level
* Parameters:
*       [in] u8DebugLevel, controller debug level, from controller info page 0
*       ci_DebugLevel.
* Return: the debug level string
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringControllerDebugLevel(const u8 u8DebugLevel);

/***************************************************************************
* Function Name: decod_getControllerDebugLevel
* Description: get the debug level from the debug level string
* Parameters:
*       [in] pstrDebugLevel, the debug level string
*       [out] pu8DebugLevel, the debug level to be returned.
* Return: PIERR_NO_ERROR or PIERR_NOT_FOUND.
* Remarks: none.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getControllerDebugLevel(const char * pstrDebugLevel, u8 * pu8DebugLevel);

/***************************************************************************
* Function Name: decod_isValidBgaRate 
* Description: validate whether the bga rate is in valid range.
*       the valid bga rate range is 0 .. 99. 0 is lowest priority rate; 
*       99 is the highest priority rate.
* Parameters:    
*       [in] u32BgaRate, the bga rate.
* Return: PIERR_NO_ERROR, valid; PIERR_INVALID_BGA_RATE, invalid. 
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_validateBgaRate(const u32 u32BgaRate);
DECODE_API u32 DECODE_CALL decod_getBgaRate(const char * pstrRate, u8 * pu8Rate);
DECODE_API const char * DECODE_CALL decod_getStringBgaRate(u8 u8Rate);

/* --- logical drive ----------------------------------------------------- */

/***************************************************************************
* Function Name: decod_getBufferCountLogDrvInfo
* Description: get the count of logical drive(s) that the logical drive info 
*       buffer contains.
* Parameters:    
*       [in] pu8Buffer, the pointer to the logical drive info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [out] pu32Count, the count of logical drive (s) to be returned.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_logdrv_info_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the logical drive id.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountLogDrvInfo(const u8 * pu8Buffer, const u32 u32Length, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_locateBufferLogDrvInfo
* Description: locate the logical drive info with the specified logical drive
*       id. If the logical drive is not available in the buffer, locate the next
*       available one. 
* Parameters:    
*       [in] pu8Buffer, the pointer to the logical drive info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the logical drive id
*       [out] ppInfo, the pointer to the logical drive info of the specified
*           logical drive or of the next available one.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_logdrv_info_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the logical drive id.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferLogDrvInfo(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, u8 ** ppInfo);
    
/***************************************************************************
* Function Name: decod_locateBufferLogDrvSettings
* Description: locate the logical drive settings with the specified logical drive
*       id. If the logical drive is not available in the buffer, locate the next
*       available one. 
* Parameters:    
*       [in] pu8Buffer, the pointer to the logical drive settings data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the logical drive id
*       [out] ppSettings, the pointer to the logical drive settings of the specified
*           logical drive or of the next available one.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_logdrv_settings_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the logical drive id.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferLogDrvSettings(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, u8 ** ppSettings);
   
/***************************************************************************
* Function Name: decod_getStringLogDrvOpStatus
* Description: a simple way of get the string of the logical drive 
*       operational status. It only returns the most significant status.
* Parameters:    
*       [out] pstrOpStatus, the op status string to be returned.
*       [in] u32Flags, the logical drive flags.
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringLogDrvOpStatus(char * pstrOpStatus, const u32 u32Flags);

/***************************************************************************
* Function Name: decod_getStringLogDrvOpStatus
* Description: get the string of the full op status of a logical drive.
* Parameters:    
*       [out] pstrOpStatus, the op status string to be returned. This string
*           might be as long as 80 characters.
*       [in] u32Flags, the logical drive flags.
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringLogDrvOpStatusEx(char * pstrOpStatus, const u32 u32Flags);

/***************************************************************************
* Function Name: decod_getLogDrvOpStatus
* Description: get the op status of a logical drive
* Parameters:    
*       [in] u32Flags, the logical drive flags.
*       [out] u16OpStatus, the array of op status to be returned
*       [out] pu32OpStatusCount, the count of the op status in the array.
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getLogDrvOpStatus(const u32 u32Flags,
    u16 u16OpStatus[], u32 * pu32OpStatusCount);

/***************************************************************************
* Function Name: decod_getStringRAIDLevel
* Description: get the string of the RAID level. If the specified RAID level
*       code is invalid, the returned string will be "Unknown"
* Parameters:    
*       [in] u16RAIDLevel, the specified RAID level code
* Return: the RAID level string.
* Remarks: None.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringRAIDLevel(const u16 u16RAIDLevel);

DECODE_API const char * DECODE_CALL decod_getNumberRAIDLevel(const u16 u16RAIDLevel);
/***************************************************************************
* Function Name: decod_getRAIDLevel
* Description: get the RAID level of the raid level string
* Parameters:    
*       [in] pstrRAIDLevel, the raid level string
*       [out] pu16RAIDLevel, the RAID level code to be returned;
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: None.  
****************************************************************************/
DECODE_API const u32 DECODE_CALL decod_getRAIDLevel(const char * pstrRAIDLevel, u16 * pu16RAIDLevel);

/***************************************************************************
* Function Name: decod_isHybridRAIDLevel
* Description: check whether the raid level is a hybrid raid level
* Parameters:    
*       [in] u16RAIDLevel, the RAID level code
* Return: TRUE/FALSE
* Remarks: None.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isHybridRAIDLevel(const u16 u16RAIDLevel);

/***************************************************************************
* Function Name: decod_getStringLogDrvWritePolicy
* Description: get the string of logical drive write policy setting:
*       "WriteThru" or "WriteBack"
* Parameters:    
*       [in] u32Attrib, the logical drive attribute
* Return: the write policy setting string.
* Remarks: None.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringLogDrvWritePolicy(const u32 u32Attrib);

DECODE_API const char * DECODE_CALL decod_getStringLogDrvCurrentWritePolicy(const u32 u32Attrib);

/***************************************************************************
* Function Name: decod_getLogDrvWritePolicy
* Description: get the logical drive write policy setting by parsing the
*       input string
* Parameters:    
*       [in] pstrWritePolicy, the input string of the write policy. The valid
*           strings are: "WriteThru" and "WriteBack". They are not case sensitive.
*       [out] pu32Attrib, the write policy setting in the LD attribute
* Return: PIERR_NO_ERROR, or PIERR_INVALID_WRITE_POLICY
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getLogDrvWritePolicy(const char * pstrWritePolicy, u32 * pu32Attrib);

/***************************************************************************
* Function Name: decod_getStringLogDrvReadPolicy
* Description: get the string of logical drive read policy setting:
*       "NoCache", "ReadCache", or "ReadAhead".
* Parameters:    
*       [in] u32Attrib, the logical drive attribute
* Return: the read policy setting string.
* Remarks: None.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringLogDrvReadPolicy(const u32 u32Attrib);

/***************************************************************************
* Function Name: decod_getLogDrvReadPolicy
* Description: get the logical drive read policy setting by parsing the
*       input string
* Parameters:    
*       [in] pstrReadPolicy, the input string of the read policy. The valid
*           strings are: "NoCache", "ReadCache" and "ReadAhead". They are not 
*           case sensitive.
*       [out] pu32Attrib, the read policy setting in the LD attribute
* Return: PIERR_NO_ERROR, or PIERR_INVALID_WRITE_POLICY
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getLogDrvReadPolicy(const char * pstrReadPolicy, u32 * pu32Attrib);

/***************************************************************************
* Function Name: decod_getStringLogDrvCachePolicy
* Description: get the string of logical drive cache policy setting:
* Parameters:    
*       [in] u32Attrib, the logical drive attribute
* Return: the cache policy setting string.
* Remarks: None.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringLogDrvCachePolicy(const u32 u32Attrib);

/***************************************************************************
* Function Name: decod_getStringLogDrvInitStatus
* Description: get the logocal drive initialization status 
* Parameters:    
* Return: the string of the feature status. 
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringLogDrvInitStatus(const u32 u32Flags);
DECODE_API const char * DECODE_CALL decod_getStringLogDrvSyncStatus(const u32 u32Flags);

DECODE_API const char * DECODE_CALL decod_getStringLogDrvALUAAccessState(const u8 u8State);

/***************************************************************************
* Function Name: decod_isLogDrv<state/condition>
* Description: check whether the logical drive is in certain state or condition
* Parameters:    
*       [in] u32Flags/u32Attrib, the logical drive flags/attribute
* Return: TRUE or FALSE
* Remarks: None.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isLogDrvSynchronized(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvInitialized(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvInitializing(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvRebuilding(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvOnline(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvOffline(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isLogDrvCritical(const u32 u32Flags);

/***************************************************************************
* Function Name: decod_isSupportedStripeSize
* Description: check whether the stripe size is supported
* Parameters:    
*       [in] u32StripeSize, the specified stripe size in blocks
* Return: TRUE or FALSE
* Remarks: None.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isSupportedStripeSize(firmware_capabilities_t * pfc, const u32 u32StripeSize);
DECODE_API boolean_t decod_isSameFwVersion(int intMajorV, int intMinorV, int intBuildN, micISCSIiSNAPMicrocodeUpdate_t *pmiciscsiUpdate);
/***************************************************************************
* Function Name: decod_getLogDrvSectorSizeCode
* Description: get the encoded sector size from the sector size in number
*       bytes.
* Parameters:    
*       [in] u32SectorSize, the specified sector size in number of bytes
*       [out] pu8SectorSizeCode, the encoded sector size
* Return: PIERR_NO_ERROR or PIERR_INVALID_SECTOR_SIZE
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getLogDrvSectorSizeCode(u32 u32SectorSize, u8 * pu8SectorSizeCode);

/***************************************************************************
* Function Name: decod_getLogDrvSectorSize
* Description: get the sector size in number bytes from the encoded sector
*       size.
* Parameters:    
*       [in] u8SectorSizeCode, the encoded sector size
*       [out] pu32SectorSize, the sector size in number of bytes
* Return: PIERR_NO_ERROR or PIERR_INVALID_SECTOR_SIZE
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getLogDrvSectorSize(u8 u8SectorSizeCode, u32 * pu32SectorSize);

/***************************************************************************
* Function Name: decod_getStringLogDrvSerialNo
* Description: get the string of logical drive serial number
* Parameters:
*       [out] pstrSerialNo, the serial number string to be returned;
*       [in] pu8SerialNo, the serial number data from f/w
* Return: none.
* Remarks: none.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringLogDrvSerialNo(char * pstrSerialNo, const u8 * pu8SerialNo);

/***************************************************************************
* Function Name: DECODE_CALL decod_getLogDrvUserName
* Description: get the string of logical drive user defined name
* Parameters:
*       [out] pstrName, the name string to be returned;
*       [in] pu8Name, the user defined name data from f/w
* Return: none.
* Remarks: none.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringLogDrvUserName(char * pstrName, const u8 * pu8Name);

/* --- physical drive ---------------------------------------------------- */

DECODE_API u32 DECODE_CALL decod_locatePDPage0Settings(const u8 * pu8Buffer, const u32 u32Length, 
    u32 u32Index, micPDSetPage0Internal_t ** ppSettings);
DECODE_API u32 DECODE_CALL decod_locatePDPage1Settings(const u8 * pu8Buffer, const u32 u32Length, 
    u32 u32Index, micPDSettingsPage1Internal_t ** ppSettings);
DECODE_API u32 DECODE_CALL decod_locatePDPage3Settings(const u8 * pu8Buffer, const u32 u32Length, 
    u32 u32Index, micPDSettingsPage3Internal_t ** ppSettings);
DECODE_API u32 DECODE_CALL decod_locateBufferPhyDrvSettingsPrecise(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppSettings);

DECODE_API u32 DECODE_CALL decod_getPDSpeed(const char * pstrSpeed, u8 * pu8Value);
DECODE_API u32 DECODE_CALL decod_getPDTransferMode(const char * pstrTransferMode, u8 * pu8Value);
DECODE_API const char * DECODE_CALL decod_getStringPDUltraDMAMode(u8 u8Mode);
DECODE_API const char * DECODE_CALL decod_getStringPDMultiDMAMode(u8 u8Mode);
DECODE_API const char * DECODE_CALL decod_getStringPDDMAMode(u8 u8MultiMode, u8 u8UltraMode);

DECODE_API const char * DECODE_CALL decod_getStringPDCmdQueuingSupport(const u8 u8CmdQueuingSupport);
DECODE_API boolean_t DECODE_CALL decod_isPDCmdQueuingSupported(const u8 u8CmdQueuingSupport);

/***************************************************************************
* Function Name: decod_getBufferCountPhyDrvInfo
* Description: get the count of physical drive(s) that the logical drive info 
*       buffer contains.
* Parameters:    
*       [in] pu8Buffer, the pointer to the physical drive info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [out] pu32Count, the count of physical drive (s) to be returned.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_phydrv_info_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the physical drive id and page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountPhyDrvInfo(const u8 * pu8Buffer, 
    const u32 u32Length, u32 * pu32Count);


/***************************************************************************
* Function Name: decod_setPDConfigFlags
* Description: get physical drive config status.
* Parameters:
*       [in] pValue, the string of the physical drive config.
*       [out] u32Flags, the physical drive config flags.
* Return: void.
* Remarks: none.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_setPDConfigFlags(u8 *pValue, u32 *u32Flags);

/***************************************************************************
* Function Name: decod_locateBufferPhyDrvInfo
* Description: locate the physical drive info page with the specified physical
*       drive id and page code. If the physical drive is not available in the 
*       buffer, locate the next available one. 
* Parameters:    
*       [in] pu8Buffer, the pointer to the physical drive info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the physical drive id
*       [in] u16PageCode, the physical drive info page code
*       [out] ppInfo, the pointer to the physical drive info page of the 
*           specified physical drive or of the next available one.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_phydrv_info_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the physical drive id and page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferPhyDrvInfo(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppInfo);

/***************************************************************************
* Function Name: decod_locateBufferPhyDrvInfoPrecise
* Description: locate the physical drive info page with the specified physical
*       drive id and page code. If the physical drive is not available in the 
*       buffer, return an error of PIERR_NOT_FOUND. 
* Parameters:    
*       [in] pu8Buffer, the pointer to the physical drive info data buffer; 
*       [in] u32Length, the length of the buffer; 
*       [in] u32DevId, the physical drive id
*       [in] u16PageCode, the physical drive info page code
*       [out] ppInfo, the pointer to the physical drive info page of the 
*           specified physical drive.
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed.
* Remarks: The pu8Buffer points to a buffer of req_data_phydrv_info_t type.  
*       Assuming that the info in the buffer is in the ascending order of
*       the physical drive id and page code.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferPhyDrvInfoPrecise(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32DevId, const u16 u16PageCode, u8 ** ppInfo);

/***************************************************************************
* Function Name: decod_getStringPhyDrvOpStatus
* Description: a simple way of get the string of the physical drive 
*       operational status. It only returns the most significant op status. 
* Parameters:
*       [out] pstrOpStatus, the string of the physical drive operational status.
*       [in] u32Flags, the physical drive device flags.
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvOpStatus(char * pstrOpStatus, const u32 u32Flags);

/***************************************************************************
* Function Name: decod_getStringPhyDrvOpStatusEx
* Description: get all the phy drv op status in a string. 
* Parameters:
*       [out] pstrOpStatus, the string of the physical drive operational status.
*       [in] u32Flags, the physical drive device flags.
* Return: the string of the physical drive operational status.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvOpStatusEx(char * pstrOpStatus, const u32 u32Flags);

/***************************************************************************
* Function Name: decod_getPhyDrvOpStatus
* Description: get an array of all the operational status of the physical drive 
* Parameters:
*       [in] u32Flags, the physical drive device flags.
*       [out] u16OpStatus, the array of the op status to be returned
*       [out] pu32OpStatusSize, the size of the op status array.    
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getPhyDrvOpStatus(const u32 u32Flags, 
    u16 u16OpStatus[], u32 * pu32OpStatusCount);

/***************************************************************************
* Function Name: decod_getPhyDrvConfigStatus
* Description: get the string of physical drive configuration status
* Parameters:
*       [out] pstrConfigStatus, the config status to be returned;
*       [in] pPage0, the page 0 of the phy drv info.
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvConfigStatus(char * pstrConfigStatus, 
    const micPDInfoPage0_t * pPage0);
    
/***************************************************************************
* Function Name: decod_getStringPhyDrvLocation
* Description: get the string where the physical drive is located. If either
*       of the enclosure id and the slot id is 0xFFFF, the location string
*       will be "Unknown". Otherwise, the location string will be in the
*       format of "Encl <encl id> Slot <slot id>"
* Parameters:    
*       [out]pstrLocation, the location string to be returned
*       [in] u16EnclosureId, the enclosure id of the phy drv
*       [in] u16SlotId, the slot id of the phy drv
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvLocation(char * pstrLocation, 
    const u16 u16EnclosureId, const u16 u16SlotId);
    
/***************************************************************************
* Function Name: decod_getStringPhyDrvType
* Description: get the string of the physical drive type.
* Parameters:    
*       [in] u16Type, the type code
* Return: the string of the physical drive type.
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringPhyDrvType(const u16 u16Type);

/***************************************************************************
* Function Name: decod_getStringPhyDrvInterface
* Description: get the string of the physical drive interface. E.g. SATA 1.5G
* Parameters:    
*       [in] pPage0, the PD info page 0
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvInterface(char * pstrInterface,
    const micPDInfoPage0_t * pPage0, const micPDInfoPage3_t *pPage3);

/***************************************************************************
* Function Name: decod_getStringPhyDrvProtocolVersion
* Description: get the string of the physical drive protocol version.
* Parameters:
*       [out] pstrVersion, the protocal version string to be returned    
*       [in] u16Major, the major protocol version
*       [in] u16Minor, the minor protocol version
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvProtocolVersion(char * pstrVersion,
    const u16 u16Major, const u16 u16Minor);

/***************************************************************************
* Function Name: decod_getStringPhyDrvSpeed
* Description: get the string of the physical drive speed.
* Parameters:
*       [out] pstrVersion, the protocal version string to be returned    
*       [in] u8DriveSpeed
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvSpeed(char * pstrSpeed, u8 u8DriveSpeed);

/***************************************************************************
* Function Name: decod_getStringPhyDrvModel
* Description: get the string of the physical drive model.
* Parameters:
*       [out] pstrModel, the model string to be returned    
*       [in] pu8Model, the model data from f/w
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvModel(char * pstrModel,
    const u8 * pu8Model);
    
/***************************************************************************
* Function Name: decod_getStringPhyDrvSerialNo
* Description: get the string of the physical drive serial number.
* Parameters:
*       [out] pstrSerialNo, the serial number string to be returned    
*       [in] pu8SerialNo, the serial number data from f/w
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvSerialNo(char * pstrSerialNo,
    const u8 * pu8SerialNo);

/***************************************************************************
* Function Name: decod_getStringPhyDrvFirmwareRev
* Description: get the string of the physical drive firmware revision.
* Parameters:
*       [out] pstrRev, the revision string to be returned    
*       [in] pu8Rev, the drive f/w revision data from f/w
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringPhyDrvFirmwareRev(char * pstrRev,
    const u8 * pu8Rev);

/***************************************************************************
* Function Name: decod_isPhyDrvUnconfigured
* Description: check whether the physical drive is unconfigured (not in a
*       disk array and nor a spare
* Parameters:
*       [in] u32Flags, the phy drv flags
* Return: TRUE/FALSE
* Remarks: none.
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isPhyDrvUnconfigured(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isPhyDrvAccessible(const u32 u32Flags);

DECODE_API u32 DECODE_CALL decod_checkPhyDrvForConfig(const u32 u32Flags);
DECODE_API u32 DECODE_CALL decod_checkPhyDrvForRebuild(const u32 u32Flags);
DECODE_API u32 DECODE_CALL decod_checkPhyDrvForPDM(const u32 u32Flags);
DECODE_API u32 DECODE_CALL decod_checkPhyDrvForTransition(const u32 u32Flags);
    
/*
__u32 decod_getSATADiskDriveModel( const pmic_physicalDrv_t * pData, char * pBuf, __u32 u32BufLen );
__u32 decod_getSATADiskDriveSerialNumber( const pmic_physicalDrv_t * pData, char * pBuf, __u32 u32BufLen );
__u32 decod_getSATADiskDriveFirmwareRevision( const pmic_physicalDrv_t * pData, char * pBuf, __u32 u32BufLen );
*/

/* --- disk array  ------------------------------------------------------ */

DECODE_API u32 DECODE_CALL decod_getDANumOfTransitionPD(u8 * pu8Buffer, u32 * NumOfPD);
DECODE_API u32 DECODE_CALL decod_locateDATransitionPD(u8 * pu8Buffer, u32 index, micPDInfoPage0_t **);

/* from arrayInfo */
DECODE_API u32 DECODE_CALL decod_locateBufferNextArrayInfo(const u8 * pu8Buffer, 
    const u32 u32Length, const u32 u32DevId, u8 ** ppInfo);
DECODE_API u32 DECODE_CALL decod_getBufferCountArrayIDs(const u8 * pu8Buffer, 
    const u32 u32Length, u32 * pu32Count, u32 * pu32Ids);
DECODE_API u32 DECODE_CALL decod_locateBufferDiskArraySettings(const u8 * pu8Buffer, 
    const u32 u32Length, const u32 u32DevId, u8 ** ppSettings);

/* from arrayCfg */
/***************************************************************************
* Function Name: decod_getBufferCountDiskArrayCfg
* Description: get the count of the disk array in the buffer.
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the disk array info
*       [in] u32Length, the length of the data buffer
*       [out] pu32Count, the count of the disk arrays to be returned.
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountDiskArrayCfg(const u8 * pu8Buffer, 
    const u32 u32Length, u32 * pu32Count);

/* TBD
   all the disk array and spare decode routines should be re-do to conform the 
   way of getting next valid by the device id */
   
/***************************************************************************
* Function Name: decod_locateBufferNextDiskArrayCfg
* Description: locate the next disk array in the buffer starting from the
*       the giving index.
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the disk array info
*       [in] u32Length, the length of the data buffer
*       [in] u32IndexStart, the start index
*       [out] ppDiskArray, the pointer to the next disk array to be returned
*       [out] pu32ArrayLength, the length of the disk array info
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferNextDiskArrayCfg(const u8 * pu8Buffer, 
    const u32 u32Length, const  u32 u32IndexStart, 
    u8 ** ppDiskArray, u32 * pu32ArrayLength);

/***************************************************************************
* Function Name: decod_locateBufferNextPhyDrvInDiskArray
* Description: locate the next phy drv in the disk array buffer starting 
*       from the the giving index.
* Parameters:    
*       [in] pu8DiskArray, the data buffer that contains the disk array info
*       [in] u32Length, the length of the disk array info
*       [in] u32IndexStart, the start index
*       [out] ppPhyDrv, the pointer to the next phy drv to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferNextPhyDrvInDiskArray(const u8 * pu8DiskArray, 
    const u32 u32Length, const u32 u32IndexStart, u8 ** ppPhyDrv);

/***************************************************************************
* Function Name: decod_locateBufferNextLogDrvInDiskArray
* Description: locate the next log drv in the disk array buffer starting 
*       from the the giving index.
* Parameters:    
*       [in] pu8DiskArray, the data buffer that contains the disk array info
*       [in] u32Length, the length of the disk array info
*       [in] u32IndexStart, the start index
*       [out] ppLogDrv, the pointer to the next log drv to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferNextLogDrvInDiskArray(const u8 * pu8DiskArray, 
    const u32 u32Length, const u32 u32_IndexStart, u8 ** ppLogDrv);
DECODE_API u32 DECODE_CALL decod_locateBufferLogDrvInDaPrecise(const u8 * pu8DiskArray, 
    const u32 u32Length, const u32 u32DevId, u8 ** ppLogDrv);

/***************************************************************************
* Function Name: decod_locateBufferAxleInLogDrv
* Description: locate the specified axle in the logical drive definition buffer
* Parameters:    
*       [in] pu8LogDrv, the data buffer that contains the disk array info
*       [in] u16AxleNum, the axle number to identify the axle
*       [out] ppAxle, the pointer to the axle definition to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferAxleInLogDrv(const u8 * pu8LogDrv, 
    const u16 u16AxleNum, u8 ** ppAxle);

/***************************************************************************
* Function Name: decod_getStringDiskArrayOpStatus
* Description: get the op status string of a disk array.
* Parameters:
*       [out] pstrOpStatus, the op status string to be returned
*       [in] pu8DiskArray, disk array data buffer
*       [in] u32ArrayLength, the size of the disk array data buffer
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringDiskArrayOpStatus(char * pstrOpStatus, 
    const u8 * pu8DiskArray, const u32 u32ArrayLength);
DECODE_API void DECODE_CALL decod_getStringDiskArrayOpStatusEx(char * pstrOpStatus, 
    const u8 * pu8DiskArray, const u32 u32ArrayLength);
DECODE_API void DECODE_CALL decod_getStringDiskArrayIncompleteArrayStatus(char * pstrOpStatus, 
    const u8 * pu8DiskArray, const u32 u32ArrayLength);
/*
this may not be necessary for disk array.
void decod_getStringDiskArrayOpStatusEx(char * pstrOpStatus, const u32 u32Flags);
*/

/***************************************************************************
* Function Name: decod_getDiskArrayOpStatus
* Description: get the op status array of a disk array. The most significant
*       op status goes at u16OpStatus[0].
* Parameters:
*       [in] pu8DiskArray, disk array data buffer
*       [in] u32ArrayLength, the size of the disk array data buffer
*       [out] u16OpStatus, the op status array to be returned;
*       [out] pu32OpStatusCount, the count of the op status in the array    
* Return: none.
* Remarks: Disk Array Op status calculation
*       Unknown - disk array flag indicate disk array not present
*       OK - all the physical drives in the disk array are okay
*       PFA - at least one physical drive has PFA
*       Degraded - some phyiscal drive(s) dead or missing, but not all
*       Dead - all the physical drives are dead or missing
****************************************************************************/
DECODE_API void DECODE_CALL decod_getDiskArrayOpStatus(const u8 * pu8DiskArray, const u32 u32ArrayLength, 
    u16 u16OpStatus[], u32 * pu32OpStatusCount);

/***************************************************************************
* Function Name: decod_isDiskArrayMPEnabled
* Description: check whether Media Patrol is enabled on a disk array.
* Parameters:
*       [in] u32Flags, the disk array flags.    
* Return: TRUE or FALSE.
* Remarks: none.
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isDiskArrayPDMEnabled(const u32 u32Flags);
DECODE_API boolean_t DECODE_CALL decod_isDiskArrayMPEnabled(const u32 u32Flags);

/***************************************************************************
* Function Name: decod_getSupportedRAIDLevels
* Description: get the supported RAID levels suppported by the disk array
* Parameters:    
*       [in] u32NoOfPdInArray, the number of physical drives in the array
*       [out] pu16RAIDLevels, the supported RAID levels will be returned here
*       [out] pu32Count, the count of the RAID levels
* Return: none.
* Remarks: none.
****************************************************************************/
DECODE_API void DECODE_CALL decod_getSupportedRAIDLevels(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u32 u32NoOfPdInArray,
    u16 * pu16RAIDLevels, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_isSupportedRAIDLevel
* Description: check whether the raid level is supported by the disk array
* Parameters:    
*       [in] u16RaidLevel, the raid level
*       [in] u32NoOfPdInArray, the number of physical drives in the disk array
* Return: TRUE/FALSE.
* Remarks: none.
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isSupportedRAIDLevel(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u16 u16RaidLevel, 
    const u32 u32NoOfPdInArray);

/***************************************************************************
* Function Name: decod_getStringSupportedRAIDLevels
* Description: get the supported RAID levels suppported by the disk array
* Parameters:    
*       [out] pstrRAIDLevels, the string will be returned here
*       [in] u32NoOfPdInArray, the number of physical drives in the disk array
* Return: none.
* Remarks: none.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringSupportedRAIDLevels(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    char * pstrRAIDLevels, const u32 u32NoOfPdInArray);

/***************************************************************************
* Function Name: decod_getAutoRaidLevelAndAxle
* Description: get the auto raid level based on the number of physical drives
*       in the disk array
* Parameters:    
*       [in] u32NoOfPdInArray, the number of physical drives in the disk array
*       [out] pu8RaidLevel, the auto raid level to return;
*       [out] pu16NoOfAxles, the number of axles to return;
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getAutoRaidLevelAndAxle(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u32 u32NoOfPdInArray,
    u8 * pu8RaidLevel, u16 * pu16NoOfAxles);
    
/***************************************************************************
* Function Name: decod_getAutoAxle
* Description: get the auto number of axles based on the number of physical 
*       drives in the disk array and the raid level
* Parameters:    
*       [in] u32NoOfPdInArray, the number of physical drives in the disk array
*       [out] pu8RaidLevel, the auto raid level to return;
*       [out] pu16NoOfAxles, the number of axles to return;
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getAutoAxle(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u32 u32NoOfPdInArray, const u8 u8RaidLevel,
    u16 * pu16NoOfAxles); 

/***************************************************************************
* Function Name: decod_getMinimumAxle
* Description: get the minimum number of axles based on the number of physical 
*       drives in the disk array and the raid level
* Parameters:    
*       [in] u32NoOfPdInArray, the number of physical drives in the disk array
*       [out] pu8RaidLevel, the auto raid level to return;
*       [out] pu16NoOfAxles, the number of axles to return;
* Return: u16NoOfAxles
* Remarks: none.  
****************************************************************************/
DECODE_API u16 DECODE_CALL decod_getMinimumAxle(firmware_capabilities_t * pfc,
    const u32 u32NoOfPdInArray, const u8 u8RaidLevel); 	
/***************************************************************************
* Function Name: decod_isR5and6AlgorithmApplicable
* Description: check whether R5 algorithm setting is applicable for the 
*       RAID level
* Parameters:    
*       [in] u16RaidLevel, the RAID level
* Return: TRUE - applicable; FALSE - not applicable
* Remarks: none.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isR5and6AlgorithmApplicable(const u16 u16RaidLevel); 

/***************************************************************************
* Function Name: decod_getRAID6ParityPace
* Description: get RAID6 parity pace as string
* Parameters:
*       [in/out] pStr, the data buffer returned
*       [in] u8ParityPace
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.
****************************************************************************/
DECODE_API u32 decod_getRAID6ParityPace(char * pStr, u8 u8ParityPace);

/***************************************************************************
* Function Name: decod_getRAID6CodecScheme
* Description: get RAID6 codec scheme as string
* Parameters:
*       [in/out] pStr, the data buffer returned
*       [in] u8CodecScheme
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.
****************************************************************************/
DECODE_API u32 decod_getRAID6CodecScheme(char * pStr, u8 u8CodecScheme);
/***************************************************************************
* Function Name: decod_validateR5Algorithm
* Description: check whether R5 algorithm setting is valid
* Parameters:    
*       [in] u8R5Algorithm, the RAID5 algorithm
* Return: PIERR_NO_ERROR - valid; PIERR_INVALID_R5_ALGORITHM - invalid
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_validateR5Algorithm(const u8 u8R5Algorithm);

DECODE_API const char * DECODE_CALL decod_getStringR5Algorithm(const u8 u8R5Algorithm);

/***************************************************************************
* Function Name: decod_getDiskArrayPhysicalSize
* Description: get the physical capacity of the disk array. The physical
*       capacity is the total size of all the physical drives in the disk array.
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [out] pu64Size, the physical size to be returned in blocks
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayPhysicalSize(const u8 * pu8Array, u64 * pu64Size);

/***************************************************************************
* Function Name: decod_getDiskArrayConfigurableSize
* Description: get the total configurable size of the disk array. 
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [out] pu64Size, the physical size to be returned in bytes
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayConfigurableSize(const u8 * pu8Array, u64 * pu64Size);

/***************************************************************************
* Function Name: decod_getPartitionConfigurableSize
* Description: get the configurable size of each partition of the disk array.
*       It is the configurable size of the smallest drive in the disk array. 
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [out] pu64PartitionSize, the parition configurable size to be returned
*           in bytes
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getPartitionConfigurableSize(const u8 * pu8Array, u64 * pu64PartitionSize);

/***************************************************************************
 * Function Name: decod_getPartitionMaxConfigurableSize
 * Description: get the mamximum configurable size of each partition of the disk array.
 *       It is the configurable size of the largest drive in the disk array.
 * Parameters:
 *       [in] pu8Array, the data buffer contains the disk array info
 *       [out] pu64PartitionSize, the maximum parition size to be returned
 *           in bytes
 * Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
 * Remarks: none.
 ****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getPartitionMaxConfigurableSize(const u8 * pu8Array, u64 * pu64PartitionSize);

/***************************************************************************
* Function Name: decod_getDiskArrayAvailableSize
* Description: get the total free spaces available for configuration on the
*       stordisk array
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [out] pu64Size, the physical size to be returned in bytes
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayAvailableSize(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u8 * pu8Array, const u32 u32ArrayLength, 
    u64 * pu64Size);

/***************************************************************************
* Function Name: decod_getDiskArrayPhyDrvFreeSize
* Description: get the free configurable size of a physical drive in a disk array
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [in] u32ArrayLength, the size of the disk array buffer
*       [in] u16PhyDrvId, the physical drive id
*       [out] pu64Size, the free configurable size to be returned in bytes
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayPhyDrvFreeSize(const u8 *pu8Array, const u32 u32ArrayLength,
    const u16 u16PhyDrvId, u64 * pu64Size);
    
/***************************************************************************
* Function Name: decod_getDiskArrayMaxSupportedSize
* Description: get the size of max free slices available for configuration on
*        the disk array
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [in] u32ArrayLength, the size of the disk array buffer
*       [out] pu64Size, the max free slice size to be returned in bytes
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayMaxSupportedSize(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u8 * pu8Array, const u32 u32ArrayLength, 
    u64 * pu64Size);

/***************************************************************************
* Function Name: decod_getDiskArrayFreeFragments
* Description: get the free fragments of the disk array
* Parameters:    
*       [in] pu8Array, the data buffer contains the disk array info
*       [in] u32ArrayLength, the size of the disk array buffer
*       [out] pFragments, the fragment information to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getDiskArrayFreeFragments(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u8 * pu8Array, const u32 u32ArrayLength, 
    disk_array_free_fragment_t * pFragments);

/***************************************************************************
* Function Name: decod_removeFragment
* Description: remove a fragment from the fragment list
* Parameters:    
*       [in/out] pFragments, the fragment list
*       [in] u32IndRemove, the index of the fragment to be removed
* Return: void
* Remarks: none.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_removeFragment(disk_array_free_fragment_t * pFragments,
    u32 u32IndRemove);

/***************************************************************************
* Function Name: decod_breakFragments
* Description: Break a fragment list by a drive partition
* Parameters:    
*       [in/out] pFragments, the fragment list
*       [in] u64StartBlock, drive partition start block
*       [in] u64NoOfBlock, drive partition in block
* Return: void
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_breakFragments(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    disk_array_free_fragment_t * pFragments,
    const u64 u64StartBlock, const u64 u64NoOfBlock);

/***************************************************************************
* Function Name: decod_convertPhySizeToLogSize
* Description: convert the physical raw size to the logical drive size according
*       to the RAID configuration parameters. It will first round up the
*       physical size to the stripe size, then do the calculation.
* Parameters:    
*       [in] u64PhySize, the physical (raw) size taken from a disk array 
*           crossing all the physical drives in the array
*       [in] u16NoOfPd, the number of physical drives in the disk array
*       [in] u16RaidLevel, the raid level of the logical drive
*       [in] u16NoOfAxle, the number of axels, valid only for Hybrid RAID levels
*       [in] u32StripeSize, the stripe size of the logical drive
* Return: the logical size of the logical drive.
* Remarks: unit of the input sizes (u64PhySize and u32StripeSize) should be 
*   consistent. The output unit is the same as the input. If input unit is
*   bytes, the output is also bytes; if input is blocks, so is the output.
****************************************************************************/
DECODE_API u64 DECODE_CALL decod_convertPhySizeToLogSize(const u64 u64PhySize, const u16 u16NoOfPd, 
    const u16 u16RaidLevel, const u16 u16NoOfAxle, const u32 u32StripeSize);
    
/***************************************************************************
* Function Name: decod_convertLogSizeToPhySize
* Description: convert the logical drive size to its physical (raw) size 
*       according to the RAID configuration parameters. It will make sure
*       the physical raw size is rounded up to the stripe size.
* Parameters:    
*       [in] u64LogSize, the logical size of the logical drive
*       [in] u16NoOfPd, the number of physical drives in the disk array
*       [in] u16RaidLevel, the raid level of the logical drive
*       [in] u16NoOfAxle, the number of axels, valid only for Hybrid RAID levels
*       [in] u32StripeSize, the stripe size of the logical drive
* Return: the physical (raw) size occupied by the logical drive
* Remarks: unit of the input sizes (u64LogSize and u32StripeSize) should be 
*   consistent. The output unit is the same as the input. If input unit is
*   bytes, the output is also bytes; if input is blocks, so is the output.
****************************************************************************/
DECODE_API u64 DECODE_CALL decod_convertLogSizeToPhySize(const u64 u64LogSize, const u16 u16NoOfPd, 
    const u16 u16RaidLevel, const u16 u16NoOfAxle, const u32 u32StripeSize);

/***************************************************************************
* Function Name: decod_convertPartitionSizeToLogSize
* Description: conver the partition size of the logical size of the logical
*       drive according to the RAID configuration parameters. Partition size
*       is the space that to be occuppied on each of the physical drives of 
*       the disk array. It will first round up the partition size to the 
*       stripe size, then do the calculation.
* Parameters:    
*       [in] u64PartitionSize, the partition size
*       [in] u16NoOfPd, the number of physical drives in the disk array
*       [in] u16RaidLevel, the raid level of the logical drive
*       [in] u16NoOfAxle, the number of axels, valid only for Hybrid RAID levels
*       [in] u32StripeSize, the stripe size of the logical drive
* Return: logical size of the logical drive
* Remarks: unit of the input sizes (u64PartitionSize and u32StripeSize) should be 
*   consistent. The output unit is the same as the input. If input unit is
*   bytes, the output is also bytes; if input is blocks, so is the output.
****************************************************************************/
DECODE_API u64 DECODE_CALL decod_convertPartitionSizeToLogSize(const u64 u64PartitionSize, 
    const u16 u16NoOfPd, const u16 u16RaidLevel, const u16 u16NoOfAxle,
    const u32 u32StripeSize);

/***************************************************************************
* Function Name: decod_convertLogSizeToPartitionSize
* Description: conver the logical size of the logical to the partition size
*       drive according to the RAID configuration parameters. Partition size
*       is the space that to be occuppied on each of the physical drives of 
*       the disk array. It will round up the partition size to the stripe size.
* Parameters:    
*       [in] u64LogSize, the logical size of the logical drive
*       [in] u16NoOfPd, the number of physical drives in the disk array
*       [in] u16RaidLevel, the raid level of the logical drive
*       [in] u16NoOfAxle, the number of axels, valid only for Hybrid RAID levels
*       [in] u32StripeSize, the stripe size of the logical drive
* Return: the partition size
* Remarks: unit of the input sizes (u64LogSize and u32StripeSize) should be 
*   consistent. The output unit is the same as the input. If input unit is
*   bytes, the output is also bytes; if input is blocks, so is the output.
****************************************************************************/
DECODE_API u64 DECODE_CALL decod_convertLogSizeToPartitionSize(const u64 u64LogSize, 
    const u16 u16NoOfPd, const u16 u16RaidLevel, const u16 u16NoOfAxle, 
    const u32 u32StripeSize);

/***************************************************************************
* Function Name: decod_logSizeToPartitionSizeNoRounding
* Description: conver the logical size of the logical to the partition size
*       drive according to the RAID configuration parameters. Partition size
*       is the space that to be occuppied on each of the physical drives of 
*       the disk array. It will NOT round up the partition size to the stripe size.
* Parameters:    
*       [in] u64LogSize, the logical size of the logical drive
*       [in] u16NoOfPd, the number of physical drives in the disk array
*       [in] u16RaidLevel, the raid level of the logical drive
*       [in] u16NoOfAxle, the number of axels, valid only for Hybrid RAID levels
* Return: the partition size
* Remarks: unit of the input sizes (u64LogSize) should be 
*   consistent. The output unit is the same as the input. If input unit is
*   bytes, the output is also bytes; if input is blocks, so is the output.
****************************************************************************/
DECODE_API u64 DECODE_CALL decod_logSizeToPartitionSizeNoRounding(const u64 u64LogSize, 
    const u16 u16NoOfPd, const u16 u16RaidLevel, const u16 u16NoOfAxle);
    
/***************************************************************************
* Function Name: decod_isValidAxle
* Description: check the number of axles is valid giving the raid level and
*       the number of physical drive in the disk array
* Parameters:    
*       [in] u16RaidLevel, the raid level
*       [in] u16NoOfAxle, the number of axels
*       [in] u16NoOfPd, the number of physical drive in the disk array
* Return: TRUE, valid; FALSE, invalid.
* Remarks: none.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isValidAxle(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    const u16 u16RaidLevel, const u16 u16NoOfAxle,
    const u16 u16NoOfPd);
    
/* --- spare ------------------------------------------------------------- */

/***************************************************************************
* Function Name: decod_getBufferCountSpareInfo
* Description: get the count of spares in the data buffer
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the spare info
*       [in] u32Length, the length of the data buffer
*       [out] pu32Count, the count to be returned
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountSpareInfo(const u8 * pu8Buffer, 
    const u32 u32Length, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_locateBufferNextSpareInfo
* Description: locate the next spare in the buffer starting from the
*       the giving index.
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the spare info
*       [in] u32Length, the length of the data buffer
*       [in] u32IndexStart, the start index
*       [out] ppSpare, the spare to be returned;
*       [out] pu32SpareLength, the length of the next spare info
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferNextSpareInfo(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32IndexStart, u8 ** ppSpare, u32 * pu32SpareLength);

/***************************************************************************
* Function Name: decod_locateBufferSpareInfo
* Description: locate the spare configuration info of the next valid spare
*       with the spcified spare array id.
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the spare info
*       [in] u32Length, the length of the data buffer
*       [in] u32SpareArrayId, the spare array id
*       [out] ppSpare, the spare to be returned;
*       [out] pu32SpareLength, the length of the next spare info
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferSpareInfo(const u8 * pu8Buffer, const u32 u32Length,
    const u32 u32SpareArrayId, u8 ** ppSpare, u32 * pu32SpareLength);

/***************************************************************************
* Function Name: decod_locateBufferNextSpareInfoOfArray
* Description: locate the next spare in the buffer starting from the
*       the giving index.
* Parameters:    
*       [in] pu8Buffer, the data buffer that contains the spare info
*       [in] u32Length, the length of the data buffer
*       [in] u32IndexStart, the start index
*       [in] u32ArrayId, the id of the specified disk array
*       [out] ppSpare, the spare to be returned;
*       [out] pu32SpareLength, the length of the next spare info
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_locateBufferNextSpareInfoOfArray(const u8 * pu8Buffer, 
    const u32 u32Length, const u32 u32IndexStart, const u32 u32ArrayId, 
    u8 ** ppSpare, u32 * pu32SpareLength);
    
/***************************************************************************
* Function Name: decod_getStringSpareType
* Description: get the spare type string
* Parameters:    
*       [in] u32SpareArrayAttrib, the spare disk array attribute
* Return: the spare type string
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringSpareType(const u32 u32SpareArrayAttrib);

/***************************************************************************
* Function Name: decod_isSpareTemporary
* Description: check whether the spare is a temporary spare
* Parameters:    
*       [in] u32SpareArrayFlags, the spare disk array flags
* Return: TRUE: yes; FALSE, no
* Remarks: none.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isSpareTemporary(const u32 u32SpareArrayFlags);
    
/***************************************************************************
* Function Name: decod_isSpareDedicated
* Description: check whether the spare is a dedicated spare
* Parameters:    
*       [in] u32SpareArrayAttrib, the spare disk array attributes
* Return: TRUE: yes; FALSE, no
* Remarks: none.  
****************************************************************************/
DECODE_API boolean_t DECODE_CALL decod_isSpareDedicated(const u32 u32SpareArrayAttrib);

/* --- background activity ----------------------------------------------- */

/***************************************************************************
* Function Name: decod_getStringBGAState
* Description: get the string of BGA state
* Parameters:    
*       [in] u8State, the bga state code from f/w
* Return: the string of the bga state
* Remarks: none.  
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringBGAState(const u8 u8State);
DECODE_API const char * DECODE_CALL decod_getStringRebuildType(const u8 u8Type);

/***************************************************************************
* Function Name: decod_getBufferCountRebuildProgress
* Description: get number of rebuild progress info entities in the buffer
* Parameters:    
*       [in] pu8Data, the data buffer returned by the f/w of get rebuild
*           progress command
*       [in] u32DataSize, the size of the buffer
*       [out] pu32Count, the number of entities to be returned
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountRebuildProgress(const u8 * pu8Data, 
    const u32 u32DataSize, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_getBufferCountLdiProgress
* Description: get number of ld init progress info entities in the buffer
* Parameters:    
*       [in] pu8Data, the data buffer returned by the f/w of get ld init
*           progress command
*       [in] u32DataSize, the size of the buffer
*       [out] pu32Count, the number of entities to be returned
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountLdiProgress(const u8 * pu8Data, 
    const u32 u32DataSize, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_getBufferCountSynchProgress
* Description: get number of ld synch progress info entities in the buffer
* Parameters:    
*       [in] pu8Data, the data buffer returned by the f/w of get ld synch
*           progress command
*       [in] u32DataSize, the size of the buffer
*       [out] pu32Count, the number of entities to be returned
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountSynchProgress(const u8 * pu8Data, 
    const u32 u32DataSize, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_getBufferCountRCProgress
* Description: get number of redundancy check progress info entities in the buffer
* Parameters:    
*       [in] pu8Data, the data buffer returned by the f/w of get ld RC
*           progress command
*       [in] u32DataSize, the size of the buffer
*       [out] pu32Count, the number of entities to be returned
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountRCProgress(const u8 * pu8Data, 
    const u32 u32DataSize, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_getBufferCountSCProgress(const u8 * pu8Data, 
    const u32 u32DataSize, u32 * pu32Count);
DECODE_API const char * DECODE_CALL decod_getStringSCStatus(const u8 u8State);

/* --- event ---------------------------------------------------------------- */

/***************************************************************************
* Function Name: decod_getBufferCountEventInfo
* Description: get number of event info entities in the buffer
* Parameters:    
*       [in] pu8Data, the data buffer returned by the f/w of get event info
*           command
*       [in] u32DataSize, the size of the buffer
*       [out] pu32Count, the number of entities to be returned
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getBufferCountEventInfo(const u8 * pu8Data,
    const u32 u32DataSize, u32 * pu32Count);

/***************************************************************************
* Function Name: decod_getStringEventTimeStamp
* Description: get the string of event time stamp
* Parameters:    
*       [out] pstrTime, the string of time stamp to be returned
*       [in] u32TimeStamp, the event time stamp from f/w
* Return: none.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getStringEventTimeStamp(char * pstrTime, const u32 u32TimeStamp);

DECODE_API u32 DECODE_CALL decod_getStringEventLocalTimeStamp(char * pstrTime,
    const u32 u32TimeStamp);

/***************************************************************************
* Function Name: decod_getStringEventDeviceId
* Description: get the string of event device id
* Parameters:    
*       [out] pstrDeviceId, the string of time stamp to be returned
*       [in] pEvent, the event
* Return: none.
* Remarks: none.  
****************************************************************************/
DECODE_API void DECODE_CALL decod_getStringEventDeviceId(char * pstrDeviceId, const Event_t * pEvent);

DECODE_API u32 DECODE_CALL decod_getStringEventInfo(u8 * pstrInfo, u32 * pu32Length, const Event_t * pEvent);

/***************************************************************************
* Function Name: decod_validateEventLocation
* Description: validate whether the event location is valid or not
* Parameters:    
*       [in] u8EventLocation, the event location
* Return: PIERR_NO_ERROR - valid; PIERR_INVALID_EVENT_LOCATION - invalid.
* Remarks: none.  
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_validateEventLocation(const u8 u8EventLocation);

/* --- iscsi info and settings ---------------------------------------------- */

DECODE_API const char * DECODE_CALL decod_getStringISCSIPortDigestMethod(u8 u8DigestMethod);
DECODE_API const char * DECODE_CALL decod_getStringISCSISessionDeviceType(u32 u32OptionFlag);
DECODE_API const char * DECODE_CALL decod_getStringISCSISessionState(u32 u32SessionState);
DECODE_API void DECODE_CALL decod_getStringISCSISessionISID(char *pstrISID, u8 * u8ISID);
DECODE_API boolean_t DECODE_CALL decod_isiSCSIDeviceAccessControlEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeImmediateDataEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeInitialR2TEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeHeaderDigestEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeDataDigestEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeUniChapAuthEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeBiChapAuthEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeAccessControlEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeDataPDUInorderEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeDataSeqInorderEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeNOPActiveEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSINodeEnabled(const u32 u32OptionFlag);
DECODE_API const char * DECODE_CALL decod_getStringISCSINodeStatus(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isiSCSIPortMarkerEnabled(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isSLPSAEnabled(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isSLPUseDA(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isSLPAutoDAIP(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isISNSEnabled(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isISNSEsiEnabled(u32 u32Flag);
DECODE_API boolean_t DECODE_CALL decod_isISNSAutoIP(u32 u32Flag);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfSLPPort(u8 * pu8Data, u32 * pu32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfISNSPort(u8 * pu8Data, u32 * pu32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfPorts(u8 * pu8Data, u32 * u32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfPortSettings(u8 * pu8Data, u32 * u32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfTcpIpPorts(u8 * pu8Data, u32 * u32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfTcpIpSettings(u8 * pu8Data, u32 * u32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_getISCSINumOfSessions(u8 * pu8Data, u32 * u32NumOfSessions);
DECODE_API u32 DECODE_CALL decod_getNodeInfoNumOfNode(u8 * pu8Data, u32 * pu32NumOfNode);
DECODE_API u32 DECODE_CALL decod_getNumOfmutNode(u8 * pu8Data, u32 * pu32NumOfRecords);
DECODE_API u32 DECODE_CALL decod_getNumOfPortal(u8 * pu8Data, u32 * pu32NumOfRecords);
DECODE_API u32 DECODE_CALL decod_locateNodeInfoData(u8 * pu8Data, u32 u32Index, micNodeData_t ** ppData);
DECODE_API u32 DECODE_CALL decod_getLinkAggrNumOfRecords(u8 * pu8Data, u32 * pu32NumOfRecords);
DECODE_API u32 DECODE_CALL decod_locateLinkAggrRecord(u8 * pu8Data, u32 u32Index, micLinkAggrInfoSettingsData_t ** ppRecord);
DECODE_API u32 DECODE_CALL decod_getVLANNumOfRecords(u8 * pu8Data, u32 * pu32NumOfRecords);
DECODE_API u32 DECODE_CALL decod_locateVLANRecord(u8 * pu8Data, u32 u32Index, micVLANInfoSettingsData_t * * ppRecord);
DECODE_API u32 DECODE_CALL decod_getChapNumOfRecords(u8 * pu8Data, u32 * u32NumOfPorts);
DECODE_API u32 DECODE_CALL decod_locateChapRecord(u8 *pu8Data, u32 u32Index, micCHAPRecord_t **ppRecord);
DECODE_API u32 DECODE_CALL decod_getChapFlagType(const char * pstrType, u32 * pu32Flag);
DECODE_API const char * DECODE_CALL decod_getStringChapFlagType(u32 u32Flag);
DECODE_API u32 DECODE_CALL decod_locateMutNodeRecord(u8 * pu8Data, u32 u32Index,ExtendedNodeParameterData_t ** ppRecord);
DECODE_API u32 DECODE_CALL decod_locatePortalRecord(u8 * pu8Data, u32 u32Index, micISCSIPortalInfoData_t ** ppRecord);
DECODE_API u32 DECODE_CALL decod_locateISCSINodeInfoSetting(u8 * pu8Data, u32 u32index, ExtendedNodeParameterData_t ** pmicNode);
DECODE_API u32 DECODE_CALL decod_locateISCSIPortData(u8 * pu8Data, u32 u32index, TargetPortData_t ** pmicPort);
DECODE_API u32 DECODE_CALL decod_locateISCSIPortStats(u8 * pu8Data, u32 u32devId, u8 ** pmicStats);
DECODE_API u32 DECODE_CALL decod_locateISCSIPortSBStats(u8 * pu8Data, u32 u32devId, u8 ** pmicStats);
DECODE_API u32 DECODE_CALL decod_locateISCSISessStats(u8 * pu8Data, u32 u32devId, u8 ** pmicStats);
DECODE_API u32 DECODE_CALL decod_locateISCSIPortSetting(u8 * pu8Data, u32 u32index, TargetPortSettings_t ** pmicPort);
DECODE_API u32 DECODE_CALL decod_locateISCSITcpIpData(u8 * pu8Data, u32 u32index, micISCSITcpIpAdvOptions_t ** pmicPort);
DECODE_API u32 DECODE_CALL decod_locateISCSITcpIpSettings(u8 * pu8Data, u32 u32index, micISCSITcpIpAdvOptions_t ** pmicPort);
DECODE_API u32 DECODE_CALL decod_locateISCSISessionData(u8 * pu8Data, u32 u32index, micISCSISessionData_t ** pmicSession);
DECODE_API u32 DECODE_CALL decod_locateISCSISLPData(u8 * pu8Data, u32 u32Index, micSLPConfigPage_t ** ppData);
DECODE_API u32 DECODE_CALL decod_locateISCSIISNSData(u8 * pu8Data, u32 u32Index, micISNSConfigData_t ** ppData);

/* flash upload */
DECODE_API u32 DECODE_CALL decod_getFlashProgress(u8 * pStatus, flash_progress_t * pProgress);

/* enclosure and fru */
DECODE_API const char * DECODE_CALL decod_getStringEnclosureType(const u8 u8EnclType);
DECODE_API u32 DECODE_CALL decod_getMaxNumOfFrus(const MEI_t * pmicEnclInfo, const u8 u8FruType, u8 * pu8Max);

DECODE_API const char * DECODE_CALL decod_getStringFanStatus(unsigned char fanStatus, unsigned char psuStatus);
DECODE_API const char * DECODE_CALL decod_getStringBlowerStatus(unsigned char fanStatus);
DECODE_API const char * DECODE_CALL decod_getStringPsuStatus(unsigned char psuStatus);
DECODE_API void DECODE_CALL decod_getStringTemperature(char * pstrTemp, u8 temp, u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringTemperaturStatus(u8 u8Temp, u8 u8WarningThreshold, u8 u8CriticalThreshold);

DECODE_API void DECODE_CALL decod_getStringVoltageSensorType(
    char * pstrVoltage, MEI_t * pmicInfo, u8 u8SensorId, u8 * pu8SensorType);
DECODE_API void DECODE_CALL decod_getStringVoltageHealthyThreshold(
    char * pstrVoltage, MEI_t * pmicInfo, u8 u8SensorId);
DECODE_API void DECODE_CALL decod_getStringVoltage(char * pstrVolt, u8 volt);
DECODE_API u8 DECODE_CALL decod_getVoltageStatus(MEI_t * pmicInfo, u8 voltId, u8 * pu8Data);
DECODE_API void DECODE_CALL decod_getStringVoltageStatus(char * pstrVoltageStatus, MEI_t * pmicInfo, u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringBatteryStatus(unsigned char psuStatus);
DECODE_API void DECODE_CALL decod_getStringBatteryDate(char * pstrVolt, u16 date);
DECODE_API void DECODE_CALL decod_getStringBatteryChemistryType(char * pstrType, const u8 * pu8Chemistry);
DECODE_API void DECODE_CALL decod_getStringBatterySerialNum(char * pstrSerial, const u16 u16SerialNum,
    micControllerInfoPage0_t * pPage0);
DECODE_API u32 DECODE_CALL decod_getStringBatteryHoldTime(u8 * u8HoldTime, MBI_t * pmicInfo,
    micControllerInfoPage0_t * pPage0, micControllerInfoPage2_t * pPage2);
DECODE_API u32 DECODE_CALL decod_getStringBatteryCellType(u8 * u8CellType, MBI_t * pmicInfo,
    micControllerInfoPage0_t * pPage0);

DECODE_API u8 DECODE_CALL decod_getEnclFanStatus(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u32 DECODE_CALL decod_getEnclFanSpeed(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclPsuStatus(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclSlotLocation(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclVoltage(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclTemperature(MEI_t * pmicInfo, u8 id, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclPollInterval(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclCtrlTemp(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclTempThWarning(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclTempThCritical(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclCtrlTempThWarning(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u8 DECODE_CALL decod_getEnclCtrlTempThCritical(MEI_t * pmicInfo, u8 * pu8Data);
DECODE_API u32 DECODE_CALL decod_locateFruInfo(u8 * pu8Data, MFRU_t ** ppFruInfo);
DECODE_API const char * DECODE_CALL decod_getStringFruType(u16 u16Type);

DECODE_API u32 DECODE_CALL decod_getNumOfMissingPD(u8 * pu8Data);

DECODE_API u32 DECODE_CALL decod_locateNetworkSettings(const u8 * pu8Buffer, const u32 u32Length,
    const u16 u16PageCode, const u32 u32DevId, const u32 u32PortId, 
    u8 ** ppPort);
DECODE_API const char * DECODE_CALL decod_getStringPortLinkStatus(u8 u8Status);

/* migration */
DECODE_API u32 DECODE_CALL decod_getBufferCountMigrationProg(const u8 *pData, const u32 u32Length, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_locateBufferMigrationProg(const u8 *pData, const u32 u32Length, const u32 u32DevID, u8 ** ppmicInfo);

/* LMM */
DECODE_API u32 DECODE_CALL decod_getNumOfInitiator(u8 * pu8Data, u32 * pu32NumOfInitiator);
DECODE_API u32 DECODE_CALL decod_locateBufferInitiator(u8 * pu8Data, u32 u32Index, u8 ** ppInitiator);
DECODE_API u32 DECODE_CALL decod_getNumOfLMMEntry(u8 * pu8Data, u32 * pu32NumOfLMM);
DECODE_API u32 DECODE_CALL decod_locateBufferLMMEntry(u8 * pu8Data, u32 u32Index, u8 ** ppLMMEntry);

/* Stats */
DECODE_API u32 DECODE_CALL decod_getBufferCountStats(const u8 *pData, const u32 u32Length, u8 u8Type, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_locateBufferStatistics(const u8 *pData, const u32 u32Length, const u32 u32DevID, u8 u8Type, u8 ** ppmicStats);

/* Performance Stats */
DECODE_API u32 DECODE_CALL decod_getBufferCountPerfStats(const u8 *pData, const u32 u32Length, u8 u8Type, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_locateBufferPerfStats(const u8 *pData, const u32 u32Length, const u32 u32Index, u8 u8Type, u8 ** ppPerfStats);

DECODE_API void DECODE_CALL decod_getStringStatsNumber(u64 u64Size , char * pstrResult);
/***************************************************************************
* Function Name: decod_getStrEventSpecificData
* Description: get event specific data as string
* Parameters:
*       [in/out] pStr, the data buffer returned
*       [in] u32Length, the size of the buffer
*       [in] pEvent, the pointer of event
* Return: PIERR_NO_ERROR, suceeded; otherwise, failed
* Remarks: none.
****************************************************************************/
DECODE_API u32 decod_getStrEventSpecificData(char * pStr, u32 u32Length, Event_t * pEvent);

DECODE_API u32 decod_getStatusFlashImageType(ih_t * pi);

DECODE_API const char * DECODE_CALL decod_getStringFlashImageType(const u8 u8ImageType);
DECODE_API u32 DECODE_CALL decod_getFlashImageType(const char * pstrImageType, u8 * pu8ImageType);

/* --- utility routines ----------------------------------------------------- */

/***************************************************************************
* Function Name: decod_stringCompareNoCase
* Description: compare two strings ignoring case 
* Parameters:    
*       [in] pstr1, the first string
*       [in] pstr2, the second string
* Return: 0: equal; 1: pstr1 > pstr2; -1: pstr1 < pstr2
* Remarks: None.  
****************************************************************************/
DECODE_API int DECODE_CALL decod_stringCompareNoCase(const char * pstr1, const char * pstr2);

DECODE_API u32 DECODE_CALL decod_getBinaryFromString(u8 * u8Binary, u16 * u16BinaryLen, u8 * u8String,
    u16 u16StringLen);

/* Import & Export */
/***************************************************************************
* Function Name: decod_getStringImportError
* Description: get the import error string
* Parameters:
*       [in] u8ImportError
* Return: the import error string
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringImportError(const u8 u8ImportError);
/***************************************************************************
* Function Name: decod_getStringImportType
* Description: get the import type string
* Parameters:
*       [in] u8ImportType
* Return: the import type string
* Remarks: none.
****************************************************************************/
DECODE_API const char * DECODE_CALL decod_getStringImportType(const u8 u8ImportType);
DECODE_API const char * DECODE_CALL decod_getStringScheduleType(u8 u8Type);
DECODE_API u32 DECODE_CALL decod_getStringScheduleTime(char * pstrTime, const time_t tTime);
DECODE_API u32 DECODE_CALL decod_getStringSASAddress(u8 * strField, u64 u64Address);
DECODE_API u32 DECODE_CALL decod_getStringFCPortWWN(u8 * strField, u64 u64WWNN);
DECODE_API u32 DECODE_CALL decode_getStringFCPortState(u8 * strField, u8 u8PortState);
DECODE_API u32 DECODE_CALL decode_getStringFCTopologyAttached(u8 * strField, u32 flag);
DECODE_API u32 DECODE_CALL decode_getStringFCCurrentSpeed(u8 * strField, u32 speed);
DECODE_API u32 DECODE_CALL decode_getStringFCLinkType(u8 * strField, u32 LinkType);
DECODE_API u32 DECODE_CALL decode_getStringFCLinkConfigSpeed(u8 * strField, u8 speed);
DECODE_API u32 DECODE_CALL decode_getStringFCTopologyConfiged(u8 * strField, u8 flag);
DECODE_API u32 DECODE_CALL decode_getStringFCWareVersion(u8 * strField, u32 HardwareVersion);
DECODE_API u32 DECODE_CALL decode_getStringFCTSupportedFeature(u8 * tmpstr, u32 Flags, u32 SupportedServiceClass);
DECODE_API u32 DECODE_CALL decode_getStringFCTransceiver(u8 * strField, u8 id);
DECODE_API u32 DECODE_CALL decode_getStringFCConnector(u8 * strField, u8 Connector);
DECODE_API u32 DECODE_CALL decod_getStringFCTransceiverCode(u8 * strField, u8 * Transceiver);
DECODE_API u32 DECODE_CALL decod_getStringFCSerialEncoding(u8 * strField, u8 Encoding);
DECODE_API u32 DECODE_CALL decod_getStringFCVendorOUI(u8 * strField, u8 * VendorOUI);
DECODE_API u32 DECODE_CALL decod_getStringFCVendorRevision(u8 * strField, u8 * VendorRevision);
DECODE_API u32 DECODE_CALL decod_getStringFCu64(u8 * strField, u64 u64Integer);
DECODE_API u32 DECODE_CALL decod_getStringFCLoggedInDevicePortId(u8 * strField, u32 portId);
DECODE_API u32 DECODE_CALL decod_getFrontendType(u8 * pu8Product, u8 * pu8Data, u32 u32DataLength);
DECODE_API u32 DECODE_CALL decod_getStringFCSupportedSpeed(u8 * strField, u8 SupportedSpeeds);

DECODE_API u32 DECODE_CALL decode_getStringFCTSupportedCOS(u8 * tmpstr, u16 * u16COS);
DECODE_API u32 DECODE_CALL decode_getStringFCSupportedTypes(u8 * tmpstr, u16 * u16Types);
DECODE_API u32 DECODE_CALL decode_getStringFCPortType(u8 * strField, u32 flag, u16 PortType);

DECODE_API u32 DECODE_CALL decode_getStringSCSIPortMaxRate(u8 * strField, u8 rate);
DECODE_API u32 DECODE_CALL decode_getStringSCSITermStatus(u8 * strField, u8 termsta);
DECODE_API u32 DECODE_CALL decode_getStringSCSITargetStatus(u8 * strField, u8 status, u8 targetid);
DECODE_API u32 DECODE_CALL decode_getStringSCSIPortSetTermCtl(u8 * strField, u8 turn);	
DECODE_API u32 DECODE_CALL decode_getStringSCSITargetRunningMode(u8 * strField, u16 mode);		
DECODE_API u32 DECODE_CALL decode_getStringSCSITargetBusWidth(u8 * strField, u8 width);	

DECODE_API u32 DECODE_CALL decod_retrieveDSTDate(u8 * pu8DSTDateString, u8 * pu8Month, u8 * pu8WeekOfMonth, u8 * pu8DayOfWeek);
DECODE_API const char * DECODE_CALL decod_getStringWeekNo(const u8 u8WeekNo);
DECODE_API const char * DECODE_CALL decod_getStringWeekDay(const u8 u8WeekDay);
DECODE_API const char * DECODE_CALL decod_getStringMonth(const u8 u8Month);
DECODE_API const char * DECODE_CALL decod_getStringNTPMonth(const u8 u8Month);
DECODE_API const char * DECODE_CALL decod_getStringNTPWeek(const u8 u8Week);
DECODE_API const char * DECODE_CALL decod_getStringNTPDay(const u8 u8Day);
DECODE_API void DECODE_CALL decod_getStringNTPSyncResult(u8 * strField, const boolean_t bSyncResult,
    u32 u32NumOfTimeServerSuccessful, u8 u8TimeServerSuccessful[][MAX_TIME_SERVER_NAME_LENGTH],
    u32 u32NumOfTimeServerFailed, u8 u8TimeServerFailed[][MAX_TIME_SERVER_NAME_LENGTH]);

DECODE_API boolean_t DECODE_CALL decod_isHostInterface(feature_bits_t * pfb, u32 u32HostInterfaceMask);	
DECODE_API boolean_t DECODE_CALL decod_isVlanSupported(u32 u32FeatureMask);	
DECODE_API boolean_t DECODE_CALL decod_isLinkAggrSupported(u32 u32FeatureMask);	
DECODE_API boolean_t DECODE_CALL decod_isSlpSupported(u32 u32FeatureMask);	
DECODE_API boolean_t DECODE_CALL decod_isMultiNodeSupported(u32 u32FeatureMask);	
DECODE_API boolean_t DECODE_CALL decod_isDriveInterface(feature_bits_t * pfb, u32 u32DriveInterfaceMask);	
DECODE_API boolean_t DECODE_CALL decod_isRAIDLevel(feature_bits_t * pfb, u32 u32RAIDLevelMask);

/***************************************************************************
* Function Name: decod_getEnclFRULocatable
* Description: return which FRU component is locatable
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [out] pValue, bit map. bit0:Controller, bit1:Enc, bit2:PSU, bit3:CU (1:support locate, 0: not support)

* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclFRULocatable(MEI_t *pmicInfo, u8 *pValue);

/***************************************************************************
* Function Name: decod_getEnclTemperatueStatus
* Description: get the temperature sensor status, present (1) or non-present(0)
****************************************************************************/
DECODE_API u8 DECODE_CALL decod_getEnclTemperatueStatus(MEI_t * pmicInfo, u8 sensorId, u8 * pu8Data);

/***************************************************************************
* Function Name: decod_getEnclosureOpStatus
* Description: return overall status
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [in] pu8Data, enclosure status
*       [in] pSetting, enclosure setting
*       [out] pStatus, enclosure overall status
*       [out] pDescription, overall description
*       [in] u8BufferLength, buffer length to store the description
*       [in] u8BatteryCount, number of battery present
*       [in] u8BatteryStatus, battery status for each present battery
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclosureOpStatus(MEI_t *pmicInfo, u8 * pu8Data,
        enclosure_setting_t * pSetting, u8 * pStatus, u8 * pDescription,
        u16 u16BufferLength, u8 u8BatteryCount, u8 u8BatteryStatus[]);
/***************************************************************************
* Function Name: decod_getEnclNumFan
* Description: return number of fan and number of blower
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [out] pNumOfFans, number of fan
*       [out] pNumOfBlowers, number of blower
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclNumFan(MEI_t *pmicInfo, u8 * pNumOfFans, u8 * pNumOfBlowers);
/***************************************************************************
* Function Name: decod_getEnclNumFanPerPSU
* Description: return number of fan per PSU
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [out] pNumOfFans, number of fan
*       [out] pSpeedThreshold, hardcoded speed threshold
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclNumFanPerPSU(MEI_t *pmicInfo, u8 * pNumOfFans, u32 * pSpeedThreshold);
/***************************************************************************
* Function Name: decod_getEnclNumBlowerPerCooling
* Description: return number of blower per cooling unit
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [out] pNumOfBlowers, number of blowers
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclNumBlowerPerCooling(MEI_t *pmicInfo, u8 * pNumOfBlowers);
/***************************************************************************
* Function Name: decod_getEnclFanId
* Description: return fan id after re-order from fw data
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [in] u8FanIndex, index from f/w
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u8 DECODE_CALL decod_getEnclFanId(MEI_t *pmicInfo, u8 u8FanIndex);
/***************************************************************************
* Function Name: decod_getEnclBlowerIndex
* Description: return cooing unit inex and blower index from fw index
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [in] i, index from f/w
*       [out] pu8IndexCU, the cooling unit index
*       [out] pu8IndexBlower, the blower index
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclBlowerIndex(MEI_t *pmicInfo, u8 i, u8 * pu8IndexCU, u8 * pu8IndexBlower);
/***************************************************************************
* Function Name: decod_getEnclBlowerId
* Description: return cooing unut id and blower id from fw data
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [in] u8BlowerIndex, blower index
*       [out] pu8BlowerId, the blower id
*       [out] pu32SpeedThreshold, the blower speed threshold
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclBlowerId(MEI_t *pmicInfo, u8 u8BlowerIndex, u8 * pu8BlowerId,  u32 *pu32SpeedThreshold);
DECODE_API u32 DECODE_CALL decod_getEnclTempSensorLocation(MEI_t *pmicInfo, u8 * strField, u8 u8Id, u8 *pu8TempThreshold);
DECODE_API u32 DECODE_CALL decod_getEnclTempSensorLocationValue(MEI_t *pmicInfo, u8 *pValue, u8 u8Id);
DECODE_API u32 DECODE_CALL decod_getEnclNumTempSensor(MEI_t *pmicInfo, u8 * pu8NumSensor);
/***************************************************************************
* Function Name: decod_getEnclSetting
* Description: return enclosure setting from mic data
* Parameters:
*       [out] pSetting, the enclosure setting
*       [in] pEnclSetting, the enclosure setting from mic data
*       [in] pmicInfo, the enclosure info from mic data
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclSetting(enclosure_setting_t * pSetting, MESH_t * pEnclSetting, MEI_t * pmicInfo);
DECODE_API u32 DECODE_CALL decod_setEnclSetting(enclosure_setting_t * pSetting, MESH_t * pEnclSetting, MEI_t *pmicInfo);
/***************************************************************************
* Function Name: decod_getEnclTemperatureSettingRange
* Description: return temperature setting range
* Parameters:
*       [in] pmicInfo, the data buffer that contains enclosure info returned by I2API
*       [out] pSetting, enclosure temperature setting range
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getEnclTemperatureSettingRange(MEI_t *pmicInfo, encltemperature_setting_range_t * pSetting);

/***************************************************************************
* Function Name: decod_getSASTopologyConnections
* Description: return all connections information
* Parameters:
*       [in] pData, the data buffer that contains the topology returned by I2API
*       [out] pConnections, array of connections data
*       [out] pNumConnections, number of connections
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getSASTopologyConnections(sas_topology_connection_t *pConnections, MicSasMgtStruct_t * pData,
    u16 * pNumConnections);
DECODE_API char * DECODE_CALL decod_getSASTopologyConnectionStatus(u8 status);
/***************************************************************************
* Function Name: decod_getSASTopologyEnclInfo
* Description: return enclosure info from the topology data
* Parameters:
*       [in] pData, the data buffer that contains the topology returned by I2API
*       [in] u8EnclId, the enclosure to get info
*       [out] pInfo, enclosure info to return
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getSASTopologyEnclInfo(u8 u8EnclId, MicSasMgtStruct_t * pData,
    sas_topology_enclosure_info_t * pInfo);
/***************************************************************************
* Function Name: decod_getSASTopologyConnectionInfo
* Description: return connection info for one port
* Parameters:
*       [in] u8EnclId, the enclosure id to get connected devices, starts from 1
*       [in] ExpanderId, the expander id to get connected devices, starts from 1
*       [in] portId, the port id to get connected devices, starts from 1
*       [out] pConnections, the connected device info, could be more than on device
*       [out] pNumConnectDevice, number of connected device
*       [in] pData, the data buffer that contains the topology returned by I2API
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: None.
****************************************************************************/
DECODE_API u32 DECODE_CALL decod_getSASTopologyConnectionInfo(u8 EnclId, u8 ExpanderId, u8 PortId,
    sas_topology_connection_t *pConnections, u8 * pNumConnectDevice, MicSasMgtStruct_t * pData);
DECODE_API const char * DECODE_CALL decod_getStringRedundancyStatus(const u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringRedundancyType(const u8 u8Status);
DECODE_API void DECODE_CALL decod_getStringCacheMirroring(char * pstrCache, const u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringControllerRole(const u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringReadinessStatus(const u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getStringLunmappingMethod(const u8 u8Status);
DECODE_API const char * DECODE_CALL decod_getSASDiagAttachedType(u8 AttachedDevType);
DECODE_API const char * DECODE_CALL decod_getSASDiagPhyLinkRate(u8 PhyRateNegotiated);
DECODE_API const char * DECODE_CALL decod_getSASDiagInitiator(u8 AttachedInitiatorInfo);
DECODE_API const char * DECODE_CALL decod_getSASDiagAttachedTgt(u8 AttachedTgtInfo);
DECODE_API const char * DECODE_CALL decod_getSASDiagRouting(u8 RoutingAttribute);

DECODE_API u32 DECODE_CALL decode_getStringSASPortLinkStatus(u8 * strField, u8 u8LinkStatus);
DECODE_API u32 DECODE_CALL decode_getStringSASPortType(u8 * strField, u8 u8Type);
DECODE_API u32 DECODE_CALL decode_getStringSASPortLinkSpeed(u8 * strField, u8 u8LinkSpeed);

DECODE_API u32 DECODE_CALL decod_getStringPdVisibleToController(u8 * strCtrl, u8 u8CtrlId);

DECODE_API u32 DECODE_CALL decod_locateNextSchedule(bga_schedules_t * pBuf, u32 u32Size, u32 u32Index, bga_schedule_t ** ppbs);

DECODE_API u32 DECODE_CALL decod_getStringPowerOnTime(u8 * strTime, micControllerInfoPage0_t * pPage0);

DECODE_API u32 DECODE_CALL decod_getStringSecondTime(u8 * strTime, u32 u32SecondValue);
DECODE_API u32 DECODE_CALL decod_getNumberBatteryHoldTime(u32 * u32HoldTime, MBI_t * pmicInfo,
    micControllerInfoPage0_t * pPage0, micControllerInfoPage2_t * pPage2);

DECODE_API boolean_t DECODE_CALL decod_bNonRecoverableLD(micLogicalDriveDef_t * pmicLogDrv);
DECODE_API void DECODE_CALL decod_getMigrationEligibility(const micArrayConfigurationDef_t *cfg, const u32 length,
    u32 * u32ErrorStatus, u32 * u32ErrorStatusCount, feature_bits_t * fb);
DECODE_API boolean_t DECODE_CALL decod_bPDDeadOrMissing(u32 u32Flag);
DECODE_API u8 DECODE_CALL decod_getNumberParityDrive(const u8 raidLevel, const u8 numParityDrives);
DECODE_API u8 DECODE_CALL decod_getTolerableNumDeadDrivesPerAxle(const u8 raidLevel);

DECODE_API u32 DECODE_CALL decod_getBufferCountEnclInfo(const u8 * pu8Buffer, const u32 u32Length, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_locateBufferEnclInfo(const u8 * pu8Buffer,
    const u32 u32Length, const u16 u16DevId, u8 ** ppInfo);
DECODE_API const char * DECODE_CALL decod_getStringLCDMode(const u8 u8Mode);

DECODE_API u32 decod_appendEventPercentString(char *strDest, u32 *u32Length, Event_t * pEvent);
DECODE_API const char * DECODE_CALL decod_getStringUPSType(const u8 u8State);
DECODE_API const char * DECODE_CALL decod_getStringDetection(const u8 u8State);
DECODE_API u32 DECODE_CALL decod_setCmdlineDetectionMode(const u8 *pu8Value, u8 *pu8State);
DECODE_API u32 DECODE_CALL decod_getStringUPSFactoryDate(u8 *strDate, micUpsStatusData_t *pmicUPSStatus);
DECODE_API u32 DECODE_CALL decod_getStringUPSAutoReconditionSettings(char *pstrSetting,const u8 u8Recondition);
DECODE_API u32 DECODE_CALL decod_locateBufferUPSStatus(const char *pData, u32 u32DataLength, u32 u32Index, u8 **ppUPSStatus);
DECODE_API u32 DECODE_CALL decod_locateBufferUPSSetting(const char *pData, u32 u32DataLength, u32 u32Index, u8 **ppUPSSetting);
DECODE_API u32 DECODE_CALL decod_getBufferCountUPSStatus(const char *pData, u32 u32DataLength, u32 *pu32Count);
DECODE_API u32 DECODE_CALL decod_getStringUPSOpStatus(char * pstrOpStatus, micUpsStatusData_t *pmicUPSStatus, req_data_ups_manager_config_t rdumc);
DECODE_API const char * DECODE_CALL decod_getStringAction(const u8 u8State);
DECODE_API u32 DECODE_CALL decod_setActionMode(const u8 *pu8Value, u8 *pu8State);
DECODE_API u32 DECODE_CALL decod_getLinkAggrSlavePorts(u8 *pu8count, u16 *pu16port, micLinkAggrInfoSettingsData_t micLinkAggrInfoData);
DECODE_API boolean_t DECODE_CALL decod_isSEPVersionSupported(MEI_t * pmicInfo);
DECODE_API boolean_t DECODE_CALL decod_isSEPFromFlash(MEI_t * pmicInfo);
DECODE_API u32 DECODE_CALL decod_getStringSpindownType(u8 * strField, u8 u8SpindownType);
DECODE_API boolean_t DECODE_CALL decod_isNASLD(const u32 u32OptionFlag);
DECODE_API boolean_t DECODE_CALL decod_isNASInitiator(const u8 *pName);
DECODE_API u32 DECODE_CALL decod_getStringPowerSavingTime(u8 * strField, const u16 u16Time);
DECODE_API const char * DECODE_CALL decod_getStringPSUType(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringNarrowPortType(const u8 u8Type);

/*---bgasched info and settings---------------------------------------------*/
DECODE_API const char * DECODE_CALL decod_getStringBgaSchType(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringBgaSchRec(const u8 u8Type);
DECODE_API const char * DECODE_CALL decod_getStringBgaSchLd(u8 * pDest, rc_schedule_t * rcst);
DECODE_API u32 DECODE_CALL decod_getBufferCountBgaSch(const char *pData, u32 u32DataSize, u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_getStringBgaSchSt(u8 * pDest, u16 * u16StartTime);
DECODE_API u32 DECODE_CALL decod_getStringBgaSchMonth(u8 * pDest, u16 * u16Month);
DECODE_API u32 DECODE_CALL decod_getStringBgaSchDay(u8 * pDest, u8 * u8Day);
DECODE_API u32 DECODE_CALL decod_CmdLineBgaSchDow(const char * pu8IdList, u8 * pu8Str[], u32 * pu32Count);
DECODE_API u32 DECODE_CALL decod_CmdLineBgaSchLdId(const u8 * pu8IdList, u16 * pu32Ids, u32 * pu32IdCount);
DECODE_API u32 DECODE_CALL decod_retrieveBgaSchTime(char * pTimeString, u32 * u32Hour, u32 * u32Min);
DECODE_API u32 DECODE_CALL decod_retrieveBgaSchDate(char * pDateString, u16 * pYear, u8 * pMon, u8 * pDay);
DECODE_API u32 DECODE_CALL decod_getBgaSchRec(const char *pstrRec, u8 * u8Recurrency);
DECODE_API u32 DECODE_CALL decod_getBgaSchWeekDow( const char * u8Value, u8 * u8DayMask);
DECODE_API u32 DECODE_CALL decod_getBgaSchDowMonth( const char * u8Value, u16 * u16MonthMask);
DECODE_API u32 DECODE_CALL decod_getBgaSchDayPattern(const char *pstrRec, u8 * u8DayPattern);
DECODE_API u32 DECODE_CALL decod_getBgaSchMonthDay(const char *u8MonthDay, u8 * rValue);
DECODE_API u32 DECODE_CALL decod_getBgaSchMonthWeek(const char *u8MonthWeek, u8 * rValue);
DECODE_API u32 DECODE_CALL decod_CmdLineBgaSchLdIdUnique(u16 * pu16Ids, u32 u32Index);

#endif /*__PI_DATADECODER_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: dtdecode.h,v $
 * Revision 1.180.2.15  2009/12/18 06:25:51  xinw
 * add decod_getStringNarrowPortType
 *
 * Revision 1.180.2.14  2009/11/20 09:22:10  xinw
 * add ntp support
 *
 * Revision 1.180.2.13  2009/11/19 10:04:42  lilyz
 * for bug24110: psutype support
 *
 * Revision 1.180.2.12  2009/11/04 08:32:44  xinw
 * modify maid support
 *
 * Revision 1.180.2.11  2009/10/16 09:12:47  xinw
 * add performace monitor support
 *
 * Revision 1.180.2.10  2009/10/15 03:01:36  xinw
 * add nas support
 *
 * Revision 1.180.2.9  2009/09/29 03:05:55  xinw
 * merge Import/Export consistent to E-class
 *
 * Revision 1.180.2.8  2009/09/17 06:23:18  xinw
 * remove sepversion for 1u4bay
 *
 * Revision 1.180.2.7  2009/07/22 05:45:23  xinw
 * add new macro define for product ctrl mode
 *
 * Revision 1.180.2.6  2009/07/13 06:22:39  xinw
 * add nop-in support
 *
 * Revision 1.180.2.5  2009/05/19 09:12:17  xinw
 * add decod_getStringSpindownType
 *
 * Revision 1.180.2.4  2009/05/04 09:10:13  xinw
 * use decod_isSEPVersionSupported check get sep version
 *
 * Revision 1.180.2.3  2009/04/21 06:00:10  xinw
 * add get ups action mode, get linkaggr port info
 *
 * Revision 1.180.2.2  2009/03/30 07:01:53  xinw
 * modify decod_getStringUPSOpStatus
 *
 * Revision 1.180.2.1  2009/03/23 11:48:14  xinw
 * add ups support
 *
 * Revision 1.180  2008/08/21 07:01:28  kenh
 * Add new function decod_appendEventPercentString() for event list
 *
 * Revision 1.179  2008/08/01 06:24:36  michaell
 * Add decod_getStringVoltageStatus, decod_getVoltageStatus
 *
 * Revision 1.178  2008/06/17 07:13:20  kenh
 * Add define for new function decod_setPDConfigFlags()
 *
 * Revision 1.177  2008/04/03 11:01:15  danielz
 * support LCD management
 *
 * Revision 1.176  2007/12/12 06:19:41  danielz
 * remove the function declaration for decod_isDiskArrayMPRunning()
 *
 * Revision 1.175  2007/11/27 06:09:37  theoz
 * add function decod_getStringSize1000Based() to get the size string based 1000
 *
 * Revision 1.174  2007/11/02 03:42:52  jackyl
 * no message
 *
 * Revision 1.173  2007/10/23 10:29:46  danielz
 * support ALUA
 *
 * Revision 1.172  2007/09/21 06:33:42  danielz
 * 2 decode function to get count of enclosure info and locate enclosure info
 *
 * Revision 1.171  2007/08/22 10:29:23  danielz
 * decod_getStringFlashImageType() and decod_getFlashImageType() is now used in
 * in-band also
 *
 * Revision 1.170  2007/08/17 03:12:16  danielz
 * add DECODE_API and DECODE_CALL for function decod_getPartitionMaxConfigurableSize()
 *
 * Revision 1.169  2007/08/15 05:22:32  danielz
 * new decode function decod_getPartitionMaxConfigurableSize()
 *
 * Revision 1.168  2007/06/29 09:08:59  daobang.wang
 * Add a decode funtion to get correct number of parity drive according to raid level of logical drive.
 *
 * Revision 1.167  2007/06/28 00:29:06  debinc
 * RAID6 migration support
 *
 * Revision 1.166  2007/06/07 09:56:53  JudithLi
 * i2api v3&v4 consolidation
 *
 * Revision 1.165  2007/05/09 17:39:45  danielz
 * revert back the change to sep fw version
 *
 * Revision 1.164  2007/05/08 21:58:08  debinc
 * migration eligibility
 *
 * Revision 1.163  2007/05/07 23:38:56  debinc
 * migration eligibility
 *
 * Revision 1.162  2007/05/03 21:30:28  debinc
 * nonRecoverableLD
 *
 * Revision 1.161  2007/04/22 07:23:42  xinw
 * modify fw version compare parameter
 *
 * Revision 1.160  2007/04/20 10:21:49  xinw
 * add decode for fw version compare
 *
 * Revision 1.159  2007/04/20 04:47:20  danielz
 * new decode function for cache mirroring
 *
 * Revision 1.158  2007/04/16 22:59:40  danielz
 * new function decod_getStringSepFwVersion()
 *
 * Revision 1.157  2007/02/09 03:00:29  danielz
 * current write policy of LD
 *
 * Revision 1.156  2007/02/02 10:05:38  xinw
 * add decode for multi node support
 *
 * Revision 1.155  2007/02/01 03:59:11  xinw
 * add new Mx10i support
 *
 * Revision 1.154  2007/01/27 01:24:54  debinc
 * support battery new feature
 *
 * Revision 1.153  2007/01/11 10:38:47  danielz
 * new decode functions to get local time
 *
 * Revision 1.152  2007/01/09 09:02:06  danielz
 * new decode function decod_getStringEventInfo
 *
 * Revision 1.151  2007/01/02 23:13:48  debinc
 * slot wwn mapping support
 *
 * Revision 1.150  2006/12/05 07:49:14  danielz
 * 1. New OpStatus, OPSTATUS_MAINTENANCE, OPSTATUS_DEVICE_NOT_ACCESSIBLE and
 *    OPSTATUS_SHUTDOWN
 * 2. New decode function decod_getStringCtrlOverallRaidStatus() to get the RAID
 *    status (reflect ci_RaidState and etc in controller page 0)
 *
 * Revision 1.149  2006/11/28 08:12:00  danielz
 * decod_getStatusFlashImageType() is used for in-band now
 *
 * Revision 1.148  2006/10/31 02:19:46  danielz
 * 2 new functions for battery cell type and battery hold time
 *
 * Revision 1.147  2006/10/17 07:28:32  shirleyw
 * add new function decod_getStringSecondTime()
 *
 * Revision 1.146  2006/10/13 08:39:05  michaell
 * Add decod_getEnclTempSensorLocationValue() to head file
 *
 * Revision 1.145  2006/09/22 11:21:33  danielz
 * Add a function decod_getStringBatterySerialNum()
 *
 * Revision 1.144  2006/09/14 08:35:40  danielz
 * Add a new function decod_getStringSASAddress()
 *
 * Revision 1.143  2006/09/12 08:26:37  danielz
 * Add a new function decod_isPhyDrvAccessible()
 *
 * Revision 1.142  2006/09/07 08:50:36  danielz
 * Add a new function decod_getStringPowerOnTime()
 *
 * Revision 1.141  2006/08/30 09:46:56  leync
 * wrap bgaschd_locateNextSchedule to decode library to
 * avoild inband windows build issue.
 *
 * Revision 1.140  2006/08/28 06:18:05  danielz
 * Add a new function decod_getStringPdVisibleToController()
 *
 * Revision 1.139  2006/07/21 18:55:54  debinc
 * sas pd drive interface
 *
 * Revision 1.138  2006/07/13 01:20:14  debinc
 * use new decodeVoltageSensorType function.
 *
 * Revision 1.137  2006/06/29 21:46:51  debinc
 * obsolete enclosureOverallStatus
 *
 * Revision 1.136  2006/06/14 01:20:01  debinc
 * SAS frontend support
 *
 * Revision 1.135  2006/05/31 19:20:55  debinc
 * factory defaults encl
 *
 * Revision 1.134  2006/05/15 23:56:27  debinc
 * update enclosure overall status
 *
 * Revision 1.133  2006/05/11 23:49:48  debinc
 * sas diag
 *
 * Revision 1.132  2006/05/02 04:01:26  leync
 * fix bug 8605,8672,8929
 *
 * Revision 1.131  2006/04/26 07:23:39  danielz
 * Add a new routine decod_getPDSpeed() to get the speed of PD.
 *
 * Revision 1.130  2006/04/17 23:04:43  weny
 * let getStringEventTimeStamp return error
 *
 * Revision 1.129  2006/04/05 00:35:47  debinc
 * dual ctrl info
 *
 * Revision 1.128  2006/03/24 19:59:51  debinc
 * support dual controller subsys info/setting
 *
 * Revision 1.127  2006/02/24 01:03:01  debinc
 * correct indentation
 *
 * Revision 1.126  2006/02/22 23:53:36  debinc
 * decode enclosure temperature setting range
 *
 * Revision 1.125  2006/02/22 19:55:56  debinc
 * rename decod_enclosureOverallStatus2()
 *
 * Revision 1.124  2006/02/22 19:28:07  debinc
 * remove original decod_enclosureOverallStatus()
 *
 * Revision 1.123  2006/02/22 01:28:31  debinc
 * get/set enclosure setting
 *
 * Revision 1.122  2006/02/15 00:10:40  debinc
 * get correct controller temperature threshold
 *
 * Revision 1.121  2006/02/07 22:12:27  debinc
 * correct function prototype
 *
 * Revision 1.120  2006/02/04 00:57:25  debinc
 * encl temerature sensor status
 *
 * Revision 1.119  2006/02/03 19:29:44  debinc
 * add decode funtion
 *
 * Revision 1.118  2006/01/30 22:59:40  debinc
 * enclosure overall status
 *
 * Revision 1.117  2006/01/14 00:40:54  debinc
 * improve enclosure decode lib
 *
 * Revision 1.116  2006/01/04 21:36:52  weny
 * replace MAX values with those from feature bits and capabilities
 *
 * Revision 1.115  2005/12/18 23:21:55  debinc
 * SAS topology verbose support
 *
 * Revision 1.114  2005/12/14 00:36:28  debinc
 * SAS topology support
 *
 * Revision 1.113  2005/12/10 00:27:37  debinc
 * multi-enclosure info/status support
 *
 * Revision 1.112  2005/11/25 10:03:33  JudithLi
 * 8136,8137
 * CLU expand migration will report Not enough capacity on some configuration
 * & choosing Expand Capacity failed report
 *
 * Revision 1.111  2005/11/23 19:28:22  debinc
 * *** empty log message ***
 *
 * Revision 1.110  2005/11/23 02:16:05  debinc
 * SAS drive CLI check featue bit for SAS
 *
 * Revision 1.109  2005/11/23 01:46:37  debinc
 * SAS drive CLI
 *
 * Revision 1.108  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.107  2005/08/02 00:04:37  debinc
 * version number change from u8 to u32
 *
 * Revision 1.106  2005/07/01 08:35:40  fieldsy
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2005/06/30 08:35:40  binx
 *
 * Version 2005/06/29 
 * merge binx/xinc/leync codes at the base of aslavista_sw_0615
 *
 *
 * Revision 1.1.1.1  2005/06/20 07:02:02  challoc
 * ptt_asg-sw-20050620
 *
 * Revision 1.105  2005/05/20 23:09:31  debinc
 * FC MIC change
 *
 * Revision 1.104  2005/05/16 22:34:46  weny
 * change promise specific op status start from 0x8000, where CIM vendor reserve op status begins
 *
 * Revision 1.103  2005/05/03 18:20:57  debinc
 * fix display hardALPA problem
 *
 * Revision 1.102  2005/04/20 23:31:15  debinc
 * new decode function
 *
 * Revision 1.101  2005/04/05 01:56:17  weny
 * add DECODE_CALL for all FC related functions
 *
 * Revision 1.100  2005/03/31 18:38:10  weny
 * add decod_getStringBatteryChemistryType
 *
 * Revision 1.99  2005/03/25 00:48:32  weny
 * add some voltage decode functions
 *
 * Revision 1.98  2005/03/24 18:21:14  weny
 * use const char* in decod_retrieveIPAddress
 *
 * Revision 1.97  2005/03/10 23:19:03  debinc
 * frontend type for differen product
 *
 * Revision 1.96  2005/02/26 01:46:31  debinc
 * more function
 *
 * Revision 1.95  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.94  2005/02/10 02:49:53  weny
 * fix 5740 about getStringPhyDrvInterface
 *
 * Revision 1.93  2004/12/04 00:17:30  debinc
 * add decode event specific data function
 *
 * Revision 1.92  2004/11/30 07:32:08  weny
 * 1. Fix bug 5064 - expose migration storage for ctrl settings
 * 2. add drive speed decod func
 *
 * Revision 1.91  2004/11/13 04:54:16  weny
 * add decode function for flash image type
 *
 * Revision 1.90  2004/11/09 22:45:31  debinc
 * check user name
 *
 * Revision 1.89  2004/10/19 04:34:16  weny
 * Online Array Removal support
 *
 * Revision 1.88  2004/10/08 22:57:39  weny
 * 1. add support to enclosure type, maxCtrl and maxSEP
 * 2. add support to TCQ/NCQ support
 *
 * Revision 1.87  2004/09/30 03:54:08  weny
 * added migration storage decode routine
 *
 * Revision 1.86  2004/09/30 03:19:20  ken.cai
 * (lak) added decod_getStringDiskArrayIncompleteArrayStatus()
 *
 * Revision 1.85  2004/09/23 04:02:52  weny
 * R5 algorithm support
 *
 * Revision 1.84  2004/09/14 04:43:49  weny
 * add LD Opstatus for Redundancy Check
 *
 * Revision 1.83  2004/09/10 00:38:02  weny
 * added decod_getStringStatsNumber to display more user friendly stats numbers
 *
 * Revision 1.82  2004/09/08 22:40:34  debinc
 * decode SMTP auth method
 *
 * Revision 1.81  2004/08/31 06:41:19  weny
 * added more op status for nvram watermark
 *
 * Revision 1.80  2004/08/18 23:27:16  weny
 * added some decode routines
 *
 * Revision 1.79  2004/07/29 02:12:38  weny
 * enhance error handling of time related routines
 *
 * Revision 1.78  2004/07/22 23:09:40  weny
 * sync with mic iscsi extended node page
 *
 * Revision 1.77  2004/07/22 04:03:00  weny
 * stale drive handling
 *
 * Revision 1.76  2004/07/20 04:22:02  weny
 * add decode routines for controller settings
 *
 * Revision 1.75  2004/07/06 23:11:28  weny
 * remove BGA_STATE_INACTIVE, use BGA_STATE_NONE (in mic.h) instead
 *
 * Revision 1.74  2004/06/29 02:02:39  weny
 * change SectorSize to SectorSizeCode
 *
 * Revision 1.73  2004/06/28 20:31:49  weny
 * Added LD Variable Sector Size Support
 *
 * Revision 1.72  2004/05/13 18:09:08  zhengj
 * added support for spare check and locate enclosure
 *
 * Revision 1.71  2004/05/04 18:25:03  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.70  2004/04/15 00:32:38  zhengj
 * added api for alias
 *
 * Revision 1.69  2004/04/13 00:19:47  zhengj
 * added decod_getStringDMAMode
 *
 * Revision 1.68  2004/04/07 02:24:15  zhengj
 * added LOGDRV_OPERATION_SYNCHRONIZING
 *
 * Revision 1.67  2004/04/02 20:48:10  zhengj
 * added validateIPAddress
 *
 * Revision 1.66  2004/03/26 00:29:07  zhengj
 * added PDM enable
 *
 * Revision 1.65  2004/03/25 17:44:14  zhengj
 * bug fix
 *
 * Revision 1.64  2004/03/23 03:54:53  zhengj
 * added support for PDM
 *
 * Revision 1.63  2004/03/17 23:07:43  zhengj
 * added iscsi stats decode
 *
 * Revision 1.62  2004/03/05 22:20:12  zhengj
 * added support for system time and stats
 *
 * Revision 1.61  2004/02/26 18:58:55  zhengj
 * added string not supported
 *
 * Revision 1.60  2004/02/10 23:35:17  zhengj
 * flash support modification
 *
 * Revision 1.59  2004/02/06 03:33:47  debinc
 * use new evtstr functions
 *
 * Revision 1.58  2004/01/30 03:55:38  zhengj
 * lmm support
 *
 * Revision 1.57  2004/01/30 03:34:00  weny
 * add ctrl debug level decode functions
 *
 * Revision 1.56  2004/01/20 20:35:21  debinc
 * Add decode subsystem alias function
 *
 * Revision 1.55  2004/01/16 00:00:46  zhengj
 * added transitionPD and its status
 *
 * Revision 1.54  2004/01/09 23:01:48  wenyis
 * add node list functions
 *
 * Revision 1.53  2004/01/08 19:04:07  zhengj
 * iSNS support
 *
 * Revision 1.52  2004/01/07 21:36:39  wenyis
 * add decod_breakFragments()
 *
 * Revision 1.51  2003/12/18 03:35:21  zhengj
 * migration support
 *
 * Revision 1.50  2003/12/18 01:31:33  debinc
 * decode import/export error string
 *
 * Revision 1.49  2003/11/25 03:27:53  zhengj
 * added OEM code in fw revision
 *
 * Revision 1.48  2003/11/07 00:00:34  zhengj
 * added iscsi tcpip support
 *
 * Revision 1.47  2003/11/05 20:57:08  debinc
 * Add swmgt to CLI, I2, I2client
 *
 * Revision 1.46  2003/11/04 23:38:40  zhengj
 * some changes for device numbering and more
 *
 * Revision 1.45  2003/10/22 22:43:09  zhengj
 * seperate uni and bi CHAP
 *
 * Revision 1.44  2003/10/22 03:40:21  zhengj
 * added more check for addld
 *
 * Revision 1.43  2003/10/17 01:13:36  zhengj
 * added decode for ctrl temp threshold
 *
 * Revision 1.42  2003/09/26 23:15:10  zhengj
 * added decode for sessionISID
 *
 * Revision 1.41  2003/09/26 21:24:53  weny
 * Event Device Id String
 *
 * Revision 1.40  2003/09/25 00:14:10  zhengj
 * flash support
 *
 * Revision 1.39  2003/09/23 01:33:32  zhengj
 * added network settings
 *
 * Revision 1.38  2003/09/19 20:56:37  zhengj
 * added fru signature checking
 *
 * Revision 1.37  2003/09/19 01:42:48  weny
 * add clear event log
 *
 * Revision 1.36  2003/09/19 00:05:48  weny
 * add some support to bga cmd and phydrv online/offline
 *
 * Revision 1.35  2003/09/18 19:12:32  zhengj
 * subsys ctrl PD settings
 *
 * Revision 1.34  2003/09/13 00:34:37  weny
 * config lock support
 *
 * Revision 1.33  2003/09/11 03:48:23  zhengj
 * added slp
 *
 * Revision 1.32  2003/09/10 22:18:08  zhengj
 * initial check-in for iscsi
 *
 * Revision 1.31  2003/08/27 01:13:50  zhengj
 * missing drive support and bug fix
 *
 * Revision 1.30  2003/08/22 01:25:12  zhengj
 * added support for enclosure mgmt and others
 *
 * Revision 1.29  2003/08/21 02:51:01  debinc
 * Add user management support
 *
 * Revision 1.28  2003/08/15 21:42:20  zhengj
 * modify the opStatus implementation
 *
 * Revision 1.27  2003/08/12 01:35:54  weny
 * changes for In-band on Windows
 *
 * Revision 1.26  2003/08/11 23:42:37  zhengj
 * added partial support for uploading
 *
 * Revision 1.25  2003/08/08 22:41:41  zhengj
 * added support for array setting and info and others ..
 *
 * Revision 1.24  2003/07/29 22:31:18  zhengj
 * added decod_getStringLogDrvCachePolicy
 *
 * Revision 1.23  2003/07/22 00:09:11  zhengj
 * added decod_getStringLogDrvInitStatus
 *
 * Revision 1.22  2003/07/14 18:48:22  weny
 * hybrid raid config support - add more for axle support
 *
 * Revision 1.21  2003/07/01 19:58:18  zhengj
 * added api for MAC address string
 *
 * Revision 1.20  2003/06/30 20:07:59  zhengj
 * added api for string to binary conversion
 *
 * Revision 1.19  2003/06/28 03:26:56  weny
 * iscsi node info support
 *
 * Revision 1.18  2003/06/27 23:48:16  weny
 * add ld settings and rc support
 *
 * Revision 1.17  2003/06/26 21:03:54  weny
 * 1. WriteCache to WritePolicy
 * 2. add ReadPolicy decode routines
 * 3. add decod_getStringIPAddress
 * 4. add decod_stringCompareNoCase
 *
 * Revision 1.16  2003/06/05 02:00:29  weny
 * change the decode function prefix to decod_
 *
 * Revision 1.15  2003/06/04 02:27:57  weny
 * pool to disk array
 *
 * Revision 1.14  2003/06/03 20:57:20  weny
 * add more disk array cfg routines
 *
 * Revision 1.13  2003/04/15 17:49:17  weny
 * add more routines for event, ldi and lds
 *
 * Revision 1.12  2003/04/14 19:36:26  weny
 * 1. add support to event & rb
 * 2. add more for storpool
 *
 * Revision 1.11  2003/04/11 05:15:53  weny
 * add BGA_STATE_INACTIVE
 *
 * Revision 1.10  2003/04/10 03:35:11  weny
 * 1. add getDiskArrayPhysicalSize
 * 2. add getStringBGAState
 *
 * Revision 1.9  2003/04/09 19:49:57  weny
 * add stripe size check support
 *
 * Revision 1.8  2003/04/08 23:30:16  weny
 * add more decode routines for configurations
 *
 * Revision 1.7  2003/04/05 03:19:01  weny
 * add more decode func for log/phy/storpool/spare
 *
 * Revision 1.6  2003/04/04 03:39:24  weny
 * 1. add phy drv info decode routines
 * 2. add overall op status code definitions
 * 2. changed prototype of decod_getStringOpStatus()
 *
 * Revision 1.5  2003/04/03 05:40:36  weny
 * add "const" before the arguments that should be const
 *
 * Revision 1.4  2003/04/02 04:50:12  weny
 * 1. changed ctrl info decode func
 * 2. add phy drv and log drv info decode func
 *
 * Revision 1.3  2003/04/02 00:10:10  weny
 * add routines of get SATA fru info string
 *
 * Revision 1.2  2003/03/27 20:14:54  weny
 * add support to spare and storpool
 *
 * Revision 1.1  2003/03/22 00:54:00  weny
 * add data decode functions to i2client
 *
 ******************************************************************************/
