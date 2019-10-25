/*******************************************************************************
 * Filename    : i2typesob.h
 * Description : I2 API plug-in for IslaVista sepcific data structure header file
 * Created on  : 07/20/04
 * CVS Version : $Id: i2typesob.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2004 - 2004
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __I2_TYPES_ISLAVISTA_H__
#define __I2_TYPES_ISLAVISTA_H__

#include "pibasic.h"
#include "i2types.h"

#include "autoconfig.h"
#include "bgaschd.h"
#include "userdata.h"
#include "swmgt.h"
#include "emaildata.h"
#include "imexportdata.h"
#include "sessdata.h"
#include "internalmic.h"
#include "ntpdata.h"

/* --- constants & data structures ------------------------------------------ */

#define I2API_CTRL_CONDITION_WATERMARK  0
typedef struct req_param_ctrl_condition
{
    u32 rpcc_u32CtrlId;
    u8 rpcc_u8Condition;
    u8 rpcc_u8Reserved[13];
} req_param_ctrl_condition_t;

typedef struct req_param_session_login
{
    u32 rpsl_u32UsernameLength;
    u32 rpsl_u32PasswordLength;
    u8 rpsl_u8Username[MAX_USER_NAME_LENGTH];
    u8 rpsl_u8Password[MAX_PASSWORD_LENGTH];
    u8 rpsl_u8Interface[MAX_SESSION_INTERFACE_LENGTH]; /* the interfaces can be: HTTP, CIM, SNMP, TELNET, RS232, TFTP */
} req_param_session_login_t;

typedef struct
{
    __u32 rdsl_u32SessionId;
    u8 rdsl_u8UserGroup;
    u8 rdsl_u8Reserved[3];
} req_data_session_login_t;

#define AUTHORIZE(req, grp) ((grp >= req)?PIERR_NO_ERROR:PIERR_NOT_AUTHORIZED)

typedef struct
{
    DataBufferHeader_t rdsi_dbhHeader;
    session_info_t rdsi_siSessionInfo[1];
} req_data_session_info_t;

/* user management */
typedef struct
{
    user_list_t rdui_ulList;
} req_data_user_info_t;

typedef struct
{
    u8 rpu_u8Username[MAX_USER_NAME_LENGTH]; 
} req_param_user_name_t;

typedef struct
{
    user_info_t rpua_uiUser;
} req_param_user_info_t;

typedef struct
{
    user_info_t rpuam_uiUser;
} req_param_user_add_mod_t;

typedef struct
{
    u8 rpp_u8Username[MAX_USER_NAME_LENGTH];
    u8 rpp_u8OldPassword[MAX_PASSWORD_LENGTH];
    u8 rpp_u8NewPassword[MAX_PASSWORD_LENGTH];
} req_param_pwd_t;

/* bga scheduler */
typedef struct
{
    u8 rpbs_u8BgaType; /* BGAS_TYPE_MP, BGAS_TYPE_RC or BGA_TYPE_ALL */
    u8 rpbs_u8Reserved[7];
} req_param_bga_schedule_t;

/* bga scheduler */
typedef bga_schedules_t req_data_bga_schedule_t;

/* sw component management */
typedef struct
{
    u8 rsdi_u8NumDaemon;
    u8 rsdi_u8Reserved[7];
    swmgt_daemon_info_t rsdi_sdiDaemonInfo[MAX_NUM_DAEMON];
} req_swmgt_daemon_info_t;

typedef struct
{
    u8 rpd_u8DaemonName[MAX_DAEMON_NAME_LEN];
    u8 rpd_u8DameonStatusType;
    boolean_t rpd_bBlockingRestart;
    u8 rpd_u8Reserved[6];
} req_param_daemon_t;

/* ntp test*/
typedef struct
{
    u8 rdnt_u8TimeServer[MAX_TIME_SERVER_NAME_LENGTH];
} req_param_ntp_test_t;

/* email event notifiy */
typedef struct
{
    email_config_t rec_ecEmailConfig;
} req_email_config_t;

/* Smbsend */
typedef struct
{
    u32 rdsc_u32recipientCfgOffset;
    u16 rdsc_u16NumberOfrecipients;
} req_data_Smbsend_config_t;

