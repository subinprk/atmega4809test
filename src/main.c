#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    // Select 16 MHz internal oscillator and disable prescaler
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc);
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0);
    
    // LED blink on PA7 to confirm MCU runs
    PORTA.DIRSET = PIN7_bm;
    
    USART1_init();

    while (1)
    {
        // Blink LED
        PORTA.OUTTGL = PIN7_bm;
        
        // Send single character (simpler than string)
        // USART1_sendChar('H');
        // USART1_sendChar('\r');
        // USART1_sendChar('\n');
        
        // Echo received characters
        if (USART1.STATUS & USART_RXCIF_bm)
        {
            char c = USART1_readChar();
            USART1_sendChar(c);
        }

        _delay_ms(500);
    }
}