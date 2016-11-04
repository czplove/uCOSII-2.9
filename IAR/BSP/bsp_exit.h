/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        MICIUM BOARD SUPPORT PACKAGE
*                                               I2C INTERFACE
*
* Filename      : bsp_exit.h
* Version       : V1.00
* Programmer(s) : Yuf
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_I2C present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_EXIT_PRESENT
#define  BSP_EXIT_PRESENT


/*
*********************************************************************************************************
*                                              EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_EXIT_MODULE
#define  BSP_EXIT_EXT
#else
#define  BSP_EXIT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  BSP_EXIT0_ID                             0x0001
#define  BSP_EXIT1_ID                             0x0002
#define  BSP_EXIT2_ID                             0x0004
#define  BSP_EXIT3_ID                             0x0008
#define  BSP_EXIT4_ID                             0x0010
#define  BSP_EXIT5_ID                             0x0020
#define  BSP_EXIT6_ID                             0x0040
#define  BSP_EXIT7_ID                             0x0080
#define  BSP_EXIT8_ID                             0x0100
#define  BSP_EXIT9_ID                             0x0200
#define  BSP_EXIT10_ID                            0x0400
#define  BSP_EXIT11_ID                            0x0800
#define  BSP_EXIT12_ID                            0x1000
#define  BSP_EXIT13_ID                            0x2000
#define  BSP_EXIT14_ID                            0x4000
#define  BSP_EXIT15_ID                            0x8000


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/
CPU_BOOLEAN  BSP_EXIT_Init (CPU_INT08U  exit_id)  ;
static  void  BSP_EXTIISR_Handler      (void) ;
static  void  BSP_EXTI0ISR_Handler     (void) ;
static  void  BSP_EXTI1ISR_Handler     (void);
static  void  BSP_EXTI2ISR_Handler     (void);
static  void  BSP_EXTI3ISR_Handler     (void);
static  void  BSP_EXTI4ISR_Handler     (void);
static  void  BSP_EXTI9_5ISR_Handler   (void);
static  void  BSP_EXTI15_10ISR_Handler (void);

/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/


#endif
