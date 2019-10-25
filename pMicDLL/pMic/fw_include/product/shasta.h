#ifndef __SHASTA_H
#define __SHASTA_H


/* Backend Definitions go here */
#define MAX_CONTROLLERS                     2  /* assuming each can support 8 targets*/
#define TOTAL_MAX_TARGETS                   256 // 16
#define RESERVED_BICS                       16 
#define MAXBICS                             1024            /* (maxcmds/tgt( drive can accept 32 cmds at a time))*maxtgts */
/* RCM Specific Defines */

#define MAX_COMPONENT_DEVICES               TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_ARRAY         TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_CTLR          TOTAL_MAX_TARGETS  

#define MAX_DISK_LDS_IN_ARRAY               32 
#define MAX_STORAGE_LDS_IN_CTLR             256
#define MAX_DISK_EXTENTS_IN_ARRAY           256

#define MAX_DISK_EXTENTS_IN_LD              16
#define MAX_DISK_ARRAYS_IN_CTLR             256
#define MAX_SPARE_ARRAYS_IN_CTLR            256

#define MAX_ALLOWED_SECTOR_SIZES            6

/* For RAID 50/60, there'll be 16 AXLES and for RAID 51/61, there'll be 2 AXLES */
#define MAX_AXLES                           16
#define MIN_AXLES                           2
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID5  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID5  3
#define MAX_AXLES_FOR_RAID51                2

#ifdef SHASTA_RAID60
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID6  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID6  4
#endif

#define MAX_SPARE_ARRAYS_PER_DATA_ARRAY     8
#define MAX_REBUILDING_PDS_PER_ARRAY        DDF_PHYSICAL_DRIVES/2 //raid 10 configuration

/* DDF Definitions go here */
#define MAX_PHYSICAL_DRIVES                 256 // 16
#define MAX_VIRTUAL_DRIVES                  256 // 32 /* this may be a function of arrays and LUNS */
#define MAX_GLOBALSPARES                    256 // 8

#define DDF_PHYSICAL_DRIVES                 256
#define DDF_VIRTUAL_DRIVES                  256
#define DDF_DISK_LDS_IN_ARRAY               32  // support 4 LD only

#define DEFAULT_PROMISE_CO_NAME             "Promise Technology,Inc."
#define DEFAULT_PRODUCT_NAME                "STRAK EX8350"
#define VENDOR_INFO_MATRIX_FILE             "/oem/fw/VendorInfoMatrix.conf"

#define PROM_SUPPORT_RAID_LEVEL     (PI_FB_RAID_0 | PI_FB_RAID_1 | PI_FB_RAID_1E | \
                                     PI_FB_RAID_5 | PI_FB_RAID_6 | PI_FB_RAID_10 | \
                                     PI_FB_RAID_50 | PI_FB_RAID_60)

#define MAX_RIOS_RES_FOR_MIC_OB   4

#define PROM_MAX_MEMORY_CONFIG    1
 
#define OS_MEMORY_RESOURCE_MATRIX_DEF  \
    { 64,  256},            /* Total System MEMORY_128 */ \

#define HIDDEN_MEMORY_RESOURCE_MATRIX_DEF  \
    {  64,  256},            /* Total System MEMORY_128 */ \

#define MAX_SSNAME_MATRIX      1

#define DEFAULT_VENDOR_MATRIX  \
   /*  CID, BPID, Product ID, FEIT      , BEIT     ,  R,R,R,R,R,R,R,R,R,R    Name[16]--------"  ,  VId[8]  , ProductId[16], NFT            ,  R,R,R,R,R,R , Dom-Date , Domain Name */  \
    {  0xFF, 0xFF, CTRL_EX8350, FEIT_PCI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_NOT_DEFINED , {0,0,0,0,0,0}, "", ""},
                                                                                                                                                                                        
#define  DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX  \
    /*  CID, BPID, MCS  , CSV */                  \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }, \

#endif /* __SHASTA_H */


