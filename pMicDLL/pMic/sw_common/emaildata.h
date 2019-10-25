/*******************************************************************************
 * Filename    : emaildata.h
 * Description : email data header file
 *               * Shared email related data strcture
 * Created on  : 12/01/03
 * CVS Version : $Id: emaildata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __EMAILDATA_H__
#define __EMAILDATA_H__

#include "pibasic.h"
#include "userdata.h"

#define EVENT_FILTER_TYPE_SEV_CLASS 1
#define EVENT_FILTER_TYPE_EVT_ID 2

#define EVT_SEVERITY_NONE                        0xFF
#define EVT_SEVERITY_MIN                        0x2
#define EVT_SEVERITY_MAX                        0x7

#define EMAIL_AUTH_LOGIN                        0x1
#define EMAIL_AUTH_PLAIN                        0x2
#define EMAIL_AUTH_NONE                         0x3
#define EMAIL_AUTH_AUTO                         0x4

#define EMAIL_MAX_SUBJECT_LENGTH                128


typedef struct
{
    u8 es_u8SMTPHost[16];
    u32 es_u32SMTPPort;
    u8 es_u8AthuMethod;
    boolean_t es_bSetByUser;
    u8 es_u8Reserved1[2];
    u8 es_u8AthuUser[MAX_USER_NAME_LENGTH];
    u8 es_u8AthuPassword[MAX_PASSWORD_LENGTH];
    u8 es_u8From[MAX_EMAIL_LENGTH];
    u8 es_u8Subject[EMAIL_MAX_SUBJECT_LENGTH];
    u8 es_u8Reserved2[64];
} email_config_t;

#endif /* __EMAILDATA_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: emaildata.h,v $
 * Revision 1.9  2005/08/18 18:27:13  debinc
 * Change SMTP authentication
 *
 * Revision 1.8  2004/08/06 21:38:58  debinc
 * create email_setting_t
 *
 * Revision 1.7  2004/08/05 19:02:21  debinc
 * version stamp setting file
 *
 * Revision 1.6  2004/06/28 23:42:03  debinc
 * move from common to email
 *
 * Revision 1.5  2004/06/10 18:03:18  debinc
 * Add some reserved byte to make 8-byte aligned
 *
 * Revision 1.4  2004/04/06 22:39:48  debinc
 * *** empty log message ***
 *
 ******************************************************************************/



