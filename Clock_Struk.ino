#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

#include "Timer.h"

Timer _timer;

#include "global.h"
#include "NTP_str.h"


extern "C" {
#include "user_interface.h"
}

String y;     // год
String mon;   // месяц
String wd;    // день недели
String d;     // дени
String h;     // часоы
String m;     // минуты
String s;     // секунды
//---------------------------------------------------------------------------------------------------------------------------
IPAddress ip(192, 168, 1, 99);
IPAddress gateway(192, 168, 1, 199);
IPAddress primaryDNS(192, 168, 1, 199);  // опционально
IPAddress subnet(255, 255, 255, 0);
IPAddress secondaryDNS(8, 8, 8, 8);  // опционально
const char* ssid = "home";
const char* password = "30011980";
int raz_podk;  //сколько раз пробуем подключиться до прпезапуска
//---------------------------------------------------------------------------------------------------------------------------
void loop() {
_timer.update();

  // put your main code here, to run repeatedly:

}

void test_t(){
  h = String (DateTime.hour/10) + String (DateTime.hour%10);
  m = String (DateTime.minute/10) + String (DateTime.minute%10);
  y = String (DateTime.year);
     Serial.print(h);Serial.print(":"); Serial.print(m);Serial.print("  "); Serial.println(y);
     Serial.print(DateTime.hour);Serial.print(":"); Serial.print(DateTime.minute);Serial.print("  "); Serial.println(DateTime.year);
}


