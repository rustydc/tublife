#ifndef Lights_h
#define Lights_h

#include "Debounce.h"

class Lights
{
  public:
    Lights(int button, int r, int g, int b, int relay);
    void setup();
    void update();
    void toggle();
    void setState(int state);
  private:
    int _state;
    int _button_state;
    int _r, _g, _b, _bp, _relay;
    Debounce _button;
    void setColor(int r, int g, int b);
};

#endif
