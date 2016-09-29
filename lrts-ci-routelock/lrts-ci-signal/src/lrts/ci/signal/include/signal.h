#ifndef _SIGNAL_H
#define _SIGNAL_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief �����źŻ����̣�
*
* @param signal_id �źŻ�ָ��
* @param dis    ���õ�ɫ
*
* @return  �ɹ�/ʧ��
*/
int16_t signal_set_grn(msg_t m, void *p);
/**
* @brief �����źŻ����
*
* @param
*
* @return
*/
int16_t signal_set_red(msg_t m, void *p);
/**
* @brief ��ȡ�źŻ�״̬����ɫ����˿������/��⣩
*
* @param signal_id �źŻ�ָ��
*
* @return  ��ɫ����˿������/���
*/
int16_t signal_get_status(uint32_t signal_id);

/**
* @brief ����Ƶ�˿
*
* @param signal_id �źŻ�ָ��
*
* @return  ��/��
*/
int16_t signal_check_gob_red(uint32_t signal_id);

/**
* @brief ����˿�û������е�˿��
*
* @param signal_id �źŻ�ָ��
*
* @return  ��/��
*/
int16_t signal_check_gob(uint32_t signal_id);

/**
* @brief ����źŻ���ʾ
*
* @param signal_id �źŻ�ָ��
* @param color     ��Ҫ��ʾ�ĵ�ɫ
*
* @return  ��ȷ/����
*/
int16_t signal_check_dis(uint32_t signal_id, uint16_t color);

/**
* @brief ����/�ر��źŻ����졢�̡��Ƶȣ�
*
* @param signal_id �źŻ�ָ��
* @param dis       ���õ�ɫ
*
* @return  �ɹ�/ʧ��
*/
int16_t signal_set_dis(uint32_t signal_id, uint16_t dis);

/**
* @brief ����/���
*
* @param signal_id �źŻ�ָ��
* @param command   ������/���
*
* @return  �ɹ�/ʧ��
*/
int16_t signal_set_light(uint32_t signal_id, uint16_t command);

/**
* @brief �źŻ�����/���
*
* @param signal_id �źŻ�ָ��
* @param command   ���÷���/���
*
* @return  �ɹ�/ʧ��
*/
int16_t signal_set_trackade(uint32_t signal_id, uint16_t command);

/**
* @brief �˹������źŻ����졢�̡��Ƶȣ�
*
* @param signal_id �źŻ�ָ��
* @param dis       ���õ�ɫ����/�𡢷���/���
*
* @return  �ɹ�/ʧ��
*/
int16_t signal_manu_set(uint32_t signal_id, uint16_t command);

#ifdef __cplusplus
}
#endif

#endif
