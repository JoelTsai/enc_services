/*******************************************************************************
 * Filename    : pdefault.h
 * Description : Promise IslaVista Factory Defaults header file
 *               * provide factory default setting values
 * Created on  : 07/15/2003
 * CVS Version : $Id: pdefault.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2004 - 2004
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_DEFAULT_H__
#define __PI_DEFAULT_H__

/* --- standard C lib header files ----------------------------------------- */
#include <time.h>

#undef DECODE_API
#undef DECODE_CALL
#ifdef WINDOWS
    #include "windows.h"
	#if defined(PROMISE_DEFAULT_DLL)
		#define PDEFAULT_API  __declspec(dllexport)
		#define PDEFAULT_CALL
	#else
		//#define PROMISEAPI  __declspec(dllimport)
		#define PDEFAULT_API
		#define PDEFAULT_CALL __cdecl
	#endif
#else
	#define PDEFAULT_API
	#define PDEFAULT_CALL
#endif

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "i2types.h"
#include "i2typesob.h"

typedef struct
{
    u8 eas_u8EnclCount;
    u8 eas_u8Reserved[7];
    enclosure_setting_t eas_EnclosureSetting[32];
} enclosure_all_setting_t;

/* --- constant definitions ------------------------------------------------ */

#define DEFAULT_NULL_STRING             ""

#define DEFAULT_USER_EMAIL                    "admin@yourcompany.com"
#define DEFAULT_USER_FULLNAME                 "Super user"
#ifdef CLEARBAY
#define DEFAULT_USER_PASSWORD                 "@dmin"
#define DEFAULT_USER_USERNAME                 "admin"
#else
#define DEFAULT_USER_PASSWORD                 "password"
#define DEFAULT_USER_USERNAME                 "administrator"
#endif

#define DEFAULT_SNMP_TRAP_SINKS               0
#define DEFAULT_SNMP_PORT_NUM                 161
#define DEFAULT_SNMP_SYSTEM_NAME              ""
#define DEFAULT_SNMP_SYSTEM_CONTACT           "admin@yourcompany.com"
#define DEFAULT_SNMP_SYSTEM_LOCN              "USA"
#define DEFAULT_SNMP_READ_COMMUNITY           "public"
#define DEFAULT_SNMP_WRITE_COMMUNITY          "private"

#define DEFAULT_CIM_HTTP_PORT                 5988
#define DEFAULT_CIM_HTTPS_PORT                5989

#define DEFAULT_WEBSERVER_HTTP_PORT           80
#define DEFAULT_WEBSERVER_HTTPS_PORT          443
#define DEFAULT_WEBSERVER_SESSION_TIMEOUT     1440

#define DEFAULT_EMAIL_SMTP_PORT               25
#define DEFAULT_EMAIL_AUTH_USER               ""
#define DEFAULT_EMAIL_AUTH_PASSWORD           ""
#define DEFAULT_EMAIL_FROM                    ""
#define DEFAULT_EMAIL_SMTP_HOST               "0.0.0.0"
#define DEFAULT_EMAIL_SUBJECT                 "Event Notification"

#define DEFAULT_TELNET_PORT                   2300
#define DEFAULT_TELNET_SESSION_TIMEOUT        1440
#define DEFAULT_TELNET_MAX_CONNECTIONS        4

#define DEFAULT_SSH_PORT                      22
#define DEFAULT_SSH_SESSION_TIMEOUT           1440
#define DEFAULT_SSH_MAX_CONNECTIONS           4

#define DEFAULT_NTP_TIMEZONE                  0
#define DEFAULT_NTP_TIME_SERVER_CNT           0
#define DEFAULT_NTP_DST_STARTTIME_MONTH       2
#define DEFAULT_NTP_DST_STARTTIME_WOM         1
#define DEFAULT_NTP_DST_STARTTIME_DOW         0
#define DEFAULT_NTP_DST_ENDTIME_MONTH         10
#define DEFAULT_NTP_DST_ENDTIME_WOM           0
#define DEFAULT_NTP_DST_ENDTIME_DOW           0

#define DEFAULT_UPS_RUNTIME_REMAIN_THRESHOLD  5
#define DEFAULT_UPS_LOADING_RATIO_THRESHOLD   80
#define DEFAULT_UPS_CRITICAL_TEMP_THRESHOLD   38
#define DEFAULT_UPS_CURRENT_DRIVER            0
#define DEFAULT_UPS_IP                        "0.0.0.0"


