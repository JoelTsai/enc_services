/*******************************************************************************
 * Filename    : reqdef.h
 * Description : Request Definition header file
 *               * It provides the request group and request definitions of the
 *                 I2 IPC requests 
 *               * This file will be shared among I2 and I2 Client library.
 * Created on  : 02/04/03
 * CVS Version : $Id: reqdef.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_REQDEF_H__
#define __PI_REQDEF_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */

/* --- constant definitions ------------------------------------------------ */

/* request groups */

#define I2IPC_REQ_GRP_COUNT 15
#define I2IPC_REQ_GRP_FWBYPASS 0        /* firmware bypass request */
#define I2IPC_REQ_GRP_EVENT 1           /* event info/notification */
#define I2IPC_REQ_GRP_SESSION 2         /* login and logout */
#define I2IPC_REQ_GRP_USERMGT 3         /* user management */
#define I2IPC_REQ_GRP_SCHEDULER 4       /* the bga scheduler */
#define I2IPC_REQ_GRP_LOCKMGT 5         /* lock management */
#define I2IPC_REQ_GRP_SWMGT 6           /* sw management */
#define I2IPC_REQ_GRP_EMAILEVT 7        /* email event notify management */
#define I2IPC_REQ_GRP_IMEXPORT 8        /* import export management */
#define I2IPC_REQ_GRP_SWCONFIG 9        /* sw config management */
#define I2IPC_REQ_GRP_FLASH 10          /* FLASH management */
#define I2IPC_REQ_GRP_SYSTEM 11       /* shutdown management */
#define I2IPC_REQ_GRP_DEBUG 12        /* set debug option */
#define I2IPC_REQ_GRP_UPS 13        /* ups management */
#define I2IPC_REQ_GRP_EXECUTE 14        /* execute command */
#define I2IPC_REQ_GRP_DRIVER 15        /* get driver version request */

/* requests firmware bypass */
#define I2IPC_REQ_GRP_FWBYPASS_ID_COUNT 2
#define I2IPC_REQ_FWBYPASS_IOCTL 0         /* firmware IOCTL command */
#define I2IPC_REQ_FWBYPASS_DIRECT 1        /* firmware direct command */
#define I2IPC_REQ_DRIVER_IOCTL 2        /* driver IOCTL command */

/* requests of event */
#define I2IPC_REQ_GRP_EVENT_ID_COUNT 6      /* number of req ids in EVENT req grp */
#define I2IPC_REQ_EVENT_GETEVENT 0
#define I2IPC_REQ_EVENT_GETEVENTSTATS 1
#define I2IPC_REQ_EVENT_GETFIRSTEVENT 2
#define I2IPC_REQ_EVENT_GETLASTEVENT 3
#define I2IPC_REQ_EVENT_SUBSCRIBE 4
#define I2IPC_REQ_EVENT_UNSUBSCRIBE 5

/* requests of session */
#define I2IPC_REQ_GRP_SESSION_ID_COUNT 5
#define I2IPC_REQ_SESSION_LOGIN 0
#define I2IPC_REQ_SESSION_LOGOUT 1
#define I2IPC_REQ_SESSION_GET_CURRENT 2
#define I2IPC_REQ_SESSION_GET 3
#define I2IPC_REQ_SESSION_FORCE_LOGOUT 4

/* user management */
#define I2IPC_REQ_GRP_USERMGT_ID_COUNT 7
#define I2IPC_REQ_USERMGT_GETALLUSER 0
#define I2IPC_REQ_USERMGT_ADDUSER 1
#define I2IPC_REQ_USERMGT_DELUSER 2
#define I2IPC_REQ_USERMGT_GETUSER 3
#define I2IPC_REQ_USERMGT_MODUSER 4
#define I2IPC_REQ_USERMGT_SETPWD 5
#define I2IPC_REQ_USERMGT_RESTORE_FACTORYDEFAULTS 6

/* sw management */
#define I2IPC_REQ_GRP_SWMGT_ID_COUNT 4
#define I2IPC_REQ_SWMGT_GETALLDAEMON 0
#define I2IPC_REQ_SWMGT_STARTSTOP 1
#define I2IPC_REQ_SWMGT_SETSTARTTYPE 2
#define I2IPC_REQ_SWMGT_STARTSTOPSLAVE 3

