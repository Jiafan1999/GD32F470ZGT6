#ifndef _BSP_SPI_FLASH_H
#define _BSP_SPI_FLASH_H

#include "gd32f4xx.h"

void init_spi_flash(void);
uint8_t spi_read_write_byte(uint8_t data);
uint16_t W25Q64_readID(void);

#endif
