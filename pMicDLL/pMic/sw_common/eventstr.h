#ifndef _EVENTSTR_H_
#define _EVENTSTR_H_
  
#include "mic.h"
#include "parseXML.h"

u32 getEvtStrDesc (EventId_t EvtId, u8 *pStrBuf, u32 *pBufLen, u8 * pLanguage);

u32 getEvtStrDescShort (EventId_t EvtId, u8 *pStrBuf, u32 *pBufLen, u8 * pLanguage);
  
u32 getEvtStrCause (EventId_t EvtId, u8 *pStrBuf, u32 *pBufLen, u8 * pLanguage);

u32 getEvtStrAction (EventId_t EvtId, u8 *pStrBuf, u32 *pBufLen, u8 * pLanguage);

u8 * getEvtStrSeverity(const u8 u8Severity, u8 * pLanguage);
u8 * getEvtStrClass(const u16 u16Class, u8 * pLanguage);
 
u32 initEvtStrLib();
u32 finalizeEvtStrLib();
u32 getEvtStrLibStatus(boolean_t * pbSuccess, u8 ** pbStatus, u8 * pLanguage);
EventCus_All_t * getEvtCusAll(u8 * pLanguage);
#endif /* _EVENTSTR_H_ */
/*******************************************************************************
 * Change Log
 *
 * $Log: eventstr.h,v $
 * Revision 1.13  2006/11/17 08:48:08  theoz
 * add winccfg64.mak to support 64-bits Windows
 *
 * Revision 1.12  2004/11/12 00:30:34  debinc
 * *** empty log message ***
 *
 * Revision 1.11  2004/06/10 00:02:03  debinc
 * move some string function from parseXML to libeventstr
 *
 * Revision 1.10  2004/04/06 22:39:55  debinc
 * *** empty log message ***
 *
 *******************************************************************************/



