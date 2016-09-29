/** 
 * @file ver_loop.c
 * @brief 
 * @author dingjian
 * @date 2016-09-23
 * 
 * $Id$
 */

#include "ci_public_comm.h"

/**
===Change Log of module===

 v0.1.0 dingjian

=====End of change log====
*/

/**
 * 定义静态全局变量
 */
static track_t g_track_old[TRACK_NUM];
static route_t g_route_old[ROUTE_NUM];
static signal_t g_signal_old[SIGNAL_NUM];

int16_t backup_g()
{
	memcpy(g_track_old, g_track, sizeof(track_t)*TRACK_NUM);
	memcpy(g_route_old, g_route, sizeof(route_t)*ROUTE_NUM);
	memcpy(g_signal_old, g_signal, sizeof(signal_t)*SIGNAL_NUM);
	return RET_SUCCESS;
}

int16_t make_message(uint8_t device_type, uint8_t device_id, uint16_t event)
{
	int16_t ret = 0;
	ret = (device_type<<24) + (device_id<<16) + event;
	return ret;
}

int16_t send_message(msg_t m)
{
	//OSQPost();
	return RET_SUCCESS;
}

int16_t check_device_status()
{
	uint8_t i;
	int16_t ret = 0;
	uint8_t status = 0;

	/**
	 * check track: send_message(make_message(DEVICE_TRACK, i, ));
	 */
	for (i = 0; i <= TRACK_NUM; i++) {
		status = g_route[g_track[i].t_r_id].r_status;
		if (g_track_old[i].t_status != g_track[i].t_status) {
			switch (status) {
			case SMOD_CI_R_UNLOCK:
				send_message(make_message(DEVICE_TRACK, i, CI_R_UNLOCK_SELLECT));
				break;
			case SMOD_CI_R_ARRAY:
				break;
			case SMOD_CI_R_ADVLOCK:
				send_message(make_message(DEVICE_TRACK, i, CI_R_ADVLOCK_APPLOCK));
				send_message(make_message(DEVICE_TRACK, i, CI_R_ADVLOCK_FAULTLOCK));
				break;
			case SMOD_CI_R_APPLOCK:
				send_message(make_message(DEVICE_TRACK, i, CI_R_APPLOCK_FRONTOCCUPY));
				send_message(make_message(DEVICE_TRACK, i, CI_R_APPLOCK_FAULTLOCK));
				break;
			case SMOD_CI_R_OCCUPY:
				send_message(make_message(DEVICE_TRACK, i, CI_R_OCCUPY_CLEANSUCC));
				break;
			case SMOD_CI_R_CLEAN:
				send_message(make_message(DEVICE_TRACK, i, CI_R_CLEAN_CLEAN));
				break;
			default:
				break;
			}
		}
	}
	backup_g();
	return RET_SUCCESS;
}

/** 
 * @brief main_loop 主循环的主函数
 * 
 * @param
 * 
 * @return 
 */
int16_t main_loop()
{
	check_device_status();
	return RET_SUCCESS;
}

int16_t stub_fun(msg_t m, void *p)
{
	return RET_SUCCESS;
}

