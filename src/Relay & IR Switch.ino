//////////// LIBRARIES ////////////
#include <IRremote.hpp>

//////////// VARIABLES ////////////

// Pins
#define IR 9
#define SWITCH 8
#define RELAY1 2
#define RELAY2 3
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

  // SWITCH //
  int switchState = digitalRead(SWITCH);

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

// RELAYS //
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    
    // Ignores repeat signals and invalid codes
    if (code == 0x0 || code == 0xFFFFFFFF) {
      IrReceiver.resume();
      return;
    }

    Serial.println(code, HEX); // For experimental / pre development purpose

    switch (code) {

      // RELAY 1
      case 0x7F80BA45:
      case 0xFE01BA45:
        relayState = !relayState;
        digitalWrite(RELAY1, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Relay1 ON" : "Relay1 OFF"); // For experimental / pre development purpose
        break;
      
      // RELAY 2
      case 0x7E81BA45:
      case 0xFD02BA45:
        relayState = !relayState;
        digitalWrite(RELAY2, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Relay2 ON" : "Relay2 OFF"); // For experimental / pre development purpose
        break;

      // RELAY 3
      case 0xAE51BA45:
      case 0xFC03BA45:
        relayState = !relayState;
        digitalWrite(RELAY3, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Relay3 ON" : "Relay3 OFF"); // For experimental / pre development purpose
        break;

      // RELAY 4
      case 0xB24DBA45:
      case 0xFB04BA45:
        relayState = !relayState;
        digitalWrite(RELAY4, relayState ? HIGH : LOW);
        Serial.println(relayState ? "Relay4 ON" : "Relay4 OFF"); // For experimental / pre development purpose
        break;
    }

    // Continuing the detection of IR signals after last signal
    IrReceiver.resume();
  }
}
