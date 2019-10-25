/*******************************************************************************
 * Filename    : parseXML.h
 * Description : paring imported XML header file
 *               * function headers to handle import XML file parsing
 * Created on  : 01/26/04
 * CVS Version : $Id: parseXML.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PARSE_XML_H__
#define __PARSE_XML_H__

#include <libxml/tree.h>

#include "pibasic.h"
#include "errorlog.h"
#include "errcode.h"
#include "events.h"
#include "mic.h"

/* --- constant definitions & data structures ------------------------------ */

#define MAX_NUM_EVENT   800
#define EVTCUS_FILE_NAME "event_EN.xml"
#define EVTCUS_FILE_LOCATION "../evtxml/"
#define EVTCUS_RNG_FILE_NAME "event.rng"
#define EVTCUS_REG_PATH "SOFTWARE\\Promise\\Common"
#define EVTCUS_REG_KEY_NAME "EventXmlFilePath"
#define EVTCUS_MAX_EVENTINFO_LEN 64
#define EVTCUS_MAX_EVENTSTR_LEN 256
#define EVTCUS_MAX_CLASS_LEN 64
#define EVTCUS_MAX_SEVERITY_LEN 32
#define EVTCUS_MAX_LOGLOCATION_LEN 32
#define MAX_STATUS_LEN 1024
#define STRING_NO_IMPORT_ERR_WARN "No error or warning"

// Log location used by SW should start with the last log location for FW
#define EVT_LOCATION_POPUP   (EVT_LOCATION_CURRENT_MAX + 0x1)
// The last one is the mamimum
#define EVT_LOCATION_MAX     EVT_LOCATION_POPUP

typedef struct
{
  u32 esi_u32EvtStrDesc;
  u32 esi_u32EvtStrCause;
  u32 esi_u32EvtStrAction;
  u32 esi_reserved;
} EvtCusStrOffset_t;

typedef struct
{
    u8          ecd_Classtype[EVT_CURRENT_MAX_CLASSES+1][EVTCUS_MAX_CLASS_LEN];
    u8          ecd_Secerity[EVT_SEVERITY_MAX_LEVEL+1][EVTCUS_MAX_SEVERITY_LEN];
    u8          ecd_LogLocation[EVT_LOCATION_MAX+1][EVTCUS_MAX_LOGLOCATION_LEN];
}EventCus_Display_t;

typedef struct
{
    u8          ec_EventInfo[EVTCUS_MAX_EVENTINFO_LEN];
    u8          ec_EventDesc[EVTCUS_MAX_EVENTSTR_LEN];
    u8          ec_EventCause[EVTCUS_MAX_EVENTSTR_LEN];
    u8          ec_EventAction[EVTCUS_MAX_EVENTSTR_LEN];
    u32         ec_VendorEventId;
    u16         ec_EventCode;
    u16         ec_Class;
    boolean_t   ec_LogLocation[EVT_LOCATION_MAX+1];
    u8          ec_Severity;
    u8          ec_Reserved[3];
} EventCus_t;

typedef struct
{
    u32         eci_VendorEventId;
    u8          eci_Count;  
    u8          eci_Reserved[3];  
} EventCus_Id_t;

typedef struct
{
     u8                     eca_u8Language[32];
     u16                    eca_u16NumEvent;
     boolean_t              eca_bParseSuccess;
     u8                     eca_u8CompleteFlag;
     u8                     eca_u8Reserved[4];
     u8                     eca_u8ParseStatus[MAX_STATUS_LEN];
     EventCus_Display_t     eca_Display;
     EventCus_t             eca_Events[MAX_NUM_EVENT];
     EventCus_Id_t          eca_EvtIdMap[EVT_CURRENT_MAX_CLASSES+1][EVT_MAX_EVENTS_PER_CLASS];
     EvtCusStrOffset_t      eca_esoStrOffset[EVT_CURRENT_MAX_CLASSES+1][EVT_MAX_EVENTS_PER_CLASS];
} EventCus_All_t;

/* --- public routine section ---------------------------------------------- */

u32 getNumEvt(u32 * u32numEvt );

