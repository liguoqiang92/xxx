#ifndef  _PLAT_SUPPORT_H
#define  _PLAT_SUPPORT_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file unifw_plat.h
 * @brief 
 * @author 003
 * @version 
 * @date 2016-06-05
 */

/**
 * ==========================
 * 提供BSP函数
 * ==========================
 */

void bsp_can_init(uint16_t port);

uint8_t bsp_can_send(uint16_t port, uint8_t *id, uint8_t *data, uint16_t len);

uint8_t bsp_can_get(uint16_t port, uint8_t *id, uint8_t *data,uint8_t *n);

/*================== SPI函数 =========================*/
/**
 * @brief bsp_spi_send 通过平台发送SPI数据
 *
 * @param port 待发送端口号
 * @param data 数据对应buffer
 * @param len  数据长度
 */
void bsp_spi_send(uint16_t port, uint8_t *data, uint16_t len);

void bsp_spi_sendbyte(uint16_t port, uint8_t data);

uint8_t bsp_spi_getbyte(uint16_t port);

int8_t bsp_spi_get(uint16_t port, uint8_t *data, uint16_t len);


void bsp_uart_init(uint16_t port);

uint8_t bsp_uart_send(uint16_t port, uint8_t *id, uint8_t *data, uint16_t len);

uint8_t bsp_uart_get(uint16_t port, uint8_t *id, uint8_t *data,uint8_t *n);

void bsp_udp_send_byaddr(uint16_t offset, uint8_t *addr, uint16_t port, uint8_t *src, uint16_t len);

/**
 * ==========================
 * 提供平台初始化函数
 * ==========================
 */

void plat_init(void);

/**
 * @brief plat_launch 提供平台启动函数
 */
void plat_launch(void);

/**
 * @brief plat_parse_config 提供平台解析函数
 *
 * @param argc 输入参数数量
 * @param argv[]	参数列表
 */
void plat_parse_config(int argc, const char * argv[]);

/**
 * ==========================
 * 提供平台外设函数
 * ==========================
 */

/**
 * @brief plat_get_io_buff 获取外部的IO buffer
 *
 * @param buff 用于存储IO变量的buff
 *
 * @return 更新的字节数
 */
int16_t plat_dio_get(uint8_t *buff);

/**
 * @brief plat_set_io 设置外部的IO
 *
 * @param group IO的组号
 * @param value IO的数值
 *
 * @return 返回读取的IO数值
 */
int16_t plat_dout_set(uint8_t group, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif   /*_PLAT_SUPPORT_H*/

