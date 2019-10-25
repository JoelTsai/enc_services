#ifndef EVENT_SEND_SYNC_H
#define EVENT_SEND_SYNC_H
#undef EVENT_NOTIFY_API
#undef EVENT_NOTIFY_CALL
#ifdef WINDOWS
    #include "windows.h"
            #if defined(PROMISE_EVENT_NOTIFY_DLL)
                        #define EVENT_NOTIFY_API  __declspec(dllexport)
                        #define EVENT_NOTIFY_CALL
            #else
                        //#define PROMISEAPI  __declspec(dllimport)
                        #define EVENT_NOTIFY_API
                        #define EVENT_NOTIFY_CALL __cdecl
            #endif
#else
            #define EVENT_NOTIFY_API
            #define EVENT_NOTIFY_CALL
#endif

#define MAX_SUBSYS  16

#include "errorlog.h"

#include "i2types.h"

#include "mic.h"



//typedef __u32 (* pfunc_sendevent_t)( Event_t *  );

typedef u32 (* pfunc_sendevent_t)(void * pParam, device_id_t, Event_t *  );

typedef struct
{
    u16 en_u16Size; /* size of this data structure */
    u8 en_u8Reserved1[6];

    device_id_t en_diDeviceId;
    session_id_t en_siSessionId;
    u32 en_u32SeverityMask;
    u64 en_u64EventClassMask;
    #ifdef EMBEDDED
    u8 en_u8PidFileName[MAX_PATH_LENGTH+1];
    #else
    u32 en_u32PollInterval;
    u8 en_u8Reserved2[MAX_PATH_LENGTH-3];
    #endif
    pfunc_sendevent_t en_pfsendevent;
    #ifndef PLATFORM_64BIT	
    void * en_pPadding1;       /* padding for 8 byte alignment */
    #endif
    boolean_t * en_pbToTerminate;
    #ifndef PLATFORM_64BIT	
    void * en_pPadding2;       /* padding for 8 byte alignment */
    #endif
    error_handler_t * en_pehErrorHandler;
    #ifndef PLATFORM_64BIT	
    void * en_pPadding3;       /* padding for 8 byte alignment */
    #endif
    void * en_pSendEventParam;
    #ifndef PLATFORM_64BIT	
    void * en_pPadding4;       /* padding for 8 byte alignment */
    #endif
}event_notify_param_t;

EVENT_NOTIFY_API u32 EVENT_NOTIFY_CALL initializeEventNotify(event_notify_param_t *pen);

EVENT_NOTIFY_API u32 EVENT_NOTIFY_CALL listenForEvent();

EVENT_NOTIFY_API void EVENT_NOTIFY_CALL finalizeEventNotify();

#endif

