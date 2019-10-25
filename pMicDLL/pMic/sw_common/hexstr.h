/*******************************************************************************
 * Filename    : hexstr.h
 * Description : Hex String header file
 *				 provide some functional routine to dump hex logs
 * Created on  : 03/11/2003
 * CVS Version : $Id: hexstr.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_HEXSTRING_H__
#define __PI_HEXSTRING_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: getByteHexString 
* Description: converte the data buffer into byte hex string, starting from
*       the giving index.
* Parameters:    
*       [in] pu8Data, the data buffer
*       [in] u32DataLen, the length of the data buffer in bytes
*       [in] u32StartIndex, the start index of the data
*       [out] pstrHex, the hex string will be returned here
*       [in] u32StrSize, the size of the hex string in characters
* Return: the number of bytes converted to hex string
* Remarks: None.     
****************************************************************************/
u32 getByteHexString(u8 * pu8Data, u32 u32DataLen, u32 u32StartIndex, 
    char * pstrHex, u32 u32StrSize);

/**************************************************************************
* Function Name: getWordHexString 
* Description: converte the data buffer into word hex string, starting from
*       the giving index.
* Parameters:    
*       [in] pu16Data, the data buffer
*       [in] u32DataLen, the length of the data buffer in words
*       [in] u32StartIndex, the start index of the data
*       [out] pstrHex, the hex string will be returned here
*       [in] u32StrSize, the size of the hex string in characters
* Return: the number of words converted to hex string
* Remarks: None.     
****************************************************************************/
u32 getWordHexString(u16 * pu16Data, u32 u32DataLen, u32 u32StartIndex, 
    char * pstrHex, u32 u32StrSize);

#endif /*__PI_HEXSTRING_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: hexstr.h,v $
 * Revision 1.1  2003/03/11 23:57:15  weny
 * add hexstr for error_handler_t::logDataMsg
 *
 *
 ******************************************************************************/
