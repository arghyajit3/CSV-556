//////////// LIBRARIES ////////////
#include <IRremote.hpp>

//////////// VARIABLES ////////////

// Pins
#define IR 2 // Later to 9
#define SWITCH 3 // Later to 8
#define RELAY1 9 // Later to 2
#define RELAY2 8 // Later to 3
#define RELAY3 4
#define RELAY4 5

// States
bool relayState = false;
int lastSwitchState = HIGH;

//////////// SETUP ////////////
void setup() {
  // Serial Bandwidth Settings
  Serial.begin(9600);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);

  // Pins defined
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  
  // All relays set to low for experimental / pre development purpose
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);
}

//////////// MAIN CODE ////////////
void loop() {
  int switchState = digitalRead(SWITCH);

  // Toggle relay on switch toggle
  if (switchState != lastSwitchState) {
    delay(50); // to prevent mircoscopic debounces
    switchState = digitalRead(SWITCH); // checks switch state again to confirm that state is different
    if (switchState != lastSwitchState) {
      relayState = !relayState;
      digitalWrite(RELAY1, relayState ? HIGH : LOW);
      Serial.println(relayState ? "Relay ON" : "Relay OFF"); // For experimental / pre development purpose
      lastSwitchState = switchState;
    }
  }

  // IR remote to toggle relay
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    
    // Ignores repeat signals and invalid codes
    if (code == 0x0 || code == 0xFFFFFFFF) {
      IrReceiver.resume();
      return;
    }

    Serial.println(code, HEX); // For experimental / pre development purpose

    switch (code) {
      case 0x6E91F300: // Off button for atomberg fans (6E91F300)
        relayState = !relayState;
        digitalWrite(RELAY1, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Relay ON" : "Relay OFF"); // For experimental / pre development purpose
        break;
    }

    // Continuing the detection of IR signals after last signal
    IrReceiver.resume();
  }
}
