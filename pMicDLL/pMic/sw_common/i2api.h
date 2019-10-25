/*******************************************************************************
 * Filename    : i2api.h
 * Description : I2 API header file
 *               It declares all of I2 APIs
 * Created on  : 02/05/2004
 * CVS Version : $Id: i2api.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * Copyright (C) 2004-2004 Promise Technology Inc.
 * All Rights Reserved
 ******************************************************************************/

#ifndef I2_API_H
#define I2_API_H

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#undef I2API
#undef I2CALL
#ifdef WINDOWS
    #include "windows.h"
	#if defined(PROMISE_I2API_DLL)
		#define I2API  __declspec(dllexport)
		#define I2CALL
	#else
		//#define PROMISEAPI  __declspec(dllimport)
		#define I2API
		#define I2CALL __cdecl
	#endif
#else
	#define I2API
	#define I2CALL
#endif

#include "i2types.h"

/* --- constant definitions ------------------------------------------------ */
#define I2API_SIGNATURE 0xbaba0000

#define I2API_VERSION   (I2API_SIGNATURE | 0x00000001)

/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

I2API u32 I2CALL i2_initialize(i2api_param_t * pParam);
I2API u32 I2CALL i2_finalize();

I2API u32 I2CALL i2_discover(boolean_t bRescan);
I2API u32 I2CALL i2_discoverByProductAndCommPath(u16 u16ProductId, u8 u8CommPath);
I2API u32 I2CALL i2_getNumberOfSubsystem(u32 * pu32NumOfSubsys);
I2API u32 I2CALL i2_getNumberOfHBA(u32 * pu32NumOfHBA);
#define MIN_DISCOVER_PATH_SIZE (sizeof(DataBufferHeader_t) + sizeof(device_discover_path_t))
I2API u32 I2CALL i2_getDiscoverPath(device_id_t di, u8 * pu8Data, u32 u32DataSize);

