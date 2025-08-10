#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2;     // IR Receiver data pin
const int IR_SEND_PIN = 3;        // IR LED/emitter pin
const int BUTTON_PIN = 4;         // Pushbutton pin

unsigned long savedCode = 0;
bool codeCaptured = false;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button connected to GND when pressed

  // Initialize IR receiver and sender
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("IR Cloner Ready. Send a code to capture it.");
}

void loop() {
  // Listen for an incoming IR code
  if (IrReceiver.decode()) {
    if (!codeCaptured && IrReceiver.decodedIRData.protocol == NEC) {
      savedCode = IrReceiver.decodedIRData.decodedRawData;
      codeCaptured = true;

      Serial.print("Captured NEC code: 0x");
      Serial.println(savedCode, HEX);
      Serial.println("Press the button to replay the code.");
    } else {
      Serial.print("Other IR code: 0x");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    }

    IrReceiver.resume(); // Ready for next
  }

  // If a code has been captured and button is pressed, replay it
  if (codeCaptured && digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed! Replaying signal...");

    // Send NEC signal
    IrSender.sendNEC(savedCode, 32); // 32 = number of bits in NEC protocol
    delay(500); // Debounce delay
  }
}
