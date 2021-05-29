#ifndef _KEY_H
#define _KEY_H

#include "stm32l476xx.h"

#define MAX_KEYS 2
// Key is used to organise all data for each pin 
// in the same area, as well as providing functions for 
// enabling/disabling a single pin.
typedef struct key {
    int AFR;        // GPIO AFR value 
    int IOASCR;     // TSC->IOASCR for selected pin / group
    int IOCCR;      // TSC channel enable 
    uint32_t tuned;      // tuned value for turn on value. seems different for each.
} Key;

extern volatile Key current_key;
extern Key keys[MAX_KEYS];

void enable_key(volatile Key *key);
void disable_key(volatile Key *key);
#endif
