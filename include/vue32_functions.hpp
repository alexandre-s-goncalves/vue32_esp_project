#pragma once

#include "vue32_LedBlink.hpp"

// -------------------------------------------------------------------
// Generate a log on the Serial port
// -------------------------------------------------------------------
void log(String s) { Serial.println(s); }
// -------------------------------------------------------------------
// Define the platform
// -------------------------------------------------------------------
String platform()
{
// Get the hardware platform
#ifdef ARDUINO_ESP32_DEV
  return "ESP32";
#endif
}
// -------------------------------------------------------------------
// From HEX to String
// -------------------------------------------------------------------
String hexStr(const unsigned long &h, const byte &l = 8)
{
  String s;
  s = String(h, HEX);
  s.toUpperCase();
  s = ("00000000" + s).substring(s.length() + 8 - l);
  return s;
}
// -------------------------------------------------------------------
// Create a unique ID from the MAC address
// -------------------------------------------------------------------
String idUnique()
{
  // Returns the last 4 bytes of the MAC (rotated)
  char idunique[15];
  uint64_t chipid = ESP.getEfuseMac();
  uint16_t chip = (uint16_t)(chipid >> 32);
  snprintf(idunique, 15, "%04X", chip);
  return idunique;
}
// -------------------------------------------------------------------
// Unique device serial number
// -------------------------------------------------------------------
String deviceID()
{
  return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
// -------------------------------------------------------------------
// Configure output pins for WIFI - MQTT
// -------------------------------------------------------------------
void settingPins()
{
  pinMode(WIFILED, OUTPUT);
  pinMode(MQTTLED, OUTPUT);
  setOffSingle(WIFILED);
  setOffSingle(MQTTLED);
}
// -------------------------------------------------------------------
// Convert a char string to an IP
// -------------------------------------------------------------------
uint8_t ip[4]; // Temporary buffer for converting string to IP
IPAddress CharToIP(const char *str)
{
  sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
  return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}
// -------------------------------------------------------------------
// Return IPAddress as "n.n.n.n" string
// -------------------------------------------------------------------
String ipStr(const IPAddress &ip)
{
  String sFn = "";
  for (byte bFn = 0; bFn < 3; bFn++)
  {
    sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
  }
  sFn += String(((ip >> 8 * 3)) & 0xFF);
  return sFn;
}
