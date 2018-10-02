#include "Arduino.h"
#include "AZ3166WiFi.h"
#include "AzureIotHub.h"
#include "DevKitMQTTClient.h"
#include "GFXDisplay.h" // 3rd party graphics lib, no work :(?
#include "HTS221Sensor.h" // temp and humid
#include "LPS22HBSensor.h" // pressure
#include "parson.h"

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
    Serial.begin(115200);
    hasWifi = false;
    InitWifi();

    if (!hasWifi) {
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
    if (hasWifi)
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
        sprintf(tbuf, "Tenp %f", temperature);
        Screen.print(1, tbuf);
        sprintf(hbuf, "Humid %f", humidity);
        Screen.print(2, hbuf);

        delay(4000);
    }
}

// void setup()
// {
//     i2c = new DevI2C(D14, D15);
//     sensorTempHumidity = new HTS221Sensor(*i2c);
//     sensorTempHumidity -> init(NULL);

//     Screen.init();
// }

// void loop()
// {
//     // sensorTempHumidity -> enable();
//     Screen.draw(0, 0, 128, 8, AzureBMP);
//     delay(1000);

//     sensorTempHumidity->getTemperature(&temperature);
//     sensorTempHumidity->getHumidity(&humidity);
//     Serial.print("Temperature: ");
//     Serial.println(temperature);

//     char buf[10];
//     char *serializedString = NULL;

//     JSON_Value *root_value = json_value_init_object();
//     JSON_Object *root_object = json_value_get_object(root_value);

//     delay(4000);

//     json_object_set_number(root_object, "temperature", temperature);
//     json_object_set_number(root_object, "humidity", humidity);
//     serializedString = json_serialize_to_string_pretty(root_value);

//     sprintf(buf, "%s", serializedString);

//     // sensorTempHumidity -> disable();
//     // sensorTempHumidity -> reset();

//     delay(4000);

//     Screen.clean();
// }
