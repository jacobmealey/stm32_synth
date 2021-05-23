#include "init.h"
#include "stm32l476xx.h"


int main() {
    //System_Clock_80MHz_Init();
    DAC_init();
    LED2_Init();

    int output = 0; 

    while(1){
        //while((DAC->SR & DAC_SR_BWST1) != 0);
        DAC->DHR12R2 = output;
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG2;
        for(int i = 0; i < 1; i++);
        output = (output + 1) & 0xFFF;
    }
    


}

