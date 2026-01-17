#include <WiFi.h>
#include "time.h"

const char* ssid = "Caltech Visitor";
const char* password = NULL;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -28800;      // PST is UTC-8
const int daylightOffset_sec = 3600;    // DST +1 hour

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Configure NTP
  Serial.println("\nConfiguring NTP...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // Wait for time sync
  Serial.println("Waiting for NTP sync...");
  struct tm timeinfo;
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 20) {
    Serial.print(".");
    delay(1000);
    attempts++;
  }
  
  if (attempts >= 20) {
    Serial.println("\nERROR: NTP sync failed after 20 seconds");
    Serial.println("NTP port (123 UDP) might be blocked");
  } else {
    Serial.println("\nNTP sync successful!");
    printTime();
  }
}

void printTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("ERROR: Cannot get time");
    return;
  }
  
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
  time_t now;
  time(&now);
  Serial.print("Unix timestamp: ");
  Serial.println(now);
}

void loop() {
  delay(5000);
  printTime();
}
