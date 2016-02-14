/*
The MIT License (MIT)

Copyright (c) 2016 Field Science Robotics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Arduino.h>
#include <cc430f5137.h>
#include "HardwareSerial.h"
#include "cc430f5137.h"
#include "wiring.h"
#include "Flag.h"
#include "regtable.h"
#include "product.h"
#include "swap.h"

Flag flag;
int pin_map[] = {16, 17, 0, 1, 2, 3, 4, 5, 6, 7};
int pin_map_len = sizeof(pin_map) / sizeof(int);

void setup() {
  WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
  
  swap.init();
  swap.getRegister(REGI_PRODUCTCODE)->getData();

  initialise_flags(); //initalise flags

  _BIS_SR(LPM0_bits + GIE); //LPM0_bits
}

void initialise_flags()
{
  for(int i = 0; i < pin_map_len; i++)
  {
    int servo_pin = pin_map[i];
    flag.attach(servo_pin);
    flag.raise(3.0);
  }
}

void loop(){}





