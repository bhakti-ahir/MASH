 #include <WiFi.h>

void setup() {
  //Setup Serial Monitor
  Serial.begin(115200);

  //Put ESP32 into station mode
  WiFi.mode(WIFI_AP_STA);

  // Print MAC Adress naar Serial monitor
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
   Serial.println(WiFi.macAddress());
}

