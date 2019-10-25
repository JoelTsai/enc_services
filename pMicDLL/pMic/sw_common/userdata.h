/*******************************************************************************
 * Filename    : userdata.h
 * Description : user data header file
 *               * Shared user information data strcture
 * Created on  : 08/19/03
 * CVS Version : $Id: userdata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __USERDATA_H__
#define __USERDATA_H__

#include "pibasic.h"
#include "events.h"

/* --- constants & data structures ------------------------------------------ */

/* user group id */
#define USER_GROUP_NONE        0  /* When a user belongs to this group, it means the username have been removed */
#define USER_GROUP_USER        1  /* view only */
#define USER_GROUP_MAINTENANCE 2  /* hot spare, bg activity and view */
#define USER_GROUP_POWER       3  /* create configuration, and maintenance */
#define USER_GROUP_SUPER       4  /* full access */

/* for user management */
#define USERDB_FILE_NAME "userdb.xml"

#define MAX_NUM_USER	16
#define MAX_USER_NAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 32
#define MAX_FULL_NAME_LENGTH 40
#define MAX_EMAIL_LENGTH 48
#define MAX_NUM_EVENTID_FILTER 16
typedef struct
{
    //classtype starts from 0
    u8 ef_u32eventSevClassFilter[EVT_MAX_CLASSES];
    u16 ef_u16numEventIDFilter;
    boolean_t efl_enabled;
    u8  ef_u8Reserved[5];
    u32 ef_u32eventIDFilter[(MAX_NUM_EVENTID_FILTER/8+1)*8];
} event_filters_t;

typedef struct
{
    event_filters_t up_eflEventFilters;
} user_preference_t;

#define MAX_ENCRYPT_PASSWORD_LENGTH (MAX_PASSWORD_LENGTH*3+1)
typedef struct
{   
    u8 ui_u8Username[MAX_USER_NAME_LENGTH];
    u8 ui_u8Fullname[MAX_FULL_NAME_LENGTH];
    u8 ui_u8Password[MAX_PASSWORD_LENGTH];
    u8 ui_u8PwdEncrypted[(MAX_ENCRYPT_PASSWORD_LENGTH/8+1)*8];
    u8 ui_u8Email[MAX_EMAIL_LENGTH];
    u8 ui_u8UserGroupId;
    boolean_t ui_bEnable;
    u8 ui_u8Reserved[6];
    event_filters_t up_eflEventFilters;
} user_info_t;

typedef struct
{   
    u8 ul_u8NumUser;
    u8 ul_u8Reserved[7];
    user_info_t ul_tUser[MAX_NUM_USER];
} user_list_t;

#endif /* __USERDATA_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: userdata.h,v $
 * Revision 1.18  2006/03/14 23:48:38  debinc
 * remove unused
 *
 * Revision 1.17  2006/03/13 10:22:56  JudithLi
 * add new netsend function
 *
 * Revision 1.16  2005/03/22 21:49:48  debinc
 * update event_filter data strcuture
 *
 * Revision 1.15  2004/08/25 18:39:59  debinc
 * add common sw-conf define
 *
 * Revision 1.14  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.13  2004/07/06 21:32:44  debinc
 * 8 byte aligned
 *
 * Revision 1.12  2004/06/12 00:59:14  debinc
 * move setting save/restore data structure out of API code
 *
 * Revision 1.11  2004/06/10 18:03:18  debinc
 * Add some reserved byte to make 8-byte aligned
 *
 * Revision 1.10  2004/04/14 02:22:30  debinc
 * use a new #define of MAX_ENCRYPT_PASSWORD_LENGTH
 *
 * Revision 1.9  2004/04/06 22:40:29  debinc
 * *** empty log message ***
 *
 *******************************************************************************/



