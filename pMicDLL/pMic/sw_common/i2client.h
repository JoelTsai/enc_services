/*******************************************************************************
 * Filename    : i2client.h
 * Description : i2client header file
 *               * Define the interfaces and data structures that I2 client 
 *                 library provides to the upper layer components.
 *               * Shared among I2 IPC Client Lib, and the components that use 
 *                 the I2 IPC Client Lib
 * Created on  : 02/03/03
 * CVS Version : $Id: i2client.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_I2CLIENT_H__
#define __PI_I2CLIENT_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "reqdata.h"
#include "dtdecode.h"
#include "errorlog.h"
#include "autoconfig.h"
#ifdef IN_BAND
    #include "subspath.h"
#endif

/* --- constant definitions ------------------------------------------------ */

#define I2IPC_CLIENT_LIB_VERSION 1

/* --- data structures ----------------------------------------------------- */

typedef void i2ipc_client_t; /* to emcapsulate the i2 client mechanism inside itself */

typedef struct
{
    u32 icp_u32Version; /* Dynamic Shared Object version */
    u32 icp_u32Reserved0;

#ifndef IN_BAND
    char * icp_pstrMsgQueuePath; /* these 3 params are related to I2 IPC */
    u32 icp_u32MsgQueueChannel;
    u32 icp_u32NotificationSignal;
    u32 icp_u32Reserved1;
#endif

    u32 icp_u32MinLines; /* tune i2 ipc client performance of the IPC */
    u32 icp_u32MaxLines;
    u32 icp_u32BufferSize; /* in Bytes */
    u32 icp_u32MaxReqTimeout; /* in seconds */
	
#ifndef SINGLE_ERROR_HANDLER
    /* pass the error handler to the I2 IPC client, so that the lib will use the 
        same error handler to log the messages */
    error_handler_t * icp_pehErrorHandler;  
    u32 icp_u32Reserved2;
#endif

#ifdef PSUDO_CODE
    boolean_t icp_bPsudo;
    u8 icp_u8Reserved3[7];
#endif
} i2ipc_client_param_t;

/* --- functional routines ------------------------------------------------- */

/* construction & destruction */
/******************************************************************************
* Function Name: i2clnt_createI2IPCClient
* Description: create a I2 IPC Client object
* Parameters:    
*       [out] ppic, the I2 IPC Client object to be created and returned
*       [in] picp, the parameter of the I2 IPC Client
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: none.
*******************************************************************************/
u32 i2clnt_createI2IPCClient(i2ipc_client_t ** ppic, i2ipc_client_param_t * picp);

/******************************************************************************
* Function Name: i2clnt_destroyI2IPCClient                                       
* Description: destroy a I2 IPC Client object.
* Parameters:    
*       [in/out] ppic, the I2 IPC Client object to be destroyed. After 
*           destruction, it will be set to NULL.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
*       In case this function fails, the I2 IPC Client object will be in an
*       unknown status, it must NOT be reused any more.
* Remarks: i2clnt_createI2IPCClient should be called before this func is called.
*******************************************************************************/
u32 i2clnt_destroyI2IPCClient(i2ipc_client_t ** ppic);

#ifdef PSUDO_CODE
u32 i2clnt_getPsudo(i2ipc_client_t * pic, boolean_t * pbPsudo);
u32 i2clnt_setPsudo(i2ipc_client_t * pic, boolean_t bPsudo);
#endif

#ifdef IN_BAND
/******************************************************************************
* Function Name: i2clnt_discover                                       
* Description: discover the subsystems. This function must be called for in-band
*       after i2clnt_createI2IPCClient() and before any other management function
*       can be called. It will return up to maximum number of paths to subsystems.
*       There might be multiple paths leading to the same subsystem. It is up to
*       the upper layer to resolve the multi-path.
*       The I2 IPC Client communicates to one subsystem at one time. Therefore,
*       the upper layer need to set the current subsystem path to the desired 
*       subsystem and through the desired path.
*       After discovery, the current subsystem path will be set to the first
*       discovered path. The upper layer can use i2clnt_changeSubsysPath to chage
*       the current subsystem path to the desired one.
* Parameters:    
*       [in] pic, the pointer to the I2 IPC Client, returned from 
*           i2clnt_createI2IPCClient()
*       [in] u32MaxPaths, the maximum subsystem paths that the upper layer wants
*           the I2 IPC Client to return.
*       [out] pu32PathReturned, the actual number of subsystem paths discovered
*       [out] pspSubsysPaths, the buffer to for the subsystem paths to be returned.
*           The upper layer must make sure it is a buffer enough to hold u32MaxPaths
*           number of subsys_path_t. Otherwise, it may cause memory violation.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
*       In case this function fails, the I2 IPC Client object will be in an
*       unknown status, it must NOT be reused any more.
* Remarks: i2clnt_createI2IPCClient should be called before this func is called.
*******************************************************************************/
u32 i2clnt_discover(i2ipc_client_t * pic, u32 u32MaxPaths, 
    u32 * pu32PathReturned, u32 * pu32CurrentPath, subsys_path_t * pspSubsysPaths);
    
