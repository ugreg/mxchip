#ifndef AZURE_IOTCEN_API
#define AZURE_IOTCEN_API

#ifndef ESP_PLATFORM
#define TARGET_MXCHIP_AZ3166
#endif

#ifndef TARGET_MXCHIP_AZ3166
#include <Arduino.h>
#endif

#ifndef _cpluscplus
// TODO: consider replacing extern c with cpp, what are the implications
// https://stackoverflow.com/questions/31903594/typedef-struct-in-c-vs-c
extern "C"
{
    #endif
    typedef struct IOT_C_HTTP_PROXY_OPTIONS_TAG
    {
        const char *host_address;
        int port;
        const char *username;
        const char *password;
    } IOT_HTTP_PROXY_OPTIONS;

    typedef struct IOTCallbackInfo_TAG
    {
        const char *event_name;
        const char *tag;
        const char *payload;
        unsigned payload_length;

        void *app_context;

        int status_code;
        void *callback_response;
    } IOTCallbackInfo;

    typedef void* IOTContext;

    // ᕕ( ᐛ )ᕗ memory addresses!!!
}
