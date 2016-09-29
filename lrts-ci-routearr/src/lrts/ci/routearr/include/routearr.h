#ifndef _ROUTE_ARRANGE_H
#define _ROUTE_ARRANGE_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

#define R_OK    0
#define R_ERROR -1


/**
 * @brief 检查进路区段
 *
 * @param track_id 	区段指针
 * @param number 	  区段数量
 *
 * @return 允许/拒绝
 */
int32_t track_check(track_t *track_list, uint32_t number);

/**
 * @brief 检查进路信号机
 *
 * @param signal_id  信号机指针
 *
 * @return 允许/拒绝
 */
int32_t signal_check(signal_t *signal_id);

/**
 * @brief 检查进路选路条件
 *
 * @param route_id 	进路指针
 *
 * @return 允许/拒绝
 */
int32_t route_choose_check(route_t *route_id);

/**
 * @brief 测试函数
 *	      把传入的*g_route, *g_track, *g_signal全局化
 *
 * @param *route 	  进路指针
 * @param *track 	  区段指针
 * @param *signal 	信号机指针
 *
 * @return 成功/失败
 */
int32_t main_test(route_t *route, track_t *track, signal_t *signal);




#ifdef __cplusplus
}
#endif

#endif
