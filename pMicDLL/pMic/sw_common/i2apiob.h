/*******************************************************************************
 * Filename    : i2apiob.h
 * Description : I2 API plug-in for out of band sepcific header file
 *               It defines the data structures and APIs specific to out-of-band
 *               plug-in.
 * Created on  : 02/18/2004
 * CVS Version : $Id: i2apiob.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * Copyright (C) 2004-2004 Promise Technology Inc.
 * All Rights Reserved
 ******************************************************************************/

#ifndef I2_API_OB_H
#define I2_API_OB_H

/* --- standard C lib header files ------------------------------------------ */

/* --- internal header files ------------------------------------------------ */
#include "pibasic.h"
#include "errcode.h"
#include "i2types.h"
#include "i2api.h"
#include "i2typesob.h"

/* --- constants & data structures ------------------------------------------ */

typedef struct
{
    u32 ivsp_u32BufferSize;
    u8 ivsp_u8MinLines;
    u8 ivsp_u8MaxLines;
    u8 ivsp_u8padding1[10];
#ifdef EMBEDDED
    char * ivsp_pstrMsgQueuePath; 
#ifndef PLATFORM_64BIT
    void * ivsp_pPadding2;
#endif /* ifdef 64BIT */
    u32 ivsp_u32MsgQueueChannel;
    u32 ivsp_u32NotificationSignal;
#else
    u32 ivsp_u32MaxSubsystems;
    u32 ivsp_u32MaxPathPerSubsys;
    u8 ivsp_u8Padding4[8];
#endif /* ifdef EMBEDDED */
    u8 ivsp_u8Reserved1[96];
} i2plugin_vtrak15300_specific_param_t;

/*
 * the plugin specific parameter should be passed in 
 * i2api_param_t.ip_u8PluginParam during i2_initialize with 
 * i2api_param_t.ip_bPluginParamValid set to TRUE.
 * if i2api_param_t.ip_bPluginParamValid is set to FALSE, the default plug-in
 * specific parameters will be used.
 *
 * ivsp_u8MinLines - min number of threads that can talk thru the plugin 
 *      simutaneously. The default is 1.
 * ivsp_u8MaxLines - max number of threads that can talk thru the plugin 
 *      simutaneously. The default is 1.
 * ivsp_u32BufferSize - the buffer size in number of bytes. It specifies the
 *      max data transfer size. The default is MAX_DATA_TRANSFER_SIZE.
 *
 * the following 3 parameters are specific to embedded
 *
 * ivsp_pstrMsgQueuePath - the message queue path, used in I2 IPC. The default
 *      is DEFAULT_I2IPC_MSGQ_PATH
 * ivsp_u32MsgQueueChannel - the message queue channel, used in I2 IPC. The
 *      default is DEFAULT_I2IPC_MSGQ_CHANNEL
 * ivsp_u32NotificationSignal - the event notification signal, used in I2 IPC.
 *      The default is DEFAULT_I2IPC_NOTIFY_SIGNAL
 *
 * the following 2 parameters are specific to non-embedded
 * 
 * ivsp_u32MaxSubsystems - the max number of subsystems the plug-in should
 *      discover. The default is 16.
 * ivsp_u32MaxPathPerSubsys - the max number of paths that should be discovered
 *      for one subsystem. The default is 4.
 */

/* --- functional routines ------------------------------------------------- */

I2API u32 I2CALL i2_clearControllerCondition(device_id_t di, session_id_t si, req_param_ctrl_condition_t * pParam);

I2API u32 I2CALL i2_arrayConfigParam(device_id_t di, session_id_t si, 
    array_config_param_t * pacp);
I2API u32 I2CALL i2_configArray(device_id_t di, session_id_t si, 
    u8 * pu8Buffer);

I2API u32 I2CALL i2_dumpCtrlDebugInfo(device_id_t di, session_id_t si, req_param_dump_ctrl_debug_info_t * pParam,
    req_data_dump_ctrl_debug_info_t * pData, u32 u32DataSize);

#ifndef EMBEDDED
#ifdef WINDOWS
I2API u32 I2CALL i2_sendBypassCommandToDevice(u8 * pu8DevPath, bypass_cmd_t * pbc);
#endif
I2API u32 I2CALL i2_scanForExistingDevice(u32 u32Timeout);
#endif

