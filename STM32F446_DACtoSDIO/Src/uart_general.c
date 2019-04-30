

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "main.h"
#include "string.h"
#include "uart_general.h"

/* USER CODE BEGIN Includes */
#include "EMbed_GPIO_General.h"
/* USER CODE END Includes */

UART_GENERAL_TypeDef uart1_general;
UART_GENERAL_TypeDef uart4_general;

uint8_t	BLE_Response[2] = "OK";

void GENERAL_UART_IT_Init(UART_HandleTypeDef *huartx)
{
	HAL_UART_MspInit(huartx);
	__HAL_UART_ENABLE_IT(huartx, UART_IT_RXNE);
}

void put_char(UART_HandleTypeDef *huartx, uint16_t Data)
{
	while(__HAL_UART_GET_FLAG(huartx, UART_FLAG_TXE) == RESET);

	huartx->Instance->DR = (Data & (uint16_t)0x01FF);
}

void put_str(UART_HandleTypeDef *huartx, uint8_t *str)
{
	while( *str != NULL)                     // 문자의 마지막에는 '\0'이 들어가 있으므로 
	{
		put_char(huartx, (uint16_t)*str);                // '\0'이 나올 때까지 출력한다.
		str++;
	}
}

void put_str_size(UART_HandleTypeDef *huartx, uint8_t *str, uint16_t dataSize)
{
	uint16_t index = 0;

	for(index = 0; index < dataSize; index++){
		put_char(huartx, (uint16_t)*str);
		str++;
	}
}


void GENERAL_UART_IRQHandler(UART_HandleTypeDef *huartx, unsigned int UARTx, unsigned int CR_LF_STATE)
{
	if((__HAL_UART_GET_FLAG(huartx, UART_FLAG_RXNE) != RESET) 
			&& (__HAL_UART_GET_IT_SOURCE(huartx, UART_IT_RXNE)!=RESET)){


		/* USER CODE BEGIN GENERAL_UART_IRQx */

		if(UARTx ==	USER_UART1){
			uart1_general.rxByte = (uint8_t)(huartx->Instance->DR & (uint8_t)0x00FF);

			switch(uart1_general.rxByte)
			{
			case '<'	:
				uart1_general.rxFlag = ENABLE;
				uart1_general.CellCnt = 0;
				break;
			case '>'	:
				uart1_general.rxFlag = DISENABLE;

				uart1_general.rxStr[uart1_general.CellCnt] = NULL;
				put_str(huartx, uart1_general.rxStr);		//huart1 tx call : Debug-UART
				uart1_general.CellCnt = 0;
				memset(uart1_general.rxStr, NULL, sizeof(uart1_general.rxStr));
				break;
			default	:
				if(uart1_general.rxFlag == ENABLE)
				{
					uart1_general.rxStr[uart1_general.CellCnt++] = uart1_general.rxByte;
				}
				break;
			}
		}
		else if(UARTx == USER_UART4){
			uart4_general.rxByte = (uint8_t)(huartx->Instance->DR & (uint8_t)0x00FF);
			put_char(&huart1, uart4_general.rxByte);

		}

		/* USER CODE END GENERAL_UART_IRQx */

		__HAL_UART_CLEAR_PEFLAG(huartx);
		return;
	}
}

void _USER_HAL_UART_Transmit_IT(UART_HandleTypeDef *huartx, uint8_t *str)
{
	HAL_UART_Transmit_IT(huartx, str, strlen((char *)str));
}

void GENERAL_UART_Variable_Init(UART_GENERAL_TypeDef *uartx_general)
{
	memset(uartx_general,	0, sizeof(UART_GENERAL_TypeDef));
}

void GENERAL_TX_TEST(UART_HandleTypeDef *huartx)
{
	_USER_HAL_UART_Transmit_IT(huartx, (uint8_t *)"uart_ready\r\n");
	HAL_Delay(1000);
	_USER_HAL_UART_Transmit_IT(huartx, (uint8_t *)"uart_start\r\n");
	HAL_Delay(1000);
}