/* email event notify management */
#define I2IPC_REQ_GRP_EMAILEVT_ID_COUNT 5
#define I2IPC_REQ_EMAILEVT_GETEMAILSETTING 0
#define I2IPC_REQ_EMAILEVT_SETEMAILSETTING 1
#define I2IPC_REQ_EMAILEVT_TESTEMAIL 2
#define I2IPC_REQ_EMAILEVT_GETUSERPREFERENCE 3
#define I2IPC_REQ_EMAILEVT_SETUSERPREFERENCE 4

/* import export management */
#define I2IPC_REQ_GRP_IMEXPORT_ID_COUNT 5
#define I2IPC_REQ_IMEXPORT_EXPORT 0
#define I2IPC_REQ_IMEXPORT_IMPORTTRANSFER 1
#define I2IPC_REQ_IMEXPORT_IMPORTGETINFO 2
#define I2IPC_REQ_IMEXPORT_IMPORTABORT 3
#define I2IPC_REQ_IMEXPORT_IMPORTAPPLY 4

/* bga scheduler */
#define I2IPC_REQ_GRP_SCHEDULER_COUNT 6
#define I2IPC_REQ_SCHEDULER_GET 0
#define I2IPC_REQ_SCHEDULER_ADD 1
#define I2IPC_REQ_SCHEDULER_DELETE 2
#define I2IPC_REQ_SCHEDULER_MODIFY 3
#define I2IPC_REQ_SCHEDULER_SAVE 4
#define I2IPC_REQ_SCHEDULER_RESTORE 5

/* lock management */
#define I2IPC_REQ_GRP_LOCKMGT_COUNT 4
#define I2IPC_REQ_LOCKMGT_CHECK 0
#define I2IPC_REQ_LOCKMGT_LOCK 1
#define I2IPC_REQ_LOCKMGT_EXTEND 2
#define I2IPC_REQ_LOCKMGT_UNLOCK 3

/* swconfig management */
#define I2IPC_REQ_GRP_SWCONFIG_ID_COUNT 19
#define I2IPC_REQ_SWCONFIG_SNMP_GET_CFG 0
#define I2IPC_REQ_SWCONFIG_SNMP_SET_CFG 1
#define I2IPC_REQ_SWCONFIG_WEBSERVER_GET_CFG 2
#define I2IPC_REQ_SWCONFIG_WEBSERVER_SET_CFG 3
#define I2IPC_REQ_SWCONFIG_TELNET_GET_CFG 4
#define I2IPC_REQ_SWCONFIG_TELNET_SET_CFG 5
#define I2IPC_REQ_SWCONFIG_SMBSEND_GET_CFG 6
#define I2IPC_REQ_SWCONFIG_SMBSEND_SET_CFG 7
#define I2IPC_REQ_SWCONFIG_CIMSERVER_GET_CFG 8
#define I2IPC_REQ_SWCONFIG_CIMSERVER_SET_CFG 9
#define I2IPC_REQ_SWCONFIG_WEBSERVER_GET_CURCFG 10
#define I2IPC_REQ_SWCONFIG_BONJOUR_GET_CFG 11
#define I2IPC_REQ_SWCONFIG_BONJOUR_SET_CFG 12
#define I2IPC_REQ_SWCONFIG_SSH_GET_CFG 13
#define I2IPC_REQ_SWCONFIG_SSH_SET_CFG 14
#define I2IPC_REQ_SWCONFIG_NTP_GET_CFG 15
#define I2IPC_REQ_SWCONFIG_NTP_SET_CFG 16
#define I2IPC_REQ_SWCONFIG_NTP_GET_SYNCSTATUS 17
#define I2IPC_REQ_SWCONFIG_NTP_SET_SYNCSTATUS 18



/* flash management */
#define I2IPC_REQ_GRP_FLASH_ID_COUNT 7
#define I2IPC_REQ_FLASH_INITIALIZE 0
#define I2IPC_REQ_FLASH_FINALIZE 1
#define I2IPC_REQ_FLASH_TRANSFER_IMG 2
#define I2IPC_REQ_FLASH_FLASH_IMG 3
#define I2IPC_REQ_FLASH_VERIFY_IMG 4
#define I2IPC_REQ_FLASH_GET_IMGHDR 5
#define I2IPC_REQ_FLASH_GET_PROGRESS 6

