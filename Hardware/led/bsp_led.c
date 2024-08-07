#include "bsp_led.h"
#include "gd32f4xx_dac.h"

/************************************************
�������� �� led_gpio_config
��    �� �� led��gpio��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void led_gpio_config(void)
{
	/* ʹ��ʱ�� */
	rcu_periph_clock_enable(RCU_LED2);
	rcu_periph_clock_enable(RCU_LED4);

	/* ����Ϊ���ģʽ ����ģʽ */
	gpio_mode_set(PORT_LED2, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED2);

	gpio_mode_set(PORT_LED4, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_LED4);
	/* ����Ϊ������� 50MHZ */
	gpio_output_options_set(PORT_LED2, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED2);

	gpio_output_options_set(PORT_LED4, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED4);

	rcu_periph_clock_enable(RCU_DAC);
	dac_deinit();
	dac_trigger_disable(DAC1);
	dac_wave_mode_config(DAC1, DAC_WAVE_DISABLE);
	dac_output_buffer_enable(DAC1);
	dac_enable(DAC1);

}
