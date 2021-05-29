#include "init.h"
#include "key.h"
#include "stm32l476xx.h"

int main() {
    LED2_Init();
    TSC_Init();

    Key key;
    key.AFR = GPIO_AFRL_AFSEL6_Msk & (9UL << GPIO_AFRL_AFSEL6_Pos);
    key.IOASCR = TSC_IOASCR_G2_IO3; 
    key.IOCCR = TSC_IOCCR_G2_IO3;
    while(1){
        // Discharge Caps
        TSC->CR &= ~TSC_CR_IODEF;
        // Start TSC
        enable_key(&key);
        TSC->CR |= TSC_CR_START;
        // Wait for complettion
        for(int i = 0; i < 25000; i++);
    }
    


}