#define PDEFAULT_SIZE_SUBSYS            sizeof(micSubsystemSettings_t)
#define PDEFAULT_SIZE_CLIQUE            sizeof(micCliqueSettings_t)
#define PDEFAULT_SIZE_CTRL_RAID         sizeof(micCtrlSettingsPage0_t)
#define PDEFAULT_SIZE_CTRL_OTHER_HW     sizeof(micCtrlSettingsPage3_t)
#define PDEFAULT_SIZE_CTRL_ISCSI_NETWORK     sizeof(micCtrlSettingsPage4_t)
#define PDEFAULT_SIZE_CTRL_ETHER_NETWORK     sizeof(micCtrlSettingsPage5_t)
#define PDEFAULT_SIZE_CTRL_ETHER_NETWORK_MAINTENANCE     sizeof(micCtrlSettingsPage7_t)
#define PDEFAULT_SIZE_ENCLOSURE                         sizeof(enclosure_all_setting_t)
#define PDEFAULT_SIZE_PHYDRV_SATA       sizeof(micPDSettingsPage1_t)  
#define PDEFAULT_SIZE_PHYDRV_SAS       sizeof(micPDSettingsPage3_t)  
#define PDEFAULT_SIZE_ISCSI_NODE        sizeof(micISCSIExtendedNodeParameterInfoPage_t)
#define PDEFAULT_SIZE_ISCSI_TCPIP_ADV   sizeof(micTcpIpAdvSettings_t)
#define PDEFAULT_SIZE_ISCSI_GBETHER     0  /* a place holder for iSCSI GB ethernet settings */
#define MAX_DEFAULT_ISCSI_CHAP_RECORDS  1
#define PDEFAULT_SIZE_ISCSI_CHAP        (sizeof(micChapConfigData_t) + ((MAX_DEFAULT_ISCSI_CHAP_RECORDS -1) * sizeof(micCHAPRecord_t)))
#define PDEFAULT_SIZE_ISCSI_SLP         sizeof(micSLPInfoSettings_t)
#define PDEFAULT_SIZE_ISCSI_ISNS        sizeof(micISNSInfoSettings_t)
#define PDEFAULT_SIZE_ISCSI_SESSION     sizeof(miciSCSISessionSettings_t)
#define PDEFAULT_SIZE_ISCSI_PORT        (sizeof(micTargetPortSettings_t) + ((MAX_ISCSI_PORTS - 1) * sizeof(TargetPortSettings_t)))
#define PDEFAULT_SIZE_FC_PORT           sizeof(micFCConfigPage_Parameters_t)
#define PDEFAULT_SIZE_SAS_PORT           sizeof(SASPortSetting_t)
#define PDEFAULT_SIZE_SCSI_PORT           sizeof(micPSCSIPortSettings_t)

/* --- data structures ----------------------------------------------------- */


/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: pdflt_get<object>SettingDefaults 
* Description: get the default settings of <object>.
* Parameters:
*       [in] u16PageCode, the page code of the settings
*   	[out] pDefaults, default <object> settings
* Return: possible return values are:
*       PIERR_NO_ERROR, succeeded; 
*       PIERR_NO_DEFAULT_SETTINGS: the settings do not have defaults;
*       PIERR_OEM_DEFAULT_NOT_AVAILABLE: OEM customized defaults are not 
*           available, usually due to an error encountered at parsing the 
*           OEM factory defaults.
* Remarks: the function assume pDefaults points to a valid buffer, which is 
*           big enough to hold the returned default settings.     
****************************************************************************/

PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSubsystemSettingDefaults(micSubsystemSettings_t * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getCliqueSettingDefaults(micCliqueSettings_t * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getControllerSettingDefaults(u16 u16PageCode, u8 * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getPhyDrvSettingDefaults(u16 u16PageCode, u8 * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getiSCSISettingDefaults(u16 u16PageCode, u8 * pDefaults);

PDEFAULT_API u32 PDEFAULT_CALL pdflt_getUserSettingDefaults(user_list_t * pui);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSwmgtSettingDefaults(req_swmgt_daemon_info_t * prsdi);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getBgaSchedulersSettingDefaults(req_data_bga_schedule_t * pBuf, u32 * pu32BufSize);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSnmpSettingDefaults(req_data_snmp_config_t * prdsc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getWebserverSettingDefaults(req_data_webserver_config_t * prdwc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getCimserverSettingDefaults(req_data_cimserver_config_t * prdcc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getEmailSettingDefaults( email_config_t * pec);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getTelnetSettingDefaults( req_data_telnet_config_t * prdtc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSshSettingDefaults( req_data_ssh_config_t * prdtc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getNtpSettingDefaults( req_data_ntp_config_t * prdnc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getFCSettingDefaults(u8 * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSASSettingDefaults(u8 * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSCSISettingDefaults(u8 * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getEnclosureSettingDefaults(enclosure_all_setting_t * pDefaults);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getSmbsendSettingDefaults(req_data_Smbsend_config_t * prdsc);
PDEFAULT_API u32 PDEFAULT_CALL pdflt_getUPSManagerConfigDefaults(req_data_ups_manager_config_t *prdumc);
#endif /*__PI_DEFAULT_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: pdefault.h,v $
 * Revision 1.13.42.4  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.13.42.3  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.13.42.2  2009/09/29 03:05:55  xinw
 * merge Import/Export consistent to E-class
 *
 * Revision 1.13.42.1  2009/04/06 08:51:50  xinw
 * add pdflt_getUPSManagerConfigDefaults
 *
 * Revision 1.13  2006/08/07 22:31:38  debinc
 * restore clique setting
 *
 * Revision 1.12  2006/07/22 01:15:17  debinc
 * sas factory default
 *
 * Revision 1.11  2006/05/31 19:21:05  debinc
 * factory defaults encl
 *
 * Revision 1.10  2006/05/30 18:25:49  debinc
 * factory defaults
 *
 * Revision 1.9  2006/05/03 04:46:36  leync
 * add cimserver set factory default support.
 *
 * Revision 1.8  2006/03/16 01:39:09  debinc
 * rename header file
 *
 * Revision 1.7  2005/12/27 13:56:18  linusc
 * support sas pd settings
 *
 * Revision 1.6  2005/06/30 08:10:09  sergiyv
 * MX00P merge
 *
 * Revision 1.5  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.4  2004/09/28 17:49:13  debinc
 * factory default for telnet
 *
 * Revision 1.3  2004/07/26 21:27:22  debinc
 * Add restore sw factory default
 *
 * Revision 1.2  2004/07/22 03:56:24  weny
 * for iscsi port default settings
 *
 * Revision 1.1  2004/07/20 04:21:20  weny
 * add support of promise factory default library
 *
 ******************************************************************************/
