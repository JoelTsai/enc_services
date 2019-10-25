/*******************************************************************************
 * Filename    : hostinfo.h
 * Description : get host computer information header file.
 *
 * Created on  : 08/24/2006
 * CVS Version : $Id: hostinfo.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2005
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_HOSTINFO_H__
#define __PI_HOSTINFO_H__
#endif
/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"
#define MAX_NET_COUNT 16
#define MAX_IP_LENGTH 16
#define MAX_MAC_LENGTH 17
#define MAX_STRING_LENGTH 255
/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */
typedef struct
{
    u8 u8Name[MAX_STRING_LENGTH];	
    u8 u8IPAddress[MAX_IP_LENGTH];
    u8 u8MACAddress[MAX_MAC_LENGTH];
    u8 u8Reserved;
    u16 u16Flags;
    u16 u16Reserved[3];
} net_info_t;
typedef struct
{
    u8 u8HostName[MAX_STRING_LENGTH];	
    u8 u8OSName[MAX_STRING_LENGTH];
    u32 u32NetCount;
    net_info_t netInfo[MAX_NET_COUNT];
} host_info_t;
/* --- functional routines ------------------------------------------------- */
/***************************************************************************
* Function Name: getHostInfo 
* Description: get host info
* Parameters:    
*       [out] phi, the pointer to the host_info_t struct
* Return: PIERR_NO_ERROR: succeed, otherwise: fail.
* Remarks: This function only can be called on in-band mode 
****************************************************************************/
u32 getHostInfo(host_info_t *phi);/*******************************************************************************
 * Change Log
 *
 * $Log: hostinfo.h,v $
 * Revision 1.3  2007/09/19 06:12:32  michaell
 * bug fix 15086
 *
 * Revision 1.2  2006/08/25 02:36:02  xinc
 * Fix header and footer format
 *
 ******************************************************************************/
 

