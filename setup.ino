void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);   WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  while (WiFi.status() != WL_CONNECTED) { delay(300);Serial.print("."); if(raz_podk++>250){ESP.reset(); }}  
  delay(500);  
  
  _timer.every(5000, test_t);
  _timer.every(1000, ISRsecondTick);


  if  (WiFi.status() == WL_CONNECTED) { getNTPtime();}
  // put your setup code here, to run once:
//_timer.every(1000, ISRsecondTick);

//Serial.println("Start3");
}