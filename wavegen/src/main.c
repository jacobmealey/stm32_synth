#include "init.h"
#include "key.h"
#include "stm32l476xx.h"

Key keys[2];
volatile Key current_key;

int main() {
    LED2_Init();
    TSC_Init();
    int key = 0;
    keys[0].AFR = GPIO_AFRL_AFSEL6_Msk & (9UL << GPIO_AFRL_AFSEL6_Pos);
    keys[0].IOASCR = TSC_IOASCR_G2_IO3; 
    keys[0].IOCCR = TSC_IOCCR_G2_IO3;
    keys[0].tuned = 26;

    keys[1].AFR = GPIO_AFRL_AFSEL5_Msk & (9UL << GPIO_AFRL_AFSEL5_Pos);
    keys[1].IOASCR = TSC_IOASCR_G2_IO2; 
    keys[1].IOCCR = TSC_IOCCR_G2_IO2;
    keys[1].tuned = 25;

    while(1){
        if(key == 1) key = 0;
        else if(key == 0) key = 1;

        current_key = keys[key];
        // Discharge Caps
        TSC->CR &= ~TSC_CR_IODEF;
        // Start TSC
        enable_key(&current_key);
        TSC->CR |= TSC_CR_START;
        for(int i = 0; i < 1000; i++);
    }
    


}

