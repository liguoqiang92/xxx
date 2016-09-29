
/**
* @file route_lock.c
* @brief
* @author liguoqiang
* @date 2016-09-26
*
* $Id$
*/

#include "routelock.h"
#include "routelock_in.h"
#include "routeopen.h"
#include "stdio.h"




/*
* @brief 区段空闲未锁闭检查
*
* @param track_id   区段id
*
* @return 区段锁闭状态1/2
*/
int16_t track_lock_check(uint32_t track_id)
{
    int16_t i,ret = 0;

    for(i = 0;i< TRACK_NUM;i++){
        if(track_id == g_track[i].t_id ){
            if(g_track[i].t_status ==2 && g_track[i].t_lock == 2){

                printf("\n%x  %s  %u %u\n",g_track[i].t_id,g_track[i].t_name,g_track[i].t_status,g_track[i].t_lock);
                printf("%x区段空闲未锁闭条件满足\n",g_track[i].t_id);
                ret = 1;

            }else
            {

                printf("%x区段条件不满足\n",g_track[i].t_id);
                ret = 2;
            }

        }

    }

    return ret;

}



/**
* @brief 进路预先锁闭(包括锁闭保护区段)
*
* @param route_id  进路指针
*
* @return 允许/拒绝 1/2/3/4 (3/4代表锁闭保护区段成功/失败)
*/
int16_t route_lock_advance(uint32_t route_id)
{
    int16_t i,m,ret=0;
    r_t_list_t *prt;


    for(i = 0;i< ROUTE_NUM;i++){
        if(route_id == g_route[i].r_id){
            prt = g_route[i].r_t_list;
            if(prt->num == 1){
                if(track_lock_check( prt->id1)==1){
                    track_lock(prt->id1);
                    if(track_lock(prt->id1)==1){
                        g_route[i].r_status =1;
                        g_route[i].r_lock_advance = 1;

                        route_open(route_id);
                    }
                    ret = 1;
                    printf("%x可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);

                }else
                {
                    ret = 2;
                    printf("%x不可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);
                }


            }
            if(prt->num == 2){
                if(track_lock_check( prt->id1)==1 && track_lock_check( prt->id2)==1){
                    track_lock(prt->id1);
                    track_lock(prt->id2);
                    if(track_lock(prt->id1)==1 && track_lock(prt->id2)==1){
                        g_route[i].r_status = 1;
                        g_route[i].r_lock_advance = 1;

                        route_open(route_id);

                    }
                    ret = 1;
                    printf("%x可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);

                }else
                {
                    ret = 2;
                    printf("%x不可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);
                }

            }
            if(prt->num == 3){
                if(track_lock_check( prt->id1)==1 && track_lock_check( prt->id2)==1 && track_lock_check( prt->id3)==1){
                    track_lock(prt->id1);
                    track_lock(prt->id2);
                    track_lock(prt->id3);
                    if(track_lock(prt->id1)==1 && track_lock(prt->id2)==1 && track_lock(prt->id3)==1){
                        g_route[i].r_status =1;
                        g_route[i].r_lock_advance = 1;

                        route_open(route_id);

                    }
                    ret = 1;
                    printf("%x可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);

                }else
                {
                    ret = 2;
                    printf("%x不可以预先锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_advance);
                }

            }
            if(0 != g_route[i].r_t_protect){
                for(m = 0;m < TRACK_NUM;m++){
                    if(g_route[i].r_t_protect == g_track[m].t_id){
                        g_track[m].t_lock = 1;
                        ret = 3;
                        printf("%x锁闭%u保护区段%u\n",g_route[m].r_id,g_track[m].t_id,g_track[m].t_lock);

                    }else{
                        ret = 4;
                    }

                }

            }

        }

    }
    return ret;
}


/**
* @brief 进路接近锁闭
*        消息触发，检查进路FSM，若为进路开放，设置进路FSM为接近锁闭
*
* @param route_id   进路指针
*
* @return 成功/失败  1/2
*/
int16_t route_lock_prox(uint32_t route_id)
{
    int16_t i,ret=0;

    for(i = 0;i<ROUTE_NUM;i++){
        if(route_id == g_route[i].r_id){
            if(g_route[i].r_lock_advance == 1){
                g_route[i].r_lock_prox = 1;
                g_route[i].r_lock_advance = 2;
                printf("%x可以接近锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_prox);
                ret = 1;

            }else
            {
                printf("%x不可以接近锁闭 %u\n",g_route[i].r_id,g_route[i].r_lock_prox);
                ret = 2;

            }

        }

    }
    return ret;
}

/*
* @brief 区段锁闭设置
*
* @param track_id   区段id
*
* @return 区段锁闭状态1/2
*/
int16_t track_lock(uint32_t track_id)
{
    int16_t i,ret=0;

    for(i = 0;i< TRACK_NUM;i++){
        if(track_id == g_track[i].t_id ){
            g_track[i].t_lock = 1;
            printf("%u  %s  %u %u\n",g_track[i].t_id,g_track[i].t_name,g_track[i].t_status,g_track[i].t_lock);
            printf("%x区段锁闭\n",g_track[i].t_id);
            ret = 1;

        }else{
            ret = 2;
        }

    }
    return ret;
}
