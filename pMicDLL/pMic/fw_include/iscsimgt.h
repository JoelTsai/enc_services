/*-------------------------------------------------------------------------**
 **                                                                        **
 **    Filename    : iscsimgt.h                                            **
 **    Description : iSCSI Defines shared by Raid Core and FED.            **
 **    Created on  : Sept 28, 2006.                                        **
 **    Created by  : Santosh Kumar.                                        **
 **                                                                        **
 **    (C) Copyright Promise Technology Inc., 2007                         **
 **    All Rights Reserved.                                                **
 **                                                                        **
 **-------------------------------------------------------------------------*/
#ifndef _ISCSIMGT_H_
#define _ISCSIMGT_H_

#ifdef ISLAVISTA_VERSION_DEBUG
static char *CVSId = "$Id: iscsimgt.h 117 2010-05-06 10:01:05Z spoca.huang $"; 
#endif

/* INCLUDE FILE DECLARATIONS
 */


/* MACRO DEFINE
 */
#define ISCSI_MIC_CTLR_GET_INFORMATION          0x0
#define ISCSI_MIC_CTLR_GET_PARAMS               0x1
#define ISCSI_MIC_CTLR_SET_PARAMS               0x2



/* STRUCTURE DEFINITION
 */
typedef struct FD_INFO_DESC
{
    u16 Type;
#define ISCSI_CNTL_GET_NAME_FOR_INDEX           0x0001
#define ISCSI_CNTL_GET_NUM_SESSIONS_FOR_PORT    0x0002
#define ISCSI_CNTL_GET_NUM_SESSION_FOR_NODE     0x0003
#define ISCSI_CNTL_GET_NUM_NODE_FOR_TARGET      0x0004
#define ISCSI_CNTL_GET_NUM_PORTAL_FOR_TARGET    0x0005
#define ISCSI_CNTL_GET_ETHERNET_PORT_PARAMETER  0x0006
#define ISCSI_CNTL_SET_ETHERNET_PORT_PARAMETER  0x0007
#define ISCSI_CNTL_GET_NUM_VLAN_FOR_TARGET      0x0008
#define ISCSI_CNTL_GET_NUM_LINK_AGG_FOR_TARGET  0x0009
#define ISCSI_CNTL_GET_ETHERNET_PORT_COUNT      0x000a
#define ISCSI_CNTL_GET_NUM_CHAP                 0x000b
#define ISCSI_CNTL_GET_NAS_DEVICE_NODE_COUNT    0x000c
#define ISCSI_CNTL_SHUTDOWN                     0x00FF

    u16 PortID;
    u16 Index;
    u8 *rcvBuffer;
    u32 rcvBufferSize;
    u8 *sndBuffer;     /* Not Currently used */
    u32 sndBufferSize; /* Not Currently used */

} FID_t;


typedef struct iscsiMgtFEToRCStruct
{
    u16  type;
#define ISCSI_MGT_GET_NODE_NAME            0x0001
#define ISCSI_MGT_GET_NODE_ALIAS           0x0002

    u8   *rdWrBuffer;
    u32  bufferSize;

} iscsiMgtFEToRC_t;




/* EXPORTED FUNCTION PROTYPE
 */
void iscsiLogEventToRaidCore (u32, u16, u8 *, u32);
u8   iscsiMgmtNVRamReadWrite (u8, u32, u8 *, u32);
u8   iscsiMgmtFEGetSetRC (iscsiMgtFEToRC_t *);



/* EXTERN DECLARATIONS
 */
extern void iscsiRaidModuleDeInit (void);





#endif /* _ISCSIMGT_H_ */


