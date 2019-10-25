/*******************************************************************************
 * Filename    : errcode.h
 * Description : error code header file
 *               It provides the definitions of error codes and the related 
 *               external routines .
 * Created on  : 01/27/03
 * CVS Version : $Id: errcode.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_ERRCODE_H__
#define __PI_ERRCODE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"

/* --- constant definitions ------------------------------------------------ */

#define PIERR_NO_ERROR 0x0
#define PIERR_UNKNOWN_ERROR 0x1

#define PIERR_GENERIC_ERROR 0x100
#define PIERR_SECURITY_ERROR 0x200
#define PIERR_COMMAND_ERROR 0x400
#define PIERR_MODULE_ERROR 0x800
#define PIERR_I2API_ERROR 0x1000
#define PIERR_CLI_ERROR 0x2000
#define PIERR_DEVICE_ERROR 0x4000
#define PIERR_CONFIG_ERROR 0x8000
#define PIERR_BGA_ERROR 0x10000
#define PIERR_SERVICE_ERROR 0x12000
#define PIERR_EVENT_ERROR 0x20000
#define PIERR_SCHEDULE_ERROR 0x40000
#define PIERR_XMLPARSER_ERROR 0x80000
#define PIERR_CIM_ERROR 0x100000       

#define PIERR_PMIC_ERROR 0x40000000
#define PIERR_PENDING 0x80000000

/* generic errors */
#define PIERR_NOT_FOUND (PIERR_GENERIC_ERROR + 0)
#define PIERR_OUT_OF_MEMORY (PIERR_GENERIC_ERROR + 1)
#define PIERR_TIMEOUT (PIERR_GENERIC_ERROR + 2)
#define PIERR_FILE_NOT_FOUND (PIERR_GENERIC_ERROR + 3)
#define PIERR_NOT_SUPPORTED (PIERR_GENERIC_ERROR + 4)
#define PIERR_OPERATION_FAIL (PIERR_GENERIC_ERROR + 5)
#define PIERR_PROGRAM_ERROR (PIERR_GENERIC_ERROR + 6)
#define PIERR_BUFFER_TOO_SMALL (PIERR_GENERIC_ERROR + 7)
#define PIERR_RESOURCE_BUSY (PIERR_GENERIC_ERROR + 8)
#define PIERR_NOT_IMPLEMENTED (PIERR_GENERIC_ERROR + 9)
#define PIERR_OUT_OF_RANGE (PIERR_GENERIC_ERROR + 10)
#define PIERR_INVALID_VERSION (PIERR_GENERIC_ERROR + 11)
#define PIERR_PROCESS_FORK (PIERR_GENERIC_ERROR + 12)
#define PIERR_FW_NOT_FOUND (PIERR_GENERIC_ERROR + 13)
#define PIERR_FW_LOCKED (PIERR_GENERIC_ERROR + 14)
#define PIERR_NOT_LOCKED (PIERR_GENERIC_ERROR + 15)
#define PIERR_LOCK_EXPIRED (PIERR_GENERIC_ERROR + 16)
#define PIERR_ALREADY_RUNNING (PIERR_GENERIC_ERROR + 17)
#define PIERR_EMAIL_FAIL (PIERR_GENERIC_ERROR + 18)
#define PIERR_FILE_PATH_TOO_LONG (PIERR_GENERIC_ERROR + 19)
#define PIERR_INVALID_CDB_LENGTH (PIERR_GENERIC_ERROR + 20)
#define PIERR_FILE_ACCESS_VIOLOATION (PIERR_GENERIC_ERROR + 21)
#define PIERR_NULL_POINTER (PIERR_GENERIC_ERROR + 22)
#define PIERR_WRONG_PRODUCT_TYPE (PIERR_GENERIC_ERROR + 23)
#define PIERR_EMAIL_SUBJECT_TOO_LONG (PIERR_GENERIC_ERROR + 24)
#define PIERR_SYNC_NOT_COMPLETE (PIERR_GENERIC_ERROR + 25)
#define PIERR_SYNC_FAIL (PIERR_GENERIC_ERROR + 26)
#define PIERR_SYNC_CREATE_FAIL (PIERR_GENERIC_ERROR + 27)
#define PIERR_HALF_SYNC (PIERR_GENERIC_ERROR + 28)
#define PIERR_READ_FILE_ERROR (PIERR_GENERIC_ERROR + 29)
#define PIERR_WRITE_FILE_ERROR (PIERR_GENERIC_ERROR + 30)

#define PIERR_TFTP_GET_FAIL (PIERR_GENERIC_ERROR + 0x40)
#define PIERR_TFTP_PUT_FAIL (PIERR_GENERIC_ERROR + 0x41)
#define PIERR_DHCP_RENEW_FAIL (PIERR_GENERIC_ERROR + 0x42)
#define PIERR_UNRESOLVED_IPADDRESS (PIERR_GENERIC_ERROR + 0x43)

#define PIERR_INVALID_IP_ADDR_TYPE (PIERR_GENERIC_ERROR + 0x80)
#define PIERR_NULL_IP_ADDRESS (PIERR_GENERIC_ERROR + 0x81)

