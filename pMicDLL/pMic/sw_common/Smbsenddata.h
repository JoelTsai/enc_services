/*******************************************************************************
 * Filename    : Smbsenddata.h
 * Description : Smbsend data header file
 * Created on  : 02/14/06
 * CVS Version : $Id: Smbsenddata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2006
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __SMBSENDDATA_H__
#define __SMBSENDDATA_H__

#include "pibasic.h"
#include "userdata.h"

#define EVENT_FILTER_TYPE_SEV_CLASS 1
#define EVENT_FILTER_TYPE_EVT_ID 2

#define EVT_SEVERITY_NONE                        0xFF
#define EVT_SEVERITY_MIN                        0x2
#define EVT_SEVERITY_MAX                        0x7

#define SMBSEND_AUTH_LOGIN                        0x1
#define SMBSEND_AUTH_PLAIN                        0x2
#define SMBSEND_AUTH_NONE                         0x3
#define SMBSEND_AUTH_AUTO                         0x4

#define SMBSEND_MAX_SUBJECT_LENGTH                128


typedef struct
{
    u8 sc_u8recipient[32];
    u8 sc_u8EventSeverity;
    u8 sc_u8Reserved[7];
} Smbsend_config_t;

#endif /* __SMBSENDDATA_H__ */