u32 i2clnt_rescan(i2ipc_client_t * pic);

/******************************************************************************
* Function Name: i2clnt_changeSubsysPath                                       
* Description: change the current subsystem path that the I2 IPC Client 
*       communicates to.
*       Before calling this function, the upper layer should make sure there is 
*       not any pending request on the original subsystem path. Otherwise, the
*       result behavior might be unpredictable.
* Parameters:    
*       [in] pic, the pointer to the I2 IPC Client, returned from 
*           i2clnt_createI2IPCClient()
*       [in] pspSubsysPath, the desired subsystem path.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
*       In case this function fails, the I2 IPC Client object will be in an
*       unknown status, it must NOT be reused any more.
* Remarks: i2clnt_createI2IPCClient and i2clnt_discover() should be called 
*       before this func is called.
*******************************************************************************/
u32 i2clnt_changeSubsysPath(i2ipc_client_t * pic, subsys_path_t * pspSubsysPath);
#endif /* IN_BAND */

/* management */
/******************************************************************************
* Function Name Prototype: i2clnt_get<element>Info
* Description: get the information of the specific manageable element
* Parameters:    
*       [in] pic, the pinter to the i2 client
*       [in] u32SessionId, the session id obtained by a call to i2clnt_login
*       [in] pParam, the parameter if applicable
*       [out] pData, the data buffer where the info will be returned
*       [in] u32ParamSize, the size of the param buffer if applicable. This is
*           required whe the param size is variable.
*       [in] u32DataSize, the size of the data buffer if applicable. This is
*           required when the returned information has a variable size.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient should be called before this function is
*       is called. Except for i2clnt_getSubsystemInfo, i2clnt_login should be
*       called to obtain a valid session id.
*******************************************************************************/
u32 i2clnt_getSubsystemInfo(i2ipc_client_t * pic, u32 u32SessionId, req_data_subsys_info_t * pData);
u32 i2clnt_getControllerInfo(i2ipc_client_t * pic, u32 u32SessionId, req_param_ctrl_info_t * pParam, req_data_ctrl_info_t * pData, u32 u32DataSize);
u32 i2clnt_getLogDrvInfo(i2ipc_client_t * pic, u32 u32SessionId, req_param_logdrv_info_t * pParam, req_data_logdrv_info_t * pData, u32 u32DataSize);
u32 i2clnt_getPhyDrvInfo(i2ipc_client_t * pic, u32 u32SessionId, req_param_phydrv_info_t * pParam, req_data_phydrv_info_t * pData, u32 u32DataSize);
u32 i2clnt_getMissingPhyDrvInfo(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_phydrv_info_t *pParam, req_data_phydrv_info_t *pData, 
    u32 u32DataSize);
u32 i2clnt_processIncompleteArray(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_array_process_t *pParam);
u32 i2clnt_getTransitionPhyDrvInfo(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_array_info_t *pParam, req_data_phydrv_info_t *pData, 
    u32 u32DataSize);

/******************************************************************************
* Function Name Prototype: i2clnt_get/set<element>Settings
* Description: get or set the settings of the specific manageable element
* Parameters:    
*       [in] pic, the pinter to the i2 client
*       [in] u32SessionId, the session id obtained by a call to i2clnt_login
*       [in] pParam, the id and page code of the settings
*       [in/out] pData, the data buffer contains the settings
*       [in] u32DataSize, the size of the data buffer if applicable.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient should be called before this function is
*       is called. i2clnt_login should be called to obtain a valid session id.
*******************************************************************************/
u32 i2clnt_getSubsystemSettings(i2ipc_client_t * pic, u32 u32SessionId, req_data_subsys_settings_t * pData);
u32 i2clnt_setSubsystemSettings(i2ipc_client_t * pic, u32 u32SessionId, req_data_subsys_settings_t * pData);
u32 i2clnt_getControllerSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_ctrl_settings_t * pParam, req_data_ctrl_settings_t * pData, u32 u32DataSize);
u32 i2clnt_setControllerSettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ctrl_settings_t * pParam, req_data_ctrl_settings_t * pData, u32 u32DataSize);

u32 i2clnt_getPhyDrvSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_phydrv_settings_t * pParam, req_data_phydrv_settings_t * pData, 
    u32 u32DataSize);
u32 i2clnt_setPhyDrvSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_phydrv_settings_t * pParam, req_data_phydrv_settings_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getLogDrvSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_logdrv_settings_t * pParam, req_data_logdrv_settings_t * pData, u32 u32DataSize);
u32 i2clnt_setLogDrvSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_logdrv_settings_t * pParam, req_data_logdrv_settings_t * pData, u32 u32DataSize);
    
