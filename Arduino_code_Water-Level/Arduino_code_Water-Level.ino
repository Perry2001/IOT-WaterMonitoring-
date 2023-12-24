const int buttonPin = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;

int prevReading = -1;

int buttonState = 0, buttonState2 = 0, buttonState3= 0, buttonState4 = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  int tot = buttonState + buttonState2 + buttonState3 + buttonState4;

    Serial.print("SwitchesOn:");
    Serial.println(tot);
    prevReading = tot; 


  

  delay(100);  // Adjust the delay as needed for your application
}

