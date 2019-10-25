/*******************************************************************************
 * Filename    : sessdata.h
 * Description : sesssion data header file
 *               * Shared session information data strcture
 * Created on  : 07/20/04
 * CVS Version : $Id: sessdata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2004 - 2004
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __PR_SESSION_DATA_H__
#define __PR_SESSION_DATA_H__

#include "pibasic.h"
#include "userdata.h"

/* --- constants & data structures ------------------------------------------ */

#define MAX_SESSION_INTERFACE_LENGTH 16

#define MAX_SESSION_INTERFACES 16
/* These three are internal, string comes from swmgt.xml */
#define INTERFACE_SNMP "snmp"
#define INTERFACE_EMAIL "email"
#define INTERFACE_SMBSEND "netsend"
#define INTERFACE_BGASCHED "bgasched"
/* telnet is passed by telnetd */
#define INTERFACE_TELNET "telnet"
/* sshd is passed by ssh server */
#define INTERFACE_SSH "ssh"
/* RS232 is passed from start script */
#define INTERFACE_RS232 "rs232"
#define INTERFACE_FW "fw"
/* CLI default to be INBAND */
#define INTERFACE_INBANDCLI "inband"
#define INTERFACE_HTTP "www"
#define INTERFACE_CIM "cim"
#define INTERFACE_SLPASSISTANT "slpa"

#define INTERFACE_MANGLER "mangler"
#define INTERFACE_UPSD "upsd"
#define INTERFACE_NTP "ntp"

typedef struct
{   
    time_t s_tLoginTimeStamp;
    time_t s_tLogoutTimeStamp;
    u8 s_u8Username[MAX_USER_NAME_LENGTH];
    u8 s_u8SessionInterface[MAX_SESSION_INTERFACE_LENGTH];
    u32 s_u32Inactivity;
    u32 s_u32SessionId;
    u8 s_u8UserGroupId;
    u8 s_u8InternalReserved[15]; /* reserved for internal use */
} session_info_t;

#endif /* __PR_SESSION_DATA_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: sessdata.h,v $
 * Revision 1.7.42.4  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.7.42.3  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.7.42.2  2009/05/20 07:49:26  xinw
 * add fw interface for cli
 *
 * Revision 1.7.42.1  2009/03/23 11:51:37  xinw
 * add ups support
 *
 * Revision 1.7  2006/04/06 04:45:31  JudithLi
 * SR3 change to Main tree
 *
 * Revision 1.6  2006/04/05 04:15:02  david.chiu
 * Added network mangler
 *
 * Revision 1.5  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.4  2005/03/26 01:16:58  debinc
 * increase session_interface length
 *
 * Revision 1.3  2004/11/01 19:05:28  debinc
 * add SLP login
 *
 * Revision 1.2  2004/07/26 21:28:18  debinc
 * update defintion
 *
 * Revision 1.1  2004/07/20 20:57:45  weny
 * I2 API clean up
 *
 *******************************************************************************/



