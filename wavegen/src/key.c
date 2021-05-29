#include "key.h"

void enable_key(Key *key) {
    key->AFR |= 1;
}
void disable_key(Key *key){
    key->AFR &= ~1;
}
