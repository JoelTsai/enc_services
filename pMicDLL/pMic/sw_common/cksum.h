/*******************************************************************************
 *
 * Filename    : cksum.h
 * Description : Header file used for check sum routines (posix checksum is the
 *               only supported file currently)
 * Created on  : 07/29/2003
 * CVS Version : $Id: cksum.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _CKSUM_H_
#define _CKSUM_H_

unsigned int cksum32(char *file, size_t offset, size_t size);

#endif /* _CKSUM_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: cksum.h,v $
 * Revision 1.1  2006/08/14 18:35:11  david.chiu
 * Copied from util/ptiflash
 *
 * Revision 1.2  2003/07/30 00:36:37  randallc
 * Forgot to add the change log at the bottom of all the source files.
 *
 ******************************************************************************/
