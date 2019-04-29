#include "Jets.h"
#include "Lights.h"

const int POWER_RELAY_PIN = 2;
const int JET_BUTTON_RED_PIN = 3;
const int SPEED_RELAY_PIN = 4;
const int JET_BUTTON_GREEN_PIN = 5;
const int JET_BUTTON_BLUE_PIN = 6;
const int JET_BUTTON_PIN = 7;
const int LIGHTS_BUTTON_PIN = 8;
const int LIGHTS_BUTTON_RED_PIN = 9;
const int LIGHTS_BUTTON_GREEN_PIN = 10;
const int LIGHTS_BUTTON_BLUE_PIN = 11;
const int LIGHTS_RELAY_PIN = 12;
const int CIRC_PUMP_RELAY_PIN = 13;
const int THERMOMETER_BUS_PIN = 14;

Jets jets(
    JET_BUTTON_PIN,
    JET_BUTTON_RED_PIN,
    JET_BUTTON_GREEN_PIN,
    JET_BUTTON_BLUE_PIN,
    POWER_RELAY_PIN,
    SPEED_RELAY_PIN);
Lights lights(
    LIGHTS_BUTTON_PIN,
    LIGHTS_BUTTON_RED_PIN,
    LIGHTS_BUTTON_GREEN_PIN,
    LIGHTS_BUTTON_BLUE_PIN,
    LIGHTS_RELAY_PIN);

void setup() {
  jets.setup();
  lights.setup();
}

void loop() {
  jets.update();
  lights.update();
}
