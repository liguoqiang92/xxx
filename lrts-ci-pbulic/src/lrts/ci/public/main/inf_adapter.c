/** 
 * @file ver_public
 * @brief 
 * @author dingjian
 * @date 2016-09-26
 * 
 * $Id$
 */

#include "unifw.h"

/**
===Change Log of module===

 v0.1.0 dingjian

=====End of change log====
*/

#include "ci_public_comm.h"

/**
 * @brief 
 * 
 * @param 
 *
 * @return 
 * 	- -E_NULL_PT  Ŀ�����ݽṹ��ָ��
 * 	- >=0         ����ɹ�
 */
int16_t inf_get_route_input_handle(route_input_data_t* p)
{
	int16_t ret = E_OK;
	if (NULL != p)
	{
		
		/*TODO: ����ƽ̨��ӿڻ�ȡIO���룬Ȼ�������Ŀ��ṹ���� */
	}
	else
	{
		ret = E_NULL_PT;
	}
	return ret;
}

/**
 * @brief 
 * 
 * @param 
 *
 * @return 
 * 	- -E_NULL_PT  Ŀ�����ݽṹ��ָ��
 * 	- >=0         ����ɹ�
 */
int16_t inf_get_track_input_handle(track_input_data_t* p)
{
	int16_t ret = E_OK;
	if (NULL != p)
	{
		
		/*TODO: ����ƽ̨��ӿڻ�ȡIO���룬Ȼ�������Ŀ��ṹ���� */
	}
	else
	{
		ret = E_NULL_PT;
	}
	return ret;
}

/**
 * @brief 
 * 
 * @param 
 *
 * @return 
 * 	- -E_NULL_PT  Ŀ�����ݽṹ��ָ��
 * 	- >=0         ����ɹ�
 */
int16_t inf_set_balise_input_handle(balise_output_data_t* p)
{
	int16_t ret = E_OK;
	if (NULL != p)
	{
		
		/*TODO: ����ƽ̨��ӿڻ�ȡIO���룬Ȼ�������Ŀ��ṹ���� */
	}
	else
	{
		ret = E_NULL_PT;
	}
	return ret;
}

/**
 * @brief 
 * 
 * @param 
 *
 * @return 
 * 	- -E_NULL_PT  Ŀ�����ݽṹ��ָ��
 * 	- >=0         ����ɹ�
 */
int16_t inf_set_signal_input_handle(signal_output_data_t* p)
{
	int16_t ret = E_OK;
	if (NULL != p)
	{
		
		/*TODO: ����ƽ̨��ӿڻ�ȡIO���룬Ȼ�������Ŀ��ṹ���� */
	}
	else
	{
		ret = E_NULL_PT;
	}
	return ret;
}
