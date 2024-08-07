#include "bsp_led.h"
#include "gd32f4xx_dac.h"

/************************************************
函数名称 ： led_gpio_config
功    能 ： led灯gpio引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void led_gpio_config(void)
{
	/* 使能时钟 */
	rcu_periph_clock_enable(RCU_LED2);
	rcu_periph_clock_enable(RCU_LED4);

	/* 配置为输出模式 浮空模式 */
	gpio_mode_set(PORT_LED2, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED2);

	gpio_mode_set(PORT_LED4, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_LED4);
	/* 配置为推挽输出 50MHZ */
	gpio_output_options_set(PORT_LED2, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED2);

	gpio_output_options_set(PORT_LED4, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED4);

	rcu_periph_clock_enable(RCU_DAC);
	dac_deinit();
	dac_trigger_disable(DAC1);
	dac_wave_mode_config(DAC1, DAC_WAVE_DISABLE);
	dac_output_buffer_enable(DAC1);
	dac_enable(DAC1);

}