u32 i2clnt_getDiskArrayConfig(i2ipc_client_t * pic, u32 u32SessionId, req_param_array_cfg_t * pParam, req_data_array_cfg_t * pData, u32 u32DataSize);
u32 i2clnt_getDiskArrayInfo(i2ipc_client_t * pic, u32 u32SessionId, req_param_array_info_t * pParam, req_data_array_info_t * pData, u32 u32DataSize);
u32 i2clnt_addDiskArray(i2ipc_client_t * pic, u32 u32SessionId, req_param_array_add_t * pParam);
u32 i2clnt_delDiskArray(i2ipc_client_t * pic, u32 u32SessionId, req_param_array_del_t * pParam, u32 u32ParamSize);
u32 i2clnt_delAllDiskArray(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_addLogDrv(i2ipc_client_t * pic, u32 u32SessionId, req_param_logdrv_add_t * pParam, u32 u32ParamSize);
u32 i2clnt_delLogDrv(i2ipc_client_t * pic, u32 u32SessionId, req_param_logdrv_del_t * pParam, u32 u32ParamSize);
u32 i2clnt_delLogDrvInArray(i2ipc_client_t * pic, u32 u32SessionId, req_param_logdrv_del_t * pParam, u32 u32ParamSize);
/*u32 i2clnt_delAllLdOfDiskArray(i2ipc_client_t * pic, u32 u32SessionId);*/
u32 i2clnt_getDiskArraySettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_array_settings_t * pParam, 
    req_data_array_settings_t * pData, u32 u32DataSize);
u32 i2clnt_setDiskArraySettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_array_settings_t * pParam, 
    req_data_array_settings_t * pData, u32 u32DataSize);

