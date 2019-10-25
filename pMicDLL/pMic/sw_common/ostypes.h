/*******************************************************************************
 *
 * Filename    : ostypes.h
 * Description : OS specific defines
 * Created on  : 07/29/2003
 * CVS Version : $Id: ostypes.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _OSTYPES_H_
#define _OSTYPES_H_

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

#endif /* _OSTYPES_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: ostypes.h,v $
 * Revision 1.1  2006/08/14 18:36:04  david.chiu
 * Copied from util/ptiflash
 *
 * Revision 1.2  2003/07/30 00:36:37  randallc
 * Forgot to add the change log at the bottom of all the source files.
 *
 ******************************************************************************/
