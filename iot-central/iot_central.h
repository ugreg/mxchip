#ifndef AZURE_IOT_CENTRAL_API
#define AZURE_IOT_CENTRAL_API

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
    typedef struct IOT_CENTRAL_HTTP_PROXY_OPTIONS_TAG
    {
        const char *host_address;
        int port;
        const char *username;
        const char *password;
    } IOT_HTTP_PROXY_OPTIONS;

    typedef struct IOT_CallbackInfo_TAG
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

    // TODO: hex to int
    // ᕕ( ᐛ )ᕗ memory addresses!!!... no... just constants defined as hex instead of ints for some reason...
    #define IOT_CENTRAL_PROTOCOL_MQTT 0x01
    #define IOT_CENTRAL_PROTOCOL_AMQP 0x02
    #define IOT_CENTRAL_PROTOCOL_HTTP 0x04
    typedef short IOTProtocol;

    #define IOT_CENTRAL_LOGGING_DISABLED 0x01
    #define IOT_CENTRAL_LOGGING_API_ONLY 0x02
    #define IOT_CENTRAL_LOGGING_ALL      0x10
    typedef short IOTLogLevel;

    #define IOT_CENTRAL_CONNECT_SYMM_KEY          0x01
    #define IOT_CENTRAL_CONNECT_X509_CERT         0x02
    #define IOT_CENTRAL_CONNECT_CONNECTION_STRING 0x04
    typedef short IOTConnectType;

    #define IOT_CENTRAL_CONNECTION_EXPIRED_SAS_TOKEN    0x01
    #define IOT_CENTRAL_CONNECTION_DEVICE_DISABLED      0x02
    #define IOT_CENTRAL_CONNECTION_BAD_CREDENTIAL       0x04
    #define IOT_CENTRAL_CONNECTION_RETRY_EXPIRED        0x08
    #define IOT_CENTRAL_CONNECTION_NO_NETWORK           0x10
    #define IOT_CENTRAL_CONNECTION_COMMUNICATION_ERROR  0x20
    #define IOT_CENTRAL_CONNECTION_OK                   0x40
    typedef short IOTConnectionState;

    #define IOT_CENTRAL_MESSAGE_ACCEPTED   0x01
    #define IOT_CENTRAL_MESSAGE_REJECTED   0x02
    #define IOT_CENTRAL_MESSAGE_ABANDONED  0x04
    typedef short IOTMessageStatus;


}
