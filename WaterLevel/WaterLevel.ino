#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "connection.h"

#define RELAY_PIN D4  // Define the pin where the relay is connected

FirebaseData firebaseData;

unsigned long previousMillis = 0;
const long interval = 100;  // Update interval in milliseconds
int WaterLevel = 100;       // Default water level
int previousWaterLevel = -1;

void setup() {
  Serial.begin(9600);

  connectToWiFi();
  connectToFirebase();

  pinMode(RELAY_PIN, OUTPUT);  // Set the relay pin as output
  Serial.println("Firebase setup complete");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Process the received data from Serial
    while (Serial.available() > 0) {


      String data = Serial.readStringUntil('\n');

      // Process the received data
      if (data.startsWith("SwitchesOn:")) {
        int tot = data.substring(11).toInt();  // Extract the value after the prefix



        // Update water level based on the received value
        if (tot == 1) {
          WaterLevel = 75;
        } else if (tot == 2) {
          WaterLevel = 50;
        } else if (tot == 3) {
          WaterLevel = 20;
        } else if (tot == 4) {
          WaterLevel = 0;
        } else {
          WaterLevel = 100;
        }

        if (WaterLevel != previousWaterLevel) {
          if (Firebase.set(firebaseData, "/WaterLevelPercentage", WaterLevel)) {
            Serial.println("Firebase data updated successfully.");
          }
          previousWaterLevel = WaterLevel;
        }
        
      }
    }
  }
}



        
