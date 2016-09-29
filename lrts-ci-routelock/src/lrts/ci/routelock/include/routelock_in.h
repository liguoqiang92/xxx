#ifndef _ROUTE_LOCK_IN_H
#define _ROUTE_LOCK_IN_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif


/**
* @brief ��������
*
* @param block_id   ����ָ��
*
* @return ������������
*/
int16_t track_lock(uint32_t track_id);

int16_t track_lock_check(uint32_t track_id);



/**
* @brief ��·Ԥ�������������
*
* @param route_id  ��·ָ��
*
* @return ����/�ܾ�
*/
int16_t route_lock_advance_check(uint32_t route_id);




#ifdef __cplusplus
}
#endif

#endif
