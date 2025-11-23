#include "mlx90640.h"

void TWI0_init(void)
{
    // SDA = PA2, SCL = PA3
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;

    // 400 kHz → MBAUD = (F_CPU/(2*SCL)) - 5
    // 20MHz → MBAUD = (20,000,000 / 800,000) - 5 = 20
    TWI0.MBAUD = 20;

    TWI0.MCTRLA = TWI_ENABLE_bm;
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

uint8_t TWI0_start(uint8_t address)
{
    TWI0.MADDR = address;
    while (!(TWI0.MSTATUS & (TWI_WIF_bm | TWI_RIF_bm)));
    return !(TWI0.MSTATUS & TWI_RXACK_bm);
}

void TWI0_stop(void)
{
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
}

uint8_t TWI0_write(uint8_t data)
{
    TWI0.MDATA = data;
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    return !(TWI0.MSTATUS & TWI_RXACK_bm);
}

uint8_t TWI0_read_ack(void)
{
    TWI0.MCTRLB = TWI_ACKACT_ACK_gc | TWI_MCMD_RECVTRANS_gc;
    while (!(TWI0.MSTATUS & TWI_RIF_bm));
    return TWI0.MDATA;
}

uint8_t TWI0_read_nack(void)
{
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_RECVTRANS_gc;
    while (!(TWI0.MSTATUS & TWI_RIF_bm));
    return TWI0.MDATA;
}