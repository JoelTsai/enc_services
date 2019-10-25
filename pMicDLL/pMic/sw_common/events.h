#ifndef _EVENTS_H_
#define _EVENTS_H_

/*******************************************************************************
 *
 * Filename    : events.h
 * Description :
 * Created on  : 04/11/2003
 * CVS Version : $Id: events.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/

/*
 * NOTE:
 *
 * An event ID is defined as the unique value of an event.  An event ID is made
 * from two values, the event class and the event code.  Event codes are NOT
 * unique!
 *
 * Macros:
 *
 * EVT_CLASS_*      defines for event classes
 * EVT_CODE_*       defines for each event within a class - remember, these
 *                  are NOT unique
 * EVT_ID_*         defines for the event class & event id together - these are
 *                  unqiue values that identify a particular event
 */
#define EVT_MAX_CLASSES                             64
#define EVT_MAX_EVENTS_PER_CLASS                    256

#define EVT_SEVERITY_MAX_LEVEL                      0x7
#define EVT_SEVERITY_UNKNOWN                        0x0
#define EVT_SEVERITY_OTHER                          0x1
#define EVT_SEVERITY_INFORMATION                    0x2
#define EVT_SEVERITY_WARNING                        0x3
#define EVT_SEVERITY_MINOR                          0x4
#define EVT_SEVERITY_MAJOR                          0x5
#define EVT_SEVERITY_CRITICAL                       0x6
#define EVT_SEVERITY_FATAL                          0x7


/*
 * EVT_SEVERITY_INVALID_EVT used to signify that event is not a valid event in
 * event info structure - not to be used for logging event
 */
#define EVT_SEVERITY_INVALID_EVT                    0xFF

/* Event Classes */
#define EVT_CURRENT_MAX_CLASSES                     0x28

#define EVT_CLASS_BATTERY                           0x0001
#define EVT_CLASS_BBU                               0x0002
#define EVT_CLASS_REDUNDANCY_CHECK                  0x0003
#define EVT_CLASS_CONTROLLER                        0x0004
#define EVT_CLASS_COOLING_DEVICE                    0x0005
#define EVT_CLASS_SEP                               0x0006
#define EVT_CLASS_FRONT_END_CONTROLLER              0x0007
#define EVT_CLASS_INITIALIZATION                    0x0008
#define EVT_CLASS_LOGICAL_DRIVE                     0x0009
#define EVT_CLASS_MDD                               0x000a
#define EVT_CLASS_MEDIA_PATROL                      0x000b
#define EVT_CLASS_RAID_MIGRATION                    0x000c
#define EVT_CLASS_PHYSICAL_DISK                     0x000d
#define EVT_CLASS_PSU                               0x000e
#define EVT_CLASS_REBUILD                           0x000f
#define EVT_CLASS_SMART                             0x0010
#define EVT_CLASS_SUBSYSTEM                         0x0011
#define EVT_CLASS_SYNCHRONIZATION                   0x0012
#define EVT_CLASS_DISK_ARRAY                        0x0013
#define EVT_CLASS_BACK_END_CONTROLLER               0x0014
#define EVT_CLASS_ONLINE_CAPACITY_EXPANSION         0x0015
#define EVT_CLASS_RAID_LEVEL_MIGRATION              0x0016
#define EVT_CLASS_STRIPE_LEVEL_MIGRATION            0x0017

/* Class only for software.....fw is not to use this class id! */
#define EVT_CLASS_SOFTWARE                          0x0018

#define EVT_CLASS_RESOURCE_CONTROL                  0x0019     /* added by Walen */
#define EVT_CLASS_BLOWER                            0x001a
#define EVT_CLASS_PDM                               0x001b     /* added by Walen 03/11/04 */

#define EVT_CLASS_CUSTOM_FEATURE                    0x001c     /* added by Walen 03/22/04 for custom function that does
                                                                  not fit in any about class and features that might only
                                                                  for debug and special request. */
#define EVT_CLASS_SPARE_CHECK                       0x001d
#define EVT_CLASS_TEMPERATURE                       0x001e
#define EVT_CLASS_FW_UPDATE                         0x001f

#define EVT_CLASS_NAS                               0x0020
/* 0x20 is taken by LCD class */
#define EVT_CLASS_UPS                               0x0021
#define EVT_CLASS_PLATFORM_CBAY                     0x0022

#define EVT_CLASS_OS                                0x0024

#define EVT_CLASS_POWER_MANAGEMENT                  0x0027

#define EVT_CLASS_UNKNOWN                           0xFFFF

/*******************************
 * Event Codes listed by class *
 ******************************/

/* EVT_CLASS_BATTERY                    0x01 */
#define EVT_CODE_BATTERY_TEMPERATURE_RISE           0x00
#define EVT_CODE_BATTERY_TEMPERATURE_DROPPED        0x01
#define EVT_CODE_BATTERY_CAPACITY_BELOW_THRESHOLD   0x02
#define EVT_CODE_BATTERY_CAPACITY_NORMAL            0x03
#define EVT_CODE_BATTERY_DISCHARGING                0x04
#define EVT_CODE_BATTERY_CHARGING                   0x05
#define EVT_CODE_BATTERY_MAINTENANCE_MODE_EXIT      0x06
#define EVT_CODE_BATTERY_NOT_FUNCTIONING            0x07
#define EVT_CODE_BATTERY_SELF_TEST_PASS             0x08
#define EVT_CODE_BATTERY_SELF_TEST_FAIL             0x09
#define EVT_CODE_BATTERY_REACHED_CYCLE_THRESHOLD    0x0A
#define EVT_CODE_BATTERY_REMOVED                    0x0B
#define EVT_CODE_BATTERY_INSTALLED                  0x0C
#define EVT_CODE_BATTERY_CHARGING_FOR_TOO_LONG      0x0D
#define EVT_CODE_BATTERY_SELF_TEST_START            0x0E
#define EVT_CODE_BATTERY_SELF_TEST_END              0x0F
#define EVT_CODE_BATTERY_SEND_NOTIFICATION         0x10
#define EVT_CODE_BATTERY_WB_CACHE_SWITCHED_TO_WT   0x11
#define EVT_CODE_BATTERY_WT_CACHE_SWITCHED_TO_WB   0x12
#define EVT_CODE_BATTERY_CHARGING_IN_HI_TEMP        0x13    /* charging continue in high temperature */

#define EVT_CODE_BATTERY_MISMATCHED_ID              0x14    /* mismatch between battery board id and battery id */
#define EVT_CODE_BATTERY_CACHE_ENABLE_NO_BTY        0x15    /* cache enable w/o battery support */
#define EVT_CODE_BATTERY_FULL_CHARGED               0x16    /* full charge event */
#define EVT_CODE_BATTERY_NOT_PRESENT                0x17
#define EVT_CODE_BATTERY_HAS_FAILED                 0x18
/* END EVT_CLASS_BATTERY                0x01 */

/* EVT_CLASS_BBU                        0x02 */
#define EVT_CLASS_BBU_FLUSH_ABORT                   0x00            /* added by Walen */
#define EVT_CLASS_BBU_FLUSH_START                   0x01            /* added by Walen */
#define EVT_CLASS_BBU_FLUSH_END                     0x02            /* added by Walen */
#define EVT_CLASS_BBU_FLUSH_FAILED                  0x03            /* added by Walen */

/* END EVT_CLASS_BBU                    0x02 */

/* EVT_CLASS_REDUNDANCY_CHECK           0x03 */
#define EVT_CODE_RC_STARTED                         0x00
#define EVT_CODE_RC_COMPLETED                       0x01
#define EVT_CODE_RC_PAUSED                          0x02
#define EVT_CODE_RC_RESUMED                         0x03
#define EVT_CODE_RC_STOPPED                         0x04
#define EVT_CODE_RC_PD_ERROR_ENCOUNTERED            0x05
#define EVT_CODE_RC_ABORTED_INTERNAL_ERROR          0x06
#define EVT_CODE_RC_INCONSISTENT_STRIPE             0x07
#define EVT_CODE_RC_QUEUED                          0x08
#define EVT_CODE_RC_FIXED_INCONSISTENCE             0x09    /* added by Walen */
#define EVT_CODE_RC_STOPPED_INTERNALLY              0x0A

/* END EVT_CLASS_REDUNDANCY_CHECK       0x03 */

/* EVT_CLASS_CONTROLLER                 0x04 */
#define EVT_CODE_CONTROLLER_EVT_LOG_ENABLED                 0x00
#define EVT_CODE_CONTROLLER_EVT_LOG_DISABLED                0x01
#define EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_RAM             0x02
#define EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_NVRAM           0x03
#define EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_MDD             0x04
#define EVT_CODE_CONTROLLER_SYSTEM_STARTED                  0x05
#define EVT_CODE_CONTROLLER_SYSTEM_STOPPED                  0x06
#define EVT_CODE_CONTROLLER_PARAMETER_CHANGED               0x07
#define EVT_CODE_CONTROLLER_WATCHDOG_RESET                  0x08
#define EVT_CODE_CONTROLLER_NEW_CRASH_INFO_FOUND            0x09
#define EVT_CODE_CONTROLLER_DETECTED                        0x0A
#define EVT_CODE_CONTROLLER_REMOVED                         0x0B
#define EVT_CODE_CONTROLLER_REVISION_MISMATCH               0x0C
#define EVT_CODE_CONTROLLER_PATH_FAILOVER                   0x0D
#define EVT_CODE_CONTROLLER_USER_REQ_MAINTENANCE_MODE       0x0E
/* David Chiu 11.09.2005 Heart Beat Event Codes */
#define EVT_CODE_CONTROLLER_HBM_LOCAL_STRTD         0x10    /* Local HB started */
#define EVT_CODE_CONTROLLER_HBM_LOCAL_STPPD         0x11    /* Local HB stopped */
#define EVT_CODE_CONTROLLER_HBM_REMOTE_STRTD        0x12    /* Remote HB started (received) */
#define EVT_CODE_CONTROLLER_HBM_REMOTE_STPPD        0x13    /* Remote HB stopped (timed out) */
#define EVT_CODE_CONTROLLER_HBM_SKIPPED             0x14    /* Remote HB sequence no. skipped */
#define EVT_CODE_CONTROLLER_HBM_FROZEN              0x15    /* Local Main Scheduler Frozen */
/* controller set to maintenance mode internally due to following */
#define EVT_CODE_CONTROLLER_MNTMODE_CFGPD_NOT_SEEN         0x16
#define EVT_CODE_CONTROLLER_MNTMODE_DISKTYPE_MISMATCH      0x17
#define EVT_CODE_CONTROLLER_MNTMODE_DISKWWN_MISMATCH       0x18
#define EVT_CODE_CONTROLLER_MNTMODE_DISKSATA_MISMATCH      0x19
#define EVT_CODE_CONTROLLER_MNTMODE_DISKID_MISMATCH        0x20
#define EVT_CODE_CONTROLLER_MNTMODE_NODRIVES_SEEN          0x21
#define EVT_CODE_CONTROLLER_STARTED                        0x22
#define EVT_CODE_CONTROLLER_ACTIVE                         0x23
#define EVT_CODE_CONTROLLER_STANDBY                        0x24
#define EVT_CODE_CONTROLLER_FAILOVER_PARTNER_REMOVED       0x25
#define EVT_CODE_CONTROLLER_FAILOVER_HEART_BEAT_STOPPED    0x26
#define EVT_CODE_CONTROLLER_MNTMODE_HARDWARE_MISMATCH      0x27
#define EVT_CODE_CONTROLLER_FW_MISMATCH_WITH_PARTNER       0x28
#define EVT_CODE_CONTROLLER_MNTMODE_FW_FLASHING_IN_PARTNER 0x29
#define EVT_CODE_CONTROLLER_FW_FLASH_FAILOVER_TO_PARTNER   0x2A

#define EVT_CODE_CONTROLLER_RESET_PARTNER_DUE_TO_FAILOVER  0x2B
#define EVT_CODE_CONTROLLER_RESET_DUE_TO_FAILOVER          0x2C
#define EVT_CODE_CONTROLLER_MNTMODE_FIRMWARE_MISMATCH      0x2D
#define EVT_CODE_CONTROLLER_RESET_AS_NOT_ABLE_TO_JOIN_PARTNER      0x2E
#define EVT_CODE_CONTROLLER_MNTMODE_HW_MISMATCH_BOARD_MODEL_VER    0x30
#define EVT_CODE_CONTROLLER_MNTMODE_HW_MISMATCH_MEM_SIZE   0x31

#define EVT_CODE_PARTNER_CTRL_MNTMODE_CFGPD_NOT_SEEN_LD_NONREDUNDANT    0x32
#define EVT_CODE_CONTROLLER_CRASH_RESET                    0x33
#define EVT_CODE_CONTROLLER_TRIGGER_FAILOVER               0x36
#define EVT_CODE_CONTROLLER_TRIGGER_FAILBACK               0x37

#define EVT_CODE_CONTROLLER_INCOMPATIBLE                    0x38
#define EVT_CODE_CONTROLLER_BAD_VPD                         0x39
#define EVT_CODE_CONTROLLER_MNTMODE_INCOMPATIBLE            0x3A
#define EVT_CODE_CONTROLLER_MNTMODE_BAD_VPD                 0x3B

#define EVT_CODE_CONTROLLER_BAD_MAC                     (0x3C)
#define EVT_CODE_CONTROLLER_MGMT_PORT_UP                (0x3D)
#define EVT_CODE_CONTROLLER_MGMT_PORT_DN                (0x3E)
#define EVT_CODE_CONTROLLER_MGMT_PORT_DHCP_ACQUIRED     (0x3F)
#define EVT_CODE_CONTROLLER_MGMT_PORT_LINK_LOCAL        (0x40)

typedef struct {

    u16 nei_PageCode;
    u8 Rsvd0[2];

    u8 nei_MAC[6];
    u8 Rsvd1[2];

    u8 Rsvd2[12];
    u8 nei_WWN[8];

} NetworkEventInfo_t;

/* END EVT_CLASS_CONTROLLER             0x04 */

