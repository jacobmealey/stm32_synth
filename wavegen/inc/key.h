#ifndef _KEY_H
#define _KEY_H

#include "stm32l476xx.h"

// 12 keys in an octave brooooo
#define MAX_KEYS 3

#define TSC_G1 0
#define TSC_G2 1
#define TSC_G3 2
#define TSC_G4 3

// Key is used to organise all data for each pin 
// in the same area, as well as providing functions for 
// enabling/disabling a single pin.
typedef struct key {
    int AFR;        // GPIO AFR value 
    int IOASCR;     // TSC->IOASCR for selected pin / group
    int IOCCR;      // TSC channel enable 
    uint32_t tuned; // tuned value for turn on value. seems different for each.
    uint8_t gpio;   // 0 = GPIOB; 1 = GPIOC
    uint8_t group;
} Key;

extern volatile Key current_key;
extern Key keys[MAX_KEYS];

void enable_key(volatile Key *key);
void disable_key(volatile Key *key);
#endif
