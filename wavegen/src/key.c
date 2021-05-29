#include "key.h"

void enable_key(Key *key) {
    // We need a way tracking which GPIO is with it.
    GPIOB->AFR[0] |= key->AFR;
    TSC->IOASCR |= key->IOASCR;
    TSC->IOCCR |= key->IOCCR;
}

void disable_key(Key *key){
    GPIOB->AFR[0] &= ~(key->AFR);
    TSC->IOASCR &= ~(key->IOASCR);
    TSC->IOCCR &= ~(key->IOCCR);
}

