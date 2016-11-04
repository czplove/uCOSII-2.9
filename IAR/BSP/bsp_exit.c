/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
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
*                                     MICIUM BOARD SUPPORT PACKAGE
*                                        GPIO EXIT
*                                                                         
*
* Filename      : bsp_exit.c
* Version       : V1.00
* Programmer(s) : YF
* Date          :20120810
*********************************************************************************************************
* Note(s)       :
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GPIO_MODULE
#include <bsp.h>

extern void EXTI9_5ISR_Handler(void); 
extern void EXTI15_10ISR_Handler(void);
/*
*********************************************************************************************************
*                                              LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void        BSP_EXTIISR_Handler  (void); 
static  void        BSP_EXTI0ISR_Handler  (void);
static  void        BSP_EXTI1ISR_Handler  (void);
static  void        BSP_EXTI2ISR_Handler  (void);
static  void        BSP_EXTI3ISR_Handler  (void);
static  void        BSP_EXTI4ISR_Handler  (void);
static  void        BSP_EXTI9_5ISR_Handler  (void);
static  void        BSP_EXTI15_10ISR_Handler  (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        BSP_I2C_Init()
*
* Description : Initialize the I2C.
*
* Argument(s) : i2c_id     I2C peripheral ID
*                              BSP_I2C_ID_I2C1
*                              BSP_I2C_ID_I2C2
*
*               freq       I2C clock speed. It must be set to a value lower than 100 kHz (Standard Mode) or
*                          400 Khz (Fast mode)
*
* Return(s)   : DEF_OK     If the I2C peripheral was initialized
*               DEF_FAIL   If the I2C peripheral could not be initialized.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_EXIT_Init (CPU_INT08U  exit_id)  ;
CPU_BOOLEAN  BSP_EXIT_Init (CPU_INT08U  exit_id)                   
{
   switch (exit_id) 
   {
   case  BSP_EXIT0_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI0 , BSP_EXTI0ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI0); //中断允许函数
     }
     break;
   case  BSP_EXIT1_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI1 , BSP_EXTI1ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI1); //中断允许函数
     }
     break;
   case  BSP_EXIT2_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI2 , BSP_EXTI2ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI2); //中断允许函数
     }
     break;
   case  BSP_EXIT3_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI3 , BSP_EXTI3ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI3); //中断允许函数
     }
     break;
   case  BSP_EXIT4_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI4 , BSP_EXTI4ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI4); //中断允许函数
     }
     break;
   case  BSP_EXIT5_ID:
   case  BSP_EXIT6_ID:
   case  BSP_EXIT7_ID:
   case  BSP_EXIT8_ID:
   case  BSP_EXIT9_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI9_5 , BSP_EXTI9_5ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI9_5); //中断允许函数
     }
     break;
   case  BSP_EXIT10_ID:
   case  BSP_EXIT11_ID:
   case  BSP_EXIT12_ID:
   case  BSP_EXIT13_ID:
   case  BSP_EXIT14_ID:
   case  BSP_EXIT15_ID:
     {       
       BSP_IntVectSet  (BSP_INT_ID_EXTI15_10 , BSP_EXTI15_10ISR_Handler); //中断设置函数
       BSP_IntEn (BSP_INT_ID_EXTI15_10); //中断允许函数
     }
     break;
   } 
 return 0;  
}

/*
*********************************************************************************************************
*                                        BSP_EXITx_EventISR_Handler()
*
* Description : Generic ISR events handler
*
* Argument(s) : exit                  EXIT peripheral number.

*
* Return(s)   : none.
*
*
* Note(s)     : none.
*********************************************************************************************************
*/
static  void  BSP_EXTIISR_Handler    (void) 
{
//  OS_ENTER_CRITICAL();    /* Tell uC/OS-II that we are starting an ISR          */ 
  OSIntNesting++; 
//  OS_EXIT_CRITICAL();  
  
  //Add your code
  
//  OSIntExit();            /* Tell uC/OS-II that we are leaving the ISR          */ 
}
static  void  BSP_EXTI0ISR_Handler    (void) 
{
//    if(EXTI->PR &EXTI_Line0)
//    EXTI0ISR_Handler();
}


static  void  BSP_EXTI1ISR_Handler    (void)
{
//    EXTI1ISR_Handler();
}

static  void  BSP_EXTI2ISR_Handler    (void)
{
//    EXTI2ISR_Handler();
}
static  void  BSP_EXTI3ISR_Handler    (void)
{
//  EXTI3ISR_Handler();
}
static  void  BSP_EXTI4ISR_Handler    (void)
{
//  EXTI4ISR_Handler();
}
static  void  BSP_EXTI9_5ISR_Handler    (void)
{
  EXTI9_5ISR_Handler();
}
static  void  BSP_EXTI15_10ISR_Handler    (void)
{
  EXTI15_10ISR_Handler();
}


