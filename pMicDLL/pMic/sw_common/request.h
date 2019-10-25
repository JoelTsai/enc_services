/*******************************************************************************
 * Filename    : request.h
 * Description : Request header file
 *               * It provides the external definition of the I2 IPC request
 *                 and the related routines and data structures. 
 *               * This file will be shared among I2 and I2 Client library.
 * Created on  : 01/27/03
 * CVS Version : $Id: request.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_REQUEST_H__
#define __PI_REQUEST_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "reqdata.h"

/* --- constant definitions ------------------------------------------------ */

/* request groups */
#define REQ_GRP_COUNT    7

#define REQ_GRP_SUBSYSTEM 0
#define REQ_GRP_CONTROLLER 1
#define REQ_GRP_PHYDRV 2
#define REQ_GRP_LOGDRV 3
#define REQ_GRP_STORPOOL 4
/*#define REQ_GRP_BGACTIVITY 10*/      /* ? */
#define REQ_GRP_EVENT 20
#define REQ_GRP_SESSION 100        /* login and logout */
/*#define REQ_GRP_USERMGT 101*/        /* user management */

/* request of subsystem */
#define REQ_SUBSYSTEM_COUNT 1
#define REQ_SUBSYSTEM_GETINFO 0

/* request of controller */
#define REQ_CONTROLLER_COUNT 4
#define REQ_CONTROLLER_GETINFO 0
#define REQ_CONTROLLER_GETSETTING 1
#define REQ_CONTROLLER_SETSETTING 2
#define REQ_CONTROLLER_GETCOUNT 3

/* request of physical drive */
#define REQ_PHYDRV_COUNT 4
#define REQ_PHYDRV_GETINFO 0
#define REQ_PHYDRV_GETSETTING 1
#define REQ_PHYDRV_SETSETTING 2
#define REQ_PHYDRV_GETCOUNT 3

/* request of logical drive */
#define REQ_LOGDRV_COUNT 4
#define REQ_LOGDRV_GETINFO 0
#define REQ_LOGDRV_GETSETTING 1
#define REQ_LOGDRV_SETSETTING 2
#define REQ_LOGDRV_GETCOUNT 3

/* request of storage pool */
#define REQ_STORPOOL_COUNT 4
#define REQ_STORPOOL_GETINFO 0
#define REQ_STORPOOL_GETSETTING 1
#define REQ_STORPOOL_SETSETTING 2
#define REQ_STORPOOL_GETCOUNT 3

/* request of event */
#define REQ_EVENT_COUNT 4
#define REQ_EVENT_GETINFO 0
#define REQ_EVENT_SUBSCRIBE 1
#define REQ_EVENT_UNSUBSCRIBE 2
#define REQ_EVENT_GETCOUNT 3

/* request of session */
#define REQ_SESSION_COUNT 2
#define REQ_SESSION_LOGIN 0
#define REQ_SESSION_LOGOUT 1

/* --- data structures ----------------------------------------------------- */

/* request */
typedef struct
{
    __u32 r_u32SessionId;
    __u8 r_u8RequestGroupId;
    __u8 r_u8RequestId;
	__u8 r_u8Reserved[2];
    __u32 *r_pu32Status;
    __u32 *r_pu32SizeParam;
    __u32 *r_pu32DataSize;
    __u32 *r_pu32ReturnDataSize;
    __u8 *r_pu8Param;
    __u8 *r_pu8Data;
} request_t;

/* --- functional routines ------------------------------------------------- */

#endif /*__PI_REQUEST_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: request.h,v $
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
