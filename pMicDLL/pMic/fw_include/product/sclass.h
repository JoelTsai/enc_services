/*******************************************************************************
 *
 * Filename    : sclass.h
 * Description : 
 * Created on  : 02/01/2006
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef __SCLASS_H
#define __SCLASS_H

/* Backend Definitions go here */
#define MAX_CONTROLLERS                    64      /* assuming each can support 8 targets*/
#define TOTAL_MAX_TARGETS                  256
#define RESERVED_BICS                      256 
#define MAXBICS                            4096   /* (maxcmds/tgt( drive can accept 32 cmds at a time))*maxtgts */
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

/* For RAID50/RAID60, there'll be 16 AXLES and for RAID51/RAID61, there'll be 2 AXLES */
#define MIN_AXLES                           2
#define MAX_AXLES                           16
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID5  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID5  3
#define MAX_AXLES_FOR_RAID51                2

#ifdef SHASTA_RAID60
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID6  4
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID6  16
#endif

#define MAX_SPARE_ARRAYS_PER_DATA_ARRAY    8
#define MAX_REBUILDING_PDS_PER_ARRAY       DDF_PHYSICAL_DRIVES/2 //raid 10 configuration

/* DDF Definitions go here */
#define MAX_PHYSICAL_DRIVES                256
#define MAX_VIRTUAL_DRIVES                 256 /* this may be a function of arrays and LUNS */
#define MAX_GLOBALSPARES                   256

#define DDF_PHYSICAL_DRIVES                MAX_PHYSICAL_DRIVES
#define DDF_VIRTUAL_DRIVES                 MAX_VIRTUAL_DRIVES
#define DDF_DISK_LDS_IN_ARRAY              MAX_DISK_LDS_IN_ARRAY  // support 4 LD only

#define DEFAULT_PROMISE_CO_NAME            "Promise Technology,Inc."
#define DEFAULT_PRODUCT_NAME               "VTrak"
#define VENDOR_INFO_MATRIX_FILE            "/oem/fw/VendorInfoMatrix.conf"

#define MAX_RIOS_RES_FOR_MIC_OB   16

#define PROM_MAX_MEMORY_CONFIG    5
 
#define OS_MEMORY_RESOURCE_MATRIX_DEF  \
    { 64,  256},            /* Total System MEMORY_128 */ \
    {128, 1024},            /* Total System MEMORY_256 */ \
    {192, 1024},            /* Total System MEMORY_512 */ \
    {192, 1024},            /* Total System MEMORY_1GB */ \
    {192, 1024}             /* Total System MEMORY_2GB */ \

#define HIDDEN_MEMORY_RESOURCE_MATRIX_DEF  \
    {  64,  256},            /* Total System MEMORY_128 */ \
    { 128, 4096},            /* Total System MEMORY_256 */ \
    { 320, 8192},            /* Total System MEMORY_512 */ \
    { 832, 8192},            /* Total System MEMORY_1GB */ \
    {1856, 8192}             /* Total System MEMORY_2GB */ \

#define MAX_SSNAME_MATRIX      7

#define DEFAULT_VENDOR_MATRIX  \
    /*  CID, BPID, Product ID, FEIT      , BEIT     ,  R,R,R,R,R,R,R,R,R,R    Name[16]--------"  ,  VId[8]  , ProductId[16], NFT            ,  R,R,R,R,R,R , Dom-Date , Domain Name */  \
/*  {  0x20, 0xXX, CTRL_M510P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M510p"     , "Promise", "VTrak M510p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },*/ \
    {  0x20, 0x05, CTRL_M310P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M310p"     , "Promise", "VTrak M310p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x20, 0x06, CTRL_M210P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M210p"     , "Promise", "VTrak M210p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
/*                                                                                                                                                                                      \
    {  0x21, 0xXX, CTRL_M210S, FEIT_SSCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M510s"    , "Promise", "VTrak M510s", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x21, 0x05, CTRL_M210S, FEIT_SSCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M310s"    , "Promise", "VTrak M310s", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x21, 0x06, CTRL_M210S, FEIT_SSCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M210s"    , "Promise", "VTrak M210s", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
*/                                                                                                                                                                                      \
                                                                                                                                                                                        \
/*  {  0x22, 0xXX, CTRL_M510I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M510i"     , "Promise", "VTrak M510i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"},*/ \
    {  0x22, 0x05, CTRL_M310I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M310i"     , "Promise", "VTrak M310i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
    {  0x22, 0x06, CTRL_M210I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M210i"     , "Promise", "VTrak M210i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"},   \
                                                                                                                                                                                        \
/*  {  0x23, 0xXX, CTRL_M510F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M510f"     , "Promise", "VTrak M510f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },*/ \
    {  0x23, 0x05, CTRL_M310F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M310f"     , "Promise", "VTrak M310f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
    {  0x23, 0x06, CTRL_M210F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M210f"     , "Promise", "VTrak M210f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           },   \
                                                                                                                                                                                        \
    {  0xFF, 0xFF, CTRL_M210P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""},            \
                                                                                                                                                                                        
#define  DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX  \
    /*  CID, BPID, MCS  , CSV */                  \
/*  {  0x20, 0xXX, 1    , CTRL_SUPPORTED_FIXED }, */ \
    {  0x20, 0x05, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x20, 0x06, 1    , CTRL_SUPPORTED_FIXED }, \
/*                                                   \
    {  0x21, 0xXX, 1    , CTRL_SUPPORTED_FIXED },    \
    {  0x21, 0x05, 1    , CTRL_SUPPORTED_FIXED },    \
    {  0x21, 0x06, 1    , CTRL_SUPPORTED_FIXED },    \
*/                                                   \
                                                  \
/*  {  0x22, 0xXX, 1    , CTRL_SUPPORTED_FIXED }, */ \
    {  0x22, 0x05, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x22, 0x06, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  \
/*  {  0x23, 0xXX, 1    , CTRL_SUPPORTED_FIXED }, */ \
    {  0x23, 0x05, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x23, 0x06, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }, \

#endif /* __SCLASS_H */