#define PIERR_NO_DEFAULT_SETTINGS       (PIERR_GENERIC_ERROR + 0x90)
#define PIERR_OEM_DEFAULT_NOT_AVAILABLE (PIERR_GENERIC_ERROR + 0x91)

/* security error */
#define PIERR_INVALID_USER (PIERR_SECURITY_ERROR + 0)
#define PIERR_INVALID_PWD (PIERR_SECURITY_ERROR + 1)
#define PIERR_INVALID_USER_PWD (PIERR_SECURITY_ERROR + 2)
#define PIERR_INVALID_PWDS_NOT_MATCH (PIERR_SECURITY_ERROR + 3)
#define PIERR_NOT_AUTHORIZED (PIERR_SECURITY_ERROR + 4)
#define PIERR_INACTIVE_SESSION (PIERR_SECURITY_ERROR + 5)
#define PIERR_TOO_MANY_USER (PIERR_SECURITY_ERROR + 6)
#define PIERR_USER_DISABLED (PIERR_SECURITY_ERROR + 7)
#define PIERR_INVALID_SSL_CERTIFICATE (PIERR_SECURITY_ERROR + 8)

/* request, command and invalid data format or contents errors */
#define PIERR_INVALID_CMD_GROUP (PIERR_COMMAND_ERROR + 0)
#define PIERR_INVALID_COMMAND (PIERR_COMMAND_ERROR + 1)
#define PIERR_INVALID_PARAM (PIERR_COMMAND_ERROR + 2)
#define PIERR_MISSING_PARAM (PIERR_COMMAND_ERROR + 3)
#define PIERR_CMD_TOO_LONG (PIERR_COMMAND_ERROR + 4)
#define PIERR_BLANK_CMD (PIERR_COMMAND_ERROR + 5)
#define PIERR_INVALID_DATA (PIERR_COMMAND_ERROR + 6)
#define PIERR_INVALID_COUNT (PIERR_COMMAND_ERROR + 7)
#define PIERR_COMMENT_CMD (PIERR_COMMAND_ERROR + 8)
#define PIERR_INVALID_SIZE_PARAM (PIERR_COMMAND_ERROR + 9)
#define PIERR_FWCMD_NOT_SUPPORTED (PIERR_COMMAND_ERROR + 0x10)
#define PIERR_CMD_NOT_SUPPORTED_IN_MAITENANCE (PIERR_COMMAND_ERROR + 0x11)

#define PIERR_UNKNOWN_HOST_INTERFACE_TYPE (PIERR_COMMAND_ERROR + 0x20)
#define PIERR_UNKNOWN_DEVICE_INTERFACE_TYPE (PIERR_COMMAND_ERROR + 0x21)

/* i2ipc */

#define PIERR_I2API_INITIALIED (PIERR_I2API_ERROR + 0)
#define PIERR_I2API_NOT_INITIALIZED (PIERR_I2API_ERROR + 1)
#define PIERR_I2API_INVALID_VERSION (PIERR_I2API_ERROR + 2)
#define PIERR_I2API_PLUGINS_NOT_AVAILABLE (PIERR_I2API_ERROR + 3)
#define PIERR_I2API_PLUGIN_LOAD_FAILED (PIERR_I2API_ERROR + 4)
#define PIERR_I2API_GET_PLUGINAPI_FAILED (PIERR_I2API_ERROR + 5)
#define PIERR_I2API_INVALID_PLUGIN_INDEX (PIERR_I2API_ERROR + 6)

#define PIERR_I2API_DISCOVER_IN_PROGRESS (PIERR_I2API_ERROR + 0x10)

#define PIERR_I2API_PLUGIN_SPECIFIC_ERROR   (PIERR_I2API_ERROR + 0x100)   
#define PIERR_I2IPC_NO_MESSAGE (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 0)
#define PIERR_I2IPC_INVALID_MESSAGE (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 1)
#define PIERR_I2IPC_MESSAGE_TIMEOUT (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 2)
#define PIERR_I2IPC_PENDING (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 3)
#define PIERR_I2IPC_FAIL (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 4)
#define PIERR_I2IPC_COMM_ERROR (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 5)
#define PIERR_I2IPC_MSGQ_NOT_FOUND (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 6)
#define PIERR_I2IPC_I2_RESTARTED (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 7)

#define PIERR_I2API_NO_EVENT_SUBSCRIPTION (PIERR_I2API_PLUGIN_SPECIFIC_ERROR + 0x10)

/* I2 Sync Error */
#define PIERR_I2SYNC_ERROR               (PIERR_I2API_ERROR + 0x500)
#define PIERR_I2SYNC_INVALID_MSG         (PIERR_I2SYNC_ERROR + 0x0)
#define PIERR_I2SYNC_INVALID_MSG_REQ_GRP (PIERR_I2SYNC_ERROR + 0x1)
#define PIERR_I2SYNC_INVALID_MSG_REQ_ID  (PIERR_I2SYNC_ERROR + 0x2)
#define PIERR_I2SYNC_MSG_PENDING         (PIERR_I2SYNC_ERROR + 0x3)
#define PIERR_I2SYNC_CONN_BROKEN         (PIERR_I2SYNC_ERROR + 0x4)
#define PIERR_I2SYNC_REQHNDLR_NEW_ERROR      (PIERR_I2SYNC_ERROR + 0x5)
#define PIERR_I2SYNC_REQHNDLR_NEW_SUCCESS    (PIERR_I2SYNC_ERROR + 0x6)
#define PIERR_I2SYNC_MSG_TIMEOUT         (PIERR_I2SYNC_ERROR + 0x7)
#define PIERR_I2SYNC_NOT_INITIALIZED     (PIERR_I2SYNC_ERROR + 0x8)
#define PIERR_I2SYNC_INIT_IN_PROGRESS    (PIERR_I2SYNC_ERROR + 0x9)

