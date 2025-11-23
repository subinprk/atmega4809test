#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    // Select 20 MHz internal oscillator and disable prescaler (but runs at 16MHz effectively)
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc);
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0);
    //Subin: I've checked this but oddly if I did't define clock here again with Oscillator
    //it did not work even though I defined F_CPU in Makefile.
    //Ahaaaa...GPT said me if I don't do this here
    //MCU it's actually running at 3.33MHz which is default internal clock.
    _delay_ms(100); // Wait for clock to stabilize
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
        //USART1_sendString("Hello, UART!\r\n");
        
        

        _delay_ms(500);
    }
}