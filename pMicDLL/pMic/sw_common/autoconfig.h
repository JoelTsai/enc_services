/*******************************************************************************
 * Filename    : autoconfig.h
 * Description : configuration automation header file
 * Created on  : 07/21/03
 * CVS Version : $Id: autoconfig.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_AUTOCONFIG_H__
#define __PI_AUTOCONFIG_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "i2types.h"

/* --- constant definitions ------------------------------------------------ */

#define APP_FILE_SERVER         1
#define APP_VIDEO_STREAM        2
#define APP_TRANSACTION_DATA    3
#define APP_TRANSACTION_LOG     4
#define APP_OTHER               5

#define INVALID_LOGDRV_NUM      0xFFFF

/* --- data structures ----------------------------------------------------- */

typedef struct pd_list
{
    u16 pl_u16NumFreePD;
    u32 pl_u32PdIdList[MAX_PHYSICAL_DRIVES];
    u16 pl_u16DriveType[MAX_PHYSICAL_DRIVES];
    u64 pl_u64PdSizeList[MAX_PHYSICAL_DRIVES];
    u8 pl_u8DriveSpeed[MAX_PHYSICAL_DRIVES];
    u16 pl_u16EnclosureId[MAX_PHYSICAL_DRIVES];
} pd_list_t;

typedef struct config_data
{
    req_param_spare_add_t cd_rpsa;
    u32 cd_u32NumOfArrays;
    req_param_array_add_t cd_rpaa[1];
} config_data_t;

typedef struct array_config_param
{
    u16 acp_u16NumFreePD;
    u16 acp_u16NumExistDA;
    u16 acp_u16NumExistLD;
    u32 acp_u32PdIdList[MAX_PHYSICAL_DRIVES];
    u16 acp_u16DriveType[MAX_PHYSICAL_DRIVES];
    u64 acp_u64PdSizeList[MAX_PHYSICAL_DRIVES];
    u8 acp_u8DriveSpeed[MAX_PHYSICAL_DRIVES];
    u16 acp_u16EnclosureId[MAX_PHYSICAL_DRIVES];
    feature_bits_t acp_fbFeatureBits;
    firmware_capabilities_t acp_fcFwCapabilities;
} array_config_param_t;

typedef struct array_auto_param
{
    u8 aap_u8Action;
    boolean_t aap_bRedundancy;
    boolean_t aap_bPerformance;
    boolean_t aap_bCapacity;
    boolean_t aap_bSpare;
    boolean_t aap_bMixingDriveType;
    u8 aap_bReserved[6];
    u16 aap_u16Application;
    u16 aap_u16NumConfigLD;
} array_auto_param_t;

/* --- function declarations ---------------------------------------------- */

/******************************************************************************
 * Function Name: setDefaultParamArrayAutomation
 * Description: set the default parameters for array configuration automation
 *
 * Parameters:
 * 	[in] paap, pointer to array_auto_param_t
 * Return: NONE
 * Remarks: NONE
 * ***************************************************************************/
void setDefaultParamArrayAutomation(array_auto_param_t * paap);
/******************************************************************************
 * Function Name: expr_configArray
 * Description: array configuration automation: express option
 *
 * Parameters:
 * 	[in] pacp, pointer to array_config_param_t
 * 	[in] paap, pointer to array_auto_param_t
 * 	[in] pDataBuf, pointer to software buffer
 * 	[in] u32BufLen, software buffer length
 * Return: Error Code
 * Remarks: The caller should provide pDataBuf with sufficient length
 * ***************************************************************************/
u32 expr_configArray(array_config_param_t * pacp, 
		     array_auto_param_t * paap,
                     u8 * pDataBuf,
                     u32 u32BufLen);
/******************************************************************************
 * Function Name: auto_configArray
 * Description: array configuration automation: automatic option
 *
 * Parameters:
 * 	[in] pacp, pointer to array_config_param_t
 * 	[in] pDataBuf, pointer to software buffer
 * 	[in] u32BufLen, software buffer length
 * Return: Error Code
 * Remarks: The caller should provide pDataBuf with sufficient length
 * ***************************************************************************/
u32 auto_configArray(array_config_param_t * pacp, 
                     u8 * pDataBuf,
                     u32 u32BufLen);

#endif
/*******************************************************************************
 * Change Log
 *
 * $Log: autoconfig.h,v $
 * Revision 1.6  2006/07/03 10:17:13  danielz
 * Add 3 fields for the drive's type, speed, location. Add a new option to
 * allow mixing drive type (SATA/SAS) or not
 *
 * Revision 1.5  2005/12/08 04:30:05  weny
 * use feature bits and fw capabilities
 *
 * Revision 1.4  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.3  2003/09/12 16:33:24  zhengj
 * added data structure for config data buffer
 *
 * Revision 1.2  2003/08/08 22:41:41  zhengj
 * added support for array setting and info and others ..
 *
 * Revision 1.1  2003/07/31 18:32:22  zhengj
 * initial revision for autoconfig.h
 *
 ******************************************************************************/
