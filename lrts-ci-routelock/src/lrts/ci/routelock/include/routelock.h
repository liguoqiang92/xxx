#ifndef _ROUTE_LOCK_H
#define _ROUTE_LOCK_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif



/**
* @brief 进路预先锁闭
*        锁闭进路内所有区段、道岔；并不断检查是否完成，完成后置进路FSM为预先锁闭，并触发锁闭保护区段。
*
* @param route_id   进路指针
*
* @return 成功/失败
*/
int16_t route_lock_advance(msg_t m, void *p);

/**
* @brief 进路接近锁闭
*        消息触发，检查进路FSM，若为进路开放，设置进路FSM为接近锁闭
*
* @param route_id   进路指针
*
* @return 成功/失败
*/
int16_t route_lock_prox(msg_t m, void *p);


#ifdef __cplusplus
}
#endif

#endif
