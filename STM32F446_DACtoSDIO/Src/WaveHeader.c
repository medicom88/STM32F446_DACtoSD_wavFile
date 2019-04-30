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

volatile WAVE_HDR__TypeDef WaveHdr_test;

volatile unsigned char WavHdrData[44] = {0,};

char uarttest[64] = {0,};


void WaveFile_Hdr_Var_Init(volatile WAVE_HDR__TypeDef *hWavehdr)
{
	memcpy((unsigned char *)hWavehdr->Riff.ChunkID, "RIFF", 4);
	memcpy((unsigned char *)hWavehdr->Riff.Format, "WAVE", 4);
	memcpy((unsigned char *)hWavehdr->Fmt.ChunkID, "fmt ", 4);
	memcpy((unsigned char *)hWavehdr->Data.ChunkID, "data", 4);
}

void WaveFile_HDR_Read(volatile WAVE_HDR__TypeDef *hWavehdr)
{
	int WaveFile_OK = 0;

	sd_FileRead("test_music.wav", hWavehdr, sizeof(WAVE_HDR__TypeDef));

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
}



//int scale : Wave Max Amplitude Point / ex) scale:256 -> 0~256 / scale:4096 -> 0~4096
//int SamplingNum : Wave period Total Count

void SinWave(int scale, int SamplingNum, int *SineValue)
{
	float RadAngle;                             // Angle in Radians
	int PSineValue[100] = {0,};
	char uartStr[64] = {0,};

	for(int MyAngle = 0; MyAngle < SamplingNum; MyAngle++) {
	RadAngle = MyAngle * ((2 * PI) / SamplingNum);                          // 8 bit angle converted to radians   // there are 2 x PI radians in a circle hence the 2*PI
	SineValue[MyAngle] = ( sin (RadAngle) * ((scale / 2) - 1) ) + (scale / 2);

	sprintf(uartStr, "%d\r\n", SineValue[MyAngle]);
	put_str(&huart1, uartStr);
	}
}















