/*******************************************************************************
 *
 * Filename    : imgheader.h
 * Description : Header file describing image header structs, fis structs,
 *               flash map structs and function prototypes for reading/writing
 *               header info
 * Created on  : 07/29/2003
 * CVS Version : $Id: imgheader.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _IMGHEADER_H_
#define _IMGHEADER_H_

#ifndef IN_BAND
#ifndef __KERNEL__
#define u8      unsigned char
#define u16     unsigned short
#define u32     unsigned int
#define u64     unsigned long long

#define s8      char
#define s16     short
#define s32     int
#define s64     long long
#endif
#endif

#define IH_HEADER_VERSION               1
#define IH_PTI_SIGNATURE                0xAB105ACD
#define IH_MAX_NUM_IMAGES               13
#define IH_MAX_FLASH_MAP_INFO           64

/* Error Codes */
#define IH_OK                           0x00000000
#define IH_ERR_GENERAL                  0x00000001
#define IH_ERR_NO_MEM                   0x00000002
#define IH_ERR_NOT_MULTI_IMAGE          0x00000003
#define IH_ERR_IMG_HEADER_NOT_FOUND     0x00000004
#define IH_ERR_OPENING_FILE             0x00000005
#define IH_ERR_CLOSING_FILE             0x00000006
#define IH_ERR_READING_FILE             0x00000007
#define IH_ERR_WRITING_FILE             0x00000008

/* Product Types */

/* V3 on irvine hardware */
#define IH_PROD_IRVINE                  0x00000001

/* DO NOT USE 0x00000002 -- used by sonoma */

/* V3 on sonoma hardware */
#define IH_PROD_SONOMA                  0x00000003

/* V4 engine on islavista b1 hardware */
#define IH_PROD_ISLAVISTA_002           0x00000004

/* V4 engine on irvine hardware */
#define IH_PROD_ISLAVISTA_001           0x00000005

/* V4 engine on LINDSAY IOP331 based platform */
#define IH_PROD_MX10X                   0x00000006

/* V4 engine on Cx20y hardware */
#define IH_PROD_CX20Y                   0x00000007
#define IH_PROD_VESSRAID                0x00000008

/* The HBA will start from 0x00000080 */
/* V4 engine on Shasta HBA hardware */
#define IH_PROD_SHASTA_HBA		0x00000080

/* V4 engine on Yosemite HBA hardware */
#define IH_PROD_YOSEMITE_HBA		0x00000081

/* Un known product type */
#define IH_PROD_UNKNOWN             0x00000000


/* End Product Types */

/* MUST BE IN SEQUENTIAL ORDER....NO HOLES!!!!! */
/* Flash Types for individual image header */
#define IH_TYPE_MANUFACTORING           1      /* zero padded */
#define IH_TYPE_ENTIRE                  2      /* non-zero padded */
#define IH_TYPE_REDBOOT_ROM             3      /* rom version */
#define IH_TYPE_KERNEL                  4
#define IH_TYPE_FIRMWARE                5
#define IH_TYPE_SOFTWARE                6
#define IH_TYPE_CONFIG_DATA             7
#define IH_TYPE_ROOTFS                  8
#define IH_TYPE_FIS_CONFIG              9
#define IH_TYPE_FIS_DIRECTORY           10
#define IH_TYPE_IMAGE_VERSIONS          11
#define IH_TYPE_SEP_FIRMWARE            12
#define IH_TYPE_REDBOOT_RAM             13     /* ram version */
#define IH_TYPE_OEM_CUSTOMIZATION       14
#define IH_TYPE_REDBOOT_DIAG            15
/*
 * Additional flash types for newly created conf_init and conf_user
 * partitions.
 */
#define IH_TYPE_CONFIG_INIT_DATA        16
#define IH_TYPE_CONFIG_USER_DATA        17
#define IH_TYPE_3RD_FIRMWARE	        18
#define IH_TYPE_SB_MCODE                22
#define IH_TYPE_BIOS                    19
#define IH_TYPE_EFI                     20
#define IH_TYPE_3RD_MICROCODE           21
#define IH_TYPE_NAND_FIS                23
#define IH_TYPE_SPECIAL_REDBOOT         24
#define IH_TYPE_APPLICATION             25
#define IH_TYPE_RESERVE                 26
#define IH_TYPE_MAX_NUM                 26

/* CheckSum Types */
#define IH_CK_POSIX_2                   0x01
#define IH_CK_MD5SUM                    0x02

