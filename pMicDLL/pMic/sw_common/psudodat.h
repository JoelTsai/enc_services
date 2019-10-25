/*******************************************************************************
 * Filename    : pusdodat.h
 * Description : Psudo Data header file
 *               It provides routines to set the psudo data.
 * Created on  : 03/12/2003
 * CVS Version : $Id: psudodat.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifdef PSUDO_CODE

#ifndef __PI_PSUDODATA_H__
#define __PI_PSUDODATA_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "reqdata.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

/******************************************************************************
* Function Name Prototype: psudo_set<element>Info 
* Description: set psudo data of the information of the manageable element.
* Parameters:
*       [in] pParam, the pointer the get info parameter, if applicable
*   	[out] pData, the pointer to the data buffer where the psudo data will 
*           be returned.
*       [in/out] pu32DataSize, the size of the data buffer as in param; the
*           length of the returned data as out param. This parameters is
*           applicable for the info with variable length.
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: none.     
*******************************************************************************/
u32 psudo_setSubsystemInfo(req_data_subsys_info_t * pData);
u32 psudo_setControllerInfo(req_param_ctrl_info_t * pParam, 
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setPhysicalDriveInfo(req_param_phydrv_info_t * pParam, 
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setLogicalDriveInfo(req_param_logdrv_info_t * pParam, 
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setLogicalDriveInfo(req_param_logdrv_info_t * pParam, 
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setDiskArrayConfig(req_param_array_cfg_t * pParam,
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setSpareInfo(req_param_spare_info_t * pParam,
    u8 * pData, u32 * pu32DataSize);
u32 psudo_setMediaPatrolStatus(u8 * pData, u32 * pu32DataSize);

#endif /*__PI_PSUDODATA_H__*/
#endif /* PSUDO_CODE */

/*******************************************************************************
 * Change Log
 *
 * $Log: psudodat.h,v $
 * Revision 1.5  2003/06/04 02:29:33  weny
 * pool to disk array
 *
 * Revision 1.4  2003/04/08 23:28:15  weny
 * changes in param of add storpool and addld storpool
 *
 * Revision 1.3  2003/03/27 20:12:24  weny
 * add support for storpool and spare
 *
 * Revision 1.2  2003/03/14 20:00:51  weny
 * add more psudo support
 *
 * Revision 1.1  2003/03/12 23:28:45  weny
 * add psudo data for i2 and i2client, may be shared by more modules.
 *
 ******************************************************************************/
