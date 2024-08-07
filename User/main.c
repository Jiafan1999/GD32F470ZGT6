/********************************************************************************
 * �� �� ��: main.c
 * �� �� ��: ����
 * �޸�����: LC
 * �޸�����: 2022��04��12��
 * ���ܽ���:
 ******************************************************************************
 * ע������:
 *********************************************************************************/

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"

/************************************************
�������� �� main
��    �� �� ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
int main(void)
{
  systick_config();         // �δ�ʱ����ʼ��
  led_gpio_config();        // led��ʼ��
  usart_gpio_config(9600U); // ����0��ʼ��
  init_spi_flash();
  while (1)
  {

    // printf("Try read Flash ID\r\n");
    delay_1ms(10);
    uint16_t id = W25Q64_readID();

    printf("FLASH MANUFACURE ID: %X\r\n", id >> 8);
    printf("FLASH DEVICE ID: %X\r\n", id & 0xFF);
    delay_1ms(1000);
    // gpio_bit_write(PORT_LED4, PIN_LED4, SET); // LED2����ߵ�ƽ
    // delay_1ms(1000);
    // gpio_bit_write(PORT_LED4, PIN_LED4, RESET); // LED2����ߵ�ƽ
    // delay_1ms(1000);
  }
}
