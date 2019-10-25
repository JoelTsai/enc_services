/*******************************************************************************
 *
 * Filename    : smartstor_products.h
 * Description :
 * Created on  : 2008/5/13
 * CVS Version :
 *
 * (C) Copyright Promise Technology Inc., 2002-2008
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef __SMARTSTOR_PRD_H
#define __SMARTSTOR_PRD_H

/*for BBU module threshold*/
#define BBUPlusII_TempThresholdCharge       60
#define BBUPlusII_TempThresholdDischarge    60

/* Common Backend Definitions go here */
#define MAX_CONTROLLERS                     1  /* not in use  */
#define MAX_CHANNELS                        1  /* not in use */
#define MAX_TARGETS                         256 // SSP devices
#define RESERVED_BICS                      256
#define MAXBICS                             4096  /* max cmd per host */

/* Below 4 are specifically only in Yosemite, see if these 4 can be removed */
#define MAX_SSP_ID                          MAX_TARGETS
#define MAX_ENCLOSURES_SUPPORTED            65
#define MAX_ENCLOSURE_ID                    MAX_ENCLOSURES_SUPPORTED
#define MAX_PD_ID                           1024

#define TOTAL_MAX_TARGETS                   256 // physical drive supported
/* RCM Specific Defines */

#define MAX_COMPONENT_DEVICES              TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_ARRAY        TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_CTLR         TOTAL_MAX_TARGETS

#define MAX_DISK_LDS_IN_ARRAY              32
#define MAX_STORAGE_LDS_IN_CTLR            256
#define MAX_DISK_EXTENTS_IN_ARRAY          512

#define MAX_DISK_EXTENTS_IN_LD             16
#define MAX_DISK_ARRAYS_IN_CTLR            256
#define MAX_SPARE_ARRAYS_IN_CTLR           256

#define MAX_ALLOWED_SECTOR_SIZES           6
#define MAX_SPINDLES_IN_AXLE_FOR_PARITY_RAID      32
#define MIN_SPINDLES_IN_AXLE_FOR_PARITY_RAID      3
/* For RAID 50, there'll be 16 AXLES and for RAID 51, there'll be 2 AXLES */
#define MAX_AXLES                           16
#ifdef __RAID30__
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID3  MAX_SPINDLES_IN_AXLE_FOR_PARITY_RAID
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID3  MIN_SPINDLES_IN_AXLE_FOR_PARITY_RAID
#endif
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID5  MAX_SPINDLES_IN_AXLE_FOR_PARITY_RAID
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID5  MIN_SPINDLES_IN_AXLE_FOR_PARITY_RAID
#define MAX_AXLES_FOR_RAID51                2

#ifdef SHASTA_RAID60
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID6  MAX_SPINDLES_IN_AXLE_FOR_PARITY_RAID
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID6  4
#endif

#define MAX_SPARE_ARRAYS_PER_DATA_ARRAY    8
/* raid 10 configuration */
#define MAX_REBUILDING_PDS_PER_ARRAY        DDF_PHYSICAL_DRIVES/2

/* DDF Definitions go here */
#define MAX_PHYSICAL_DRIVES                256
#define MAX_VIRTUAL_DRIVES                 256 /* this may be a function of arrays and LUNS */
#define MAX_GLOBALSPARES                   256

#define DDF_PHYSICAL_DRIVES                MAX_PHYSICAL_DRIVES
#define DDF_VIRTUAL_DRIVES                 MAX_VIRTUAL_DRIVES
// support 4 LD only
#define DDF_DISK_LDS_IN_ARRAY               MAX_DISK_LDS_IN_ARRAY

#define DEFAULT_PROMISE_CO_NAME             "Promise Technology,Inc."
#define DEFAULT_PRODUCT_NAME                "SmartRAID"

#define VENDOR_INFO_MATRIX_FILE            "/oem/fw/VendorInfoMatrix.conf"
#ifndef __RAID3__
#define PROM_SUPPORT_RAID_LEVEL     (PI_FB_RAID_0 | PI_FB_RAID_1 | PI_FB_RAID_1E | \
                                     PI_FB_RAID_5 | PI_FB_RAID_6 | PI_FB_RAID_10 | \
                                     PI_FB_RAID_50 | PI_FB_RAID_60)
#else
#ifndef __RAID30__
#define PROM_SUPPORT_RAID_LEVEL     (PI_FB_RAID_0 | PI_FB_RAID_1 | PI_FB_RAID_1E | \
                                     PI_FB_RAID_5 | PI_FB_RAID_6 | PI_FB_RAID_10 | \
                                     PI_FB_RAID_3 | \
                                     PI_FB_RAID_50 | PI_FB_RAID_60)
