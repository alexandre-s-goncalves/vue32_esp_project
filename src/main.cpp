#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <EEPROM.h>

#include "vue32_header.hpp"
#include "vue32_functions.hpp"
#include "vue32_settings.hpp"
#include "vue32_wifi.hpp"

void setup()
{
    Serial.begin(115200);
    setCpuFrequencyMhz(240);
    // EEPROM memory init
    EEPROM.begin(256);
    EEPROM.get(Restart_Address, device_restart);
    device_restart++;
    EEPROM.put(Restart_Address, device_restart);
    EEPROM.commit();
    EEPROM.end();
    log("\n[INFO ] Starting setup");
    log("[ INFO ] Restarts " + String(device_restart));
    log("[ INFO ] Setup running on Core " + String(xPortGetCoreID()));
    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        log("[ ERROR ] Failed to initialize SPIFFS");
        while (true)
            ;
    }
    // read the settings.json file
    if (!settingsRead())
    {
        settingsSave();
    }
    // LED configuration
    settingPins();
    // WiFi setup
    wifi_setup();
}

void loop() {}