/* EVT_CLASS_COOLING_DEVICE             0x05 */
#define EVT_CODE_COOLING_DEVICE_STARTED             0x00
#define EVT_CODE_COOLING_DEVICE_STOPPED             0x01
#define EVT_CODE_COOLING_DEVICE_SPEED_INCREASED     0x02
#define EVT_CODE_COOLING_DEVICE_SPEED_DECREASED     0x03
#define EVT_CODE_COOLING_DEVICE_MALFUNCTIONING      0x04
#define EVT_CODE_COOLING_DEVICE_INSERTED            0x05
#define EVT_CODE_COOLING_DEVICE_REMOVED             0x06
#define EVT_CODE_COOLING_DEVICE_FUNCTIONAL          0x07
#define EVT_CODE_COOLING_DEVICE_NOT_INSTALLED       0x08
#define EVT_CODE_COOLING_DEVICE_UNKNOWN_STS         0x09
/* END EVT_CLASS_COOLING_DEVICE         0x05 */

/* EVT_CLASS_SEP                        0x06 */
#define EVT_CODE_SEP_COM_ERROR                      0x00        /* added by Walen */
#define EVT_CODE_SEP_TIMEOUT                        0x01        /* added by Walen */
#define EVT_CODE_SEP_ONLINE                         0x02        /* added by Walen */
#define EVT_CODE_SEP_FRU_STATE_CHANGE               0x03        /* added by Walen */
#define EVT_CODE_SEP_DETECTED                       0x0A
#define EVT_CODE_SEP_REMOVED                        0x0B
#define EVT_CODE_SEP_I2C_ACCESS_FAIL                0x0E
#define EVT_CODE_SEP_I2C_ACCESS_RECOVERED           0x0F
#define EVT_CODE_SEP_JBOD_INCOMPATIBLE              0x15
/* END EVT_CLASS_SEP                    0x06 */

/* EVT_CLASS_FRONT_END_CONTROLLER       0x07 */
#define EVT_CODE_FEC_PARITY_ERROR                   0x00
#define EVT_CODE_FEC_DATA_PARITY_ERROR              0x01
#define EVT_CODE_FEC_COMMAND_PARITY_ERROR           0x02
#define EVT_CODE_FEC_BUS_RESET_DETECTED             0x03
#define EVT_CODE_FEC_UNRECOVERABLE_ERROR            0x04
#define EVT_CODE_FEC_ABORT_TASK                     0x05
#define EVT_CODE_FEC_ABORT_TASK_SET                 0x06
#define EVT_CODE_FEC_CLEAR_ACA                      0x07
#define EVT_CODE_FEC_CLEAR_TASK_SET                 0x08
#define EVT_CODE_FEC_LUN_RESET                      0x09
#define EVT_CODE_FEC_INITIATOR_DETECTED_ERROR       0x0A
#define EVT_CODE_FEC_ILLEGAL_SECONDARY_IDENTIFY     0x0B
#define EVT_CODE_FEC_MESSAGE_PARITY_ERROR           0x0C
#define EVT_CODE_FEC_BUS_REBOOT                     0x0D
#define EVT_CODE_FEC_LINK_UP                        0x0E
#define EVT_CODE_FEC_LINK_DOWN                      0x0F
#define EVT_CODE_FEC_UNKNOWN_ERROR                  0x10            /* added by Walen */
#define EVT_CODE_FEC_SYSTEM_ERROR                   0x11
#define EVT_CODE_FEC_FATAL_ERROR                    0x12
#define EVT_CODE_FEC_SETTINGS_CHANGED				0x13
#define EVT_CODE_FEC_WARM_RESET                     0x14
#define EVT_CODE_FEC_COLD_RESET                     0x15

#define EVT_CODE_FEC_PCI_FMU_HANDSHAKE_WARNING      0x60
#define EVT_CODE_FEC_PCI_FMU_CONN_STOP              0x61
#define EVT_CODE_FEC_PCI_FMU_UNLOAD                 0x62

// Fibre channel subgroup
#define EVT_CODE_FEC_FC_BUS_RESET_DETECTED             	0x80
#define EVT_CODE_FEC_FC_LUN_RESET                      	0x81
#define EVT_CODE_FEC_FC_FATAL_ERROR                    	0x82
#define EVT_CODE_FEC_FC_LINK_UP                       	0x83
#define EVT_CODE_FEC_FC_LINK_DOWN                      	0x84
#define EVT_CODE_FEC_FC_SETTINGS_CHANGED		0x85

// PSCSI subgroup
#if 1
#define EVT_CODE_FEC_SCSI_SETTINGS_CHANGED          0xA0
#else
#define EVT_CODE_FEC_SCSI_TARGET_LIST_CHANGED       0xA0
#define EVT_CODE_FEC_SCSI_TERM_CNTL_CHANGED         0xA1
#define EVT_CODE_FEC_SCSI_MODE_PAGE_19_CHANGED      0xA2
#define EVT_CODE_FEC_SCSI_TGT_SETTINGS_CHANGED      0xA3
#endif
#define EVT_CODE_FEC_SCSI_EXTBUSRESET               0xA6
#define EVT_CODE_FEC_SCSI_IOC_BUS_RESET             0xA7
#define EVT_CODE_FEC_SCSI_CMD_PARITY_ERR            0xA8
#define EVT_CODE_FEC_SCSI_MSG_OUT_PARITY_ERR        0xA9
#define EVT_CODE_FEC_SCSI_CMD_CRC_ERR               0xAA
#define EVT_CODE_FEC_SCSI_PROTOCOL_ERR              0xAB
#define EVT_CODE_FEC_SCSI_DATA_OUT_PARITY_ERR       0xAC
#define EVT_CODE_FEC_SCSI_DATA_OUT_CRC_ERR          0xAD
#define EVT_CODE_FEC_SCSI_UNKNOWN_PRIORITYREASON    0xAE


/* END EVT_CLASS_FRONT_END_CONTROLLER   0x07 */

/* EVT_CLASS_INITIALIZATION             0x08 */
#define EVT_CODE_LDI_FULL_STARTED                   0x00
#define EVT_CODE_LDI_FULL_COMPLETED                 0x01
#define EVT_CODE_LDI_FULL_PAUSED                    0x02
#define EVT_CODE_LDI_FULL_RESUMED                   0x03
#define EVT_CODE_LDI_FULL_STOPPED                   0x04
#define EVT_CODE_LDI_FULL_MARKED_OFFLINE            0x05
#define EVT_CODE_LDI_FULL_ABORTED_INTERNAL_ERROR    0x06
#define EVT_CODE_LDI_QUICK_STARTED                  0x07
#define EVT_CODE_LDI_QUICK_COMPLETED                0x08
#define EVT_CODE_LDI_QUICK_PAUSED                   0x09
#define EVT_CODE_LDI_QUICK_RESUMED                  0x0A
#define EVT_CODE_LDI_QUICK_STOPPED                  0x0B
#define EVT_CODE_LDI_QUICK_MARKED_OFFLINE           0x0C
#define EVT_CODE_LDI_QUICK_ABORTED_INTERNAL_ERROR   0x0D

#define EVT_CODE_LDI_FULL_QUEUED                    0x0E
#define EVT_CODE_LDI_QUICK_QUEUED                   0x0F
#define EVT_CODE_LDI_IS_IN_PROGRESS                 0x10
/* END EVT_CLASS_INITIALIZATION         0x08 */

/* EVT_CLASS_LOGICAL_DRIVE              0x09 */
#define EVT_CODE_LD_CREATED                         0x00
#define EVT_CODE_LD_DELETED                         0x01
#define EVT_CODE_LD_ONLINE                          0x02
#define EVT_CODE_LD_OFFLINE                         0x03
#define EVT_CODE_LD_CRITICAL                        0x04
#define EVT_CODE_LD_AXLE_ONLINE                     0x05
#define EVT_CODE_LD_MARKED_SYNCED_BY_REBUILD        0x06
#define EVT_CODE_LD_SETTINGS_CHANGE					0x07
#define EVT_CODE_LD_QUICKINIT_START                 0x08
#define EVT_CODE_LD_QUICKINIT_COMPLETED             0x09
#define EVT_CODE_LD_CREATED_IO                      0x0a
#define EVT_CODE_LD_DELETED_IO                      0x0b
#define EVT_CODE_LD_DEGRADE                         0x0c
#define EVT_CODE_LD_DEGRADE_WORSE                   0x0d


/* END EVT_CLASS_LOGICAL_DRIVE          0x09 */

/* EVT_CLASS_MDD                        0x0a */
#define EVT_CODE_DDF_WRITE_FAILED                   0x00
/* END EVT_CLASS_MDD                    0x0a */

/* EVT_CLASS_MEDIA_PATROL               0x0b */
#define EVT_CODE_MP_STARTED                         0x00
#define EVT_CODE_MP_COMPLETED                       0x01
#define EVT_CODE_MP_PAUSED                          0x02
#define EVT_CODE_MP_RESUMED                         0x03
#define EVT_CODE_MP_STOPPED                         0x04
#define EVT_CODE_MP_PD_ERROR_ENCOUNTERED            0x05
#define EVT_CODE_MP_ABORTED_INTERNAL_ERROR          0x06
#define EVT_CODE_MP_QUEUED                          0x07
#define EVT_CODE_MP_STOPPED_INTERNALLY              0x08
#define EVT_CODE_MP_IS_IN_PROGRESS                  0x09
/* END EVT_CLASS_MEDIA_PATROL           0x0b */

/* EVT_CLASS_RAID_MIGRATION             0x0c */
#define EVT_CODE_RM_STARTED                         0x00
#define EVT_CODE_RM_COMPLETED                       0x01
#define EVT_CODE_RM_PAUSED                          0x02
#define EVT_CODE_RM_RESUMED                         0x03
#define EVT_CODE_RM_STOPPED                         0x04
#define EVT_CODE_RM_PD_ERROR_ENCOUNTERED            0x05
#define EVT_CODE_RM_ABORTED_INTERNAL_ERROR          0x06
#define EVT_CODE_RM_QUEUED                          0x07
#define EVT_CODE_RM_STALE_NV_DETECTED               0x08
#define EVT_CODE_RM_STALE_NV_CLEARED                0x09
#define EVT_CODE_RM_MISSING_NV_ARRAY_MADE_INCOMPLETE     0x0A
#define EVT_CODE_RM_MISSING_NV_ARRAY_INCOMPLETE_ACCEPTED 0x0B
#define EVT_CODE_RM_IS_IN_PROGRESS                  0x0C
#define EVT_CODE_RM_LD_OFFLINE_SKIPPED              0x0D
/* END EVT_CLASS_RAID_MIGRATION         0x0c */

/* EVT_CLASS_PHYSICAL_DISK              0x0d */
#define EVT_CODE_PD_MARKED_ONLINE                   0x00
#define EVT_CODE_PD_MARKED_OFFLINE                  0x01
#define EVT_CODE_PD_MARKED_DEAD                     0x02
#define EVT_CODE_PD_RESET                           0x03
#define EVT_CODE_PD_GLOBAL_SPARE_ADDED              0x04
#define EVT_CODE_PD_GLOBAL_SPARE_DELETED            0x05
#define EVT_CODE_PD_GLOBAL_SPARE_USED               0x06
#define EVT_CODE_PD_DEDICATED_SPARE_ADDED           0x07
#define EVT_CODE_PD_DEDICATED_SPARE_DELETED         0x08
#define EVT_CODE_PD_DEDICATED_SPARE_USED            0x09
#define EVT_CODE_PD_DETECTED                        0x0A
#define EVT_CODE_PD_REMOVED                         0x0B
#define EVT_CODE_PD_RETRIED_COMMAND                 0x0C
#define EVT_CODE_PD_ECC_ERROR                       0x0D
#define EVT_CODE_PD_CRC_ERROR                       0x0E
#define EVT_CODE_PD_BAD_SECTOR                      0x0F
#define EVT_CODE_PD_ERROR_IN_REMAP_SECTORS          0x10
#define EVT_CODE_PD_COMMAND_TIME_OUT                0x11
#define EVT_CODE_PD_NEGOTIATION_SPEED_DECREASED     0x12
#define EVT_CODE_PD_NOT_PRESENT                     0x13
#define EVT_CODE_PD_NON_ECC_MEDIA_ERROR             0x14
#define EVT_CODE_PD_PFA_ERROR                       0x15
#define EVT_CODE_ONLINE_DDF_CFG_DEAD_PD_FOUND       0x16
#define EVT_CODE_PD_PARAMETER_PAGE0_CHANGED         0x17
#define EVT_CODE_PD_PARAMETER_PAGE1_CHANGED         0x18
#define EVT_CODE_PD_SMART_CMD_FAIL                  0x19        /* added by Walen (01/11/05) */
#define EVT_CODE_PD_MARKED_DEAD_DRIVE_REMOVED       0x1a
#define EVT_CODE_PD_MARKED_DEAD_RSA_FAILED          0x1b
#define EVT_CODE_PD_MARKED_DEAD_PFA_FOUND           0x1c
#define EVT_CODE_PD_MARKED_DEAD_FORCED              0x1d
#define EVT_CODE_PD_PATH_FAILOVER                   0x1e
#define EVT_CODE_PD_PARAMETER_PAGE3_CHANGED         0x1f
#define EVT_CODE_PD_NOT_SEEN                        0x20
#define EVT_CODE_PD_SINGLE_PORTED_FOUND             0x21
#define EVT_CODE_PD_DID_NOT_BECOME_READY            0x22   /* TUR failed */

#define EVT_CODE_PD_PFA_BY_USER                     0x24        /* for Clearbay Only */
#define EVT_CODE_PD_INCOMPATIBLE                    0x30


/* 0x31 to 0x36 are used by PTT team */


#define EVT_CODE_PD_UPDATE_PD_WCACHE_ENABLE         0x37    /* for UPS event only. the disk Wcache is enabled */
#define EVT_CODE_PD_UPDATE_PD_WCACHE_DISABLE        0x38    /* for UPS event only. the disk Wcache is disable */
#define EVT_CODE_PD_TEMP_OVER                       0x39
#define EVT_CODE_PD_TEMP_RETURNED_TO_NORMAL         0x3a

// not re rcm logs this #define EVT_CODE_ONLINE_DDF_CFG_PD_FOUND            0x17
/* END EVT_CLASS_PHYSICAL_DISK          0x0d */

/* EVT_CLASS_PSU                        0x0e */
#define EVT_CODE_PSU_NOT_PRESENT                    0x00       /* added by Walen */
//#define EVT_CODE_PSU_OFF                            0x01       /* added by Walen */
//#define EVT_CODE_PSU_ON                             0x02       /* added by Walen */
#define EVT_CODE_PSU_INSTALLED_AND_TURNED_ON        0x03
#define EVT_CODE_PSU_INSTALLED_AND_TURNED_OFF       0x04
#define EVT_CODE_PSU_OPERATIONAL_AND_TURNED_ON      0x05
#define EVT_CODE_PSU_OPERATIONAL_AND_TURNED_OFF     0x06
#define EVT_CODE_PSU_MALFUNCTIONING_AND_TURNED_ON   0x07
#define EVT_CODE_PSU_MALFUNCTIONING_AND_TURNED_OFF  0x08
#define EVT_CODE_PSU_REMOVED                        0x09

