#include "mlx90640.h"
#include "uart.h"
#include <stdio.h>

uint16_t MLX_read16(uint16_t reg)
{
    uint8_t hi, lo;

    // Write register address
    TWI0_start((MLX_ADDR << 1) | 0);
    TWI0_write(reg >> 8);
    TWI0_write(reg & 0xFF);

    // Restart and read
    TWI0_start((MLX_ADDR << 1) | 1);
    hi = TWI0_read_ack();
    lo = TWI0_read_nack();
    TWI0_stop();

    return (hi << 8) | lo;
}

void debug_MLX_read16(uint16_t reg)
{
    uint16_t value = MLX_read16(reg);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Reg 0x%04X: 0x%04X\r\n", reg, value);
    USART1_sendString(buffer);
}