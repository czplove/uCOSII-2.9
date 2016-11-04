/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

extern    OS_STK MyTask_Stk[OS_TASK_STK_SIZE];      /* 任务堆栈             */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void   NVIC_Configuration(void);
void   OS_ClockStart(void);

extern void MyTask(void *pdat);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    BSP_Init();
    
    NVIC_Configuration();
  
//    Printf_COMInit();
    
//    printf("I Miss You");
    
    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */

//    OSTaskCreate(TaskOne,(void *)0,TaskOneSTK+OS_TASK_STK_SIZE-1,5);
    OSTaskCreate(MyTask,  (void *)0, (void *)&MyTask_Stk[OS_TASK_STK_SIZE-1],5); //* 建立主任务  堆栈向上
    
    OS_ClockStart();
    
    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
}

/*
static  void TaskOne(void*pg_)
{
pg_ = pg_;
    while(1)
    {
        GPIO_SetBits(BSP_GPIO_LEDS_PORT,BSP_GPIO_LEDS);
        OSTimeDlyHMSM(0,0,1,0);
        GPIO_ResetBits(BSP_GPIO_LEDS_PORT,BSP_GPIO_LEDS);
        OSTimeDlyHMSM(0,0,2,0);
    }
}
*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

#ifdef USE_USART2
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel ;
#else
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel ;
#endif
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

void   OS_ClockStart(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_SetReload(720000);
	SysTick_ITConfig(ENABLE);
	SysTick_CounterCmd(ENABLE);
}


