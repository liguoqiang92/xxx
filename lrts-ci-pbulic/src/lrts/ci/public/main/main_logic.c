/** 
 * @file main_logic.c
 * @brief 
 * @author dingjian
 * @date 2016-09-23
 * 
 * $Id$
 */

#include "ci_public_comm.h"
#include "base/fsm.h"

/**
===Change Log of module===

 v0.1.0 dingjian

=====End of change log====
*/

/*******************************************************************************
 * 状态机
 *
 ******************************************************************************/
/**
 * @brief CI_R_UNLOCK模式核心层消息表
 */
static const fsm_convert_t ci_r_unlock_core_tbl[]= 
{
	{CI_R_UNLOCK_SELLECT, SMOD_CI_R_ARRAY, stub_fun}
};

static const fsm_convert_t ci_r_array_core_tbl[]=
{
	{CI_R_ARRAY_SUCC, SMOD_CI_R_ADVLOCK, stub_fun/*route_arrange*/},
	{CI_R_ARRAY_FAIL, SMOD_CI_R_UNLOCK, stub_fun/*route_fail*/},
	{CI_R_ARRAY_READY, SMOD_CI_R_ADVLOCK, stub_fun/*route_lock_advance*/}
};

static const fsm_convert_t ci_r_advlock_core_tbl[]=
{
	{CI_R_ADVLOCK_CANCEL, SMOD_CI_R_UNLOCK, stub_fun/*route_cancel*/},
	{CI_R_ADVLOCK_APPLOCK, SMOD_CI_R_APPLOCK, stub_fun/*route_lock_prox*/},
	{CI_R_ADVLOCK_FAULTLOCK, SMOD_CI_R_ADVLOCK, stub_fun/*track_unlock_manu*/},
};

static const fsm_convert_t ci_r_applock_core_tbl[]=
{
	{CI_R_APPLOCK_FRONTOCCUPY, SMOD_CI_R_OCCUPY, stub_fun/*route_occu*/},
	{CI_R_APPLOCK_MANUALUNLOCK, SMOD_CI_R_UNLOCK, stub_fun/*route_unlock_manu*/},
	{CI_R_APPLOCK_FAULTLOCK, SMOD_CI_R_UNLOCK, stub_fun/*track_unlock_manu*/},
};

static const fsm_convert_t ci_r_occupy_core_tbl[]=
{
	{CI_R_OCCUPY_CLEANSUCC, SMOD_CI_R_CLEAN, route_clean},
	{CI_R_OCCUPY_ATUOPASS, SMOD_CI_R_ADVLOCK, route_add_autopass},
	{CI_R_OCCUPY_AUTOTRIGGER, SMOD_CI_R_CLEAN, route_add_autotrig},
	{CI_R_OCCUPY_ATUOBACK, SMOD_CI_R_UNLOCK, route_add_reentry},
	{CI_R_OCCUPY_FAULTLOCK, SMOD_CI_R_UNLOCK, track_unlock_manu},
};

static const fsm_convert_t ci_r_clean_core_tbl[]=
{
	{CI_R_CLEAN_CLEAN, SMOD_CI_R_UNLOCK, route_unlock_normal},
};

/**
 * @brief 所有模式核心层消息表
 */
static const fsm_item_t _TAB(ci_core)[]=
{
	_FSM_CONVERT_ITEM(SMOD_CI_R_UNLOCK, ci_r_unlock_core_tbl, NULL, NULL),
	_FSM_CONVERT_ITEM(SMOD_CI_R_ARRAY, ci_r_array_core_tbl, NULL, NULL),
	_FSM_CONVERT_ITEM(SMOD_CI_R_ADVLOCK, ci_r_advlock_core_tbl, NULL, NULL),
	_FSM_CONVERT_ITEM(SMOD_CI_R_APPLOCK, ci_r_applock_core_tbl, NULL, NULL),
	_FSM_CONVERT_ITEM(SMOD_CI_R_OCCUPY, ci_r_occupy_core_tbl, NULL, NULL),
	_FSM_CONVERT_ITEM(SMOD_CI_R_CLEAN, ci_r_clean_core_tbl, NULL, NULL),
};
DEF_FSM_DSCRP(ci_core);

static const fsm_item_t _TAB(ci_std)[]=
{
	_FSM_CONVERT_ITEM(NULL, NULL, NULL, NULL),
};
DEF_FSM_DSCRP(ci_std);

static const fsm_item_t _TAB(ci_usr)[]=
{
	_FSM_CONVERT_ITEM(NULL, NULL, NULL, NULL),
};
DEF_FSM_DSCRP(ci_usr);

int16_t get_type(msg_t m)
{
	return (uint8_t)(m>>24);
}

int16_t get_id(msg_t m)
{
	return (uint8_t)(m>>16);
}

int16_t get_event(msg_t m)
{
	return (uint16_t)m;
}

int16_t logic_handler(msg_t msg)
{
	uint8_t type, id;
	uint16_t event;

	type = get_type(msg);
	id = get_id(msg);
	event = get_event(msg);

	switch(type){
	case DEVICE_TRACK:
		//fsmr_update_seri(&(g_route[get_id(msg)].r_fsm), &(g_route[get_id(msg)]), msg, &_FSM_DSCRP(ci_usr), &_FSM_DSCRP(ci_std), &_FSM_DSCRP(ci_core));
		break;
	}

	return RET_SUCCESS;
}

/** 
 * @brief 主逻辑的主函数
 * 
 * @param 
 * 
 * @return 
 */
int16_t main_logic()
{
	for(;;)
	{
		msg_t message = 0;
        message = 1;
		//OSQPend();
		logic_handler(message);
	}
	return RET_SUCCESS;
}

