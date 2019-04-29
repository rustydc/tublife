#ifndef Lights_h
#define Lights_h

#include "RGB.h"
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
    RGB _rgb;
    int _bp, _relay;
    Debounce _button;
};

#endif
