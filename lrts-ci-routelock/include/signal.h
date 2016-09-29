#ifndef _SIGNAL_H
#define _SIGNAL_H

#include "ci_public_comm.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief 开放信号机（绿）
*
* @param signal_id 信号机指针
* @param dis    设置灯色
*
* @return  成功/失败
*/
int16_t signal_set_grn(msg_t m, void *p);
/**
* @brief 设置信号机红灯
*
* @param
*
* @return
*/
int16_t signal_set_red(msg_t m, void *p);
/**
* @brief 获取信号机状态（灯色、灯丝、封锁/解封）
*
* @param signal_id 信号机指针
*
* @return  灯色、灯丝、封锁/解封
*/
int16_t signal_get_status(uint32_t signal_id);

/**
* @brief 检查红灯灯丝
*
* @param signal_id 信号机指针
*
* @return  好/坏
*/
int16_t signal_check_gob_red(uint32_t signal_id);

/**
* @brief 检查灯丝好坏（所有灯丝）
*
* @param signal_id 信号机指针
*
* @return  好/坏
*/
int16_t signal_check_gob(uint32_t signal_id);

/**
* @brief 检查信号机显示
*
* @param signal_id 信号机指针
* @param color     需要显示的灯色
*
* @return  正确/错误
*/
int16_t signal_check_dis(uint32_t signal_id, uint16_t color);

/**
* @brief 开放/关闭信号机（红、绿、黄等）
*
* @param signal_id 信号机指针
* @param dis       设置灯色
*
* @return  成功/失败
*/
int16_t signal_set_dis(uint32_t signal_id, uint16_t dis);

/**
* @brief 亮灯/灭灯
*
* @param signal_id 信号机指针
* @param command   设置亮/灭灯
*
* @return  成功/失败
*/
int16_t signal_set_light(uint32_t signal_id, uint16_t command);

/**
* @brief 信号机封锁/解封
*
* @param signal_id 信号机指针
* @param command   设置封锁/解封
*
* @return  成功/失败
*/
int16_t signal_set_trackade(uint32_t signal_id, uint16_t command);

/**
* @brief 人工操作信号机（红、绿、黄等）
*
* @param signal_id 信号机指针
* @param dis       设置灯色、亮/灭、封锁/解封
*
* @return  成功/失败
*/
int16_t signal_manu_set(uint32_t signal_id, uint16_t command);

#ifdef __cplusplus
}
#endif

#endif