/* CLI */
#define PIERR_LOGOUT_REQUIRED (PIERR_CLI_ERROR + 0)
#define PIERR_LINE_TOO_LONG (PIERR_CLI_ERROR + 1)
#define PIERR_MORE_CANCELED (PIERR_CLI_ERROR + 2)
#define PIERR_CLI_TOO_MANY_OPTIONS (PIERR_CLI_ERROR + 3)
#define PIERR_CLI_TERMINATED (PIERR_CLI_ERROR + 4)

#define PIERR_INVALID_ACTION (PIERR_CLI_ERROR + 0x10)
#define PIERR_ACTION_NOT_APPLY (PIERR_CLI_ERROR + 0x11)
#define PIERR_INVALID_OPTION (PIERR_CLI_ERROR + 0x12)
#define PIERR_INVALID_SETTING (PIERR_CLI_ERROR + 0x13)
#define PIERR_SETTING_TOO_LONG (PIERR_CLI_ERROR + 0x14)
#define PIERR_MISSING_QUOTE (PIERR_CLI_ERROR + 0x15)
#define PIERR_SETTING_EMPTY (PIERR_CLI_ERROR + 0x16)

#define PIERR_INVALID_BGA_RATE (PIERR_CLI_ERROR + 0x30)
#define PIERR_INVALID_IP (PIERR_CLI_ERROR + 0x31)
#define PIERR_INVALID_DATE (PIERR_CLI_ERROR + 0x32)
#define PIERR_INVALID_TIME (PIERR_CLI_ERROR + 0x33)
#define PIERR_INVALID_ALIAS (PIERR_CLI_ERROR + 0x34)
#define PIERR_INVALID_INTEGER (PIERR_CLI_ERROR + 0x35)

#define PIERR_CLU_HELP_NOT_FOUND (PIERR_CLI_ERROR + 0x40)

/* Device */
#define PIERR_DEVICE_NOT_FOUND (PIERR_DEVICE_ERROR + 0)
#define PIERR_INVALID_DEVICE_ID (PIERR_DEVICE_ERROR + 1)
#define PIERR_DUP_DEVICE_ID (PIERR_DEVICE_ERROR + 2)

#define PIERR_SUBSYS_NOT_FOUND (PIERR_DEVICE_ERROR + 0x08)
#define PIERR_INVALID_SUBSYS_PATH_ID (PIERR_DEVICE_ERROR + 0x09)

#define PIERR_CTRL_NOT_FOUND (PIERR_DEVICE_ERROR + 0x10)
#define PIERR_INVALID_CTRL_ID (PIERR_DEVICE_ERROR + 0x11)
#define PIERR_DUP_CTRL_ID (PIERR_DEVICE_ERROR + 0x12)
#define PIERR_INVALID_CTRL_DEBUG_LEVEL (PIERR_DEVICE_ERROR + 0x13)
#define PIERR_CTRL_MAINTENANCE (PIERR_DEVICE_ERROR + 0x14)

#define PIERR_PHYDRV_NOT_FOUND (PIERR_DEVICE_ERROR + 0x20)
#define PIERR_PHYDRV_IN_USE (PIERR_DEVICE_ERROR + 0x21)
#define PIERR_PHYDRV_OUT_OF_SPACE (PIERR_DEVICE_ERROR + 0x22)
#define PIERR_INVALID_PHYDRV_ID (PIERR_DEVICE_ERROR + 0x23)
#define PIERR_DUP_PHYDRV_ID (PIERR_DEVICE_ERROR + 0x24)
#define PIERR_PHYDRV_PFA (PIERR_DEVICE_ERROR + 0x25)
#define PIERR_PHYDRV_STALE (PIERR_DEVICE_ERROR + 0x26)
#define PIERR_INVALID_DRIVE_TYPE (PIERR_DEVICE_ERROR + 0x27)
#define PIERR_PHYDRV_NOT_DEAD (PIERR_DEVICE_ERROR + 0x28) 
#define PIERR_PHYDRV_NOT_ACCESSIBLE (PIERR_DEVICE_ERROR + 0x29)

#define PIERR_LOGDRV_NOT_FOUND (PIERR_DEVICE_ERROR + 0x30)
#define PIERR_INVALID_LOGDRV_ID (PIERR_DEVICE_ERROR + 0x31)
#define PIERR_DUP_LOGDRV_ID (PIERR_DEVICE_ERROR + 0x32)
#define PIERR_NAS_LD_ILLEGAL_OPERATION (PIERR_DEVICE_ERROR + 0x33)

