#include <Arduino.h>

#ifndef VUE32_HEADER_HPP
#define VUE32_HEADER_HPP

// -------------------------------------------------------------------
// Definitions
// -------------------------------------------------------------------
#define WIFILED 12 // GPIO12 - WiFi LED
#define MQTTLED 13 // GPIO13 - MQTT LED

// -------------------------------------------------------------------
// JSON capacity (ArduinoJson helper)
// See: https://arduinojson.org/v6/assistant/
// Documentation: https://arduinojson.org/v6/api/json/deserializejson/
// -------------------------------------------------------------------
static const size_t capacitySettings = 1536;

// -------------------------------------------------------------------
// Firmware version provided by the build environment (platformio.ini)
// -------------------------------------------------------------------
#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)
extern String device_fw_version;

// -------------------------------------------------------------------
// Hardware version and manufacturer
// -------------------------------------------------------------------
#define device_hw_version "ADMINVUE32 v1 00000000" // Hardware version
#define device_manufacturer "IOTHOST"              // Manufacturer

// -------------------------------------------------------------------
// Device configuration area (declarations)
// -------------------------------------------------------------------
extern bool device_config_file;       // Flag for configuration file
extern char device_config_serial[30]; // Unique serial number for config file
extern char device_id[30];            // Device ID
extern int device_restart;            // Restart counter
extern char device_old_user[15];      // Web server username
extern char device_old_password[15];  // Web server password

// -------------------------------------------------------------------
// WiFi client configuration area (declarations)
// -------------------------------------------------------------------
extern bool wifi_ip_static;         // Use static IP (DHCP disabled)
extern char wifi_ssid[30];          // WiFi SSID
extern char wifi_password[30];      // WiFi password
extern char wifi_ipv4[15];          // Static IPv4 address
extern char wifi_gateway[15];       // IPv4 gateway
extern char wifi_subnet[15];        // IPv4 subnet
extern char wifi_dns_primary[15];   // Primary DNS IPv4
extern char wifi_dns_secondary[15]; // Secondary DNS IPv4

// -------------------------------------------------------------------
// WiFi access-point (AP) configuration area (declarations)
// -------------------------------------------------------------------
extern bool ap_mode;         // AP mode enabled
extern char ap_ssid[31];     // AP SSID
extern char ap_password[63]; // AP password
extern int ap_chanel;        // AP channel
extern int ap_visibility;    // AP visibility (0 = visible, 1 = hidden)
extern int ap_connect;       // Max number of AP connections (ESP32 max ~8)

// -------------------------------------------------------------------
// MQTT configuration area (declarations)
// -------------------------------------------------------------------
extern bool mqtt_cloud_enable; // Enable MQTT
extern char mqtt_cloud_id[30]; // MQTT client ID
extern char mqtt_user[30];     // MQTT username
extern char mqtt_password[39]; // MQTT password
extern char mqtt_server[39];   // MQTT server
extern int mqtt_port;          // MQTT server port
extern bool mqtt_retain;       // Retain flag
extern int mqtt_qos;           // QoS level
extern bool mqtt_time_send;    // Enable periodic data send
extern int mqtt_time_interval; // MQTT send interval (seconds)
extern bool mqtt_status_send;  // Enable status publishing

// -------------------------------------------------------------------
// Firmware update (API / REST) area
// -------------------------------------------------------------------
extern size_t content_len;
#define U_PART U_SPIFFS

// -------------------------------------------------------------------
// EEPROM addresses for restart counter
// -------------------------------------------------------------------
#define Start_Address 0
#define Restart_Address (Start_Address + sizeof(int))

#endif // VUE32_HEADER_HPP
