bool relayState = false;
int lastSwitchState = HIGH;
int lastButtonState = HIGH;

void setup() {
  pinMode(2, INPUT_PULLUP); // switch
  pinMode(3, INPUT_PULLUP); // button
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int switchState = digitalRead(2);
  int buttonState = digitalRead(3);

  // toggle on switch change
  if (switchState != lastSwitchState) {
    relayState = !relayState;
    digitalWrite(9, relayState ? HIGH : LOW);
    Serial.println(relayState ? "Relay ON" : "Relay OFF");
    lastSwitchState = switchState;
  }

  // toggle on button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    relayState = !relayState;
    digitalWrite(9, relayState ? HIGH : LOW);
    Serial.println(relayState ? "Relay ON" : "Relay OFF");
  }
  lastButtonState = buttonState;

  delay(50);
}