#define PIERR_DSKARR_NOT_FOUND (PIERR_DEVICE_ERROR + 0x40)
#define PIERR_INVALID_DSKARR_ID (PIERR_DEVICE_ERROR + 0x41)
#define PIERR_DUP_DSKARR_ID (PIERR_DEVICE_ERROR + 0x42)
#define PIERR_INVALID_DSKARR_DRV_SEQNUM (PIERR_DEVICE_ERROR + 0x43)
#define PIERR_SPARE_NOT_FOUND (PIERR_DEVICE_ERROR + 0x44)
#define PIERR_INVALID_SPARE_ID (PIERR_DEVICE_ERROR + 0x45)
#define PIERR_DUP_SPARE_ID (PIERR_DEVICE_ERROR + 0x46)
#define PIERR_DSKARR_CONDITION_NORMAL (PIERR_DEVICE_ERROR + 0x47)

#define PIERR_ISCSI_PORT_NOT_FOUND (PIERR_DEVICE_ERROR + 0x50)
#define PIERR_MGMT_PORT_NOT_FOUND (PIERR_DEVICE_ERROR + 0x51)
#define PIERR_INVALID_PORT_ID (PIERR_DEVICE_ERROR + 0x52)
#define PIERR_INVALID_ENCLOSURE_ID (PIERR_DEVICE_ERROR + 0x53)
#define PIERR_INVALID_BATTERY_ID (PIERR_DEVICE_ERROR + 0x54)
#define PIERR_INVALID_NODE_ID (PIERR_DEVICE_ERROR + 0x55)
#define PIERR_INVALID_SESS_ID (PIERR_DEVICE_ERROR + 0x56)
#define PIERR_INVALID_FRU_ID (PIERR_DEVICE_ERROR + 0x57)
#define PIERR_INVALID_FRU_TYPE (PIERR_DEVICE_ERROR + 0x58)
#define PIERR_INVALID_ENCLOSURE_TYPE (PIERR_DEVICE_ERROR + 0x59)

#define PIERR_INITIATOR_NOT_FOUND (PIERR_DEVICE_ERROR + 0x60)
#define PIERR_INVALID_INITIATOR_INDEX (PIERR_DEVICE_ERROR + 0x61)
#define PIERR_DUP_INITIATOR_INDEX (PIERR_DEVICE_ERROR + 0x62)
#define PIERR_INVALID_TARGET_INDEX (PIERR_DEVICE_ERROR + 0x63)

#define PIERR_LMM_NOT_FOUND (PIERR_DEVICE_ERROR + 0x70)
#define PIERR_INVALID_LMM_INDEX (PIERR_DEVICE_ERROR + 0x71)
#define PIERR_INVALID_LUN_VALUE (PIERR_DEVICE_ERROR + 0x72)
#define PIERR_DUP_LMM_INDEX (PIERR_DEVICE_ERROR + 0x73)
#define PIERR_DUP_LUN_VALUE (PIERR_DEVICE_ERROR + 0x74)

/* Configuration */
#define PIERR_LIMIT_LOGDRV_PER_DSKARR (PIERR_CONFIG_ERROR + 0)
#define PIERR_LIMIT_PHYDRV_PER_DSKARR (PIERR_CONFIG_ERROR + 1)
#define PIERR_LIMIT_LOGDRV_PER_CTRL (PIERR_CONFIG_ERROR + 2)
#define PIERR_LIMIT_DSKARR_PER_DSPARE (PIERR_CONFIG_ERROR + 3)
#define PIERR_LIMIT_DSPARE_PER_DSKARR (PIERR_CONFIG_ERROR + 4)
#define PIERR_LIMIT_FRAGMENT_PER_DSKARR (PIERR_CONFIG_ERROR + 5)
#define PIERR_LIMIT_LOGDRV_PER_NAS (PIERR_CONFIG_ERROR + 6)

#define PIERR_INVALID_DSKARR_FOR_GSPARE (PIERR_CONFIG_ERROR + 0x10)
#define PIERR_NO_DSKARR_FOR_DSPARE (PIERR_CONFIG_ERROR + 0x11)
#define PIERR_INVALID_SIZE (PIERR_CONFIG_ERROR + 0x12)
#define PIERR_INVALID_STRIPESIZE (PIERR_CONFIG_ERROR + 0x13)
#define PIERR_IMPOSSIBLE_RAID_LEVEL (PIERR_CONFIG_ERROR + 0x14)
#define PIERR_INVALID_RAID_LEVEL (PIERR_CONFIG_ERROR + 0x15)
#define PIERR_INVALID_AXLE (PIERR_CONFIG_ERROR + 0x16)
#define PIERR_INVALID_WRITE_POLICY (PIERR_CONFIG_ERROR + 0x17)
#define PIERR_INVALID_READ_POLICY (PIERR_CONFIG_ERROR + 0x18)
#define PIERR_INVALID_LOGDRV_DEF (PIERR_CONFIG_ERROR + 0x19)
#define PIERR_INVALID_SECTOR_SIZE (PIERR_CONFIG_ERROR + 0x1a)
#define PIERR_SECTOR_GREATER_THAN_STRIPE (PIERR_CONFIG_ERROR + 0x1b)
#define PIERR_INVALID_R5_ALGORITHM (PIERR_CONFIG_ERROR + 0x1c)
#define PIERR_DSPARE_SIZE_TOO_SMALL (PIERR_CONFIG_ERROR + 0x1d)

