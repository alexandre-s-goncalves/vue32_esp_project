/* Definitions for vue32_header variables
 * This source file provides the storage for extern declarations
 * in include/vue32_header.hpp
 */

#include "../include/vue32_header.hpp"

// Firmware version (from platformio build flag BUILD_TAG)
String device_fw_version = ESCAPEQUOTE(BUILD_TAG);

// Device configuration
bool device_config_file = false;
char device_config_serial[30] = "";
char device_id[30] = "";
int device_restart = 0;
char device_old_user[15] = "";
char device_old_password[15] = "";

// WIFI client
bool wifi_ip_static = false;
char wifi_ssid[30] = "";
char wifi_password[30] = "";
char wifi_ipv4[15] = "";
char wifi_gateway[15] = "";
char wifi_subnet[15] = "";
char wifi_dns_primary[15] = "";
char wifi_dns_secondary[15] = "";

// WIFI AP
bool ap_mode = false;
char ap_ssid[31] = "";
char ap_password[63] = "";
int ap_chanel = 1;
int ap_visibility = 0;
int ap_connect = 4;

// MQTT
bool mqtt_cloud_enable = false;
char mqtt_cloud_id[30] = "";
char mqtt_user[30] = "";
char mqtt_password[39] = "";
char mqtt_server[39] = "";
int mqtt_port = 1883;
bool mqtt_retain = false;
int mqtt_qos = 0;
bool mqtt_time_send = false;
int mqtt_time_interval = 60;
bool mqtt_status_send = false;

// Firmware update
size_t content_len = 0;
