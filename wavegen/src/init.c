#include "stm32l476xx.h"
#include "init.h"



void LED2_Init(void) {
    // Enable the clock to GPIO port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Set mode of pin as alternate function (mode 10)
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= 1UL << (2*5);

    GPIOA->MODER &= ~GPIO_MODER_MODE4;
    GPIOA->MODER |= GPIO_MODER_MODE4_1;
    // Set alternate function 3 (011) for PA5 (TIM8_CH1N)
    //GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5;
    //GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_1 | GPIO_AFRL_AFSEL5_0;
    // Set output speed of pin as low by clearing speed bits
    //GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
    // Set pin as no pull-up, no pull-down
    //GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void DAC_init(void) {
    // Enable DAC Clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;

    // Disable DAC channels
    DAC->CR &= ~(DAC_CR_EN1 | DAC_CR_EN2);

    // Set dac Mode ?? 
    DAC->MCR &= ~(7U);

    // Triangle Wave Generation
    DAC->CR |= DAC_CR_TEN1;
    DAC->CR |= DAC_CR_WAVE1_1;
    DAC->CR |= 0x01 << DAC_CR_TSEL1_Pos;
    DAC->CR |= 0xE << DAC_CR_MAMP1_Pos;

    // enable channel 1
    DAC->CR |= DAC_CR_EN1;

}


void TIM8_init(void) {
    // Disable the dac if it is currently being used
    TIM8->CR1 &= ~TIM_CR1_CEN;
    // Needs a global value for frequencie 
    // depending on frequncie must change the prescalar to
    // the selected frequncie :)
    // Everytime TIM8 triggers it will increase the triangle wave value 
    // in the DAC

    // Clock spped is 4MHz, we can use the equaction f_out = f_clock / (prescaler + 1)
    // So ... prescaler = (f_clock / f_out) - 1
    // 262 Hz is the freq of middle C. good starting point.
    int prescaler = (1000000 / freq) - 1; // Make this an inline function
    
    // Enable TIM8
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN; 
    //TIM8->CR1 &= ~(1UL); // upcounting
    //TIM8->PSC = prescaler/(2047); // set 
    TIM8->ARR = prescaler/(4096*2); 
    TIM8->CR2 |= 0x02UL << TIM_CR2_MMS_Pos;
    TIM8->CR1 |= TIM_CR1_CEN;


}

