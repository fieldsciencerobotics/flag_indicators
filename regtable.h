#ifndef regtable_h
#define regtable_h

#include "Arduino.h"
#include "register.h"
#include "commonregs.h"

/**
 * Register indexes
 */
DEFINE_REGINDEX_START()
  REGI_RAISE_FLAG,
  REGI_LOWER_FLAG,
  REGI_REQ_BATT_VOLT,
  REGI_BATT_VOLT
DEFINE_REGINDEX_END()

#endif
