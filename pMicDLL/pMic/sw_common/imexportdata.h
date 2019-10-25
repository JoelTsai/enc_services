/*******************************************************************************
 * Filename    : imexportdata.h
 * Description : import export data header file
 *               * Shared import export information data strcture
 * Created on  : 12/16/03
 * CVS Version : $Id: imexportdata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __IMEXPORT_H__
#define __IMEXPORT_H__

#include "pibasic.h"

#define IMEXPORT_UNKNOWNTYPE 0
#define IMEXPORT_USERDATABASE 1
#define IMEXPORT_EVENTCUS 2
#define IMEXPORT_SUBSYSTEM 3
#define IMEXPORT_CONFIGSCRIPT 4

#ifdef EMBEDDED
#ifdef DUAL_SYNC_SUPPORT
#define IMEXPORT_SUBSYSTEM_FILE_NAME   "/islavista/flash/subsysteminfo"
#define IMEXPORT_CONFIGSCRIPT_NAME    "/islavista/flash/configscript"
#define IMPORT_FILE_PATH "/islavista/flash/import"
#else
#define IMEXPORT_SUBSYSTEM_FILE_NAME   "/tmp/subsysteminfo"
#define IMEXPORT_CONFIGSCRIPT_NAME    "/tmp/configscript"
#define IMPORT_FILE_PATH "/tmp/import"
#endif
#endif

#define IMEXPORT_HTTP 1
#define IMEXPORT_TFTP 2

//error will defined in order of seriousness
#define IMPORT_ERR_NOERROR      0
#define IMPORT_ERR_WARNING      1
#define IMPORT_ERR_DATAERROR    2
#define IMPORT_ERR_WRONGFILE    3
#define IMPORT_ERR_SYNTEXERROR  4
#define IMPORT_ERR_UNKNOWN      5

typedef struct
{
    u8          ep_u8FileType;
    boolean_t   ep_bEncryption;
    u8          ep_u8Method;
    u8          ep_u8Language;
    u16         ep_u16PortNum;
    boolean_t   ep_bTextFormat;
    boolean_t   ep_bZip;
    u8          ep_u8Host[16];
    u8          ep_u8DisableTFTP;
    u8          ep_u8FileName[MAX_PATH_LENGTH+1];

} export_param_t;

typedef struct
{

    u8          ip_u8Filename[MAX_PATH_LENGTH+1];
    boolean_t   ip_bDecryption;
    u8          ip_u8Method;
    boolean_t   ip_bImmediate;
    boolean_t   ip_bInfoOnly;
    u8          ip_u8Language;
    u8          ip_u8FileType;
    u8          ip_u8Reserved1;
    u16         ip_u16PortNum;
    u8          ip_u8Reserved2[6];
    u8          ip_u8Host[16];    
} import_param_t;

typedef struct
{
    u8          is_u8FileType;
    u8          is_u8Status;
    u8          is_u8Reserved[6];
    u8          is_u8Detail[1024];    
} import_status_t;
#endif /* __IMEXPORT_H__ */

/*******************************************************************************
 * Change Log
 *
 * $Log: imexportdata.h,v $
 * Revision 1.12.6.1  2009/09/29 03:05:55  xinw
 * merge Import/Export consistent to E-class
 *
 * Revision 1.12  2008/06/20 03:03:12  danielz
 * move macro definition IMPORT_FILE_PATH from i2/imexport.c
 *
 * Revision 1.11  2008/05/07 07:31:44  xinw
 * add ep_bTextFormat to export_param_t
 *
 * Revision 1.10  2007/11/23 05:36:27  danielz
 * zip option in export_param_t
 *
 * Revision 1.9  2007/03/23 10:43:28  xinc
 * Add export function to GUI subsystem info page
 *
 * Revision 1.8  2006/12/01 08:07:56  danielz
 * subsystem info file location shared by i2 and CLI
 *
 * Revision 1.7  2006/08/24 02:32:44  xinc
 * Support "Configuration Export" in CLI
 *
 * Revision 1.6  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.5  2004/03/24 23:03:16  debinc
 * remove extra empty lines
 *
 * Revision 1.4  2004/03/24 03:28:34  weny
 * I2 API porting
 *
 * Revision 1.3  2004/02/12 03:47:22  debinc
 * support for event customization export/import
 *
*******************************************************************************/
