#include <Arduino.h>
#include "Lights.h"

Lights::Lights(int button, int r, int g, int b, int relay):
    _r(r), _g(g), _b(b), _relay(relay),
    _bp(button), _button(50, button),
    _button_state(LOW) {}

void Lights::setup() {
  pinMode(_r, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_b, OUTPUT);
  pinMode(_relay, OUTPUT);
  pinMode(_bp, INPUT_PULLUP);
  setColor(0, 255, 255);
}

void Lights::update() {
  _button.update();
  // Check for button.
  int prev = _button_state;
  _button_state = _button.read();
  if (prev == HIGH && _button_state == LOW) {
    // Button press.
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

void Lights::setColor(int r, int g, int b) {
  analogWrite(_r, r);
  analogWrite(_g, g);
  analogWrite(_b, b);
}
