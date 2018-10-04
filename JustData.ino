#include "Arduino.h"
#include "AZ3166WiFi.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"
#include "GFXDisplay.h" // 3rd party graphics lib, no work :(?
#include "HTS221Sensor.h" // temp and humid
#include "LPS22HBSensor.h" // pressure
#include "parson.h"

#define MESSAGE_MAX_LEN 256
#define DEVICE_ID "MXCHIPa3625351-648f-41a0-9a0b-e7d3d2681fbd"

unsigned char AzureBMP[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,192,192,224,240,56,12,192,240,224,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,224,224,224,224,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,224,248,252,254,255,255,63,15,3,64,248,254,255,255,255,255,255,252,248,224,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,240,252,127,31,3,3,15,127,254,240,192,0,0,0,0,8,28,28,28,28,156,220,252,124,60,28,0,0,0,252,252,248,0,0,0,0,0,0,252,252,248,0,0,0,0,252,252,252,112,56,28,28,28,0,128,224,240,248,28,28,12,12,28,248,248,240,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,224,248,252,255,255,255,255,63,15,3,0,0,0,0,0,0,3,7,15,31,63,127,255,255,255,255,255,252,240,224,128,0,0,0,0,0,0,64,112,124,127,31,7,7,7,7,7,7,7,7,31,127,126,120,64,0,96,112,120,126,127,103,99,97,96,96,96,0,0,0,63,127,127,240,224,224,96,96,56,127,127,127,0,0,0,0,127,127,127,0,0,0,0,0,0,15,63,127,123,243,227,227,227,227,99,99,35,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,8,8,8,8,8,12,12,12,12,12,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

DevI2C *i2c;
GFXDisplay display;
HTS221Sensor *sensorTempHumidity;

float humidity = 0;
float temperature = 0;
static bool hasWifi = false;

static void InitWifi()
{
    Screen.print(2, "Connecting Wifi...");

    if (WiFi.begin() == WL_CONNECTED) {
        IPAddress ip = WiFi.localIP();
        Screen.print(1, ip.get_address());
        hasWifi = true;
        Screen.print(2, "Connected! \r\n");
        delay(1000);
        Screen.clean();
    }
    else {
        hasWifi = false;
        Screen.print(1, "No Wi-Fi :(\r\n ");
    }
}

void setup()
{
    Screen.init();
    Serial.begin(115200); // wifi module
    hasWifi = false;
    InitWifi();

    if (hasWifi == true) {
        return;
    }
    else {
        Screen.print("start prgm...");
        delay(500);
        Screen.draw(0, 0, 128, 8, AzureBMP);
        delay(1000);
        i2c = new DevI2C(D14, D15);

        sensorTempHumidity = new HTS221Sensor(*i2c);
        sensorTempHumidity->init(NULL);
    }
}

void loop()
{
    if (hasWifi == false)
    {
        delay(1000);

        sensorTempHumidity->reset();
        sensorTempHumidity->getTemperature(&temperature);
        sensorTempHumidity->getHumidity(&humidity);
        Serial.print("Temperature: ");
        Serial.println(temperature);
        Serial.print("Humidity: ");
        Serial.println(humidity);

        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_number(root_object, "temperature", temperature);
        json_object_set_number(root_object, "humidity", humidity);

        char *serialized_string = json_serialize_to_string_pretty(root_value);

        char tbuf[10];
        char hbuf[10];
        sprintf(tbuf, "Temp %f", temperature);
        Screen.print(1, tbuf);
        sprintf(hbuf, "Humid %f", humidity);
        Screen.print(2, hbuf);

        char jsonbuf[256];
        snprintf(jsonbuf, 256, "JSON %s", serialized_string);

        char payload[MAMESSAGE_MAX_LENX];
        EVENT_INSTANCE *message = DevKitMQTTClient_Event_Generate(payload, MESSAGE);
        DevKitMQTTClient_SendEventInstance(message);

        json_free_serialized_string(serialized_string);
        json_value_free(root_value);

        delay(4000);
    }
}
