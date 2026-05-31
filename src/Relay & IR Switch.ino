//////////// LIBRARIES ////////////
#include <IRremote.hpp>

//////////// VARIABLES ////////////

/// Pins ///
#define IR 9

#define SWITCH1 6
#define SWITCH2 7
#define SWITCH3 8
#define SWITCH4 12

#define RELAY1 2
#define RELAY2 3
#define RELAY3 4
#define RELAY4 5

/// States ///
bool relay1State = false;
bool relay2State = false;
bool relay3State = false;
bool relay4State = false;

int lastSwitch1State = HIGH;
int lastSwitch2State = HIGH;
int lastSwitch3State = HIGH;
int lastSwitch4State = HIGH;

//////////// SETUP ////////////
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(SWITCH3, INPUT_PULLUP);
  pinMode(SWITCH4, INPUT_PULLUP);

  // All relays OFF at startup (active LOW module)
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
}

//////////// MAIN CODE ////////////
void loop() {

  /// SWITCHES ///
  int switch1State = digitalRead(SWITCH1);
  int switch2State = digitalRead(SWITCH2);
  int switch3State = digitalRead(SWITCH3);
  int switch4State = digitalRead(SWITCH4);

  // Switch 1
  if (switch1State != lastSwitch1State) {
    delay(50);
    switch1State = digitalRead(SWITCH1);
    if (switch1State != lastSwitch1State) {
      relay1State = !relay1State;
      digitalWrite(RELAY1, relay1State ? LOW : HIGH);
      Serial.println(relay1State ? "Relay1 ON" : "Relay1 OFF");
      lastSwitch1State = switch1State;
    }
  }

  // Switch 2
  if (switch2State != lastSwitch2State) {
    delay(50);
    switch2State = digitalRead(SWITCH2);
    if (switch2State != lastSwitch2State) {
      relay2State = !relay2State;
      digitalWrite(RELAY2, relay2State ? LOW : HIGH);
      Serial.println(relay2State ? "Relay2 ON" : "Relay2 OFF");
      lastSwitch2State = switch2State;
    }
  }

  // Switch 3
  if (switch3State != lastSwitch3State) {
    delay(50);
    switch3State = digitalRead(SWITCH3);
    if (switch3State != lastSwitch3State) {
      relay3State = !relay3State;
      digitalWrite(RELAY3, relay3State ? LOW : HIGH);
      Serial.println(relay3State ? "Relay3 ON" : "Relay3 OFF");
      lastSwitch3State = switch3State;
    }
  }

  // Switch 4
  if (switch4State != lastSwitch4State) {
    delay(50);
    switch4State = digitalRead(SWITCH4);
    if (switch4State != lastSwitch4State) {
      relay4State = !relay4State;
      digitalWrite(RELAY4, relay4State ? LOW : HIGH);
      Serial.println(relay4State ? "Relay4 ON" : "Relay4 OFF");
      lastSwitch4State = switch4State;
    }
  }

  /// IR REMOTE ///
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    if (code == 0x0 || code == 0xFFFFFFFF) {
      IrReceiver.resume();
      return;
    }

    Serial.println(code, HEX);

    switch (code) {
      case 0x7F80BA45:
      case 0xFE01BA45:
        relay1State = !relay1State;
        digitalWrite(RELAY1, relay1State ? LOW : HIGH);
        Serial.println(relay1State ? "Relay1 ON" : "Relay1 OFF");
        break;

      case 0x7E81BA45:
      case 0xFD02BA45:
        relay2State = !relay2State;
        digitalWrite(RELAY2, relay2State ? LOW : HIGH);
        Serial.println(relay2State ? "Relay2 ON" : "Relay2 OFF");
        break;

      case 0xAE51BA45:
      case 0xFC03BA45:
        relay3State = !relay3State;
        digitalWrite(RELAY3, relay3State ? LOW : HIGH);
        Serial.println(relay3State ? "Relay3 ON" : "Relay3 OFF");
        break;

      case 0xB24DBA45:
      case 0xFB04BA45:
        relay4State = !relay4State;
        digitalWrite(RELAY4, relay4State ? LOW : HIGH);
        Serial.println(relay4State ? "Relay4 ON" : "Relay4 OFF");
        break;
    }

    IrReceiver.resume();
  }
}
