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
 * �ṩBSP����
 * ==========================
 */

void bsp_can_init(uint16_t port);

uint8_t bsp_can_send(uint16_t port, uint8_t *id, uint8_t *data, uint16_t len);

uint8_t bsp_can_get(uint16_t port, uint8_t *id, uint8_t *data,uint8_t *n);

/*================== SPI���� =========================*/
/**
 * @brief bsp_spi_send ͨ��ƽ̨����SPI����
 *
 * @param port �����Ͷ˿ں�
 * @param data ���ݶ�Ӧbuffer
 * @param len  ���ݳ���
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
 * �ṩƽ̨��ʼ������
 * ==========================
 */

void plat_init(void);

/**
 * @brief plat_launch �ṩƽ̨��������
 */
void plat_launch(void);

/**
 * @brief plat_parse_config �ṩƽ̨��������
 *
 * @param argc �����������
 * @param argv[]	�����б�
 */
void plat_parse_config(int argc, const char * argv[]);

/**
 * ==========================
 * �ṩƽ̨���躯��
 * ==========================
 */

/**
 * @brief plat_get_io_buff ��ȡ�ⲿ��IO buffer
 *
 * @param buff ���ڴ洢IO������buff
 *
 * @return ���µ��ֽ���
 */
int16_t plat_dio_get(uint8_t *buff);

/**
 * @brief plat_set_io �����ⲿ��IO
 *
 * @param group IO�����
 * @param value IO����ֵ
 *
 * @return ���ض�ȡ��IO��ֵ
 */
int16_t plat_dout_set(uint8_t group, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif   /*_PLAT_SUPPORT_H*/