#define PIERR_DSKARR_OUT_OF_SPACE (PIERR_CONFIG_ERROR + 0x20)
#define PIERR_FRAGMENT_SIZE_TOO_SMALL (PIERR_CONFIG_ERROR + 0x21)
#define PIERR_INVALID_PAGE_CODE (PIERR_CONFIG_ERROR + 0x22)

#define PIERR_SETTINGS_NO_CHANGE (PIERR_CONFIG_ERROR + 0x30)

/* MIGRATION */
#define PIERR_MIGRATION_IMPOSSIBLE (PIERR_CONFIG_ERROR + 0x40)
#define PIERR_NO_LOGDRV_IN_ARRAY (PIERR_CONFIG_ERROR + 0x41)
#define PIERR_MIGRATION_RAID6_NOT_SUPPORTED (PIERR_CONFIG_ERROR + 0x42)
#define PIERR_MIGRATION_ARRAY_DEGRADED (PIERR_CONFIG_ERROR + 0x43)
#define PIERR_MIGRATION_BGA_RUNNING (PIERR_CONFIG_ERROR + 0x44)
#define PIERR_MIGRATION_ARRAY_OFFLINE (PIERR_CONFIG_ERROR + 0x45)
#define PIERR_MIGRATION_ARRAY_INCOMPLETE (PIERR_CONFIG_ERROR + 0x46)
#define PIERR_MIGRATION_ARRAY_TRANSPORT_READY (PIERR_CONFIG_ERROR + 0x47)
#define PIERR_MIGRATION_LOGDRV_NOT_OK (PIERR_CONFIG_ERROR + 0x48)
#define PIERR_MIGRATION_RAID6_OCE_NOT_SUPPORTED (PIERR_CONFIG_ERROR + 0x49)
#define PIERR_MIGRATION_RAID6_RLM_NOT_SUPPORTED (PIERR_CONFIG_ERROR + 0x4A)
#define PIERR_MIGRATION_NOT_START_RAID6_LOGDRV (PIERR_CONFIG_ERROR + 0x4B)

/* FLASH */
#define PIERR_FLASH_NOT_READY (PIERR_CONFIG_ERROR + 0x50)
#define PIERR_FLASH_TRANSFER_ERROR (PIERR_CONFIG_ERROR + 0x51)
#define PIERR_FLASH_TRANSFER_TIMEOUT (PIERR_CONFIG_ERROR + 0x52)
#define PIERR_FLASH_TRANSFER_FILE_NOT_FOUND (PIERR_CONFIG_ERROR + 0x53)
#define PIERR_FLASH_FLASH_ERROR (PIERR_CONFIG_ERROR + 0x54)
#define PIERR_INVALID_FLASH_IMG (PIERR_CONFIG_ERROR + 0x55)
#define PIERR_INVALID_FLASH_IMG_SEP (PIERR_CONFIG_ERROR + 0x56)
#define PIERR_FLASH_ABORTED_FAILOVER (PIERR_CONFIG_ERROR + 0x57)
#define PIERR_FLASH_UPDATE_IN_PROGRESS (PIERR_CONFIG_ERROR + 0x58)

/*nas */
#define PIERR_NAS_LOGDRV_SIZE_TOO_SMALL (PIERR_CONFIG_ERROR + 0x60) 
#define PIERR_NAS_LOGDRV_SIZE_TOO_BIG (PIERR_CONFIG_ERROR + 0x61)
#define PIERR_NAS_LOGDRV_INVALID_MOUNT_POINT (PIERR_CONFIG_ERROR + 0x62)

/* BGA */
#define PIERR_BGA_INACTIVE (PIERR_BGA_ERROR + 0)
#define PIERR_BGA_DELETE_ERROR (PIERR_BGA_ERROR + 1)
#define PIERR_BGA_ADD_ERROR (PIERR_BGA_ERROR + 2)

/* service*/
/* ntp*/
#define PIERR_SERVICE_NTP_ERROR (PIERR_SERVICE_ERROR + 0)
#define PIERR_SERVICE_NTP_DISABLED (PIERR_SERVICE_NTP_ERROR + 0)
#define PIERR_SERVICE_NTP_NONE_TIMESERVER (PIERR_SERVICE_NTP_ERROR + 1)
#define PIERR_SERVICE_NTP_NTPDATE_FAIL (PIERR_SERVICE_NTP_ERROR + 2)
#define PIERR_SERVICE_NTP_EXECUTE_FAIL (PIERR_SERVICE_NTP_ERROR + 3)
#define PIERR_SERVICE_NTP_TESTSERVER_FAIL (PIERR_SERVICE_NTP_ERROR + 4)

