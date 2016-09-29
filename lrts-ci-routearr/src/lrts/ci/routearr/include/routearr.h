#ifndef _ROUTE_ARRANGE_H
#define _ROUTE_ARRANGE_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

#define R_OK    0
#define R_ERROR -1


/**
 * @brief ����·����
 *
 * @param track_id 	����ָ��
 * @param number 	  ��������
 *
 * @return ����/�ܾ�
 */
int32_t track_check(track_t *track_list, uint32_t number);

/**
 * @brief ����·�źŻ�
 *
 * @param signal_id  �źŻ�ָ��
 *
 * @return ����/�ܾ�
 */
int32_t signal_check(signal_t *signal_id);

/**
 * @brief ����·ѡ·����
 *
 * @param route_id 	��·ָ��
 *
 * @return ����/�ܾ�
 */
int32_t route_choose_check(route_t *route_id);

/**
 * @brief ���Ժ���
 *	      �Ѵ����*g_route, *g_track, *g_signalȫ�ֻ�
 *
 * @param *route 	  ��·ָ��
 * @param *track 	  ����ָ��
 * @param *signal 	�źŻ�ָ��
 *
 * @return �ɹ�/ʧ��
 */
int32_t main_test(route_t *route, track_t *track, signal_t *signal);




#ifdef __cplusplus
}
#endif

#endif
