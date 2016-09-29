#ifndef _ROUTE_OPEN_H
#define _ROUTE_OPEN_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif


/*
* @brief ���ο��������ռ��
*
* @param track_id   ����id
*
* @return ��������״̬1/0
*/
int16_t track_lock_check2(uint32_t track_id);


/**
* @brief ��·���ż��
*
* @param route_id   ��·ָ��
*
* @return ����/�ܾ�
*/
int16_t route_open_check(uint32_t route_id);

/**
* @brief ��·����
*        ��Ϣ�������жϽ�·FSMΪԤ�����գ��ټ����������, �������ý�·FSMΪ��·����
*
* @param route_id   ��·ָ��
*
* @return �ɹ�/ʧ��
*/
int16_t route_open(uint32_t route_id);


#ifdef __cplusplus
}
#endif

#endif
