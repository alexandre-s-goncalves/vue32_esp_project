
#pragma once

#include "vue32_functions.hpp"
#include "vue32_header.hpp"
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <WiFi.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress ap_IPv4(192, 168, 4, 1);
IPAddress ap_subnet(255, 255, 255, 0);

// WiFi.mode(WIFI_STA)      - station mode: the ESP32 connects to an access
// point WiFi.mode(WIFI_AP)       - access point mode: stations can connect to
// the ESP32 WiFi.mode(WIFI_AP_STA)   - access point and a station connected to
// another access point

int wifi_mode = WIFI_STA;
bool wifi_change = false;

unsigned long previousMillisWIFI = 0;
unsigned long previousMillisAP = 0;
unsigned long intervalWIFI = 30000; // 30 seconds

// http://adminesp32.local
const char *esp_hostname = device_id;

// -------------------------------------------------------------------
// Start WiFi AP Mode
// -------------------------------------------------------------------
void startAP()
{
  log("[ INFO ] Starting AP Mode");
  WiFi.disconnect(true);
  WiFi.softAPConfig(ap_IPv4, ap_IPv4, ap_subnet);
  WiFi.hostname(esp_hostname);
  WiFi.softAP(ap_ssid, ap_password, ap_chanel, ap_visibility, ap_connect);
  log("[ INFO ] WiFi AP " + String(ap_ssid) + " - IP " +
      ipStr(WiFi.softAPIP()));
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNSSERVER_PORT, "*", ap_IPv4);
  wifi_mode = WIFI_AP;
}
// -------------------------------------------------------------------
// Start WiFi Station Mode
// -------------------------------------------------------------------
void startClient()
{
  log("[ INFO ] Starting Station Mode");
  WiFi.mode(WIFI_STA);
  if (wifi_ip_static)
  {
    if (!WiFi.config(CharToIP(wifi_ipv4), CharToIP(wifi_gateway),
                     CharToIP(wifi_subnet), CharToIP(wifi_dns_primary),
                     CharToIP(wifi_dns_secondary)))
    {
      log("[ ERROR ] Failed to configure Station Mode");
    }
  }
  WiFi.hostname(esp_hostname);
  WiFi.begin(wifi_ssid, wifi_password);
  log("[ INFO ] Connecting to SSID " + String(wifi_ssid));
  byte b = 0;
  while (WiFi.status() != WL_CONNECTED && b < 60)
  {
    b++;
    log("[ WARNING ] Attempting WiFi connection...");
    vTaskDelay(500);
    blinkSingle(100, WIFILED);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    log("[ INFO ] WiFi connected (" + String(WiFi.RSSI()) + ") dBm IPv4 " +
        ipStr(WiFi.localIP()));
    blinkRandomSingle(10, 100, WIFILED);
    wifi_mode = WIFI_STA;
    wifi_change = true;
  }
  else
  {
    log("[ ERROR ] WiFi not connected");
    blinkRandomSingle(10, 100, WIFILED);
    wifi_change = true;
    startAP();
  }
}
// -------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------
void wifi_setup()
{
  WiFi.disconnect(true);
  // 1) If AP Mode is active
  if (ap_mode)
  {
    startAP();
    log("[ INFO ] WiFi in AP Mode");
  }
  else
  {
    // 2) Otherwise in Station Mode
    startClient();
    if (WiFi.status() == WL_CONNECTED)
    {
      log("[ INFO ] WiFi Station Mode");
    }
  }
  // Start hostname broadcast in STA or AP mode
  if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP)
  {
    if (MDNS.begin(esp_hostname))
    {
      MDNS.addService("http", "tcp", 80);
    }
  }
}
// -------------------------------------------------------------------
// Station Mode Loop
// -------------------------------------------------------------------
byte w = 0;
void wifiLoop()
{
  unsigned long currentMillis = millis();
  if (WiFi.status() != WL_CONNECTED &&
      (currentMillis - previousMillisWIFI >= intervalWIFI))
  {
    w++;
    blinkSingle(100, WIFILED);
    WiFi.disconnect(true);
    WiFi.reconnect();
    previousMillisWIFI = currentMillis;
    // 2 = 1 minute
    if (w == 2)
    {
      log("[ INFO ] Switching to AP Mode");
      wifi_change = true;
      w = 0;
      startAP();
    }
    else
    {
      log("[ WARNING ] SSID " + String(wifi_ssid) + " disconnected ");
    }
  }
  else
  {
    blinkSingleAsy(10, 500, WIFILED);
  }
}
// -------------------------------------------------------------------
// AP Mode Loop
// -------------------------------------------------------------------
byte a = 0;
void wifiAPLoop()
{
  blinkSingleAsy(5, 100, WIFILED);
  dnsServer.processNextRequest(); // Captive portal DNS
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillisAP >= intervalWIFI) && wifi_change)
  {
    a++;
    previousMillisAP = currentMillis;
    // 20 equals 10 minutes
    if (a == 20)
    {
      log("[ INFO ] Switching to Station Mode");
      wifi_change = false;
      a = 0;
      startClient();
    }
  }
}