void TSC_Init(void) {
    // Enable Touch Sensor
    RCC->AHB1ENR |= RCC_AHB1ENR_TSCEN; 
    TSC->IER |= TSC_IER_EOAIE;
    TSC->CR &= ~TSC_CR_AM;
    TSC->CR |= TSC_CR_TSCE;

    // Enable port B and C 
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;

    // Set gpio to alternate function :) 
    // Group 1
    GPIOB->MODER |= GPIO_MODER_MODE12_1; // G1 IO1
    GPIOB->MODER |= GPIO_MODER_MODE13_1; // G1 IO2
    GPIOB->MODER |= GPIO_MODER_MODE14_1; // G1 IO3
    GPIOB->MODER |= GPIO_MODER_MODE15_1; // G1 IO4

    // Group 2
    GPIOB->MODER |= GPIO_MODER_MODE4_1; // G2 IO1
    GPIOB->MODER |= GPIO_MODER_MODE5_1; // G2 IO2
    GPIOB->MODER |= GPIO_MODER_MODE6_1; // G2 IO3
    GPIOB->MODER |= GPIO_MODER_MODE7_1; // G2 IO4

    // GROUP 3  -- IO1 is in GPIOA 
    // but we don't need it
    GPIOC->MODER |= GPIO_MODER_MODE10_1; // G3 IO2
    GPIOC->MODER |= GPIO_MODER_MODE11_1; // G3 IO3
    GPIOC->MODER |= GPIO_MODER_MODE12_1; // G3 IO4
    
    // Group 4
    GPIOC->MODER |= GPIO_MODER_MODE6_1; // G4 IO1
    GPIOC->MODER |= GPIO_MODER_MODE7_1; // G4 IO2
    GPIOC->MODER |= GPIO_MODER_MODE8_1; // G4 IO3
    GPIOC->MODER |= GPIO_MODER_MODE9_1; // G4 IO4

    // Set up the first IO of each group as AF
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_Msk & (9UL << GPIO_AFRL_AFSEL4_Pos);
    GPIOB->AFR[0] |= GPIO_AFRH_AFSEL12_Msk & (9UL << GPIO_AFRH_AFSEL12_Pos);
    GPIOC->AFR[0] |= GPIO_AFRL_AFSEL6_Msk & (9UL << GPIO_AFRL_AFSEL6_Pos);
    GPIOC->AFR[0] |= GPIO_AFRH_AFSEL10_Msk & (9UL << GPIO_AFRH_AFSEL10_Pos);

    // Set gpio 4 as TSC Sampler 
    GPIOB->OTYPER |= GPIO_OTYPER_OT12; // G1
    GPIOB->OTYPER |= GPIO_OTYPER_OT4;  // G2
    GPIOC->OTYPER |= GPIO_OTYPER_OT10; // G3
    GPIOC->OTYPER |= GPIO_OTYPER_OT6;  // G4

    // Set TSC TSC Sensor
    // G2
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT5);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT6);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT7);
    // G1
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT13);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT14);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT15);

    // enable analog switching
    TSC->IOASCR |= TSC_IOASCR_G1_IO1;
    TSC->IOASCR |= TSC_IOASCR_G2_IO1;
    TSC->IOASCR |= TSC_IOASCR_G3_IO2;
    TSC->IOASCR |= TSC_IOASCR_G4_IO1;

    // Set first IO of each group as sampling capacitor
    TSC->IOSCR |= TSC_IOSCR_G1_IO1;
    TSC->IOSCR |= TSC_IOSCR_G2_IO1;
    TSC->IOSCR |= TSC_IOSCR_G3_IO2;
    TSC->IOSCR |= TSC_IOSCR_G4_IO1;

    // enable TSC groups
    TSC->IOGCSR |= TSC_IOGCSR_G1E;
    TSC->IOGCSR |= TSC_IOGCSR_G2E;
    TSC->IOGCSR |= TSC_IOGCSR_G3E;
    TSC->IOGCSR |= TSC_IOGCSR_G4E;

    // Enable TSC interrupt
    NVIC_SetPriority(TSC_IRQn, 1);
    NVIC_EnableIRQ(TSC_IRQn);
}

void TSC_IRQHandler(void) {
    if(TSC->ISR & TSC_ISR_EOAF) {
        // This will be replaced with the dac enable flags
        // OR the DMA start flags if we're in SIN mode.
        if(TSC->IOGXCR[current_key.group] > current_key.tuned){
            freq = current_key.note;
            activated_key = &current_key;
            GPIOA->ODR |= 1 << 5;
        }else if(activated_key == &current_key && TSC->IOGXCR[current_key.group] < current_key.tuned){
            freq = 0;
        }else{
            GPIOA->ODR &= ~(1 << 5);
        } 
    }
    // Reset tim8
    TIM8_init();
    // disable the current key
    disable_key(&current_key);
    // Clear the interrupts
    TSC->ICR |= TSC_ICR_EOAIC;
}


void SysTick_init(void){
    SysTick->CTRL = 0;
    // Curremt clock speed is 4MHz, LOAD at 3999 means every 1 ms
    SysTick->LOAD = 4000 - 1;

    // Enable SysTick Interrup 
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
    // enabe SysTick
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


void SysTick_Handler(void){
    // key must persist through all systick calls
    // it keeps track of what keey is being scanned nxt
    static int key = 0;
    // update current_key globally
    current_key = keys[key++];
    // if we've scanned all keys go back to first
    if(key == MAX_KEYS) key = 0;
    // Discharge Caps
    TSC->CR &= ~TSC_CR_IODEF;
    // enable the current key
    enable_key(&current_key);
    // Start TSC
    TSC->CR |= TSC_CR_START;
}
        
