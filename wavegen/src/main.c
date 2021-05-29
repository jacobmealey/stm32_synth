#include "init.h"
#include "key.h"
#include "stm32l476xx.h"

Key keys[MAX_KEYS];
volatile Key current_key;

int main() {
    LED2_Init();
    TSC_Init();
    SysTick_init();

    // Sets up PB.6 and PB.5 as Keys
    keys[0].AFR = GPIO_AFRL_AFSEL6_Msk & (9UL << GPIO_AFRL_AFSEL6_Pos);
    keys[0].IOASCR = TSC_IOASCR_G2_IO3; 
    keys[0].IOCCR = TSC_IOCCR_G2_IO3;
    keys[0].tuned = 26;

    keys[1].AFR = GPIO_AFRL_AFSEL5_Msk & (9UL << GPIO_AFRL_AFSEL5_Pos);
    keys[1].IOASCR = TSC_IOASCR_G2_IO2; 
    keys[1].IOCCR = TSC_IOCCR_G2_IO2;
    keys[1].tuned = 25;

    // Dead loop
    while(1){}
}

