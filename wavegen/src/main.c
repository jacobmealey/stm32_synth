#include "init.h"
#include "key.h"
#include "stm32l476xx.h"

Key keys[MAX_KEYS];
volatile Key current_key;

int main() {

    // TSC group 2
    int G2_tune = 26;
    keys[0].AFR = GPIO_AFRL_AFSEL6_Msk & (9UL << GPIO_AFRL_AFSEL6_Pos);
    keys[0].IOASCR = TSC_IOASCR_G2_IO3; 
    keys[0].IOCCR = TSC_IOCCR_G2_IO3;
    keys[0].tuned = G2_tune;
    keys[0].gpio = 0;
    keys[0].group = TSC_G2;

    keys[1].AFR = GPIO_AFRL_AFSEL5_Msk & (9UL << GPIO_AFRL_AFSEL5_Pos);
    keys[1].IOASCR = TSC_IOASCR_G2_IO2; 
    keys[1].IOCCR = TSC_IOCCR_G2_IO2;
    keys[1].tuned = G2_tune - 1;
    keys[1].gpio = 0;
    keys[1].group = TSC_G2;

    keys[2].AFR = GPIO_AFRL_AFSEL7_Msk & (9UL << GPIO_AFRL_AFSEL7_Pos);
    keys[2].IOASCR = TSC_IOASCR_G2_IO4; 
    keys[2].IOCCR = TSC_IOCCR_G2_IO4;
    keys[2].tuned = G2_tune;
    keys[2].gpio = 0;
    keys[2].group = TSC_G2;

    // // TSC group 1
    // int G1_tune = 29;
    // keys[3].AFR = GPIO_AFRH_AFSEL13_Msk & (9UL << GPIO_AFRH_AFSEL13_Pos);
    // keys[3].IOASCR = TSC_IOASCR_G1_IO2; 
    // keys[3].IOCCR = TSC_IOCCR_G1_IO2;
    // keys[3].tuned = G1_tune;
    // keys[3].gpio = 0;
    // keys[3].group = TSC_G1;

    // keys[4].AFR = GPIO_AFRH_AFSEL14_Msk & (9UL << GPIO_AFRH_AFSEL14_Pos);
    // keys[4].IOASCR = TSC_IOASCR_G1_IO3; 
    // keys[4].IOCCR = TSC_IOCCR_G1_IO3;
    // keys[4].tuned = G1_tune;
    // keys[4].gpio = 0;
    // keys[4].group = TSC_G1;

    // keys[5].AFR = GPIO_AFRH_AFSEL15_Msk & (9UL << GPIO_AFRH_AFSEL15_Pos);
    // keys[5].IOASCR = TSC_IOASCR_G1_IO4; 
    // keys[5].IOCCR = TSC_IOCCR_G1_IO4;
    // keys[5].tuned = G1_tune;
    // keys[5].gpio = 0;
    // keys[5].group = TSC_G1;

    //// TSC group 3
    //int G3_tune = 60;
    //keys[7].AFR = GPIO_AFRH_AFSEL11_Msk & (9UL << GPIO_AFRH_AFSEL11_Pos);
    //keys[7].IOASCR = TSC_IOASCR_G3_IO3; 
    //keys[7].IOCCR = TSC_IOCCR_G3_IO3;
    //keys[7].tuned = G3_tune;
    //keys[7].gpio = 0;

    //keys[8].AFR = GPIO_AFRH_AFSEL12_Msk & (9UL << GPIO_AFRH_AFSEL12_Pos);
    //keys[8].IOASCR = TSC_IOASCR_G3_IO4; 
    //keys[8].IOCCR = TSC_IOCCR_G3_IO4;
    //keys[8].tuned = G3_tune;
    //keys[8].gpio = 0;

    //// TSC group 4
    //int G4_tune = 60;
    //keys[9].AFR = GPIO_AFRL_AFSEL7_Msk & (9UL << GPIO_AFRL_AFSEL7_Pos);
    //keys[9].IOASCR = TSC_IOASCR_G4_IO2; 
    //keys[9].IOCCR = TSC_IOCCR_G4_IO2;
    //keys[9].tuned = G4_tune;
    //keys[9].gpio = 1;

    //keys[10].AFR = GPIO_AFRH_AFSEL8_Msk & (9UL << GPIO_AFRH_AFSEL8_Pos);
    //keys[10].IOASCR = TSC_IOASCR_G4_IO3; 
    //keys[10].IOCCR = TSC_IOCCR_G4_IO3;
    //keys[10].tuned = G4_tune;
    //keys[10].gpio = 1;

    //keys[11].AFR = GPIO_AFRH_AFSEL9_Msk & (9UL << GPIO_AFRH_AFSEL9_Pos);
    //keys[11].IOASCR = TSC_IOASCR_G4_IO4; 
    //keys[11].IOCCR = TSC_IOCCR_G4_IO4;
    //keys[11].tuned = G4_tune;
    //keys[11].gpio = 1;

    LED2_Init();
    TSC_Init();
    TIM8_init();
    DAC_init();
    SysTick_init();

    // Dead loop
    while(1){
        //DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
    }
}

