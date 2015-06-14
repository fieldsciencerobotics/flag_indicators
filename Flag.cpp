#include "Flag.h"
#include "HardwareSerial.h"

int const Flag::lower_pulse = 2300;
int const Flag::raise_pulse = 1000;
int const Flag::period = 20000;

Flag::Flag()
{
  
}

void Flag::attach(int pin)
{
  this->servo_pin = pin;
  pinMode(this->servo_pin, OUTPUT);
}

void Flag::lower(float seconds)
{   
 // Serial.println("Pushing down");
  
  int cycles = 50 * seconds;
  for(int i = 0; i < cycles; i++)
  {    
    const int remaining_time = Flag::period - Flag::lower_pulse;
    digitalWrite(this->servo_pin, HIGH);
    delayMicroseconds(Flag::lower_pulse);
    digitalWrite(this->servo_pin, LOW);
    delayMicroseconds(remaining_time);
  }
}
  
void Flag::raise(float seconds)
{
 // Serial.println("Pulling up");
  
  int cycles = 50 * seconds;
  for(int i = 0; i < cycles; i++)
  {    
    const int remaining_time = Flag::period - Flag::raise_pulse;
    digitalWrite(this->servo_pin, HIGH);
    delayMicroseconds(Flag::raise_pulse);
    digitalWrite(this->servo_pin, LOW);
    delayMicroseconds(remaining_time);
  }
}


