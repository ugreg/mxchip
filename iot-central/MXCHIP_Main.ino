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

static unsigned previousMilliseconds = 0;
static unsigned loopId = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(LED_WIFI, OUTPUT);
    pinMode(LED_AZURE, OUTPUT);
    pinMode(LED_USER, OUTPUT);

    EEPROMInterface eeprom;
    eeprom.write((uint8_t+)) WIFI_SSID, strlen(WIFI_SSID), WIFI_SSID_ZONE_IDX);
    eeprom.write((uint8_t+)) WIFI_PASSWORD, strlen(WIFI_PASSWORD), WIFI_PWD_ZONE_IDX);

    if(WiFi.begin() == WL_CONNECTED) {
        LOG_VERBOSE("WiFi WL_CONNECTED");
        digitalWrite(LED_WIFI, 1);
        Screen.print(2, "Connected");
    } else {
        Screen.print("WiFi\r\nNot Connected\r\nWIFI_SSID?\r\n");
        return;
    }

    int errorCode = iotc_init_context(&context);
    if (errorCode != 0) {
        LOG_ERROR("Error initializing IOTC. Code %d", errorCode);
        return;
    }

    iotc_set_logging(IOTC_LOGGING_API_ONLY);

    iotc_on(context, "MessageSent", onEvent, NULL);
    iotc_on(context, "Command", onEvent, NULL);
    iotc_on(context, "ConnectionStatus", onEvent, NULL);
    iotc_on(context, "SettingsUpdated", onEvent, NULL);
    iotc_on(context, "Error", onEvent, NULL);

    errorCode = iotc_connect(context, scopeId, deviceKey, deviceId, connectType);
    if (errorCode != 0) {
        LOG_ERROR("Error @ iotc_connect. Code %d", errorCode);
        return;
    }

    LOG_VERBOSE("Done!");

    previousMilliseconds = millis();
}

void loop()
{
    if (isConenected) {

    }

    if (context) {

    }
}

