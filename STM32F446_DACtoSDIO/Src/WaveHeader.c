/*
 * WaveHeader.c
 *
 *  Created on: 2019. 4. 26.
 *      Author: Hybus_EDU_3
 */


#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "main.h"
#include "WaveHader.h"
#include "string.h"
#include "stdlib.h"

/* USER CODE BEGIN Includes */
#include "uart_general.h"
#include "sd_user_code.h"
#include "EMbed_GPIO_General.h"
/* USER CODE END Includes */

volatile WAVE_HDR__TypeDef WaveHdr;
volatile WAV_DATA_TypeDef	WaveData;


void WaveFile_Hdr_Var_Init(volatile WAVE_HDR__TypeDef *hWavehdr)
{
	memset(hWavehdr, NULL, sizeof(WAVE_HDR__TypeDef));
	memcpy((unsigned char *)hWavehdr->Riff.ChunkID, "RIFF", 4);
	memcpy((unsigned char *)hWavehdr->Riff.Format, "WAVE", 4);
	memcpy((unsigned char *)hWavehdr->Fmt.ChunkID, "fmt ", 4);
	memcpy((unsigned char *)hWavehdr->Data.ChunkID, "data", 4);
}

void WaveFile_HDR_Read(volatile WAVE_HDR__TypeDef *hWavehdr, const TCHAR* pathFile)
{
	int WaveFile_OK = 0;

	if(f_open(&myFiles, pathFile, FA_READ) == FR_OK){

		if(f_read(&myFiles, hWavehdr, sizeof(WAVE_HDR__TypeDef), &myReadBytes) == FR_OK){

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.ChunkID, "RIFF", 4);

			if(WaveFile_OK == NONE_ERROR){
				put_str(&huart1, (uint8_t *)"RIFF_OK\n");
			}
			else{
				put_str(&huart1, (uint8_t *)"RIFF_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.Format, "WAVE", 4);

			if(WaveFile_OK == NONE_ERROR){
				put_str(&huart1, (uint8_t *)"WAVE_OK\n");
			}
			else{
				put_str(&huart1, (uint8_t *)"WAVE_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Fmt.ChunkID, "fmt ", 4);

			if(WaveFile_OK == NONE_ERROR){

				if(hWavehdr->Fmt.AudioFormat != WAVE_FORMAT_PCM){
					put_str(&huart1, (uint8_t *)"AudioFormat_ERROR\n");
				}

				if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_MONO){

				}
				else if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_STEREO){

				}
				else{
					put_str(&huart1, (uint8_t *)"NumChannels_ERROR\n");
				}

				if(hWavehdr->Fmt.NumChannels != hWavehdr->Fmt.BlockAlign){
					put_str(&huart1, (uint8_t *)"BlockAlign_ERROR\n");
				}

				put_str(&huart1, (uint8_t *)"FMT_OK\n");
			}
			else{
				put_str(&huart1, (uint8_t *)"FMT_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Data.ChunkID, "data", 4);

			if(WaveFile_OK == NONE_ERROR){
				put_str(&huart1, (uint8_t *)"DATA_OK\n");
			}
			else{
				put_str(&huart1, (uint8_t *)"DATA_ERROR\n");
			}

			sprintf(UartTestStr, "%d\r\n", hWavehdr->Data.ChunkSize);
			put_str(&huart1, UartTestStr);

//			if(f_read(&myFiles, WaveData.Wav4K_buff_L, 30000, &myReadBytes) == FR_OK){
//				//put_str(&huart1, WaveData.Wav4K_buff_L);
//			}
//			else{
//				HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
//			}
//
//			f_close(&myFiles);

			WaveData.WavHdrClearFlag		= ENABLE_FLAG_BIT;
			WaveData.WavRepeatDataFlag 		= ENABLE_FLAG_BIT;
			WaveData.WavLasRepeattDataFlag	= DISABLE_FLAG_BIT;
			WaveData.WavClearDataFlag 		= DISABLE_FLAG_BIT;

			WaveData.WavDataSize = WAV_4KBYTE;

			HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);
		}
		else{
			HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
		}
	}
	else{
		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
	}
}

void WaveDataRead()
{
	if(WaveData.WavHdrClearFlag == ENABLE_FLAG_BIT){
		if(WaveData.WavRepeatDataFlag == ENABLE_FLAG_BIT){
			if(f_read(&myFiles, WaveData.WavData, WaveData.WavDataSize, &myReadBytes) == FR_OK){
				//put_str(&huart1, WaveData.Wav4K_buff_L);
				WaveData.WavRepeatDataFlag = DISABLE_FLAG_BIT;
			}
			else{
				HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
			}
		}
	}

	if(WaveData.WavClearDataFlag == ENABLE_FLAG_BIT){
		f_close(&myFiles);

		WaveData.WavClearDataFlag 	= DISABLE_FLAG_BIT;
	}

}



//int scale : Wave Max Amplitude Point / ex) scale:256 -> 0~256 / scale:4096 -> 0~4096
//int SamplingNum : Wave period Total Count

void SinWave(int scale, int SamplingNum, int *SineValue)
{
	float RadAngle;                             // Angle in Radians
	char uartStr[64] = {0,};

	for(int MyAngle = 0; MyAngle < SamplingNum; MyAngle++) {
	RadAngle = MyAngle * ((2 * PI) / SamplingNum);                          // 8 bit angle converted to radians   // there are 2 x PI radians in a circle hence the 2*PI
	SineValue[MyAngle] = ( sin (RadAngle) * ((scale / 2) - 1) ) + (scale / 2);

	sprintf(uartStr, "%d\r\n", SineValue[MyAngle]);
	put_str(&huart1, uartStr);
	}
}















