#include <Arduino.h>
#include "Jets.h"

#define SHUTOFF 5000
#define WARN 4000

Jets::Jets(int button, int r, int g, int b, int power, int speed):
    _r(r), _g(g), _b(b), _power(power), _speed(speed),
    _bp(button), _button(50, button), _state(0),
    _last(0), _button_state(LOW), _is_warn(false) {}

void Jets::setup() {
  pinMode(_r, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_b, OUTPUT);
  pinMode(_bp, INPUT_PULLUP);
  pinMode(_power, OUTPUT);
  pinMode(_speed, OUTPUT);
  setColor(0, 255, 255);
  digitalWrite(_power, LOW);
  digitalWrite(_speed, LOW);
}

void Jets::update() {
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
      setColor(0, 255, 255);
    }
    toggle();
  }

  if (_state != 0) {
    // Check for shutoff.
    int t = millis() - _last;
    if (t >= SHUTOFF) {
      _is_warn = false;
      setColor(0, 255, 255);
      setState(0);
    } else if (t >= WARN) {
      _is_warn = true;
      setColor(255, 0, 0);
    }
  }
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
  setColor(0, 255, 255);
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

void Jets::setColor(int r, int g, int b) {
  analogWrite(_r, r);
  analogWrite(_g, g);
  analogWrite(_b, b);
}
