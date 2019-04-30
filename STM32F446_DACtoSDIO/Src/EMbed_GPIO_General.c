#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "main.h"
#include "EMbed_GPIO_General.h"

/* USER CODE BEGIN Includes */
#include "uart_general.h"
#include "sd_user_code.h"
#include "WaveHader.h"
/* USER CODE END Includes */

BUTTON_TypeDef hButton;
TICK_TypeDef hsystick;


void GPIO_BT_READ(BUTTON_TypeDef *hBT)
{
	hBT->ucState = 	(HAL_GPIO_ReadPin(GPIO_SW_PORT, GPIO_SW_BT1) << 0) | (HAL_GPIO_ReadPin(GPIO_SW_PORT, GPIO_SW_BT2) << 1)
								| (HAL_GPIO_ReadPin(GPIO_SW_PORT, GPIO_SW_BT3) << 2) | (HAL_GPIO_ReadPin(GPIO_SW_PORT, GPIO_SW_BT4) << 3)
								| (HAL_GPIO_ReadPin(GPIO_SW_PORT, GPIO_SW_BT5) << 4);
	hBT->ucState &= 0xFF;
	
	
	if(hBT->ucState != 0x1F){			//first botton click	
		if(!hBT->ucPressed){
			hBT->ucPressed = HIGH;			
			hBT->uiDelaycount = 0;
			hBT->ucValue = 0;
			hBT->ucValue = hBT->ucState;
		}	
	}
	else{
		if(hBT->uiDelaycount >= SHORTPRESS && hBT->uiDelaycount < LONGPRESS){	//	>=50ms, <2000ms
				BT_SHORT_Event(hBT->ucValue);
		}
		if(hBT->uiDelaycount >= LONGPRESS){		//	>= 2000ms
			//function input START
			BT_LONG_Event_test();
			//funciton input END
		}
		hBT->uiDelaycount = 0;
		hBT->ucPressed = LOW;
	}
}

		
void BT_SHORT_Event(unsigned char bt_state)
{

	switch(bt_state){
		case 0x1E :		//0b xxx1 1110
//			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_1);
			sd_FileWrite(myFileName, myWriteData, sizeof(myWriteData));
		break;
		case 0x1D :		//0b xxx1 1101
//			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_2);
//			sd_FileRead("test_music.wav", myReadData, 44);

			WaveFile_HDR_Read(&WaveHdr);
//			put_str_size(&huart1, myReadData, 44);
		break;
		case 0x1B :		//0b xxx1 1011
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_3);
		break;
		case 0x17 :		//0b xxx1 0111
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_4);

		break;
		case 0x0F :		//0b xxx0 1111
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_5);
		break;
	}
}

void BT_LONG_Event_test()
{
	for(int i=0; i<=10; i++){
		HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_1 | GPIO_LED_2 | GPIO_LED_3 | GPIO_LED_4 | GPIO_LED_5);
		HAL_Delay(GPIO_DLY);
	}
}

//bt TO timer ISR
void BT_TICK_FUNC(BUTTON_TypeDef *hBT)
{
	if(hBT->ucPressed == HIGH){
		hBT->uiDelaycount++;
	}
	else{
		hBT->uiDelaycount = 0;
	}
}

void LED_test()
{
	for(int i=0; i<=4; i++){
		HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_1 | GPIO_LED_2 | GPIO_LED_3 | GPIO_LED_4 | GPIO_LED_5);
		HAL_Delay(GPIO_DLY);
	}
}