#else
#define PROM_SUPPORT_RAID_LEVEL     (PI_FB_RAID_0 | PI_FB_RAID_1 | PI_FB_RAID_1E | \
                                     PI_FB_RAID_5 | PI_FB_RAID_6 | PI_FB_RAID_10 | \
                                     PI_FB_RAID_3 | PI_FB_RAID_30 | \
                                     PI_FB_RAID_50 | PI_FB_RAID_60)
#endif
#endif

#define MAX_RIOS_RES_FOR_MIC_OB     16 // 4

#define PROM_MAX_MEMORY_CONFIG    5

//#define MULTIPLE_INITAITOR_SUPPORT

#define OS_MEMORY_RESOURCE_MATRIX_DEF  \
    { 64,  256},            /* Total System MEMORY_128 */ \
    {128, 1024},            /* Total System MEMORY_256 */ \
    {256, 1024},            /* Total System MEMORY_512 */ \
    {384, 1024},            /* Total System MEMORY_1GB */ \
    {512, 1024}             /* Total System MEMORY_2GB */ \

#define HIDDEN_MEMORY_RESOURCE_MATRIX_DEF  \
    {  64,  256},            /* Total System MEMORY_128 */ \
    { 128, 4096},            /* Total System MEMORY_256 */ \
    { 256, 8192},            /* Total System MEMORY_512 */ \
    { 640, 8192},            /* Total System MEMORY_1GB */ \
    {1536, 8192}             /* Total System MEMORY_2GB */ \

#define MAX_SSNAME_MATRIX      22

#define DEFAULT_VENDOR_MATRIX  \
    /*  CID, BPID,                            Product ID,    FEIT,       BEIT,      R,R,R,R,R,R,R,R,R,R , Name[16]--------" ,  VId[8]  , ProductId[16]    , NFT            ,  R,R,R,R,R,R , Dom-Date , Domain Name */    \
    {  0x30, ENC_TYPE_VR1000Y_2U8BAY_TOWER_S, CTRL_VR1320S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1320s"  , "Promise", "VessRAID 1320s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U8BAY_TOWER_R, CTRL_VR1420S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1420s"  , "Promise", "VessRAID 1420s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U8BAY_S,       CTRL_VR1720S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1720s"  , "Promise", "VessRAID 1720s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U8BAY_R,       CTRL_VR1820S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1820s"  , "Promise", "VessRAID 1820s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U12BAY_S,      CTRL_VR1730S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1730s"  , "Promise", "VessRAID 1730s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U12BAY_S,      CTRL_VR1731S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1731s"  , "Promise", "VessRAID 1731s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U12BAY_R,      CTRL_VR1830S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1830s"  , "Promise", "VessRAID 1830s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_2U12BAY_R,      CTRL_VR1831S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1831s"  , "Promise", "VessRAID 1831s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_3U16BAY_S,      CTRL_VR1740S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1740s"  , "Promise", "VessRAID 1740s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x30, ENC_TYPE_VR1000Y_3U16BAY_R,      CTRL_VR1840S,  FEIT_SAS,   BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1840s"  , "Promise", "VessRAID 1840s" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x31, ENC_TYPE_VR1000Y_1U4BAY_S,       CTRL_VR1710I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1710i"  , "Promise", "VessRAID 1710i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U8BAY_TOWER_S, CTRL_VR1320I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1320i"  , "Promise", "VessRAID 1320i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U8BAY_TOWER_R, CTRL_VR1420I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1420i"  , "Promise", "VessRAID 1420i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U8BAY_S,       CTRL_VR1720I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1720i"  , "Promise", "VessRAID 1720i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U8BAY_R,       CTRL_VR1820I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1820i"  , "Promise", "VessRAID 1820i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U12BAY_S,      CTRL_VR1730I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1730i"  , "Promise", "VessRAID 1730i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U12BAY_S,      CTRL_VR1731I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1731i"  , "Promise", "VessRAID 1731i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U12BAY_R,      CTRL_VR1830I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1830i"  , "Promise", "VessRAID 1830i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_2U12BAY_R,      CTRL_VR1831I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1831i"  , "Promise", "VessRAID 1831i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_3U16BAY_S,      CTRL_VR1740I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1740i"  , "Promise", "VessRAID 1740i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x31, ENC_TYPE_VR1000Y_3U16BAY_R,      CTRL_VR1840I,  FEIT_ISCSI, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "VessRAID 1840i"  , "Promise", "VessRAID 1840i" , NFT_NOT_DEFINED, {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0xFF, 0xFF,                            CTRL_VR1320S,  FEIT_SAS  , BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}

#define  DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX  \
    /*  CID, BPID, MCS  , CSV */                  \
    {  0x30, 0x0B, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0C, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0D, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0E, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0B, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0C, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0D, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x30, 0x0E, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }, \

#endif /* __SMARTSTOR_PRD_H */

