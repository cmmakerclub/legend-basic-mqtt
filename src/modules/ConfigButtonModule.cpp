#include "ConfigButtonModule.h" 

void ConfigButtonModule::isLongPressed() {
  if (digitalRead(0) == LOW) {
    Serial.println("low.."); 
    unsigned timer = millis();
    while(digitalRead(0) == LOW) {
      delay(10); 
    }
    if (millis() - timer > 5000L) {
      SPIFFS.remove("/enabled");
      digitalWrite(0, LOW);
      delay(2000);
      ESP.restart(); 
    }
  }
}

void ConfigButtonModule::configLoop() {
  if (digitalRead(0) == LOW) {
    Serial.println("low..");
    while(digitalRead(0) == LOW) {
      delay(10); 
    }
    File f = SPIFFS.open("/enabled", "a+");
    f.close();
    digitalWrite(0, LOW);
    delay(100);
    ESP.restart();
  }
}

void ConfigButtonModule::configSetup() {
    pinMode(0,INPUT_PULLUP);
}

void ConfigButtonModule::config(CMMC_System *os, AsyncWebServer *server)
{
}


void ConfigButtonModule::setup()
{
  pinMode(0,INPUT_PULLUP); 
}

void ConfigButtonModule::loop() {
  isLongPressed();
}

