/** 
 * @file route_clean.c
 * @brief 
 * @author dingjian
 * @date 2016-09-27
 * 
 * $Id$
 */



/**
===Change Log of module===

 v0.1.0 dingjian

=====End of change log====
*/

#include "ci_public_comm.h"

uint8_t t[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; // axle changed timing record

int16_t check3timing(uint8_t track_id)
{
	/**
	 * �������˼·
	 * 1. ͨ��һ�ַ�������ÿ�μ���ı仯��¼��timing�������棻
	 * 2. һ����¼���������ݣ�
	 * 3. ͨ��������Ĺ���
	 */
	int16_t ret = CI_T_OCCUPY;

	if((t[0][0] && t[0][1] && (!t[0][2])) // timing1 110
	  && ((!t[1][0]) && t[1][1] && (!t[1][2])) // timing2 010
	  // t[2][*]
	  && ((!t[3][0]) && (!t[3][1]) && t[3][2])) // timing3 001
	{
	    ret = CI_T_CLEAN;
	    g_track[track_id].t_status = ret;
	}
	return ret;
}

int16_t check_track_occupt(uint32_t track_id)
{
	uint8_t i = 0;
	int16_t ret = 1;

	for (i = 0; i < TRACK_NUM; i++) {
		if((g_track[1].t_id == track_id) 
		  && (CI_T_CLEAN == g_track[i].t_status)
		  && (2 == g_track[i].t_lock))
		{
			ret = 0;
		}
	}
	return ret;
}

int16_t check_route_occupy(uint8_t route_id)
{
	uint8_t i = 0;
	int16_t ret = 1;
	r_t_list_t *t1 = g_route[route_id].r_t_list;
	uint8_t num = t1->num;

	switch (num) {
		case 1:
			if (check_track_occupt(t1->id1)) {
				ret = 1;
			}
			break;
		case 2:
			if (check_track_occupt(t1->id1) 
			  || check_track_occupt(t1->id2)) {
				ret = 1;
			}
			break;
		case 3:
			if (check_track_occupt(t1->id1) 
			  || check_track_occupt(t1->id2) 
			  || check_track_occupt(t1->id3)) {
				ret = 1;
			}
			break;
	default:
		break;
	}
	return ret;
}

/**
 * @brief ��·����ɹ�
 * 
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 ����ɹ�
 * 	- 1 ռ��
 */
int16_t route_clean(msg_t m, void *p)
{
	int16_t ret = SMOD_CI_R_OCCUPY;
	uint8_t i = 0;
	
	if (CI_R_OCCUPY_CLEANSUCC != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = check_route_occupy(get_id(m));
	}
	return ret;
}

/**
 * @brief �����Զ�ͨ������
 * ����route��r_triggertype
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 		 ��ʾ����ת��
 * 	- -E_NOT_END ��ʾ��Ҫ����
 */
int16_t route_add_autopass(msg_t m, void *p)
{
	int16_t ret = RET_SUCCESS;
	
	if (CI_R_OCCUPY_ATUOPASS != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = 1;
		g_route[get_id(m)].r_triggertype = ret;
	}
	return ret;
}

/**
 * @brief �����Զ���������
 * ����route��r_triggertype
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 		 ��ʾ����ת��
 * 	- -E_NOT_END ��ʾ��Ҫ����
 */
int16_t route_add_autotrig(msg_t m, void *p)
{
	int16_t ret = RET_SUCCESS;
	
	if (CI_R_OCCUPY_AUTOTRIGGER != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = 2;
		g_route[get_id(m)].r_triggertype = ret;
	}
	return ret;
}

/**
 * @brief �����Զ��۷�����
 * ����route��r_triggertype
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 		 ��ʾ����ת��
 * 	- -E_NOT_END ��ʾ��Ҫ����
 */
int16_t route_add_reentry(msg_t m, void *p)
{
	int16_t ret = RET_SUCCESS;
	
	if (CI_R_OCCUPY_ATUOBACK != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = 3;
		g_route[get_id(m)].r_triggertype = ret;
	}
	return ret;
}

/**
 * @brief �������ι���
 * ����track��t_status
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 		 ��ʾ����ת��
 * 	- -E_NOT_END ��ʾ��Ҫ����
 */
int16_t track_unlock_manu(msg_t m, void *p)
{
	int16_t ret = RET_SUCCESS;
	uint32_t track_id = 0;
	
	if (CI_R_FAULTLOCK_FAULTUNLOCK != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = 1;
		track_id = (uint32_t)p;
		g_track[track_id].t_status = ret;
	}
	return ret;
}

/**
 * @brief ��·����
 * ����route��r_status
 *
 * @param msg ��Ϣ
 * @param pdata ��Ϣ�������
 *
 * @return
 * 	- 0 		 ��ʾ����ת��
 * 	- -E_NOT_END ��ʾ��Ҫ����
 */
int16_t route_unlock_normal(msg_t m, void *p)
{
	int16_t ret = RET_SUCCESS;
	
	if (CI_R_CLEAN_CLEAN != get_event(m)) {
		ret = RET_FSM;
	}else{
		ret = 0;
		g_route[get_id(m)].r_status = ret;
	}
	return ret;
}

