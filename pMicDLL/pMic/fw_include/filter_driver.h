#ifndef __FILTER_DRIVER_H
#define __FILTER_DRIVER_H

#define IDDQ_SUCCESS                    0x0
#define IDDQ_FAILURE                    0xb
#define IDDQ_INVLD_CMD_TYPE             0xc
#define IDDQ_INVLD_CMD_HNDLE            0xd
#define IDDQ_INVLD_SGPTR                0xe
#define IDDQ_INVLD_DMA_DIR              0xf

#define IDSQ_SUCCESS                    0x0
#define IDSQ_FAILURE                    0x11
#define IDSQ_INVLD_CMD_TYPE             0x12
#define IDSQ_INVLD_CMD_HNDLE            0x13
#define IDSQ_INVLD_SGPTR                0x14
#define IDSQ_INVLD_DMA_DIR              0x15

#define OPERATION_FAILURE               0x16
#define OPERATION_SUCCESS               0x17

#define SENSE_BUFFER_LENGTH 	        64
#define MAX_SGLIST 	                    32

#define FER_DMA_IN          0x01
#define FER_DMA_OUT         0x02
#define FER_STATUS          0x04

#define FD_SUCCESS                          0x00
#define FD_BUFFER_OVERRUN                   0x01
#define FD_BUFFER_UNDERRUN                  0x02
#define FD_BUFFER_DMA_FAILURE               0x03
#define FD_FAILURE                          0xFF

#define MAX_QUEUE_ELEMENTS                      512

typedef struct fe_global
{
    u32 fe_device_handle;
    spinlock_t cmdresp_lock;
    spinlock_t wait_list_lock;
#ifdef PROM_FE_ISCSI
	BD_t *fd_list_head;
#endif
}fe_global_t;

struct frontend_cmdresp_chain
{
    struct frontend_cmdresp_chain *fecc_next;
    struct frontend_cmdresp_chain *fecc_prev;
    FrontEndCmdResp_t *fecc_ptrtocmdresp;
    struct iscsi_cmnd *fecc_cmnd_hndle;
};

struct frontend_cmdresp_desc
{
    u32 fecd_count;

    struct frontend_cmdresp_chain *fecd_head;
    struct frontend_cmdresp_chain *fecd_tail;
};

struct frontend_cmdresp_freelist
{
    u32 fcfl_total;
    u32 fcfl_used;
    FrontEndCmdResp_t *fcfl_head;
    FrontEndCmdResp_t *fcfl_tail;
};

struct iscsi_cmnd;

//u32 SubmitCmdToRaidDriver(FrontEndCmdResp_t*);
u32 SubmitDMAStatusToRaidDriver(FrontEndCmdResp_t*);

u8 DeRegisterResource(u8);

int init_filter_driver(void);

u8 ret_cmdresp_to_list(FrontEndCmdResp_t *);
extern FrontEndCmdResp_t *AllocateRioForFE(void);
extern void ReleaseRIOForFE(FrontEndCmdResp_t *cmd_resp);

extern FrontEndCmdResp_t *AllocateReserveRioForFE(void);

extern u32 convert_cmdresp_to_fedesc_for_dma(FrontEndCmdResp_t *cmd_resp);

extern u32 convert_cmdresp_to_fedesc_for_status(FrontEndCmdResp_t *cmd_resp);

extern u32 gNumVolumesInController;

extern fe_global_t fe_ctl;
extern void fd_queue_to_wait_list (FrontEndCmdResp_t *cmd_resp);
/*extern FrontEndCmdResp_t *fd_remove_from_wait_list (void); */
extern void fd_remove_from_wait_list (FrontEndCmdResp_t *cmd_resp);
extern void process_wait_list (void);
extern u8 SubmitCmdRespToRaidDriver (FrontEndCmdResp_t *cmd_resp);

#endif /*__FILTER_DRIVER_H */
