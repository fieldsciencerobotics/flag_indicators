
#ifndef Flag_h
#define Flag_h

#include <Arduino.h>

class Flag
{
  public:
    Flag();
    void lower(float seconds=1.0);
    void raise(float seconds=1.0);
    void attach(int pin);
    void stop();
  private:
    static const int lower_pulse;
	static const int raise_pulse;
	static const int period;
	int servo_pin;
};

#endif
