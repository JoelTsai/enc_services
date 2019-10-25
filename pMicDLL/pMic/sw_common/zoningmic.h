/***************************************************************
 *
 * Filename    : zoningmic.h
 * Description : Zoning MIC definitions
 * Created on  : 2006/11/25
 * CVS Version : $Id: zoningmic.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2006-2007
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef _ZONINGMIC_H_
#define _ZONINGMIC_H_

#if 0
#include "mgtapilib.h"
#include "cctl_support.h"

/*
 * PMIC_ZONING_GET_GROUP_MEMBERSHIP_TABLE
 * - Platform defined read only MIC.
 */
typedef struct micZoningGroupMembershipTable_ 
{
    u8          mzgmt_ScsiOpCode;
    u8          mzgmt_MicSignature;
    u16         mzgmt_MicOpCode;
    u8          mzgmt_UniqueCmdId;
    u8          mzgmt_LoginKey;
    u8          mzgmt_Reserved0;
    u8          mzgmt_Reserved1;
    u8          mzgmt_Reserved2;
    u8          mzgmt_Reserved3; 
    u16         mzgmt_TransferLength;
    u16         mzgmt_TransferOffset;
    u8          mzgmt_Reserved; 
    Control_t   mzgmt_Control;
} __attribute__ ((packed)) micZoningGroupMembershipTable_t;
#endif

/*
 * Output for Get Group Membership Table.
 */
#define MAX_ZONING_GROUP_NAME (255)
typedef struct MicZoningGroupMemberEntry_
{
    u8           mzgme_groupId;
    u8           mzgme_reserved0[7];           
    u8           mzgme_groupname[MAX_ZONING_GROUP_NAME + 1];
    u8           mzgme_portnum;    /* nr of ports in this group */
    u8           mzgme_reserved1[3]; 
    u32          mzgme_port[1];    /* each of the logical ports */
} __attribute__ ((packed)) MicZoningGroupMemberEntry_t;

typedef struct MicZoningGroups_ {
    u8          mzg_groupnum;
    u8          mzg_reserved[7];
    MicZoningGroupMemberEntry_t mzg_groupentry[1];
} __attribute__ ((packed)) MicZoningGroups_t;

#if 0
/*
 * Read/Write MIC. PMIC_ZONING_[GET|SET]_GROUP_PERMISSION_TABLE
 */
typedef struct micZoningGroupPermissionTable_
{
    u8          mz_ScsiOpCode;
    u8          mz_MicSignature;
    u16         mz_MicOpCode;
    u8          mz_UniqueCmdId;
    u8          mz_LoginKey;
    u8          mz_GroupCode;
    u8          mz_Reserved0;
    u8          mz_Reserved1;
    u8          mz_Reserved2; 
    u16         mz_TransferLength;
    u16         mz_TransferOffset;
    u8          mz_ControllerId; 
    Control_t   mz_Control;
} __attribute__ ((packed)) micZoningGetGroupPermissionTable_t,
						   micZoningSetGroupPermissionTable_t,
                           ZONING_MIC_T;
#endif



#define PLATFORM_MAX_GROUPS                (12)
#define MAX_ZONING_GROUP_NAME (255)
/* 
 * Output format: 
 * A two dimensional matrix is being returned here.
 * x denoting the row indices and y denoting the column indices.
 */
typedef struct MicZoningGroupPermissionEntry_ {
    u8   mzgpe_GroupIdx; /* row index in the output matrix */
    u8   mzgpe_GroupIdy; /* col index in the output matrix */
    u8   mzgpe_CtrlId;
    u8   mzgpe_Reserved[5];
#define ZONING_GROUP_ACCESS_CONFIGURABLE     (1)
#define ZONING_GROUP_ACCESS_NOT_CONFIGURABLE (0)
    u8   mzgpe_IsGroupAccessConfigurable;
#define ZONING_GROUP_ACCESS_ALLOW    (1)
#define ZONING_GROUP_ACCESS_DISALLOW (0)
    u8   mzgpe_GroupAccess; /* Get=>current setting, Set=>Applied setting */
    u8   mzgpe_Reserved1[6];
} __attribute__ ((packed)) MicZoningGroupPermissionEntry_t;

typedef struct MicZoningGroupPermissionTable_ {
    u8 mzgpt_Group_Xdim; /* nr of rows in the matrix */
    u8 mzgpt_Group_Ydim; /* nr of rows in the matrix */
    u8 mzgpt_Reserved[6];
    /* a two dimensional array of Xdim X Ydim follows. */
    MicZoningGroupPermissionEntry_t mzgpt_PermitEntry[1][PLATFORM_MAX_GROUPS]; 
} MicZoningGroupPermissionTable_t;

#if 0
/*
 * Internally used structure definitions. 
 */

struct zoning_mini_rio_;
typedef struct zoning_mic_priv_ {
    struct list_head list; /* look at include/linux/list.h */
    RIO_t *origRio;

    u16 micopc; /* mic opc */
    u8 cid; /* controller id */
    u8 gid; /* group code */
    u8 ec; /* error code */

#define ZONING_LOCAL_FER    (0x00)
#define ZONING_REMOTE_FER   (0x01)
#define ZONING_FER_PROGRESS (0x02)
#define ZONING_MIC_COMPLETE (0x80)
    int status; /* XX_LOCAL_FER, XX_REMOTE_FER */

	/* tracking c2c mic path */
    int c2crecvdata; /* target mode operation */
    int c2c_simulated_req;
    void *alloc_resource; /* this holds c2c data */
    CCTL_C2C_STATUS_t c2c_status; /* tracks c2c status */

    void *dptr; /* data buffer starts here */
    size_t len; /* len of data buffer */
	void (*cb_func)(struct zoning_mini_rio_*);
} zoning_mic_priv_t;

typedef struct zoning_mini_rio_ {
    RIOHeader_t rh;
    zoning_mic_priv_t priv;
} zoning_mini_rio_t;


/* each group entry definition takes in worst case.... */
typedef struct micZGMTE_ {
    MicZoningGroupMemberEntry_t  mzgmte_entry;
    u32                          mzgmte_ports[PLATFORM_MAX_PORT_IN_GROUP];
} micZGMTE_t;

/* entire group membership table definition for a particular platform ....*/
typedef struct micZGMT_ {
    MicZoningGroups_t  mzgmt_zg;
    micZGMTE_t         mzgmt_group[PLATFORM_MAX_GROUPS];
} micZGMT_t;


/* entire zoning group permission table memory allocation footprint */
typedef struct micZGPT_ {
    MicZoningGroupPermissionTable_t     mzgpt_header;
    MicZoningGroupPermissionEntry_t     
				mzgpt_entry[PLATFORM_MAX_GROUPS][PLATFORM_MAX_GROUPS];
} micZGPT_t;
#endif

#endif /* _ZONINGMIC_H_ */
/***************************************************************
 * Change Log
 *
 * $Log: zoningmic.h,v $
 * Revision 1.2  2007/07/24 22:17:31  debinc
 * update MAX_GROUP
 *
 * Revision 1.1  2007/01/12 01:14:09  debinc
 * sas zoning support
 *
 * Revision 1.1.2.1  2006/11/28 21:15:29  lakshmi.s
 * Update New MIC definition for Zoning
 *
 ****************************************************************/
