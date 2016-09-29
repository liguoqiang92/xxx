#ifndef _ROUTE_LOCK_H
#define _ROUTE_LOCK_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif



/**
* @brief ��·Ԥ������
*        ���ս�·���������Ρ����������ϼ���Ƿ���ɣ���ɺ��ý�·FSMΪԤ�����գ����������ձ������Ρ�
*
* @param route_id   ��·ָ��
*
* @return �ɹ�/ʧ��
*/
int16_t route_lock_advance(msg_t m, void *p);

/**
* @brief ��·�ӽ�����
*        ��Ϣ����������·FSM����Ϊ��·���ţ����ý�·FSMΪ�ӽ�����
*
* @param route_id   ��·ָ��
*
* @return �ɹ�/ʧ��
*/
int16_t route_lock_prox(msg_t m, void *p);


#ifdef __cplusplus
}
#endif

#endif