#define EVT_CODE_PSU_12V_OUT_OF_RANGE               0x10        /* for V4 group */
#define EVT_CODE_PSU_5V_OUT_OF_RANGE                0x11        /* for V4 group */
#define EVT_CODE_PSU_3_3V_OUT_OF_RANGE              0x12        /* for V4 group */
#define EVT_CODE_PSU_3_3V_NORMAL                    0x13        /* for V4 group */
#define EVT_CODE_PSU_5V_NORMAL                      0x14        /* for V4 group */
#define EVT_CODE_PSU_12V_NORMAL                     0x15        /* for V4 group */
/* END EVT_CLASS_PSU                    0x0e */

/* EVT_CLASS_REBUILD                    0x0f */
#define EVT_CODE_REBUILD_STARTED                    0x00
#define EVT_CODE_REBUILD_COMPLETED                  0x01
#define EVT_CODE_REBUILD_PAUSED                     0x02
#define EVT_CODE_REBUILD_RESUMED                    0x03
#define EVT_CODE_REBUILD_STOPPED                    0x04
#define EVT_CODE_REBUILD_PENDING                    0x05
//#define EVT_CODE_REBUILD_NOT_FAULT_TOLERANT         0x06
#define EVT_CODE_REBUILD_ABORTED_INTERNAL_ERROR     0x07
//#define EVT_CODE_REBUILD_MARKED_LD_SYNCHRONIZED     0x08
#define EVT_CODE_REBUILD_QUEUED                     0x09
#define EVT_CODE_REBUILD_TRANSITION_STARTED         0x0A
#define EVT_CODE_REBUILD_TRANSITION_COMPLETED       0x0B
#define EVT_CODE_REBUILD_TRANSITION_PAUSED          0x0C
#define EVT_CODE_REBUILD_TRANSITION_RESUMED         0x0D
#define EVT_CODE_REBUILD_TRANSITION_STOPPED         0x0E
#define EVT_CODE_REBUILD_TRANSITION_SWITCH_TO_REBUILD       0x0F
#define EVT_CODE_REBUILD_INVALID_DISK               0x10    /* added by Walen -- refer doc */
#define EVT_CODE_REBUILD_STOPPED_INTERNALLY         0x11
#define EVT_CODE_REBUILD_IS_IN_PROGRESS             0x12
#define EVT_CODE_REBUILD_TRANSITION_IS_IN_PROGRESS  0x13
/* END EVT_CLASS_REBUILD                0x0f */

/* EVT_CLASS_SMART                      0x10 */
#define EVT_CODE_SMART_ERROR_RECEIVED               0x00
/* END EVT_CLASS_SMART                  0x10 */

/* EVT_CLASS_SUBSYSTEM                  0x11 */
#define EVT_CODE_SUBSYS_12V_OUT_OF_RANGE            0x00        /* for V3 group */
#define EVT_CODE_SUBSYS_5V_OUT_OF_RANGE             0x01        /* for V3 group */
#define EVT_CODE_SUBSYS_3_3V_OUT_OF_RANGE           0x02        /* for V3 group */
#define EVT_CODE_SUBSYS_TEMP_ABOVE_THRESHOLD        0x03        /* for V3 group */
#define EVT_CODE_SUBSYS_3_3V_NORMAL                 0x04        /* for V3 group */
#define EVT_CODE_SUBSYS_5V_NORMAL                   0x05        /* for V3 group */
#define EVT_CODE_SUBSYS_12V_NORMAL                  0x06        /* for V3 group */
#define EVT_CODE_SUBSYS_TEMP_ABOVE_CRITICAL         0x07        /* for V3 group */
#define EVT_CODE_SUBSYS_TEMP_ABOVE_WARNING          0x08        /* for V3 group */
#define EVT_CODE_SUBSYS_TEMP_RETURNED_TO_NORMAL     0x09        /* for V3 group */
#define EVT_CODE_SUBSYS_PARAMETER_CHANGED           0x0A
#define EVT_CODE_SUBSYSTEM_REDUNDANT                0x0B
#define EVT_CODE_SUBSYSTEM_CRITICAL                 0x0C
#define EVT_CODE_SUBSYSTEM_NON_REDUNDANT            0x0D
#define EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_AUTO       0x10    /* UPS event only, user, fw or sw have updated to auto */
#define EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_ENABLE     0x11    /* UPS event only, user, fw or sw have updated to enable */
#define EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_DISABLE    0x12    /* UPS event only, user, fw or sw have updated to disable */
/* END EVT_CLASS_SUBSYSTEM              0x11 */

/* EVT_CLASS_SYNCHRONIZATION            0x12 */
#define EVT_CODE_SYNC_STARTED                       0x00
#define EVT_CODE_SYNC_COMPLETED                     0x01
#define EVT_CODE_SYNC_PAUSED                        0x02
#define EVT_CODE_SYNC_RESUMED                       0x03
#define EVT_CODE_SYNC_STOPPED                       0x04
#define EVT_CODE_SYNC_ABORTED_INTERNAL_ERROR        0x05
#define EVT_CODE_SYNC_QUEUED                        0x06
#define EVT_CODE_SYNC_COMPARE_ERROR                 0x07
#define EVT_CODE_SYNC_STOPPED_INTERNALLY            0x08
#define EVT_CODE_SYNC_IS_INPROGRESS                 0x09
/* END EVT_CLASS_SYNCHRONIZATION        0x12 */

/* EVT_CLASS_DISK_ARRAY                 0x13 */
#define EVT_CODE_DA_CREATED                         0x00
#define EVT_CODE_DA_DELETED                         0x01
#define EVT_CODE_DA_ADDED                           0x02
#define EVT_CODE_DA_REMOVED                         0x03
#define EVT_CODE_ARRAY_SETTINGS_CHANGE				0x04
/* END EVT_CLASS_DISK_ARRAY             0x13 */

/* EVT_CLASS_BACK_END_CONTROLLER        0x14 */
#define EVT_CODE_BEC_FOUND                          0x00
#define EVT_CODE_BEC_NOT_FOUND                      0x01
#define EVT_CODE_BEC_DIAG_OK                        0x02
#define EVT_CODE_BEC_DIAG_FAIL                      0x03
#define EVT_CODE_BEC_GENERAL_PARITY_ERR             0x04
#define EVT_CODE_BEC_DATA_PARITY_ERR                0x05
/* END EVT_CLASS_BACK_END_CONTROLLER    0x14 */

/* EVT_CLASS_ONLINE_CAPACITY_EXPANSION  0x15 */
#define EVT_CODE_OCE_STARTED                         0x00
#define EVT_CODE_OCE_COMPLETED                       0x01
#define EVT_CODE_OCE_PAUSED                          0x02
#define EVT_CODE_OCE_RESUMED                         0x03
#define EVT_CODE_OCE_STOPPED                         0x04
#define EVT_CODE_OCE_PD_ERROR_ENCOUNTERED            0x05
#define EVT_CODE_OCE_ABORTED_INTERNAL_ERROR          0x06
#define EVT_CODE_OCE_QUEUED                          0x07
/* END EVT_CLASS_ONLINE_CAPACITY_EXPANSION 0x15 */

/* EVT_CLASS_RAID_LEVEL_MIGRATION       0x16 */
#define EVT_CODE_RLM_STARTED                        0x00
#define EVT_CODE_RLM_COMPLETED                      0x01
#define EVT_CODE_RLM_PAUSED                         0x02
#define EVT_CODE_RLM_RESUMED                        0x03
#define EVT_CODE_RLM_STOPPED                        0x04
#define EVT_CODE_RLM_PD_ERROR_ENCOUNTERED           0x05
#define EVT_CODE_RLM_ABORTED_INTERNAL_ERROR         0x06
#define EVT_CODE_RLM_QUEUED                         0x07
/* END EVT_CLASS_RAID_LEVEL_MIGRATION   0x16 */

/* EVT_CLASS_STRIPE_LEVEL_MIGRATION     0x17 */
#define EVT_CODE_SLM_STARTED                        0x00
#define EVT_CODE_SLM_COMPLETED                      0x01
#define EVT_CODE_SLM_PAUSED                         0x02
#define EVT_CODE_SLM_RESUMED                        0x03
#define EVT_CODE_SLM_STOPPED                        0x04
#define EVT_CODE_SLM_PD_ERROR_ENCOUNTERED           0x05
#define EVT_CODE_SLM_ABORTED_INTERNAL_ERROR         0x06
#define EVT_CODE_SLM_QUEUED                         0x07
/* END EVT_CLASS_STRIPE_LEVEL_MIGRATION 0x17 */

/* EVT_CLASS_RESOURCE_CONTROL           0x19 */
#define EVT_CODE_RESOURCE_OUT                       0x00           /* added by Walen */
#define EVT_CODE_RESOURCE_DUPLICATED                0x01           /* added by Walen */
#define EVT_CODE_RESOURCE_TABLE_NOT_CREATED         0x02           /* added by Walen */
#define EVT_CODE_RESOURCE_RESUME_MEM_ERROR          0x03           /* added by Walen */
#define EVT_CODE_RESOURCE_FW_START_LOADING          0x04           /* added by Walen for power on/reset state */
/* END EVT_CLASS_RESOURCE_CONTROL        0x19 */

/* EVT_CLASS_BLOWER                      0x1a */
#define EVT_CODE_BLOWER_STARTED                     0x00
#define EVT_CODE_BLOWER_STOPPED                     0x01
#define EVT_CODE_BLOWER_SPEED_INCREASED             0x02
#define EVT_CODE_BLOWER_SPEED_DECREASED             0x03
#define EVT_CODE_BLOWER_MALFUNCTIONING              0x04
#define EVT_CODE_BLOWER_INSERTED                    0x05
#define EVT_CODE_BLOWER_REMOVED                     0x06
#define EVT_CODE_BLOWER_FUNCTIONAL                  0x07
#define EVT_CODE_BLOWER_NOT_INSTALLED               0x08
#define EVT_CODE_BLOWER_UNKNOWN_STS                 0x09
/* END EVT_CLASS_BLOWER                  0x1a */

/* EVT_CLASS_PDM                         0x1b */
#define EVT_CODE_PDM_STARTED                        0x00
#define EVT_CODE_PDM_COMPLETED                      0x01
#define EVT_CODE_PDM_PAUSED                         0x02
#define EVT_CODE_PDM_RESUMED                        0x03
#define EVT_CODE_PDM_STOPPED                        0x04
#define EVT_CODE_PDM_ABORTED                        0x05
#define EVT_CODE_PDM_ERROR                          0x06
#define EVT_CODE_PDM_MARK_DEVICE                    0x07
#define EVT_CODE_PDM_QUEUED                         0x08
#define EVT_CODE_PDM_SWITCH_TO_REBUILD              0x09
#define EVT_CODE_PDM_STOPPED_INTERNALLY             0x0A
#define EVT_CODE_PDM_IS_IN_PROGRESS                 0x0B
/* END EVT_CLASS_PDM                     0x1b */

/* EVT_CLASS_CUSTOM_FEATURE              0x1c */
#define EVT_CODE_CF_WIPE_DISK_RAID_INFO             0x01    /* wipe out RAID info from the specific device */
#define EVT_CODE_CF_WIPE_DISK_BOOT_INFO             0x02    /* wipe out boot info (first 4 sectors -- LBA 0 ~ 3 ) of the specific device */
#define EVT_CODE_CF_LMM_SETTING_CHANGED             0x03    /* LMM setting changed */
/* END EVT_CLASS_CUSTOM_FEATURE          0x1c */

/* EVT_CLASS_SPARE_CHECK                 0x1d */
#define EVT_CODE_SPARE_CHECK_STARTED                     0x00
#define EVT_CODE_SPARE_CHECK_COMPLETED              0x01
#define EVT_CODE_SPARE_CHECK_FAILED                 0x02
/* END EVT_CLASS_SPARE_CHECK             0x1d */

/* EVT_CLASS_TEMPERATURE                0x1e */
#define EVT_CODE_TEMP_ABOVE_THRESHOLD               0x00        /* for V4 group */
#define EVT_CODE_TEMP_ABOVE_CRITICAL                0x01        /* for V4 group */
#define EVT_CODE_TEMP_ABOVE_WARNING                 0x02        /* for V4 group */
#define EVT_CODE_TEMP_RETURNED_TO_NORMAL            0x03        /* for V4 group */
#define EVT_CODE_CTRL_TEMP_ABOVE_CRITICAL           0x04        /* for V4 group */
#define EVT_CODE_CTRL_TEMP_ABOVE_WARNING            0x05        /* for V4 group */
#define EVT_CODE_CTRL_TEMP_RETURNED_TO_NORMAL       0x06        /* for V4 group */
#define EVT_CODE_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU       0x07        /* for V4 group */
/* EVT_CLASS_TEMPERATURE                0x1e */

/* EVT_CLASS_FW_UPDATE                  0x1f */
#define EVT_CODE_FW_UPDATE_STARTED                  0x00
#define EVT_CODE_FW_UPDATE_COMPLETED                0x01
#define EVT_CODE_FW_UPDATE_FAILED                   0x02
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_SUCCESS      0x03
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_SUCCESS       0x04
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_FAILED       0x05
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_FAILED        0x06
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_STARTED      0x07
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_STARTED       0x08

