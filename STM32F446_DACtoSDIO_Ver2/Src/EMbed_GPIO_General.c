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

char Sine8bitTo16bit_ChangeFlag = 0;
char Music8bitTo16bit_ChangeFlag = 0;


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
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_1);

			if(Sine8bitTo16bit_ChangeFlag == 0){
				WaveFile_HDR_Read(&WaveHdr, "sinewave_8bit.wav");
				Sine8bitTo16bit_ChangeFlag = 1;
			}
			else{
				WaveFile_HDR_Read(&WaveHdr, "sinewave.wav");
				Sine8bitTo16bit_ChangeFlag = 0;
			}

		break;
		case 0x1D :		//0b xxx1 1101
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_2);

			if(Music8bitTo16bit_ChangeFlag == 0){
				WaveFile_HDR_Read(&WaveHdr, "test_music.wav");
				Music8bitTo16bit_ChangeFlag = 1;
			}
			else{
				WaveFile_HDR_Read(&WaveHdr, "SuperMario.wav");
				Music8bitTo16bit_ChangeFlag = 0;
			}

		break;
		case 0x1B :		//0b xxx1 1011
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_3);

			WaveFile_HDR_Read(&WaveHdr, "sample08.wav");
		break;
		case 0x17 :		//0b xxx1 0111
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_4);

			f_close(&myFiles);

			//DAC Stop Func
			HAL_DAC_Stop(&hdac, DAC_CHANNEL_2);
			//Disable Timer 4
			HAL_TIM_Base_Stop_IT(&htim4);

			WaveData.WavHdrClearFlag 		= DISABLE_FLAG_BIT;
			WaveData.WavRepeatDataFlag 		= DISABLE_FLAG_BIT;
			WaveData.WavLasRepeattDataFlag	= DISABLE_FLAG_BIT;
			WaveData.WavClearDataFlag 		= DISABLE_FLAG_BIT;

			WaveFile_Hdr_Var_Init(&WaveHdr);
		break;
		case 0x0F :		//0b xxx0 1111
			HAL_GPIO_TogglePin(GPIO_LED_PORT, GPIO_LED_5);

			switch(WaveData.WavVolumLevel){
				case VOLUM_LEVEL_1 :
					WaveData.WavVolumLevel = VOLUM_LEVEL_2;

					WaveData.WavVolumValue = VOLUM_LEVEL_VALUE_1;
				break;
				case VOLUM_LEVEL_2 :
					WaveData.WavVolumLevel = VOLUM_LEVEL_3;

					WaveData.WavVolumValue = VOLUM_LEVEL_VALUE_2;
				break;
				case VOLUM_LEVEL_3 :
					WaveData.WavVolumLevel = VOLUM_LEVEL_4;

					WaveData.WavVolumValue = VOLUM_LEVEL_VALUE_3;
				break;
				case VOLUM_LEVEL_4 :
					WaveData.WavVolumLevel = VOLUM_LEVEL_5;

					WaveData.WavVolumValue = VOLUM_LEVEL_VALUE_4;
				break;
				case VOLUM_LEVEL_5 :
					WaveData.WavVolumLevel = VOLUM_LEVEL_1;

					WaveData.WavVolumValue = VOLUM_LEVEL_VALUE_5;
				break;
			}

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