u32 loadEvtCus(EventCus_All_t * pec, u8 * fileName);

const char * getEvtInternalStrSeverity(u8 u8Severity);

const char * getEvtInternalStrSeverityAndAbove(u8 u8Severity);

void getEvtInternalSeverityId(const char * pstrKeyword, u8 * id);

const char * getClassStr(u16 id);

const char * getLogLocationStr(u8 id);

u32 getClassId(const char * pstrKeyword, u16 * id);

u32 getIntFromStr(u8 * str, u32 * pInt);


/**************************************************************************
* Function Name: validateRelaxNg
* Description: validate XML file
* Parameters:
*       [in] fileName, rng file to be checked against.
*       [out] error, parsing errors
*       [in] doc, doc pointer of XML file
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: None.
****************************************************************************/
u32 validateRelaxNG(char *rngFile, char * error, xmlDocPtr doc);

u32 readEvents(EventCus_All_t * peca, char * fileName);

#endif  /* __PARSE_XML_H__ */

/*******************************************************************************
 * Change Log
 *
 * $Log: parseXML.h,v $
 * Revision 1.24.40.1  2009/12/02 06:38:18  xinw
 * expand MAX_NUM_EVENT
 *
 * Revision 1.24  2007/01/22 08:58:44  danielz
 * new log location "popup"
 *
 * Revision 1.23  2006/09/26 01:46:52  xinc
 * Change EVTCUS_REG_KEY_NAME from "EventPath" to ""EventXmlFilePath""
 *
 * Revision 1.22  2006/09/25 06:00:48  xinc
 * Store the path of event_EN.xml in registry, which will be used to find event_EN.xml by CLI or other in-band SW.
 *
 * Revision 1.21  2006/09/25 05:52:23  xinc
 * *** empty log message ***
 *
 * Revision 1.20  2006/08/21 03:42:02  danielz
 * Add a new function getEvtInternalStrSeverityAndAbove() to return something
 * like "info and above" etc.
 *
 * Revision 1.19  2005/01/27 23:00:08  debinc
 * 8 byte aligned
 *
 * Revision 1.18  2004/12/02 02:34:18  debinc
 * mobe some variables to shared memory to save memory
 *
 * Revision 1.17  2004/12/01 18:25:59  debinc
 * Fix shared memory problem
 *
 * Revision 1.16  2004/11/12 00:30:34  debinc
 * *** empty log message ***
 *
 * Revision 1.15  2004/06/10 18:03:18  debinc
 * Add some reserved byte to make 8-byte aligned
 *
 * Revision 1.14  2004/06/10 00:02:15  debinc
 * move some string function from parseXML to libeventstr
 *
 * Revision 1.13  2004/04/06 22:40:08  debinc
 * *** empty log message ***
 *
 * Revision 1.12  2004/03/31 19:14:39  debinc
 * move getEvtCusAll to other file
 *
 * Revision 1.11  2004/03/24 03:30:25  weny
 * I2 API porting
 *
 * Revision 1.10  2004/03/15 22:19:56  debinc
 * make two more function public
 *
 * Revision 1.9  2004/03/05 03:24:28  debinc
 * provide a getLogLocation function
 *
 * Revision 1.8  2004/02/18 22:37:42  debinc
 * Add more functions
 *
 * Revision 1.7  2004/02/12 03:47:22  debinc
 * support for event customization export/import
 *
 * Revision 1.6  2004/02/10 20:24:57  debinc
 * include "mic.h" for some #define
 *
 * Revision 1.5  2004/02/07 02:33:32  debinc
 * roll back
 *
 * Revision 1.4  2004/02/07 01:03:44  debinc
 * move two function headers from libparseXML to libeventstr
 *
 * Revision 1.3  2004/02/07 00:14:13  debinc
 * correct a function definition merge error
 *
 * Revision 1.2  2004/02/06 22:09:13  debinc
 * move errorHadle fuction to individual files
 *
 * Revision 1.1  2004/02/06 03:41:39  debinc
 * use new eventstr lib
 *
 ******************************************************************************/

