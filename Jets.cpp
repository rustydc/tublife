#include <Arduino.h>
#include "Jets.h"

#define SHUTOFF 5000
#define WARN 4000

Jets::Jets(int button, int r, int g, int b, int power, int speed):
    _rgb(r, g, b),  _power(power), _speed(speed),
    _bp(button), _button(50, button), _state(0),
    _last(0), _button_state(LOW), _is_warn(false) {}

void Jets::setup() {
  _rgb.setup();
  pinMode(_bp, INPUT_PULLUP);
  pinMode(_power, OUTPUT);
  pinMode(_speed, OUTPUT);
  digitalWrite(_power, LOW);
  digitalWrite(_speed, LOW);
  _rgb.set(0, 255, 255);
}

void Jets::update() {
  delay(1);
  _button.update();
  // Check for button.
  int prev = _button_state;
  _button_state = _button.read();
  if (prev == HIGH && _button_state == LOW) {
    // Button press.
    // TODO(rmel): Factor this out.
    _last = millis();
    if (_is_warn) {
      _is_warn = false;
      _rgb.ease_to(0, 255, 255, 500);
    } else {
      _rgb.pulse(255, 255, 255, 500);
      toggle();
    }
  }

  if (_state != 0) {
    // Check for shutoff.
    int t = millis() - _last;
    if (t >= SHUTOFF) {
      _is_warn = false;
      _rgb.ease_to(0, 255, 255, 1000);
      setState(0);
    } else if (t >= WARN && !_is_warn) {
      _is_warn = true;
      _rgb.ease_to(255, 0, 0, 1000);
    }
  }

  _rgb.update();
}

void Jets::toggle() {
  if (_state == 2) {
    setState(0);
  } else {
    setState(_state + 1);
  }
}

void Jets::setState(int state) {
  _is_warn = false;
  if (state == 0) {
    digitalWrite(_power, LOW);
    digitalWrite(_speed, LOW);
  } else if (state == 1) {
    digitalWrite(_power, HIGH);
    digitalWrite(_speed, LOW);
  } else if (state == 2) {
    digitalWrite(_power, HIGH);
    digitalWrite(_speed, HIGH);
  }
  _state = state;
}

