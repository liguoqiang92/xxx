#ifndef _ROUTE_LOCK_IN_H
#define _ROUTE_LOCK_IN_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif


/**
* @brief 区段锁闭
*
* @param block_id   区段指针
*
* @return 区段锁闭设置
*/
int16_t track_lock(uint32_t track_id);

int16_t track_lock_check(uint32_t track_id);



/**
* @brief 进路预先锁闭条件检查
*
* @param route_id  进路指针
*
* @return 允许/拒绝
*/
int16_t route_lock_advance_check(uint32_t route_id);




#ifdef __cplusplus
}
#endif

#endif
