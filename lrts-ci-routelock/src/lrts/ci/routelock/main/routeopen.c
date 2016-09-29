/**
* @file route_open.c
* @brief
* @author liguoqiang
* @date 2016-09-27
*
* $Id$
*/

#include "routeopen.h"
#include "signal.h"
#include "stdio.h"


/*
* @brief 区段空闲且锁闭检查
*
* @param track_id   区段id
*
* @return 区段锁闭状态1/2
*/
int16_t track_lock_check2(uint32_t track_id)
{
    int i,ret=0;

    for(i = 0;i< TRACK_NUM;i++){
        if(track_id == g_track[i].t_id ){
            if(g_track[i].t_status ==2 && g_track[i].t_lock == 1){

                printf("%u  %s  %u %u\n",g_track[i].t_id,g_track[i].t_name,g_track[i].t_status,g_track[i].t_lock);
                printf("%u区段空闲且锁闭条件满足\n",g_track[i].t_id);
                ret = 1;

            }else
            {

                printf("%u区段条件不满足\n",g_track[i].t_id);
                ret = 2;
            }

        }

    }

    return ret;

}



/**
* @brief 进路开放
*
* @param route_id   进路id
*
* @return 允许/拒绝 1/2
*/
int16_t route_open_check(uint32_t route_id)
{
    int16_t i,ret=0;
    r_t_list_t *prt;

    for(i = 0;i< 14;i++){
        if(route_id == g_route[i].r_id){
            prt = g_route[i].r_t_list;
            if(prt->num == 1){
                if(track_lock_check2( prt->id1)==1){

                    ret = 1;
                    printf("%u可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);

                }else
                {
                    ret = 2;
                    printf("%u不可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);
                }

            }
            if(prt->num == 2){
                if(track_lock_check2( prt->id1)==1 && track_lock_check2( prt->id2)==1){
                    ret = 1;
                    printf("%u可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);

                }else
                {
                    ret = 2;
                    printf("%u不可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);
                }

            }

            if(prt->num == 3){
                if(track_lock_check2( prt->id1)==1 && track_lock_check2( prt->id2)==1 && track_lock_check2( prt->id3)==1){
                    ret = 1;
                    printf("%u可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);

                }else
                {
                    ret = 2;
                    printf("%u不可以开放 %u\n",g_route[i].r_id,g_route[i].r_s_start_id);
                }

            }

        }

    }
    return ret;
}

/**
* @brief 进路开放
*        消息触发，判断进路FSM为预先锁闭，再检查其他条件, 满足设置进路FSM为进路开放
*
* @param route_id   进路指针
*
* @return 成功/失败
*/
int16_t route_open(uint32_t route_id)
{

    int16_t i,ret=0;
    uint32_t signal_id;
    for(i = 0;i< 14;i++){
        if(route_id == g_route[i].r_id){
            signal_id = g_route[i].r_s_start_id;
            if(g_route[i].r_t_protect == 0){
                signal_set_dis(signal_id,GREEN_WITHOUT_PROTECT);
                ret = 1;

            }
            if(0!=g_route[i].r_t_protect){
                if(track_lock_check2(g_route[i].r_t_protect)==1){
                    signal_set_dis(signal_id,GREEN_WITH_PROTECT);
                    ret = 2;

                }

            }
        }

    }
    return ret;
}
