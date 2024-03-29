#ifndef I2_LIMIT_H
#define I2_LIMIT_H

#define MAX_ENCLOSURES 8
#define MAX_CONTROLLERS 2
#define MAX_PHYSICAL_DRIVES 256
#define MAX_LOGICAL_DRIVES 256
#define MAX_PORTS 16
#define MAX_ISCSI_NODES 25 /* Myron */
#define MAX_ISCSI_PORTS 4
#define MAX_FC_PORTS_PER_CTRL   2
#define MAX_ETHERNET_PORTS 1
#define MAX_SESSIONS 128
#define MAX_IMAGE_NAME_LEN 128
#define MAX_HOST_NAME_LEN 32
#define MAX_INITIATORS 128
#define MAX_LMM_ENTRIES 256
#define MAX_LUN_VALUE 256
#define MAX_PSCSI_LUN_VALUE 64

#define MAX_STORAGE_ARRAYS 256  /* TBD */
#define MAX_PHYDRV_PER_ARRAY 256  /* TBD */
#define MAX_LOGDRV_PER_ARRAY 32  /* TBD */
#define MAX_AXLES_PER_LOGDRV  16
#define MAX_PHYDRV_PER_AXLE  16
#define MAX_ASSOCIATED_ARRAYS_PER_ARRAY    8

#define MAX_ASSOCIATED_ARRAYS_PER_SPARE    MAX_ASSOCIATED_ARRAYS_PER_ARRAY

#define MAX_MISSING_PHYDRV 64
#define MAX_TRANSITION_PHYDRV 64

#define MAX_SPARES 256
#define SPARE_ARRAY_ID_MIN   256
#define SPARE_ARRAY_ID_MAX   511

#define MAX_TRAP_SINKS 32
#define MAX_RECIPIENTS 32

#define MAX_CACHE_POLICY_LENGTH 16
#define NETSEND_TRANSFER_SIZE  12600
#define MAX_DATA_TRANSFER_SIZE	65535
#define MAX_DATA_TRANSFER_SIZE_NEW (MAX_DATA_TRANSFER_SIZE * 3)

#define MAX_CHAP_RECORDS_PER_NODE   16
#define MAX_LENGTH_ISCSI_NODE_NAME  223

#endif /* I2_LIMIT_H */
