#ifndef Jets_h
#define Jets_h

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
    int _r, _g, _b, _power, _speed, _bp;
    Debounce _button;
    void setColor(int r, int g, int b);
};

#endif
