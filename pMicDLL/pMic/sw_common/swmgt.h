/*******************************************************************************
 * Filename    : swmgt.h
 * Description : sw component management header file
 *               Shared swmgt data strcture
 * Created on  : 10/23/03
 * CVS Version : $Id: swmgt.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __SWMGT_H__
#define __SWMGT_H__

#include "pibasic.h"

#define DAEMON_EMAIL "Email"
#define DAEMON_TELNET "Telnet"
#define DAEMON_SSH "SSH"
#define DAEMON_WEBSERVER "Webserver"
#define DAEMON_SLP "SLP"
#define DAEMON_SNMP "SNMP"
#define DAEMON_CIM "CIM"
#define DAEMON_NETSEND "Netsend"
#define DAEMON_BONJOUR "Bonjour"

#define MAX_NUM_DAEMON 24
#define MAX_DAEMON_NAME_LEN 16
#define MAX_DAEMON_PARAM_LEN 128

#define DAEMON_NOACTION 0
#define DAEMON_STARTED 1
#define DAEMON_STOPPED 2
#define DAEMON_RESTART 3
#define DAEMON_ERROR_STATE 4

#define DAEMON_STARTTYPE_AUTO 1
#define DAEMON_STARTTYPE_MANUAL 2

#define DAEMON_MONITOR_POLLING 1
#define DAEMON_MONITOR_HEARTBEAT 2

#define DAEMON_INTERNAL 1
#define DAEMON_USER 2

#define DAEMON_HEALTHY 1
#define DAEMON_SICK 0

#define SWMGT_FILE_PATH "/var/run/swmgt.pid"

/* for internal sw management */
typedef struct
{   
    u8 sds_u8DaemonName[MAX_DAEMON_NAME_LEN];
    u8 sds_u8DaemonStatus;
    u8 sds_u8DaemonStartupType;
    u8 sds_u8DaemonInternal;
    u8 sds_u8DaemonHeartbeat;
    u8 sds_u8Reserved[4];
    u8 sds_u8DaemonCmdPath[MAX_PATH_LENGTH+1];
    u8 sds_u8DaemonCmd[MAX_DAEMON_NAME_LEN];
    u8 sds_u8DaemonParam[MAX_DAEMON_PARAM_LEN];
    u8 sds_u8Reserved2[8*2];
} swmgt_daemon_setting_t;

typedef struct
{   
    u8 ss_u8NumDaemon;
    u8 ss_u8PollingInterval;
    u8 ss_u8HeartbeatInterval;
    u8 ss_u8Reserved;
    u32 ss_u32SockPort;
    swmgt_daemon_setting_t ss_tDaemon[MAX_NUM_DAEMON];
    u32 ss_u32DaemonTimeStamp[MAX_NUM_DAEMON];
    u8 ss_u8DaemonHealth[MAX_NUM_DAEMON];
    u8 ss_u8Version[8];
} swmgt_setting_t;

/* external API use */
typedef struct
{
    u8 sdi_u8DaemonName[MAX_DAEMON_NAME_LEN];
    u8 sdi_u8DaemonStatus;
    u8 sdi_u8DaemonStartupType;
    u8 sdi_u8Reserved[6];
} swmgt_daemon_info_t;

/***************************************************************************
* Function Name: syncByLock
* Description:  Enter critical section by locking a file
* Parameters: [out] pFd, the pointer to the file descriptor.
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 syncByLock(int * pFd);
/***************************************************************************
* Function Name: syncByUnLock
* Description:  Leave critical section by unlocking a file
* Parameters: [in] pFd, the pointer to the file descriptor.
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 syncByUnLock(int * pFd); 
/***************************************************************************
* Function Name: getDaemonStatus
* Description:  get daemons' status from a saved file, it is not current
*               running status
* Parameters: [out] pss, the pointer to the daemon's setting.
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 getDaemonStatus(swmgt_setting_t * pss);
/***************************************************************************
* Function Name: swmgt_setDaemonStartupType
* Description:  set daemons' startup type to a file in flash
* Parameters: [in] pDaemonName, daemon name
*             [in] daemonStartupType, startup type
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 swmgt_setDaemonStartupType(u8 * pDaemonName, u8 daemonStartupType);
/***************************************************************************
* Function Name: swmgt_startStopDaemon
* Description:  action of start/stop a daemon
* Parameters: [in] pDaemonName, daemon name
*             [in] daemonStatus, start/stop
*             [in] bMode, blocking or non-blocking restart
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 swmgt_startStopDaemon(u8 * pDaemonName, u8 daemonStatus, boolean_t bMode);
/***************************************************************************
* Function Name: swmgt_getAllDaemonsInfo
* Description:  get all daemon's info
* Parameters: [out] pDaemonInfo, list if daemon info
* Return: success/fail
* Remarks: none.
****************************************************************************/
u32 swmgt_getAllDaemonsInfo(swmgt_setting_t * pDaemonInfo);

#endif /* __SWMGT_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: swmgt.h,v $
 * Revision 1.18.6.1  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.18  2008/06/23 07:42:20  jackyl
 * add bonjour support
 *
 * Revision 1.17  2006/12/08 06:06:38  theoz
 * SWMGT improvement
 *
 * Revision 1.16  2006/11/30 08:31:13  theoz
 * swmgt improvement and test for windows
 *
 * Revision 1.15  2006/09/11 02:06:47  weny
 * make swmgt_setting_t attributes name consistent
 *
 * Revision 1.14  2006/04/06 04:45:31  JudithLi
 * SR3 change to Main tree
 *
 * Revision 1.13  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.12  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.11  2005/03/24 20:31:14  debinc
 * use captial case dameon name
 *
 * Revision 1.10  2005/03/19 00:33:51  debinc
 * change swmgt startstop to support non-blocking restart
 *
 * Revision 1.9  2005/02/01 19:25:35  debinc
 * 8-byte aligned
 *
 * Revision 1.8  2004/11/16 00:25:16  debinc
 * add function to sync "ps -C".
 *
 * Revision 1.7  2004/08/05 19:02:21  debinc
 * version stamp setting file
 *
 * Revision 1.6  2004/06/10 18:03:18  debinc
 * Add some reserved byte to make 8-byte aligned
 *
 * Revision 1.5  2004/04/06 22:40:19  debinc
 * *** empty log message ***
 *
 *******************************************************************************/



