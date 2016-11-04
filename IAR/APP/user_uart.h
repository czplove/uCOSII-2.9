
#define MAX_RS232_RCV_LEN 350  //必须为 256 512 1024 ... 下面用到了 &
#define USART_RX_ERROR_FLAGS (USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)

extern u16    datLength;
extern void USART1_Init(u32 baudrate);

extern void USART2_Init(u32 baudrate,u16 parity);
extern void USART3_Init(u32 baudrate,u16 parity);
extern void SendRS232Data(USART_TypeDef* USARTx,char *pdata,u16 datalen);

extern void USART2_ISR_Handler(void);
extern void USART3_ISR_Handler(void);
