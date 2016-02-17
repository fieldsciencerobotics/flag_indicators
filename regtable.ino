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

#include "product.h"
#include "regtable.h"
#include "byteops.h"

/**
 * Define common registers
 */
 
DEFINE_COMMON_REGISTERS()


//Define custom registers

static byte dt_heart_beat[2];
REGISTER reg_heart_beat(dt_heart_beat, sizeof(dt_heart_beat), &send_heart_beat, NULL);

static byte dt_ack_heart_beat[2];
REGISTER reg_ack_heart_beat(dt_ack_heart_beat, sizeof(dt_ack_heart_beat), NULL, &set_ack_heart_beat);

static byte dt_raise_flag[2];
REGISTER reg_raise_flag(dt_raise_flag, sizeof(dt_raise_flag), NULL, &set_raise_flag);

static byte dt_lower_flag[2];
REGISTER reg_lower_flag(dt_lower_flag, sizeof(dt_lower_flag), NULL, &set_lower_flag);
                      

/**
 * Table of registers
 */
 
DECLARE_REGISTERS_START()
  &reg_heart_beat, //19
  &reg_ack_heart_beat, //20
  &reg_raise_flag,  // 11
  &reg_lower_flag  // 12
DECLARE_REGISTERS_END()


/**
 * Define common getter/setter callback functions
 */
 
DEFINE_COMMON_CALLBACKS()


/**
 * Define custom getter/setter callback functions
 */

 
const void set_ack_heart_beat(byte rId, byte *value)
{
  hb_state = Pulse;
  swap.getRegister(REGI_HEART_BEAT)->getData();
}

const void send_heart_beat(byte rId)
{
  int_to_reg(swap.getRegister(REGI_HEART_BEAT), hb_state);
}

const void set_raise_flag(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(regTable[rId]->value));
  int servo_index;
  reg_to_int(regTable[rId], servo_index);

  if(servo_index < pin_map_len && servo_index >= 0)
  {  
    int servo_pin = pin_map[servo_index];
    flag.attach(servo_pin);
    flag.raise(3.0);
  }
}


const void set_lower_flag(byte rId, byte *value)
{ 
  memcpy(regTable[rId]->value, value, sizeof(regTable[rId]->value));
  int servo_index;
  reg_to_int(regTable[rId], servo_index);

  if(servo_index < pin_map_len && servo_index >= 0)
  {  
    int servo_pin = pin_map[servo_index];
    flag.attach(servo_pin);
    flag.lower(3.0);
  }
}





