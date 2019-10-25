/*******************************************************************************
 * Filename    : ipcdflt.h
 * Description : I2 IPC Default header file
 *               It provides default values for I2 IPC Settings
 * Created on  : 03/19/2003
 * CVS Version : $Id: ipcdflt.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_I2IPCDEFAULT_H__
#define __PI_I2IPCDEFAULT_H__

/* --- include standard C lib header files --------------------------------- */
#include <signal.h>

/* --- include internal header files --------------------------------------- */

/* --- constant definitions ------------------------------------------------ */
#define DEFAULT_I2IPC_MSGQ_PATH "/dev/islavista"
#define DEFAULT_I2IPC_MSGQ_CHANNEL 1
#define DEFAULT_I2IPC_NOTIFY_SIGNAL (SIGRTMAX-1)

#define DEFAULT_LIBEVT_CHANNEL 2
/* --- data structures ----------------------------------------------------- */

/* --- functional routines ------------------------------------------------- */

#endif /*__PI_I2IPCDEFAULT_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: ipcdflt.h,v $
 * Revision 1.2  2004/02/06 03:34:25  debinc
 * new shared memory channel
 *
 * Revision 1.1  2003/03/22 01:08:24  weny
 * separate ipc default from ipc.h.
 *
 ******************************************************************************/
