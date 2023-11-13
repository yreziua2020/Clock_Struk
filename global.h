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
///-----------------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------------
const char* DB_host = "dev.ibc-composite.com";  //host_name
const int Port = 80;
const char* database_pass = "Kvw1scUvg97Y";  //пароль пользователя базы данных
//uint16_t f_eror_sql;                         //флаг ошибки sql

String postData = ""; //--> Variables sent for HTTP POST request data.
String payload = "";  //--> Variable for receiving response from HTTP POST.
int  vlaga_perem; //чтения значение флаги из базы
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///-----------------------------------------------------------------------------------------------



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
#endif