typedef struct
{
	u8  rdumc_u8DetectionMode;
	u8  rdumc_u8ActionMode;
    u8  rdumc_u8CritTempThs;         /* critical temperature threshold */
    u8  rdumc_u8RTRThs;              /* running time remaining threshold in minute */
    u8  rdumc_u8LRThs;               /* loading ratio threshold */
    u8  rdumc_u8CurDriver;           /* current driver being used */
    u8  rdumc_u8Reserved[2];
    u8  rdumc_u8UPS0IP[16];
    u8  rdumc_u8UPS1IP[16];
    u8  rdumc_u8Reserved2[32];
} req_data_ups_manager_config_t;

typedef struct
{
    u8 rdstc_u8recipient[32];
    u8 rdstc_u8EventSeverity;
    u8 rdstc_u8Reserved[7];
} req_data_Smbsend_recipient_config_t;

typedef struct
{
    u8 rup_u8Username[MAX_USER_NAME_LENGTH];
    user_preference_t rup_upUserPreference;
} req_user_preference_t;

/* import export */
typedef struct
{
    export_param_t re_epExport;    
} req_export_t;

typedef struct
{
    import_param_t rip_ipImport;
} req_import_param_t;

typedef struct
{
    import_status_t rid_isImport;
} req_import_data_t;

/* snmp */
typedef struct
{
    u32 rdsc_u32TrapCfgOffset;
    u16 rdsc_u16NumberOfTrapSinks;
    u16 rdsc_u16PortNum;
    u8 rdsc_u8SystemName[256];
    u8 rdsc_u8SystemContact[256];
    u8 rdsc_u8SystemLocation[256];
    u8 rdsc_u8ReadCommunity[64];
    u8 rdsc_u8WriteCommunity[64];
} req_data_snmp_config_t;

typedef struct
{
    u8 rdstc_u8TrapSink[32];
    u8 rdstc_u8EventSeverity;
    u8 rdstc_u8Reserved[7];
} req_data_snmp_trap_config_t;

/* cim server */
typedef struct
{
    u16 rdcc_u16HttpPort;
    u16 rdcc_u16HttpsPort;
    boolean_t rdcc_bHttpEnabled;
    boolean_t rdcc_bHttpsEnabled;
    boolean_t rdcc_bAuthenticationEnabled;
    boolean_t rdcc_bRestoreDefaultUser; /* Not a configuration option */
    u8 rdcc_u8Reserved[4];	
    u8 rdcc_u8UserName[256];
    u8 rdcc_u8OldPassword[256];
    u8 rdcc_u8Password[256];
} req_data_cimserver_config_t;

/* web server */
typedef struct
{
    u16 rdwc_u16HttpPort;
    u16 rdwc_u16HttpsPort;
    u32 rdwc_u32SessionTimeout;
    boolean_t rdwc_bSSLEnabled;
    u8 rdwc_u8Reserved[7];
} req_data_webserver_config_t;

/* bonjour */
typedef struct
{
    u8 rdbc_u8HostName[64];
    u8 rdbc_u8DomainName[16];
    u8 rdbc_u8Reserved[4];
} req_data_bonjour_config_t;

/* telnet */
typedef struct
{
    u32 rdtc_u32SessionTimeout;
    u16 rdtc_u16Port;
    u8 rdtc_u8NumConnection;
    u8 rdtc_u8Reserved[9];
} req_data_telnet_config_t;

/* ssh */
typedef struct
{
    u32 rdsc_u32SessionTimeout;
    u16 rdsc_u16Port;
    u8 rdsc_u8MaxNumOfConnection;
    u8 rdsc_u8Reserved[9];
} req_data_ssh_config_t;

/* ntp */
typedef struct
{
    boolean_t rdnc_bNTPEnabled;
    boolean_t rdnc_bDSTEnabled; //enable Daylight Saving Time
    u8 rdnc_u8Reserved[2];
    s32 rdnc_s32TimeZone;
    u32 rdnc_u32NumOfTimeServer;
    dst_WeekDayOfMonth_t rdnc_dwDSTStartTime;
    dst_WeekDayOfMonth_t rdnc_dwDSTEndTime;
    u8 rdnc_u8TimeServer[MAX_TIME_SERVER_COUNT][MAX_TIME_SERVER_NAME_LENGTH];
} req_data_ntp_config_t;