u32 i2clnt_setSpareSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_spare_del_t * pDelParam, req_param_spare_add_t * pAddParam); 
u32 i2clnt_getSpareInfo(i2ipc_client_t * pic, u32 u32SessionId, req_param_spare_info_t * pParam, req_data_spare_info_t * pData, u32 u32DataSize);
u32 i2clnt_getAllSpareInfo(i2ipc_client_t * pic, u32 u32SessionId, req_data_spare_info_t * pData, u32 u32DataSize);
u32 i2clnt_addSpare(i2ipc_client_t * pic, u32 u32SessionId, req_param_spare_add_t * pParam, u32 u32ParamSize);
u32 i2clnt_delSpare(i2ipc_client_t * pic, u32 u32SessionId, req_param_spare_del_t * pParam, u32 u32ParamSize);
u32 i2clnt_delAllSpare(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_setSpareDriveSettings(i2ipc_client_t * pic, u32 u32SessionId, req_param_sparecfg_t * prps);
u32 i2clnt_migrateDiskArray(i2ipc_client_t * pic, u32 u32SessionId, req_param_migrate_t * pParam);
u32 i2clnt_migrateGetProgress(i2ipc_client_t * pic, u32 u32SessionId, req_param_device_ids_t * pParam, req_data_migrate_progress_t * pData, u32 u32DataSize);
u32 i2clnt_delSpare(i2ipc_client_t * pic, u32 u32SessionId, req_param_spare_del_t * pParam, u32 u32ParamSize);
/* background activities */
u32 i2clnt_getMediaPatrolProgress(i2ipc_client_t * pic, u32 u32SessionId, req_data_mpprogress_t * pData, u32 u32DataSize);
u32 i2clnt_startMediaPatrol(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_stopMediaPatrol(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_pauseMediaPatrol(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_resumeMediaPatrol(i2ipc_client_t * pic, u32 u32SessionId);

u32 i2clnt_getRebuildProgress(i2ipc_client_t * pic, u32 u32Sessionid, 
    req_param_rbprogress_t * pParam, req_data_rbprogress_t * pData, u32 u32DataSize);
u32 i2clnt_startRebuild(i2ipc_client_t * pic, u32 u32Sessionid, 
    req_param_rbctrl_t * pParam);
u32 i2clnt_stopRebuild(i2ipc_client_t * pic, u32 u32Sessionid, 
    req_param_rbctrl_t * pParam);
u32 i2clnt_pauseRebuild(i2ipc_client_t * pic, u32 u32Sessionid, 
    req_param_rbctrl_t * pParam);
u32 i2clnt_resumeRebuild(i2ipc_client_t * pic, u32 u32Sessionid, 
    req_param_rbctrl_t * pParam);
    
u32 i2clnt_getLogDrvInitProgress(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_init_t * pParam, req_data_ldiprogress_t * pData, u32 u32DataSize);
u32 i2clnt_startLogDrvInit(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_init_t * pParam, u32 u32ParamSize);
u32 i2clnt_stopLogDrvInit(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_init_t * pParam);
u32 i2clnt_pauseLogDrvInit(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_init_t * pParam);
u32 i2clnt_resumeLogDrvInit(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_init_t * pParam);

u32 i2clnt_getLogDrvSynchProgress(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_synch_t * pParam, req_data_synchprogress_t * pData, u32 u32DataSize);
u32 i2clnt_stopLogDrvSynch(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ld_synch_t * pParam);

u32 i2clnt_getRedundancyCheckProgress(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_rc_t * pParam, req_data_rcprogress_t * pData, u32 u32DataSize);
u32 i2clnt_startRedundancyCheck(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_rc_t * pParam);
u32 i2clnt_stopRedundancyCheck(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_rc_t * pParam);
u32 i2clnt_pauseRedundancyCheck(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_rc_t * pParam);
u32 i2clnt_resumeRedundancyCheck(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_rc_t * pParam);
    
/* events */
u32 i2clnt_getEventInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_event_info_t * pParam, req_data_event_info_t * pData, 
    u32 u32DataSize);
u32 i2clnt_setEventInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_event_info_t * pParam, req_data_event_info_t * pData, 
    u32 u32DataSize);
u32 i2clnt_resetEventInfo(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_getEvents(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
u32 i2clnt_getFirstEvents(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
u32 i2clnt_getLastEvents(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
u32 i2clnt_getEventStats(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_event_stats_t * pData);
u32 i2clnt_getEventLocationStats(i2ipc_client_t * pic, u32 u32SessionId,
    u8 u8EventLocation, req_data_event_location_stats_t * pData);
u32 i2clnt_clearEventLog(i2ipc_client_t * pic, u32 u32SessionId,
    u8 u8EventLocation);

/* iSCSI info and settings */

u32 i2clnt_getiSCSIInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_iscsi_info_t * pParam, req_data_iscsi_info_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getiSCSISettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_iscsi_setting_t * pParam, req_data_iscsi_setting_t * pData, 
    u32 u32DataSize);
u32 i2clnt_setiSCSISettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_iscsi_setting_t * pParam, req_data_iscsi_setting_t * pData, 
    u32 u32DataSize);
u32 i2clnt_iscsiGetSLPInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_slp_info_t * pParam, req_data_slp_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiGetSLPSettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_slp_info_t * pParam, req_data_slp_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiSetSLPSettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_slp_info_t * pParam, req_data_slp_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiGetISNSInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_isns_info_t * pParam, req_data_isns_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiGetISNSSettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_isns_info_t * pParam, req_data_isns_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiSetISNSSettings(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_isns_info_t * pParam, req_data_isns_info_t * pData,
    u32 u32DataSize);
u32 i2clnt_iscsiGetChapRecord(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_chap_config_t * pParam, req_data_chap_config_t * pData, 
    u32 u32DataSize);
u32 i2clnt_iscsiSetChapRecord(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_chap_config_t * pParam, req_data_chap_config_t * pData, 
    u32 u32DataSize);
u32 i2clnt_iscsiAddChapRecord(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_chap_config_t * pParam, req_data_chap_config_t * pData, 
    u32 u32DataSize);
u32 i2clnt_iscsiDelChapRecord(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_chap_config_t * pParam);
u32 i2clnt_iscsiPing(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_iscsi_ping_t * pParam, req_data_iscsi_ping_t * pData,
    u32 u32DataSize);
u32 i2clnt_getNodeList(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_node_list_t * pParam, req_data_node_list_t * pData,
    u32 u32DataSize);

/******************************************************************************
 * Function:        i2clnt_getInitiatorList
 *
 * Description:    to get the initiator list 
 *
 *****************************************************************************/
u32 i2clnt_getInitiatorList(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_initiator_t * pParam, req_data_initiator_t * pData,
    u32 u32DataSize);
/******************************************************************************
 * Function:        i2clnt_addInitiatorList
 *
 * Description:    to add an initiator to the list
 *
 *****************************************************************************/
u32 i2clnt_addInitiator(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_initiator_t * pData, u32 u32DataSize);
/******************************************************************************
 * Function:        i2clnt_delInitiatorList
 *
 * Description:    to delete an initiator from the list
 *
 *****************************************************************************/
u32 i2clnt_delInitiator(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_initiator_t * pParam);
/******************************************************************************
 * Function:        i2clnt_getLMMEntry
 *
 * Description:    to get the LMM table
 *
 *****************************************************************************/
u32 i2clnt_getLMMTable(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_lmm_t * pParam, req_data_lmm_t * pData,
    u32 u32DataSize);
/******************************************************************************
 * Function:        i2clnt_addLMMEntry
 *
 * Description:    to add an LMM Entry in LMM Table
 *
 *****************************************************************************/
u32 i2clnt_addLMMEntry(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_lmm_t * pData, u32 u32DataSize);
/******************************************************************************
 * Function:        i2clnt_setLMMEntry
 *
 * Description:    to set an LMM Entry in LMM Table
 *
 *****************************************************************************/
u32 i2clnt_setLMMEntry(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_lmm_t * pData, u32 u32DataSize);
/******************************************************************************
 * Function:        i2clnt_delLMMEntry
 *
 * Description:    to delete an LMM Entry from LMM Table
 *
 *****************************************************************************/
u32 i2clnt_delLMMEntry(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_lmm_t * pParam);

#ifndef IN_BAND
/* event subscription */

u32 i2clnt_subscribeEventNotification(i2ipc_client_t * pic, 
    req_param_event_subscribe_t * pParam);
u32 i2clnt_unsubscribeEventNotification(i2ipc_client_t * pic);
u32 i2clnt_waitForSubscribedEvent(i2ipc_client_t * pic, u32 u32Timeout);
#endif
    
/*
u32 i2clnt_lockController(i2ipc_client_t * pic, u32 u32SessionId, req_param_lock_ctrl_t * pParam, req_data_lock_ctrl_t * pData);
u32 i2clnt_unlockController(i2ipc_client_t * pic, u32 u32SessionId, req_param_unlock_ctrl_t * pParam);
*/

/* auto config */
u32 i2clnt_arrayConfigParam(i2ipc_client_t * pic, u32 u32SessionId, 
    array_config_param_t * pacp);
u32 i2clnt_configArray(i2ipc_client_t * pic, u32 u32SessionId, 
    u8 * pu8Buffer);
/******************************************************************************
* Function Name: i2clnt_login                                       
* Description: login to I2
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] pParam, the login param
*       [out] pData, the returned info of login - the sesison id and the user's
*           previlige level.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient should be called before this func is called.
*******************************************************************************/
u32 i2clnt_login(i2ipc_client_t * pic, req_param_session_login_t * pParam, req_data_session_login_t * pData);

/******************************************************************************
* Function Name: i2clnt_logout                                       
* Description: logout from I2
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient should be called before this func is called.
*******************************************************************************/
u32 i2clnt_logout(i2ipc_client_t * pic, u32 u32SessionId);

/* bga scheduler */
u32 i2clnt_getBGASchedule(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_bga_schedule_t * pParam, req_data_bga_schedule_t * pData, u32 u32DataSize);
u32 i2clnt_addBGASchedule(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_bga_schedule_t * pData, u32 u32DataSize);
u32 i2clnt_deleteBGASchedule(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_bga_schedule_t * pData, u32 u32DataSize);
u32 i2clnt_modifyBGASchedule(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_bga_schedule_t * pData, u32 u32DataSize);

#ifndef IN_BAND
/* flash upload */
u32 i2clnt_initializeFlashProcess(i2ipc_client_t * pic, u32 u32SessionId); 
u32 i2clnt_finalizeFlashProcess(i2ipc_client_t * pic, u32 u32SessionId); 
u32 i2clnt_transferFlashImage(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_flash_t * pParam); 
u32 i2clnt_verifyFlashImage(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_flash_t * pParam); 
u32 i2clnt_getFlashImageHeader(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_flash_t * pParam, void * pHeader, u32 u32DataSize); 
u32 i2clnt_flashImage(i2ipc_client_t * pic, u32 u32SessionId); 
u32 i2clnt_getFlashProgress(i2ipc_client_t * pic, u32 u32SessionId,
    flash_progress_t * pData, u32 u32DataSize); 

/*****************************************************************************
 * Function: i2clnt_setsmbsendConfig
 * Description: set Smbsend configurations
 ****************************************************************************/
u32 i2clnt_setSmbsendConfig(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_Smbsend_config_t * pData, u32 u32DataSize);
/*****************************************************************************
 * Function: i2clnt_getsmbsendConfig
 * Description: get Smbsend configurations
 ****************************************************************************/
u32 i2clnt_getSmbsendConfig(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_Smbsend_config_t * pData, u32 u32DataSize);

/*****************************************************************************
 * Function: i2clnt_setSnmpConfig
 * Description: set SNMP configurations
 ****************************************************************************/
u32 i2clnt_setSnmpConfig(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_snmp_config_t * pData, u32 u32DataSize);
/*****************************************************************************
 * Function: i2clnt_getSnmpConfig
 * Description: get SNMP configurations
 ****************************************************************************/
u32 i2clnt_getSnmpConfig(i2ipc_client_t * pic, u32 u32SessionId, 
    req_data_snmp_config_t * pData, u32 u32DataSize);
    
u32 i2clnt_getWebserverConfig(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_webserver_config_t * pData, u32 u32DataSize);
u32 i2clnt_setWebserverConfig(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_webserver_config_t * pData, u32 u32DataSize);    
u32 i2clnt_getWebserverCurrentConfig(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_webserver_config_t * pData, u32 u32DataSize);  
#endif /* ifndef IN_BAND */

/* Enclosure and FRU */
u32 i2clnt_getEnclosureInfo(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_encl_info_t *pParam, req_data_encl_info_t * prdei, 
    u8 * pData, u32 u32DataSize);
#if 0 /* move to controller */
u32 i2clnt_getEnclosureSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_encl_settings_t *pParam, req_data_encl_settings_t * pData, 
    u32 u32DataSize);
u32 i2clnt_setEnclosureSettings(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_encl_settings_t *pParam, req_data_encl_settings_t * pData, 
    u32 u32DataSize);
#endif
u32 i2clnt_getBatteryInfo(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_bat_info_t *pParam, req_data_bat_info_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getFRUInfo(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_fru_info_t *pParam, req_data_fru_info_t * pData, 
    u32 u32DataSize);
u32 i2clnt_startBatteryReconditioning(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_bat_info_t *pParam);
u32 i2clnt_locateArrayInEnclosure(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_locate_info_t *pParam);
u32 i2clnt_locateLogDrvInEnclosure(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_locate_info_t *pParam);
u32 i2clnt_locatePhyDrvInEnclosure(i2ipc_client_t * pic, u32 u32SessionId, 
    req_param_locate_info_t *pParam);

/* buzzer */
u32 i2clnt_turnOnBuzzer(i2ipc_client_t * pic, u32 u32SessionId, u16 u16CtrlId);
u32 i2clnt_turnOffBuzzer(i2ipc_client_t * pic, u32 u32SessionId, u16 u16CtrlId);
u32 i2clnt_getBuzzerStatus(i2ipc_client_t * pic, u32 u32SessionId,
    u16 u16CtrlId, u8 * pData, u32 u32DataSize);

/* user management */
u32 i2clnt_getAllUser(i2ipc_client_t * pic, u32 u32SessionId,
		      req_data_user_info_t * pData, u32 u32DataSize);
u32 i2clnt_getUser(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_user_name_t * pParam, req_data_user_info_t * pData, u32 u32DataSize);
u32 i2clnt_addUser(i2ipc_client_t * pic, u32 u32SessionId,
    user_info_t * pData, u32 u32DataSize);
u32 i2clnt_modUser(i2ipc_client_t * pic, u32 u32SessionId,
    user_info_t * pData, u32 u32DataSize);
u32 i2clnt_deleteUser(i2ipc_client_t * pic, u32 u32SessionId,
    u8 * pData, u32 u32DataSize);
u32 i2clnt_setPwd(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_pwd_t * pData, u32 u32DataSize);
  
/* lock management */
/******************************************************************************
* Function Name: i2clnt_lock                                       
* Description: lock the subsystem for the specified time. 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] u32LockTime, the amount of time to lock the subsystem, in seconds
*       [out] pu64ExpirationTime, if locked successfully, it returns the lock
*           expiration time here. It is the number of seconds since 0:0:0 Jan 1,
*           1970.
* Return: the completion error code. 
*       PIERR_NO_ERROR      - no error
*       PIERR_SUBSYS_LOCKED - the subsystem has been locked already
*       others
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_lock(i2ipc_client_t * pic, u32 u32SessionId,
    u32 u32LockTime, u64 * pu64ExpirationTime);  

/******************************************************************************
* Function Name: i2clnt_lockExtend                                       
* Description: extend the lock to the subsystem for the specified time.
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] u32ExtentionTime, the amount of time to extend the lock, in seconds
*       [out] pu64ExpirationTime, if extended successfully, it returns the lock
*           expiration time here. It is the number of seconds since 0:0:0 Jan 1,
*           1970.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_lockExtend(i2ipc_client_t * pic, u32 u32SessionId,
    u32 u32ExtentionTime, u64 * pu64ExpirationTime);  

/******************************************************************************
* Function Name: i2clnt_unlock                                       
* Description: unlock the subsystem. 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] bForce, whether to force unlock the subsystem. Only the super user
*           can force to unlock a subsystem which is locked by another user or
*           another session.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_unlock(i2ipc_client_t * pic, u32 u32SessionId, boolean_t bForce);

/******************************************************************************
* Function Name: i2clnt_checkLock                                       
* Description: check whether the current session owns the lock. 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [out] pbIsOwner, the check result
*       [out] pu64ExpirationTime, if pbIsOwner is TRUE, it is set to the lock
*           expiration time here. If pbIsOwner is FALSE, it is set to 0, if the 
*           the session did not lock the subsystem; it is set to the original
*           expiration time, if the lock has expired. The expiration time is in 
*           number of seconds since 0:0:0 Jan 1, 1970.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_checkLock(i2ipc_client_t * pic, u32 u32SessionId, 
    boolean_t * pbIsOwner, u64 * pu64ExpirationTime);

/******************************************************************************
 * Function:        i2clnt_getErrorTable
 *
 * Description:    get error table
 *
*****************************************************************************/
u32 i2clnt_getErrorTable(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_error_table_t *pParam, req_data_error_table_t *pData,
    u32 u32DataSize) ;
/******************************************************************************
* Function Name: i2clnt_getAllDaemonsInfo                                       
* Description: get all user's visible daemons' running status and startup type 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [out] prsdiDaemonsInfo, the list of daemon info
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_getAllDaemonsInfo(i2ipc_client_t * pic, u32 u32SessionId,
        req_swmgt_daemon_info_t *prsdiDaemonsInfo);
/******************************************************************************
* Function Name: i2clnt_setDaemonStartupType                                       
* Description: set a daemon's startup type 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pu8DaemonName, which daemon to set
*       [in] u8DaemonStartupType, startup type to set
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_setDaemonStartupType(i2ipc_client_t * pic, u32 u32SessionId,
        u8 * pu8DaemonName, u8 u8DaemonStartupType);
/******************************************************************************
* Function Name: i2clnt_startStopDaemon                                       
* Description: start or stop a daemon 
* Parameters:    
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pu8DaemonName, which daemon to act on
*       [in] u8DaemonStatus, action of start or stop
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before 
*       this func is called.
*******************************************************************************/
u32 i2clnt_startStopDaemon(i2ipc_client_t * pic, u32 u32SessionId,
        u8 * pu8DaemonName, u8 u8DaemonStatus);
/******************************************************************************
* Function Name: i2clnt_getEmailSetting
* Description: get email setting
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [out] pData, email setting
*       [in] u32DataSize, the size of the data buffer if applicable
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_getEmailSetting(i2ipc_client_t * pic, u32 u32SessionId,
    req_email_setting_t * pData, u32 u32DataSize);
/******************************************************************************
* Function Name: i2clnt_setEmailSetting
* Description: set email setting
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pData, email setting
*       [in] u32DataSize, the size of the data buffer if applicable
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/    
u32 i2clnt_setEmailSetting(i2ipc_client_t * pic, u32 u32SessionId,
    req_email_setting_t * pData, u32 u32DataSize);
/******************************************************************************
* Function Name: i2clnt_getUserPreference
* Description: get user preference such as event filters
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pParam, contains user name
*       [out] pData, contains user preference
*       [in] u32DataSize, the size of the data buffer if applicable
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/    
u32 i2clnt_getUserPreference(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_user_name_t * pParam, req_user_preference_t * pData, u32 u32DataSize);
/******************************************************************************
* Function Name: i2clnt_setUserPreference
* Description: set user preference such as event filters
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pData, contains user preference
*       [in] u32DataSize, the size of the data buffer if applicable
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/    
u32 i2clnt_setUserPreference(i2ipc_client_t * pic, u32 u32SessionId,
    req_user_preference_t * pData, u32 u32DataSize);
/******************************************************************************
* Function Name: i2clnt_testEmail
* Description: send a test email to a user
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pData, contains user name
*       [in] u32DataSize, the size of the data buffer if applicable
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_testEmail(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_user_name_t * pData, u32 u32DataSize);

/******************************************************************************
* Function Name: i2clnt_export
* Description: export file
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pData, contains export parameters
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_export(i2ipc_client_t * pic, u32 u32SessionId,
    req_export_t * pData);
/******************************************************************************
* Function Name: i2clnt_importTransfer
* Description: transfer file into islavista
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [in] pData, contains import parameters
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_importTransfer(i2ipc_client_t * pic, u32 u32SessionId,
    req_import_param_t * pParam);
/******************************************************************************
* Function Name: i2clnt_importGetInfo
* Description: check again imported file
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
*       [out] pData, contains parsing info regards the import file
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_importGetInfo(i2ipc_client_t * pic, u32 u32SessionId,
    req_import_data_t * pData);
/******************************************************************************
* Function Name: i2clnt_importAbort
* Description: abort import, delete temp file
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_importAbort(i2ipc_client_t * pic, u32 u32SessionId);
/******************************************************************************
* Function Name: i2clnt_importApply
* Description: last step of import, apply
* Parameters:
*       [in] pic, the I2 IPC Client object
*       [in] u32SessionId, the session id
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: i2clnt_createI2IPCClient and i2clnt_login should be called before
*       this func is called.
*******************************************************************************/
u32 i2clnt_importApply(i2ipc_client_t * pic, u32 u32SessionId);


/* statistics */
u32 i2clnt_resetStats(i2ipc_client_t * pic, u32 u32SessionId);
u32 i2clnt_getStatsSubsystem(i2ipc_client_t * pic, u32 u32SessionId,
    req_data_subsys_stats_t * pData, u32 u32DataSize);
u32 i2clnt_getStatsEnclosure(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_encl_info_t * pParam, req_data_encl_stats_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getStatsController(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_ctrl_info_t * pParam, req_data_ctrl_stats_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getStatsPhyDrv(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_phydrv_info_t * pParam, req_data_phydrv_stats_t * pData, 
    u32 u32DataSize);
u32 i2clnt_getStatsLogDrv(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_logdrv_info_t * pParam, req_data_logdrv_stats_t * pData, 
    u32 u32DataSize);

u32 i2clnt_getDateAndTime(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_device_ids_t * pParam, req_data_time_t * pData, 
    u32 u32DataSize);
u32 i2clnt_setDateAndTime(i2ipc_client_t * pic, u32 u32SessionId,
    req_param_device_ids_t * pParam, req_data_time_t * pData, 
    u32 u32DataSize);

#endif /*__PI_I2CLIENT_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: i2client.h,v $
 * Revision 1.58  2008/06/23 07:42:20  jackyl
 * add bonjour support
 *
 * Revision 1.57  2006/03/14 03:42:48  JudithLi
 * add netsend APIs
 *
 * Revision 1.56  2004/03/18 01:43:00  debinc
 * Add get/set web config functions
 *
 * Revision 1.55  2004/03/05 22:20:12  zhengj
 * added support for system time and stats
 *
 * Revision 1.54  2004/03/03 21:42:02  weny
 * add i2clnt_rescan support manual rescan SCSI bus for Windows in-band
 *
 * Revision 1.53  2004/02/10 23:35:17  zhengj
 * flash support modification
 *
 * Revision 1.52  2004/01/30 03:55:38  zhengj
 * lmm support
 *
 * Revision 1.51  2004/01/26 20:45:34  weny
 * buzz cmd
 *
 * Revision 1.50  2004/01/20 21:17:59  zhengj
 * added i2clnt_delLogDrvInArray
 *
 * Revision 1.49  2004/01/16 00:00:46  zhengj
 * added transitionPD and its status
 *
 * Revision 1.48  2004/01/08 22:45:14  zhengj
 * added i2clnt_getNodeList
 *
 * Revision 1.47  2004/01/08 19:04:07  zhengj
 * iSNS support
 *
 * Revision 1.46  2003/12/18 03:35:21  zhengj
 * migration support
 *
 * Revision 1.45  2003/12/18 01:31:48  debinc
 * import export APIs
 *
 * Revision 1.44  2003/12/04 02:08:11  debinc
 * correct check in error on setUserPreference
 *
 * Revision 1.43  2003/12/03 22:24:11  debinc
 * support event filters
 *
 * Revision 1.42  2003/11/21 01:47:21  zhengj
 * add i2clnt_getDiskArrayInfo
 *
 * Revision 1.41  2003/11/05 20:57:08  debinc
 * Add swmgt to CLI, I2, I2client
 *
 * Revision 1.40  2003/11/04 23:38:40  zhengj
 * some changes for device numbering and more
 *
 * Revision 1.39  2003/10/02 01:53:37  zhengj
 * SLP get/set Settings
 *
 * Revision 1.38  2003/09/25 03:15:50  debinc
 * Add getErrTable function header
 *
 * Revision 1.37  2003/09/25 02:51:28  weny
 * Event Log change
 *
 * Revision 1.36  2003/09/25 00:14:10  zhengj
 * flash support
 *
 * Revision 1.35  2003/09/24 23:11:28  weny
 * support sw check lock
 *
 * Revision 1.34  2003/09/23 23:14:13  debinc
 * Add restart SNMP API
 *
 * Revision 1.33  2003/09/19 01:42:48  weny
 * add clear event log
 *
 * Revision 1.32  2003/09/18 19:12:32  zhengj
 * subsys ctrl PD settings
 *
 * Revision 1.31  2003/09/16 03:56:28  zhengj
 * fix for iscsi settings
 *
 * Revision 1.30  2003/09/13 00:34:38  weny
 * config lock support
 *
 * Revision 1.29  2003/09/11 03:48:23  zhengj
 * added slp
 *
 * Revision 1.28  2003/09/10 22:18:08  zhengj
 * initial check-in for iscsi
 *
 * Revision 1.27  2003/09/10 19:20:44  weny
 * Linux In-Band CLI porting
 *
 * Revision 1.26  2003/09/08 19:15:57  wenyis
 * add i2clnt_setSpareDriveSettings()
 *
 * Revision 1.25  2003/09/04 22:53:15  weny
 * disable TFTP flash uploading for in-band
 *
 * Revision 1.24  2003/09/04 01:13:04  zhengj
 * added support for flash
 *
 * Revision 1.23  2003/08/27 01:13:50  zhengj
 * missing drive support and bug fix
 *
 * Revision 1.22  2003/08/22 01:25:12  zhengj
 * added support for enclosure mgmt and others
 *
 * Revision 1.21  2003/08/21 02:51:01  debinc
 * Add user management support
 *
 * Revision 1.20  2003/08/12 01:35:54  weny
 * changes for In-band on Windows
 *
 * Revision 1.19  2003/08/08 22:41:41  zhengj
 * added support for array setting and info and others ..
 *
 * Revision 1.17  2003/07/31 22:17:45  zhengj
 * added support for snmp config settings
 *
 * Revision 1.16  2003/06/28 05:47:44  weny
 * add bga scheduler support
 *
 * Revision 1.15  2003/06/28 03:26:56  weny
 * iscsi node info support
 *
 * Revision 1.14  2003/06/27 23:48:35  weny
 * add ld settings and rc support
 *
 * Revision 1.13  2003/06/12 02:34:22  weny
 * 1. event request data structure change
 * 2. get events and event notification support
 *
 * Revision 1.12  2003/06/07 01:29:54  weny
 * add full support to ldi and lds, some for rc.
 *
 * Revision 1.11  2003/06/04 02:28:21  weny
 * pool to disk array
 *
 * Revision 1.10  2003/06/03 20:58:15  weny
 * add support for add ld to disk array
 *
 * Revision 1.9  2003/05/17 03:03:45  weny
 * Remove the old Severity Set routines.
 *
 * Revision 1.8  2003/04/15 17:49:59  weny
 * adding ldi and lds progress
 *
 * Revision 1.7  2003/04/14 19:36:37  weny
 * add support to event & rb
 *
 * Revision 1.6  2003/04/08 23:27:54  weny
 * 1. changes in param of add storpool and addld storpool
 * 2. media patrol support
 *
 * Revision 1.5  2003/04/02 00:11:02  weny
 * added some routines about storpool and spare configuration
 *
 * Revision 1.4  2003/03/27 20:15:19  weny
 * add support to spare and storpool
 *
 * Revision 1.3  2003/03/22 00:53:48  weny
 * add data decode functions to i2client
 *
 * Revision 1.2  2003/03/14 20:01:35  weny
 * add psudo support
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 ******************************************************************************/