/* event */
#define PIERR_EVENT_NOT_FOUND (PIERR_EVENT_ERROR + 0)
#define PIERR_INVALID_EVENT_LOCATION (PIERR_EVENT_ERROR + 0x1)
#define PIERR_EVENT_ID_OUTOFRANGE (PIERR_EVENT_ERROR + 0x2)
#define PIERR_EVENT_EMPTY_STRING (PIERR_EVENT_ERROR + 0x3)
#define PIERR_EVENT_STRLENGTH_TOOLONG (PIERR_EVENT_ERROR + 0x4)
#define PIERR_EVENT_DUPLICATED (PIERR_EVENT_ERROR + 0x5)
#define PIERR_EVENT_TOTAL_EXCEED_MAX (PIERR_EVENT_ERROR + 0x6)
#define PIERR_EVENT_NEW_EVENT (PIERR_EVENT_ERROR + 0x7)
#define PIERR_EVENT_MISSING_EVENT (PIERR_EVENT_ERROR + 0x8)
#define PIERR_EVENT_DUPLICATE_SEVERITY (PIERR_EVENT_ERROR + 0x9)
#define PIERR_EVENT_DUPLICATE_CLASS (PIERR_EVENT_ERROR + 0xA)
#define PIERR_EVENT_DUPLICATE_LOGLOCATION (PIERR_EVENT_ERROR + 0xB)
#define PIERR_EVENT_LINE_BREAK (PIERR_EVENT_ERROR + 0xC)
#define PIERR_EVENT_NOTIFY_NOT_INITIALIZED (PIERR_EVENT_ERROR + 0xD)

/* bga schedule */
#define PIERR_LIMIT_SCHEDULES (PIERR_SCHEDULE_ERROR + 0)
#define PIERR_SCHEDULE_NOT_FOUND (PIERR_SCHEDULE_ERROR + 1)
#define PIERR_END_OF_SCHEDULE (PIERR_SCHEDULE_ERROR + 2)

#define PIERR_EXIST_SCHEDULE_ON_DEVICE (PIERR_SCHEDULE_ERROR + 0x10)
#define PIERR_INVALID_SCHEDULE_TYPE (PIERR_SCHEDULE_ERROR + 0x11)
#define PIERR_INVALID_SCHEDULE (PIERR_SCHEDULE_ERROR + 0x12)

/* XML Parser Error */
#define PIERR_XMLPARSER_PARSE_ERROR    (PIERR_XMLPARSER_ERROR + 0)
#define PIERR_XMLPARSER_NOSUCH_FILETYPE (PIERR_XMLPARSER_ERROR + 1)
#define PIERR_XML_VALID_ERROR (PIERR_XMLPARSER_ERROR + 2)

/* CIM Error */
#define PIERR_CIM_EXCEPTION (PIERR_CIM_ERROR + 0)
/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: getErrorDescription 
* Description: get the description of the specified error code.
* Parameters:    
*   	[in] errCode, the specified error code
* Return: The error message.
* Remarks: none.     
****************************************************************************/
ERRLOGAPI char * ERRLOGCALL getErrorDescription(u32 u32ErrCode);

/**************************************************************************
* Function Name: formPMICErrorCode 
* Description: form the PMIC error code according to completion status,
*       and sense information.
* Parameters:    
*   	[in] u8CompStatus, the completion status
*       [in] pu8Sense, the sense buffer
*       [in] u32SenseLen, the sense buffer length
* Return: The PMIC error code. The format of the PMIC error code is:
*           (PIERR_PMIC_ERROR | (<sense key> << 24) | (<asc> << 16) |
*           (<ascq> << 8) | (completion status))
* Remarks: none.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL formPMICErrorCode(u8 u8CompStatus, u8 * pu8Sense, u32 u32SenseLen);

ERRLOGAPI boolean_t ERRLOGCALL isPMICErrorCode(const u32 u32ErrorCode);

ERRLOGAPI u8 ERRLOGCALL getPMICErrorAsc(const u32 u32ErrorCode);
ERRLOGAPI u8 ERRLOGCALL getPMICErrorAscq(const u32 u32ErrorCode);
ERRLOGAPI u8 ERRLOGCALL getPMICErrorSenseKey(const u32 u32ErrorCode);
ERRLOGAPI u8 ERRLOGCALL getPMICErrorStatus(const u32 u32ErrorCode);

/**************************************************************************
* Function Name: getPMICErrorDescription 
* Description: get the description message of the PMIC error code.
* Parameters:    
*   	[in] u32PMICErrCode, the PMIC error code formed by 
*           formPMICErrorCode(...).
*       [out] pstrBuf, the message will be returned here.
*       [in] u32BufLen, the length of the message buffer.
* Return: PIERR_NO_ERROR, if succeeded; otherwise, failed.
* Remarks: none.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL getPMICErrorDescription(u32 u32PMICErrCode, char * pstrBuf, u32 u32BufLen);

#endif /* __PI_ERRCODE_H__ */

