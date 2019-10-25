/*******************************************************************************
 * Filename    : reqdata.h
 * Description : Request Data Type header file
 *               * Define the data structures of the parameters and return data for
 *                 each I2 IPC request.
 *               * Shared among I2, I2 Client Lib, and the components that use 
 *                 the I2 Client Lib
 * Created on  : 02/03/03
 * CVS Version : $Id: reqdata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_REQDATA_H__
#define __PI_REQDATA_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "i2types.h"
#include "i2typesob.h"

#ifdef EMBEDDED
    #include "../../utils/ptiflash/imgheader.h"
    #include "../../utils/ptiflash/ptiflashlib/ptiflashlib.h"
#endif

/* --- constant definitions ------------------------------------------------ */

/* dup with defs in micext.h */
/*
#define INVALID_CTRL_ID 0xFFFFFFFF
#define INVALID_PORT_ID 0xFFFFFFFF
#define INVALID_ARRAY_ID 0xFFFFFFFF
#define INVALID_PHYDRV_ID 0xFFFFFFFF
#define INVALID_LOGDRV_ID 0xFFFFFFFF
#define INVALID_ENCL_ID 0xFFFFFFFF
#define INVALID_SLOT_ID 0xFFFFFFFF
#define INVALID_SEQUENCE_NUMBER 0xFFFFFFFF
#define INVALID_FSH_HANDLE 0xFFFFFFFF
#define INVALID_RAID_LEVEL 0xFFFF
#define INVALID_STRIPE_SIZE 0xFFFF
#define INVALID_CAPACITY 0xFFFFFFFFFFFFFFFFLL
#define INVALID_INITIATOR_INDEX 0xFFFF
*/
/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: reqdata_checkReqParam<request type>
* Description: check whether the buf size is big enough to hold the request
*       data according to the request param. If the buffer is not big enough
*       to hold all the request data, it will check whether it can hold the
*       request data for one device if the data can be divided logically
*       in device base. If the buffer is big enough for one device, it will
*       still return PIERR_NO_ERROR, and change the request param and the 
*       actual data size accordingly
* Parameters:    
*       [in/out] pParam, the param of the request
*       [in/out] pu32DataSize, the buffer size or returned data size
*       [out] pu32Count, the device count in the buffer if applicable
* Return: the possible values are:
*       PIERR_NO_ERROR: big enough; 
*       PIERR_BUFFER_TOO_SMALL: the buffer is too small;
*       PIERR_INVALID_PARAM: the parameter is invalid. 
* Remarks: none.      
****************************************************************************/
u32 reqdata_checkReqParamCtrlInfo(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ctrl_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamLogDrvInfo(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamPhyDrvInfo(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_phydrv_info_t * pParam, u32 * pu32DataSize);

u32 reqdata_checkReqParamGetPDSettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_phydrv_settings_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetPDSettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_phydrv_settings_t * pParam, 
    req_data_phydrv_settings_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetCtrlSettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ctrl_settings_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetCtrlSettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ctrl_settings_t * pParam, 
    req_data_ctrl_settings_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetLDSettings(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_settings_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetLDSettings(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_settings_t * pParam, 
    req_data_logdrv_settings_t * pData, u32 * pu32DataSize);

u32 reqdata_checkReqParamGetArrayInfo(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetArraySettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_settings_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetArraySettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_settings_t * pParam, 
    req_data_array_settings_t * pData, u32 * pu32DataSize);

u32 reqdata_checkReqParamDiskArrayConfig(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_cfg_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamDiskArrayAdd(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_add_t * pParam);
u32 reqdata_checkReqParamDiskArrayDel(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_array_del_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamLogDrvAdd(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_add_t * pParam, u32 u32ParamSize, u32 u32NumOfPD);
u32 reqdata_checkReqParamLogDrvDel(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_del_t * pParam, u32 u32ParamSize);
u32 reqdata_checkReqParamMigration(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_migrate_t * pParam);
u32 reqdata_checkReqParamGetMigrationProg(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_device_ids_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSpareInfo(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_spare_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamAllSpareInfo(
    feature_bits_t * pfb, firmware_capabilities_t * pfc, 
    u32 * pu32DataSize);
u32 reqdata_checkReqParamSpareAdd(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_spare_add_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSpareDel(
    feature_bits_t * pfb, firmware_capabilities_t * pfc, 
    req_param_spare_del_t * pParam, u32 * pu32DataSize);

u32 reqdata_checkReqParamMediaPatrolProgress(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    u32 * pu32DataSize);
u32 reqdata_checkReqParamRebuildProgress(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_rbprogress_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamRebuildControl(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_rbctrl_t * pParam);

u32 reqdata_checkReqParamLdiProgress(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_init_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamLdiStart(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_init_t * pParam, u32 u32ParamSize);
u32 reqdata_checkReqParamLdiOther(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_init_t * pParam);

u32 reqdata_checkReqParamLdsProgress(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_synch_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamLdsStop(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_synch_t * pParam);
u32 reqdata_checkReqParamLdsStart(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ld_synch_t * pParam);
u32 reqdata_checkReqParamLdsPause(feature_bits_t * pfb, firmware_capabilities_t * pfc,
                                  req_param_ld_synch_t * pParam);
u32 reqdata_checkReqParamLdsResume(feature_bits_t * pfb, firmware_capabilities_t * pfc,
                                  req_param_ld_synch_t * pParam);

u32 reqdata_checkReqParamRcProgress(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_rc_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamRcOther(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_rc_t * pParam);
u32 reqdata_checkReqParamSpareCheckProgress(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_sparechk_t * pParam, u32 * pu32DataSize);

u32 reqdata_checkReqParamGetEvents(req_param_event_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetEventInfo(req_param_event_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetEventInfo(req_param_event_info_t * pParam, req_data_event_info_t * pData, u32 * pu32DataSize);

u32 reqdata_checkReqParamGetiSCSIInfo(req_param_iscsi_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetiSCSISettings(req_param_iscsi_setting_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetiSCSISettings(req_param_iscsi_setting_t * pParam, req_data_iscsi_setting_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetLLSVLAN(req_param_vlan_config_t * pParam, req_data_vlan_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetChap(req_param_chap_config_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetChap(req_param_chap_config_t * pParam, req_data_chap_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetSLP(req_param_device_ids_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetSLP(req_param_device_ids_t * pParam, req_data_slp_info_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetISNS(req_param_isns_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetNodeList(req_param_node_list_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetISNS(req_param_isns_info_t * pParam, req_data_isns_info_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetBGASchedules(req_param_bga_schedule_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamAddBGASchedules(req_data_bga_schedule_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamDeleteBGASchedules(req_data_bga_schedule_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamModifyBGASchedules(req_data_bga_schedule_t * pData, u32 * pu32DataSize);
#ifdef EMBEDDED
u32 reqdata_checkReqParamSetSnmp(req_data_snmp_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetSmbsend(req_data_Smbsend_config_t  * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetWebserverConfig(req_data_webserver_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetTelnetConfig(req_data_telnet_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetSshConfig(req_data_ssh_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetNtpConfig(req_data_ntp_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetUPSConfig(req_data_ups_manager_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetBonjourConfig(req_data_bonjour_config_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamSetCimserverConfig(req_data_cimserver_config_t * pData, u32 * pu32DataSize);
#endif
u32 reqdata_checkReqParamGetInitiator(req_param_initiator_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamGetLMM(req_param_lmm_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamAddLMM(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_data_lmm_t * pData, u32 * pu32DataSize);
u32 reqdata_checkReqParamEnclStats(req_param_encl_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamCtrlStats(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_ctrl_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamPhyDrvStats(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_phydrv_info_t * pParam, u32 * pu32DataSize);
u32 reqdata_checkReqParamLogDrvStats(feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_logdrv_info_t * pParam, u32 * pu32DataSize);

u32 reqdata_checkReqParamFCGetInfo(req_param_fc_port_t * pParam, req_data_fc_info_t * pData,
    u32 * pu32DataSize);
u32 reqdata_checkReqParamFCGetPortInfo(req_param_fc_port_t * pParam, req_data_fc_port_info_t * pData,
    u32 * pu32DataSize);
u32 reqdata_checkReqParamFCGetSetting(req_param_fc_port_t * pParam, req_data_fc_port_setting_t * pData,
    u32 * pu32DataSize);
u32 reqdata_checkReqParamFCGetLoggedInDevice(req_param_fc_port_t * pParam, req_data_fc_loggedin_device_t * pData,
    u32 * pu32DataSize);
u32 reqdata_checkReqParamFCGetInitiatorList(req_data_fc_initiator_list_t * pData,
    u32 * pu32DataSize);   

u32 reqdata_checkReqParamGetEnclSettings(
    feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_encl_settings_t * pParam, u32 * pu32DataSize);

u32 reqdata_checkReqParamSetEnclSettings(
     feature_bits_t * pfb, firmware_capabilities_t * pfc,
    req_param_encl_settings_t *pParam, req_data_encl_settings_t * pData, u32 * pu32DataSize);
#endif /*__PI_REQDATA_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: reqdata.h,v $
 * Revision 1.78.6.3  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.78.6.2  2009/11/03 03:49:28  xinw
 * merge ssh support
 *
 * Revision 1.78.6.1  2009/03/23 11:51:06  xinw
 * add ups support
 *
 * Revision 1.78  2008/07/29 07:55:57  michaell
 * add start/pause/resume sync
 *
 * Revision 1.77  2008/06/26 08:37:59  jackyl
 * add bonjour support
 *
 * Revision 1.76  2007/02/01 03:59:00  xinw
 * add new Mx10i support
 *
 * Revision 1.75  2006/08/22 09:19:35  JudithLi
 * 10544/suggest netsend doesn't accept the empty IP as the vaild IP address
 *
 * Revision 1.74  2006/04/01 01:29:32  leync
 * get rid of a warning
 *
 * Revision 1.73  2006/03/16 01:39:09  debinc
 * rename header file
 *
 * Revision 1.72  2006/02/22 01:28:32  debinc
 * get/set enclosure setting
 *
 * Revision 1.71  2006/01/04 21:37:01  weny
 * replace MAX values with those from feature bits and capabilities
 *
 * Revision 1.70  2005/12/08 04:35:56  weny
 * use feature bits and fw capabilities for MAX_LOGICAL_DRIVES
 *
 * Revision 1.69  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.68  2005/05/20 23:09:31  debinc
 * FC MIC change
 *
 * Revision 1.67  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.66  2004/09/16 01:39:33  debinc
 * telnet setting
 *
 * Revision 1.65  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.64  2004/07/06 23:19:47  weny
 * commented dup #def with micext.h
 *
 * Revision 1.63  2004/06/08 21:26:40  weny
 * change #ifndef IN_BAND to #ifdef EMBEDDED
 *
 * Revision 1.62  2004/05/13 18:09:08  zhengj
 * added support for spare check and locate enclosure
 *
 * Revision 1.61  2004/04/01 00:59:31  debinc
 * add checking against webserver setting
 *
 * Revision 1.60  2004/03/30 02:22:49  zhengj
 * added snmp config API error check
 *
 * Revision 1.59  2004/03/24 03:32:29  weny
 * I2 API porting
 *
 * Revision 1.58  2004/03/23 03:54:53  zhengj
 * added support for PDM
 *
 * Revision 1.57  2004/03/22 22:12:57  zhengj
 * add snmp port
 *
 * Revision 1.56  2004/03/18 01:43:24  debinc
 * Add webconfig structure
 *
 * Revision 1.55  2004/03/05 22:20:12  zhengj
 * added support for system time and stats
 *
 * Revision 1.54  2004/02/19 20:45:46  zhengj
 * fix inband error
 *
 * Revision 1.53  2004/02/19 20:28:12  debinc
 * Add one more flash stage
 *
 * Revision 1.52  2004/02/10 23:35:17  zhengj
 * flash support modification
 *
 * Revision 1.51  2004/01/30 03:55:38  zhengj
 * lmm support
 *
 * Revision 1.50  2004/01/19 23:44:13  zhengj
 * added da id for req_param_logdrv_del_t
 *
 * Revision 1.49  2004/01/08 19:04:07  zhengj
 * iSNS support
 *
 * Revision 1.48  2003/12/18 03:35:21  zhengj
 * migration support
 *
 * Revision 1.47  2003/12/18 01:32:44  debinc
 * import export request data strcuture
 *
 * Revision 1.46  2003/12/04 02:08:17  debinc
 * correct check in error on setUserPreference
 *
 * Revision 1.45  2003/12/03 22:24:11  debinc
 * support event filters
 *
 * Revision 1.44  2003/11/21 01:48:45  zhengj
 * modify data structure req_param_array_ldcfg_t
 *
 * Revision 1.43  2003/11/05 20:57:08  debinc
 * Add swmgt to CLI, I2, I2client
 *
 * Revision 1.42  2003/11/04 23:38:40  zhengj
 * some changes for device numbering and more
 *
 * Revision 1.41  2003/10/22 03:40:21  zhengj
 * added more check for addld
 *
 * Revision 1.40  2003/09/25 02:51:29  weny
 * Event Log change
 *
 * Revision 1.39  2003/09/25 00:14:10  zhengj
 * flash support
 *
 * Revision 1.38  2003/09/19 02:02:47  zhengj
 * added error table structure
 *
 * Revision 1.37  2003/09/18 19:12:32  zhengj
 * subsys ctrl PD settings
 *
 * Revision 1.36  2003/09/16 03:56:28  zhengj
 * fix for iscsi settings
 *
 * Revision 1.35  2003/09/13 01:38:06  zhengj
 * added support for iscsi setting
 *
 * Revision 1.34  2003/09/13 00:34:38  weny
 * config lock support
 *
 * Revision 1.33  2003/09/12 16:32:18  zhengj
 * modify init param
 *
 * Revision 1.32  2003/09/11 03:48:23  zhengj
 * added slp
 *
 * Revision 1.31  2003/09/10 22:18:08  zhengj
 * initial check-in for iscsi
 *
 * Revision 1.30  2003/09/04 22:53:15  weny
 * disable TFTP flash uploading for in-band
 *
 * Revision 1.29  2003/09/04 01:13:04  zhengj
 * added support for flash
 *
 * Revision 1.28  2003/08/30 00:03:20  debinc
 * Add new field username to change password data structure
 *
 * Revision 1.27  2003/08/27 01:13:50  zhengj
 * missing drive support and bug fix
 *
 * Revision 1.26  2003/08/22 01:25:12  zhengj
 * added support for enclosure mgmt and others
 *
 * Revision 1.25  2003/08/21 02:51:01  debinc
 * Add user management support
 *
 * Revision 1.24  2003/08/08 22:41:41  zhengj
 * added support for array setting and info and others ..
 *
 * Revision 1.23  2003/08/04 18:50:35  zhengj
 * added support for array addld and delld
 *
 * Revision 1.22  2003/07/14 18:49:45  weny
 * hybrid raid config support
 *
 * Revision 1.21  2003/06/28 05:47:44  weny
 * add bga scheduler support
 *
 * Revision 1.20  2003/06/28 03:26:56  weny
 * iscsi node info support
 *
 * Revision 1.19  2003/06/27 23:48:45  weny
 * add ld settings and rc support
 *
 * Revision 1.18  2003/06/26 21:06:14  weny
 * write cache to write policy in ld attrib
 *
 * Revision 1.17  2003/06/16 22:08:50  weny
 * change event class mask from u32 to u64
 *
 * Revision 1.16  2003/06/12 02:33:53  weny
 * 1. event request data structure change
 * 2. check more on the get events request param
 *
 * Revision 1.15  2003/06/07 01:29:37  weny
 * add full support to ldi and lds, some for rc.
 *
 * Revision 1.14  2003/06/04 02:29:54  weny
 * pool to disk array
 *
 * Revision 1.13  2003/06/03 20:59:08  weny
 * add support to ad ld to disk array.
 *
 * Revision 1.12  2003/05/17 03:04:22  weny
 * Rewrite the event related data structures.
 *
 * Revision 1.11  2003/04/15 17:51:00  weny
 * add data structures of ldi and lds progress
 *
 * Revision 1.10  2003/04/14 19:36:53  weny
 * add support to event & rb
 *
 * Revision 1.9  2003/04/11 05:14:53  weny
 * adding support to spare cfg
 *
 * Revision 1.8  2003/04/09 19:50:36  weny
 * changed the pool del structure
 *
 * Revision 1.7  2003/04/08 23:27:23  weny
 * 1. changes in param of add storpool and addld storpool
 * 2. media patrol support
 *
 * Revision 1.6  2003/04/02 04:52:23  weny
 * changed the param structures of phy/log drv info and settings
 *
 * Revision 1.5  2003/04/02 00:13:54  weny
 * add some param check routines for storpool and spare config
 *
 * Revision 1.4  2003/03/27 20:11:52  weny
 * 1. add support for storpool and spare
 *
 * Revision 1.3  2003/03/22 00:52:57  weny
 * i2 ipc interface change - isolcate f/w data struct & cmd inside i2client.
 *
 * Revision 1.2  2003/03/12 23:27:34  weny
 * change the subsys info data structure according to f/w struct
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 ******************************************************************************/
