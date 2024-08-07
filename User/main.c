/********************************************************************************
 * 文 件 名: main.c
 * 版 本 号: 初版
 * 修改作者: LC
 * 修改日期: 2022年04月12日
 * 功能介绍:
 ******************************************************************************
 * 注意事项:
 *********************************************************************************/

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"

/************************************************
函数名称 ： main
功    能 ： 主函数
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
int main(void)
{
  systick_config();         // 滴答定时器初始化
  led_gpio_config();        // led初始化
  usart_gpio_config(9600U); // 串口0初始化
  init_spi_flash();
  while (1)
  {

    // printf("Try read Flash ID\r\n");
    delay_1ms(10);
    uint16_t id = W25Q64_readID();

    printf("FLASH MANUFACURE ID: %X\r\n", id >> 8);
    printf("FLASH DEVICE ID: %X\r\n", id & 0xFF);
    delay_1ms(1000);
    // gpio_bit_write(PORT_LED4, PIN_LED4, SET); // LED2输出高电平
    // delay_1ms(1000);
    // gpio_bit_write(PORT_LED4, PIN_LED4, RESET); // LED2输出高电平
    // delay_1ms(1000);
  }
}
