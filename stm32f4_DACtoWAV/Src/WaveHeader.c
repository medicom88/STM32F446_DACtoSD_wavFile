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

//	sd_FileRead("test_music.wav", (char *)WavHdrData, sizeof(WavHdrData));

	sd_FileRead("test_music.wav", hWavehdr, sizeof(WAVE_HDR__TypeDef));
//	sd_FileRead("test_music.wav", &WaveHdr_test, 44);
//
//	sprintf(uarttest, "%d\r\n", sizeof(WAVE_HDR__TypeDef));
//	put_str(&huart1, uarttest);
//
//	sd_FileRead("test_music.wav", (char *)WavHdrData, sizeof(WavHdrData));


//	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.ChunkID, (unsigned char *)WavHdrData, 4);
	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.ChunkID, "RIFF", 4);

	if(WaveFile_OK == NONE_ERROR){
//
//		hWavehdr->Riff.ChunkSize = (*(WavHdrData+7)<<24);
//		hWavehdr->Riff.ChunkSize |= (*(WavHdrData+6)<<16);
//		hWavehdr->Riff.ChunkSize |= (*(WavHdrData+5)<<8);
//		hWavehdr->Riff.ChunkSize |= *(WavHdrData+4);
//
		//file total size : hWavehdr->Riff.ChunkSize + 8byte

		put_str(&huart1, (uint8_t *)"RIFF_OK\n");
	}
	else{
		put_str(&huart1, (uint8_t *)"RIFF_ERROR\n");
	}

//	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.Format, (unsigned char *)(WavHdrData+8), 4);
	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.Format, "WAVE", 4);

	if(WaveFile_OK == NONE_ERROR){
		put_str(&huart1, (uint8_t *)"WAVE_OK\n");
	}
	else{
		put_str(&huart1, (uint8_t *)"WAVE_ERROR\n");
	}

//	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Fmt.ChunkID, (unsigned char *)(WavHdrData+12), 4);
	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Fmt.ChunkID, "fmt ", 4);

	if(WaveFile_OK == NONE_ERROR){

//		hWavehdr->Fmt.ChunkSize = (*(WavHdrData+19)<<24);
//		hWavehdr->Fmt.ChunkSize |= (*(WavHdrData+18)<<16);
//		hWavehdr->Fmt.ChunkSize |= (*(WavHdrData+17)<<8);
//		hWavehdr->Fmt.ChunkSize |= *(WavHdrData+16);
//
//		hWavehdr->Fmt.AudioFormat = (*(WavHdrData+21)<<8);
//		hWavehdr->Fmt.AudioFormat |= *(WavHdrData+20);

		if(hWavehdr->Fmt.AudioFormat != WAVE_FORMAT_PCM){
			put_str(&huart1, (uint8_t *)"AudioFormat_ERROR\n");
		}

//		hWavehdr->Fmt.NumChannels = (*(WavHdrData+23)<<8);
//		hWavehdr->Fmt.NumChannels |= *(WavHdrData+22);

		if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_MONO){

		}
		else if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_STEREO){

		}
		else{
			put_str(&huart1, (uint8_t *)"NumChannels_ERROR\n");
		}

//		hWavehdr->Fmt.SampleRate = (*(WavHdrData+27)<<24);
//		hWavehdr->Fmt.SampleRate |= (*(WavHdrData+26)<<16);
//		hWavehdr->Fmt.SampleRate |= (*(WavHdrData+25)<<8);
//		hWavehdr->Fmt.SampleRate |= *(WavHdrData+24);
//
//		hWavehdr->Fmt.AvgByteRate = (*(WavHdrData+31)<<24);
//		hWavehdr->Fmt.AvgByteRate |= (*(WavHdrData+30)<<16);
//		hWavehdr->Fmt.AvgByteRate |= (*(WavHdrData+29)<<8);
//		hWavehdr->Fmt.AvgByteRate |= *(WavHdrData+28);
//
//		hWavehdr->Fmt.BlockAlign = (*(WavHdrData+33)<<8);
//		hWavehdr->Fmt.BlockAlign |= *(WavHdrData+32);

		if(hWavehdr->Fmt.NumChannels != hWavehdr->Fmt.BlockAlign){
			put_str(&huart1, (uint8_t *)"BlockAlign_ERROR\n");
		}

//		hWavehdr->Fmt.BitPerSample = (*(WavHdrData+35)<<8);
//		hWavehdr->Fmt.BitPerSample |= *(WavHdrData+34);

		put_str(&huart1, (uint8_t *)"FMT_OK\n");
	}
	else{
		put_str(&huart1, (uint8_t *)"FMT_ERROR\n");
	}

//	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Data.ChunkID, (unsigned char *)(WavHdrData+36), 4);
	WaveFile_OK = memcmp((unsigned char *)hWavehdr->Data.ChunkID, "data", 4);

	if(WaveFile_OK == NONE_ERROR){

//		hWavehdr->Data.ChunkSize = (*(WavHdrData+43)<<24);
//		hWavehdr->Data.ChunkSize |= (*(WavHdrData+42)<<16);
//		hWavehdr->Data.ChunkSize |= (*(WavHdrData+41)<<8);
//		hWavehdr->Data.ChunkSize |= *(WavHdrData+40);

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















