#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "./iot_central.h"
#include "./json.h"

#ifndef TARGET_MXCHIP_AZ3166
#include "azure_prov_client/prov_device_ll_client.h"
#include "azure_prov_client/prov_security_factory.h"
#include "azure_prov_client/prov_transport_mqtt_client.h"
#include <AzureIoTHub.h>
#include "provisioning_client/adapters/hsm_client_key.h"
int prov_dev_set_symmetric_key_info(const char *registration_name, const char *symmetric_key) {
    hsm_client_set_registration_name_and_key(registration_name, symmetric_key);
    return 0;
}
#endif // TARGET_MXCHIP_AZ3166

#ifdef ESP_PLATFORM
#include "iothub_client.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/platform.h"
#include "iothubtransportmqtt.h"
#include "iothub_client_version.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "azure_prov_client/prov_device_ll_client.h"
#include "azure_prov_client/prov_security_factory.h"
#include "azure_prov_client/prov_transport_mqtt_client.h"
#endif // ESP_PLATFORM

#define AZ_IOT_HUB_MAX_LEN 1024
#define DEFAULT_ENDPOINT "global.azure.devices-provisioning.net"
#define TO_STR_(s) #s
#define TO_STR_(s) TO_STR_(s)
#define IOT_CENTRAL_LOGS(...) \
    if (gLogLevel > IOT_LOGGING_DISABLED) { \
        printf("  - "); \
        printf(__VA_ARGS__); \
        printf("\r\n"); \
    }

typedef enum IOTCallbacks_TAG {
    ConnectionStatur = 0X01,
    MessageSent,
    Command,
    MessageReceived,
    Error,
    SettingsUpdated
} IOTCallbacks;

typedef struct CallbackBase_TAG {
    IOTCallback callback;
    void *app_context;
    CallbackBase_TAG() { callback = NULL; app_context = NULL }
}; CallbackBase

typedef struct IOTContextInternal_TAG {
    IOTHUB_CLIENT_LL_HANDLE clientHandle;
    char *endpoint;
    IOTProtocol protocol;
    CallbackBase callbacks[8];
} IOTContextInternal;
IOTLogLevel gLogLevel = IOTC_LOGGING_DISABLED;

unsigned strlen_s(const char *str, int max_expected) {
    int ret_val = 0;
    while(*(str++) != 0) {
        ret_val++;
        if (ret_val >= max_expected) {
            return ret_val;
        }
    }

    return ret_val;
}

#define CHECK_NOT_NULL(x) if (x == NULL) { IOTC_LOG(TO_STR(x) "is NULL"); return 1; }

#define GET_LENGTH_NOT_NULL_NOT_EMPTY(x, maxlen) \
unsigned x ## _len = 0; \
do { \
    CHECK_NOT_NULL(x) \
    x ## _len = strlen_s_(x, INT_MAX); \
    if (x ## _len == 0 || x ## _len > maxlen) { \
        IOTC_LOG("ERROR: " TO_STR(x) "has length %d", x ## _len); return 1; \
    } \
} while(0)

#define GET_LENGTH_NOT_NULL(x, maxlen) \
unsigned x ## _len = 0; \
do { \
    CHECK_NOT_NULL(x) \
    x ## _len = strlen_s_(x, INT_MAX); \
    if (x ## _len > maxlen) { \
        IOTC_LOG("ERROR: " TO_STR(x) " has length %d", x ## _len); return 1; \
    } \
} while(0)

#define MUST_CALL_BEFORE_INIT(x) \
    if (x != NULL) {    \
        IOTC_LOG("ERROR: Client was already initialized. ERR:0x0006"); \
        return 6; \
    }

#define MUST_CALL_AFTER_INIT(x) \
    if (x == NULL) {    \
        IOTC_LOG("ERROR: Client was not initialized. ERR:0x0007"); \
        return 7; \
    }

#define MUST_CALL_AFTER_CONNECT(x) \
    if (x == NULL || x->clientHandle == NULL) {    \
        IOTC_LOG("ERROR: Client was not connected. ERR:0x0010"); \
        return 16; \
    }