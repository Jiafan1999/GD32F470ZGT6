#include "bsp_spi_flash.h"
#include "gd32f4xx.h"

void init_spi_flash(void)
{
    printf("START INIT SPI...\r\n");

    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_SPI4);

    gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_7);
    gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_8);
    gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_9);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);

    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    rcu_periph_clock_enable(RCU_GPIOF);
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_bit_write(GPIOF, GPIO_PIN_6, SET);

    spi_parameter_struct spi_init_data;
    spi_init_data.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_data.device_mode = SPI_MASTER;
    spi_init_data.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_data.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_data.nss = SPI_NSS_SOFT;
    spi_init_data.prescale = SPI_PSC_2;
    spi_init_data.endian = SPI_ENDIAN_MSB;
    spi_init(SPI4, &spi_init_data);
    spi_enable(SPI4);

    printf("SPI INIT DONE!\r\n");
}

uint8_t spi_read_write_byte(uint8_t data)
{
    while (spi_i2s_flag_get(SPI4, SPI_FLAG_TBE) == RESET)
        ;
    spi_i2s_data_transmit(SPI4, data);

    while (spi_i2s_flag_get(SPI4, SPI_FLAG_RBNE) == RESET)
        ;
    return spi_i2s_data_receive(SPI4);
}

uint16_t W25Q64_readID(void)
{

    uint16_t temp = 0;
    gpio_bit_write(GPIOF, GPIO_PIN_6, RESET);

    spi_read_write_byte(0x90);
    spi_read_write_byte(0x00);
    spi_read_write_byte(0x00);
    spi_read_write_byte(0x00);
    temp |= spi_read_write_byte(0x00) << 8;
    temp |= spi_read_write_byte(0x00);
    gpio_bit_write(GPIOF, GPIO_PIN_6, SET);

    return temp;
}
