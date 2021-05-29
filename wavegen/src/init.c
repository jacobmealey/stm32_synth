#include "stm32l476xx.h"
#include "init.h"



void LED2_Init(void) {
    // Enable the clock to GPIO port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Set mode of pin as alternate function (mode 10)
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= 1UL << (2*5);
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

    DAC->CR &= ~(DAC_CR_EN1 | DAC_CR_EN2);

    // Set dac Mode ?? 
    DAC->MCR &= ~(7U << 16);

    DAC->CR |= DAC_CR_TEN2;
    DAC->CR |= DAC_CR_TSEL2;

    DAC->CR |= DAC_CR_EN2;

}


void TSC_Init(void) {
    // Enable Touch Sensor
    RCC->AHB1ENR |= RCC_AHB1ENR_TSCEN; 
    TSC->IER |= TSC_IER_EOAIE;
    TSC->CR &= ~TSC_CR_AM;
    TSC->CR |= TSC_CR_TSCE;

    // Set up PB.4 - PB.7 to run on TSC_G2
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    // Set gpio to alternate function :) 
    GPIOB->MODER |= 2UL << (2 * 4);
    GPIOB->MODER |= 2UL << (2 * 5);
    GPIOB->MODER |= 2UL << (2 * 6);
    // will this work ?? lol
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_Msk & (9UL << GPIO_AFRL_AFSEL4_Pos);

    // Set gpio 4 as TSC Sampler 
    GPIOB->OTYPER |= 1 << 4;

    // Set gpio 5 as TSC Sensor
    GPIOB->OTYPER &= ~(1 << 5);

    // enable analog switching
    TSC->IOASCR |= TSC_IOASCR_G2_IO1;

    // Set PB.4 as sampling capacitor
    TSC->IOSCR |= TSC_IOSCR_G2_IO1;
    // enable TSC group 2
    TSC->IOGCSR |= TSC_IOGCSR_G2E;

    // Enable TSC interrupt
    NVIC_SetPriority(TSC_IRQn, 1);
    NVIC_EnableIRQ(TSC_IRQn);
}

void TSC_IRQHandler(void) {
    if(TSC->ISR & TSC_ISR_EOAF) {
        if(TSC->IOGXCR[1] > current_key.tuned){
            GPIOA->ODR |= 1 << 5;
        }else{
            GPIOA->ODR &= ~(1 << 5);
        } 
    }
    // disable the current key
    disable_key(&current_key);
    // Clear the interrupts
    TSC->ICR |= TSC_ICR_EOAIC;
}


void SysTick_init(void){
    SysTick->CTRL = 0;
    // Curremt clock speed is 4MHz, LOAD at 2000 means every .5 ms
    SysTick->LOAD = 2000 - 1;

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
        
