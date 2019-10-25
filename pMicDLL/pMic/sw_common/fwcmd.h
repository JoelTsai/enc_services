/*******************************************************************************
 * Filename    : fwcmd.h
 * Description : Firmware command information header file
 *               It provides the information about the firmware command, such as
 *			     which user privilege level is required, and whether lock is
 *				 required. 
 * Created on  : 03/28/03
 * CVS Version : $Id: fwcmd.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_FIRMWARECMD_H__
#define __PI_FIRMWARECMD_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "userdata.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */
typedef struct
{
    u16 fci_u16OpCode;
    u8 fci_u8UserPrivilege;
    boolean_t fci_bLockRequired;
    u32 fci_u32Reserved;
} firmware_command_info_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: fci_getFirmwareCommandInfo 
* Description: get the firmware command info according to the specified
*       firmware command op code.
* Parameters:
*       [in] u16OpCode, the firmware opcode
*       [out] pfci, the command info will be returned here
* Return: The possible values are:
*       PIERR_NO_ERROR - succeed,  the object is created.
*       PIERR_INVALID_PARAM - pfci is passed as NULL.
*   	PIERR_NOT_FOUND - the specified opcode is not found.
* Remarks: none.     
****************************************************************************/
u32 fci_getFirmwareCommandInfo(u16 u16OpCode, firmware_command_info_t * pfci);

#endif /*__PI_FIRMWARECMD_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: fwcmd.h,v $
 * Revision 1.3  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.2  2003/09/16 22:01:52  weny
 * make the structure 8 byte aligned
 *
 * Revision 1.1  2003/09/13 00:33:43  weny
 * move from i2 to common
 *
 * Revision 1.1  2003/04/02 00:25:00  weny
 * add the privilege and f/w lock info for some phase1 commands
 *
 ******************************************************************************/