/*******************************************************************************
 * Change Log
 *
 * $Log: errcode.h,v $
 * Revision 1.95.6.4  2010/02/04 07:28:18  xinw
 * add new nas error
 *
 * Revision 1.95.6.3  2009/11/23 10:54:24  xinw
 * add PIERR_LIMIT_LOGDRV_PER_NAS
 *
 * Revision 1.95.6.2  2009/11/20 09:22:10  xinw
 * add ntp support
 *
 * Revision 1.95.6.1  2009/10/15 03:01:37  xinw
 * add nas support
 *
 * Revision 1.95  2008/03/24 09:04:36  danielz
 * add some error codes for i2 sync
 *
 * Revision 1.94  2007/10/22 09:04:49  xinw
 * add new error code for reject shutdown command during updating fw
 *
 * Revision 1.93  2007/08/15 05:25:25  danielz
 * new error code PIERR_DSPARE_SIZE_TOO_SMALL
 *
 * Revision 1.92  2007/07/31 21:34:25  JudithLi
 * change PIERR_EVENT_NOT_INITIALIZED to PIERR_EVENT_NOTIFY_NOT_INITIALIZED
 *
 * Revision 1.91  2007/07/31 03:37:13  danielz
 * new error code PIERR_MIGRATION_NOT_START_RAID6_LOGDRV
 *
 * Revision 1.90  2007/07/24 18:13:35  JudithLi
 * Event Notification in-band support
 *
 * Revision 1.89  2007/06/27 05:30:47  danielz
 * new error code for Raid6/60 RLM/OCM
 *
 * Revision 1.88  2007/05/07 23:38:56  debinc
 * migration eligibility
 *
 * Revision 1.87  2006/11/28 08:14:30  danielz
 * new error code PIERR_READ_FILE_ERROR for failing to read file
 *
 * Revision 1.86  2006/09/21 19:49:17  xinw
 * remove error code PIERR_JUST_SYNC_FAIL
 *
 * Revision 1.85  2006/09/17 00:31:11  xinw
 * add new error code for one ctrl aborted during dual ctrls flash
 *
 * Revision 1.84  2006/09/15 06:36:47  danielz
 * Add a new error code PIERR_CMD_NOT_SUPPORTED_IN_MAITENANCE
 *
 * Revision 1.83  2006/08/28 23:59:36  xinw
 * add and modify some error code
 *
 * Revision 1.82  2006/08/04 07:26:20  danielz
 * Add a new error code PIERR_MIGRATION_RAID6_NOT_SUPPORTED
 *
 * Revision 1.81  2006/07/26 06:36:49  danielz
 * Add a new error code PIERR_PHYDRV_NOT_ACCESSIBLE for the inaccessible
 * physical drive
 *
 * Revision 1.80  2006/07/13 10:07:38  xinw
 * add error code
 *
 * Revision 1.79  2006/06/19 10:09:15  danielz
 * Add a new error code PIERR_NO_LOGDRV_IN_ARRAY
 *
 * Revision 1.78  2006/05/30 16:18:07  xinw
 * update dual sync
 *
 * Revision 1.77  2006/05/17 03:34:04  danielz
 * Add a new error code PIERR_PHYDRV_NOT_DEAD.
 *
 * Revision 1.76  2006/04/15 19:01:54  xinw
 * add dual shutdown
 *
 * Revision 1.75  2006/01/12 05:22:50  JudithLi
 * CLU Advanced Configuration to improve error message
 *
 * Revision 1.74  2005/12/10 00:37:09  weny
 * Add Invalid Drive Type
 *
 * Revision 1.73  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.72  2005/07/01 08:35:40  fieldsy
 * *** empty log message ***
 *
 * Revision 1.71  2005/04/20 23:31:15  debinc
 * new decode function
 *
 * Revision 1.70  2005/04/16 01:14:53  debinc
 * new error code
 *
 * Revision 1.69  2005/04/15 02:07:54  debinc
 * new error code
 *
 * Revision 1.68  2005/03/24 18:09:20  weny
 * add NULL_IP_ADDRESS
 *
 * Revision 1.67  2005/02/23 02:28:29  debinc
 * add error code
 *
 * Revision 1.66  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.65  2004/12/02 07:48:58  weny
 * add error code of SETTING_EMPTY
 *
 * Revision 1.64  2004/11/17 06:39:28  weny
 * add error code for none user exit
 *
 * Revision 1.63  2004/10/08 22:58:39  weny
 * added INVALID_ENCLOSURE_TYPE
 *
 * Revision 1.62  2004/10/07 02:04:55  debinc
 * add unresolve ip  error
 *
 * Revision 1.61  2004/10/06 23:06:59  debinc
 * add network interface error code
 *
 * Revision 1.60  2004/10/06 21:06:07  ken.cai
 * added CLU help info error code
 *
 * Revision 1.59  2004/09/23 04:03:40  weny
 * R5 algorithm support
 *
 * Revision 1.58  2004/08/31 06:43:35  weny
 * more error codes for nvram watermark
 *
 * Revision 1.57  2004/08/27 21:10:34  debinc
 * new error code INVALID_SSL_CERTIFICATE
 *
 * Revision 1.56  2004/08/26 03:59:41  weny
 * add an error code
 *
 * Revision 1.55  2004/08/18 23:28:17  weny
 * added some error codes
 *
 * Revision 1.54  2004/08/03 03:30:36  weny
 * add more error codes
 *
 * Revision 1.53  2004/07/28 01:36:14  weny
 * add more error codes to improve error msg more descriptive
 *
 * Revision 1.52  2004/07/22 04:03:00  weny
 * stale drive handling
 *
 * Revision 1.51  2004/07/15 18:21:22  weny
 * add some error codes for factory default settings
 *
 * Revision 1.50  2004/07/08 23:05:05  weny
 * merge with Napa I2 API
 *
 * Revision 1.49  2004/07/06 21:33:22  debinc
 * new user disable error code
 *
 * Revision 1.48  2004/06/28 20:31:49  weny
 * Added LD Variable Sector Size Support
 *
 * Revision 1.47  2004/05/04 18:25:03  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.46  2004/04/15 00:32:19  zhengj
 * added error code for cli
 *
 * Revision 1.45  2004/04/13 22:25:08  debinc
 * Add a "access voliation" error definition
 *
 * Revision 1.44  2004/04/13 00:37:22  debinc
 * Add a event related log location error definition
 *
 * Revision 1.43  2004/04/09 23:26:20  zhengj
 * added error code for flash
 *
 * Revision 1.42  2004/04/02 21:54:32  debinc
 * add user error code
 *
 * Revision 1.41  2004/03/30 19:01:13  debinc
 * Add two more event customization errors
 *
 * Revision 1.40  2004/03/24 03:27:22  weny
 * I2 API porting
 *
 * Revision 1.39  2004/03/11 00:03:37  debinc
 * Add two more BGA error definition
 *
 * Revision 1.38  2004/03/05 22:20:12  zhengj
 * added support for system time and stats
 *
 * Revision 1.37  2004/03/05 03:23:35  debinc
 * Two new event error code
 *
 * Revision 1.36  2004/02/18 22:36:49  debinc
 * More event customization related error code
 *
 * Revision 1.35  2004/02/14 01:44:34  zhengj
 * improve flash error code
 *
 * Revision 1.34  2004/02/10 23:35:17  zhengj
 * flash support modification
 *
 * Revision 1.33  2004/02/06 03:33:57  debinc
 * new XML error code
 *
 * Revision 1.32  2004/01/30 03:55:38  zhengj
 * lmm support
 *
 * Revision 1.31  2004/01/30 03:33:31  weny
 * add error code of INVALID_CTRL_DEBUG_LEVEL
 *
 * Revision 1.30  2004/01/28 00:36:18  weny
 * add error codes for TFTP get/put
 *
 * Revision 1.29  2004/01/23 01:03:04  weny
 * add an error code
 *
 * Revision 1.28  2003/12/18 01:31:14  debinc
 * XML parser error
 *
 * Revision 1.27  2003/12/03 22:23:41  debinc
 * new error code
 *
 * Revision 1.26  2003/11/04 23:38:40  zhengj
 * some changes for device numbering and more
 *
 * Revision 1.25  2003/10/17 01:13:14  zhengj
 * more error code
 *
 * Revision 1.24  2003/10/14 00:07:36  weny
 * add PIERR_ALREADY_RUNNING for I2 singleton
 *
 * Revision 1.23  2003/09/26 21:25:01  weny
 * CIM Error code
 *
 * Revision 1.22  2003/09/19 00:05:48  weny
 * add some support to bga cmd and phydrv online/offline
 *
 * Revision 1.21  2003/09/18 19:12:32  zhengj
 * subsys ctrl PD settings
 *
 * Revision 1.20  2003/09/13 00:34:37  weny
 * config lock support
 *
 * Revision 1.19  2003/07/14 18:48:36  weny
 * add INVALID_LD_DEF
 *
 * Revision 1.18  2003/06/28 05:47:44  weny
 * add bga scheduler support
 *
 * Revision 1.17  2003/06/28 03:26:56  weny
 * iscsi node info support
 *
 * Revision 1.16  2003/06/27 23:48:25  weny
 * add some more error codes
 *
 * Revision 1.15  2003/06/26 21:04:08  weny
 * add some error codes
 *
 * Revision 1.14  2003/06/24 02:25:29  zhengj
 * added PIERR_COMMENT_COMMAND
 *
 * Revision 1.13  2003/06/12 02:34:38  weny
 * add some event related error codes
 *
 * Revision 1.12  2003/06/03 20:57:48  weny
 * add more specific error codes.
 *
 * Revision 1.11  2003/04/15 17:49:29  weny
 * adding more error codes
 *
 * Revision 1.10  2003/04/14 19:36:02  weny
 * add PMIC error support
 *
 * Revision 1.9  2003/04/11 05:15:37  weny
 * add more error codes
 *
 * Revision 1.8  2003/04/10 03:35:30  weny
 * add more cfg error code
 *
 * Revision 1.7  2003/04/09 19:50:13  weny
 * add more error codes for cfg
 *
 * Revision 1.6  2003/04/08 23:29:49  weny
 * add some configuration related error codes
 *
 * Revision 1.5  2003/04/02 00:10:39  weny
 * add some error codes related to f/w interface
 *
 * Revision 1.4  2003/03/22 00:55:39  weny
 * add some new error codes.
 *
 * Revision 1.3  2003/03/11 23:53:52  weny
 * add pmic error code support.
 *
 * Revision 1.2  2003/03/07 04:50:08  weny
 * add PIERR_PROCESS_FORK.
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/

