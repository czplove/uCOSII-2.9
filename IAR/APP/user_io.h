
#include  <stm32f10x_lib.h>

extern void USER_GPIO_Init(void);


extern void ExtiIONvicConfig(void);
extern void EXTI9_5ISR_Handler(void); 
extern void EXTI15_10ISR_Handler(void); 