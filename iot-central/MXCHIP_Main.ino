// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#define SERIAL_VERBOSE_LOGGING_ENABLED 1
#include "./iot_central.h"
#include "./string_buffer.h"
#include <EEPROMInterface.h>
#include "AZ3166WiFi.h"

static IOTContext context = NULL;

#define WIFI_SSID "Lorule";
#define WIFI_PASSWORD "pwnnubz";

IOTConnectType connectType = IOTC_CONNECT_CONNECTION_STRING;
const char *scopeId = "";
const char *deviceId = "";
const char *deviceKey = "";

// PRIMARY/SECONDARY KEY ?? (DPS)
// Uncomment below to Use DPS Symm Key (primary/secondary key..)
// IOTConnectType connectType = IOTC_CONNECT_SYMM_KEY;
// const char* scopeId = "<Enter ScopeID>";
// const char* deviceId = "<Enter DeviceId>";
// const char* deviceKey = "<Enter Primary or Secondary Device Key here>";

static bool isConnected = false;

void onEvent(IOTContext iotContext, IOTCallbackInfo *callbackInfo)
{
    if (strcmp(callbackInfo->eventName, "ConnectionStatus") == 0) {
        LOG_VERBOSE("Is connected ? %s (%d)", callbackInfo->statusCode == IOTC_CONNECTION_OK ? "Yes" : "No",
        callbackInfo->statusCode);
        isConnected = callbackInfo->statusCode == IOTC_CONNECTION_OK;
    }

    AzureIOT::StringBuffer stringBuffer;
    if (callbackInfo->payloadLength > 0) {
        stringBuffer.initialize(callbackInfo->payload, callbackInfo->payloadLength);
    }

    LOG_VERBOSE("- [%s] event was received. Payload => %s", callbackInfo->eventName, buffer.getLength() ? *buffer : "EMPTY");

    if (strcmp(callbackInfo->eventName, "Command") == 0) {
        LOG_VERBOSE("Command name was => %s\r\n", callbackInfo->tag);
    }
}