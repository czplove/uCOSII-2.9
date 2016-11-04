#include <includes.h>
#include  <stm32f10x_lib.h>
#define  N_MESSAGES       					256

#define  OS_TaskUart2Rec_STK_SIZE           128
#define  OS_TaskUart3Rec_STK_SIZE           128
#define  SENDBUF_LENGTH					    50



OS_STK   MyTask_Stk[OS_TASK_STK_SIZE];      /* �����ջ             */

OS_STK   Task_Uart2_Rec_Stk[OS_TaskUart2Rec_STK_SIZE];      /* �����ջ             */
OS_STK   Task_Uart3_Rec_Stk[OS_TaskUart3Rec_STK_SIZE];      /* �����ջ             */


OS_EVENT  *Qsem;
OS_EVENT  *CpldQsem;
void  *MsgGrp[N_MESSAGES];     /*��Ϣ����,��Ϣ�������Ÿ���Ϣ��ָ��*/

char SendBuf[SENDBUF_LENGTH];


extern OS_EVENT *lcdsem;            /* ����һ���ź���       */
extern char g_FileVerDate[];


void Wdt_Init(void);
void iwdg_init(u8 prer,u16 rlr) ;
void Task_Uart2_Rec (void *pdat) ;
void Task_Uart3_Rec(void * pdat) ;
int ProcessUart2Data(INT8U * pData,int iLen);
int ProcessUart3Data(INT8U * pData,int iLen);


//--------------------------------
//       ����0 'MYTASK                                                     */
//------------------------------------
void MyTask (void *pdat) 
{
    pdat = pdat; 
//    Wdt_Init();
    iwdg_init(254,10);

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                                   */
#endif
    Qsem = OSQCreate( &MsgGrp[0], N_MESSAGES ); /*������Ϣ����,����Ϊ��Ϣָ���������ַ*/
    CpldQsem = OSQCreate( &MsgGrp[0], N_MESSAGES ); /*������Ϣ����,����Ϊ��Ϣָ���������ַ*/
    if(Qsem== (void *)0)
    {
      sprintf(SendBuf,"������Ϣ����ʧ��...\r\n");
    }

//	 OSTaskCreate(TaskAutoUART,  (void *)0, (void *)&TaskAutoUART_Stk[OS_TaskAutoUART_STK_SIZE-1],11); //* ��������2     
	 
    OSTaskCreate(Task_Uart2_Rec, (void *)0, (void *)&Task_Uart2_Rec_Stk[OS_TaskUart2Rec_STK_SIZE-1],6); //* ��������1
    OSTaskCreate(Task_Uart3_Rec, (void *)0, (void *)&Task_Uart3_Rec_Stk[OS_TaskUart3Rec_STK_SIZE-1],12); //* ��������2
     //    OSTaskDel (OS_PRIO_SELF); //ɾ���Լ�
    //   Str_Q = OSQCreate( &MsgGrp[0], N_MESSAGES ); /*������Ϣ����,����Ϊ��Ϣָ���������ַ
    
  while(1)
  	{
  	}

  
}





//--------------------------------
//       ���� UART2 ���ݴ��������������                                              
//------------------------------------
void Task_Uart2_Rec (void *pdat) 
{
    INT8U  err;
    char *pData;
    pdat = pdat; 
    
    /*
    BSP_IntVectSet(BSP_INT_ID_EXTI9_5, EXTI9_5ISR_Handler);
    BSP_IntPrioSet(BSP_INT_ID_EXTI9_5,2);
    BSP_IntEn(BSP_INT_ID_EXTI9_5);
    */
    USART2_Init(9600,USART_Parity_No);//connect card reader       
    BSP_IntVectSet(BSP_INT_ID_USART2, USART2_ISR_Handler);
    BSP_IntPrioSet(BSP_INT_ID_USART2,3);
    BSP_IntEn(BSP_INT_ID_USART2);

    while (1) 
    {
      pData = OSQPend(CpldQsem, 0,&err); /* Get message */
      if(err == OS_ERR_NONE)
      {
        ProcessUart2Data((char*)pData,strlen(pData));
      }
      else
      {
      }
    }          
}


//--------------------------------
//       ���� UART3 ���ݴ��������������                                              
//------------------------------------
void Task_Uart3_Rec (void *pdat) 
{
    INT8U  err;
    char *pData;
    pdat = pdat; 
    
    /*
    BSP_IntVectSet(BSP_INT_ID_EXTI9_5, EXTI9_5ISR_Handler);
    BSP_IntPrioSet(BSP_INT_ID_EXTI9_5,2);
    BSP_IntEn(BSP_INT_ID_EXTI9_5);
    */
    USART3_Init(9600,USART_Parity_No);//connect card reader       
    BSP_IntVectSet(BSP_INT_ID_USART3, USART3_ISR_Handler);
    BSP_IntPrioSet(BSP_INT_ID_USART3,4);
    BSP_IntEn(BSP_INT_ID_USART3);

    while (1) 
    {
      pData = OSQPend(CpldQsem, 0,&err); /* Get message */
      if(err == OS_ERR_NONE)
      {
        ProcessUart2Data((char*)pData,strlen(pData));
      }
      else
      {
      }
    }          
}

/*******************************************************************************
* Function Name  : SystemReset
* Description    : Configures the port pin connected to the push button. GPIO_D_4
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
__asm void SystemReset(void)
{
 MOV R0, #1           //; 
 MSR FAULTMASK, R0    //; ���FAULTMASK ��ֹһ���жϲ���
 LDR R0, =0xE000ED0C  //;
 LDR R1, =0x05FA0004  //; 
 STR R1, [R0]         //; ϵͳ�����λ   
 
deadloop
    B deadloop        //; ��ѭ��ʹ�������в�������Ĵ���
}
*/

int ProcessUart2Data(INT8U * pData,int iLen)
{

  return 0;
}

int ProcessUart3Data(INT8U*pData,int iLen)
{

  return 0;
}

void Wdt_Init(void)
{
 // Enable write access to IWDG_PR and IWDG_RLR registers 
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //IWDG->KR = 0x5555
 
 // IWDG counter clock: 40KHz(LSI) / 64 = 0.625 KHz 
 IWDG_SetPrescaler(IWDG_Prescaler_256);   //IWDG->PR = 0x06;

 // Set counter reload value to 1250 
 IWDG_SetReload(0xfff);           //IWDG->RLR =0xFFF

//  Red IWDG counter
  IWDG_ReloadCounter();   //IWDG->KR = 0xAAAA

// Enable IWDG (the LSI oscillator will be enabled by hardware) 
// IWDG_Enable();   //IWDG->KR = 0xCCCC

}
//���Ź���������
//��ʼ���������Ź�
//prer����Ƶ����0~7��ֻ�е�3λ��Ч����
//��Ƶ����=4*2^prer���ֵΪ256
//rlr: ��װ�ؼĴ���ֵ: ��11 λ��Ч. 
// ʱ�����(���):Tout=((4��2^prer) ��rlr)/40 (ms).
void iwdg_init(u8 prer,u16 rlr) 
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    IWDG->KR=0X5555;//ʹ�ܶ�IWDG->PR��IWDG->RLR��д                                                
    IWDG->PR=prer;  //���÷�Ƶϵ��   
    IWDG->RLR=rlr;  //�Ӽ��ؼĴ��� IWDG->RLR  
    IWDG->KR=0XAAAA;//reload                                            
//    IWDG->KR=0XCCCC;//ʹ�ܿ��Ź�  
}
//ι�������Ź�
void iwdg_feed(void)
{
    IWDG->KR=0XAAAA;//reload                                            
}