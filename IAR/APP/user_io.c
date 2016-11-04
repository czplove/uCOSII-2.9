

#include <includes.h>

extern OS_EVENT  *RcvQue;

void USER_GPIO_Init(void);

void USER_GPIO_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   //启动GPIOA CLOCK
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB ,ENABLE); 
    //启动AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
    
    //for input 1~4
    GPIO_InitStructure.GPIO_Pin 	=   GPIO_Pin_12|GPIO_Pin_13| GPIO_Pin_14|GPIO_Pin_15;      
                                           //input  IO-sel
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;//GPIO_Mode_Out_OD;//GPIO_Mode_Out_PP;GPIO_Mode_AF_PP;//
    GPIO_Init(GPIOB, &GPIO_InitStructure);    
}



void ExtiIONvicConfig(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Enable the EXTI15_10 Interrupt */      //PB.11  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line    = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

}

void EXTI3ISR_Handler(void) ;
void EXTI3ISR_Handler(void)  //PA.03   uart2  
{

  OSIntEnter();                  // 调用“进入中断服”务函数
//  OSSemPost(Sem);                  // 发送信号量
  EXTI->PR |= 1 << 3;                  // 清楚LINE0上的中断标志位 
  OSIntExit();                           // 调用“退出中断”服务函数
}

u8 led = 0;
void EXTI9_5ISR_Handler(void); 
void EXTI9_5ISR_Handler(void) //
{
//  OSIntEnter();                  // 调用“进入中断服”务函数
  
//  OSIntExit();                           // 调用“退出中断”服务函数
}


void EXTI15_10ISR_Handler(void);
void EXTI15_10ISR_Handler(void) //PA.10   //PB.11
{

  OSIntEnter();                  // 调用“进入中断服”务函数
  //  OSSemPost(Sem);                  // 发送信号量
 
  if((EXTI->PR & EXTI_Line11) == EXTI_Line11)
  	{
  	}
  
  OSIntExit();                           // 调用“退出中断”服务函数
}
//end
//BSP_IntVectSet(BSP_INT_ID_USART1, BSP_IntHandlerUSART1);
//BSP_IntEn(BSP_INT_ID_USART1);