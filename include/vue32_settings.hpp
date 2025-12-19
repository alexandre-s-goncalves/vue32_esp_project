#include <SPIFFS.h>

boolean settingsRead();
void settingsReset();
boolean settingsSave();
// -------------------------------------------------------------------
// Read settings.json
// -------------------------------------------------------------------
boolean settingsRead() {

  DynamicJsonDocument jsonSettings(capacitySettings);

  File file = SPIFFS.open("/settings.json", "r");

  if (deserializeJson(jsonSettings, file)) {
    // Take factory default values
    settingsReset();
    DeserializationError error = deserializeJson(jsonSettings, file);
    log("[ ERROR ] Failed to read configuration, using default values");
    if (error) {
      log(String("[ ERROR ] ") + String(error.c_str()));
    }
    return false;
  } else {
    // -------------------------------------------------------------------
    // Device settings.json
    // -------------------------------------------------------------------
    device_config_file = jsonSettings["device_config_file"];
    strlcpy(device_config_serial, jsonSettings["device_config_serial"],
            sizeof(device_config_serial));
    strlcpy(device_id, jsonSettings["device_id"], sizeof(device_id));
    strlcpy(device_old_user, jsonSettings["device_old_user"],
            sizeof(device_old_user));
    strlcpy(device_old_password, jsonSettings["device_old_password"],
            sizeof(device_old_password));
    // -------------------------------------------------------------------
    // WiFi Client settings.json
    // -------------------------------------------------------------------
    wifi_ip_static = jsonSettings["wifi_ip_static"];
    strlcpy(wifi_ssid, jsonSettings["wifi_ssid"], sizeof(wifi_ssid));
    strlcpy(wifi_password, jsonSettings["wifi_password"],
            sizeof(wifi_password));
    strlcpy(wifi_ipv4, jsonSettings["wifi_ipv4"], sizeof(wifi_ipv4));
    strlcpy(wifi_subnet, jsonSettings["wifi_subnet"], sizeof(wifi_subnet));
    strlcpy(wifi_gateway, jsonSettings["wifi_gateway"], sizeof(wifi_gateway));
    strlcpy(wifi_dns_primary, jsonSettings["wifi_dns_primary"],
            sizeof(wifi_dns_primary));
    strlcpy(wifi_dns_secondary, jsonSettings["wifi_dns_secondary"],
            sizeof(wifi_dns_secondary));
    // -------------------------------------------------------------------
    // WiFi AP settings.json
    // -------------------------------------------------------------------
    ap_mode = jsonSettings["ap_mode"];
    strlcpy(ap_ssid, jsonSettings["ap_ssid"], sizeof(ap_ssid));
    strlcpy(ap_password, jsonSettings["ap_password"], sizeof(ap_password));
    ap_visibility = jsonSettings["ap_visibility"];
    ap_chanel = jsonSettings["ap_chanel"];
    ap_connect = jsonSettings["ap_connect"];
    // -------------------------------------------------------------------
    // Cloud settings.json
    // -------------------------------------------------------------------
    mqtt_cloud_enable = jsonSettings["mqtt_cloud_enable"];
    strlcpy(mqtt_user, jsonSettings["mqtt_user"], sizeof(mqtt_user));
    strlcpy(mqtt_password, jsonSettings["mqtt_password"],
            sizeof(mqtt_password));
    strlcpy(mqtt_server, jsonSettings["mqtt_server"], sizeof(mqtt_server));
    strlcpy(mqtt_cloud_id, jsonSettings["mqtt_cloud_id"],
            sizeof(mqtt_cloud_id));
    mqtt_port = jsonSettings["mqtt_port"];
    mqtt_retain = jsonSettings["mqtt_retain"];
    mqtt_qos = jsonSettings["mqtt_qos"];
    mqtt_time_send = jsonSettings["mqtt_time_send"];
    mqtt_time_interval = jsonSettings["mqtt_time_interval"];
    mqtt_status_send = jsonSettings["mqtt_status_send"];

    file.close();
    log("[ INFO ] Configuration read successfully");
    return true;
  }
}
// -------------------------------------------------------------------
// Factory default values for settings.json
// -------------------------------------------------------------------
void settingsReset() {
  // -------------------------------------------------------------------
  // Device settings.json
  // -------------------------------------------------------------------
  device_config_file = true;
  strlcpy(device_config_serial, deviceID().c_str(),
          sizeof(device_config_serial));
  strlcpy(device_id, "adminvue32", sizeof(device_id));
  strlcpy(device_old_user, "admin", sizeof(device_old_user));
  strlcpy(device_old_password, "admin", sizeof(device_old_password));
  // -------------------------------------------------------------------
  // WiFi Client settings.json
  // -------------------------------------------------------------------
  wifi_ip_static = true;
  strlcpy(wifi_ssid, "iotmaster", sizeof(wifi_ssid));
  strlcpy(wifi_password, "iotmaster84", sizeof(wifi_password));
  strlcpy(wifi_ipv4, "192.168.20.150", sizeof(wifi_ipv4));
  strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
  strlcpy(wifi_gateway, "192.168.20.1", sizeof(wifi_gateway));
  strlcpy(wifi_dns_primary, "8.8.8.8", sizeof(wifi_dns_primary));
  strlcpy(wifi_dns_secondary, "8.8.4.4", sizeof(wifi_dns_secondary));
  // -------------------------------------------------------------------
  // WiFi AP settings.json
  // -------------------------------------------------------------------
  ap_mode = false;
  strlcpy(ap_ssid, deviceID().c_str(), sizeof(ap_ssid));
  strlcpy(ap_password, "adminVUE32", sizeof(ap_password));
  ap_visibility = false;
  ap_chanel = 9;
  ap_connect = 4;
  // -------------------------------------------------------------------
  // Cloud settings.json
  // -------------------------------------------------------------------
  mqtt_cloud_enable = false;
  strlcpy(mqtt_user, "cuba_iot", sizeof(mqtt_user));
  strlcpy(mqtt_password, "cuba_iot", sizeof(mqtt_password));
  strlcpy(mqtt_server, "192.168.10.1", sizeof(mqtt_server));
  strlcpy(mqtt_cloud_id, deviceID().c_str(), sizeof(mqtt_cloud_id));
  mqtt_port = 1883;
  mqtt_retain = false;
  mqtt_qos = 0;
  mqtt_time_send = true;
  mqtt_time_interval = 30000;
  mqtt_status_send = true;
  log("[ INFO ] All defaults have been reset");
}
// -------------------------------------------------------------------
// Save settings.json
// -------------------------------------------------------------------
boolean settingsSave() {

  DynamicJsonDocument jsonSettings(capacitySettings);

  File file = SPIFFS.open("/settings.json", "w+");

  if (file) {
    // -------------------------------------------------------------------
    // Device settings.json
    // -------------------------------------------------------------------
    jsonSettings["device_config_file"] = device_config_file;
    jsonSettings["device_config_serial"] = device_config_serial;
    jsonSettings["device_id"] = device_id;
    jsonSettings["device_old_user"] = device_old_user;
    jsonSettings["device_old_password"] = device_old_password;
    // -------------------------------------------------------------------
    // WiFi Client settings.json
    // -------------------------------------------------------------------
    jsonSettings["wifi_ip_static"] = wifi_ip_static;
    jsonSettings["wifi_ssid"] = wifi_ssid;
    jsonSettings["wifi_password"] = wifi_password;
    jsonSettings["wifi_ipv4"] = wifi_ipv4;
    jsonSettings["wifi_subnet"] = wifi_subnet;
    jsonSettings["wifi_gateway"] = wifi_gateway;
    jsonSettings["wifi_dns_primary"] = wifi_dns_primary;
    jsonSettings["wifi_dns_secondary"] = wifi_dns_secondary;
    // -------------------------------------------------------------------
    // WiFi AP settings.json
    // -------------------------------------------------------------------
    jsonSettings["ap_mode"] = ap_mode;
    jsonSettings["ap_ssid"] = ap_ssid;
    jsonSettings["ap_password"] = ap_password;
    jsonSettings["ap_visibility"] = ap_visibility;
    jsonSettings["ap_chanel"] = ap_chanel;
    jsonSettings["ap_connect"] = ap_connect;
    // -------------------------------------------------------------------
    // Cloud settings.json
    // -------------------------------------------------------------------
    jsonSettings["mqtt_cloud_enable"] = mqtt_cloud_enable;
    jsonSettings["mqtt_user"] = mqtt_user;
    jsonSettings["mqtt_password"] = mqtt_password;
    jsonSettings["mqtt_server"] = mqtt_server;
    jsonSettings["mqtt_cloud_id"] = mqtt_cloud_id;
    jsonSettings["mqtt_port"] = mqtt_port;
    jsonSettings["mqtt_retain"] = mqtt_retain;
    jsonSettings["mqtt_qos"] = mqtt_qos;
    jsonSettings["mqtt_time_send"] = mqtt_time_send;
    jsonSettings["mqtt_time_interval"] = mqtt_time_interval;
    jsonSettings["mqtt_status_send"] = mqtt_status_send;

    serializeJsonPretty(jsonSettings, file);
    file.close();
    log("[ INFO ] Configuration saved successfully");
    serializeJsonPretty(jsonSettings, Serial);
    return true;
  } else {
    log("[ ERROR ] Failed to save configuration");
    return false;
  }
}