/* Compression formats */
#define IH_COMPRESS_NONE                0x01
#define IH_COMPRESS_GZIP                0x02
#define IH_COMPRESS_BZIP                0x03
#define IH_COMPRESS_COMPRESS            0x04
#define IH_COMPRESS_PKZIP               0x05

/* Flash Header Types */
#define IH_FHTYPE_REDBOOT               1

typedef struct verPartitionHeader
{
    u32 vp_Signature;       /* set as IH_PTI_SIGNATURE */
    u32 vp_NumImages;
    u8  vp_Reserved[248];   /* Pad to size of an image header */
} verPartitionHeader_t;

typedef struct fisPartition
{
    u8  fp_Name[16];        /* Null terminated name */
    u32 fp_FlashBase;       /* Address within FLASH of image */
    u32 fp_MemBase;         /* Address in memory where it executes */
    u32 fp_Size;            /* Length of image */
    u32 fp_EntryPoint;      /* Execution entry point */
    u32 fp_DataLength;      /* Length of actual data */
    u8  fp_Pad[256 - (16 + 4 * sizeof (u32) + 3 * sizeof (u32))];
    u32 fp_DescCksum;       /* Checksum over image descriptor */
    u32 fp_FileCksum;       /* Checksum over image data */
} fisPartition_t;

typedef struct flashMapInfo
{
    u32 fmi_Address;        /* Address of flash image location */
    u32 fmi_Length;         /* Length of flash partition */
    u8  fmi_BlockNumber;    /* Parition num (linux dev node '/dev/mtdblockX') */
    u8  fmi_CopyNumber;     /* Used for primary/secondary backup */
    u16 fmi_FlashType;      /* flash type, must be one of IH_TYPE_* */
    u32 fmi_Reserved01;
    u8  fmi_Name[16];       /* Name of partition */
} flashMapInfo_t;

typedef struct flashMapHeader
{
    u8  fmh_Type;           /* one of IH_FHTYPE_* - only Redboot supported */
    u8  fmh_Reserved0[3];
    u32 fmh_Count;          /* Number of partitions in flash */
    flashMapInfo_t fmh_FmiPartitions[IH_MAX_FLASH_MAP_INFO];
} flashMapHeader_t;

typedef struct posixCheckSum_2
{
    u32 pc2_CheckSum;
    u32 Reserved[3];
} posixCheckSum2_t;

typedef struct md5_checksum
{
    u32 md5cs_WordA;
    u32 md5cs_WordB;
    u32 md5cs_WordC;
    u32 md5cs_WordD;
} md5CheckSum_t;

typedef union CheckSum
{
    posixCheckSum2_t ih_pcs2;
    md5CheckSum_t    ih_md5cs;
} checkSum_t;

typedef struct ImageHeader
{
    u32 ih_HeaderVersion;           /* Bytes 0-3     */
    u32 ih_PtiSignature;            /* Bytes 4-7     */

    /* Checksum for each image (or entire image if main header for multi-image
     * file)
     */
    checkSum_t ih_CheckSum;         /* Bytes 8-23    */

    /* Size of image in bytes (not including header) */
    u32 ih_ImageSize;               /* Bytes 24-27   */

    /* Offset in bytes from beginning of file of image data
     * (if ih_NumImages > 1, this is the offset to the first image header)
     */
    u32 ih_Offset;                  /* Bytes 28-31   */
    u32 ih_ProductType;             /* Bytes 32-35   */
    u32 ih_OEMCode;                 /* Bytes 36-39   */
    u16 ih_NumImages;               /* Bytes 40-41   */
    u16 ih_FlashType;               /* Bytes 42-43   */
    u8  ih_PtiString[64];           /* Bytes 44-107  */
    u8  ih_MajorVer;                /* Byte  108     */
    u8  ih_MinorVer;                /* Byte  109     */
    u8  ih_BuildNum;                /* Byte  110     */
    u8  ih_BuildMonth;              /* Byte  111     */
    u8  ih_BuildDate;               /* Byte  112     */
    u8  ih_BuildYear;               /* Byte  113     */
    u8  ih_CheckSumType;            /* Byte  114     */
    u8  ih_CompressionFormat;       /* Byte  115     */
    u32 ih_FlashMapHeaderLength;    /* Bytes 116-119 */
    u32 ih_FlashMapHeaderOffset;    /* Bytes 120-123 */

    /* Primary = 1, Secondary = 2, Tertiary = 3, etc.... */
    u8  ih_CopyNum;                 /* Byte  124     */

    u8  ih_BuildHr;                 /* Bytes 125 */
    u8  ih_BuildMin;                /* Bytes 126 */
    u8  ih_BuildSec;                /* Bytes 127 */
	/*  The folowing 6 bytes are reserved for PtiFlash utility to
		store the time stamp when flash the images into Flash device 
	*/
    u8  ih_FlashMonth;              /* Byte  128     */
    u8  ih_FlashDate;               /* Byte  129     */
    u8  ih_FlashYear;               /* Byte  130     */
    u8  ih_FlashHr;                 /* Byte  131     */
    u8  ih_FlashMin;                /* Byte  132     */
    u8  ih_FlashSec;                /* Byte  133     */

    u8  ih_Reserved01[122];         /* Bytes 134-255 */
} ih_t;

