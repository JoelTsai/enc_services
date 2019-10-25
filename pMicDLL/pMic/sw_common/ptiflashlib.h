#ifndef _PTIFLASHLIB_H_
#define _PTIFLASHLIB_H_

/* Cmd type values */
#define FSH_CMD_DONE                0x01
#define FSH_CMD_FILE                0x02
#define FSH_CMD_FILE_TFTP           0x03
#define FSH_CMD_GET_STATUS          0x04
#define FSH_CMD_INIT                0x05
#define FSH_CMD_RESERVED0           0x06
#define FSH_CMD_READ_HEADER         0x07
#define FSH_CMD_RESERVED1           0x08
#define FSH_CMD_VALIDATE_HEADER     0x09
#define FSH_CMD_WRITE_FLASH         0x0a

/* NDIU type values */
#define FSH_CMD_FORCE_CIS           0x20
#define FSH_CMD_FORCE_NDIUS         0x21
#define FSH_CMD_PROCEED_WRITE       0x22

/* Error Codes */
#define FSH_OK                      0
#define FSH_ERR_GENERAL             (-1)
#define FSH_ERR_INVALID_HANDLE      (-2)
#define FSH_ERR_UNKNOWN_STS_TYPE    (-3)
#define FSH_ERR_NO_VALID_FILE       (-4)
#define FSH_ERR_VALIDATION_FAILED   (-5)
#define FSH_ERR_WRITING_FLASH       (-6)

/* Possible Status values - this is (somewhat of) a bit field */
#define FSH_STS_ERROR               (0x80)
#define FSH_STS_COMPLETE            (0x40)
#define FSH_STS_ABORTED             (0x20)
#define FSH_STS_MASK                (FSH_STS_ERROR | FSH_STS_ABORTED | FSH_STS_COMPLETE)
#define FSH_ERROR_STATE( s )        ((s & FSH_STS_ERROR   ) != 0)
#define FSH_ABORT_STATE( s )        ((s & FSH_STS_ABORTED ) != 0)
#define FSH_CMPLT_STATE( s )        ((s & FSH_STS_COMPLETE) != 0)
#define FSH_BASIC_STATE( s )        (s & ~FSH_STS_MASK)

#define FSH_STS_UNKNOWN                         (0xFF)
#define FSH_STS_READY                           (0x00)
#define FSH_STS_LOCKED                          (0x01)
#define FSH_STS_FLASHING                        (0x02)
#define FSH_STS_FLASHING_COMPLETE               (FSH_STS_FLASHING    | FSH_STS_COMPLETE)
#define FSH_STS_FLASHING_ERROR                  (FSH_STS_FLASHING    | FSH_STS_ERROR   )
#define FSH_STS_DOWNLOADING                     (0x03)
#define FSH_STS_DOWNLOADING_COMPLETE            (FSH_STS_DOWNLOADING | FSH_STS_COMPLETE)
#define FSH_STS_DOWNLOADING_ERROR               (FSH_STS_DOWNLOADING | FSH_STS_ERROR   )
#define FSH_STS_VALIDATING                      (0x04)
#define FSH_STS_VALIDATING_COMPLETE             (FSH_STS_VALIDATING  | FSH_STS_COMPLETE)
#define FSH_STS_VALIDATING_ERROR                (FSH_STS_VALIDATING  | FSH_STS_ERROR   )
#define FSH_STS_DELETING                        (0x05)
#define FSH_STS_DELETED                         (FSH_STS_DELETING    | FSH_STS_COMPLETE)

#define FSH_STS_DOWNLOADING_FILE_NOT_FOUND      (FSH_STS_ERROR | 0x0f)
#define FSH_STS_DOWNLOADING_TIMEOUT             (FSH_STS_ERROR | 0x0e)
#define FSH_STS_DOWNLOADING_ACCESS_VIOLATION    (FSH_STS_ERROR | 0x0d)
/* NDIU states */
#define FSH_STS_WAIT_SYNC                       (0x06)
#define FSH_STS_WAIT_SYNC_ERROR                 (FSH_STS_WAIT_SYNC   | FSH_STS_ERROR   )
#define FSH_STS_WAIT_SYNC_ABORTED               (FSH_STS_WAIT_SYNC   | FSH_STS_ABORTED )
#define FSH_STS_WAIT_IMG                        (0x07)
#define FSH_STS_WAIT_IMG_ERROR                  (FSH_STS_WAIT_IMG    | FSH_STS_ERROR   )
#define FSH_STS_WAIT_IMG_ABORTED                (FSH_STS_WAIT_IMG    | FSH_STS_ABORTED )
#define FSH_STS_UPLOADING                       (0x08)
#define FSH_STS_UPLOADING_ERROR                 (FSH_STS_UPLOADING   | FSH_STS_ERROR   )
#define FSH_STS_UPLOADING_ABORTED               (FSH_STS_UPLOADING   | FSH_STS_ABORTED )
#define FSH_STS_MONITORING                      (0x09)
#define FSH_STS_MONITORING_COMPLETE             (FSH_STS_MONITORING  | FSH_STS_COMPLETE)
#define FSH_STS_MONITORING_ERROR                (FSH_STS_MONITORING  | FSH_STS_ERROR   )
#define FSH_STS_MONITORING_ABORTED              (FSH_STS_MONITORING  | FSH_STS_ABORTED )
#define FSH_STS_FAILOVER                        (0x0a)
#define FSH_STS_FAILOVER_COMPLETE               (FSH_STS_FAILOVER    | FSH_STS_COMPLETE)
#define FSH_STS_FAILOVER_ERROR                  (FSH_STS_FAILOVER    | FSH_STS_ERROR   )

#define FSH_STS_REBOOT                          (0x0b)

typedef int fsh_Handle_t;

typedef struct fsh_Status
{
    unsigned int fsts_Status;

    unsigned char fsts_StatusValue[62];

    unsigned char fsts_CtlrID;
    unsigned char fsts_SlotNo;

} fsh_Status_t;

#define NDIU_CMND_UDP_PORT  (8196)
#define NDIU_RESP_UDP_PORT  (8194)
#define PTIF_CMND_UDP_PORT  (8195)
#define PTIF_RESP_UDP_PORT  (8193)

/* Function Prototypes */
#define PTI_TYPE_ECLASS     (0x81)
#define PTI_TYPE_MCLASS     (0x05)

int fsh_Done( int Type );
int fsh_File( int Type, const char *File );
int fsh_FileTftp( int Type, const char *Hostname, int Port, const char *File );
int fsh_GetStatus( int Type, fsh_Status_t *pStatus );
int fsh_Init( int Type );
int fsh_ReadHeader( int Type, ih_t* ImgHeader );
int fsh_ValidateImage( int Type );
int fsh_WriteImage( int Type );

int fsh_ForceCIS( int Type );
int fsh_ForceNDIUS( int Type );

int fsh_ProceedWrite( int Type );

#endif /* _PTIFLASH_LIB_H_ */
