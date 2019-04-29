#ifndef Jets_h
#define Jets_h

#include "RGB.h"
#include "Debounce.h"

class Jets
{
  public:
    Jets(int button, int r, int g, int b, int power, int speed);
    void setup();
    void update();
    void toggle();
    void setState(int state);
  private:
    int _state;
    int _last;
    int _button_state;
    int _is_warn;
    RGB _rgb;
    int _power, _speed, _bp;
    Debounce _button;
};

#endif
