#ifndef CONF_H
#define CONF_H

#define APP_KEY           "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx-xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "xxxxxxxxxxxxxxxxxxxxxxxx"

#define STASSID   "xxxxxxxx" // Wifi network SSID
#define STAPSK    "xxxxxxxx" // Wifi network password

#define DEFAULT_LOGIN       "changename" //Default login name
#define DEFAULT_PASS        "changepasswd" //Default login password
#define MAX_LOGIN_ATTEMPTS 5

#define MDNSHOST "espdevice_update" //change to your device name  
#define HOSTNAME "espdevice" //change to your device name  

// IR REMOTE COMMANDS
#define YAMAHA_OFF  0x5EA17887
#define YAMAHA_ON   0x5EA1B847

//Networks to add (change ssid and key)
const char WiFiAPs_JSON[] = "{\"count\":2,\"items\":[{\"ssid\":\"xxxxx\",\"key\":\"xxxxxx\"},{\"ssid\":\"xxxxxxxx\",\"key\":\"xxxxxxxx\"}]}";

const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE HTML><html><head><meta name="viewport" content="width=device-width, initial-scale=1"></head><h1>INDEX</h1><p1>ESP8266 for controlling the YAMAHA AV with ALEXA through SINRIC PRO.</p1></html>
)=====";
#endif

/*
    Yamaha remote HEX codes:
    STANDBY       5EA17887 (to turn off)
    SYSTEM POWER  5EA1B847 (to turn on)
    CD            5EA1A857
    TUNER         5EA16897
    VOLUME UP     5EA158A7
    VOLUME DOWN   5EA1D827
*/
