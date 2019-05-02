/*
 *  F12018_DASHBOARD is licensed under the GNU General Public License v3.0
 *      
 *  2019-05-02
 *  @Walter Pisani
 *  walpis@gmail.com
 *  
 *  Github URL: https://github.com/drospy/F12018_DASHBOARD
 *  Watch video on Youtube https://www.youtube.com/watch?v=uoGu7ikt2NM
 *  Follow me on Facebook @Psimula
 *  
 *  ESP32 + Nextion display
 *  F12018 codemaster
 *  Dashboard works only in Time Trial Mode
 *      
 *  This Example is a Demo.
 *  Change SSID and PASSWORD for WiFi connection
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include "F12018UDP.h"

boolean connected = false;

WiFiUDP udp;
WiFiClient client;
F12018UDP psdata;

const char * networkName = "SSID";
const char * networkPswd = "PASSWORD";

uint8_t ver;
int8_t gear=0;
uint16_t vspeed=0;
uint8_t nlap=0;

void setup() {
  Serial.begin(9600);
  // WiFi Connect
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  
  /* Receive data via Udp */
  int packetSize = udp.parsePacket();
  if (packetSize) {
    byte packetBuffer[packetSize]; 
    udp.read(packetBuffer,packetSize);
          f12018(packetBuffer);
  }
}

void f12018(byte *packetBuffer) { 

   psdata.aggiornaDati(packetBuffer);
   ver= *(uint8_t *)&packetBuffer[3];

   if (ver == 6) {     // Car Telemetry - Frequency: Menu Setting
      vspeed = psdata.getVelocita();
      gear = psdata.getMarce();
    
    }
   if (ver == 2) {     // Lap Data - Frequency: Menu Setting
      nlap = psdata.getNlap();
    }
 
   page_F12018();      
}

void page_F12018() {
    
    String command="";
    if (ver == 6) {     // Car Telemetry - Frequency: Menu Setting
      // Gear
      switch(gear)
        {
          case -1 : command="m.txt=\"R\"";break;
          case 0 : command="m.txt=\"N\"";break;
          case 1 : command="m.txt=\"1\"";break;
          case 2 : command="m.txt=\"2\"";break;
          case 3 : command="m.txt=\"3\"";break;
          case 4 : command="m.txt=\"4\"";break;
          case 5 : command="m.txt=\"5\"";break;
          case 6 : command="m.txt=\"6\"";break;
          case 7 : command="m.txt=\"7\"";break;
          case 8 : command="m.txt=\"8\"";break;
        }
      inviaComando(command);
      // Speed
      command = "v.txt=\""+String(vspeed)+"\""; 
      inviaComando(command);
    }
    
    if (ver == 2) {     // Lap Data - Frequency: Menu Setting
      // Lap  
      command="l.txt=\""+String(nlap)+"\"";
      inviaComando(command);
    }
}

void inviaComando(String c){
    Serial.print(c);
    Serial.write(0xff);   
    Serial.write(0xff);   
    Serial.write(0xff);
}

void connectToWiFi(const char * ssid, const char * pwd){
  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  //Initiate connection
  WiFi.begin(ssid, pwd);
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          udp.begin(20777);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
