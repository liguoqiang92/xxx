#ifndef  _UNIFW_H
#define  _UNIFW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file unifw.h
 * @brief define public header for UNIfied FrameWork
 * @author 003
 * @date 2016-03-25
 *
 * @Log
 * 	v0.1.0, 003, 2016-03-25
 * 		initial version
 *
 * $Id$
 */
#include "unifw_errno.h"

/* for Windows and Linux, using stardard header files */

#if defined(_WINDOWS)
#include <windows.h>
#include <process.h>

#elif defined(__linux)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* for using socket and threads */
typedef int SOCKET;
typedef int HANDLE;
typedef struct sockaddr SOCKADDR;

#define MAX_PATH 1024

#define _getwch getchar
#define _putwch putchar
#define _putch(c) write(1, &c, 1)
#else
#include "arch_config.h"
#endif

#if defined(_WINDOWS) || defined(__linux) || defined(POSIX)
#include <stdint.h>
#include <stdio.h>
#ifdef _WINDOWS
#include <conio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EnableInterrupts
#define DisableInterrupts

#define printp printf
#define STATIC

#else
#ifndef _STDINT
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
#endif
#endif

#ifndef FAR
#define FAR
#endif

#ifndef INTERRUPT
#define INTERRUPT
#endif

#ifndef TRUE
#define TRUE 1U
#endif

#ifndef FALSE
#define FALSE 0U
#endif

#ifndef NULL
#define NULL (void *)(0)
#endif

#ifdef _WINDOWS
#if defined(DLL_OUT)
#define LIB_TYPE __declspec(dllexport)
#elif defined(DLL_IN)
#define LIB_TYPE __declspec(dllimport)
#else
#define LIB_TYPE 
#endif
#else
#define LIB_TYPE
#endif

#ifndef MAIN
#define MAIN main
#endif

#ifndef STATIC
#define STATIC static
#endif

#ifndef TICK_BASE
#if defined(_WINDOWS) || defined(__linux)
#define TICK_BASE 100	/**< if not defined, default to 100 ms on OS */
#else
#define TICK_BASE 10	/**< if not defined, default to 10ms on RTOS */
#endif
#endif

typedef int16_t fsm_t;

/** ��������ģ�� for module descriptor */
typedef struct _mod_dscrp
{
	char     name[15]   ;
	char     nzero      ;
	char     scmrev[15] ;
	char     scmzero    ;
	char     time[31]   ;
	char     tzero      ;
	uint8_t  major      ;
	uint8_t  minor      ;
	uint16_t patch      ;
}mod_dscrp_t            ;

/**
 * @brief ����������
 */
typedef struct data_item
{
	char 	*name ; /*-<  �Ƚ��ַ��� */
	int16_t width ; /*-< ���ݵ�size������Ϊ�޷�����������Ϊ�з����� */
	void	*ptr  ; /*-< ͨ�õ�Ŀ��ָ�� */
}data_item_t      ;

void unit_print_module(const mod_dscrp_t *mod); /*-< supply by unitframe */

/*=== public definitions ===*/

/** ��ȡ��ϢԴID */
#define get_msg_src(msg) (msg/256U)
/** ��ȡ��Ϣ���� */
#define get_msg_type(msg) (msg%256U)
/** ��ȡ��Ϣ���� */
#define get_msg_len(msg) (msg%256U)
/** ������Ϣ */
#define make_msg(src, type) ((uint16_t)((uint16_t)src*256U+type))
/** ���ɻ�����Ϣ */
#define make_base_msg(base, value) (base+value)

#define _TAB(n) n##table
#define _TAB_L(n) n##table_len

#define CPPUNIT_EASSERT(a,b) CPPUNIT_ASSERT_EQUAL((int)a, (int)b)

#ifdef __cplusplus
}
#endif

#endif   /*_UNIFW_H*/

