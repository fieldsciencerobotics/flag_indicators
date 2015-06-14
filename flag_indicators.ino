#include <Arduino.h>
#include <cc430f5137.h>
#include "HardwareSerial.h"
#include "cc430f5137.h"
#include "wiring.h"
#include "Flag.h"
#include "VoltageDivider.h"
#include "regtable.h"
#include "product.h"
#include "swap.h"

Flag flag;
VoltageDivider d2;
VoltageDivider d3;
int pin_map[] = {16, 17, 0, 1, 2, 3, 4, 5, 6, 7};

DECLARE_COMMON_CALLBACKS()
DEFINE_COMMON_REGISTERS()

//Define custom registers
static byte dt_raise_flag[1];
REGISTER reg_raise_flag(dt_raise_flag, sizeof(dt_raise_flag), NULL, &set_raise_flag);

static byte dt_lower_flag[1];
REGISTER reg_lower_flag(dt_lower_flag, sizeof(dt_lower_flag), NULL, &set_lower_flag);

static byte dt_req_batt_volt[1];
REGISTER reg_req_batt_volt(dt_req_batt_volt, sizeof(dt_req_batt_volt), NULL, &set_req_batt_volt);
                      
static byte dt_batt_volt[4];
REGISTER reg_batt_volt(dt_batt_volt, sizeof(dt_batt_volt), &updt_batt_volt, NULL);
                     
DECLARE_REGISTERS_START()
  &reg_raise_flag,  // 11
  &reg_lower_flag,  // 12
  &reg_req_batt_volt, //13
  &reg_batt_volt, //14
DECLARE_REGISTERS_END()

DEFINE_COMMON_CALLBACKS()


void setup() {
  WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
  Serial.begin(9600);
  
  //Attach other devices
  d2.attach(8, 10000, 5600);
  d3.attach(9, 10000, 10000);
  
  swap.init(); // Initialize SWAP registers
  swap.getRegister(REGI_PRODUCTCODE)->getData(); // Transmit product code;
  swap.getRegister(REGI_BATT_VOLT)->getData();

  _BIS_SR(LPM0_bits + GIE); //LPM0_bits
}


const void set_raise_flag(byte rId, byte *servo_id)
{
  Serial.println("Raising flag");  
  memcpy(regTable[rId]->value, servo_id, sizeof(regTable[rId]->value));
  int pin_num = pin_map[servo_id[0]];
  flag.attach(pin_num);
  flag.raise(3.0);
}


const void set_lower_flag(byte rId, byte *servo_id)
{  
  Serial.println("Lowering flag");
  memcpy(regTable[rId]->value, servo_id, sizeof(regTable[rId]->value));
  int pin_num = pin_map[servo_id[0]];
  flag.attach(pin_num);
  flag.lower(3.0);
}

//Send updated battery voltages to server
const void set_req_batt_volt(byte rId, byte *junk)
{
  Serial.println("Requesting battery voltages");
  memcpy(regTable[rId]->value, junk, sizeof(regTable[rId]->value));
  swap.getRegister(REGI_BATT_VOLT)->getData();
}

//Updates register with battery cell voltages
const void updt_batt_volt(byte rId)
{
  float d2_val = d2.read_voltage(); 
  float d3_val = d3.read_voltage();
  
  float cell_2 = d2_val - d3_val;
  float cell_3 = d3_val;
  
  int cell_2_int = int(cell_2*100.0);
  int cell_3_int = int(cell_3*100.0);
  
  regTable[rId]->value[0] = (cell_2_int >> 8) & 0xFF;
  regTable[rId]->value[1] = cell_2_int & 0xFF;
  
  regTable[rId]->value[2] = (cell_3_int >> 8) & 0xFF;
  regTable[rId]->value[3] = cell_3_int & 0xFF;  
}

void loop(){}





