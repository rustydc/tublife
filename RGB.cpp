#include <Arduino.h>
#include "RGB.h"

RGB::RGB(int r, int g, int b):
    _r(r), _g(g), _b(b), 
    _r1(0), _g1(0), _b1(0),
    _r2(0), _g2(0), _b2(0),
    _start(0), _duration(0), _anim(0) {}

void RGB::setup() {
  pinMode(_r, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_b, OUTPUT);
}

void RGB::update() {
  int now;
  float t, p;
  int r, g, b;
  switch (_anim) {
    case 0:
      light(_r1, _g1, _b1);
      break;
    case 1:
      // Ease to.
      now = millis();
      t = now - _start;
      p = t / _duration;
      if (p >= 1) {
        _r1 = _r2;
	_g1 = _g2;
	_b1 = _b2;
	_anim = 0;
	light(_r1, _g1, _b1);
      } else {
        r = lerp(_r1, _r2, p);
        g = lerp(_g1, _g2, p);
        b = lerp(_b1, _b2, p);
        light(r, g, b);
      }
      break;
    case 2:
      // Pulse.
      now = millis();
      t = now - _start;
      p = 1 - (t / _duration);
      if (p <= 0) {
	_anim = 0;
	light(_r1, _g1, _b1);
      }
      r = lerp(_r1, _r2, p);
      g = lerp(_g1, _g2, p);
      b = lerp(_b1, _b2, p);
      light(r, g, b);
      break;
  }
}

void RGB::ease_to(int r, int g, int b, int duration) {
  if (_anim == 1) {
    _r1 = _r2;
    _g1 = _g2;
    _b1 = _b2;
  }
  _r2 = r;
  _g2 = g;
  _b2 = b;
  _anim = 1;
  _start = millis();
  _duration = duration;
}

void RGB::pulse(int r, int g, int b, int duration) {
  if (_anim == 1) {
    _r1 = _r2;
    _g1 = _g2;
    _b1 = _b2;
  }
  _r2 = r;
  _g2 = g;
  _b2 = b;
  _anim = 2;
  _start = millis();
  _duration = duration;
}

void RGB::set(int r, int g, int b) {
  _r1 = r;
  _g1 = g;
  _b1 = b;
  _anim = 0;
}

int RGB::lerp(int a, int b, float p) {
  return a + (p * (b - a));
}

void RGB::light(int r, int g, int b) {
  analogWrite(_r, r);
  analogWrite(_g, g);
  analogWrite(_b, b);
}
