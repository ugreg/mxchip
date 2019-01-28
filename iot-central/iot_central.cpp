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