#include <Arduino.h>
#include "Bounce2.h"

#define NORTH_PIN 2
#define EAST_PIN 3
#define SOUTH_PIN 4
#define WEST_PIN 5
#define DEBOUNCE_INTERVAL 50

enum Direction {North, East, South, West};
Direction sequence[5] = {North, North, South, East, East};
Bounce btn_North = Bounce();
Bounce btn_East = Bounce();
Bounce btn_South = Bounce();
Bounce btn_West = Bounce();

void setup() {
  Serial.begin(115200);
  btn_North.attach(NORTH_PIN, INPUT);
  btn_North.interval(DEBOUNCE_INTERVAL);
  btn_East.attach(EAST_PIN, INPUT);
  btn_East.interval(DEBOUNCE_INTERVAL);
  btn_South.attach(SOUTH_PIN, INPUT);
  btn_South.interval(DEBOUNCE_INTERVAL);
  btn_West.attach(WEST_PIN, INPUT);
  btn_West.interval(DEBOUNCE_INTERVAL);
  Serial.println("Combination Lock initialized");
}

void loop() {
  btn_North.update();
  btn_East.update();
  btn_South.update();
  btn_West.update();

  if (btn_North.read() || btn_East.read() || btn_South.read() || btn_West.read()) {
    Serial.println("Button pressed");
  }
}