I2API u32 I2CALL i2_restoreFactoryDefaultsBga(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsCtrl(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsEncl(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsIscsi(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsNetIscsi(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsNetMgmt(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsPhyDrv(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSubsys(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsFC(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSAS(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
#ifdef EMBEDDED
/* TBD - Web server/CIMOM/Email Server/SSL settings */
I2API u32 I2CALL i2_getAllDaemonsInfo(device_id_t di, session_id_t si,
        req_swmgt_daemon_info_t *pData);
I2API u32 I2CALL i2_setDaemonStartupType(device_id_t di, session_id_t si,
        u8 * pDaemonName, u8 daemonStartupType);
I2API u32 I2CALL i2_startStopDaemon(device_id_t di, session_id_t si,
        u8 * pDaemonName, u8 daemonStatus, boolean_t bBlockingRestart);

I2API u32 I2CALL i2_testEmail(device_id_t di, session_id_t si,
    req_param_user_name_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_export(device_id_t di, session_id_t si,
    req_export_t * pData);
I2API u32 I2CALL i2_importTransfer(device_id_t di, session_id_t si,
    req_import_param_t * pParam);
I2API u32 I2CALL i2_importGetInfo(device_id_t di, session_id_t si,
    req_import_data_t * pData);
I2API u32 I2CALL i2_importAbort(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_importApply(device_id_t di, session_id_t si);

I2API u32 I2CALL i2_subscribeEventNotification(device_id_t di, 
    req_param_event_subscribe_t * pParam);
I2API u32 I2CALL i2_unsubscribeEventNotification(device_id_t di);
I2API u32 I2CALL i2_waitForSubscribedEvent(device_id_t di, u32 u32Timeout);

I2API u32 I2CALL i2_restoreFactoryDefaultsUserSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsBgaSchedulersSettting(device_id_t di, session_id_t si,
    u8 * pData, u32 u32DataSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSnmpSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsWebserverSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsCimserverSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsEmailSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSmbsendSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsTelnetSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsSshSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsNtpSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsDaemonSettting(device_id_t di, session_id_t si,
    u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_restoreFactoryDefaultsUPSManagerConfig(device_id_t di,session_id_t si,
        u8 * pu8Buffer, u32 u32BufSize);
I2API u32 I2CALL i2_filesync(device_id_t di, session_id_t si, req_param_filesync_t *prpf);
I2API u32 I2CALL i2_startStopSlaveDaemon(device_id_t di, session_id_t si, u8 * pDaemonName, u8 daemonStatus, boolean_t bBlockingRestart);
#endif

I2API u32 I2CALL i2_login(device_id_t di, session_id_t * pSi, req_param_session_login_t * pParam);
I2API u32 I2CALL i2_logout(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_getCurrentSessionInfo(device_id_t di, session_id_t si, session_info_t * pSession);
I2API u32 I2CALL i2_getSessionInfo(device_id_t di, session_id_t si, req_data_session_info_t * pu8Data, u32 u32DataSize);
I2API u32 I2CALL i2_forceSessionLogout(device_id_t di, session_id_t si, u32 * pu32SessionId);
/* TBD - all user APIs needs mondification */

#ifdef EMBEDDED
I2API u32 I2CALL i2_getUser(device_id_t di, session_id_t si, req_param_user_name_t * pParam, req_data_user_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getAllUser(device_id_t di, session_id_t si, req_data_user_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addUser(device_id_t di, session_id_t si, user_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_modifyUser(device_id_t di, session_id_t si, user_info_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_deleteUser(device_id_t di, session_id_t si, u8 u8UserName[MAX_USER_NAME_LENGTH]);
I2API u32 I2CALL i2_setPwd(device_id_t di, session_id_t si, req_param_pwd_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getUserPreference(device_id_t di, session_id_t si, 
    req_param_user_name_t * pParam, req_user_preference_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setUserPreference(device_id_t di, session_id_t si,
      req_user_preference_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSnmpConfig(device_id_t di, session_id_t si, req_data_snmp_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setSnmpConfig(device_id_t di, session_id_t si, req_data_snmp_config_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getSmbsendConfig(device_id_t di, session_id_t si, req_data_Smbsend_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setSmbsendConfig(device_id_t di, session_id_t si, req_data_Smbsend_config_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getEmailConfig(device_id_t di, session_id_t si,
    req_email_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setEmailConfig(device_id_t di, session_id_t si,
    req_email_config_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getCimserverConfig(device_id_t, session_id_t si,
    req_data_cimserver_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setCimserverConfig(device_id_t, session_id_t si,
    req_data_cimserver_config_t * pData, u32 u32DataSize); 

I2API u32 I2CALL i2_getWebserverConfig(device_id_t, session_id_t si,
    req_data_webserver_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setWebserverConfig(device_id_t, session_id_t si,
    req_data_webserver_config_t * pData, u32 u32DataSize);    
I2API u32 I2CALL i2_getWebserverCurrentConfig(device_id_t, session_id_t si,
    req_data_webserver_config_t * pData, u32 u32DataSize); 
    
I2API u32 I2CALL i2_getBonjourConfig(device_id_t, session_id_t si,
    req_data_bonjour_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setBonjourConfig(device_id_t, session_id_t si,
    req_data_bonjour_config_t * pData, u32 u32DataSize);

I2API u32 I2CALL i2_getTelnetConfig(device_id_t, session_id_t si,
    req_data_telnet_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setTelnetConfig(device_id_t, session_id_t si,
    req_data_telnet_config_t * pData, u32 u32DataSize);   
I2API u32 I2CALL i2_getPowerScheduleSetting (device_id_t di, session_id_t si, 
    req_data_power_schedule_setting_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_getSshConfig(device_id_t, session_id_t si,
    req_data_ssh_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setSshConfig(device_id_t, session_id_t si,
    req_data_ssh_config_t * pData, u32 u32DataSize); 
#endif /* EMBEDDED */
I2API u32 I2CALL i2_getNtpConfig(device_id_t, session_id_t si,
    req_data_ntp_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setNtpConfig(device_id_t, session_id_t si,
    req_data_ntp_config_t * pData, u32 u32DataSize);
    
I2API u32 I2CALL i2_getLastNtpSyncStatus(device_id_t, session_id_t si,
    req_data_ntp_sync_status_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setLastNtpSyncStatus(device_id_t, session_id_t si,
    req_data_ntp_sync_status_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_executeNtp(device_id_t di, session_id_t si);
I2API u32 I2CALL i2_testNtpServer(device_id_t di, session_id_t si, req_param_ntp_test_t *pParam);

I2API u32 I2CALL i2_getUPSManagerConfig(device_id_t, session_id_t si,
    req_data_ups_manager_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setUPSManagerConfig(device_id_t, session_id_t si,
    req_data_ups_manager_config_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setPowerScheduleSetting (device_id_t di, session_id_t si, 
    req_data_power_schedule_setting_t * pData, u32 u32DataSize); 
I2API u32 I2CALL i2_getBGASchedule(device_id_t di, session_id_t si, req_param_bga_schedule_t * pParam, req_data_bga_schedule_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_addBGASchedule(device_id_t di, session_id_t si, req_data_bga_schedule_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_deleteBGASchedule(device_id_t di, session_id_t si, req_data_bga_schedule_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_modifyBGASchedule(device_id_t di, session_id_t si, req_data_bga_schedule_t * pData, u32 u32DataSize);
I2API u32 I2CALL i2_setFirmwareDebugSetting (device_id_t di, session_id_t si, 
	req_param_firmware_debug_settings_t * pParam);
I2API u32 I2CALL i2_setSoftwareDebugSetting (device_id_t di, session_id_t si, 
	req_param_software_debug_settings_t * pParam);
I2API u32 I2CALL i2_getNASDeviceNodeinfo (device_id_t di, session_id_t si, 
    req_data_nas_device_node_info_t * pData, u32 u32DataSize);

#endif /* I2_API_OB_H */

/******************************************************************************
 * Change Log
 *
 * $Log: i2apiob.h,v $
 * Revision 1.11.6.6  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.11.6.5  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.11.6.4  2009/10/15 03:01:37  xinw
 * add nas support
 *
 * Revision 1.11.6.3  2009/03/23 11:49:36  xinw
 * add ups support
 *
 * Revision 1.11.6.2  2009/01/22 02:24:34  xinw
 * move i2_setPowerScheduleSetting for both embedded and inband
 *
 * Revision 1.11.6.1  2008/12/02 06:54:49  xinw
 * add power schedule support
 *
 * Revision 1.11  2008/06/25 02:42:05  xinw
 * SW Serviceability Improvement
 *
 * Revision 1.10  2008/06/23 07:42:20  jackyl
 * add bonjour support
 *
 * Revision 1.9  2007/08/28 10:22:07  danielz
 * support for the dump controller debug information.
 * add a new i2 api i2_dumpCtrlDebugInfo()
 *
 * Revision 1.8  2006/09/12 09:39:34  leync
 * add i2_startStopSlaveDaemon().
 *
 * Revision 1.7  2006/08/22 22:07:20  xinw
 * add i2 call for file sync
 *
 * Revision 1.6  2006/07/06 01:35:34  debinc
 * place holder for restore sas setting.
 *
 * Revision 1.5  2006/05/03 04:46:36  leync
 * add cimserver set factory default support.
 *
 * Revision 1.4  2006/04/26 07:54:18  danielz
 * Remove the fifth parameter which is useless of i2 API
 * i2_restoreFactoryDefaultsUserSettting()
 *
 * Revision 1.3  2006/04/14 02:48:40  JudithLi
 * netsend factory default
 *
 * Revision 1.2  2006/03/31 04:50:22  leync
 * add cimom server setting feature in CLU
 *
 * Revision 1.1  2006/03/16 03:02:16  debinc
 * rename header file
 *
 * Revision 1.15  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.14  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.13  2005/03/19 00:33:50  debinc
 * change swmgt startstop to support non-blocking restart
 *
 * Revision 1.12  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.11  2005/02/03 01:58:33  debinc
 * pass password when restoring user setting
 *
 * Revision 1.10  2004/09/28 17:49:13  debinc
 * factory default for telnet
 *
 * Revision 1.9  2004/09/16 01:39:33  debinc
 * telnet setting
 *
 * Revision 1.8  2004/08/31 06:47:59  weny
 * add i2_clearControllerCondition for clearing nvram watermark
 *
 * Revision 1.7  2004/08/18 23:28:49  weny
 * Added i2_sendBypassCommandToDevice
 *
 * Revision 1.6  2004/07/26 21:27:22  debinc
 * Add restore sw factory default
 *
 * Revision 1.5  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.4  2004/07/20 04:23:03  weny
 * add i2_restoreFactoryDefaults... APIs
 *
 * Revision 1.3  2004/07/06 23:15:18  weny
 * use pibasic.h
 *
 * Revision 1.2  2004/05/04 18:25:03  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 *
 *****************************************************************************/