typedef struct
{
	u32 rdne_u32NumOfTimeServerSuccessful;
	u32 rdne_u32NumOfTimeServerFailed;
	u8 rdne_u8Reserved[32];
    u8 rdne_u8TimeServerSuccessful[MAX_TIME_SERVER_COUNT][MAX_TIME_SERVER_NAME_LENGTH];
	u8 rdne_u8TimeServerFailed[MAX_TIME_SERVER_COUNT][MAX_TIME_SERVER_NAME_LENGTH];
} req_data_ntp_execute_t;

typedef struct
{
    boolean_t rdnss_bNTPSyncExist; //TRUE:exist, FALSE:not exist
    boolean_t rdnss_bNTPSyncResult; //TRUE:successful, FALSE:failed
    u8 rdnss_u8Reserved[6];
    u64 rdnss_u64NTPSyncTime;
	u32 rdnss_u32NumOfTimeServerSuccessful;
	u32 rdnss_u32NumOfTimeServerFailed;
    u8 rdnss_u8TimeServerSuccessful[MAX_TIME_SERVER_COUNT][MAX_TIME_SERVER_NAME_LENGTH];
	u8 rdnss_u8TimeServerFailed[MAX_TIME_SERVER_COUNT][MAX_TIME_SERVER_NAME_LENGTH];
} req_data_ntp_sync_status_t;

typedef struct req_param_dump_ctrl_debug_info
{
    req_param_device_ids_t rpdcdi_rpdiDeviceIds;
} req_param_dump_ctrl_debug_info_t;

typedef struct req_data_dump_ctrl_debug_info
{
    DataBufferHeader_t rddcdi_dbhHeader;
    micCtrlDumpInfo1_t rddcdi_DumpInfo;
} req_data_dump_ctrl_debug_info_t;

#endif /* __I2_TYPES_ISLAVISTA_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: i2typesob.h,v $
 * Revision 1.7.6.4  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.7.6.3  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.7.6.2  2009/04/21 05:58:10  xinw
 * add action choise item
 *
 * Revision 1.7.6.1  2009/03/23 11:50:08  xinw
 * add ups support
 *
 * Revision 1.7  2008/07/04 08:58:06  jackyl
 * increase bonjour hostname length to 64
 *
 * Revision 1.6  2008/06/23 07:42:20  jackyl
 * add bonjour support
 *
 * Revision 1.5  2008/02/18 09:56:13  danielz
 * remove req_param_dump_ctrl_debug_info_t and req_data_dump_ctrl_debug_info_t
 * from i2types.h to i2typesob.h as those structure are used for embedded only
 *
 * Revision 1.4  2006/12/30 08:54:04  danielz
 * Add a flag in req_data_cimserver_config_t for restoring default user of
 * factory default of CIM service
 *
 * Revision 1.3  2006/04/06 04:45:31  JudithLi
 * SR3 change to Main tree
 *
 * Revision 1.2  2006/03/31 04:50:22  leync
 * add cimom server setting feature in CLU
 *
 * Revision 1.1  2006/03/16 03:02:16  debinc
 * rename header file
 *
 * Revision 1.8  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.7  2005/03/19 00:33:51  debinc
 * change swmgt startstop to support non-blocking restart
 *
 * Revision 1.6  2005/02/01 19:25:35  debinc
 * 8-byte aligned
 *
 * Revision 1.5  2004/09/16 01:39:33  debinc
 * telnet setting
 *
 * Revision 1.4  2004/08/31 06:46:58  weny
 * add type for i2_clearControllerCondition
 *
 * Revision 1.3  2004/08/27 22:46:56  debinc
 * use env SW_CONF_PATH
 *
 * Revision 1.2  2004/08/25 18:39:50  debinc
 * add common sw-conf define
 *
 * Revision 1.1  2004/07/20 20:57:45  weny
 * I2 API clean up
 *
 *******************************************************************************/



