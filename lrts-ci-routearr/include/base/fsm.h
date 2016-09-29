/** 
 * @file fsm.h
 * @brief FSMģ���ͷ�ļ�
 * @author zhuo.kaikuo@byd.com
 * @date 2016-6-10
 * 
 * $Id$
*/ 
#ifndef _FSM_H_
#define _FSM_H_

/** 
 * @defgroup fsm common/fsm 
 * @{
 * */

#ifdef __cplusplus
extern "C"{
#endif

LIB_TYPE extern mod_dscrp_t ver_fsm;

#define FSM_RESERVED 0
#define FSM_START 1

typedef uint16_t msg_t;

/** 
 * @brief ����FSM��ת����������
 */
typedef struct _fsm_convert
{
	msg_t  msg			;	/**<  ��Ϣ */
	fsm_t  dst_mode			;	/**<  Ŀ��ģʽ */
	int16_t (*check_cond)(msg_t msg, void *pdata);	/**<  ���������0��ʾ��ת��, -E_NOT_END��ʾ����� */
}fsm_convert_t;

/** 
 * @brief ģʽ�µ�FSM������Ŀ
 */
typedef struct _fsm_item
{
	fsm_t 	cur_mode	;	/**<  ��ǰģʽ */
	uint16_t 	table_len	;	/**<  ģʽת������ */
	const fsm_convert_t *table		;	/**<  ģʽת����ÿһ��msgֻ��һ����Ŀ */
	int16_t (*msg_not_found)(msg_t msg, void *pdata);	/**< ��Ϣδ�ҵ�ʱ���� */
	void (*fsm_change_handler)(fsm_t old, fsm_t cur, void *pdata);	/**< ״̬�����仯ʱ���� */
}fsm_item_t;

/** 
 * @brief �ܱ���һ��ṹ����
 */
typedef struct _fsm_dscrp
{
	fsm_item_t *table	;	/**< fsmת����� */
	uint16_t 	len		;	/**< ת�����ĳ��� */
}fsm_dscrp_t;

/** 
 * @brief fsmr_update Ĭ�ϵĸ���״̬��
 *
 * @param mode ״̬������
 * @param msg ��Ϣ
 * @param desp ״̬��������
 * 
 * @return ת����־
 * 	- -E_NOT_FOUND δ�ҵ���Ӧ����Ϣ�Ĵ�����
 * 	- -E_NOT_END  ��ʾ�Ѿ�ת���ɹ����Ҳ���Ҫ��������
 * 	- -E_NULL_PT  ת����Ϊ��
 * 	- >=0         ��ʾ�Ϸ���ģʽ���Ҳ���Ҫ��������
 */
int16_t fsm_update(fsm_t *mode, const msg_t msg, const fsm_dscrp_t *desp);

int16_t fsmr_update(fsm_t *mode, void *pdata, const uint16_t msg, const fsm_dscrp_t *desp);

/** 
 * @brief fsmr_update_seri ����ϵ��FSM
 * 
 * @param mode  fsmģʽ
 * @param pdata fsm��ص�����
 * @param msg   ��Ϣ
 * @param user  ����״̬��
 * @param std   ��׼״̬��
 * @param core  ����״̬��
 * 
 * @return 
 */
int16_t fsm_update_seri(fsm_t *mode, const msg_t msg, 
		const fsm_dscrp_t *user, const fsm_dscrp_t *std, const fsm_dscrp_t *core);

int16_t fsmr_update_seri(fsm_t *mode, void *pdata, const uint16_t msg, const fsm_dscrp_t *user, const fsm_dscrp_t *std, const fsm_dscrp_t *core);

/** 
 * @brief fsm_reset ��λ״̬��
 * 
 * @param f ״̬��ָ��
 */
void fsm_reset(fsm_t *f);

fsm_t fsm_get(const fsm_t *f);

fsm_t fsm_set(fsm_t *f, fsm_t v);

/** ����FSM*/
#define _FSM(n) _##n##_fsm
/** ����FSM����������*/
#define _FSM_TABLE(n) _##n##_fsm_table
/** ����FSM�������������*/
#define _FSM_DSCRP(n) _##n##_fsm_dscrp

/** 
 * @brief _FSM_CONVERT_ITEM չ��FSM_CONVERT_ITEM
 * 
 * @param m ģʽ
 * @param n ת��������
 */
#define _FSM_CONVERT_ITEM(m, n, f1, f2) {m, sizeof(n)/sizeof(fsm_convert_t), (const fsm_convert_t *)n, f1, f2}

#ifdef _WIN32
#define _FSM_CONVERT_VA(m, n, ...) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n, __VA_ARGS__}
#elif defined Platform_Chip_S12
#define _FSM_CONVERT_VA(m, n) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n}
#else
#define _FSM_CONVERT_VA(m, n, args...) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n, ##args}
#endif

/** ����FSM��غ�����������set */
#define DEF_SFSM(name) static fsm_t _FSM(name)=FSM_START; void name##_fsm_reset(void){_FSM(name)=FSM_START;} \
	fsm_t name##_fsm_get(void){return _FSM(name);} 

/** ����FSM������ */
#define DEF_FSM_DSCRP(n) const fsm_dscrp_t _FSM_DSCRP(n)={(fsm_item_t*)_TAB(n), sizeof(_TAB(n))/sizeof(_TAB(n)[0])}

#define DCLR_FSM_DSCRP(n) extern const fsm_dscrp_t _FSM_DSCRP(n);

/** ����FSM���к���������set*/
#define DEF_FSM(name) DEF_SFSM(name); fsm_t name##_fsm_set(fsm_t t){_FSM(name) = t; return t;}

/** ����FSM���к���*/
#define DCLR_FSM(name) void name##_fsm_reset(void); fsm_t name##_fsm_get(void); fsm_t name##_fsm_set(fsm_t t);

/** ���շǾ�̬�ķ�ʽ���� */
#define DEF_FSMV(name) fsm_t _FSM(name)=FSM_START;

/** ���շǾ�̬�ķ�ʽ���� */
#define DCLR_FSMV(name) extern fsm_t _FSM(name);

/** ��λ������f������չ��_FSM(f) */
#define FSM_RESET(f) fsm_reset(&_FSM(f))

/** ���ú�����_FSM(f)�������ó�v */
#define FSM_SET(f, v) fsm_set(&_FSM(f), v)

/** ��ȡ����������ȡ_FSM(f)��ֵ */
#define FSM_GET(f) fsm_get(&_FSM(f))

#ifdef TEST
/* �ڲ���ģʽ�£����е������� */
extern int16_t not_found_ret;
extern int16_t fsm_change_ret;
#endif

#ifdef __cplusplus
}
#endif

/** @} */

#endif