/* EVT_CLASS_NAS                0x20 */
#define EVT_CODE_NAS_ADD_USER                        0x01
#define EVT_CODE_NAS_DEL_USER                        0x02
#define EVT_CODE_NAS_CHANGE_PASSWD                   0x03
#define EVT_CODE_NAS_NAS_ADD_GROUP                   0x04
#define EVT_CODE_NAS_DEL_GROUP                       0x05
#define EVT_CODE_NAS_CHANGE_MEMBER                   0x06
#define EVT_CODE_NAS_CIFS_START                      0x07
#define EVT_CODE_NAS_FTP_START                       0x08
#define EVT_CODE_NAS_NFS_START                       0x09
#define EVT_CODE_NAS_CIFS_FAIL                       0x0a
#define EVT_CODE_NAS_FTP_FAIL                        0x0b
#define EVT_CODE_NAS_NFS_FAIL                        0x0c
#define EVT_CODE_NAS_CIFS_STOP                       0x0d
#define EVT_CODE_NAS_FTP_STOP                        0x0e
#define EVT_CODE_NAS_NFS_STOP                        0x0f
#define EVT_CODE_NAS_CIFS_SETTING_CHANGE             0x10
#define EVT_CODE_NAS_FTP_SETTING_CHANGE              0x11
#define EVT_CODE_NAS_CREATE_SHARE_FOLDER             0x12
#define EVT_CODE_NAS_REMOVE_SHARE_FOLDER			 0x13
#define EVT_CODE_NAS_MODIFY_SHARE_FOLDER             0x14
#define EVT_CODE_NAS_CHANGE_NFS_SETTING              0x15
#define EVT_CODE_NAS_CHANGE_CIFS_SETTING             0x16
#define EVT_CODE_NAS_CHANGE_FTP_SETTING              0x17
#define EVT_CODE_NAS_CREATE_VOLUME                   0x18
#define EVT_CODE_NAS_DEL_VOLUME                      0x19
#define EVT_CODE_NAS_EXPAND_START                    0x1a
#define EVT_CODE_NAS_EXPAND_FAIL                     0x1b
#define EVT_CODE_NAS_EXPAND_COMPLETE                 0x1c
#define EVT_CODE_NAS_RSYNC_START                     0x1d
#define EVT_CODE_NAS_RSYNC_COMPLETE                  0x1e
#define EVT_CODE_NAS_RSYNC_FAIL                      0x1f
#define EVT_CODE_NAS_RSYNC_SETTING_CHANGE            0x20
#define EVT_CODE_NAS_MOUNT_POINT_CONFLICT            0x21

/* EVT_CLASS_UPS                0x21 */
#define EVT_CODE_UPS_DEVICE_NOT_EXIST               0x00     /* could not find UPS device during firmware load */
#define EVT_CODE_UPS_DEVICE_DETECTED                0x01     /* UPS is detected */
#define EVT_CODE_UPS_DEVICE_REMOVED                 0x02     /* UPS connection is removed */
#define EVT_CODE_UPS_DEVICE_ONLINE_MODE             0x03     /* running on main source power */
#define EVT_CODE_UPS_DEVICE_ON_BATTERY              0x04     /* running on battery power */
#define EVT_CODE_UPS_DEVICE_CAP_CRITICAL            0x05     /* low battery on backup */
#define EVT_CODE_UPS_DEVICE_BACKUP_SAFE             0x06     /* the attached device is protected by the UPS */
#define EVT_CODE_UPS_DEVICE_TEMP_CRITICAL           0x07     /* above set critical temperature */
#define EVT_CODE_UPS_DEVICE_TEMP_NORMAL             0x08     /* normal temperature generate during firmware load
                                                               time or back from critical */
#define EVT_CODE_UPS_DEVICE_RECONDITION_START       0x09     /* recalibration start */
#define EVT_CODE_UPS_DEVICE_RECONDITION_COMPLETE    0x0A     /* recalibration complete successfully */
#define EVT_CODE_UPS_DEVICE_RECONDITION_END_ERROR   0x0B     /* recalibration end with error detected */
#define EVT_CODE_UPS_DEVICE_REPLACE_BATTERY         0x0C     /* need to replace battery */
#define EVT_CODE_UPS_DEVICE_POWER_OVERLOAD          0x0D     /* device feel the power overload */
#define EVT_CODE_UPS_DEVICE_OVERLOAD_SAFE           0x0E     /* device ok with the loading */
#define EVT_CODE_UPS_DEVICE_ZERO_LOADING            0x0F     /* device has no attachment */
/* EVT_CLASS_UPS                0x21 */

/*
 * Event Code for PLATFORM_CBAY    0x22
 */
#define EVT_CODE_PLATFORM_CBAY_BLADE_INSERTED        (0x00)
#define EVT_CODE_PLATFORM_CBAY_BLADE_REMOVED         (0x01)
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_SUCCESS      0x03
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_SUCCESS       0x04
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_FAILED       0x05
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_FAILED        0x06
#define EVT_CODE_SEP_BKEND_IMG_UPGRADE_STARTED      0x07
#define EVT_CODE_SEP_FEND_IMG_UPGRADE_STARTED       0x08

/*
 * Event Code for OS    0x24
 */
#define EVT_CODE_TIME_SYNCED_NTP                    0x00

/*
 * Event Code for POWER MANAGEMENT    0x27
 */
#define EVT_CODE_PM_ARRAY_TO_ACTIVE        	    (0x01)
#define EVT_CODE_PM_ARRAY_TO_IDLE                  (0x02)
#define EVT_CODE_PM_ARRAY_TO_STANDBY               (0x03)
#define EVT_CODE_PM_ARRAY_TO_STOPPED               (0x04)
#define EVT_CODE_PM_PD_TO_ACTIVE                   (0x05)
#define EVT_CODE_PM_PD_TO_IDLE                     (0x06)
#define EVT_CODE_PM_PD_TO_STANDBY                 (0x07)
#define EVT_CODE_PM_PD_TO_STOPPED                  (0x08)

typedef struct
{
    u8  MajorVer;
    u8  MinorVer;
    u8  BuildNum;
    u8  Rsvd;

    u8  BuildMonth;
    u8  BuildDate;
    u16 BuildYear;

} img_info_t;

typedef struct {

    img_info_t SrcInfo;
    img_info_t DstInfo;

} fwupdt_iop_info_t;

typedef struct {

    u8 sep_type;
    u8 encid;
    u8 opstatus;
    u8 rsvd0;

    u8 scsi_status;
    u8 asc;
    u8 ascq;
    u8 rsvd1;

    u8 rsvd2[8];

} fwupdt_sep_info_t;

typedef struct {
    u16 FlashType;                /* see imgheader.h IH_TYPE_* in software tree */
    u8 Error;                       /* populated for EVT_ID_FW_UPDATE_FAILED only */
    u8 controller_id;

    union {
        fwupdt_sep_info_t sep;
        fwupdt_iop_info_t iop;

        u8 rsvd1[16];

    } type_info;

    u8 rsvd2[4];
    u8 wwn[8];

} fwupdt_event_info_t;

/* EVT_CLASS_FW_UPDATE                  0x1f */

/* EVT_CLASS_UPS                0x21 */
#define EVT_CODE_UPS_DEVICE_NOT_EXIST               0x00     /* could not find UPS device during firmware load */
#define EVT_CODE_UPS_DEVICE_DETECTED                0x01     /* UPS is detected */
#define EVT_CODE_UPS_DEVICE_REMOVED                 0x02     /* UPS connection is removed */
#define EVT_CODE_UPS_DEVICE_ONLINE_MODE             0x03     /* running on main source power */
#define EVT_CODE_UPS_DEVICE_ON_BATTERY              0x04     /* running on battery power */
#define EVT_CODE_UPS_DEVICE_CAP_CRITICAL            0x05     /* low battery on backup */
#define EVT_CODE_UPS_DEVICE_BACKUP_SAFE             0x06     /* the attached device is protected by the UPS */
#define EVT_CODE_UPS_DEVICE_TEMP_CRITICAL           0x07     /* above set critical temperature */
#define EVT_CODE_UPS_DEVICE_TEMP_NORMAL             0x08     /* normal temperature generate during firmware load
                                                               time or back from critical
                                                             */
#define EVT_CODE_UPS_DEVICE_RECONDITION_START       0x09     /* recalibration start */
#define EVT_CODE_UPS_DEVICE_RECONDITION_COMPLETE    0x0A     /* recalibration complete successfully */
#define EVT_CODE_UPS_DEVICE_RECONDITION_END_ERROR   0x0B     /* recalibration end with error detected */
#define EVT_CODE_UPS_DEVICE_REPLACE_BATTERY         0x0C     /* need to replace battery */
#define EVT_CODE_UPS_DEVICE_POWER_OVERLOAD          0x0D     /* device feel the power overload */
#define EVT_CODE_UPS_DEVICE_OVERLOAD_SAFE           0x0E     /* device ok with the loading */
#define EVT_CODE_UPS_DEVICE_ZERO_LOADING            0x0F     /* UPS has no loading */
#define EVT_CODE_UPS_UPDATE_IP_ADDRESS                      0x10    /* users have updated ip address */
#define EVT_CODE_UPS_UPDATE_TEMPERATURE_THRESHOLD           0x11    /* users have updated a new temperature threshold */
#define EVT_CODE_UPS_UPDATE_RUN_TIME_REMAINING_THRESHOLD    0x12    /* users have updated a new run time remaining threshold */
#define EVT_CODE_UPS_UPDATE_TRIGGER_CACHE_FAILED            0x13    /* The process of updating the cache to LD/PD has failed */
#define EVT_CODE_UPS_DEVICE_ALERT_POWER_OVERLOAD            0x14    /* The UPS device HW has alerted high loading power */

/* EVT_CLASS_UPS                0x21 */


/***********************************
 * End Event Codes listed by class *
 **********************************/

/*******************************
 * Event internal error values *
 ******************************/
#define EVT_ERROR_INTERNAL_ABORT                    0x01
#define EVT_ERROR_MEM_FAILED                        0x02
#define EVT_ERROR_WM_INVALID_CMD                    0x03
#define EVT_ERROR_WM_FAILED                         0x04
#define EVT_ERROR_ALLOCATE_BICS_FAILED              0x05
#define EVT_ERROR_LD_NOT_ONLINE                     0x06
#define EVT_ERROR_LD_NOT_PRESENT                    0x07
/* Sync may be stopped due to LDI started on same LD / Delete LD / delete Array, Start Migration */
/* For MP may be stopped due to delete array, or start migration */
#define EVT_ERROR_STOPPED_BY_HIGHER_PRIORITY_TASK   0x08
#define EVT_ERROR_LD_NOT_CRITICAL                   0x09
#define EVT_ERROR_UNKNOWN                           0x20

/***********************************
 * End Event internal error values *
 **********************************/

/**********************************
 * Full Event IDs listed by class *
 *********************************/
#define EVT_ID_UNKNOWN                              0xFFFFFFFF

/* EVT_CLASS_BATTERY                    0x01 */
#define EVT_ID_BATTERY_TEMPERATURE_RISE \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_TEMPERATURE_RISE)
#define EVT_ID_BATTERY_TEMPERATURE_DROPPED \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_TEMPERATURE_DROPPED)
#define EVT_ID_BATTERY_CAPACITY_BELOW_THRESHOLD \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CAPACITY_BELOW_THRESHOLD)
#define EVT_ID_BATTERY_CAPACITY_NORMAL \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CAPACITY_NORMAL)
#define EVT_ID_BATTERY_DISCHARGING \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_DISCHARGING)
#define EVT_ID_BATTERY_CHARGING \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CHARGING)
#define EVT_ID_BATTERY_MAINTENANCE_MODE_EXIT \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_MAINTENANCE_MODE_EXIT)
#define EVT_ID_BATTERY_NOT_FUNCTIONING \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_NOT_FUNCTIONING)
#define EVT_ID_BATTERY_SELF_TEST_PASS \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_SELF_TEST_PASS)
#define EVT_ID_BATTERY_SELF_TEST_FAIL \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_SELF_TEST_FAIL)
#define EVT_ID_BATTERY_REACHED_CYCLE_THRESHOLD \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_REACHED_CYCLE_THRESHOLD)
#define EVT_ID_BATTERY_REMOVED \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_REMOVED)
#define EVT_ID_BATTERY_INSTALLED \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_INSTALLED)
#define EVT_ID_BATTERY_CHARGING_FOR_TOO_LONG \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CHARGING_FOR_TOO_LONG)
#define EVT_ID_BATTERY_SELF_TEST_START \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_SELF_TEST_START)
#define EVT_ID_BATTERY_SELF_TEST_END \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_SELF_TEST_END)
#define EVT_ID_BATTERY_SEND_NOTIFICATION \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_SEND_NOTIFICATION)           /* added by Walen */
#define  EVT_ID_BATTERY_CACHESWITCH_TO_WT \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_WB_CACHE_SWITCHED_TO_WT)
#define  EVT_ID_BATTERY_CACHESWITCH_TO_WB \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_WT_CACHE_SWITCHED_TO_WB)
#define  EVT_ID_BATTERY_CHARGING_IN_HI_TEMP \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CHARGING_IN_HI_TEMP)          /* added by Walen requested by Challo */
#define  EVT_ID_BATTERY_MISMATCHED_ID \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_MISMATCHED_ID)                /* added by Walen */
#define  EVT_ID_BATTERY_CACHE_ENABLE_NO_BTY \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_CACHE_ENABLE_NO_BTY)          /* added by Walen requested by Challo */
#define EVT_ID_BATTERY_NOT_PRESENT \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_NOT_PRESENT)
#define EVT_ID_BATTERY_HAS_FAILED \
        ((EVT_CLASS_BATTERY << 16) | EVT_CODE_BATTERY_HAS_FAILED)
/* END EVT_CLASS_BATTERY                0x01 */

/* EVT_CLASS_BBU                        0x02 */
#define EVT_ID_BBU_FLUSH_ABORT \
        ((EVT_CLASS_BBU << 16) | EVT_CLASS_BBU_FLUSH_ABORT)           /* added by Walen */
#define EVT_ID_BBU_FLUSH_START \
        ((EVT_CLASS_BBU << 16) | EVT_CLASS_BBU_FLUSH_START)           /* added by Walen */
#define EVT_ID_BBU_FLUSH_END \
        ((EVT_CLASS_BBU << 16) | EVT_CLASS_BBU_FLUSH_END)             /* added by Walen */
#define EVT_ID_BBU_FLUSH_FAILED \
        ((EVT_CLASS_BBU << 16) | EVT_CLASS_BBU_FLUSH_FAILED)             /* added by Walen */

/* END EVT_CLASS_BBU                    0x02 */

/* EVT_CLASS_REDUNDANCY_CHECK           0x03 */
#define EVT_ID_RC_STARTED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_STARTED)
#define EVT_ID_RC_COMPLETED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_COMPLETED)
#define EVT_ID_RC_PAUSED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_PAUSED)
#define EVT_ID_RC_RESUMED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_RESUMED)
#define EVT_ID_RC_STOPPED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_STOPPED)
#define EVT_ID_RC_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_PD_ERROR_ENCOUNTERED)
#define EVT_ID_RC_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | \
         EVT_CODE_RC_ABORTED_INTERNAL_ERROR)
