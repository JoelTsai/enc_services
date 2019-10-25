/*******************************************************************************
 * Filename    : i2ipc.h
 * Description : I2 IPC header file
 *               It provides the data structure and constant definitions of  
 *               I2 IPC.
 * Created on  : 01/27/03
 * CVS Version : $Id: i2ipc.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_I2IPC_H__
#define __PI_I2IPC_H__

/* --- include standard C lib header files --------------------------------- */
#include <signal.h>

/* --- include internal header files --------------------------------------- */
#include "pibasic.h"
#ifdef EMBEDDED
#include "ipcdflt.h"
#endif
#include "reqdef.h"

/* --- constant definitions ------------------------------------------------ */
#define I2IPC_SIGNATURE         0x01
#define I2IPC_MESSAGE_TYPE		1

#define SV_W	0400
#define SV_R	0200

#define SVMSG_MODE	( SV_W | SV_R | (SV_W>>3) | (SV_R>>3) | (SV_W>>6) | (SV_R>>6) )
#define SVSHM_MODE	SVMSG_MODE

#define I2IPC_MESSAGE_MAX_SIZE 512 /* including the message type */

/* read/write control */
#define I2IPC_RW_NONE       0
#define I2IPC_RW_READ       0x01
#define I2IPC_RW_WRITE      0x02

/* --- data structures ----------------------------------------------------- */

typedef struct
{
    long im_lType;            /*the type of the message, always I2IPC_MESSAGE_TYPE*/
	__u32 im_u32TimeStamp;    /*the time stamp just before the msg is sent to the queue*/
	__u32 im_u32Timeout;      /*the timeout interval of the request*/
	__u32 im_u32ProcessId;    /*the process id of the sending process*/
	__u32 im_u32ThreadId;     /*the thread id of the sending thread*/
	__u32 im_u32Signature;    /*the signature of the I2 IPC, always I2IPC_SIGNATURE*/
	__u32 im_u32SessionId;    /*the session id of a logging session*/
	int im_nSharedMemoryId;   /*the id of the shared memory associated to the request*/
    int im_nSemaphoreId;      /*the id of the semaphore associated to the request*/
    __u8 im_u8RWControl;      /*the data transfer direction, it can be I2IPC_RW_NONE, I2IPC_RW_READ, or I2IPC_RW_WRITE*/
	__u8 im_u8RequestGroupId; /*the request group id*/
	__u8 im_u8RequestId;      /*the request id*/
    __u8 im_u8Reserved;       /*reserved for data alignment*/
	__u32 im_u32ParamLength;  /*the length of the request parameter in bytes*/
	__u8 im_u8Param[4];       /*the request parameter begins here. Its length can be variable*/
} i2ipc_message_t;

typedef struct
{
	__u32 ism_u32Status;      /*the completion status of the request, using the error code defined in errcode.h*/
	__u32 ism_u32Length;      /*the length of the expected data for READ, the length of the data for WRITE*/
	__u32 ism_u32RetLength;   /*the return data length for READ, 0 for WRITE*/
	__u8  ism_u8Data[4];      /*the returned data for READ, the data sent to I2 for WRITE*/
} i2ipc_shared_memory_t;

/* --- functional routines ------------------------------------------------- */

#endif /*__PI_I2IPC_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: i2ipc.h,v $
 * Revision 1.6  2008/06/05 06:49:12  theoz
 * 1. remove I2IPC_RW_RESET
 *
 * Revision 1.5  2008/05/28 07:01:40  theoz
 * Add Pd Reset Pass Thru Command
 *
 * Revision 1.4  2004/06/08 21:26:04  weny
 * include ipcdflt.h only for embedded
 *
 * Revision 1.3  2004/03/24 03:28:18  weny
 * I2 API porting
 *
 * Revision 1.2  2003/03/22 00:53:07  weny
 * i2 ipc interface change - isolcate f/w data struct & cmd inside i2client.
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 ******************************************************************************/
