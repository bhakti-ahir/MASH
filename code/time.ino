#include <WiFi.h>
#include "time.h"

const char* ssid = "Caltech Visitor";
const char* password = NULL;  // NULL for open networks

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -28800;      // PST is UTC-8
const int daylightOffset_sec = 3600;    // DST +1 hour

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("ERROR CODE: NTP_SYNC_FAILED");
    Serial.print("Error Details: Unable to retrieve time from NTP server | ");
    Serial.print("Epoch: ");
    time_t now;
    time(&now);
    Serial.print(now);
    Serial.print(" | WiFi Status: ");
    Serial.println(WiFi.status());
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for time...");
  delay(2000);
  
  printLocalTime();
}

void loop() {
  delay(1000);
  printLocalTime();
}