/*  system management */
#define I2IPC_REQ_GRP_SYSTEM_ID_COUNT 3
#define I2IPC_REQ_SHUTDOWN 0
#define I2IPC_REQ_MGMTPORT_SET 1
#define I2IPC_REQ_FILESYNC 2

/*  set debug option */
#define I2IPC_REQ_GRP_DEBUG_ID_COUNT 2
#define I2IPC_REQ_SET_FW_DEBUG_SETTING 0
#define I2IPC_REQ_SET_SW_DEBUG_SETTING 1

/* execute command */
#define I2IPC_REQ_GRP_EXECUTE_COUNT 2
#define I2IPC_REQ_EXECUTE_NTP 0
#define I2IPC_REQ_TEST_NTPSERVER 1
/* ups */
#define I2IPC_REQ_GRP_UPS_ID_COUNT 3
#define I2IPC_REQ_UPS_GET_STATUS 0
#define I2IPC_REQ_UPS_GET_CFG 1
#define I2IPC_REQ_UPS_SET_CFG 2

#define I2IPC_REQ_PARAMSIZE_FWBYPASS_IOCTL  PMIC_MAX_PMIC_SIZE

#define I2IPC_REQ_PARAMSIZE_DRIVER_IOCTL  PMIC_MAX_PMIC_SIZE

/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

#endif /*__PI_REQDEF_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: reqdef.h,v $
 * Revision 1.26.6.3  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.26.6.2  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.26.6.1  2009/03/23 11:51:23  xinw
 * add ups support
 *
 * Revision 1.26  2008/06/25 02:42:17  xinw
 * SW Serviceability Improvement
 *
 * Revision 1.25  2008/06/23 07:42:20  jackyl
 * add bonjour support
 *
 * Revision 1.24  2006/09/11 07:45:55  leync
 * add i2_startStopSlaveDaemon().
 *
 * Revision 1.23  2006/08/24 02:32:44  xinc
 * Support "Configuration Export" in CLI
 *
 * Revision 1.22  2006/08/22 22:07:27  xinw
 * add i2 call for file sync
 *
 * Revision 1.21  2006/04/26 08:04:03  danielz
 * Add a new request I2IPC_REQ_USERMGT_RESTORE_FACTORYDEFAULTS in user management
 * request group to restore factory defaults of user settings
 *
 * Revision 1.20  2006/04/15 19:01:46  xinw
 * add dual shutdown
 *
 * Revision 1.19  2006/03/31 04:50:22  leync
 * add cimom server setting feature in CLU
 *
 * Revision 1.18  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.17  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.16  2004/12/09 22:45:52  debinc
 * implement getEventStats for RAM in s/w
 *
 * Revision 1.15  2004/10/27 18:57:40  debinc
 * shutdown command support
 *
 * Revision 1.14  2004/09/16 01:39:33  debinc
 * telnet setting
 *
 * Revision 1.13  2004/07/09 23:42:10  debinc
 * add force logout
 *
 * Revision 1.12  2004/03/24 03:32:46  weny
 * I2 API porting
 *
 * Revision 1.11  2004/03/18 01:43:48  debinc
 * Modify snmp group to swconfig group
 *
 * Revision 1.10  2004/02/10 23:35:17  zhengj
 * flash support modification
 *
 * Revision 1.9  2003/12/18 01:32:54  debinc
 * import export APIs
 *
 * Revision 1.8  2003/12/03 22:24:11  debinc
 * support event filters
 *
 * Revision 1.7  2003/11/05 20:57:08  debinc
 * Add swmgt to CLI, I2, I2client
 *
 * Revision 1.6  2003/09/13 00:34:38  weny
 * config lock support
 *
 * Revision 1.5  2003/08/21 02:51:01  debinc
 * Add user management support
 *
 * Revision 1.4  2003/06/28 05:47:44  weny
 * add bga scheduler support
 *
 * Revision 1.3  2003/05/17 03:04:40  weny
 * Rewrite the event related request ids
 *
 * Revision 1.2  2003/03/22 00:52:42  weny
 * i2 ipc interface change - isolcate f/w data struct & cmd inside i2client.
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 ******************************************************************************/
