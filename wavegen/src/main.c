#include "init.h"
#include "stm32l476xx.h"


int main() {
    System_Clock_80MHz_Init();
    DAC_init();
    LED2_Init();
    User_Button1_Init();

    int output = 0; 
    int dir = 1;

    while(1){
        //while((DAC->SR & DAC_SR_BWST1) != 0);
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG2;
        if(output >= 0xFFF || output <= 0){
            dir = -1 * dir;
        }


        DAC->DHR12R2 = output & 0xFFF;
        //DAC->DHR12R2 = 0xFFFF;
        output += dir;
        for(int i = 0; i < 20; i++);
    }
    


}

