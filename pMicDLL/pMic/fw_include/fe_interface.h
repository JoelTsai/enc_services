/***************************************************************
 *
 * Filename    : fe_interface.h
 * Description : Frontend Interface common definitions 
 * Created on  : 2006/11/27
 * CVS Version : $Id: fe_interface.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2006
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef _FE_INTERFACE_H_
#define _FE_INTERFACE_H_

/* 
 * front end interface for raid. 
 */
struct fe_query_ {
    int qid;
    u16 initiator_id;
    u16  port_id;
    int  micopc;
    void *data;
    int status;
    void *resp;
    size_t resplen;
};

typedef struct fe_query_ fe_query_t, fesas_query_t, zoning_query_t, 
                            cbay_query_t;

#define FE_QUERY_SASADDRESS (0x01)
#define FE_QUERY_NEWMIC     (0x02)
#define FE_QUERY_INITIATOR_NAME (0x03) /* This maybe SAS Addr or Slotnr */
#define FE_QUERY_SET_CTL_STATE (0x04)

typedef int (*femichandler)(int, void*);
femichandler fe_register_mic_handler(femichandler);
int fesas_process_ctl_state(u32 ctl_state);

#define CONTROLLER_STATE_ACTIVE     0x00000002
#define CONTROLLER_STATE_PASSIVE    0x00000004
#define CONTROLLER_STATE_MAINTENANCE 0x00000008

#define CONTROLLER_STATE_AA         0x00000010
#define CONTROLLER_STATE_AA_FO      0x00000020
#define CONTROLLER_STATE_AA_FB      0x00000040
#define CONTROLLER_STATE_AA_MA      0x00000080

#define CONTROLLER_STATE_MASTER     0x00000100
#define CONTROLLER_STATE_SLAVE      0x00000200

#define CONTROLLER_STATE_SINGLE     0x00000400

#define CONTROLLER_STATE_AP         0x00001000
#define CONTROLLER_STATE_AP_FO      0x00002000
#define CONTROLLER_STATE_AP_FB      0x00004000
#define CONTROLLER_STATE_AP_MA      0x00008000

#define CONTROLLER_STATE_AA_LA      0x00010000

#define CONTROLLER_STATE_INIT       0x80000000

#endif /* _FE_INTERFACE_H_ */
/***************************************************************
 * Change Log
 *
 * $Log: fe_interface.h,v $
 * Revision 1.1.2.1  2008/08/21 02:58:52  willy.lin
 * no message
 *
 * Revision 1.1.2.1  2007/09/11 22:09:43  lakshmi.s
 * Move file for GPL compliance
 *
 * Revision 1.1.2.5  2007/03/09 01:12:02  vimal.nakum
 * Lun Affinity changes for SAS frontend - E310S/Clear Bay.
 *
 * Revision 1.1.2.4  2006/12/02 01:17:48  lakshmi.s
 * Request #12064: sas mics crash
 *
 * Revision 1.1.2.3  2006/11/30 01:08:10  lakshmi.s
 * Include fe interface definitions for zoning/lmm mics
 *
 * Revision 1.1.2.2  2006/11/28 02:11:34  lakshmi.s
 * Fix definition from FESAS to FE
 *
 * Revision 1.1.2.1  2006/11/28 02:04:01  lakshmi.s
 * Code reorg for frontend access
 *
 ***************************************************************/
