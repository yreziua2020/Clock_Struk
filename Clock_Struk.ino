#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "Timer.h"
Timer _timer;

WiFiClient client;


#include "global.h"
#include "NTP_str.h"


extern "C" {
#include "user_interface.h"
}


void loop() {
_timer.update();

  // put your main code here, to run repeatedly:

}

void test_t(){
  h = String (DateTime.hour/10) + String (DateTime.hour%10);
  m = String (DateTime.minute/10) + String (DateTime.minute%10);
  y = String (DateTime.year);
     //Serial.print(h);Serial.print(":"); Serial.print(m);Serial.print("  "); Serial.println(y);
    // Serial.print(DateTime.hour);Serial.print(":"); Serial.print(DateTime.minute);Serial.print(":");Serial.print(DateTime.second);Serial.print("  "); Serial.println(DateTime.year);
}


