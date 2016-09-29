#ifndef _PUBLICK_ARR_H
#define _PUBLICK_ARR_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief 进路选路
 * @param s_start_id 	始端信号机ID
 * @param s_end_id 	  终端信号机ID
 *
 * @return 进路ID/失败
 */
int32_t route_choose(msg_t m, void *p);

/**
 * @brief 进路排路
 *	      扳动道岔，并不断检测条件是否满足(同选路检查)
 *
 * @param route_id 	进路指针
 *
 * @return 成功/失败
 */
int32_t route_arrange(msg_t m, void *p);

#ifdef __cplusplus
}
#endif

#endif
