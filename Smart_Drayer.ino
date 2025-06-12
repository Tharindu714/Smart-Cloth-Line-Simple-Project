// Smart Dryer: Blink-Idle + Wet/Dry Triggered 15s Motor Runs
// - Water sensor on D2 (INPUT_PULLUP: LOW = wet, HIGH = dry)
// - Built-in LED on D13: shows blink in idle, HIGH for CW, LOW for CCW
// - L298N driver: IN1→D7, IN2→D8, ENA→D9
// - CW run = 15 s, CCW run = 15 s, then back to idle blink

#include <Arduino.h>

const uint8_t PIN_WATER = 2;   // water sensor OUT (with INPUT_PULLUP)
const uint8_t PIN_LED   = 13;  // on-board LED

const uint8_t PIN_IN1 = 7;     // L298N dir1
const uint8_t PIN_IN2 = 8;     // L298N dir2
const uint8_t PIN_ENA = 9;     // L298N enable (PWM)

enum State { IDLE, RUN_CW, RUN_CCW };
State currentState = IDLE;
bool lastWasCW = false;        // track last run direction (initial = CCW logically)

unsigned long stateStart = 0;
unsigned long blinkStart = 0;
bool blinkLED = false;

const unsigned long DUR_RUN  = 2UL * 1000UL;  // 15 seconds
const unsigned long DUR_BLINK = 500;           // blink interval 0.5 s

void setup() {
  Serial.begin(9600);
  Serial.println("=== Smart Dryer Init ===");

  pinMode(PIN_WATER, INPUT_PULLUP);
  pinMode(PIN_LED,   OUTPUT);
  pinMode(PIN_IN1,   OUTPUT);
  pinMode(PIN_IN2,   OUTPUT);
  pinMode(PIN_ENA,   OUTPUT);

  // ensure motors off
  digitalWrite(PIN_ENA, LOW);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);

  // start in IDLE
  stateStart = millis();
  blinkStart = millis();
  blinkLED = false;
  digitalWrite(PIN_LED, blinkLED);
  lastWasCW = false;  // pretend last run was CCW so first wet→CW triggers
  Serial.println("Entering IDLE (blinking).");
}

void loop() {
  unsigned long now = millis();
  bool isWet = (digitalRead(PIN_WATER) == LOW);

  switch (currentState) {
    case IDLE:
      // blink LED
      if (now - blinkStart >= DUR_BLINK) {
        blinkStart = now;
        blinkLED = !blinkLED;
        digitalWrite(PIN_LED, blinkLED);
      }

      // check for wet→CW
      if (isWet && !lastWasCW) {
        currentState = RUN_CW;
        stateStart = now;
        // start CW
        digitalWrite(PIN_IN1, HIGH);
        digitalWrite(PIN_IN2, LOW);
        analogWrite(PIN_ENA, 255);
        digitalWrite(PIN_LED, HIGH);
        Serial.println("Sensor WET → RUN CW for 15 s");
      }
      // check for dry→CCW
      else if (!isWet &&  lastWasCW) {
        currentState = RUN_CCW;
        stateStart = now;
        // start CCW
        digitalWrite(PIN_IN1, LOW);
        digitalWrite(PIN_IN2, HIGH);
        analogWrite(PIN_ENA, 255);
        digitalWrite(PIN_LED, LOW);
        Serial.println("Sensor DRY → RUN CCW for 15 s");
      }
      break;

    case RUN_CW:
      if (now - stateStart >= DUR_RUN) {
        // stop motor
        analogWrite(PIN_ENA, 0);
        digitalWrite(PIN_IN1, LOW);
        // record last
        lastWasCW = true;
        // back to idle
        currentState = IDLE;
        blinkStart = now;
        Serial.println("CW done → back to IDLE");
      }
      break;

    case RUN_CCW:
      if (now - stateStart >= DUR_RUN) {
        // stop motor
        analogWrite(PIN_ENA, 0);
        digitalWrite(PIN_IN2, LOW);
        // record last
        lastWasCW = false;
        // back to idle
        currentState = IDLE;
        blinkStart = now;
        Serial.println("CCW done → back to IDLE");
      }
      break;
  }

  delay(10);  // small loop delay
}

