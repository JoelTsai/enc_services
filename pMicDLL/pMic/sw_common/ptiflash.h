/*******************************************************************************
 *
 * Filename    : ptiflash.h
 * Description : Contains mostly error codes for use throughout flashing utility
 *               modules
 * Created on  : 07/29/2003
 * CVS Version : $Id: ptiflash.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _PTIFLASH_H_
#define _PTIFLASH_H_

/* Print Macros */
#ifndef NDEBUG
#include <sys/sysinfo.h>
extern FILE* gDbgOut;
extern FILE* gErrOut;

#define PTIF_DBG( fmt, args... ) \
{ \
    struct sysinfo Info; \
    if ( sysinfo( &Info ) < 0 ) \
        Info.uptime = 0; \
    fprintf( gDbgOut, "%08ld:INF:%04d:%s(%d): "fmt"\n", \
        Info.uptime, getpid(), __FUNCTION__, __LINE__, ##args ); \
    fflush( gDbgOut ); \
}

#define PTIF_ERR( fmt, args... ) \
{ \
    struct sysinfo Info; \
    if ( sysinfo( &Info ) < 0 ) \
        Info.uptime = 0; \
    fprintf( gErrOut, "%08ld:ERR:%04d:%s(%d): "fmt"\n", \
        Info.uptime, getpid(), __FUNCTION__, __LINE__, ##args ); \
    fflush( gDbgOut ); \
}
#else
#define PTIF_DBG( fmt, args... )
#define PTIF_ERR( fmt, args... )
#endif

/* Error Codes */
#define PTIF_OK                             0
#define PTIF_SAME                           1     /* used for comparisons */
#define PTIF_NEED_TO_FLASH                  2     /* used for comparisons */

#define PTIF_ERR_GENERAL                    (-1)
#define PTIF_ERR_BAD_ARGS                   (-2)
#define PTIF_ERR_NO_MEM                     (-3)
#define PTIF_ERR_NOT_MULTI_IMAGE            (-4)
#define PTIF_ERR_IMG_HEADER_NOT_FOUND       (-5)
#define PTIF_ERR_OPENING_FILE               (-6)
#define PTIF_ERR_CLOSING_FILE               (-7)
#define PTIF_ERR_READING_FILE               (-8)
#define PTIF_ERR_WRITING_FILE               (-9)
#define PTIF_ERR_INVALID_CHECKSUM_TYPE      (-10)
#define PTIF_ERR_CHECK_SUM_FAILED           (-11)
#define PTIF_ERR_NO_VALID_IMAGE             (-12)
#define PTIF_ERR_INVALID_CHECK_SUM_TYPE     (-13)
#define PTIF_ERR_INVALID_COMPRESSION_TYPE   (-14)
#define PTIF_ERR_INVALID_FLASH_TYPE         (-15)
#define PTIF_ERR_INVALID_PRODUCT_TYPE       (-16)
#define PTIF_ERR_INVALID_PTISIGNATURE       (-17)
#define PTIF_ERR_TOO_MANY_FLASH_PARTITIONS  (-18)
#define PTIF_ERR_READING_FLASH_MAP          (-19)
#define PTIF_ERR_READING_FLASH              (-20)
#define PTIF_ERR_WRITING_FLASH              (-21)
#define PTIF_ERR_UPDATE_FIS_DIR             (-22)
#define PTIF_ERR_CHANGING_FILE_PERMS        (-23)

#define PTIF_ERR_DIFFERENT_MONTH            (-24) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_DATE             (-25) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_YEAR             (-26) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_MAJOR_NUM        (-27) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_MINOR_NUM        (-28) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_BUILD_NUM        (-29) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_OEM_NUM          (-30) /* used for comparisons */
#define PTIF_ERR_DIFFERENT_CHECKSUM         (-31) /* used for comparisons */

/* 
 * Included for sep firmware download path
 */
#define PTIF_ERR_SEP_FW_COMMIT_FAILED         (-32)
#define PTIF_ERR_SEP_FW_STATUS_FAILED         (-33)


/* Socket errors */
#define PTIF_ERR_OPENING_SOCKET             (-100)
#define PTIF_ERR_BINDING                    (-101)
#define PTIF_ERR_LISTENING                  (-102)
#define PTIF_ERR_ACCEPTING                  (-103)
#define PTIF_ERR_CONNECTING                 (-104)
#define PTIF_ERR_NOT_A_SOCKET               (-105)
#define PTIF_ERR_SOCKET_PERMISSIONS         (-106)
#define PTIF_ERR_STALE_SOCKET               (-107)
#define PTIF_ERR_READING_SOCKET             (-108)
#define PTIF_ERR_WRITING_SOCKET             (-109)

#define PTIF_DEVNODE_BASENAME               "/dev/mtdblock"
#define PTIF_DEVNODE_SEP                    "/dev/sep"
#define PTIF_FLASH_PATH                     "/islavista/flash"
#define PTIF_FILE_LENGTH                    256
#define PTIF_HOST_NAME_LENGTH               128
#define PTIF_MAX_FSH_HANDLES                5

typedef struct ptif_Progress
{
    unsigned int  pp_Status;
    char          pp_Filename[PTIF_FILE_LENGTH];
    char          pp_Hostname[PTIF_HOST_NAME_LENGTH];
    int           pp_TftpPortNum;
    int           pp_UseTftp;
    int           pp_TotalSizeToBeFlashed;
    int           pp_TotalSizeFlashedSoFar;
    unsigned char pp_FlashPercentage;
    unsigned char pp_DownloadPercentage;
    unsigned char pp_Reserved0[2];
} ptif_Process_t;

#define FSH_MAX_CMD_DATA_SIZE               512
#define FSH_MAX_RSP_DATA_SIZE               512

#define FSH_MAX_STATUS_COUNT                2
#define FSH_LOCAL_STATUS                    0
#define FSH_REMOTE_STATUS                   1

#define FSH_VERSION                         1

typedef struct fsh_TftpSettings
{
    char fts_Filename[PTIF_FILE_LENGTH];
    char fts_Hostname[PTIF_HOST_NAME_LENGTH];
    int  fts_PortNum;
} fsh_TftpSettings_t;

typedef struct fsh_Command
{
    unsigned int fcmd_CommandType;
    unsigned int fcmd_Version;

    unsigned char Rsvd[7];
    unsigned char fcmd_Tag;

    union
    {
        unsigned char      fcmd_Bytes[FSH_MAX_CMD_DATA_SIZE];
        char               fcmd_Filename[PTIF_FILE_LENGTH];
        fsh_TftpSettings_t fcmd_Tftp;
    } fcmd_CmdData;
} fsh_Command_t;

typedef struct fsh_Response
{
    unsigned int frsp_CommandType;
    unsigned int frsp_Version;

    int          frsp_RetStatus;

    unsigned char Rsvd[3];
    unsigned char frsp_Tag;

    union
    {
        unsigned char frsp_Bytes[FSH_MAX_RSP_DATA_SIZE];
        ih_t          frsp_ImageHeader;
        fsh_Status_t  frsp_Status;

        fsh_Status_t  frsp_CtlrSts[FSH_MAX_STATUS_COUNT];

    } frsp_RspData;

} fsh_Response_t;

/* Function Declarations */
int ptif_ReadFlashPartitionMap (char *Filename);
int ptif_ValidateImage (u8 *FileToFlash, ih_t *pImgHeader);
int ptif_CalculateCheckSum (char *pDataFile, ih_t *pImgHeader,
        checkSum_t *pCksum);
int ptif_ValidateCheckSum (checkSum_t *Correct, checkSum_t *Test,
        unsigned char CheckSumType);
int ptif_UpdateFisDirectory (ih_t *pImgHeader,
        flashMapHeader_t *pFlashMapHeader);
int ptif_UpdateVersionPartition (ih_t *pImgHeader,
        flashMapHeader_t *pFlashMapHeader);
int ptif_FlashImage( ptif_Process_t* pProcess, char* FileToFlash, ih_t* pImgHeader,
    flashMapHeader_t* pFlashMapHeader, int UpgradeSepInFlash, int UpgradeExpDirectly );

#endif /* _PTIFLASH_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: ptiflash.h,v $
 * Revision 1.3  2006/11/01 23:48:33  david.chiu
 * no message
 *
 * Revision 1.2  2006/10/12 20:50:23  david.chiu
 * no message
 *
 * Revision 1.1  2006/08/14 18:41:56  david.chiu
 * Copied from util/ptiflash
 * Added extra status in union for dual control
 *
 * Revision 1.7  2006/02/09 01:30:36  randallc
 * 1. Added support for an image containing more than 6 images (as in the case
 *    of the "all" image file which as fw, sw, ramdisk, oem, kernel, redboot
 *    rom & redboot ram.
 * 2. Added check for redboot rom before flashing.  If version and build date
 *    are the same as the image that is being flashed and the checksum of the
 *    redboot rom image on the flash chip is correct, then the flashing of the
 *    redboot rom image is skipped.
 *
 * Revision 1.6  2004/02/10 19:17:27  randallc
 * removed file handle support as this was complicated and unecessary.  Only
 * one flash process should be running at a time.
 *
 * Revision 1.5  2003/10/14 22:34:36  randallc
 * Add support for flash sep firmware.
 *
 * Revision 1.4  2003/10/01 01:26:56  randallc
 * 1)  fixed bug when calculating percentages of a multi-image file.
 * 2)  changed permissions on socket file (/tmp/ptif_pipe) to be 777 so that
 *     when thttpd ran as nobody and used ptiflashlib that it could be opened.
 *
 * Revision 1.3  2003/09/03 22:31:50  randallc
 * Added library support for flashing.
 *
 * Revision 1.2  2003/07/30 00:36:37  randallc
 * Forgot to add the change log at the bottom of all the source files.
 *
 ******************************************************************************/
