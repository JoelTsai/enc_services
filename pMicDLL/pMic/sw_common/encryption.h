/*******************************************************************************
 * Filename    : encryption.h
 * Description : encryption/decryption header file
 *               It provides fucntions to en/decrypt text file and string.
 * Created on  : 12/09/03
 * CVS Version : $Id: encryption.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_ENCRYPTION_H__
#define __PI_ENCRYPTION_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- data structures ----------------------------------------------------- */


/* --- functional routines ------------------------------------------------- */
/***************************************************************************
* Function Name: encryptTextFile
* Description:  encrypt a text file
* Parameters: [in] pSrcFile, file to be encrypted
*             [in] pDesFile, generated encrypted file
*             [in] pKey, encryption key
*             [in] keyLenght, the length of pKey array. Must >= 8. But only first
*                             7 bytes are used
* Return:  success/fail
* Remarks: none.
****************************************************************************/
u32 encryptTextFile(char * pSrcFile, char * pDesFile, char * pKey);

/***************************************************************************
* Function Name: decryptTextFile
* Description:  decrypt to generate a  text file
* Parameters: [in] pSrcFile, file to be decrypted
*             [in] pDesFile, generated decrypted file
*             [in] pKey, encryption key
*             [in] keyLenght, the length of pKey array. Must >= 8. But only first
*                             7 bytes are used
* Return:  success/fail
* Remarks: none.
****************************************************************************/
u32 decryptTextFile(char * pSrcFile, char * pDesFile, char * pKey);
/***************************************************************************
* Function Name: encryptString
* Description:  encrypt a string, the encrypted string is convert to another string
* Parameters: [in] pSrcStr, string to be encrypted
*             [out] pDesStr, generated encrypted string
*             [in] desStrSize, size of the buffer to hold encrypted string
*                               if ( strlen(pSrcStr)+1) is 8 byte aligned
*                                   desStrSize > 3*( (strlen(pSrcStr)+1)
*                               else
*                                   desStrSize > 3*(((strlen(pSrcStr)+1)/8+1)*8)
*             [in] pKey, encryption key
*             [in] keyLenght, the length of pKey array. Must >= 8. But only first
*                             7 bytes are used
* Return:  success/fail
* Remarks: none.
****************************************************************************/
u32 encryptString(const unsigned char * pSrcStr, unsigned char * pDesStr, int desStrSize,
        unsigned char * pKey);
/***************************************************************************
* Function Name: decryptString
* Description:  decrypt to generate original string
* Parameters: [in] pSrcStr, string to be decrypted
*             [out] pDesStr, generated original string
*             [in] desStrSize, size of the buffer to hold decrypted string
*                               if ( strlen(originalString)+1) is 8 byte aligned
*                                   desStrSize >= strlen(originalString)+1
*                               else
*                                   desStrSize >= ((strlen(originalString)+1)/8+1)*8
*             [in] pKey, encryption key
*             [in] keyLenght, the length of pKey array. Must >= 8. But only first
*                             7 bytes are used
* Return:  success/fail
* Remarks: none.
****************************************************************************/
u32 decryptString(const unsigned char * pSrcStr, unsigned char * pDesStr, int desStrSize,
        unsigned char * pKey);
#endif /*__PI_ENCRYPTION_H__*/

