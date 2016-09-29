#ifndef _PUBLICK_ARR_H
#define _PUBLICK_ARR_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief ��·ѡ·
 * @param s_start_id 	ʼ���źŻ�ID
 * @param s_end_id 	  �ն��źŻ�ID
 *
 * @return ��·ID/ʧ��
 */
int32_t route_choose(msg_t m, void *p);

/**
 * @brief ��·��·
 *	      �⶯���������ϼ�������Ƿ�����(ͬѡ·���)
 *
 * @param route_id 	��·ָ��
 *
 * @return �ɹ�/ʧ��
 */
int32_t route_arrange(msg_t m, void *p);

#ifdef __cplusplus
}
#endif

#endif
