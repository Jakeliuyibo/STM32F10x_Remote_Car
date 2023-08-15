/* ©2015-2016 hznu. All rights reserved.
 + 文件名  ：scheduler.c
 + 描述    ：任务调度
 */
#include "stm32f10x.h"
#include "scheduler.h"
#include "time.h"


/* 循环计数结构体 */
typedef struct
{
    /* 循环运行完毕标志 */
    uint8_t check_flag;
    /* 代码在预定周期内没有运行完错误计数 */
    uint8_t err_flag;
    /* 不同周期的执行任务独立计时 */
    uint16_t cnt_10ms;
    uint16_t cnt_30ms;
    uint16_t cnt_50ms;
    uint16_t cnt_100ms;
    uint16_t cnt_200ms;
    uint16_t cnt_500ms;
} loop_t;


/* 循环计数结构体 */
loop_t loop;

/* 循环任务指针结构体 */
SCHEDULER_TASKS_Struct task;

/* 调度机启动标志位 */
uint8_t SCHEDULER_START_FLAG = 0;


/*----------------------------------------------------------
 + 实现功能：主循环 由主函数调用
----------------------------------------------------------*/
void Scheduler_Main_Loop()
{
    /* 循环周期为1ms */
    if( loop.check_flag == 1 )
    {
        task.pDuty_1ms();     //周期1ms的任务

        if( loop.cnt_10ms >= 10 )
        {
            loop.cnt_10ms = 0;
            task.pDuty_10ms();    //周期10ms的任务
        }
        if( loop.cnt_30ms >= 30 )
        {
            loop.cnt_30ms = 0;
            task.pDuty_30ms();    //周期30ms的任务
        }
        if( loop.cnt_50ms >= 50 )
        {
            loop.cnt_50ms = 0;
            task.pDuty_50ms();    //周期50ms的任务
        }
        if( loop.cnt_100ms >= 100 )
        {
            loop.cnt_100ms = 0;
            task.pDuty_100ms();    //周期100ms的任务
        }
        if( loop.cnt_200ms >= 200 )
        {
            loop.cnt_200ms = 0;
            task.pDuty_200ms();    //周期200ms的任务
        }
        if( loop.cnt_500ms >= 500 )
        {
            loop.cnt_500ms = 0;
            task.pDuty_500ms();    //周期500ms的任务
        }
        
        /* 循环运行完毕 标志清零 */
        loop.check_flag = 0;
    }
}

/*----------------------------------------------------------
 + 实现功能：由Systick定时器调用 周期：1毫秒
----------------------------------------------------------*/
void Scheduler_Loop_timer()
{
    /* 不同周期的执行任务独立计时 */
    loop.cnt_10ms++;
    loop.cnt_30ms++;
    loop.cnt_50ms++;
    loop.cnt_100ms++;
    loop.cnt_200ms++;
    loop.cnt_500ms++;
  
    /* 如果代码在预定周期内没有运行完 */
    if( loop.check_flag == 1)
        /* 错误次数计数 */
        loop.err_flag ++;
    /* 循环运行开始 标志置1 */
    else loop.check_flag = 1;

}

/*----------------------------------------------------------
 + 实现功能：调度机，初始化
----------------------------------------------------------*/
void Scheduler_Init(SCHEDULER_TASKS_Struct initTask)
{
	  if ( !SCHEDULER_START_FLAG )
		{
			  /*设置调度机的任务指针变量*/
			  task.pDuty_1ms   = initTask.pDuty_1ms;
			  task.pDuty_10ms  = initTask.pDuty_10ms;			
			  task.pDuty_30ms  = initTask.pDuty_30ms;
			  task.pDuty_50ms  = initTask.pDuty_50ms;	
			  task.pDuty_100ms = initTask.pDuty_100ms;
			  task.pDuty_200ms = initTask.pDuty_200ms;
			  task.pDuty_500ms = initTask.pDuty_500ms;
      
				/*挂结Scheduler_Loop_timer到SysTick定时中断*/
				Set_SysTick_HookFun(Scheduler_Loop_timer);
		}
}

/*----------------------------------------------------------
 + 实现功能：调度机，启动
----------------------------------------------------------*/
void Scheduler_Start()
{
	  /*开启SysTick定时中断，钩子函数调用功能 */
	  Start_SysTick_HookFun();
	  SCHEDULER_START_FLAG = 1;
	
// 	  while(1)  Scheduler_Main_Loop();
}



/* ©2015-2016 hznu. All rights reserved. */
