#ifndef __UART_GENERAL_H__
#define __UART_GENERAL_H__

#include "stm32f4xx.h"

#define USER_UART1		1
#define USER_UART2		2
#define USER_UART3		3
#define USER_UART4		4
#define USER_UART5		5
#define USER_UART6		6

#define ENABLE			1
#define DISENABLE		0

#define CR_LF_ENABLE			1
#define CR_LF_DISENABLE		0

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart4;

typedef struct
{
	uint8_t txStr[256];
	uint8_t rxStr[256];
	uint8_t rxByte;
	uint8_t rxFlag;
	uint8_t CellCnt;
	
	uint8_t	PacketBit;
	uint8_t	PacketBuff[256];
}UART_GENERAL_TypeDef;

extern UART_GENERAL_TypeDef uart1_general;
extern UART_GENERAL_TypeDef uart4_general;

void GENERAL_UART_IT_Init(UART_HandleTypeDef *huartx);

void put_char(UART_HandleTypeDef *huartx, uint16_t Data);
void put_str(UART_HandleTypeDef *huartx, uint8_t *str);
void put_str_size(UART_HandleTypeDef *huartx, uint8_t *str, uint16_t dataSize);

void _USER_HAL_UART_Transmit_IT(UART_HandleTypeDef *huartx, uint8_t *str);

void GENERAL_UART_IRQHandler(UART_HandleTypeDef *huartx, unsigned int UARTx, unsigned int CR_LF_STATE);

void GENERAL_UART_Variable_Init(UART_GENERAL_TypeDef *uartx_general);
void GENERAL_TX_TEST(UART_HandleTypeDef *huartx);




#endif /* __UART_GENERAL_H__ */
