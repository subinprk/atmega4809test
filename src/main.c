#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "mlx90640.h"

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
    TWI0_init();

    USART1_sendString("MLX90640 TEST START\r\n");
    TWI0_debug_status();
    TWI0_scan();  // 한 번만 스캔
    
    _delay_ms(100);  // 스캔 후 안정화


    while (1)
    {
        // Blink LED
        PORTA.OUTTGL = PIN7_bm;
        
        //========UART Echo Test========//
        // Echo received characters
        // if (USART1.STATUS & USART_RXCIF_bm)
        // {
        //     char c = USART1_readChar();
        //     USART1_sendChar(c);
        // }
        

        //========MLX90640 Read Test========//
        TWI0_reset_bus();  // 읽기 전 버스 리셋
        
        USART1_sendString("Device ID: ");
        debug_MLX_read16(0x2407);  // Device ID
        
        USART1_sendString("Status Reg: ");
        debug_MLX_read16(0x240D);  // Status (0x0000 정상)
        
        USART1_sendString("RAM pixel[0]: ");
        debug_MLX_read16(0x0400);  // RAM 첫 픽셀
        
        USART1_sendString("RAM pixel[100]: ");
        debug_MLX_read16(0x0464);  // RAM 중간 픽셀
        
        _delay_ms(2000);  // 2초마다 읽기
    }
}