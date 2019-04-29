#ifndef RGB_h
#define RGB_h

class RGB
{
  public:
    RGB(int r, int g, int b);
    void setup();
    void update();
    void ease_to(int r, int g, int b, int duration);
    void pulse(int r, int g, int b, int duration);
    void set(int r, int g, int b);
  private:
    void light(int r, int g, int b);
    int lerp(int a, int b, float p);
    int _start, _duration;
    int _r, _g, _b;
    int _r1, _g1, _b1;
    int _r2, _g2, _b2;
    int _anim; // 0 = none, 1 = ease, 2 = pulse.
};

#endif
