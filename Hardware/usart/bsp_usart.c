/********************************************************************************
 * 文 件 名: bsp_usart.c
 * 版 本 号: 初版
 * 修改作者: LC
 * 修改日期: 2022年04月14日
 * 功能介绍:
 ******************************************************************************
 * 注意事项:
 *********************************************************************************/

#include "bsp_usart.h"
#include "stdio.h"

/************************************************
函数名称 ： usart_gpio_config
功    能 ： 串口配置GPIO
参    数 ： band_rate:波特率
返 回 值 ： 无
作    者 ： LC
*************************************************/
void usart_gpio_config(uint32_t band_rate)
{
    /* 开启时钟 */
    rcu_periph_clock_enable(BSP_USART_TX_RCU); // 开启串口时钟
    rcu_periph_clock_enable(BSP_USART_RX_RCU); // 开启端口时钟
    rcu_periph_clock_enable(BSP_USART_RCU);    // 开启端口时钟

    /* 配置GPIO复用功能 */
    gpio_af_set(BSP_USART_TX_PORT, BSP_USART_AF, BSP_USART_TX_PIN);
    gpio_af_set(BSP_USART_RX_PORT, BSP_USART_AF, BSP_USART_RX_PIN);

    /* 配置GPIO的模式 */
    /* 配置TX为复用模式 上拉模式 */
    gpio_mode_set(BSP_USART_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_TX_PIN);
    /* 配置RX为复用模式 上拉模式 */
    gpio_mode_set(BSP_USART_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_RX_PIN);

    /* 配置TX为推挽输出 50MHZ */
    gpio_output_options_set(BSP_USART_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_TX_PIN);
    /* 配置RX为推挽输出 50MHZ */
    gpio_output_options_set(BSP_USART_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_RX_PIN);

    /* 配置串口的参数 */
    usart_deinit(BSP_USART);                         // 复位串口
    usart_baudrate_set(BSP_USART, band_rate);        // 设置波特率
    usart_parity_config(BSP_USART, USART_PM_NONE);   // 没有校验位
    usart_word_length_set(BSP_USART, USART_WL_8BIT); // 8位数据位
    usart_stop_bit_set(BSP_USART, USART_STB_1BIT);   // 1位停止位

    /* 使能串口 */
    usart_enable(BSP_USART);                                 // 使能串口
    usart_transmit_config(BSP_USART, USART_TRANSMIT_ENABLE); // 使能串口发送
}

/************************************************
函数名称 ： usart_send_data
功    能 ： 串口重发送一个字节
参    数 ： ucch：要发送的字节
返 回 值 ：
作    者 ： LC
*************************************************/
void usart_send_data(uint8_t ucch)
{
    usart_data_transmit(BSP_USART, (uint8_t)ucch); // 发送数据
    while (RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE))
        ; // 等待发送数据缓冲区标志置位
}

/************************************************
函数名称 ： usart_send_String
功    能 ： 串口发送字符串
参    数 ： ucstr:要发送的字符串
返 回 值 ：
作    者 ： LC
*************************************************/
void usart_send_string(uint8_t *ucstr)
{
    while (ucstr && *ucstr) // 地址为空或者值为空跳出
    {
        usart_send_data(*ucstr++); // 发送单个字符
    }
}

/************************************************
函数名称 ： fputc
功    能 ： 串口重定向函数
参    数 ：
返 回 值 ：
作    者 ： LC
*************************************************/
int fputc(int ch, FILE *f)
{
    usart_send_data(ch);
    // 等待发送数据缓冲区标志置位
    return ch;
}
