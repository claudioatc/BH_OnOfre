#include <JustWifi.h> //https://github.com/xoseperez/justwifi
#include <ESP8266mDNS.h>
#include <Timing.h> //https://github.com/scargill/Timing
#include <AsyncMqttClient.h> //https://github.com/marvinroger/async-mqtt-client
#include <ArduinoJson.h> ////Install from Arduino IDE Library Manager
#include <FS.h> 
#include <Ticker.h>
#include <ESPAsyncTCP.h> //https://github.com/me-no-dev/ESPAsyncTCP
#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncJson.h> //https://github.com/me-no-dev/ESPAsyncWebServer
//#define FORMAT
#define HARDWARE "bhonofre" 
#define MODEL "Easy-Light"
#define NODE_ID MODEL
#define FIRMWARE_VERSION 1.1
#define HOSTNAME String(HARDWARE)+"-"+String(NODE_ID)
#define CONFIG_FILENAME  "/config_"+String(HARDWARE)+".json"
#define CONFIG_BUFFER_SIZE 512
#define WIFI_SSID ""
#define WIFI_SECRET ""
//     ___ ___ ___ ___  _    
//    / __| _ \_ _/ _ \( )___
//   | (_ |  _/| | (_) |/(_-<
//    \___|_| |___\___/  /__/
//     
#define RELAY_ONE 4
#define RELAY_TWO 5 
#define SWITCH_ONE 12
#define SWITCH_TWO 13

//    ___ ___ ___ _____ _   _ ___ ___ ___ 
//   | __| __/ __|_   _| | | | _ \ __/ __|
//   | _|| _| (__  | | | |_| |   / _|\__ \
//   |_| |___\___| |_|  \___/|_|_\___|___/
// 
#define PRINT_TO_SERIAL_MONITOR false

//    __  __  ___ _____ _____ 
//   |  \/  |/ _ \_   _|_   _|
//   | |\/| | (_) || |   | |  
//   |_|  |_|\__\_\|_|   |_|  
//  
#define MQTT_BROKER_IP ""
#define MQTT_BROKER_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define PAYLOAD_ON "ON"
#define PAYLOAD_OFF "OFF"
#define PAYLOAD_PULSE_OFF_ON "PULSE_OFF"
#define PAYLOAD_PULSE_ON_OFF "PULSE_ON"


#define HOME_ASSISTANT_AUTO_DISCOVERY_PREFIX  "homeassistant"
//NODE
String hostname = HOSTNAME;
String nodeId = NODE_ID;

//MQTT
String mqttIpDns = MQTT_BROKER_IP;
String mqttUsername = MQTT_USERNAME;
String mqttPassword = MQTT_PASSWORD;



//WI-FI
String wifiSSID = WIFI_SSID;
String wifiSecret = WIFI_SECRET;

//CONTROL FLAGS
bool configNeedsUpdate = false;
bool restartMqtt = false;
bool shouldReboot = false;

//HOME ASSISTANT
bool homeAssistantAutoDiscovery = true;
String homeAssistantAutoDiscoveryPrefix = HOME_ASSISTANT_AUTO_DISCOVERY_PREFIX  ;

DynamicJsonBuffer jsonBuffer(CONFIG_BUFFER_SIZE);
JsonArray& getJsonArray(){
  return jsonBuffer.createArray();
  }
JsonArray& getJsonArray(File file){
  return jsonBuffer.parseArray(file);
  }

  JsonObject& getJsonObject(){
  return jsonBuffer.createObject();
  }
JsonObject& getJsonObject(File file){
  return jsonBuffer.parseObject(file);
  }
  JsonObject& getJsonObject(const char* data){
  return jsonBuffer.parseObject(data);
  }