#ifndef __KERNEL__
s32 ih_ReadImgHeader (s8 *Filename, ih_t *ImgHeader, u32 Offset);
s32 ih_ReadFlashMapHeader (s8 *Filename, ih_t *pImgHeader,
        flashMapHeader_t *pNewFmh);
s32 ih_WriteImgHeader (s8 *Filename, ih_t *ImgHeader);
s32 ih_WriteFlashMapHeader (s8 *Filename, flashMapHeader_t *pFlashMapHeader);
void ih_PrintImgHeader (ih_t *ImgHeader);
void ih_PrintFlashMapHeader (flashMapHeader_t *pFmh);
int ih_ValidateCheckSumType (int Value);
int ih_ValidateCompressionFormat (int Value);
int ih_ValidateFlashType (int Value);
int ih_ValidateProductType (int Value);
int ih_ValidatePtiSignature (u32 Value);
#endif

#endif /* _IMGHEADER_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: imgheader.h,v $
 * Revision 1.3.38.2  2009/11/30 10:14:08  xinw
 * update with ptiflash
 *
 * Revision 1.3.38.1  2008/09/04 01:54:00  billy.chiu
 * add new product cx20y partition infomation for ptiflash, and modify update fis directory to satisfy nor type and nand type flash
 *
 * Revision 1.3  2007/03/04 01:13:37  weny
 * fix compiling error with VC++ .NET 2002.
 *
 * Revision 1.2  2007/02/01 09:52:57  linusc
 * Define product type IH_PROD_MX10X for V4 engine on LINDSAY IOP331 based platform.
 * Add IH_TYPE_3RD_MICROCODE.
 *
 * Revision 1.1  2006/08/14 18:40:22  david.chiu
 * Copied from util/ptiflash
 *
 * Revision 1.16  2006/05/07 12:21:10  linusc
 * changed from
 * int ih_ValidatePtiSignature (int Value);
 * to
 * int ih_ValidatePtiSignature (u32 Value);
 *
 * Revision 1.15  2006/04/06 13:13:28  linusc
 * Added corresponding flash type, product type support for HBA.
 *
 * Revision 1.14  2006/03/24 23:48:40  lakshmi.s
 * changes for new flash type conf_init and conf_user
 *
 * Revision 1.13  2006/02/09 01:30:36  randallc
 * 1. Added support for an image containing more than 6 images (as in the case
 *    of the "all" image file which as fw, sw, ramdisk, oem, kernel, redboot
 *    rom & redboot ram.
 * 2. Added check for redboot rom before flashing.  If version and build date
 *    are the same as the image that is being flashed and the checksum of the
 *    redboot rom image on the flash chip is correct, then the flashing of the
 *    redboot rom image is skipped.
 *
 * Revision 1.12  2004/12/16 23:07:32  debinc
 * add define IV_TYPE_MAX_NUM
 *
 * Revision 1.11  2004/11/23 23:45:25  randallc
 * changed code for checking flash types as it seems that gcc or redboot has
 * an issue handling more than 13 or 14 if statements in a row.
 *
 * Revision 1.10  2004/11/11 19:42:05  randallc
 * product ID changes
 *
 * Revision 1.9  2004/10/06 22:00:38  randallc
 * added support for flashing ptiflash rom version for islavista hw
 *
 * Revision 1.8  2003/10/14 22:34:36  randallc
 * Add support for flash sep firmware.
 *
 * Revision 1.7  2003/08/22 23:43:44  randallc
 * Fixed typo SOFTARE->SOFTWARE
 *
 * Revision 1.6  2003/08/22 17:45:12  randallc
 * Moved name to end of structure so that previous imgs are not affected.
 *
 * Revision 1.5  2003/08/20 20:34:50  randallc
 * Added flash name member for supporting of creating/overwriting FIS
 * directory partitions.
 *
 * Revision 1.4  2003/07/30 00:36:37  randallc
 * Forgot to add the change log at the bottom of all the source files.
 *
 ******************************************************************************/
