/*******************************************************************************
 * Filename    : oemfile.h
 *
 * (C) Copyright Promise Technology Inc., 2005
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_OEMFILE_H__
#define __PI_OEMFILE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */
typedef struct
{
    u8 dc_u8IscsiNodeName[256];	
} default_cus_t;

/* --- functional routines ------------------------------------------------- */
/***************************************************************************
* Function Name: oem_getDefaultValue 
* Description: get the default iscsi node name from OEM xml file.
* Parameters:    
*       [out] pdc, default value reading from xml file will return. 
*           number string will return
*       [in] pdc, the pointer to the default value structure.
* Return: None. 
* Remarks: This function will be extensioned later to support more customization default value. 
****************************************************************************/
u32 oem_getDefaultValue(default_cus_t * pdc);
/***************************************************************************
* Function Name: oem_getEnclType 
* Description: get enclosure type from xml file.
* Parameters:    
*       [out] None
*       [in] u8EnclType, get from firmware,represents to the enclosure type.
* Return: char, pointer to enclosure type.
* Remarks: This function will read xml file only once,then store the enclosure type in a global 
                 variable. 
****************************************************************************/
const char * oem_getEnclosureType(u8 u8EnclType, u16 u16CtrlType);
const char * oem_getEnclType(u8 u8EnclType );

u32  initOemLib(char *pName);

#endif /*__PI_OEMFILE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: oemfile.h,v $
 * Revision 1.4.40.1  2008/10/10 03:00:50  xinw
 * add oem_getEnclosureType to replace oem_getEnclType
 *
 * Revision 1.4  2007/02/08 07:10:02  danielz
 * change the size of array dc_u8IscsiNodeName to 256 byte for 8-byte alignment
 *
 * Revision 1.3  2007/01/05 09:14:09  theoz
 * bug fix 12487
 *
 * Revision 1.2  2005/08/25 11:08:04  leync
 * get rid of compile warning.
 *
 * Revision 1.1  2005/08/25 09:47:44  leync
 * Phase1 debut.
 *
 *
 ******************************************************************************/

