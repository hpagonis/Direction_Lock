#include <Arduino.h>
#include "Bounce2.h"

#define NORTH_PIN 2
#define EAST_PIN 3
#define SOUTH_PIN 4
#define WEST_PIN 5
#define RELAY_PIN 13
#define LED_PIN 12
#define DEBOUNCE_INTERVAL 200
#define DIRECTIONS_NUMBER 6
#define LED_BLINK_DELAY 500

enum Direction {North, East, South, West};
Direction sequence[DIRECTIONS_NUMBER] = {South, East, North, South, West, North};
uint8_t index = 0;
Bounce2::Button btn_North = Bounce2::Button();
Bounce2::Button btn_East = Bounce2::Button();
Bounce2::Button btn_South = Bounce2::Button();
Bounce2::Button btn_West = Bounce2::Button();

void WrongDirection();

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  btn_North.attach(NORTH_PIN, INPUT);
  btn_North.interval(DEBOUNCE_INTERVAL);
  btn_North.setPressedState(LOW);
  btn_East.attach(EAST_PIN, INPUT);
  btn_East.interval(DEBOUNCE_INTERVAL);
  btn_East.setPressedState(LOW);
  btn_South.attach(SOUTH_PIN, INPUT);
  btn_South.interval(DEBOUNCE_INTERVAL);
  btn_South.setPressedState(LOW);
  btn_West.attach(WEST_PIN, INPUT);
  btn_West.interval(DEBOUNCE_INTERVAL);
  btn_West.setPressedState(LOW);
  Serial.println("Combination Lock initialized");
}

void loop() {
  btn_North.update();
  btn_East.update();
  btn_South.update();
  btn_West.update();

  if (btn_North.pressed()) {
    Serial.println("Button North pressed");
    if (sequence[index] == North) {
      Serial.println("Correct direction");
      index++;
    } else {
      Serial.println("Wrong direction");
      WrongDirection();
      index = 0;
    }
    return;
  }
  if (btn_East.pressed()) {
    Serial.println("Button East pressed");
    if (sequence[index] == East) {
      Serial.println("Correct direction");
      index++;
    } else {
      Serial.println("Wrong direction");
      WrongDirection();
      index = 0;
    }
    return;
  }
  if (btn_South.pressed()) {
    Serial.println("Button South pressed");
    if (sequence[index] == South) {
      Serial.println("Correct direction");
      index++;
    } else {
      Serial.println("Wrong direction");
      WrongDirection();
      index = 0;
    }
    return;
  }
  if (btn_West.pressed()) {
    Serial.println("Button West pressed");
    if (sequence[index] == West) {
      Serial.println("Correct direction");
      index++;
    } else {
      Serial.println("Wrong direction");
      WrongDirection();
      index = 0;
    }
    return;
  }
  if (index == DIRECTIONS_NUMBER) {
    Serial.println("Relay activated");
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    digitalWrite(RELAY_PIN, LOW);
    index = 0;
    Serial.println("Relay deactivated");
  }
}

void WrongDirection() {
  for (int i=0; i<3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(LED_BLINK_DELAY);
    digitalWrite(LED_PIN, LOW);
    delay(LED_BLINK_DELAY);
  }
}