#define EVT_ID_RC_INCONSISTENT_STRIPE \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_INCONSISTENT_STRIPE)
#define EVT_ID_RC_QUEUED \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_QUEUED)
#define EVT_ID_RC_FIXED_INCONSISTENCE \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_FIXED_INCONSISTENCE)
#define EVT_ID_RC_STOPPED_INTERNALLY \
        ((EVT_CLASS_REDUNDANCY_CHECK << 16) | EVT_CODE_RC_STOPPED_INTERNALLY)
/* END EVT_CLASS_REDUNDANCY_CHECK       0x03 */

/* EVT_CLASS_CONTROLLER                 0x04 */
#define EVT_ID_CONTROLLER_EVT_LOG_ENABLED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_EVT_LOG_ENABLED)
#define EVT_ID_CONTROLLER_EVT_LOG_DISABLED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_EVT_LOG_DISABLED)
#define EVT_ID_CONTROLLER_EVT_LOG_CLEARED_RAM \
        ((EVT_CLASS_CONTROLLER << 16) | \
         EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_RAM)
#define EVT_ID_CONTROLLER_EVT_LOG_CLEARED_NVRAM \
        ((EVT_CLASS_CONTROLLER << 16) | \
         EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_NVRAM)
#define EVT_ID_CONTROLLER_EVT_LOG_CLEARED_MDD \
        ((EVT_CLASS_CONTROLLER << 16) | \
         EVT_CODE_CONTROLLER_EVT_LOG_CLEARED_MDD)
#define EVT_ID_CONTROLLER_SYSTEM_STARTED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_SYSTEM_STARTED)
#define EVT_ID_CONTROLLER_SYSTEM_STOPPED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_SYSTEM_STOPPED)
#define EVT_ID_CONTROLLER_PARAMETER_CHANGED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_PARAMETER_CHANGED)
#define EVT_ID_CONTROLLER_WATCHDOG_RESET \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_WATCHDOG_RESET)
#define EVT_ID_CONTROLLER_NEW_CRASH_INFO_FOUND \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_NEW_CRASH_INFO_FOUND)
#define EVT_ID_CONTROLLER_USER_REQ_MAINTENANCE_MODE \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_USER_REQ_MAINTENANCE_MODE)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_CFGPD_NOT_SEEN \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_CFGPD_NOT_SEEN)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_DISKTYPE_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_DISKTYPE_MISMATCH)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_DISKWWN_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_DISKWWN_MISMATCH)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_DISKSATA_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_DISKSATA_MISMATCH)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_DISKID_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_DISKID_MISMATCH)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_NODRIVES_SEEN \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_NODRIVES_SEEN)
#define EVT_ID_EVT_CODE_CONTROLLER_STARTED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_STARTED)
#define EVT_ID_EVT_CODE_CONTROLLER_ACTIVE \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_ACTIVE)
#define EVT_ID_EVT_CODE_CONTROLLER_STANDBY \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_STANDBY)
#define EVT_ID_EVT_CODE_CONTROLLER_FAILOVER_PARTNER_REMOVED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_FAILOVER_PARTNER_REMOVED)

#define EVT_ID_EVT_CODE_CONTROLLER_FAILOVER_HEART_BEAT_STOPPED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_FAILOVER_HEART_BEAT_STOPPED)
#define EVT_ID_EVT_CODE_CONTROLLER_MNTMODE_HARDWARE_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_HARDWARE_MISMATCH)
#define EVT_ID_EVT_CODE_CONTROLLER_FW_MISMATCH_WITH_PARTNER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_FW_MISMATCH_WITH_PARTNER)
#define EVT_ID_EVT_CODE_CONTROLLER_MNTMODE_FW_FLASHING_IN_PARTNER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_FW_FLASHING_IN_PARTNER)
#define EVT_ID_CONTROLLER_FW_FLASH_FAILOVER_TO_PARTNER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_FW_FLASH_FAILOVER_TO_PARTNER)

#define EVT_ID_CONTROLLER_RESET_PARTNER_DUE_TO_FAILOVER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_RESET_PARTNER_DUE_TO_FAILOVER)
#define EVT_ID_CONTROLLER_RESET_DUE_TO_FAILOVER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_RESET_DUE_TO_FAILOVER)
#define EVT_ID_EVT_CODE_CONTROLLER_MNTMODE_FIRMWARE_MISMATCH \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_FIRMWARE_MISMATCH)
#define EVT_ID_CONTROLLER_RESET_AS_NOT_ABLE_TO_JOIN_PARTNER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_RESET_AS_NOT_ABLE_TO_JOIN_PARTNER)
#define EVT_ID_CONTROLLER_MNTMODE_HW_MISMATCH_BOARD_MODEL_VER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_HW_MISMATCH_BOARD_MODEL_VER)
#define EVT_ID_CONTROLLER_MNTMODE_HW_MISMATCH_MEM_SIZE \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_HW_MISMATCH_MEM_SIZE)

#define EVT_ID_PARTNER_CTRL_MNTMODE_CFGPD_NOT_SEEN_LD_NONREDUNDANT \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_PARTNER_CTRL_MNTMODE_CFGPD_NOT_SEEN_LD_NONREDUNDANT)
#define EVT_ID_CONTROLLER_CRASH_RESET \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_CRASH_RESET)
#define EVT_ID_CONTROLLER_TRIGGER_FAILOVER \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_TRIGGER_FAILOVER)
#define EVT_ID_CONTROLLER_TRIGGER_FAILBACK \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_TRIGGER_FAILBACK)

#define EVT_ID_CONTROLLER_INCOMPATIBLE \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_INCOMPATIBLE)
#define EVT_ID_CONTROLLER_BAD_VPD \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_BAD_VPD)

#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_INCOMPATIBLE \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_INCOMPATIBLE)
#define EVT_ID_CONTROLLER_MAINTENANCE_MODE_BAD_VPD \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MNTMODE_BAD_VPD)

#define EVT_ID_CONTROLLER_MODE_BAD_MAC \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_BAD_MAC)
#define EVT_ID_CONTROLLER_MGT_PORT_UP \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MGMT_PORT_UP)
#define EVT_ID_CONTROLLER_MGT_PORT_DN \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MGMT_PORT_DN)
#define EVT_ID_CONTROLLER_MGT_PORT_DHCP_ACQUIRED \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MGMT_PORT_DHCP_ACQUIRED)
#define EVT_ID_CONTROLLER_MGT_PORT_LINK_LOCAL \
        ((EVT_CLASS_CONTROLLER << 16) | EVT_CODE_CONTROLLER_MGMT_PORT_LINK_LOCAL)

/* END EVT_CLASS_CONTROLLER             0x04 */

/* EVT_CLASS_COOLING_DEVICE             0x05 */
#define EVT_ID_COOLING_DEVICE_STARTED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_STARTED)
#define EVT_ID_COOLING_DEVICE_STOPPED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_STOPPED)
#define EVT_ID_COOLING_DEVICE_SPEED_INCREASED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | \
         EVT_CODE_COOLING_DEVICE_SPEED_INCREASED)
#define EVT_ID_COOLING_DEVICE_SPEED_DECREASED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | \
         EVT_CODE_COOLING_DEVICE_SPEED_DECREASED)
#define EVT_ID_COOLING_DEVICE_MALFUNCTIONING \
        ((EVT_CLASS_COOLING_DEVICE << 16) | \
         EVT_CODE_COOLING_DEVICE_MALFUNCTIONING)
#define EVT_ID_COOLING_DEVICE_INSERTED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_INSERTED)
#define EVT_ID_COOLING_DEVICE_REMOVED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_REMOVED)
#define EVT_ID_COOLING_DEVICE_FUNCTIONAL \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_FUNCTIONAL)
#define EVT_ID_COOLING_DEVICE_NOT_INSTALLED \
        ((EVT_CLASS_COOLING_DEVICE << 16) | \
         EVT_CODE_COOLING_DEVICE_NOT_INSTALLED)
#define EVT_ID_COOLING_DEVICE_UNKNOWN_STS \
        ((EVT_CLASS_COOLING_DEVICE << 16) | EVT_CODE_COOLING_DEVICE_UNKNOWN_STS)
/* END EVT_CLASS_COOLING_DEVICE         0x05 */

/* EVT_CLASS_SEP                        0x06 */
#define EVT_ID_SEP_COM_ERROR \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_COM_ERROR)        /* added by Walen */
#define EVT_ID_SEP_TIMEOUT \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_TIMEOUT)          /* added by Walen */
#define EVT_ID_SEP_ONLINE \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_ONLINE)           /* added by Walen */
#define EVT_ID_SEP_FRU_STATE_CHANGE \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_FRU_STATE_CHANGE)           /* added by Walen */
#define EVT_ID_SEP_I2C_ACCESS_FAIL \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_I2C_ACCESS_FAIL)
#define EVT_ID_SEP_I2C_ACCESS_RECOVERED \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_I2C_ACCESS_RECOVERED)
#define EVT_ID_SEP_JBOD_INCOMPATIBLE \
        ((EVT_CLASS_SEP << 16) | EVT_CODE_SEP_JBOD_INCOMPATIBLE)      /* added by DavidC */

/* END EVT_CLASS_SEP                    0x06 */

/* EVT_CLASS_FRONT_END_CONTROLLER       0x07 */
#define EVT_ID_FEC_PARITY_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_PARITY_ERROR)
#define EVT_ID_FEC_DATA_PARITY_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_DATA_PARITY_ERROR)
#define EVT_ID_FEC_COMMAND_PARITY_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_COMMAND_PARITY_ERROR)
#define EVT_ID_FEC_BUS_RESET_DETECTED \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_BUS_RESET_DETECTED)
#define EVT_ID_FEC_UNRECOVERABLE_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_UNRECOVERABLE_ERROR)
#define EVT_ID_FEC_ABORT_TASK \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_ABORT_TASK)
#define EVT_ID_FEC_ABORT_TASK_SET \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_ABORT_TASK_SET)
#define EVT_ID_FEC_CLEAR_ACA \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_CLEAR_ACA)
#define EVT_ID_FEC_CLEAR_TASK_SET \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_CLEAR_TASK_SET)
#define EVT_ID_FEC_LUN_RESET \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_LUN_RESET)
#define EVT_ID_FEC_INITIATOR_DETECTED_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_INITIATOR_DETECTED_ERROR)
#define EVT_ID_FEC_ILLEGAL_SECONDARY_IDENTIFY \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_ILLEGAL_SECONDARY_IDENTIFY)
#define EVT_ID_FEC_MESSAGE_PARITY_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | \
         EVT_CODE_FEC_MESSAGE_PARITY_ERROR)
#define EVT_ID_FEC_BUS_REBOOT \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_BUS_REBOOT)
#define EVT_ID_FEC_LINK_UP \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_LINK_UP)
#define EVT_ID_FEC_LINK_DOWN \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_LINK_DOWN)
#define EVT_ID_FEC_UNKNOWN_ERROR \
        ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_UNKNOWN_ERROR)
#define EVT_ID_FEC_SYSTEM_ERROR \
	((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_SYSTEM_ERROR
#define EVT_ID_FEC_FATAL_ERROR \
	((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_FATAL_ERROR
#define EVT_ID_FEC_WARM_RESET \
    ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_WARM_RESET)
#define EVT_ID_FEC_COLD_RESET \
    ((EVT_CLASS_FRONT_END_CONTROLLER << 16) | EVT_CODE_FEC_COLD_RESET)

	
/* END EVT_CLASS_FRONT_END_CONTROLLER   0x07 */

/* EVT_CLASS_INITIALIZATION             0x08 */
#define EVT_ID_LDI_FULL_STARTED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_STARTED)
#define EVT_ID_LDI_FULL_COMPLETED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_COMPLETED)
#define EVT_ID_LDI_FULL_PAUSED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_PAUSED)
#define EVT_ID_LDI_FULL_RESUMED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_RESUMED)
#define EVT_ID_LDI_FULL_STOPPED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_STOPPED)
#define EVT_ID_LDI_FULL_MARKED_OFFLINE \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_MARKED_OFFLINE)
#define EVT_ID_LDI_FULL_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_INITIALIZATION << 16) | \
         EVT_CODE_LDI_FULL_ABORTED_INTERNAL_ERROR)
#define EVT_ID_LDI_QUICK_STARTED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_STARTED)
#define EVT_ID_LDI_QUICK_COMPLETED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_COMPLETED)
#define EVT_ID_LDI_QUICK_PAUSED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_PAUSED)
#define EVT_ID_LDI_QUICK_RESUMED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_RESUMED)
#define EVT_ID_LDI_QUICK_STOPPED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_STOPPED)
#define EVT_ID_LDI_QUICK_MARKED_OFFLINE \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_MARKED_OFFLINE)
#define EVT_ID_LDI_QUICK_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_INITIALIZATION << 16) | \
         EVT_CODE_LDI_QUICK_ABORTED_INTERNAL_ERROR)
#define EVT_ID_LDI_FULL_QUEUED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_FULL_QUEUED)
#define EVT_ID_LDI_QUICK_QUEUED \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_QUICK_QUEUED)
#define EVT_ID_LDI_IS_IN_PROGRESS \
        ((EVT_CLASS_INITIALIZATION << 16) | EVT_CODE_LDI_IS_IN_PROGRESS)
/* END EVT_CLASS_INITIALIZATION         0x08 */

/* EVT_CLASS_LOGICAL_DRIVE              0x09 */
#define EVT_ID_LD_CREATED \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_CREATED)
#define EVT_ID_LD_DELETED \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_DELETED)
#define EVT_ID_LD_ONLINE \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_ONLINE)
#define EVT_ID_LD_OFFLINE \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_OFFLINE)
#define EVT_ID_LD_CRITICAL \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_CRITICAL)

#define EVT_ID_LD_DEGRADE\
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_DEGRADE)

#define EVT_ID_LD_AXLE_ONLINE \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_AXLE_ONLINE)

#define EVT_ID_LD_QUICKINIT_STARTED \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_QUICKINIT_START)

#define EVT_ID_LD_QUICKINIT_COMPLETED \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_QUICKINIT_COMPLETED)

#define EVT_ID_LD_CREATED_IO \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_CREATED_IO)

#define EVT_ID_LD_DELETED_IO \
        ((EVT_CLASS_LOGICAL_DRIVE << 16) | EVT_CODE_LD_DELETED_IO)





/* END EVT_CLASS_LOGICAL_DRIVE          0x09 */

/* EVT_CLASS_MDD                        0x0a */
#define EVT_ID_DDF_WRITE_FAILED \
        ((EVT_CLASS_MDD << 16) | EVT_CODE_DDF_WRITE_FAILED)
