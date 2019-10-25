/*******************************************************************************
 *
 * Filename    : imgheader.h
 * Description : Header describing routines to parse flash map files and version
 *               header files
 * Created on  : 07/29/2003
 * CVS Version : $Id: parse.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _PARSE_VER_H_
#define _PARSE_VER_H_

/* Print Macros */
#ifdef _PTIP_DEBUG_
#define PTIP_DBG(param, args...)  printf("PTIP: "param, ##args)
#else
#define PTIP_DBG(...)
#endif

#define PTIP_PRINT(param, args...)  printf("PTIP: "param, ##args)
#define PTIP_ERROR(param, args...)  printf("PTIP: Error "param, ##args)

#define PTIP_MAX_LINE_SIZE      1024

#define PTIP_BUILD_NUM_STR      "BUILD_NUM"
#define PTIP_FLASH_TYPE_STR     "FLASH_TYPE"
#define PTIP_MAJOR_VER_STR      "MAJOR_VER"
#define PTIP_MINOR_VER_STR      "MINOR_VER"
#define PTIP_OEM_CODE_STR       "OEM_CODE"
#define PTIP_PRODUCT_TYPE_STR   "PRODUCT_TYPE"
#define PTIP_FLASH_COPY_NUM_STR "COPY_NUM"

/* Function Declarations */
int ptip_ParseHeader (char *HeaderToRead, ih_t *ImgHeader);
int ptip_ParseFlashMap (char *FmapToRead, flashMapInfo_t *FmHeader, int MaxCount);

#endif /* _PARSE_VER_H_ */

/*******************************************************************************
 * Change Log
 *
 * $Log: parse.h,v $
 * Revision 1.1  2006/08/14 18:38:00  david.chiu
 * Copied from util/ptiflash
 *
 * Revision 1.3  2004/10/06 22:00:38  randallc
 * added support for flashing ptiflash rom version for islavista hw
 *
 * Revision 1.2  2003/07/30 00:36:37  randallc
 * Forgot to add the change log at the bottom of all the source files.
 *
 ******************************************************************************/
