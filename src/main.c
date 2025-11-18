#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void USART3_init(void);
void USART3_sendChar(char c);
unsigned char USART3_receiveChar(void);

#define BAUD_RATE 9600
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void USART3_init(void)
{
    PORTA.DIRSET = PIN0_bm;
    PORTA.DIRCLR = PIN1_bm;

    USART3.BAUD = (uint16_t)USART0_BAUD_RATE(BAUD_RATE);
    USART3.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART3_sendChar(char c)
{
    while (!(USART3.STATUS & USART_DREIF_bm));
    USART3.TXDATAL = c;
}

unsigned char USART3_receiveChar(void)
{
    while (!(USART3.STATUS & USART_RXCIF_bm));
    return USART3.RXDATAL;
}

int main(void)
{

    USART3_init();

        const char *msg = "Hello from MCU\r\n";
    while (1)
    {
        const char *p = msg;
        while (*p) {
            USART3_sendChar(*p++);
        }
        _delay_ms(1000);
    }

    while (1)
    {
        char receivedChar = USART3_receiveChar();
        USART3_sendChar(receivedChar); // 수신한 문자를 다시 전송 (에코)
    }
    // 예: PORTB5을 출력으로 설정
    // PORTA.DIRSET = PIN7_bm;

    // while (1) {
    //     PORTA.OUTTGL = PIN7_bm;
    //     _delay_ms(500);
    // }
}
