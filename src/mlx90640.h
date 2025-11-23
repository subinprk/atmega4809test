#ifndef MLX90640_H
#define MLX90640_H
#include <avr/io.h>

#define MLX_ADDR 0x33

//======== TWI (I2C) function prototypes ========
void TWI0_init(void);
uint8_t TWI0_start(uint8_t address);
void TWI0_stop(void);
uint8_t TWI0_write(uint8_t data);
uint8_t TWI0_read_ack(void);
uint8_t TWI0_read_nack(void);

//======== MLX90640 function prototypes ========
uint16_t MLX_read16(uint16_t reg);
void debug_MLX_read16(uint16_t reg);

#endif // MLX90640_H