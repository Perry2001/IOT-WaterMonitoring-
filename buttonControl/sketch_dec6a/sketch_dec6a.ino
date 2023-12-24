#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "connection.h"

#define RELAY_PIN D3  // Define the pin where the relay is connected

FirebaseData firebaseData;


void setup() {
  Serial.begin(9600);

  connectToWiFi();
  connectToFirebase();


  pinMode(RELAY_PIN, OUTPUT);  // Set the relay pin as output
  // Set up the Firebase node listener
  Firebase.beginStream(firebaseData, "/PumpStatus");
  Serial.println("Listening to Firebase stream");

  // Register the callback function for the node
  Firebase.setStreamCallback(firebaseData, onDataChange);
  Serial.println("Callback registered");
  
}

void loop() {
}

void onDataChange(StreamData data) {
  Serial.println("Stream data changed.");
  if (data.dataType() == "int") {
    int value = data.intData();

    // Check the value and control the relay pin
    if (value == 1) {
      digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay
    } else if (value == 0) {
      digitalWrite(RELAY_PIN, LOW);  // Turn off the relay
    }
  }
}