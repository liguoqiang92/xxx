#ifndef  _CI_PUBLIC_COMM_H
#define  _CI_PUBLIC_COMM_H

#ifdef __cplusplus
extern "C"{
#endif
/*******************************************************************************
 * �ļ�ͷ
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
 * ͷ�ļ�
 *
 ******************************************************************************/
#include "unifw.h"
#include "base/fsm.h"

/*******************************************************************************
 * ˵��
 *
 ******************************************************************************/
/**
 * ������д˵����
 * 1. track t ����
 * 2. routh r ��·
 * 3. signal s �źŻ�
 * 4. switch w ����
 * 5. balise b Ӧ����
 * 6. platform p վ̨
 * 7. button u ��ť
 * 8. Door d վ̨��
 */

/*******************************************************************************
 * �궨��
 *
 ******************************************************************************/
#define TRACK_NUM   32                   /* ������� */
#define ROUTE_NUM   14                   /* ��·���� */
#define SIGNAL_NUM  14                   /* �źŻ����� */
#define BALISE_NUM 12                    /* Ӧ������Ŀ */
#define BALI_MESS_SIZE 4                 /* Ӧ���������ֳ� */
#define DEVICE_NAME_SIZE 8               /* �豸�����ֳ� */

#define RET_SUCCESS E_OK                 /* ��������ֵ0 */
#define RET_FSM -1                       /* ״̬������ */

#define P printp("\n===WRONG BRANCH!!!===%s===%d===\n", __FILE__, __LINE__)

/*******************************************************************************
 * 0.
 * ����
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
 * ���� Track
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
 * @brief ���ζ������ݽṹ
 */
typedef struct _track{
    const uint32_t  t_id;             /* ����ID */
    const uint8_t   t_name[DEVICE_NAME_SIZE];        /* �������� */
    uint16_t    t_fsm;                /* ����״̬�� */
    uint16_t    t_status;             /* ����4��״̬��
                                         ռ�� CI_T_OCCUPY=1��
                                         ���� CI_T_CLEAN=2��
                                         ��ʱ���� CI_T_DEALYCLEAN=3��
                                         ARB CI_T_ARB=4 */
    uint16_t    t_r_id;               /* ���������Ľ�·index */
    uint16_t    t_lock;               /* �������գ�����=1������=2 */
    uint16_t    t_blockade;           /* ���η���������=1�����=2 */
    uint16_t    t_w_id;               /* �����ڵ���ID */
    uint16_t    t_r_id2;               /* ��Ϊ�ӽ����ζ�Ӧ�Ľ�· */
    uint16_t    t_feature;            /* �������ԣ��������Σ� */
    uint16_t    t_speed;              /* �������� */
    struct track    *t_up_next;       /* ����ָ�� */
    struct track    *t_down_next;     /* ����ָ�� */
}track_t;

/*******************************************************************************
 * 2.
 * ��· Route
 *
 ******************************************************************************/
enum route_status
{
    SMOD_CI_R_UNLOCK = 1,                /* ��·���� */
    SMOD_CI_R_ARRAY = 2,                 /* ����״̬ */
    SMOD_CI_R_ADVLOCK = 3,               /* Ԥ������ */
    SMOD_CI_R_APPLOCK = 4,               /* �ӽ����� */
    SMOD_CI_R_OCCUPY = 5,                /* ��·ռ�� */
    SMOD_CI_R_CLEAN = 6,                 /* ��·���� */
    ROUTE_STATUS_END = 7
};

/**
 * @brief ��·����ָ�����ݽṹ
 */
typedef struct _r_t_list
{
    uint16_t num;                     /* ������������ */
    uint32_t id1;                     /* ����1 */
    uint32_t id2;
    uint32_t id3;
}r_t_list_t;

/**
 * @brief ��·�������ݽṹ
 */
typedef struct _route{
    const uint32_t r_id;               /* ��·ID */
    const uint8_t r_name[DEVICE_NAME_SIZE];           /* ��·����*/
    uint16_t r_status;                 /* ��·6��״̬
                                          ��·���� SMOD_CI_R_UNLOCK=1
                                          ����״̬ SMOD_CI_R_ARRAY=2
                                          Ԥ������ SMOD_CI_R_ADVLOCK=3
                                          �ӽ����� SMOD_CI_R_APPLOCK=4
                                          ��·ռ�� SMOD_CI_R_OCCUPY=5
                                          ��·���� SMOD_CI_R_CLEAN=6 */
    uint16_t r_lock_advance;           /* Ԥ������*/
    uint16_t r_lock_prox;              /* �ӽ�����*/
    uint16_t r_fsm;                    /* ��·״̬�� */
    uint16_t r_singletrain;            /* �೵�����г���·=0�����г���·=1 */
    uint16_t r_triggertype;            /* ��·�Զ����ͣ���ͨ��·=0���Զ�������·=1��
                                          �Զ�ͨ����·=2���Զ��۷���·=3 */
    uint16_t r_direction_1;            /* ����1������=0������=1 */
    uint16_t r_direction_2;            /* ����2������=0������=1���ӳ�=2���۷�=3 */
    uint32_t r_s_start_id;             /* ��·ʼ���źŻ�ID */
    uint32_t r_s_end_id;               /* ��·�ն��źŻ�ID */
    uint32_t r_length;                 /* ��·���� */
    /* �źŻ����ԣ�������ʾ���Ƿ��������Ƶƶ��壬�ýṹ���ʾ�� */
    uint16_t *r_w_list;                /* �����б�û��ΪNone����Ϊ����ID�б� */
    uint16_t *r_s_anti_list;           /* �ж��źŻ��б� */
    r_t_list_t *r_t_list;              /* �����б� */
    uint16_t *r_other_list;            /* ������������ */
    uint16_t *r_t_proach_list;         /* �ӽ������б�û��ΪNone����ΪID�б� */
    uint16_t r_t_proach_dealy;         /* �ӽ�������ʱ����ʱ�� */
    uint16_t *r_t_auto_list_1;         /* �Զ�������·�����б�1 from CI��
                                          û��ΪNone����ΪID�б� */
    uint16_t *r_t_auto_list_2;         /* �Զ�������·�����б�2 from ATS��
                                          û��ΪNone����ΪID�б� */
    uint32_t r_t_protect;              /* �������Σ�û��ΪNone����ΪID */
    uint16_t r_t_protect_track;        /* ����������ʱ�������Σ�û��ΪNone����ΪID */
    uint16_t r_t_protect_dealy;        /* ����������ʱ����ʱ�䣺û��ΪNone����ΪID */
    uint16_t r_t_protect_unlock;       /* ����������������������=1��������=0 */
    uint16_t r_up_next;                /* ����ָ�룬���з�����һ���źŻ�ID */
    uint16_t r_down_next;              /* ����ָ�룬���з�����һ���źŻ�ID */
    uint32_t r_first_t;                /* ��·�ڵ�һ�����ε��ڲ�id */
    uint32_t r_t_size;                 /* ��·�ڰ������ε���Ŀ */
}route_t;

/*******************************************************************************
 * 3.
 * �źŻ� Signal
 *
 ******************************************************************************/
enum signal_status
{
    RED = 0x00001U,                      /* ��� */
    GREEN = 0x00006U,                    /* �̵� */
    GREEN_WITHOUT_PROTECT = 0x00002U,    /* �̵��ޱ������� */
    GREEN_WITH_PROTECT = 0x00003U,       /* �̵��б������� */
    YELLOW1 = 0x00007U,                  /* �Ƶ�1 */
    YELLOW1_WITHOUT_PROTECT = 0x00004U,  /* �Ƶ�1(U1)�ޱ������� */
    YELLOW1_WITH_PROTECT = 0x00005U,     /* �Ƶ�1(U1)�б������� */
    YELLOW2 = 0x0000AU,                  /* �Ƶ�2 */
    YELLOW2_WITHOUT_PROTECT = 0x00008U,  /* �Ƶ�2(U2)�ޱ������� */
    YELLOW2_WITH_PROTECT = 0x00009U,     /* �Ƶ�2(U2)�б������� */
    YELLOW3_WITHOUT_PROTECT = 0x0000CU,  /* �Ƶ�3(U3)�ޱ������� */
    YELLOW3_WITH_PROTECT = 0x0000DU,     /* �Ƶ�3(U3)�б������� */
    YELLOW4_WITHOUT_PROTECT = 0x00010U,  /* �Ƶ�4(U4)�ޱ������� */
    YELLOW4_WITH_PROTECT = 0x00011U,     /* �Ƶ�4(U4)�б������� */
    YELLOW5_WITHOUT_PROTECT = 0x00014U,  /* �Ƶ�5(U5)�ޱ������� */
    YELLOW5_WITH_PROTECT = 0x00015U,     /* �Ƶ�5(U5)�б������� */
    YELLOW6_WITHOUT_PROTECT = 0x00018U,  /* �Ƶ�6(U6)�ޱ������� */
    YELLOW6_WITH_PROTECT = 0x00019U,     /* �Ƶ�6(U6)�б������� */
    YELLOW7_WITHOUT_PROTECT = 0x0001CU,  /* �Ƶ�7(U7)�ޱ������� */
    YELLOW7_WITH_PROTECT = 0x0001DU      /* �Ƶ�7(U7)�б������� */
};

/**
 * @brief �źŻ��������ݽṹ
 */
typedef struct _signal{
    const uint32_t    s_id;           /*�źŻ�ID*/
    const uint8_t  s_name[DEVICE_NAME_SIZE];         /*�źŻ�����*/
    uint16_t    s_fsm;                /*�źŻ�״̬��*/
    uint16_t    s_col_red;            /*�źŻ����*/
    uint16_t    s_col_grn;            /*�źŻ��̵�*/
    uint16_t    s_col_yel1;           /*�źŻ���1*/
    uint16_t    s_col_yel2;           /*�źŻ���2*/
    uint16_t    s_filament_red;       /*�źŻ���˿��˿*/
    uint16_t    s_filament_grn;       /*�źŻ���˿��˿*/
    uint16_t    s_filament_yel1;      /*�źŻ���˿1��˿*/
    uint16_t    s_filament_yel2;      /*�źŻ���˿2��˿*/
    uint16_t    s_light;              /*��/���״̬1/0*/
    uint16_t    s_blockade;           /*�źŻ�����״̬1/0*/
    uint16_t    s_manu;               /*�źŻ��˹�����1/0*/
    uint16_t    s_direction;          /*�źŻ�����*/
    //uint16_t    s_route;            /*�źŻ�������·*/
    uint16_t    s_feature;            /*�źŻ����ԣ�������������*/

    struct signal    *s_up;           /*����ָ��*/
    struct signal    *s_down;         /*����ָ��*/
}signal_t;

/*******************************************************************************
 * 4.
 * ���� sWitch
 *
 ******************************************************************************/
enum switch_status
{
    DIRE_SIDE = 0xAAU,                   /*��λ*/
    DIRE_STRAIGHT = 0x55U,               /*��λ*/
    DIRE_NONE = 0x00U                    /*�Ŀ�*/
};

/**
 * @brief ����������ݽṹ
 */
typedef struct _switch{
    uint32_t    w_id;                 /* ����ID */
    enum        switch_status   w_status;
                                      /* ����λ��״̬ */
    uint16_t    w_lock;               /* ��������״̬ */
    uint16_t    w_blockade;           /* �������״̬ */
    uint16_t    w_feature;            /* �������ԣ�˫���� */
    uint16_t    w_fsm;                /* ����״̬�� */

    track_t     *w_straight;          /* ��λָ�� */
    track_t     *w_side;              /* ��λָ�� */
}switch_t;

/*******************************************************************************
 * 5.
 * Ӧ���� Balise
 *
 ******************************************************************************/
/**
 * @brief Ӧ�������ݽṹ
 */
typedef struct _balise{
    uint32_t b_id;                   /* Ӧ����ID */
    const uint8_t  s_name[DEVICE_NAME_SIZE];         /*Ӧ��������*/
    uint32_t b_track;                /* Ӧ������������ */
    uint16_t b_place;                /* Ӧ���������ε�ƫ���� */
    uint16_t b_feature;              /* Ӧ�������ԣ���Դ����Դ�� */
    uint32_t b_signal;               /* Ӧ������Ӧ�źŻ� */
    uint16_t b_map;                  /* ��ͼ�汾 */
    uint16_t b_message[BALI_MESS_SIZE];
}balise_t;

/*******************************************************************************
 * 6.
 * վ̨ Platform
 *
 ******************************************************************************/
/**
 * @brief վ̨���ݽṹ
 */
typedef struct _platform{
    uint32_t p_id;                    /*վ̨ID*/
    uint16_t p_d_list;                /*վ̨��վ̨�ű�*/
    uint16_t p_stop_train;            /*վ̨�۳�*/
    uint16_t p_emerg_close;           /*�����ر�*/

    uint16_t p_feature;               /*վ̨���ԣ���վ����վ��*/
}platform_t;

/*******************************************************************************
 * 7.
 * ��ť bUtton
 *
 ******************************************************************************/
enum button_reversible
{
    REVERSIBLE = 1,                      /* �Ը�ʽ���� */
    UNREVERSIBLE = 2,                    /* ���Ը�ʽ���� */
    BUTTON_REVERSIBLE_END = 3
};

enum button_feature
{
    NORMAL = 1,                          /* ��ͨ���� */
    AUTOTRIGGER = 2,                     /* �Զ��������� */
    AUTOPASS = 3,                        /* �Զ�ͨ������ */
    AUTORETRACE = 4,                     /* �Զ��۷����� */
    BUTTON_FEATURE_END = 5
};

/**
 * @brief ��ť���ݽṹ
 */
typedef struct _button{
    uint32_t u_id;                       /* ��ťID */
    enum button_reversible u_reversible; /* ��ť���ͣ��Զ��ظ������Զ��ظ� */
    uint16_t u_status;                   /* ��ť״̬������/̧��*/
    enum button_feature u_feature;       /* ��ť���ԣ��μ���ť���� */
}button_t;

/*******************************************************************************
 * 8.
 * վ̨�� Door
 *
 ******************************************************************************/
/**
 * @brief վ̨�Ŷ������ݽṹ
 */
typedef struct _door{
    uint32_t d_id;                    /*վ̨��ID*/
    uint16_t d_status;                /*վ̨�ſ���״̬*/
    uint16_t d_ignore;                /*վ̨����·*/
    uint16_t d_platform;              /*վ̨������վ*/

    uint16_t d_fsm;                   /*վ̨��״̬��*/
}door_t;

/*******************************************************************************
 * �ⲿ��������
 *
 ******************************************************************************/
int16_t main_loop();                  /* ��ѭ�� */
int16_t main_logic();                 /* ���߼� */
int16_t data_init();                  /* �������ݳ�ʼ�� */
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
 * ����ӿ����ݰ�
 * 1. ATS�·��İ��Ž�·�����·��ʼ�˺��ն��źŻ�
 * 2. ����ռ����Ϣ�����������ռ��״̬
 * 3. Ӧ�����������
 * 4. �źŵ�״̬
 ******************************************************************************/
typedef struct _route_input_data
{
    uint16_t start_id;             /* ��·ʼ���źŻ�ID */
    uint16_t end_id;               /* ��·�ն��źŻ�ID */
}route_input_data_t;

typedef struct _track_input_data
{
	uint16_t t_id[TRACK_NUM];
    uint16_t t_status[TRACK_NUM];             /* ����״̬��ռ��=1������=2����ʱ����=3��ARB=4 */
}track_input_data_t;

typedef struct _balise_output_data
{
	uint16_t b_id[BALISE_NUM];
	uint16_t b_message[BALISE_NUM];
}balise_output_data_t;

typedef struct _signal_output_data
{
    uint16_t s_light[SIGNAL_NUM];              /*��/���״̬*/
    uint16_t s_blockade[SIGNAL_NUM];           /*�źŻ�����״̬*/
    uint16_t s_direction[SIGNAL_NUM];          /*�źŻ�����*/
}signal_output_data_t;

#ifdef __cplusplus
}
#endif

#endif   /*_CI_PUBLIC_COMM_H*/
