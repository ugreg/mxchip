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

    // TODO: hex to int
    // ᕕ( ᐛ )ᕗ memory addresses!!!... no... just constants defined as hex instead of ints for some reason...
    #define IOTC_PROTOCOL_MQTT 0x01
    #define IOTC_PROTOCOL_AMQP 0x02
    #define IOTC_PROTOCOL_HTTP 0x04
    typedef short IOTCProtocol;

    #define IOTC_LOGGING_DISABLED 0x01
    #define IOTC_LOGGING_API_ONLY 0x02
    #define IOTC_LOGGING_ALL      0x10
    typedef short IOTLogLevel;

    #define IOTC_CONNECT_SYMM_KEY          0x01
    #define IOTC_CONNECT_X509_CERT         0x02
    #define IOTC_CONNECT_CONNECTION_STRING 0x04
    typedef short IOTConnectType;

    #define IOTC_CONNECTION_EXPIRED_SAS_TOKEN    0x01
    #define IOTC_CONNECTION_DEVICE_DISABLED      0x02
    #define IOTC_CONNECTION_BAD_CREDENTIAL       0x04
    #define IOTC_CONNECTION_RETRY_EXPIRED        0x08
    #define IOTC_CONNECTION_NO_NETWORK           0x10
    #define IOTC_CONNECTION_COMMUNICATION_ERROR  0x20
    #define IOTC_CONNECTION_OK                   0x40
    typedef short IOTConnectionState;

    #define IOTC_MESSAGE_ACCEPTED   0x01
    #define IOTC_MESSAGE_REJECTED   0x02
    #define IOTC_MESSAGE_ABANDONED  0x04
    typedef short IOTMessageStatus;


}
