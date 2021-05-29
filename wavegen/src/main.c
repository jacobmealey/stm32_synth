#include "init.h"
#include "stm32l476xx.h"


int main() {
    //System_Clock_80MHz_Init();
    //DAC_init();
    LED2_Init();
    //User_Button1_Init();
    TSC_Init();


    while(1){
        // Discharge Caps
        TSC->CR &= ~TSC_CR_IODEF;
        // Start TSC
        TSC->CR |= TSC_CR_START;
        // Wait for complettion
        while(!(TSC->IOGCSR & TSC_IOGCSR_G2S)){
            if(TSC->IOGXCR[1] > 34){
                GPIOA->ODR ^= 1 << 5;
                // shiddy debounce
                for(int i = 0; i < 35000; i++);
            }

        }

    }
    


}

