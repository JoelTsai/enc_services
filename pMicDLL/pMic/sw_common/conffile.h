/*******************************************************************************
 * Filename    : conffile.h
 * Description : configuration file header file
 *               * reads the options in a configuration file
 *               * an example of the configuration file
 *                 --------------------------------------------------------
 *                 |# this is an exmaple of the configuration file        |
 *                 |optiontagname1=value1 # this is an example of option  |
 *                 |optiontagname2=value2                                 |
 *                 |                                                      |
 *                 |# the end of the configuration file                   |
 *                 --------------------------------------------------------
 *               * it is NOT thread safe. The caller should provide synchronization
 *                 for the array if necessary
 * Created on  : 03/07/2003
 * CVS Version : $Id: conffile.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_CONFFILE_H__
#define __PI_CONFFILE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions ------------------------------------------------ */

#define MAX_CONFFILE_LINE_LENGTH 255

/* --- data structures ----------------------------------------------------- */

typedef void conf_file_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: createConfFile 
* Description: create a configuration file object according to the file path.
* Parameters:    
*       [out] ppcf, the configuration file object to be created and returned.
*       [in] pstrPath, the path to the configuraiton file
* Return: The funciton completion error code. PIERR_NO_ERROR: succeeded, 
*       otherwise: failed
* Remarks: None.     
****************************************************************************/
__u32 createConfFile(conf_file_t ** ppcf, const char * pstrPath);

/**************************************************************************
* Function Name: destroyConfFile 
* Description: destroy the configuration file object.
* Parameters:    
*       [in/out] ppcf, the configuration file object to be destroyed. After 
*           destruction, it will be set to NULL.
* Return: The funciton completion error code. PIERR_NO_ERROR: succeeded, 
*       otherwise: failed
* Remarks: createConfFile should be called before this one is called.     
****************************************************************************/
__u32 destroyConfFile(conf_file_t ** ppcf);

/**************************************************************************
* Function Name: getConfFileInt 
* Description: get an integer type option from the configuration file.
*       If the pcf is set to NULL, or the option is not found, the default
*       value will be returned.
* Parameters:    
*       [in] pcf, the configuration file object.
*       [in] pstrTag, the option tag name.
*       [in] nDefault, the default value of the option.
*       [out] pnValue, the option value will be return to it.
* Return: The funciton completion error code. PIERR_NO_ERROR: succeeded, 
*       otherwise: failed
* Remarks: None.     
****************************************************************************/
__u32 getConfFileInt(conf_file_t * pcf, 
    const char * pstrTag, int nDefault, int * pnValue);

/**************************************************************************
* Function Name: getConfFileString 
* Description: get an string type option from the configuration file.
*       If the pcf is set to NULL, or the option is not found, the default
*       value will be returned.
* Parameters:    
*       [in] pcf, the configuration file object.
*       [in] pstrTag, the option tag name.
*       [in] pstrDefault, the default value of the option.
*       [out] pstrValueBuf, the option value will be return to it.
*       [in] u32BufSize, the size of the pstrValueBuf.
* Return: The funciton completion error code. PIERR_NO_ERROR: succeeded, 
*       otherwise: failed
* Remarks: None.     
****************************************************************************/
__u32 getConfFileString(conf_file_t * pcf,
    const char * pstrTag, const char * pstrDefault, 
    char * pstrValueBuf, __u32 u32BufSize);

#endif /*__PI_CONFFILE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: conffile.h,v $
 * Revision 1.1  2003/03/08 04:13:35  weny
 * Added for conf file support of cim provider.
 *
 *
 ******************************************************************************/
