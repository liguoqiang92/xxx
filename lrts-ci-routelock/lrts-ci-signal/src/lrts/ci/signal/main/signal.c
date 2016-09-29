/**
* @file signal.c
* @brief
* @author liguoqiang
* @date 2016-09-27
*
* $Id$
*/


#include "signal.h"
#include "stdio.h"


/**
* @brief 检查红灯灯丝
*
* @param signal_id 信号机指针
*
* @return  好/坏
*/
int16_t signal_check_gob_red(uint32_t signal_id)
{
    int16_t i,ret=0;
    for(i=0;i<SIGNAL_NUM;i++){
        if(signal_id == g_signal[i].s_id){
            ret = g_signal[i].s_filament_red;
        }
    }
    printf("%u信号机红灯丝%d\n",signal_id,ret);
    return ret;
}


/**
* @brief 关闭信号机（红）
*
* @param signal_id 信号机指针
* @param dis    设置灯色
*
* @return  成功/失败
*/
int16_t signal_set_red(msg_t m, void *p)
{
    int16_t i,ret=0;
    uint32_t signal_id;

    if (CI_S_RED != get_event(m)) {
        ret = RET_FSM;
    }else{
        signal_id = get_id(m);
        for(i=0;i<SIGNAL_NUM;i++){
            if(signal_id == g_signal[i].s_id){
                if(g_signal[i].s_manu == 2){
                    if (g_signal[i].s_filament_red ==1){
                        g_signal[i].s_col_red =1;
                        g_signal[i].s_col_grn =2;
                        g_signal[i].s_col_yel1 =2;
                        g_signal[i].s_col_yel2 =2;

                    }else{
                        ret =2;
                    }
                }else{
                    ret =2;
                }
            }else{
                ret =2;
            }
        }
    }
    return ret;
}

/**
* @brief 开放信号机（绿）
*
* @param signal_id 信号机指针
* @param dis    设置灯色
*
* @return  成功/失败
*/
int16_t signal_set_grn(msg_t m, void *p)
{
    int16_t i,ret=0;
    uint32_t signal_id;

    if (CI_S_GREEN != get_event(m)) {
        ret = RET_FSM;
    }else{
        signal_id = get_id(m);
        for(i=0;i<SIGNAL_NUM;i++){
            if(signal_id == g_signal[i].s_id){
                if(g_signal[i].s_manu == 2){
                    if (g_signal[i].s_filament_red ==1 && g_signal[i].s_filament_grn == 1){
                        g_signal[i].s_col_red =2;
                        g_signal[i].s_col_grn =1;
                        g_signal[i].s_col_yel1 =2;
                        g_signal[i].s_col_yel2 =2;

                    }else{
                        ret =2;
                    }
                }else{
                    ret =2;
                }
            }else{
                ret =2;
            }
        }
    }
    return ret;
}

/**
* @brief 获取信号机状态（灯色）
*
* @param signal_id 信号机
*
* @return  灯色
*/
int16_t signal_get_status(uint32_t signal_id)
{
    int16_t i,ret=0;
    for(i=0;i<SIGNAL_NUM;i++){
        if(signal_id == g_signal[i].s_id){
            if(g_signal[i].s_col_red == 1 && g_signal[i].s_col_grn == 2 && g_signal[i].s_col_yel1 == 2 && g_signal[i].s_col_yel2 == 2){
                ret = RED;

            }
            if(g_signal[i].s_col_red == 2 && g_signal[i].s_col_grn == 1 && g_signal[i].s_col_yel1 == 2 && g_signal[i].s_col_yel2 == 2 ){
                ret = GREEN;

            }
            if(g_signal[i].s_col_red == 2 && g_signal[i].s_col_grn == 2 && g_signal[i].s_col_yel1 == 1 && g_signal[i].s_col_yel2 == 2 ){
                ret = YELLOW1;

            }
            if(g_signal[i].s_col_red == 2 && g_signal[i].s_col_grn == 2 && g_signal[i].s_col_yel1 == 2 && g_signal[i].s_col_yel2 == 1 ){
                ret = YELLOW2;

            }
        }


    }
    printf("%x信号机%d\n",signal_id,ret);
    return ret;

}


int16_t signal_set_dis(uint32_t signal_id, uint16_t dis)
{
    int16_t i,ret=0;
    for(i=0;i<SIGNAL_NUM;i++){
        if(signal_id == g_signal[i].s_id){
            if (g_signal[i].s_filament_red ==1){
                if(dis == RED ){
                    g_signal[i].s_col_red =1;
                    g_signal[i].s_col_grn =2;
                    g_signal[i].s_col_yel1 =2;
                    g_signal[i].s_col_yel2 =2;
                    ret = 1;
                }
                if(dis == GREEN_WITHOUT_PROTECT || dis == GREEN_WITH_PROTECT){
                    g_signal[i].s_col_red =2;
                    g_signal[i].s_col_grn =1;
                    g_signal[i].s_col_yel1 =2;
                    g_signal[i].s_col_yel2 =2;
                    ret = 1;
                    if(g_signal[i].s_col_grn ==2){
                        g_signal[i].s_col_red =1;
                        g_signal[i].s_col_grn =2;
                        g_signal[i].s_col_yel1 =2;
                        g_signal[i].s_col_yel2 =2;
                        ret = 2;
                    }

                }
                if(dis == YELLOW1_WITHOUT_PROTECT || dis == YELLOW1_WITH_PROTECT){
                    g_signal[i].s_col_red =2;
                    g_signal[i].s_col_grn =2;
                    g_signal[i].s_col_yel1 =1;
                    g_signal[i].s_col_yel2 =2;
                    ret = 1;
                    if(g_signal[i].s_col_yel1 ==2){
                        g_signal[i].s_col_red =1;
                        g_signal[i].s_col_grn =2;
                        g_signal[i].s_col_yel1 =2;
                        g_signal[i].s_col_yel2 =2;
                        ret = 2;
                    }
                }
                if(dis == YELLOW2_WITHOUT_PROTECT || dis == YELLOW2_WITH_PROTECT){
                    g_signal[i].s_col_red =2;
                    g_signal[i].s_col_grn =2;
                    g_signal[i].s_col_yel1 =2;
                    g_signal[i].s_col_yel2 =1;
                    ret = 1;
                    if(g_signal[i].s_col_yel2 ==2){
                        g_signal[i].s_col_red =1;
                        g_signal[i].s_col_grn =2;
                        g_signal[i].s_col_yel1 =2;
                        g_signal[i].s_col_yel2 =2;
                        ret = 2;
                    }

                }

            }
        }
    }
    printf("%x信号机%d\n",signal_id,ret);
    return ret;

}
