#include <Arduino.h>

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

enum btnDirection {Up, Left, Down, Right};
enum btnState {Pressed, Depressed};
uint8_t sequence[DIRECTIONS_NUMBER] = {Up, Left, Down, Up, Right, Down};
uint8_t input[DIRECTIONS_NUMBER];
uint8_t pins[4] = {2,3,4,5};
uint8_t btnStatus[4] = {Depressed, Depressed, Depressed, Depressed};
const uint8_t btnRst[4] = {0,0,0,0};

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  for (int i=0; i<4; i++) {
    pinMode(pins[i], INPUT);
  }
  Serial.println("Board initialized");
}

void loop() {
  static uint8_t btn_buf[4] = {};
  for (int i=0; i<4; i++) {
    btn_buf[i] = btn_buf[i] << 1;
    btn_buf[i] |= digitalRead(pins[i]) ? 1 : 0;
  }

  //Move array one position and add new input
  for (int i=0; i<4; i++) {
    if (btnStatus[i] == Pressed && btn_buf[i] != Pressed) {
      memmove(&input[1], &input[0], DIRECTIONS_NUMBER - 1);
      input[0] = i;
    }
    btnStatus[i] = btn_buf[i] ? Depressed : Pressed;
  }

  if (memcmp(input, sequence, DIRECTIONS_NUMBER) == 0) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Puzzle solved");
    memset(input, 0, sizeof input);
  }

  if (memcmp(btn_buf, btnRst, 4) == 0) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Puzzle reset");
  }
  delay(15);
}