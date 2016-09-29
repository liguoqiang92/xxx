#include <stdio.h>
#include <string.h>

#include "routearr.h"
#include "public_arr.h"
#include "ci_public_comm.h"


/*����ȫ�ֱ���*/
track_t *t_track;
route_t *t_route;
signal_t *t_signal;



int32_t track_check(track_t *list, uint32_t number)
{
    uint32_t list_num = 0;
    track_t *t_list;

    uint32_t i;
    uint32_t t_sign = 0;           /*track״̬����־*/

    t_list = list;                 /*��������*/
    list_num = number;             /*���β���ָ��*/

    /*�������״̬*/
    for(i=0; i<list_num; i++)
    {
        /*����״̬��������*/
        if((t_list+i)->t_blockade == UNBLOCKADE)
            if((t_list+i)->t_lock == UNLOCK)
                if((t_list+i)->t_status == CLEAR)
                    t_sign = t_sign;

                else
                {
                    t_sign = 1;
                    printp("track %d occu\n", i);
                }
            else
            {
                t_sign =1;
                printp("track %d lock\n", i);
            }
        else
        {
            t_sign = 1;
            printp("track %d blockade\n", i);
        }
    }

    if(t_sign > 0)
    {
        t_sign = 0;
        return R_ERROR;
    }
    else
        return R_OK;
}


int32_t signal_check(signal_t *signal_id)
{
    signal_t *signal;
    uint32_t s_sign = 0;             /*�źŻ����ɹ�/ʧ�ܱ�־*/

    signal = signal_id;              /*�źŻ�����ָ��*/

    printp("signal name = %s\n", signal->s_name);

    if(signal->s_blockade == UNBLOCKADE)
        s_sign = s_sign;
    else
        s_sign = 1;

    if(s_sign == 0)
        return R_OK;
    else
        return R_ERROR;


}

int32_t route_choose_check(route_t *route_id)
{
    route_t *route;                 /*��·ָ��*/
    signal_t *signal;
    track_t *track;

    uint32_t i;
    uint32_t sign_check = 0;        /*��·���ɹ�/ʧ�ܱ�־*/
    uint32_t t_list_num = 0;        /*��������*/
    r_t_list_t *r_t_list;           /*�����б�*/
    track_t *t_list;                /*���β���ָ��*/
    signal_t *r_s_start;            /*ʼ���źŻ�����ָ��*/

    route = route_id;
    track = t_track;
    signal = t_signal;

    /*�������״̬ --> δ������δ���ա�����*/
    r_t_list = route->r_t_list;                     /*��ȡ�����б�*/
    t_list_num = r_t_list->num;                     /*��ȡ��������*/

    for(i=0; i<TRACK_NUM; i++)                      /*�������β���ָ��*/
    {
        //if(track[i].t_id == (r_t_list->id1)->t_id)
        if((track+i)->t_id == r_t_list->id1)
        {
            t_list = &track[i];
        }
    }
    printp("r_t_list[0] = %d\n", r_t_list->num);

    if(track_check(t_list, t_list_num) == 0)
        sign_check += 1;
    else
        printp("check track fail!\n");


    /*����źŻ�״̬ --> δ�������ر�*/
    for(i=0; i<SIGNAL_NUM; i++)                      /*����ʼ���źŲ���ָ��*/
    {
        if(route->r_s_start_id == (signal+i)->s_id)
            r_s_start = (signal+i);
    }
    if(signal_check(r_s_start) == 0)
        sign_check += 1;
    else
        printp("check signal fail!\n");


    /*������ --> δ������δ����*/

    /*���жԽ�· -- >δ����*/


    if(sign_check == 2)
        return R_OK;
    else
        return R_ERROR;
}

int32_t route_arrange(msg_t m, void *p)
{
    int16_t ret = RET_SUCCESS;

    if(CI_R_ARRAY_SUCC != get_event(m))
	{
        ret = RET_FSM;
	    return ret;
	}
    else
    {

//    route_t *route;

//    uint32_t i = 0;
//    uint32_t w_sign = 0;              /*����״̬��־*/
//    uint32_t w_index = 0;           /*����ָ��ƫ��*/
//    uint32_t w_list_num = 0;        /*��·�ڵ�������*/
//    r_w_list_t *r_w_list;           /*��·�����б�*/
//    switch_t *w_list;               /*��·�������ָ��*/

//    route = route_id;

    /*��ʼ��*/
//    r_w_list = route->r_w_list;      /*��ȡ�����б�*/
//    w_list_num = r_w_list->num;      /*��ȡ��������*/

//    for(i=0; i<W_MAX; i++)           /*��ȡ�������ָ��*/
/*    {
        if(sswitch[i].w_id == r_w_list->id1)
        {
            w_list = &sswitch[i];
        }
    }
*/
    /*������״̬*/
/*
    for(i=0; i<w_list_num; i++)
    {
        if(switch_check_status(w_list+i, 0x55) == 0)
        {
            w_sign = 1;
            w_index = i;
            printp("switch %d fail\n", i);
        }

    }
    if(w_sign > 0)
    {
        w_sign = 0;
        printp("check switch fail\n");
*/
        /*�⶯������ָ��λ��*/
/*      (w_list+w_index)->w_status = 0x55;


        if(switch_check_status(w_list+w_index, 0x55) == 0)
        {
            printp("move switch %d fail\n", w_index);
        }
        else
            printp("move switch %d ok\n", w_index);
        }
        else
            printp("switch ok!\n");
*/

    return R_OK;
  }
}

//uint32_t route_choose(uint32_t s_start_id, uint32_t s_end_id)
int32_t route_choose(msg_t m, void *p)
{
    int16_t ret = RET_SUCCESS;

    //if(CI_R_UNLOCK_SELLECT != get_event(m))
    if(0)
        ret = RET_FSM;
    else
    {

        uint32_t s_one = 0;          /*ʼ���źŻ�*/
        uint32_t s_two = 0;          /*ĩ���źŻ�*/
        route_t *route;              /*��·ָ��*/

        uint8_t i = 0;               /*ѭ������*/
        uint8_t r_index = 0;         /*ָ��ƫ����*/
        uint32_t r_id = 0;           /*route ID*/

        /*��ʼ��*/
        //s_one = s_start_id;
        //s_two = s_end_id;

        s_one = *(uint32_t *)p;
        s_two = *((uint32_t *)p+1);
        //printf("s_one = %d, s_two = %d\n", s_one, s_two);
        route = t_route;


        /*��ȡ��·ID��*/
        for(i=0; i<ROUTE_NUM; i++)
        {
            if((route+i)->r_s_start_id == s_one && (route+i)->r_s_end_id == s_two)
            {
                r_id = (route+i)->r_id;
                r_index = i;
            }
        }
        printp("r_id = %d\n", r_id);

        /*���ѡ·����*/
        if(route_choose_check(route+r_index) == 0)
        {
            return r_id;
        }
        else
        {
            printp("Choose route fail!\n");
            return R_ERROR;

        }
      }

}



int32_t main_test(route_t *route, track_t *track, signal_t *signal)
{

    //uint32_t signal_start = 2003;
    //uint32_t signal_end = 2004;

    //uint32_t r_id;

    t_route = route;
    t_track = track;
    t_signal = signal;

    printp("t_route->r_id = %d\n", t_route->r_id);
    return(t_route->r_id);

    //data_init();

    //printp("signal = %d\n",route->r_s_start_id);

    //r_id = route_choose(signal_start, signal_end);

    //return r_id;

}
