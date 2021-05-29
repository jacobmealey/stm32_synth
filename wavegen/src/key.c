#include "key.h"

// Disables the key passed
void enable_key(volatile Key *key) {
    // We need a way tracking which GPIO is with it.
    GPIOB->AFR[0] |= key->AFR;
    // enable analog switching for current key
    TSC->IOASCR |= key->IOASCR;
    // enable TSC channel on current key
    TSC->IOCCR |= key->IOCCR;
}


// Disables the key, happens in the opposite order
// of enable_key(), not sure if its strictly needed
// to be done that way, but might as well.
void disable_key(volatile Key *key){
    // disable tsc channel on current key
    TSC->IOCCR &= ~(key->IOCCR);
    // disable analog switching
    TSC->IOASCR &= ~(key->IOASCR);
    // disable pin afr
    GPIOB->AFR[0] &= ~(key->AFR);
}

