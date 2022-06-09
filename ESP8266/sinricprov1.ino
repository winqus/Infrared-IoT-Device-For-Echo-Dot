/*
 * By WINQUS
 * Version 1.0 for SINRIC PRO - 2021-09-30
 * Using ESP8266 GENERIC
 */ 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPUpdateServer.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "conf.h"

const char* host = MDNSHOST;
const char* wifihostname = HOSTNAME;
const char* ssid = STASSID;
const char* password = STAPSK;
const char* default_login = DEFAULT_LOGIN;
const char* default_pass = DEFAULT_PASS;

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

#define IR_LED 3 //IR LED pin
IRsend irsend(IR_LED);

void handleIndex(){
  httpServer.send(200, "text/html", INDEX_HTML);
}
void setupWifiServices(){
  WiFi.mode(WIFI_STA);
  WiFi.hostname(wifihostname);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, WiFiAPs_JSON);
  if(!error)
  {
    const int c = doc["count"];
    for(int i = 0; i < c; i++)
    {
      const char* _ssid = doc["items"][i]["ssid"];
      const char* _key = doc["items"][i]["key"];
      wifiMulti.addAP(_ssid, _key);
    }
  }
  while (wifiMulti.run() != WL_CONNECTED) delay(500);
  
  MDNS.begin(host);  
  httpUpdater.setup(&httpServer, "/dankupdate", default_login, default_pass);


  httpServer.on("/", handleIndex);
  httpServer.begin();

  MDNS.addService("http", "tcp", 80);
}
bool onPowerState(const String &deviceId, bool &state) {
  irsend.sendNEC(state ? YAMAHA_ON : YAMAHA_OFF);
  return true; // request handled properly
}
void setupSinricPro() {
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   // add device to SinricPro
  mySwitch.onPowerState(onPowerState);   // set callback function to device
  SinricPro.begin(APP_KEY, APP_SECRET);
}
void setup(void) {
  setupWifiServices();
  setupSinricPro();
  irsend.begin();
}

void loop(void) {
  if (wifiMulti.run() != WL_CONNECTED)
  {
    delay(500);
    return;
  }
  httpServer.handleClient();
  MDNS.update();
  SinricPro.handle();
}
