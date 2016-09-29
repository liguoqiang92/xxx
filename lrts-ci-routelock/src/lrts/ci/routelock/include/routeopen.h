#ifndef _ROUTE_OPEN_H
#define _ROUTE_OPEN_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif


/*
* @brief 区段空闲且锁闭检查
*
* @param track_id   区段id
*
* @return 区段锁闭状态1/0
*/
int16_t track_lock_check2(uint32_t track_id);


/**
* @brief 进路开放检查
*
* @param route_id   进路指针
*
* @return 允许/拒绝
*/
int16_t route_open_check(uint32_t route_id);

/**
* @brief 进路开放
*        消息触发，判断进路FSM为预先锁闭，再检查其他条件, 满足设置进路FSM为进路开放
*
* @param route_id   进路指针
*
* @return 成功/失败
*/
int16_t route_open(uint32_t route_id);


#ifdef __cplusplus
}
#endif

#endif
