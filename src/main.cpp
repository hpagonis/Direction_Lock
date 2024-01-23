#include <Arduino.h>
#include "Bounce2.h"

#define UP_PIN 2
#define RIGHT_PIN 3
#define DOWN_PIN 4
#define LEFT_PIN 5
#define RELAY_PIN 13
#define LED_PIN 12
#define DEBOUNCE_INTERVAL 200
#define DIRECTIONS_NUMBER 6
#define LED_BLINK_DELAY 500
#define BUTTON_NUM 4

enum Direction {Up, Right, Down, Left};
Direction sequence[DIRECTIONS_NUMBER] = {Down, Right, Up, Down, Left, Up};
Direction input[DIRECTIONS_NUMBER];
int8_t index = -1;
Bounce2::Button btn_Up = Bounce2::Button();
Bounce2::Button btn_Right = Bounce2::Button();
Bounce2::Button btn_Down = Bounce2::Button();
Bounce2::Button btn_Left = Bounce2::Button();

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  btn_Up.attach(UP_PIN, INPUT);
  btn_Up.interval(DEBOUNCE_INTERVAL);
  btn_Up.setPressedState(LOW);
  btn_Right.attach(RIGHT_PIN, INPUT);
  btn_Right.interval(DEBOUNCE_INTERVAL);
  btn_Right.setPressedState(LOW);
  btn_Down.attach(DOWN_PIN, INPUT);
  btn_Down.interval(DEBOUNCE_INTERVAL);
  btn_Down.setPressedState(LOW);
  btn_Left.attach(LEFT_PIN, INPUT);
  btn_Left.interval(DEBOUNCE_INTERVAL);
  btn_Left.setPressedState(LOW);
}

void loop() {
  btn_Up.update();
  btn_Right.update();
  btn_Down.update();
  btn_Left.update();

  if (btn_Up.pressed()) {
    input[index] = Up;
    index++;
    return;
  }
  if (btn_Right.pressed()) {
    input[index] = Right;
    index++;
    return;
  }
  if (btn_Down.pressed()) {
    input[index] = Down;
    index++;
    return;
  }
  if (btn_Left.pressed()) {
    input[index] = Left;
    index++;
    return;
  }
  if (index == DIRECTIONS_NUMBER) {
    if (memcmp(sequence, input, DIRECTIONS_NUMBER)) {
      // Incorrect sequence
      for (int i=0; i<3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(LED_BLINK_DELAY);
        digitalWrite(LED_PIN, LOW);
        delay(LED_BLINK_DELAY);
      }
    } else {
      // Correct sequence
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
      delay(5000);
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
    index = 0;
  }
}