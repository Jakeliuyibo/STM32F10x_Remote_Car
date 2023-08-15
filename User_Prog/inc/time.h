/* ©2015-2016 Beijing Bechade Opto-Electronic, Co.,Ltd. All rights reserved.
 + 文件名  time.h

*/
#ifndef _TIME_H_
#define _TIME_H_

#include "stm32f10x.h"
#include "device_timer.h"


/*----------------------------------------------------------
 + 实现功能：设置，SysTick中断，外部钩子函数调用
 + 返回参数：无
----------------------------------------------------------*/
extern void Set_SysTick_HookFun(void (*hookFun)());

/*----------------------------------------------------------
 + 实现功能：启动，SysTick中断，外部钩子函数调用
 + 返回参数：无
----------------------------------------------------------*/
extern void Start_SysTick_HookFun(void);

/*----------------------------------------------------------
 + 实现功能：获取系统总运行时间
 + 返回参数：微秒
----------------------------------------------------------*/
uint32_t GetSysTime_us(void);

/*----------------------------------------------------------
 + 实现功能：延时
 + 调用参数：微秒
----------------------------------------------------------*/
extern void Delay_us(uint32_t);

/*----------------------------------------------------------
 + 实现功能：延时
 + 调用参数：毫秒
----------------------------------------------------------*/
extern void Delay_ms(uint32_t);

/*----------------------------------------------------------
 + 实现功能：计算两次点用时间间隔
 + 调用参数：统计时间项数组
 + 返回参数：两次时间间隔 单位：秒
----------------------------------------------------------*/
extern float Call_timer_cycle(u8);

/*----------------------------------------------------------
 + 实现功能：时间统计初始化
----------------------------------------------------------*/
extern void Cycle_Time_Init(void);

#endif
/* ©2015-2016 Beijing Bechade Opto-Electronic, Co.,Ltd. All rights reserved. */