/* END EVT_CLASS_MDD                    0x0a */

/* EVT_CLASS_MEDIA_PATROL               0x0b */
#define EVT_ID_MP_STARTED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_STARTED)
#define EVT_ID_MP_COMPLETED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_COMPLETED)
#define EVT_ID_MP_PAUSED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_PAUSED)
#define EVT_ID_MP_RESUMED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_RESUMED)
#define EVT_ID_MP_STOPPED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_STOPPED)
#define EVT_ID_MP_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_PD_ERROR_ENCOUNTERED)
#define EVT_ID_MP_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_ABORTED_INTERNAL_ERROR)
#define EVT_ID_MP_QUEUED \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_QUEUED)
#define EVT_ID_MP_STOPPED_INTERNALLY \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_STOPPED_INTERNALLY)
#define EVT_ID_MP_IS_IN_PROGRESS \
        ((EVT_CLASS_MEDIA_PATROL << 16) | EVT_CODE_MP_IS_IN_PROGRESS)
/* END EVT_CLASS_MEDIA_PATROL           0x0b */

/* EVT_CLASS_RAID_MIGRATION             0x0c */
#define EVT_ID_RM_STARTED\
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_STARTED)
#define EVT_ID_RM_COMPLETE \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_COMPLETED)
#define EVT_ID_RM_PAUSED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_PAUSED)
#define EVT_ID_RM_RESUMED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_RESUMED)
#define EVT_ID_RM_STOPPED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_STOPPED)
#define EVT_ID_RM_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_PD_ERROR_ENCOUNTERED)
#define EVT_ID_RM_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_ABORTED_INTERNAL_ERROR)
#define EVT_ID_RM_QUEUED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_QUEUED)
#define EVT_ID_RM_STALE_NV_DETECTED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_STALE_NV_DETECTED)
#define EVT_ID_RM_STALE_NV_CLEARED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_STALE_NV_CLEARED)
#define EVT_ID_RM_MISSING_NV_ARRAY_MADE_INCOMPLETE \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_MISSING_NV_ARRAY_MADE_INCOMPLETE)
#define EVT_ID_RM_MISSING_NV_ARRAY_INCOMPLETE_ACCEPTED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_MISSING_NV_ARRAY_INCOMPLETE_ACCEPTED)
#define EVT_ID_RM_LD_OFFLINE_SKIPPED \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_LD_OFFLINE_SKIPPED)
#define EVT_ID_RM_IS_IN_PROGRESS \
        ((EVT_CLASS_RAID_MIGRATION << 16) | EVT_CODE_RM_IS_IN_PROGRESS)
/* END EVT_CLASS_RAID_MIGRATION         0x0c */

/* EVT_CLASS_PHYSICAL_DISK              0x0d */
#define EVT_ID_PD_MARKED_ONLINE \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_ONLINE)
#define EVT_ID_PD_MARKED_OFFLINE \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_OFFLINE)
#define EVT_ID_PD_MARKED_DEAD \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_DEAD)
#define EVT_ID_PD_RESET \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_RESET)
#define EVT_ID_PD_GLOBAL_SPARE_ADDED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_GLOBAL_SPARE_ADDED)
#define EVT_ID_PD_GLOBAL_SPARE_DELETED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_GLOBAL_SPARE_DELETED)
#define EVT_ID_PD_GLOBAL_SPARE_USED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_GLOBAL_SPARE_USED)
#define EVT_ID_PD_DEDICATED_SPARE_ADDED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_DEDICATED_SPARE_ADDED)
#define EVT_ID_PD_DEDICATED_SPARE_DELETED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_DEDICATED_SPARE_DELETED)
#define EVT_ID_PD_DEDICATED_SPARE_USED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_DEDICATED_SPARE_USED)
#define EVT_ID_PD_DETECTED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_DETECTED)
#define EVT_ID_PD_REMOVED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_REMOVED)
#define EVT_ID_PD_RETRIED_COMMAND \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_RETRIED_COMMAND)
#define EVT_ID_PD_ECC_ERROR \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_ECC_ERROR)
#define EVT_ID_PD_CRC_ERROR \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_CRC_ERROR)
#define EVT_ID_PD_BAD_SECTOR \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_BAD_SECTOR)
#define EVT_ID_PD_ERROR_IN_REMAP_SECTORS \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_ERROR_IN_REMAP_SECTORS)
#define EVT_ID_PD_COMMAND_TIME_OUT \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_COMMAND_TIME_OUT)
#define EVT_ID_PD_NEGOTIATION_SPEED_DECREASED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | \
         EVT_CODE_PD_NEGOTIATION_SPEED_DECREASED)
#define EVT_ID_PD_NOT_PRESENT \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_NOT_PRESENT)
#define EVT_ID_PD_NON_ECC_MEDIA_ERROR \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_NON_ECC_MEDIA_ERROR)         /* added by Walen */
#define EVT_ID_PD_PFA_ERROR     \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_PFA_ERROR)
#define EVT_ID_ONLINE_DDF_CFG_DEAD_PD_FOUND \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_ONLINE_DDF_CFG_DEAD_PD_FOUND)
#define EVT_ID_PD_PARAMETER_PAGE0_CHANGED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_PARAMETER_PAGE0_CHANGED)
#define EVT_ID_PD_PARAMETER_PAGE1_CHANGED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_PARAMETER_PAGE1_CHANGED)
#define EVT_ID_PD_SMART_CMD_FAIL \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_SMART_CMD_FAIL)
#define EVT_ID_PD_MARKED_DEAD_DRIVE_REMOVED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_DEAD_DRIVE_REMOVED)
#define EVT_ID_PD_MARKED_DEAD_RSA_FAILED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_DEAD_RSA_FAILED)
#define EVT_ID_PD_MARKED_DEAD_PFA_FOUND \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_DEAD_PFA_FOUND)
#define EVT_ID_PD_MARKED_DEAD_FORCED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_MARKED_DEAD_FORCED)
#define EVT_ID_PD_PARAMETER_PAGE3_CHANGED \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_PARAMETER_PAGE3_CHANGED)
#define EVT_ID_PD_NOT_SEEN \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_NOT_SEEN)
#define EVT_ID_PD_SINGLE_PORTED_FOUND \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_SINGLE_PORTED_FOUND)
#define EVT_ID_PD_INCOMPATIBLE \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_INCOMPATIBLE)
#define EVT_ID_PD_MARK_PFA_BY_USER \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_PFA_BY_USER)
#define EVT_ID_PD_UPDATE_PD_WCACHE_ENABLE \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_UPDATE_PD_WCACHE_ENABLE)   /* UPS event only */
#define EVT_ID_PD_UPDATE_PD_WCACHE_DISABLE \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_UPDATE_PD_WCACHE_DISABLE)  /* UPS event only */
#define EVT_ID_PD_TEMP_OVER \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_TEMP_OVER)
#define EVT_ID_PD_TEMP_RETURNED_TO_NORMAL \
        ((EVT_CLASS_PHYSICAL_DISK << 16) | EVT_CODE_PD_TEMP_RETURNED_TO_NORMAL)
/* END EVT_CLASS_PHYSICAL_DISK          0x0d */

/* EVT_CLASS_PSU                        0x0e */
#define EVT_ID_PSU_NOT_PRESENT \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_NOT_PRESENT)         /* added by Walen */
/*
#define EVT_ID_PSU_OFF \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_OFF)
#define EVT_ID_PSU_ON \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_ON)
*/
#define EVT_ID_PSU_INSTALLED_AND_TURNED_ON \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_INSTALLED_AND_TURNED_ON)
#define EVT_ID_PSU_INSTALLED_AND_TURNED_OFF \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_INSTALLED_AND_TURNED_OFF)
#define EVT_ID_PSU_OPERATIONAL_AND_TURNED_ON \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_OPERATIONAL_AND_TURNED_ON)
#define EVT_ID_PSU_OPERATIONAL_AND_TURNED_OFF \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_OPERATIONAL_AND_TURNED_OFF)
#define EVT_ID_PSU_MALFUNCTIONING_AND_TURNED_ON \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_MALFUNCTIONING_AND_TURNED_ON)
#define EVT_ID_PSU_MALFUNCTIONING_AND_TURNED_OFF \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_MALFUNCTIONING_AND_TURNED_OFF)
#define EVT_ID_PSU_REMOVED \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_REMOVED)
#define EVT_ID_PSU_12V_OUT_OF_RANGE \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_12V_OUT_OF_RANGE)
#define EVT_ID_PSU_5V_OUT_OF_RANGE \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_5V_OUT_OF_RANGE)
#define EVT_ID_PSU_3_3V_OUT_OF_RANGE \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_3_3V_OUT_OF_RANGE)
#define EVT_ID_PSU_3_3V_NORMAL \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_3_3V_NORMAL)
#define EVT_ID_PSU_5V_NORMAL \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_5V_NORMAL)
#define EVT_ID_PSU_12V_NORMAL \
        ((EVT_CLASS_PSU << 16) | EVT_CODE_PSU_12V_NORMAL)

/* END EVT_CLASS_PSU                    0x0e */

/* EVT_CLASS_REBUILD                    0x0f */
#define EVT_ID_REBUILD_STARTED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_STARTED)
#define EVT_ID_REBUILD_COMPLETED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_COMPLETED)
#define EVT_ID_REBUILD_PAUSED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_PAUSED)
#define EVT_ID_REBUILD_RESUMED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_RESUMED)
#define EVT_ID_REBUILD_STOPPED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_STOPPED)
#define EVT_ID_REBUILD_PENDING \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_PENDING)
#define EVT_ID_REBUILD_NOT_FAULT_TOLERANT \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_NOT_FAULT_TOLERANT)
#define EVT_ID_REBUILD_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_ABORTED_INTERNAL_ERROR)
#define EVT_ID_REBUILD_MARKED_LD_SYNCHRONIZED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_MARKED_LD_SYNCHRONIZED)
#define EVT_ID_REBUILD_QUEUED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_QUEUED)
#define EVT_ID_REBUILD_TRANSITION_STARTED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_STARTED)
#define EVT_ID_TRANSITION_COMPLETED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_COMPLETED)
#define EVT_ID_TRANSITION_PAUSED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_PAUSED)
#define EVT_ID_TRANSITION_RESUMED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_RESUMED)
#define EVT_ID_TRANSITION_STOPPED \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_STOPPED)
#define EVT_ID_REBUILD_INVALID_DISK \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_INVALID_DISK)
#define EVT_ID_TRANSITION_SWITCHED_TO_REBUILD \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_SWITCH_TO_REBUILD)
#define EVT_ID_REBUILD_STOPPED_INTERNALLY \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_STOPPED_INTERNALLY)
#define EVT_ID_REBUILD_IS_IN_PROGRESS \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_IS_IN_PROGRESS)
#define EVT_ID_REBUILD_TRANSITION_IS_IN_PROGRESS \
        ((EVT_CLASS_REBUILD << 16) | EVT_CODE_REBUILD_TRANSITION_IS_IN_PROGRESS)
/* END EVT_CLASS_REBUILD                0x0f */

/* EVT_CLASS_SMART                      0x10 */
#define EVT_ID_SMART_ERROR_RECEIVED \
        ((EVT_CLASS_SMART << 16) | EVT_CODE_SMART_ERROR_RECEIVED)
/* END EVT_CLASS_SMART                  0x10 */

/* EVT_CLASS_SUBSYSTEM                  0x11 */
#define EVT_ID_SUBSYS_12V_OUT_OF_RANGE \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_12V_OUT_OF_RANGE)        /* preserve for V3 */
#define EVT_ID_SUBSYS_5V_OUT_OF_RANGE \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_5V_OUT_OF_RANGE)         /* preserve for V3 */
#define EVT_ID_SUBSYS_3_3V_OUT_OF_RANGE \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_3_3V_OUT_OF_RANGE)       /* preserve for V3 */
#define EVT_ID_SUBSYS_TEMP_ABOVE_THRESHOLD \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_TEMP_ABOVE_THRESHOLD)    /* preserve for V3 */
#define EVT_ID_SUBSYS_3_3V_NORMAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_3_3V_NORMAL)             /* preserve for V3 */
#define EVT_ID_SUBSYS_5V_NORMAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_5V_NORMAL)               /* preserve for V3 */
#define EVT_ID_SUBSYS_12V_NORMAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_12V_NORMAL)              /* preserve for V3 */
#define EVT_ID_SUBSYS_TEMP_ABOVE_CRITICAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_TEMP_ABOVE_CRITICAL)     /* preserve for V3 */
#define EVT_ID_SUBSYS_TEMP_ABOVE_WARNING \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_TEMP_ABOVE_WARNING)      /* preserve for V3 */
#define EVT_ID_SUBSYS_TEMP_RETURNED_TO_NORMAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_TEMP_RETURNED_TO_NORMAL) /* preserve for V3 */
#define EVT_ID_SUBSYS_PARAMETER_CHANGED \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_PARAMETER_CHANGED)
#define EVT_ID_EVT_CODE_SUBSYSTEM_REDUNDANT \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYSTEM_REDUNDANT)
#define EVT_ID_EVT_CODE_SUBSYSTEM_CRITICAL \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYSTEM_CRITICAL)
#define EVT_ID_EVT_CODE_SUBSYSTEM_NON_REDUNDANT \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYSTEM_NON_REDUNDANT)
#define EVT_ID_UPS_UPDATE_MONITORING_SETTO_AUTO \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_AUTO)
#define EVT_ID_UPS_UPDATE_MONITORING_SETTO_ENABLE \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_ENABLE)
#define EVT_ID_SUBSYS_UPS_MONITORING_SET_TO_DISABLE \
        ((EVT_CLASS_SUBSYSTEM << 16) | EVT_CODE_SUBSYS_UPS_MONITORING_SET_TO_DISABLE)
/* END EVT_CLASS_SUBSYSTEM              0x11 */

/* EVT_CLASS_SYNCHRONIZATION            0x12 */
#define EVT_ID_SYNC_STARTED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_STARTED)
#define EVT_ID_SYNC_COMPLETED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_COMPLETED)
#define EVT_ID_SYNC_PAUSED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_PAUSED)
#define EVT_ID_SYNC_RESUMED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_RESUMED)
#define EVT_ID_SYNC_STOPPED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_STOPPED)
#define EVT_ID_SYNC_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | \
         EVT_CODE_SYNC_ABORTED_INTERNAL_ERROR)