I2API u32 I2CALL i2_getSubsystemInfo(device_id_t di, session_id_t si, req_data_subsys_info_t * pData);
I2API u32 I2CALL i2_getSubsystemSettings(device_id_t di, session_id_t si, req_data_subsys_settings_t * pData);
I2API u32 I2CALL i2_setSubsystemSettings(device_id_t di, session_id_t si,  req_data_subsys_settings_t * pData);
I2API u32 I2CALL i2_setCliqueSettings(device_id_t di, session_id_t si, req_data_clique_setting_t * pData);
I2API u32 I2CALL i2_getCliqueSettings(device_id_t di, session_id_t si, req_data_clique_setting_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_getCliqueInfo(device_id_t di, session_id_t si, req_data_clique_info_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_enterMaintenanceMode(device_id_t di, session_id_t si, u8 u8CtrlId);
I2API u32 I2CALL i2_exitMaintenanceMode(device_id_t di, session_id_t si, u8 u8CtrlId);
            
I2API u32 I2CALL i2_getControllerInfo(device_id_t di, session_id_t si, req_param_ctrl_info_t * pParam, req_data_ctrl_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getControllerSettings(device_id_t di, session_id_t si, req_param_ctrl_settings_t * pParam, req_data_ctrl_settings_t * pData,     u32 u32DataSize);
I2API u32 I2CALL i2_setControllerSettings(device_id_t di, session_id_t si, req_param_ctrl_settings_t * pParam, req_data_ctrl_settings_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getPhyDrvInfo(device_id_t di, session_id_t si, req_param_phydrv_info_t * pParam, req_data_phydrv_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getPhyDrvSettings(device_id_t di, session_id_t si, req_param_phydrv_settings_t * pParam, req_data_phydrv_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setPhyDrvSettings(device_id_t di, session_id_t si, req_param_phydrv_settings_t * pParam, req_data_phydrv_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_locatePhyDrv(device_id_t di, session_id_t si, u16 u16PhyDrvId, u32 u32Duration);
I2API u32 I2CALL i2_stopLocatePhyDrv(device_id_t di, session_id_t si, u16 u16PhyDrvId);
I2API u32 I2CALL i2_getPhyDrvLocateStatus(device_id_t di, session_id_t si, u16 u16PhyDrvId, u8* pu8Status);
I2API u32 I2CALL i2_getMissingPhyDrvInfo(device_id_t di, session_id_t si, req_param_phydrv_info_t * pParam, req_data_phydrv_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getTransitionPhyDrvInfo(device_id_t di, session_id_t si, 
    req_param_array_info_t *pParam, req_data_phydrv_info_t *pData, 
    u32 u32DataSize);

I2API u32 I2CALL i2_getLogDrvInfo(device_id_t di, session_id_t si, req_param_logdrv_info_t * pParam, req_data_logdrv_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getLogDrvSettings(device_id_t di, session_id_t si, req_param_logdrv_settings_t * pParam, req_data_logdrv_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setLogDrvSettings(device_id_t di, session_id_t si, req_param_logdrv_settings_t * pParam, req_data_logdrv_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getErrorTable(device_id_t di, session_id_t si, req_param_error_table_t *pParam, req_data_error_table_t *pData, u32 u32DataSize) ;
I2API u32 I2CALL i2_clearErrorTable(device_id_t di, session_id_t si, req_param_error_table_t *pParam) ;
I2API u32 I2CALL i2_locateLogDrv(device_id_t di, session_id_t si, u16 u16LogDrvId, u32 u32Duration);
I2API u32 I2CALL i2_stopLocateLogDrv(device_id_t di, session_id_t si, u16 u16LogDrvId);

I2API u32 I2CALL i2_getDiskArrayInfo(device_id_t di, session_id_t si, req_param_array_info_t * pParam, req_data_array_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getDiskArraySettings(device_id_t di, session_id_t si, req_param_array_settings_t * pParam, req_data_array_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setDiskArraySettings(device_id_t di, session_id_t si, req_param_array_settings_t * pParam, req_data_array_settings_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getEnclosureSettings(device_id_t di, session_id_t si, req_param_encl_settings_t * pParam, req_data_encl_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setEnclosureSettings(device_id_t di, session_id_t si, req_param_encl_settings_t * pParam, req_data_encl_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_locateDiskArray(device_id_t di, session_id_t si, u16 u16ArrayId);
I2API u32 I2CALL i2_prepareArrayForTransport(device_id_t di, session_id_t si, req_param_array_transport_t * pParam);

I2API u32 I2CALL i2_getDiskArrayConfig(device_id_t di, session_id_t si, req_param_array_cfg_t * pParam, req_data_array_cfg_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addDiskArray(device_id_t di, session_id_t si,  req_param_array_add_t * pParam);
I2API u32 I2CALL i2_delDiskArray(device_id_t di, session_id_t si,  req_param_array_del_t * pParam, u32 u32ParamSize);
I2API u32 I2CALL i2_delAllDiskArray(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_addLogDrv(device_id_t di, session_id_t si,  req_param_logdrv_add_t * pParam, u32 u32ParamSize);
I2API u32 I2CALL i2_delLogDrv(device_id_t di, session_id_t si,  req_param_logdrv_del_t * pParam, u32 u32ParamSize);
I2API u32 I2CALL i2_processIncompleteArray(device_id_t di, session_id_t si, req_param_array_process_t *pParam);
I2API u32 I2CALL i2_migrateDiskArray(device_id_t di, session_id_t si,     req_param_migrate_t * pParam);
I2API u32 I2CALL i2_getMigrationProgress(device_id_t di, session_id_t si, 
    req_param_device_ids_t * pParam, req_data_migrate_progress_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_PauseMigration(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);
I2API u32 I2CALL i2_ResumeMigration(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);
/*I2API u32 I2CALL i2_onlineArrayProcessing(device_id_t di, session_id_t si);*/

I2API u32 I2CALL i2_getSpareInfo(device_id_t di, session_id_t si, req_param_spare_info_t * pParam, req_data_spare_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getAllSpareInfo(device_id_t di, session_id_t si, req_data_spare_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setSpareDriveSettings(device_id_t di, session_id_t si, req_param_sparecfg_t * prps);
I2API u32 I2CALL i2_addSpare(device_id_t di, session_id_t si, req_param_spare_add_t * pParam, u32 u32ParamSize);
I2API u32 I2CALL i2_delSpare(device_id_t di, session_id_t si, req_param_spare_del_t * pParam, u32 u32ParamSize);
/*I2API u32 I2CALL i2_delAllSpare(device_id_t di, session_id_t si);*/

I2API u32 I2CALL i2_startLogDrvSynch(device_id_t di, session_id_t si, req_param_ld_synch_t * pParam);
I2API u32 I2CALL i2_stopLogDrvSynch(device_id_t di, session_id_t si, req_param_ld_synch_t * pParam);
I2API u32 I2CALL i2_pauseLogDrvSynch(device_id_t di, session_id_t si, req_param_ld_synch_t * pParam);
I2API u32 I2CALL i2_resumeLogDrvSynch(device_id_t di, session_id_t si, req_param_ld_synch_t * pParam);
I2API u32 I2CALL i2_getLogDrvSynchProgress(device_id_t di, session_id_t si, req_param_ld_synch_t * pParam, req_data_synchprogress_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getLogDrvInitProgress(device_id_t di, session_id_t si, req_param_ld_init_t * pParam, req_data_ldiprogress_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startLogDrvInit(device_id_t di, session_id_t si, req_param_ld_init_t * pParam, u32 u32ParamSize);
I2API u32 I2CALL i2_stopLogDrvInit(device_id_t di, session_id_t si, req_param_ld_init_t * pParam);
I2API u32 I2CALL i2_pauseLogDrvInit(device_id_t di, session_id_t si, req_param_ld_init_t * pParam);
I2API u32 I2CALL i2_resumeLogDrvInit(device_id_t di, session_id_t si, req_param_ld_init_t * pParam);

I2API u32 I2CALL i2_getRedundancyCheckProgress(device_id_t di, session_id_t si, req_param_rc_t * pParam, req_data_rcprogress_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startRedundancyCheck(device_id_t di, session_id_t si, req_param_rc_t * pParam);
I2API u32 I2CALL i2_stopRedundancyCheck(device_id_t di, session_id_t si, req_param_rc_t * pParam);
I2API u32 I2CALL i2_pauseRedundancyCheck(device_id_t di, session_id_t si, req_param_rc_t * pParam);
I2API u32 I2CALL i2_resumeRedundancyCheck(device_id_t di, session_id_t si, req_param_rc_t * pParam);

I2API u32 I2CALL i2_getRebuildProgress(device_id_t di, session_id_t si, req_param_rbprogress_t * pParam, req_data_rbprogress_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startRebuild(device_id_t di, session_id_t si, req_param_rbctrl_t * pParam);
I2API u32 I2CALL i2_stopRebuild(device_id_t di, session_id_t si, req_param_rbctrl_t * pParam);
I2API u32 I2CALL i2_pauseRebuild(device_id_t di, session_id_t si, req_param_rbctrl_t * pParam);
I2API u32 I2CALL i2_resumeRebuild(device_id_t di, session_id_t si, req_param_rbctrl_t * pParam);

I2API u32 I2CALL i2_getMediaPatrolProgress(device_id_t di, session_id_t si, req_data_mpprogress_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startMediaPatrol(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_stopMediaPatrol(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_pauseMediaPatrol(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_resumeMediaPatrol(device_id_t di, session_id_t si);

I2API u32 I2CALL i2_getHBAMediaPatrolProgress(device_id_t di, session_id_t si, req_param_device_ids_t * pParam, req_data_hba_mpprogress_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startHBAMediaPatrol(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);
I2API u32 I2CALL i2_stopHBAMediaPatrol(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);
I2API u32 I2CALL i2_pauseHBAMediaPatrol(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);
I2API u32 I2CALL i2_resumeHBAMediaPatrol(device_id_t di, session_id_t si, req_param_device_ids_t * pParam);

I2API u32 I2CALL i2_getSpareCheckProgress(device_id_t di, session_id_t si, 
    req_param_sparechk_t * pParam, req_data_sparechk_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_startSpareCheck(device_id_t di, session_id_t si, 
    req_param_sparechk_t * pParam);

/* TBD - transitioning and mirroring */

I2API u32 I2CALL i2_getEnclosureInfo(device_id_t di, session_id_t si, req_param_encl_info_t *pParam, req_data_encl_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getEnclosureStatus(device_id_t di, session_id_t si, req_param_encl_info_t * pParam, u8 * pData, u32 u32DataSize);
I2API u32 I2CALL i2_locateEnclosure(device_id_t di, session_id_t si, u16 u16EnclId);
I2API u32 I2CALL i2_locateFRU(device_id_t di, session_id_t si, req_param_fru_info_t * pParam);
I2API u32 I2CALL i2_getFRUInfo(device_id_t di, session_id_t si, req_param_fru_info_t *pParam, req_data_fru_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setFRUInfo(device_id_t di, session_id_t si, req_param_fru_info_t *pParam, req_data_fru_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getBatteryInfo(device_id_t di, session_id_t si, req_param_bat_info_t *pParam, req_data_bat_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getBatteryCapacity(device_id_t di, session_id_t si, req_param_bat_info_t *pParam, req_data_bat_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_startBatteryReconditioning(device_id_t di, session_id_t si, req_param_bat_info_t *pParam);
I2API u32 I2CALL i2_clearDDFOnPd(device_id_t di, session_id_t si, u16 u16PdId);
I2API u32 I2CALL i2_getBuzzerStatus(device_id_t di, session_id_t si, u8 * pData, u32 u32DataSize);
I2API u32 I2CALL i2_turnOnBuzzer(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_turnOffBuzzer(device_id_t di, session_id_t si);

I2API u32 I2CALL i2_getEvents(device_id_t di, session_id_t si, req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getFirstEvents(device_id_t di, session_id_t si, req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getLastEvents(device_id_t di, session_id_t si, req_param_event_t * pParam, req_data_event_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getEventLocationStats(device_id_t di, session_id_t si, u8 u8EventLocation, req_data_event_stats_t * pData);
I2API u32 I2CALL i2_clearEventLog(device_id_t di, session_id_t si, u8 u8EventLocation);
I2API u32 I2CALL i2_getHostInfo(device_id_t di, session_id_t si, req_data_host_info_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getiSCSImutnodeInfo(device_id_t di, session_id_t si,req_param_iscsi_node_info_t * pParam, req_data_iscsi_node_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addiSCSInode(device_id_t di, session_id_t si,req_param_iscsi_node_info_t * pParam, req_data_iscsi_node_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiDelNodeRecord(device_id_t di, session_id_t si,req_param_iscsi_node_info_t * pParam, req_data_iscsi_node_info_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_getiSCSIPortalInfo(device_id_t di, session_id_t si,req_param_iscsi_portal_info_t * pParam, req_data_iscsi_portal_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getiSCSIInfo(device_id_t di, session_id_t si, req_param_iscsi_info_t * pParam, req_data_iscsi_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getiSCSIFWInfo(device_id_t di, session_id_t si, req_data_iscsi_fw_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setiSCSICleanSession(device_id_t di, session_id_t si, req_data_iscsi_fw_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiDelSession(device_id_t di, session_id_t si, req_param_iscsi_sess_info_t * prpisi);
I2API u32 I2CALL i2_getiSCSISettings(device_id_t di, session_id_t si, req_param_iscsi_setting_t * pParam, req_data_iscsi_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setiSCSISettings(device_id_t di, session_id_t si,req_param_iscsi_setting_t * pParam, req_data_iscsi_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetSLPInfo(device_id_t di, session_id_t si, req_param_device_ids_t * pParam, req_data_slp_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetSLPSettings(device_id_t di, session_id_t si, req_param_device_ids_t * pParam, req_data_slp_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiSetSLPSettings(device_id_t di, session_id_t si, req_param_device_ids_t * pParam, req_data_slp_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetISNSInfo(device_id_t di, session_id_t si, req_param_isns_info_t * pParam, req_data_isns_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetISNSSettings(device_id_t di, session_id_t si, req_param_isns_info_t * pParam, req_data_isns_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiSetISNSSettings(device_id_t di, session_id_t si, req_param_isns_info_t * pParam, req_data_isns_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetLinkAggrRecord(device_id_t di, session_id_t si,req_param_link_aggr_config_t * pParam, req_data_link_aggr_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiSetLinkAggrRecord(device_id_t di, session_id_t si,req_param_link_aggr_config_t * pParam, req_data_link_aggr_config_t* pData,u32 u32DataSize );
I2API u32 I2CALL i2_iscsiDelLinkAggrRecord(device_id_t di, session_id_t si,req_param_link_aggr_config_t * pParam,req_data_link_aggr_config_t* pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiAddLinkAggrRecord(device_id_t di, session_id_t si,req_param_link_aggr_config_t * pParam, req_data_link_aggr_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetLLSVLANRecord(device_id_t di, session_id_t si,req_param_vlan_config_t * pParam, req_data_vlan_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiAddVlanRecord(device_id_t di, session_id_t si,req_param_vlan_config_t * pParam, req_data_vlan_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiSetLLSVLANRecord(device_id_t di, session_id_t si,req_param_vlan_config_t * pParam, req_data_vlan_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiDelVlanRecord(device_id_t di, session_id_t si,req_param_vlan_config_t * pParam, req_data_vlan_config_t * pData,u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetChapRecord(device_id_t di, session_id_t si, req_param_chap_config_t * pParam, req_data_chap_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiSetChapRecord(device_id_t di, session_id_t si, req_param_chap_config_t * pParam, req_data_chap_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiAddChapRecord(device_id_t di, session_id_t si, req_param_chap_config_t * pParam, req_data_chap_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiDelChapRecord(device_id_t di, session_id_t si, req_param_chap_config_t * pParam);
I2API u32 I2CALL i2_iscsiPing(device_id_t di, session_id_t si, req_param_iscsi_ping_t * pParam, req_data_iscsi_ping_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_iscsiGetNodeList(device_id_t di, session_id_t si, req_param_node_list_t * pParam, req_data_node_list_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getInitiatorList(device_id_t di, session_id_t si, req_param_initiator_t * pParam, req_data_initiator_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addInitiator(device_id_t di, session_id_t si, req_data_initiator_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_delInitiator(device_id_t di, session_id_t si, req_param_initiator_t * pParam);
I2API u32 I2CALL i2_getLMMTable(device_id_t di, session_id_t si, req_param_lmm_t * pParam, req_data_lmm_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addLMMEntry(device_id_t di, session_id_t si, req_data_lmm_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setLMMEntry(device_id_t di, session_id_t si, req_data_lmm_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_delLMMEntry(device_id_t di, session_id_t si, req_param_lmm_t * pParam);

I2API u32 I2CALL i2_lock(device_id_t di, session_id_t si, u32 u32LockTime, u64 * pu64ExpirationTime);
I2API u32 I2CALL i2_lockExtend(device_id_t di, session_id_t si, u32 u32ExtentionTime, u64 * pu64ExpirationTime);  
I2API u32 I2CALL i2_unlock(device_id_t di, session_id_t si, boolean_t bForce);
I2API u32 I2CALL i2_checkLock(device_id_t di, session_id_t si, boolean_t * pbIsOwner, u64 * pu64ExpirationTime);

I2API u32 I2CALL i2_initializeFlashProcess(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_finalizeFlashProcess(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_transferFlashImage(device_id_t di, session_id_t si, req_param_flash_t * pParam);
I2API u32 I2CALL i2_flashImage(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_getFlashProgress(device_id_t di, session_id_t si, flash_progress_t * pProgress);
I2API u32 I2CALL i2_getFlashImageHeader(device_id_t di, session_id_t si, req_param_flash_t * pParam, void * pHeader, u32 u32DataSize);
I2API u32 I2CALL i2_verifyFlashImage(device_id_t di, session_id_t si, req_param_flash_t * pParam);
I2API u32 I2CALL i2_getFlashImageVersionInfo(device_id_t di, session_id_t si,
    req_param_flash_image_version_t * pParam, req_data_flash_image_version_t * pData,
    u32 u32DataSize);

I2API u32 I2CALL i2_sendBypassCommand(device_id_t di, session_id_t si, bypass_cmd_t * pbc);

I2API u32 I2CALL i2_getDateAndTime(device_id_t di, session_id_t si,
    req_param_device_ids_t * pParam, req_data_time_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_setDateAndTime(device_id_t di, session_id_t si,
    req_param_device_ids_t * pParam, req_data_time_t * pData, 
    u32 u32DataSize);

I2API u32 I2CALL i2_resetStats(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_getStatsController(device_id_t di, session_id_t si,
    req_param_ctrl_info_t * pParam, req_data_ctrl_stats_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getStatsPhyDrv(device_id_t di, session_id_t si,
    req_param_phydrv_info_t * pParam, req_data_phydrv_stats_t * pData, 
    u32 u32DataSize);

I2API u32 I2CALL i2_getStatsPhyDrvExt(device_id_t di, session_id_t si,
    req_param_phydrv_info_t * pParam, req_data_phydrv_stats_ext_t * pData,
    u32 u32DataSize);

I2API u32 I2CALL i2_getStatsLogDrv(device_id_t di, session_id_t si,
    req_param_logdrv_info_t * pParam, req_data_logdrv_stats_t * pData, 
    u32 u32DataSize);

I2API u32 I2CALL i2_startPerformanceStats(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_getPerformanceStats(device_id_t di, session_id_t si,
	u8 * pu8Data, u32 u32DataSize);
    
I2API u32 I2CALL i2_getBbmDefectList(device_id_t di, session_id_t si,
    req_param_bbm_t * pParam, req_data_bbm_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_clearBbmDefectList(device_id_t di, session_id_t si,
    req_param_bbm_t * pParam);

I2API u32 I2CALL i2_getDriverInfo(device_id_t di, session_id_t si, req_data_driver_info_t *pData);
I2API u32 I2CALL i2_shutdown(device_id_t di, session_id_t si, req_param_shutdown_t *prps);


I2API u32 I2CALL i2_FCGetNodeInfo(device_id_t di, session_id_t si,
    req_data_fc_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetPortInfo(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetPortStatistic(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetPortSFP(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_info_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_FCGetPortInformation(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_port_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetPortLoggedInDevices(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_loggedin_device_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetPortSetting(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_port_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCSetPortSetting(device_id_t di, session_id_t si,
    req_param_fc_port_t * pParam, req_data_fc_port_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_FCGetInitiatorList(device_id_t di, session_id_t si, u8 u8CtrlId,
    req_data_fc_initiator_list_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getSCSIPortInfo(device_id_t di, session_id_t si,
    req_param_scsi_port_t *pParam, req_data_scsi_port_info_t *pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSIPortSettings(device_id_t di, session_id_t si,
    req_param_scsi_port_t * pParam, req_data_scsi_port_settings_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_setSCSIPortSettings(device_id_t di, session_id_t si,
    req_param_scsi_port_t * pParam, req_data_scsi_port_settings_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSIPortStats(device_id_t di, session_id_t si,
    req_param_scsi_port_t *pParam, req_data_scsi_port_stats_t *pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSITargetInfo(device_id_t di, session_id_t si,
    req_param_scsi_target_t * pParam, req_data_scsi_target_info_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSITargetStat(device_id_t di, session_id_t si,
    req_param_scsi_target_t * pParam, req_data_scsi_target_stats_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSITargetSettings(device_id_t di, session_id_t si,
    req_param_scsi_target_t * pParam, req_data_scsi_target_settings_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_setSCSITargetSettings(device_id_t di, session_id_t si,
    req_param_scsi_target_t * pParam, req_data_scsi_target_settings_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_ClearSCSITargetStat(device_id_t di, session_id_t si,
    req_param_scsi_target_t * pParam, req_data_scsi_target_stats_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_getSCSILMMTable(device_id_t di, session_id_t si,
    req_param_scsi_port_t * pParam, req_data_scsi_port_lmm_table_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_setSCSILMMTable(device_id_t di, session_id_t si,
    req_param_scsi_port_t * pParam, req_data_scsi_port_lmm_table_t * pData, 
    u32 u32DataSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSCSI(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);

I2API u32 I2CALL i2_getFeatureBits(device_id_t di, session_id_t si, feature_bits_t * pFb);

I2API u32 I2CALL i2_getFirmwareCapabilities(device_id_t di, session_id_t si, firmware_capabilities_t * pFc);

I2API u32 I2CALL i2_getCurrentCtrlInfo(device_id_t di, session_id_t si, current_controller_info_t * pInfo);
 
I2API u32 I2CALL i2_getSASTopology(device_id_t di, session_id_t si,
    req_param_sas_topology_t *pParam, req_data_sas_topology_t * pData, u32 u32DataSize);
    
I2API u32 I2CALL i2_getSASSMPDiscoverInfo(device_id_t di, session_id_t si,
    req_param_sas_smp_discover_t *pParam, req_data_sas_smp_discover_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getSASPHYErrorLog(device_id_t di, session_id_t si,
    req_param_sas_phy_errorlog_t *pParam, req_data_sas_phy_errorlog_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_SASPHYControl(device_id_t di, session_id_t si, req_param_sas_phy_control_t *pParam);
I2API u32 I2CALL i2_getSASC2CPortPHYErrorLog(device_id_t di, session_id_t si,
    req_data_sas_c2cport_phy_errorlog_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_SASC2CPortPHYControl(device_id_t di, session_id_t si,
    req_param_sas_c2cport_phy_control_t * pParam);

I2API u32 I2CALL i2_clearSASHostPortStatistics(device_id_t di, session_id_t si,
    req_param_sashost_port_info_t * pParam);

I2API u32 I2CALL i2_getSASHostPHYStatistics(device_id_t di, session_id_t si,
    req_param_sashost_port_info_t * pParam, req_data_sashost_phy_stats_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSASHostPortInfo(device_id_t di, session_id_t si,
    req_param_sashost_port_info_t * pParam, req_data_sashost_port_info_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSASHostPortStatistics(device_id_t di, session_id_t si,
    req_param_sashost_port_info_t * pParam, req_data_sashost_port_info_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSASHostPortSetting(device_id_t di, session_id_t si,
    req_param_sashost_port_setting_t * pParam, req_data_sashost_port_setting_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_setSASHostPortSetting(device_id_t di, session_id_t si,
    req_param_sashost_port_setting_t * pParam, req_data_sashost_port_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getSASInitiatorList(device_id_t di, session_id_t si, u8 u8CtrlId,
    req_data_sashost_initiator_list_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSlotWWNMapping(device_id_t di, session_id_t si, req_data_slotwwn_mapping_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_getZoningGroupMembershipTable(device_id_t di, session_id_t si, req_data_zoning_groups_t * pData,
    u32 u32DataSize);
I2API u32 I2CALL i2_getZoningGroupPermissionTable(device_id_t di, session_id_t si, req_param_zoning_permission_t * pParam,
    req_data_zoning_permission_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setZoningGroupPermissionTable(device_id_t di, session_id_t si,
    req_param_zoning_permission_t * pParam, req_data_zoning_permission_t * pData, u32 u32DataSize);
#if 0
/* TBD */
I2API u32 I2CALL i2_getSoftwareCapabilities(device_id_t di, session_id_t si, software_capabilities_t * pSc);
#endif

I2API u32 I2CALL i2_sendPassThruCommand(device_id_t di, session_id_t si,  pass_through_cmd_t * pptc);

I2API u32 I2CALL i2_getUniqueCommandId(device_id_t di, session_id_t si, 
                                       req_param_unique_cmd_id_t * pParam, req_data_unique_cmd_id_t * pData);

I2API u32 I2CALL i2_releaseUniqueCommandId(device_id_t di, session_id_t si, 
                                           req_param_unique_cmd_id_t * pParam);

I2API u32 I2CALL i2_getLCDInfo(device_id_t di, session_id_t si,
    req_param_lcd_info_t *pParam, req_data_lcd_info_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_setLCDSettings(device_id_t di, session_id_t si,
    req_param_lcd_settings_t *pParam, req_data_lcd_settings_t * pData, u32 u32DataSize);

/* For UPS*/
I2API u32 I2CALL i2_getUPSStatus(device_id_t di, session_id_t si, req_param_ups_status_t * pParam, 
         req_data_ups_status_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getUPSSettings(device_id_t di, session_id_t si, req_param_ups_settings_t * pParam,
         req_data_ups_settings_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setUPSSettings(device_id_t di, session_id_t si, req_param_ups_settings_t * pParam, 
         req_data_ups_settings_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_postSoftwareEvent(device_id_t di, session_id_t si, req_param_software_event_t * pParam);
#endif /* I2_API_H */

/******************************************************************************
 * Change Log
 *
 * $Log: i2api.h,v $
 * Revision 1.50.6.3  2009/10/16 09:12:47  xinw
 * add performace monitor support
 *
 * Revision 1.50.6.2  2009/03/26 10:01:55  xinw
 * remove i2_startUPSReconditioning info
 *
 * Revision 1.50.6.1  2009/03/23 11:49:15  xinw
 * add ups support
 *
 * Revision 1.50  2008/07/30 05:24:04  michaell
 * Add i2_startLogDrvSynch/i2_pauseLogDrvSynch/i2_resumeLogDrvSynch
 *
 * Revision 1.49  2008/04/03 11:01:15  danielz
 * support LCD management
 *
 * Revision 1.48  2008/04/02 08:14:50  danielz
 * support clear error table
 *
 * Revision 1.47  2008/03/21 03:46:47  kenh
 * Remove the define of function i2_getHostDriverInfo()
 *
 * Revision 1.46  2007/12/06 12:08:17  danielz
 *  support for the extented physical drive statistic information
 *
 * Revision 1.45  2007/11/16 03:05:59  xinw
 * add new i2api of delete session
 *
 * Revision 1.44  2007/11/02 07:03:36  theoz
 * Add MIC Pass Thru APIs
 *
 * Revision 1.43  2007/08/21 09:01:13  danielz
 * support for getting version and build information of all the flash images
 * of the controllers
 *
 * Revision 1.42  2007/07/07 02:54:26  JudithLi
 * 14680/ST EX8650M-Host driver can't be updated on WPP 3.03.0000.50
 *
 * Revision 1.41  2007/04/20 10:24:07  xinw
 * add iscsi fw update support
 *
 * Revision 1.40  2007/02/06 10:57:17  danielz
 * New i2 API i2_getHostInfo() to get host information
 *
 * Revision 1.39  2007/02/01 03:59:33  xinw
 * add new Mx10i support
 *
 * Revision 1.38  2007/01/12 01:13:53  debinc
 * sas zoning support
 *
 * Revision 1.37  2007/01/04 19:48:20  debinc
 * slot wwn mapping add function header
 *
 * Revision 1.36  2007/01/02 23:13:48  debinc
 * slot wwn mapping support
 *
 * Revision 1.35  2006/11/07 08:12:08  danielz
 * SAS Host interface related APIs shall start with lower-case,
 * i2_GetSASHostPortInfo(), i2_GetSASHostPortStatistics(), i2_GetSASHostPortSetting(),
 * i2_SetSASHostPortSetting(), i2_GetSASInitiatorList()
 *
 * Revision 1.34  2006/10/24 08:58:08  danielz
 * new i2 API i2_getBatteryCapacity()
 *
 * Revision 1.33  2006/09/06 23:52:15  debinc
 * move currentctrlinfo out of raid capability
 *
 * Revision 1.32  2006/09/06 09:14:42  danielz
 * Support for clearing port statistics, getting phy level statistics of SAS host
 * Support for getting errorlog of c2c port, phy control to c2c port
 *
 * Revision 1.31  2006/08/24 02:32:44  xinc
 * Support "Configuration Export" in CLI
 *
 * Revision 1.30  2006/08/02 23:55:11  debinc
 * get sas initiator list
 *
 * Revision 1.29  2006/06/14 01:20:01  debinc
 * SAS frontend support
 *
 * Revision 1.28  2006/06/13 01:25:58  debinc
 * sas frontend api
 *
 * Revision 1.27  2006/05/11 23:49:48  debinc
 * sas diag
 *
 * Revision 1.26  2006/04/10 02:54:54  danielz
 * Add i2 API i2_clearDDFOnPd()
 *
 * Revision 1.25  2006/04/03 23:57:57  debinc
 * dual controller fc
 *
 * Revision 1.24  2006/04/01 03:36:48  debinc
 * support dual controller shutdown
 *
 * Revision 1.23  2006/03/29 02:20:07  debinc
 * support enter/exit maintenance mode
 *
 * Revision 1.22  2006/03/24 19:59:51  debinc
 * support dual controller subsys info/setting
 *
 * Revision 1.21  2006/02/22 01:28:31  debinc
 * get/set enclosure setting
 *
 * Revision 1.20  2005/12/14 00:36:28  debinc
 * SAS topology support
 *
 * Revision 1.19  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.18  2005/06/30 08:10:09  sergiyv
 * MX00P merge
 *
 * Revision 1.17  2005/05/20 23:09:31  debinc
 * FC MIC change
 *
 * Revision 1.16  2005/04/05 01:19:19  weny
 * add I2CALL to all FC API
 *
 * Revision 1.15  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.14  2004/12/23 03:41:54  weny
 * support bbm
 *
 * Revision 1.13  2004/12/09 22:45:52  debinc
 * implement getEventStats for RAM in s/w
 *
 * Revision 1.12  2004/10/27 18:57:40  debinc
 * shutdown command support
 *
 * Revision 1.11  2004/10/22 01:55:12  weny
 * add setFRUInfo support
 *
 * Revision 1.10  2004/10/19 04:34:17  weny
 * Online Array Removal support
 *
 * Revision 1.9  2004/10/05 19:39:40  debinc
 * remove subsys and enclosure stats
 *
 * Revision 1.8  2004/07/28 01:36:58  weny
 * add i2_locateFRU
 *
 * Revision 1.7  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.6  2004/07/09 23:42:10  debinc
 * add force logout
 *
 * Revision 1.5  2004/07/08 23:06:08  weny
 * merge with Napa I2 API
 *
 * Revision 1.4  2004/07/06 23:34:58  debinc
 * modify getSessionInfo
 *
 * Revision 1.3  2004/05/13 18:09:08  zhengj
 * added support for spare check and locate enclosure
 *
 * Revision 1.2  2004/05/04 18:25:04  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 *
 *****************************************************************************/
