
static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
#define LEAP_YEAR(Y) ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte wday;
};

strDateTime DateTime;
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];

//*************************************************************************************************************************************************************************************************
//*************************************************************************************************************************************************************************************************
bool getNTPtime()
{
    unsigned long _unixTime = 0;
  
    if (WiFi.status() == WL_CONNECTED)
    {
       UDPNTPClient.begin(2390);  // Port for NTP receive
       IPAddress timeServerIP;
      if( WiFi.hostByName(ntpServerName, timeServerIP)) {Serial.print("DNS в ip получение ip выполнено "); } else  {Serial.print("DNS в ip не получен ");return false; }
      // WiFi.hostByName(config.ntpServerName.c_str(), timeServerIP);
       memset(packetBuffer, 0, NTP_PACKET_SIZE);
       packetBuffer[0] = 0b11100011;   // LI, Version, Mode
       packetBuffer[1] = 0;     // Stratum, or type of clock
       packetBuffer[2] = 6;     // Polling Interval
       packetBuffer[3] = 0xEC;  // Peer Clock Precision
       packetBuffer[12]  = 49;
       packetBuffer[13]  = 0x4E;
       packetBuffer[14]  = 49;
       packetBuffer[15]  = 52;
       UDPNTPClient.beginPacket(timeServerIP, 123);
       UDPNTPClient.write(packetBuffer, NTP_PACKET_SIZE);
       UDPNTPClient.endPacket();
       delay(100);

      int cb = UDPNTPClient.parsePacket();
      if (cb == 0) {  Serial.println("No NTP packet yet");  }
      else
       {          
          Serial.print("NTP packet received, length=");      Serial.println(cb);
          UDPNTPClient.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
          unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
          unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
          unsigned long secsSince1900 = highWord << 16 | lowWord;
          const unsigned long seventyYears = 2208988800UL;
          _unixTime = secsSince1900 - seventyYears;
       }
    }  /*if (WiFi.status*/  
    else {    Serial.println("Internet yet not connected");    delay(500);  }
    yield();
    if (_unixTime > 0) UnixTimestamp = _unixTime; // store universally available time stamp
  return true;
}

//*************************************************************************************************************************************************************************************************
//*************************************************************************************************************************************************************************************************
//Передаем структуру и вернет структуру  структуру
strDateTime ConvertUnixTimeStamp( unsigned long _tempTimeStamp) {
  strDateTime _DateTime_temp; //на базе структуры strDateTime создаем обект _DateTime_temp
  uint8_t year, month, monthLength; 
  uint32_t time;
  unsigned long days;

  time = (uint32_t)_tempTimeStamp;
                _DateTime_temp.second = time % 60;
  time /= 60;   _DateTime_temp.minute = time % 60;   //Высчитываем  минут
  time /= 60;   _DateTime_temp.hour = time % 24;     //считаем часы
  time /= 24;   _DateTime_temp.wday = ((time + 4) % 7) + 1;  // считаем дни + 1

  year = 0;  days = 0;
  
  while ((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {    year++;  } //считаем год
  _DateTime_temp.year = year; // year is offset from 1970//53
  
  //------------------------------считаем наверное число-----------
  days -= LEAP_YEAR(year) ? 366 : 365;
  time  -= days; // теперь дни в этом году начинаются с 0
  //--------------------------------------------------------------------
  days = 0;  month = 0;  monthLength = 0;
  //-------------------------------считаем месяц----------
    for (month = 0; month < 12; month++) {
    if (month == 1) { // february
          if (LEAP_YEAR(year)) { monthLength = 29;
      } else {               monthLength = 28;    }
    } 
    else 
    { monthLength = monthDays[month]; }

    if (time >= monthLength) {  time -= monthLength;  } 
    else {      break; }
  }
  //-----------------------------------------------------
  _DateTime_temp.month = month + 1;  // jan is month 1
  _DateTime_temp.year += 1970;
  _DateTime_temp.day = time + 1;     // day of month
//Serial.print("_DateTime_temp.year="); Serial.println(_DateTime_temp.year);
  return _DateTime_temp ;
}
//*************************************************************************************************************************************************************************************************
//**************************************************а также выясняем надо ли переходить на летнее время *******************************
boolean summerTime(unsigned long _timeStamp ) {
  strDateTime  _DateTimetemp = ConvertUnixTimeStamp(_timeStamp);  //Конвертируем данные полученые из интернета в другой функции и уже с ними работаем
   //printTime("Innerhalb ", _tempDateTime);

  if (_DateTimetemp.month < 3 || _DateTimetemp.month > 10) return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
  if (_DateTimetemp.month > 3 && _DateTimetemp.month < 10) return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
  if (_DateTimetemp.month == 3 && (_DateTimetemp.hour + 24 * _DateTimetemp.day) >= (3 +  24 * (31 - (5 * _DateTimetemp.year / 4 + 4) % 7)) || _DateTimetemp.month == 10 && (_DateTimetemp.hour + 24 * _DateTimetemp.day) < (3 +  24 * (31 - (5 * _DateTimetemp.year / 4 + 1) % 7)))
    return true;
  else
    return false;
}
//*************************************************************************************************************************************************************************************************
//*************************************************************************************************************************************************************************************************
unsigned long adjustTimeZone(unsigned long _timeStamp, int _timeZone, bool _isDayLightSavingSaving) {   //думаю определяет пеереходить ли на етнее времяbool _isDayLightSavingSaving
  //strDateTime _tempDateTime;
  Serial.print("_timeStamp="); Serial.println(_timeStamp);
  _timeStamp += (_timeZone *  3600); // adjust timezone
  Serial.print("_timeStamp2="); Serial.println(_timeStamp);
  // printTime("Innerhalb adjustTimeZone ", ConvertUnixTimeStamp(_timeStamp));
   if (_isDayLightSavingSaving && summerTime(_timeStamp)) _timeStamp += 3600; //  летнее время Sommerzeit beachten

  //  Serial.print("_timeStamp3="); Serial.println(_timeStamp);
  return _timeStamp;
}
//*************************************************************************************************************************************************************************************************
void ISRsecondTick()
{

  UnixTimestamp++;

  absoluteActualTime  = UnixTimestamp +timeZone *  3600; 
  DateTime = ConvertUnixTimeStamp(absoluteActualTime);  //  convert to DateTime format
  Serial.print(DateTime.hour);Serial.print(":"); Serial.print(DateTime.minute);Serial.print(":");Serial.print(DateTime.second);
  Serial.print(" "); Serial.print(DateTime.day);Serial.print("/"); Serial.print(DateTime.month);Serial.print("  "); Serial.println(DateTime.year);
  
}
//*************************************************************************************************************************************************************************************************











//*************************************************************************************************************************************************************************************************
void ISRsecondTick2()
{
  //strDateTime _tempDateTime;
  //AdminTimeOutCounter++;
  //cNTP_Update++;
  UnixTimestamp++;
  absoluteActualTime = adjustTimeZone(UnixTimestamp, timeZone   , 0); //коректируем время на основании значения на основании тайм зоны и надо  ли  переключать время на летние  //1 то не коректирует впремя по  тайм зоны 
  DateTime = ConvertUnixTimeStamp(absoluteActualTime);  //  convert to DateTime format

  //Serial.println("секуда прошла"); 

  //actualTime = 3600 * DateTime.hour + 60 * DateTime.minute + DateTime.second;
   
  
}
//*************************************************************************************************************************************************************************************************