#define EVT_ID_SYNC_QUEUED \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_QUEUED)
#define EVT_ID_SYNC_COMPARE_ERROR \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_COMPARE_ERROR)   /* new added 03/11/04 by Walen */
#define EVT_ID_SYNC_STOPPED_INTERNALLY \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_STOPPED_INTERNALLY)
#define EVT_ID_SYNC_IS_INPROGRESS \
        ((EVT_CLASS_SYNCHRONIZATION << 16) | EVT_CODE_SYNC_IS_INPROGRESS)
/* END EVT_CLASS_SYNCHRONIZATION        0x12 */

/* EVT_CLASS_DISK_ARRAY                 0x13 */
#define EVT_ID_DA_CREATED \
        ((EVT_CLASS_DISK_ARRAY << 16) | EVT_CODE_DA_CREATED)
#define EVT_ID_DA_DELETED \
        ((EVT_CLASS_DISK_ARRAY << 16) | EVT_CODE_DA_DELETED)
#define EVT_ID_DA_ADDED \
        ((EVT_CLASS_DISK_ARRAY << 16) | EVT_CODE_DA_ADDED)
#define EVT_ID_DA_REMOVED \
        ((EVT_CLASS_DISK_ARRAY << 16) | EVT_CODE_DA_REMOVED)
/* END EVT_CLASS_DISK_ARRAY             0x13 */

/* EVT_CLASS_BACK_END_CONTROLLER        0x14 */
#define EVT_ID_BEC_FOUND \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | EVT_CODE_BEC_FOUND)
#define EVT_ID_BEC_NOT_FOUND \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | EVT_CODE_BEC_NOT_FOUND)
#define EVT_ID_BEC_DIAG_OK \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | EVT_CODE_BEC_DIAG_OK)
#define EVT_ID_BEC_DIAG_FAIL \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | EVT_CODE_BEC_DIAG_FAIL)
#define EVT_ID_BEC_GENERAL_PARITY_ERR \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | \
        EVT_CODE_BEC_GENERAL_PARITY_ERR)
#define EVT_ID_BEC_DATA_PARITY_ERR \
        ((EVT_CLASS_BACK_END_CONTROLLER << 16) | EVT_CODE_BEC_DATA_PARITY_ERR)
/* END EVT_CLASS_BACK_END_CONTROLLER    0x14 */

/* EVT_CLASS_ONLINE_CAPACITY_EXPANSION  0x15 */
#define EVT_ID_OCE_STARTED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_STARTED)
#define EVT_ID_OCE_COMPLETED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_COMPLETED)
#define EVT_ID_OCE_PAUSED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_PAUSED)
#define EVT_ID_OCE_RESUMED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_RESUMED)
#define EVT_ID_OCE_STOPPED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_STOPPED)
#define EVT_ID_OCE_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | \
	 EVT_CODE_OCE_PD_ERROR_ENCOUNTERED)
#define EVT_ID_OCE_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | \
         EVT_CODE_OCE_ABORTED_INTERNAL_ERROR)
#define EVT_ID_OCE_QUEUED \
        ((EVT_CLASS_ONLINE_CAPACITY_EXPANSION << 16) | EVT_CODE_OCE_QUEUED)
/* END EVT_CLASS_ONLINE_CAPACITY_EXPANSION  0x15 */

/* EVT_CLASS_RAID_LEVEL_MIGRATION       0x16 */
#define EVT_ID_RLM_STARTED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_STARTED)
#define EVT_ID_RLM_COMPLETED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_COMPLETED)
#define EVT_ID_RLM_PAUSED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_PAUSED)
#define EVT_ID_RLM_RESUMED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_RESUMED)
#define EVT_ID_RLM_STOPPED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_STOPPED)
#define EVT_ID_RLM_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | \
         EVT_CODE_RLM_PD_ERROR_ENCOUNTERED)
#define EVT_ID_RLM_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | \
         EVT_CODE_RLM_ABORTED_INTERNAL_ERROR)
#define EVT_ID_RLM_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | \
         EVT_CODE_RLM_ABORTED_INTERNAL_ERROR)
#define EVT_ID_RLM_QUEUED \
        ((EVT_CLASS_RAID_LEVEL_MIGRATION << 16) | EVT_CODE_RLM_QUEUED)
/* END EVT_CLASS_RAID_LEVEL_MIGRATION   0x16 */

/* EVT_CLASS_STRIPE_LEVEL_MIGRATION     0x17 */
#define EVT_ID_SLM_STARTED \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_STARTED)
#define EVT_ID_SLM_COMPLETED \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_COMPLETED)
#define EVT_ID_SLM_PAUSED\
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_PAUSED)
#define EVT_ID_SLM_RESUMED\
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_RESUMED)
#define EVT_ID_SLM_STOPPED \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_STOPPED)
#define EVT_ID_SLM_PD_ERROR_ENCOUNTERED \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | \
         EVT_CODE_SLM_PD_ERROR_ENCOUNTERED)
#define EVT_ID_SLM_ABORTED_INTERNAL_ERROR \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | \
         EVT_CODE_SLM_ABORTED_INTERNAL_ERROR)
#define EVT_ID_SLM_QUEUED \
        ((EVT_CLASS_STRIPE_LEVEL_MIGRATION << 16) | EVT_CODE_SLM_QUEUED)
/* END EVT_CLASS_STRIPE_LEVEL_MIGRATION 0x17 */

/* EVT_CLASS_RESOURCE_CONTROL           0x18 */
#define EVT_ID_RESOURCE_OUT \
        ((EVT_CLASS_RESOURCE_CONTROL << 16) | EVT_CODE_RESOURCE_OUT)      /* added by Walen */
#define EVT_ID_RESOURCE_DUPLICATED \
        ((EVT_CLASS_RESOURCE_CONTROL << 16) | EVT_CODE_RESOURCE_DUPLICATED)      /* added by Walen */
#define EVT_ID_RESOURCE_TABLE_NOT_CREATED \
        ((EVT_CLASS_RESOURCE_CONTROL << 16) | EVT_CODE_RESOURCE_TABLE_NOT_CREATED)      /* added by Walen */
#define EVT_ID_RESOURCE_RESUME_MEM_ERROR \
        ((EVT_CLASS_RESOURCE_CONTROL << 16) | EVT_CODE_RESOURCE_RESUME_MEM_ERROR)  /* error on getting same piece of mem */ /* added by Walen */
#define EVT_ID_RESOURCE_FW_START_LOADING \
        ((EVT_CLASS_RESOURCE_CONTROL << 16) | EVT_CODE_RESOURCE_FW_START_LOADING)  /* fw loading notification */
/* END EVT_CLASS_RESOURCE_CONTROL       0x18 */

/* EVT_CLASS_BLOWER                     0x05 */
#define EVT_ID_BLOWER_STARTED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_STARTED)
#define EVT_ID_BLOWER_STOPPED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_STOPPED)
#define EVT_ID_BLOWER_SPEED_INCREASED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_SPEED_INCREASED)
#define EVT_ID_BLOWER_SPEED_DECREASED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_SPEED_DECREASED)
#define EVT_ID_BLOWER_MALFUNCTIONING \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_MALFUNCTIONING)
#define EVT_ID_BLOWER_INSERTED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_INSERTED)
#define EVT_ID_BLOWER_REMOVED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_REMOVED)
#define EVT_ID_BLOWER_FUNCTIONAL \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_FUNCTIONAL)
#define EVT_ID_BLOWER_NOT_INSTALLED \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_NOT_INSTALLED)
#define EVT_ID_BLOWER_UNKNOWN_STS \
        ((EVT_CLASS_BLOWER << 16) | EVT_CODE_BLOWER_UNKNOWN_STS)
/* END EVT_CLASS_BLOWER         0x05 */

/* EVT_CLASS_PDM                0x1b */
#define EVT_ID_PDM_STARTED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_STARTED)
#define EVT_ID_PDM_COMPLETED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_COMPLETED)
#define EVT_ID_PDM_PAUSED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_PAUSED)
#define EVT_ID_PDM_RESUMED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_RESUMED)
#define EVT_ID_PDM_STOPPED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_STOPPED)
#define EVT_ID_PDM_ABORTED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_ABORTED)
#define EVT_ID_PDM_ERROR \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_ERROR)
#define EVT_ID_PDM_MARK_DEVICE \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_MARK_DEVICE)
#define EVT_ID_PDM_QUEUED \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_QUEUED)
#define EVT_ID_PDM_STOPPED_INTERNALLY \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_STOPPED_INTERNALLY)
#define EVT_ID_PDM_IS_IN_PROGRESS \
        ((EVT_CLASS_PDM << 16) | EVT_CODE_PDM_IS_IN_PROGRESS)
/* END EVT_CLASS_PDM            0x1b */

/* EVT_CLASS_CUSTOM_FEATURE              0x1c */
#define EVT_ID_CF_WIPE_DISK_RAID_INFO \
        ((EVT_CLASS_CUSTOM_FEATURE << 16) | EVT_CODE_CF_WIPE_DISK_RAID_INFO)
#define EVT_ID_CF_WIPE_DISK_BOOT_INFO \
        ((EVT_CLASS_CUSTOM_FEATURE << 16) | EVT_CODE_CF_WIPE_DISK_BOOT_INFO)
#define EVT_ID_CF_LMM_SETTING_CHANGED \
        ((EVT_CLASS_CUSTOM_FEATURE << 16) | EVT_CODE_CF_LMM_SETTING_CHANGED)
/* END EVT_CLASS_CUSTOM_FEATURE          0x1c */

/* EVT_CLASS_SPARE_CHECK                 0x1d */
#define EVT_ID_SPARE_CHECK_STARTED \
        ((EVT_CLASS_SPARE_CHECK << 16) | EVT_CODE_SPARE_CHECK_STARTED)
#define EVT_ID_SPARE_CHECK_COMPLETED \
        ((EVT_CLASS_SPARE_CHECK << 16) | EVT_CODE_SPARE_CHECK_COMPLETED)
#define EVT_ID_SPARE_CHECK_FAILED \
        ((EVT_CLASS_SPARE_CHECK << 16) | EVT_CODE_SPARE_CHECK_FAILED)
/* END EVT_CLASS_SPARE_CHECK             0x1d */

/* EVT_CLASS_TEMPERATURE 0x1e */
#define EVT_ID_TEMP_ABOVE_THRESHOLD \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_TEMP_ABOVE_THRESHOLD)
#define EVT_ID_TEMP_ABOVE_CRITICAL \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_TEMP_ABOVE_CRITICAL)
#define EVT_ID_TEMP_ABOVE_WARNING \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_TEMP_ABOVE_WARNING)
#define EVT_ID_TEMP_RETURNED_TO_NORMAL \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_TEMP_RETURNED_TO_NORMAL)
#define EVT_ID_CTRL_TEMP_ABOVE_CRITICAL \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_CTRL_TEMP_ABOVE_CRITICAL)
#define EVT_ID_CTRL_TEMP_ABOVE_WARNING \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_CTRL_TEMP_ABOVE_WARNING)
#define EVT_ID_CTRL_TEMP_RETURNED_TO_NORMAL \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_CTRL_TEMP_RETURNED_TO_NORMAL)
#define EVT_ID_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU \
        ((EVT_CLASS_TEMPERATURE << 16) | EVT_CODE_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU)
/* EVT_CLASS_TEMPERATURE 0x1e */

/* EVT_CLASS_FW_UPDATE 0x1f */
#define EVT_ID_FW_UPDATE_STARTED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_FW_UPDATE_STARTED)
#define EVT_ID_FW_UPDATE_COMPLETED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_FW_UPDATE_COMPLETED)
#define EVT_ID_FW_UPDATE_FAILED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_FW_UPDATE_FAILED)
#define EVT_ID_SEP_BKEND_UPGRADE_SUCCESS \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_BKEND_IMG_UPGRADE_SUCCESS)
#define EVT_ID_SEP_FEND_UPGRADE_SUCCESS \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_FEND_IMG_UPGRADE_SUCCESS)
#define EVT_ID_SEP_BKEND_UPGRADE_FAILED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_BKEND_IMG_UPGRADE_FAILED)
#define EVT_ID_SEP_FEND_UPGRADE_FAILED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_FEND_IMG_UPGRADE_FAILED)
#define EVT_ID_SEP_BKEND_UPGRADE_STARTED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_BKEND_IMG_UPGRADE_STARTED)
#define EVT_ID_SEP_FEND_UPGRADE_STARTED \
        ((EVT_CLASS_FW_UPDATE << 16) | EVT_CODE_SEP_FEND_IMG_UPGRADE_STARTED)
/* EVT_CLASS_FW_UPDATE 0x1f */

/* EVT_CLASS_NAS                    0x20 */
#define EVT_ID_NAS_ADD_USER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_ADD_USER)
#define EVT_ID_NAS_DEL_USER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_DEL_USER)
#define EVT_ID_NAS_CHANGE_PASSWD \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CHANGE_PASSWD)
#define EVT_ID_NAS_ADD_GROUP \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_ADD_GROUP)
#define EVT_ID_NAS_DEL_GROUP \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_DEL_GROUP)
#define EVT_ID_NAS_CHANGE_MEMBER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CHANGE_MEMBER)
#define EVT_ID_NAS_CIFS_START \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CIFS_START)
#define EVT_ID_NAS_FTP_START \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_FTP_START)
#define EVT_ID_NAS_NFS_START \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_NFS_START)
#define EVT_ID_NAS_CIFS_FAIL \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CIFS_FAIL)
#define EVT_ID_NAS_FTP_FAIL \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_FTP_FAIL)
#define EVT_ID_NAS_NFS_FAIL \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_NFS_FAIL)
#define EVT_ID_NAS_CIFS_STOP \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CIFS_STOP)
#define EVT_ID_NAS_FTP_STOP \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_FTP_STOP)
#define EVT_ID_NAS_NFS_STOP \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_NFS_STOP)
#define EVT_ID_NAS_CIFS_SETTING_CHANGE \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CIFS_SETTING_CHANGE)
#define EVT_ID_NAS_FTP_SETTING_CHANGE \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_FTP_SETTING_CHANGE)
#define EVT_ID_NAS_CREATE_SHARE_FOLDER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CREATE_SHARE_FOLDER)
#define EVT_ID_NAS_REMOVE_SHARE_FOLDER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_REMOVE_SHARE_FOLDER)
#define EVT_ID_NAS_MODIFY_SHARE_FOLDER \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_MODIFY_SHARE_FOLDER)
#define EVT_ID_NAS_CHANGE_NFS_SETTING \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CHANGE_NFS_SETTING)
#define EVT_ID_NAS_CHANGE_CIFS_SETTING \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CHANGE_CIFS_SETTING)
#define EVT_ID_NAS_CHANGE_FTP_SETTING \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CHANGE_FTP_SETTING)
#define EVT_ID_NAS_CREATE_VOLUME \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_CREATE_VOLUME)
#define EVT_ID_NAS_DEL_VOLUME \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_DEL_VOLUME)
#define EVT_ID_NAS_EXPAND_START \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_EXPAND_START)
#define EVT_ID_NAS_EXPAND_FAIL \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_EXPAND_FAIL)
#define EVT_ID_NAS_EXPAND_COMPLETE \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_EXPAND_COMPLETE)
#define EVT_ID_NAS_RSYNC_START \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_RSYNC_START)
#define EVT_ID_NAS_RSYNC_COMPLETE \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_RSYNC_COMPLETE)
#define EVT_ID_NAS_RSYNC_FAIL \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_RSYNC_FAIL)
#define EVT_ID_NAS_RSYNC_SETTING_CHANGE \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_RSYNC_SETTING_CHANGE)
#define EVT_ID_NAS_MOUNT_POINT_CONFLICT \
        ((EVT_CLASS_NAS << 16) | EVT_CODE_NAS_MOUNT_POINT_CONFLICT)
