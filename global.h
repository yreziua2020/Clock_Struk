#ifndef GLOBAL_H
#define GLOBAL_H

//extern String h;


ESP8266WebServer server(80);							// Веб сервер
boolean firstStart = true;								// первый старт = true, NTP получаем время
int AdminTimeOutCounter = 0;							// Counter for Disabling the AdminMode
WiFiUDP UDPNTPClient;											// NTP Client
volatile unsigned long UnixTimestamp = 0;	// GLOBALTIME  ( Will be set by NTP)
//int cNTP_Update = 0;											// Counter for Updating the time via NTP
//Ticker tkSecond;												  // Second - Timer for Updating Datetime Structure
const char* ntpServerName = "ntp.time.in.ua";
long timeZone =2;   
long absoluteActualTime;




//*************************************************************************************************************************************************************************************************


#endif