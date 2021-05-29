#ifndef _KEY_H
#define _KEY_H

#include "stm32l476xx.h"

// Key is used to organise all data for each pin 
// in the same area, as well as providing functions for 
// enabling/disabling a single pin.
typedef struct key {
    int AFR;        // GPIO AFR value 
    int IOASCR;     // TSC->IOASCR for selected pin / group
    int IOCCR;      // TSC channel enable 
    int tuned;      // tuned value for turn on value. seems different for each.
} Key;

void enable_key(Key *key);
void disable_key(Key *key);
#endif
