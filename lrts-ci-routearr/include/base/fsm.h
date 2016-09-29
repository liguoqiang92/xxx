/** 
 * @file fsm.h
 * @brief FSM模块的头文件
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
 * @brief 定义FSM的转换所需内容
 */
typedef struct _fsm_convert
{
	msg_t  msg			;	/**<  消息 */
	fsm_t  dst_mode			;	/**<  目的模式 */
	int16_t (*check_cond)(msg_t msg, void *pdata);	/**<  检查条件，0表示可转换, -E_NOT_END表示需继续 */
}fsm_convert_t;

/** 
 * @brief 模式下的FSM处理条目
 */
typedef struct _fsm_item
{
	fsm_t 	cur_mode	;	/**<  当前模式 */
	uint16_t 	table_len	;	/**<  模式转换表长度 */
	const fsm_convert_t *table		;	/**<  模式转换表，每一个msg只有一个条目 */
	int16_t (*msg_not_found)(msg_t msg, void *pdata);	/**< 消息未找到时处理 */
	void (*fsm_change_handler)(fsm_t old, fsm_t cur, void *pdata);	/**< 状态发生变化时处理 */
}fsm_item_t;

/** 
 * @brief 总表，第一层结构包括
 */
typedef struct _fsm_dscrp
{
	fsm_item_t *table	;	/**< fsm转换表格 */
	uint16_t 	len		;	/**< 转换表格的长度 */
}fsm_dscrp_t;

/** 
 * @brief fsmr_update 默认的更新状态机
 *
 * @param mode 状态机变量
 * @param msg 消息
 * @param desp 状态机描述符
 * 
 * @return 转换标志
 * 	- -E_NOT_FOUND 未找到对应的消息的处理函数
 * 	- -E_NOT_END  表示已经转换成功，且不需要继续解析
 * 	- -E_NULL_PT  转换表为空
 * 	- >=0         表示合法的模式，且不需要继续解析
 */
int16_t fsm_update(fsm_t *mode, const msg_t msg, const fsm_dscrp_t *desp);

int16_t fsmr_update(fsm_t *mode, void *pdata, const uint16_t msg, const fsm_dscrp_t *desp);

/** 
 * @brief fsmr_update_seri 更新系列FSM
 * 
 * @param mode  fsm模式
 * @param pdata fsm相关的数据
 * @param msg   消息
 * @param user  定制状态表
 * @param std   标准状态表
 * @param core  核心状态表
 * 
 * @return 
 */
int16_t fsm_update_seri(fsm_t *mode, const msg_t msg, 
		const fsm_dscrp_t *user, const fsm_dscrp_t *std, const fsm_dscrp_t *core);

int16_t fsmr_update_seri(fsm_t *mode, void *pdata, const uint16_t msg, const fsm_dscrp_t *user, const fsm_dscrp_t *std, const fsm_dscrp_t *core);

/** 
 * @brief fsm_reset 复位状态机
 * 
 * @param f 状态机指针
 */
void fsm_reset(fsm_t *f);

fsm_t fsm_get(const fsm_t *f);

fsm_t fsm_set(fsm_t *f, fsm_t v);

/** 定义FSM*/
#define _FSM(n) _##n##_fsm
/** 定义FSM表格相关内容*/
#define _FSM_TABLE(n) _##n##_fsm_table
/** 定义FSM描述符相关内容*/
#define _FSM_DSCRP(n) _##n##_fsm_dscrp

/** 
 * @brief _FSM_CONVERT_ITEM 展开FSM_CONVERT_ITEM
 * 
 * @param m 模式
 * @param n 转换表数组
 */
#define _FSM_CONVERT_ITEM(m, n, f1, f2) {m, sizeof(n)/sizeof(fsm_convert_t), (const fsm_convert_t *)n, f1, f2}

#ifdef _WIN32
#define _FSM_CONVERT_VA(m, n, ...) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n, __VA_ARGS__}
#elif defined Platform_Chip_S12
#define _FSM_CONVERT_VA(m, n) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n}
#else
#define _FSM_CONVERT_VA(m, n, args...) {m, sizeof(n)/sizeof(fsm_convert_t), (fsm_convert_t *)n, ##args}
#endif

/** 定义FSM相关函数，不包括set */
#define DEF_SFSM(name) static fsm_t _FSM(name)=FSM_START; void name##_fsm_reset(void){_FSM(name)=FSM_START;} \
	fsm_t name##_fsm_get(void){return _FSM(name);} 

/** 定义FSM描述符 */
#define DEF_FSM_DSCRP(n) const fsm_dscrp_t _FSM_DSCRP(n)={(fsm_item_t*)_TAB(n), sizeof(_TAB(n))/sizeof(_TAB(n)[0])}

#define DCLR_FSM_DSCRP(n) extern const fsm_dscrp_t _FSM_DSCRP(n);

/** 定义FSM所有函数，包括set*/
#define DEF_FSM(name) DEF_SFSM(name); fsm_t name##_fsm_set(fsm_t t){_FSM(name) = t; return t;}

/** 声明FSM所有函数*/
#define DCLR_FSM(name) void name##_fsm_reset(void); fsm_t name##_fsm_get(void); fsm_t name##_fsm_set(fsm_t t);

/** 按照非静态的方式定义 */
#define DEF_FSMV(name) fsm_t _FSM(name)=FSM_START;

/** 按照非静态的方式声明 */
#define DCLR_FSMV(name) extern fsm_t _FSM(name);

/** 复位函数，f将被扩展成_FSM(f) */
#define FSM_RESET(f) fsm_reset(&_FSM(f))

/** 设置函数，_FSM(f)将被设置成v */
#define FSM_SET(f, v) fsm_set(&_FSM(f), v)

/** 获取函数，将获取_FSM(f)数值 */
#define FSM_GET(f) fsm_get(&_FSM(f))

#ifdef TEST
/* 在测试模式下，进行单独测试 */
extern int16_t not_found_ret;
extern int16_t fsm_change_ret;
#endif

#ifdef __cplusplus
}
#endif

/** @} */

#endif
