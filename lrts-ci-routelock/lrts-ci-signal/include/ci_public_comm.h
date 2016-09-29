#ifndef  _CI_PUBLIC_COMM_H
#define  _CI_PUBLIC_COMM_H

#ifdef __cplusplus
extern "C"{
#endif
/*******************************************************************************
 * 文件头
 *
 ******************************************************************************/
/**
 * @file ci_public_comm.h
 * @brief define ci system public module datastruct
 * @author
 * @version
 * @date 2016-09-23
 */

/*******************************************************************************
 * 头文件
 *
 ******************************************************************************/
#include "unifw.h"
#include "base/fsm.h"

/*******************************************************************************
 * 说明
 *
 ******************************************************************************/
/**
 * 单词缩写说明：
 * 1. track t 区段
 * 2. routh r 进路
 * 3. signal s 信号机
 * 4. switch w 道岔
 * 5. balise b 应答器
 * 6. platform p 站台
 * 7. button u 按钮
 * 8. Door d 站台门
 */

/*******************************************************************************
 * 宏定义
 *
 ******************************************************************************/
#define TRACK_NUM   32                   /* 轨道数量 */
#define ROUTE_NUM   14                   /* 进路数量 */
#define SIGNAL_NUM  14                   /* 信号机数量 */
#define BALISE_NUM 12                    /* 应答器数目 */
#define BALI_MESS_SIZE 4                 /* 应答器报文字长 */
#define DEVICE_NAME_SIZE 8               /* 设备名称字长 */

#define RET_SUCCESS E_OK                 /* 函数返回值0 */
#define RET_FSM -1                       /* 状态机错误 */

#define P printp("\n===WRONG BRANCH!!!===%s===%d===\n", __FILE__, __LINE__)

/*******************************************************************************
 * 0.
 * 公共
 ******************************************************************************/
enum device_name
{
    DEVICE_TRACK = 1,
    DEVICE_ROUTE = 2,
    DEVICE_SIGNAL = 3,
    DEVICE_SWITCH = 4,
    DEVICE_BALISE = 5,
    DEVICE_PLATFORM = 6,
    DEVICE_BUTTON = 7,
    DEVICE_DOOR = 8,
    DEVICE_NAME_END = 9
};

enum msg
{
	/* route start */
    CI_R_UNLOCK_SELLECT = 0x01,
    CI_R_ARRAY_SUCC = 0x02,
    CI_R_ARRAY_FAIL = 0x03,
    CI_R_ARRAY_READY = 0x04,
    CI_R_ADVLOCK_CANCEL = 0x05,
    CI_R_ADVLOCK_APPLOCK = 0x06,
    CI_R_ADVLOCK_FAULTLOCK = 0x07,
    CI_R_APPLOCK_FRONTOCCUPY = 0x08,
    CI_R_APPLOCK_MANUALUNLOCK = 0x09,
    CI_R_APPLOCK_FAULTLOCK = 0x0A,
    CI_R_OCCUPY_CLEANSUCC = 0x0B,
    CI_R_OCCUPY_ATUOPASS = 0x0C,
    CI_R_OCCUPY_AUTOTRIGGER = 0x0D,
    CI_R_OCCUPY_ATUOBACK = 0x0E,
    CI_R_OCCUPY_FAULTLOCK = 0x0F,
    CI_R_FAULTLOCK_FAULTUNLOCK = 0x10,
    CI_R_CLEAN_CLEAN = 0x11,
    /* signal start */
    CI_S_GREEN = 0x12,
    CI_S_RED = 0x13,
    /* end */
    MSG_END = 0x14
};

/*******************************************************************************
 * 1.
 * 区段 Track
 *
 ******************************************************************************/
enum track_status
{
	CI_T_OCCUPY = 1,
	CI_T_CLEAN = 2,
	CI_T_DEALYCLEAN = 3,
	CI_T_ARB = 4
};

/**
 * @brief 区段对象数据结构
 */
typedef struct _track{
    const uint32_t  t_id;             /* 区段ID */
    const uint8_t   t_name[DEVICE_NAME_SIZE];        /* 区段名称 */
    uint16_t    t_fsm;                /* 区段状态表 */
    uint16_t    t_status;             /* 区段4个状态：
                                         占用 CI_T_OCCUPY=1、
                                         空闲 CI_T_CLEAN=2、
                                         延时出清 CI_T_DEALYCLEAN=3、
                                         ARB CI_T_ARB=4 */
    uint16_t    t_r_id;               /* 区段所属的进路index */
    uint16_t    t_lock;               /* 区段锁闭：锁闭=1、解锁=2 */
    uint16_t    t_blockade;           /* 区段封锁：封锁=1、解封=2 */
    uint16_t    t_w_id;               /* 区段内道岔ID */
    uint16_t    t_r_id2;               /* 作为接近区段对应的进路 */
    uint16_t    t_feature;            /* 区段特性（保护区段） */
    uint16_t    t_speed;              /* 区段限速 */
    struct track    *t_up_next;       /* 上行指针 */
    struct track    *t_down_next;     /* 下行指针 */
}track_t;

/*******************************************************************************
 * 2.
 * 进路 Route
 *
 ******************************************************************************/
enum route_status
{
    SMOD_CI_R_UNLOCK = 1,                /* 进路解锁 */
    SMOD_CI_R_ARRAY = 2,                 /* 排列状态 */
    SMOD_CI_R_ADVLOCK = 3,               /* 预先锁闭 */
    SMOD_CI_R_APPLOCK = 4,               /* 接近锁闭 */
    SMOD_CI_R_OCCUPY = 5,                /* 进路占用 */
    SMOD_CI_R_CLEAN = 6,                 /* 进路出清 */
    ROUTE_STATUS_END = 7
};

/**
 * @brief 进路区段指针数据结构
 */
typedef struct _r_t_list
{
    uint16_t num;                     /* 包含几个区段 */
    uint32_t id1;                     /* 区段1 */
    uint32_t id2;
    uint32_t id3;
}r_t_list_t;

/**
 * @brief 进路对象数据结构
 */
typedef struct _route{
    const uint32_t r_id;               /* 进路ID */
    const uint8_t r_name[DEVICE_NAME_SIZE];           /* 进路名称*/
    uint16_t r_status;                 /* 进路6个状态
                                          进路解锁 SMOD_CI_R_UNLOCK=1
                                          排列状态 SMOD_CI_R_ARRAY=2
                                          预先锁闭 SMOD_CI_R_ADVLOCK=3
                                          接近锁闭 SMOD_CI_R_APPLOCK=4
                                          进路占用 SMOD_CI_R_OCCUPY=5
                                          进路出清 SMOD_CI_R_CLEAN=6 */
    uint16_t r_lock_advance;           /* 预先锁闭*/
    uint16_t r_lock_prox;              /* 接近锁闭*/
    uint16_t r_fsm;                    /* 进路状态机 */
    uint16_t r_singletrain;            /* 多车：单列车进路=0、多列车进路=1 */
    uint16_t r_triggertype;            /* 进路自动类型：普通进路=0、自动触发进路=1、
                                          自动通过进路=2、自动折返进路=3 */
    uint16_t r_direction_1;            /* 方向1：上行=0、下行=1 */
    uint16_t r_direction_2;            /* 方向2：出段=0、发车=1、接车=2、折返=3 */
    uint32_t r_s_start_id;             /* 进路始端信号机ID */
    uint32_t r_s_end_id;               /* 进路终端信号机ID */
    uint32_t r_length;                 /* 进路长度 */
    /* 信号机属性：开放显示、是否引导、黄灯定义，用结构体表示？ */
    uint16_t *r_w_list;                /* 道岔列表：没有为None，有为道岔ID列表 */
    uint16_t *r_s_anti_list;           /* 敌对信号机列表 */
    r_t_list_t *r_t_list;              /* 区段列表 */
    uint16_t *r_other_list;            /* 其他联锁对象 */
    uint16_t *r_t_proach_list;         /* 接近区段列表：没有为None，有为ID列表 */
    uint16_t r_t_proach_dealy;         /* 接近锁闭延时解锁时间 */
    uint16_t *r_t_auto_list_1;         /* 自动触发进路区段列表1 from CI：
                                          没有为None，有为ID列表 */
    uint16_t *r_t_auto_list_2;         /* 自动触发进路区段列表2 from ATS：
                                          没有为None，有为ID列表 */
    uint32_t r_t_protect;              /* 保护区段：没有为None，有为ID */
    uint16_t r_t_protect_track;        /* 保护区段延时解锁区段：没有为None，有为ID */
    uint16_t r_t_protect_dealy;        /* 保护区段延时解锁时间：没有为None，有为ID */
    uint16_t r_t_protect_unlock;       /* 保护区段立即解锁：可以=1，不可以=0 */
    uint16_t r_up_next;                /* 上行指针，上行方向下一个信号机ID */
    uint16_t r_down_next;              /* 下行指针，下行方向下一个信号机ID */
    uint32_t r_first_t;                /* 进路内第一个区段的内部id */
    uint32_t r_t_size;                 /* 进路内包含区段的数目 */
}route_t;

/*******************************************************************************
 * 3.
 * 信号机 Signal
 *
 ******************************************************************************/
enum signal_status
{
    RED = 0x00001U,                      /* 红灯 */
    GREEN = 0x00006U,                    /* 绿灯 */
    GREEN_WITHOUT_PROTECT = 0x00002U,    /* 绿灯无保护区段 */
    GREEN_WITH_PROTECT = 0x00003U,       /* 绿灯有保护区段 */
    YELLOW1 = 0x00007U,                  /* 黄灯1 */
    YELLOW1_WITHOUT_PROTECT = 0x00004U,  /* 黄灯1(U1)无保护区段 */
    YELLOW1_WITH_PROTECT = 0x00005U,     /* 黄灯1(U1)有保护区段 */
    YELLOW2 = 0x0000AU,                  /* 黄灯2 */
    YELLOW2_WITHOUT_PROTECT = 0x00008U,  /* 黄灯2(U2)无保护区段 */
    YELLOW2_WITH_PROTECT = 0x00009U,     /* 黄灯2(U2)有保护区段 */
    YELLOW3_WITHOUT_PROTECT = 0x0000CU,  /* 黄灯3(U3)无保护区段 */
    YELLOW3_WITH_PROTECT = 0x0000DU,     /* 黄灯3(U3)有保护区段 */
    YELLOW4_WITHOUT_PROTECT = 0x00010U,  /* 黄灯4(U4)无保护区段 */
    YELLOW4_WITH_PROTECT = 0x00011U,     /* 黄灯4(U4)有保护区段 */
    YELLOW5_WITHOUT_PROTECT = 0x00014U,  /* 黄灯5(U5)无保护区段 */
    YELLOW5_WITH_PROTECT = 0x00015U,     /* 黄灯5(U5)有保护区段 */
    YELLOW6_WITHOUT_PROTECT = 0x00018U,  /* 黄灯6(U6)无保护区段 */
    YELLOW6_WITH_PROTECT = 0x00019U,     /* 黄灯6(U6)有保护区段 */
    YELLOW7_WITHOUT_PROTECT = 0x0001CU,  /* 黄灯7(U7)无保护区段 */
    YELLOW7_WITH_PROTECT = 0x0001DU      /* 黄灯7(U7)有保护区段 */
};

/**
 * @brief 信号机对象数据结构
 */
typedef struct _signal{
    const uint32_t    s_id;           /*信号机ID*/
    const uint8_t  s_name[DEVICE_NAME_SIZE];         /*信号机名称*/
    uint16_t    s_fsm;                /*信号机状态表*/
    uint16_t    s_col_red;            /*信号机红灯*/
    uint16_t    s_col_grn;            /*信号机绿灯*/
    uint16_t    s_col_yel1;           /*信号机黄1*/
    uint16_t    s_col_yel2;           /*信号机黄2*/
    uint16_t    s_filament_red;       /*信号机红丝断丝*/
    uint16_t    s_filament_grn;       /*信号机绿丝断丝*/
    uint16_t    s_filament_yel1;      /*信号机黄丝1断丝*/
    uint16_t    s_filament_yel2;      /*信号机黄丝2断丝*/
    uint16_t    s_light;              /*亮/灭灯状态1/0*/
    uint16_t    s_blockade;           /*信号机封锁状态1/0*/
    uint16_t    s_manu;               /*信号机人工设置1/0*/
    uint16_t    s_direction;          /*信号机方向*/
    //uint16_t    s_route;            /*信号机所属进路*/
    uint16_t    s_feature;            /*信号机属性（防护、引导）*/

    struct signal    *s_up;           /*上行指针*/
    struct signal    *s_down;         /*下行指针*/
}signal_t;

/*******************************************************************************
 * 4.
 * 道岔 sWitch
 *
 ******************************************************************************/
enum switch_status
{
    DIRE_SIDE = 0xAAU,                   /*反位*/
    DIRE_STRAIGHT = 0x55U,               /*定位*/
    DIRE_NONE = 0x00U                    /*四开*/
};

/**
 * @brief 道岔对象数据结构
 */
typedef struct _switch{
    uint32_t    w_id;                 /* 道岔ID */
    enum        switch_status   w_status;
                                      /* 道岔位置状态 */
    uint16_t    w_lock;               /* 道岔锁闭状态 */
    uint16_t    w_blockade;           /* 道岔封锁状态 */
    uint16_t    w_feature;            /* 道岔特性（双动） */
    uint16_t    w_fsm;                /* 道岔状态表 */

    track_t     *w_straight;          /* 定位指针 */
    track_t     *w_side;              /* 反位指针 */
}switch_t;

/*******************************************************************************
 * 5.
 * 应答器 Balise
 *
 ******************************************************************************/
/**
 * @brief 应答器数据结构
 */
typedef struct _balise{
    uint32_t b_id;                   /* 应答器ID */
    const uint8_t  s_name[DEVICE_NAME_SIZE];         /*应答器名称*/
    uint32_t b_track;                /* 应答器所在区段 */
    uint16_t b_place;                /* 应答器在区段的偏移量 */
    uint16_t b_feature;              /* 应答器属性（有源、无源） */
    uint32_t b_signal;               /* 应答器对应信号机 */
    uint16_t b_map;                  /* 地图版本 */
    uint16_t b_message[BALI_MESS_SIZE];
}balise_t;

/*******************************************************************************
 * 6.
 * 站台 Platform
 *
 ******************************************************************************/
/**
 * @brief 站台数据结构
 */
typedef struct _platform{
    uint32_t p_id;                    /*站台ID*/
    uint16_t p_d_list;                /*站台内站台门表*/
    uint16_t p_stop_train;            /*站台扣车*/
    uint16_t p_emerg_close;           /*紧急关闭*/

    uint16_t p_feature;               /*站台属性（主站、辅站）*/
}platform_t;

/*******************************************************************************
 * 7.
 * 按钮 bUtton
 *
 ******************************************************************************/
enum button_reversible
{
    REVERSIBLE = 1,                      /* 自复式开关 */
    UNREVERSIBLE = 2,                    /* 非自复式开关 */
    BUTTON_REVERSIBLE_END = 3
};

enum button_feature
{
    NORMAL = 1,                          /* 普通开关 */
    AUTOTRIGGER = 2,                     /* 自动触发开关 */
    AUTOPASS = 3,                        /* 自动通过开关 */
    AUTORETRACE = 4,                     /* 自动折返开关 */
    BUTTON_FEATURE_END = 5
};

/**
 * @brief 按钮数据结构
 */
typedef struct _button{
    uint32_t u_id;                       /* 按钮ID */
    enum button_reversible u_reversible; /* 按钮类型，自动回复，非自动回复 */
    uint16_t u_status;                   /* 按钮状态（按下/抬起）*/
    enum button_feature u_feature;       /* 按钮属性，参见按钮类型 */
}button_t;

/*******************************************************************************
 * 8.
 * 站台门 Door
 *
 ******************************************************************************/
/**
 * @brief 站台门对象数据结构
 */
typedef struct _door{
    uint32_t d_id;                    /*站台门ID*/
    uint16_t d_status;                /*站台门开关状态*/
    uint16_t d_ignore;                /*站台门旁路*/
    uint16_t d_platform;              /*站台门所属站*/

    uint16_t d_fsm;                   /*站台门状态表*/
}door_t;

/*******************************************************************************
 * 外部函数申明
 *
 ******************************************************************************/
int16_t main_loop();                  /* 主循环 */
int16_t main_logic();                 /* 主逻辑 */
int16_t data_init();                  /* 工程数据初始化 */
int16_t stub_fun(msg_t m, void *p);

extern int16_t route_clean(msg_t m, void *p);
extern int16_t route_add_autopass(msg_t m, void *p);
extern int16_t route_add_autotrig(msg_t m, void *p);
extern int16_t route_add_reentry(msg_t m, void *p);
extern int16_t track_unlock_manu(msg_t m, void *p);
extern int16_t route_unlock_normal(msg_t m, void *p);

extern track_t g_track[];
extern signal_t g_signal[];
extern route_t g_route[];

int16_t get_type(msg_t m);
int16_t get_id(msg_t m);
int16_t get_event(msg_t m);


/*******************************************************************************
 * 对外接口数据包
 * 1. ATS下发的安排进路命令。进路的始端和终端信号机
 * 2. 区段占用信息，计轴的所有占用状态
 * 3. 应答器输出报文
 * 4. 信号灯状态
 ******************************************************************************/
typedef struct _route_input_data
{
    uint16_t start_id;             /* 进路始端信号机ID */
    uint16_t end_id;               /* 进路终端信号机ID */
}route_input_data_t;

typedef struct _track_input_data
{
	uint16_t t_id[TRACK_NUM];
    uint16_t t_status[TRACK_NUM];             /* 区段状态：占用=1、空闲=2、延时出清=3、ARB=4 */
}track_input_data_t;

typedef struct _balise_output_data
{
	uint16_t b_id[BALISE_NUM];
	uint16_t b_message[BALISE_NUM];
}balise_output_data_t;

typedef struct _signal_output_data
{
    uint16_t s_light[SIGNAL_NUM];              /*亮/灭灯状态*/
    uint16_t s_blockade[SIGNAL_NUM];           /*信号机封锁状态*/
    uint16_t s_direction[SIGNAL_NUM];          /*信号机方向*/
}signal_output_data_t;

#ifdef __cplusplus
}
#endif

#endif   /*_CI_PUBLIC_COMM_H*/
