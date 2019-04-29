#include <Arduino.h>
#include "Lights.h"

Lights::Lights(int button, int r, int g, int b, int relay):
    _rgb(r, g, b), _relay(relay),
    _bp(button), _button(50, button),
    _button_state(LOW) {}

void Lights::setup() {
  _rgb.setup();
  _rgb.set(0, 255, 255);
  pinMode(_relay, OUTPUT);
  pinMode(_bp, INPUT_PULLUP);
}

void Lights::update() {
  _button.update();
  // Check for button.
  int prev = _button_state;
  _button_state = _button.read();
  if (prev == HIGH && _button_state == LOW) {
    // Button press.
    _rgb.pulse(255, 255, 255, 500);
    toggle();
  }
}

void Lights::toggle() {
  if (_state == 1) {
    setState(0);
    digitalWrite(_relay, LOW);
  } else {
    setState(_state + 1);
    digitalWrite(_relay, HIGH);
  }
}

void Lights::setState(int state) {
  _state = state;
}
