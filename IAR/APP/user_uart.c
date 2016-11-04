

#include <includes.h>

char g_FileVerDate[]=__DATE__;
char g_FileVerTime[]=__TIME__;
char g_FileVerFile[]=__FILE__;
static char _sCOMRcvBuff[MAX_RS232_RCV_LEN];
static u16 _sCOMRcvCounts=0;
static volatile unsigned _Random;


//OS_Q SMSRcvQue;
extern OS_EVENT  *Qsem;
extern OS_EVENT  *CpldQsem;
extern char SendBuf[];

void USART1_Init(u32 baudrate);

void USART2_Init(u32 baudrate,u16 parity);
void USART3_Init(u32 baudrate,u16 parity);
void SendRS232Data(USART_TypeDef* USARTx,char *pdata,u16 datalen);
void ProcessReceiveUART2Char(u8 RevDate);

void ProcessReceiveUART3Char(u8 RevDate);



void USART1_Init(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  /* Enable GPIO clock */
  //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA ,ENABLE);
  
  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  
  //  USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
  
  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);
}

void USART2_Init(u32 baudrate,u16 parity)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
    // Configure USART2 Tx (PA.02) as alternate function push-pull 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Configure USART2 Rx (PA.03) as input floating 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    USART_InitStructure.USART_BaudRate    = baudrate;
    USART_InitStructure.USART_WordLength  = USART_WordLength_8b;//USART_WordLength_9b;//USART_WordLength_8b;
    USART_InitStructure.USART_StopBits    = USART_StopBits_1;//USART_StopBits_1;
    USART_InitStructure.USART_Parity      = parity;//USART_Parity_No;//USART_Parity_Even;//USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode        = USART_Mode_Rx;// | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);  
  
//  USART_ITConfig(USART2,USART_IT_ERR, ENABLE);  
//  USART_ITConfig(USART2,USART_IT_PE, ENABLE);  
  
    // Enable USART2 
    USART_Cmd(USART2, ENABLE);
}
void USART3_Init(u32 baudrate,u16 parity)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
     // Install USART3 Handler
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);

    // Configure USART3 Rx (PB.11) as input floating 
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    USART_InitStructure.USART_BaudRate    = baudrate;
    USART_InitStructure.USART_WordLength  = USART_WordLength_9b;//USART_WordLength_9b;//USART_WordLength_8b;
    USART_InitStructure.USART_StopBits    = USART_StopBits_1;//USART_StopBits_1;
    USART_InitStructure.USART_Parity      = parity;//USART_Parity_No;//USART_Parity_Even;//USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode        = USART_Mode_Rx;// | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);  
  
//  USART_ITConfig(USART2,USART_IT_ERR, ENABLE);  
  
    // Enable USART2 
    USART_Cmd(USART3, ENABLE);
}

void SendRS232Data(USART_TypeDef* USARTx,char *pdata,u16 datalen)
{
    int i;
    for(i=0;i<datalen;i++)
    {
        USART_SendData(USARTx, (u8) pdata[i]);  
        /* Loop until the end of transmission */
         while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
//       while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {
        }    
    }
}



void USART2_ISR_Handler(void)
{
  u8 RevDate;
  int UsartStatus;
  OSIntEnter();                  // 调用“进入中断服”务函数
  //  OSSemPost(Sem);                  // 发送信号量
  UsartStatus = USART2->SR;
  if(UsartStatus&USART_IT_RXNE)
  {
    RevDate=(u8)USART2->DR;//_USART_DR;
    
    ProcessReceiveUART2Char(RevDate);
  }
  else if (UsartStatus & USART_RX_ERROR_FLAGS) 
  {  // Any error ?
    _Random = USART2->DR;//_USART_DR;                      // => Discard data
  } 
  OSIntExit();       
}
void USART3_ISR_Handler(void)
{
  u8 RevDate;
  int UsartStatus;
  OSIntEnter();                  // 调用“进入中断服”务函数
  //  OSSemPost(Sem);                  // 发送信号量
  UsartStatus = USART3->SR;
  if(UsartStatus&USART_IT_RXNE)
  {
    RevDate=(u8)USART3->DR;//_USART_DR;
    
    ProcessReceiveUART3Char(RevDate);
  }
  else if (UsartStatus & USART_RX_ERROR_FLAGS) 
  {  // Any error ?
    _Random = USART3->DR;//_USART_DR;                      // => Discard data
  } 
  OSIntExit();       
}

void ProcessReceiveUART2Char(u8 RevDate)
{
}

void ProcessReceiveUART3Char(u8 RevDate)
{
}