/* END EVT_CLASS_NAS                0x20 */

/* EVT_CLASS_UPS, 0x21 */
#define EVT_ID_UPS_DEVICE_NOT_EXIST \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_NOT_EXIST)
#define EVT_ID_UPS_DEVICE_DETECTED \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_DETECTED)
#define EVT_ID_UPS_DEVICE_REMOVED \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_REMOVED)
#define EVT_ID_UPS_DEVICE_ONLINE_MODE \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_ONLINE_MODE)
#define EVT_ID_UPS_DEVICE_ON_BATTERY \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_ON_BATTERY)
#define EVT_ID_UPS_DEVICE_CAP_CRITICAL \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_CAP_CRITICAL)
#define EVT_ID_UPS_DEVICE_BACKUP_SAFE \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_BACKUP_SAFE)
#define EVT_ID_UPS_DEVICE_TEMP_CRITICAL \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_TEMP_CRITICAL)
#define EVT_ID_UPS_DEVICE_TEMP_NORMAL \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_TEMP_NORMAL)
#define EVT_ID_UPS_DEVICE_RECONDITION_START \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_RECONDITION_START)
#define EVT_ID_UPS_DEVICE_RECONDITION_COMPLETE \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_RECONDITION_COMPLETE)
#define EVT_ID_UPS_DEVICE_RECONDITION_END_ERROR \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_RECONDITION_END_ERROR)
#define EVT_ID_UPS_DEVICE_REPLACE_BATTERY \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_REPLACE_BATTERY)
#define EVT_ID_UPS_DEVICE_POWER_OVERLOAD \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_POWER_OVERLOAD)
#define EVT_ID_UPS_DEVICE_OVERLOAD_SAFE \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_OVERLOAD_SAFE)
#define EVT_ID_UPS_DEVICE_ZERO_LOADING \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_ZERO_LOADING)
#define EVT_ID_UPS_UPDATE_IP_ADDRESS \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_UPDATE_IP_ADDRESS)
#define EVT_ID_UPS_UPDATE_TEMPERATURE_THRESHOLD \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_UPDATE_TEMPERATURE_THRESHOLD)
#define EVT_ID_UPS_UPDATE_RUN_TIME_REMAINING_THRESHOLD \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_UPDATE_RUN_TIME_REMAINING_THRESHOLD)
#define EVT_ID_UPS_UPDATE_TRIGGER_CACHE_FAILED \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_UPDATE_TRIGGER_CACHE_FAILED)
#define EVT_ID_UPS_DEVICE_ALERT_POWER_OVERLOAD \
        ((EVT_CLASS_UPS << 16) | EVT_CODE_UPS_DEVICE_ALERT_POWER_OVERLOAD)

/* EVT_CLASS_UPS, 0x21 */

/* EVT_CLASS_PLATFORM_CBAY, 0x22 */
#define EVT_ID_PLATFORM_CBAY_BLADE_INSERTED \
    ((EVT_CLASS_PLATFORM_CBAY << 16) | EVT_CODE_PLATFORM_CBAY_BLADE_INSERTED)
#define EVT_ID_PLATFORM_CBAY_BLADE_REMOVED \
    ((EVT_CLASS_PLATFORM_CBAY << 16) | EVT_CODE_PLATFORM_CBAY_BLADE_REMOVED)
/* EVT_CLASS_PLATFORM_CBAY, 0x22 */

/* EVT_CLASS_OS, 0x24 */
#define EVT_ID_TIME_SYNCED_NTP \
    ((EVT_CLASS_OS << 16) | EVT_CODE_TIME_SYNCED_NTP)
/* EVT_CLASS_OS, 0x24 */

/* EVT_CLASS_POWER_MANAGEMENT, 0x27 */
#define EVT_ID_PM_ARRAY_TO_ACTIVE \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_ARRAY_TO_ACTIVE)
#define EVT_ID_PM_ARRAY_TO_IDLE \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_ARRAY_TO_IDLE)
#define EVT_ID_PM_ARRAY_TO_STANDBY \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_ARRAY_TO_STANDBY)
#define EVT_ID_PM_ARRAY_TO_STOPPED \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_ARRAY_TO_STOPPED)
#define EVT_ID_PM_PD_TO_ACTIVE \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_PD_TO_ACTIVE)
#define EVT_ID_PM_PD_TO_IDLE \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_PD_TO_IDLE)
#define EVT_ID_PM_PD_TO_STANDBY \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_PD_TO_STANDBY)
#define EVT_ID_PM_PD_TO_STOPPED \
    ((EVT_CLASS_POWER_MANAGEMENT << 16) | EVT_CODE_PM_PD_TO_STOPPED)
/* EVT_CLASS_POWER_MANAGEMENT, 0x27 */

/**************************************
 * End Full Event IDs listed by class *
 *************************************/

#endif /* _EVENTS_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: events.h,v $
 * Revision 1.43.2.11  2010/01/07 07:04:02  xinw
 * no message
 *
 * Revision 1.43.2.10  2009/12/23 05:43:53  xinw
 * add event EVT_CODE_PD_TEMP_RETURNED_TO_NORMAL
 *
 * Revision 1.43.2.9  2009/12/01 10:37:10  xinw
 * add nas event support
 *
 * Revision 1.43.2.8  2009/11/30 04:02:16  xinw
 * change EVT_CURRENT_MAX_CLASSES
 *
 * Revision 1.43.2.7  2009/11/26 03:24:22  xinw
 * add EVT_CODE_DDF_WRITE_FAILED
 *
 * Revision 1.43.2.6  2009/11/26 03:14:27  xinw
 * add EVT_CODE_PD_TEMP_OVER
 *
 * Revision 1.43.2.5  2009/11/24 02:26:18  lilyz
 * add powermanagement event support
 *
 * Revision 1.43.2.4  2009/11/13 09:26:40  xinw
 * rall back
 *
 * Revision 1.43.2.3  2009/11/13 03:09:46  xinw
 * add new event
 *
 * Revision 1.43.2.2  2009/11/13 02:20:15  xinw
 * add new event
 *
 * Revision 1.43.2.1  2009/03/23 11:48:32  xinw
 * add ups support
 *
 * Revision 1.43  2008/08/22 08:41:25  kenh
 * Add some event ID defination for new added event code
 *
 * Revision 1.42  2008/08/22 08:16:15  michaell
 * add EVT_CODE_SYNC_IS_INPROGRESS
 *
 * Revision 1.41  2008/08/21 07:03:09  kenh
 * Add new event code
 *
 * Revision 1.40  2008/04/02 22:01:19  david.chiu
 * Date          : 04/02/2008
 * Description   : Added support for Fail Over/Back status in CBay IPMI Device Info
 *                 command. This REQUIRES MATCHING FIRMWARE.
 * Files Affected: cbay_mgmt_brdg/ipmi_ubridge.c
 *                 common/events.h
 *                 common/ipmi.h
 * Affected Trees: cbay_sra_plus_90, main
 * Reviewed By   : NONE
 * Committed By  : DavidC
 *
 * Revision 1.39  2007/11/20 02:27:04  xinw
 * add new event
 *
 * Revision 1.38  2007/10/27 02:18:59  david.chiu
 * belated Model 2 change
 *
 * Revision 1.37.2.1  2007/09/05 01:26:53  david.chiu
 * Model 2 changes
 *
 * Revision 1.37  2007/08/22 22:06:52  rajesh.p
 * Defect 14870
 *
 * Revision 1.36  2007/08/22 21:45:42  rajesh.p
 * New Event for Disk Array Transport Ready
 *
 * Revision 1.35  2007/07/27 18:27:57  david.chiu
 * - 1 -
 * Date          : 07/26/2007
 * Bugtracker#   : NONE
 * Description   : Some event IDs are generated as 0x0000 0001 instead of
 *                 correct code.
 * Fix           : Fixed some events macros
 * Files Affected: common/include_closed/events.h
 * Affected Trees: Fortuna_dev
 * Reviewed By   : Manoj
 * Committed By  : DavidC
 *
 * Revision 1.34  2007/07/27 06:42:14  weny
 * Take out DOS EOLs
 *
 * Revision 1.33  2007/05/02 19:17:12  david.chiu
 * no message
 *
 * Revision 1.32  2007/03/16 15:58:23  linusc
 * no message
 *
 * Revision 1.31  2007/02/13 09:00:47  danielz
 * new event class for fw update
 *
 * Revision 1.30  2006/06/21 22:52:09  david.chiu
 * Merged in new events from firmware events.h
 *
 * Revision 1.29  2006/04/13 22:09:42  debinc
 * dual ctrl support 2
 *
 * Revision 1.28  2006/04/05 04:16:33  david.chiu
 * Merged in Firmware version of this file (varies heartbeat related events)
 *
 * Revision 1.27  2005/11/23 19:48:26  debinc
 * RAID6
 *
 * Revision 1.26  2005/08/19 00:53:52  debinc
 * add pSCSI events
 *
 * Revision 1.25  2005/03/25 01:04:56  debinc
 * new event code
 *
 * Revision 1.24  2005/02/01 00:06:34  debinc
 * increase max event code per class to 256
 *
 * Revision 1.23  2005/01/27 19:28:50  debinc
 * add #define of MAX_CLASSES
 *
 * Revision 1.22  2005/01/26 19:59:52  debinc
 * update event.h from f/w
 *
 * Revision 1.21  2005/01/25 02:12:26  debinc
 * Add new event class temperature
 *
 * Revision 1.20  2005/01/14 23:27:31  debinc
 * Add new event class temperature
 *
 * Revision 1.19  2004/12/04 00:17:44  debinc
 * change #define of max event code
 *
 * Revision 1.18  2004/11/01 23:56:10  debinc
 * add spare check event class
 *
 * Revision 1.17  2004/07/28 21:43:59  manojm
 * Add events for Watch Dog timer reset and new crash information found.
 *
 * Revision 1.16  2004/07/16 00:26:07  manojm
 * Event support while setting Subsystem and Controller settings
 *
 * Revision 1.15  2004/07/01 21:56:50  debinc
 * add pdm event class
 *
 * Revision 1.14  2004/02/12 03:47:22  debinc
 * support for event customization export/import
 *
 * Revision 1.13  2004/02/06 03:34:05  debinc
 * new eventstr lib
 *
 * Revision 1.12  2003/09/13 01:13:27  randallc
 * new events.h from fw
 *
 * Revision 1.21  2003/09/12 23:27:06  randallc
 * changed power on/off to system started/stopped
 *
 * Revision 1.20  2003/09/12 20:16:01  randallc
 * Added power on/off events
 *
 * Revision 1.19  2003/09/12 07:38:37  randallc
 * Changed all references to online expansion (OE) to onlince capacity
 * expansion (OCE)
 *
 * Revision 1.18  2003/09/12 07:07:59  randallc
 * Added new PSU events
 *
 * Revision 1.17  2003/09/12 06:48:49  randallc
 * Added BGA QUEUED events and Blower class events
 *
 * Revision 1.16  2003/09/06 00:56:38  randallc
 * Added support for new ssd events and some asd events.
 *
 * Revision 1.15  2003/09/05 04:15:12  venkatr
 * Link Up Down Event Add
 *
 * Revision 1.14  2003/08/19 17:50:38  randallc
 * Add SEP not found event.
 *
 * Revision 1.13  2003/08/18 18:30:03  randallc
 * Fixed battery event code typo CLASS->CODE and added EVENT_ID_* for battery
 *
 * Revision 1.12  2003/08/18 18:07:51  randallc
 * Added events: EVT_CODE_LD_AXLE_ONLINE &
 *               EVT_CODE_REBUILD_MARKED_LD_SYNCHRONIZED
 *
 * Also added EVT_ID_* for subsystem & cooling device events that were added
 * prior.
 *
 * Revision 1.11  2003/08/15 18:53:48  vedat
 * Added events for enclosure and BBU management
 *
 * Revision 1.10  2003/08/12 19:13:26  randallc
 * typo...COMPELETED should be COMPLETED
 *
 * Revision 1.9  2003/06/16 18:51:41  randallc
 * Terminology change of event code/id:
 *     An Event ID is will be known as a unique number which consists
 *     of an event class and event code.  An event code IS NOT unique,
 *     however, event classes are.
 *
 * Revision 1.8  2003/06/16 00:52:57  venkatr
 * setting partionflags
 *
 * Revision 1.7  2003/05/28 02:14:18  venkatr
 * term-pool2array merge
 *
 * Revision 1.6.2.1  2003/05/21 18:11:22  venkatr
 * Terminology Changes
 *
 * Revision 1.6  2003/05/10 01:16:59  randallc
 * Added global/dedicated spare used/deleted
 *
 * Revision 1.5  2003/05/09 22:56:37  randallc
 * Added support for mmap/async notification and fixed up some errors in
 * structure definitions.  Also added a new event for clearing event log
 *
 * Revision 1.4  2003/04/16 23:18:36  randallc
 * Added supported for global/dedicate spare deletion and addition
 *
 * Revision 1.3  2003/04/15 00:14:44  randallc
 * Missed event ID for media patrol - PD error encountered
 *
 * Revision 1.2  2003/04/12 22:37:07  randallc
 * Removed ^M from file
 *
 * Revision 1.1  2003/04/12 22:26:09  randallc
 * events.h file which defines all event classes and event IDs.
 *
 ******************************************************************************/
