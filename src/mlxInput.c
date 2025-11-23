#include "mlx90640.h"
#include "uart.h"
#include <stdio.h>

uint16_t MLX_read16(uint16_t reg)
{
    uint8_t hi, lo;
    uint8_t result;

    // Write register address
    result = TWI0_start((MLX_ADDR << 1) | 0);
    if (!result) {
        USART1_sendString("START WRITE FAIL\r\n");
        TWI0_stop();
        return 0xFFFF;
    }
    
    result = TWI0_write(reg >> 8);
    if (!result) {
        USART1_sendString("WRITE HIGH FAIL\r\n");
        TWI0_stop();
        return 0xFFFF;
    }
    
    result = TWI0_write(reg & 0xFF);
    if (!result) {
        USART1_sendString("WRITE LOW FAIL\r\n");
        TWI0_stop();
        return 0xFFFF;
    }

    // NO STOP - use Repeated START for read
    result = TWI0_start((MLX_ADDR << 1) | 1);
    if (!result) {
        USART1_sendString("START READ FAIL\r\n");
        TWI0_stop();
        return 0xFFFF;
    }
    
    hi = TWI0_read_ack();
    lo = TWI0_read_nack();
    // TWI0_stop();  // ← read_nack에서 이미 STOP 보냄

    return (hi << 8) | lo;
}

void debug_MLX_read16(uint16_t reg)
{
    uint16_t value = MLX_read16(reg);
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Reg 0x%04X: 0x%04X\r\n", reg, value);
    USART1_sendString(buffer);
}