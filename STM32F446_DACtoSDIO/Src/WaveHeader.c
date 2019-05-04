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

void Audio_Format_Check(unsigned short AudioFormat)
{
	switch(AudioFormat)
	{
		case WAVE_FORMAT_UNKNOWN :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_UNKNOWN\n");
		break;
		case WAVE_FORMAT_PCM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_PCM\n");
		break;
		case WAVE_FORMAT_MS_ADPCM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_MS_ADPCM\n");
		break;
		case WAVE_FORMAT_IEEE_FLOAT :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_IEEE_FLOAT\n");
		break;
		case WAVE_FORMAT_ALAW :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_ALAW\n");
		break;
		case WAVE_FORMAT_MULAW :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_MULAW\n");
		break;
		case WAVE_FORMAT_IMA_ADPCM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_IMA_ADPCM\n");
		break;
		case WAVE_FORMAT_YAMAHA_ADPCM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_YAMAHA_ADPCM\n");
		break;
		case WAVE_FORMAT_GSM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_GSM\n");
		break;
		case WAVE_FORMAT_ITU_ADPCM :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_ITU_ADPCM\n");
		break;
		case WAVE_FORMAT_MPEG :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_MPEG\n");
		break;
		case WAVE_FORMAT_EXTENSIBLE :
			put_str(&huart1, (uint8_t *)"WAVE_FORMAT_EXTENSIBLE\n");
		break;
		default :
			put_str(&huart1, (uint8_t *)"AudioFormat_ERROR\n");
		break;
	}
}

void SampleRate_Check(unsigned int SampleRate)
{
	switch(SampleRate)
	{
		case WAVE_SAMPLE_RATE_22050 : 		//22,058Hz(APB1CLK:84MHz)
			htim4.Init.Prescaler = 119-1;
			htim4.Init.Period = 32-1;
			put_str(&huart1, (uint8_t *)"WAVE_SAMPLE_RATE_22050\n");
		break;
		case WAVE_SAMPLE_RATE_44100 : 		//44,117Hz(APB1CLK:84MHz)
			htim4.Init.Prescaler = 119-1;
			htim4.Init.Period = 16-1;
			put_str(&huart1, (uint8_t *)"WAVE_SAMPLE_RATE_44100\n");
		break;
		case WAVE_SAMPLE_RATE_192000 : 		//192,219Hz(APB1CLK:84MHz)
			htim4.Init.Prescaler = 23-1;
			htim4.Init.Period = 19-1;
			put_str(&huart1, (uint8_t *)"WAVE_SAMPLE_RATE_192000\n");
		break;
		default :
			put_str(&huart1, (uint8_t *)"SampleRate_ERROR\n");
		break;
	}
	htim4.Instance = TIM4;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_Base_Init(&htim4);
}

void BitPerSample_Check(unsigned short BPS)
{
	switch(BPS)
	{
		case WAVE_BPS_8 : 		//0 ~ 255			(1Byte)

			put_str(&huart1, (uint8_t *)"WAVE_BPS_8\n");
		break;
		case WAVE_BPS_16 : 		//0 ~ 65,535		(2Byte)

			put_str(&huart1, (uint8_t *)"WAVE_BPS_16\n");
		break;
		case WAVE_BPS_24 : 		//0 ~ 16,777,215	(3Byte)

			put_str(&huart1, (uint8_t *)"WAVE_BPS_24\n");
		break;
		case WAVE_BPS_32 : 		//0 ~ 4,294,967,295	(4Byte)

			put_str(&huart1, (uint8_t *)"WAVE_BPS_32\n");
		break;
		default :
			put_str(&huart1, (uint8_t *)"BitPerSample_ERROR\n");
		break;
	}
}


void WaveFile_HDR_Read(volatile WAVE_HDR__TypeDef *hWavehdr, const TCHAR* pathFile)
{
	int WaveFile_OK = 0;

	if(f_open(&myFiles, pathFile, FA_READ) == FR_OK){

		if(f_read(&myFiles, hWavehdr, sizeof(WAVE_HDR__TypeDef), &myReadBytes) == FR_OK){

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.ChunkID, "RIFF", 4);

			if(WaveFile_OK != NONE_ERROR){
				put_str(&huart1, (uint8_t *)"RIFF_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Riff.Format, "WAVE", 4);

			if(WaveFile_OK != NONE_ERROR){
				put_str(&huart1, (uint8_t *)"WAVE_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Fmt.ChunkID, "fmt ", 4);

			if(WaveFile_OK == NONE_ERROR){

				//AudioFormat Check
				Audio_Format_Check(hWavehdr->Fmt.AudioFormat);

				//NumChannels Check(This project defaults to mono.)
				if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_MONO){
					//User Code Write

				}
				else if(hWavehdr->Fmt.NumChannels == WAVE_FORMAT_STEREO){
					//User Code Write

				}
				else{
					put_str(&huart1, (uint8_t *)"NumChannels_ERROR\n");
				}

				//SampleRate Check
				SampleRate_Check(hWavehdr->Fmt.SampleRate);



				//BitPerSample Check
				BitPerSample_Check(hWavehdr->Fmt.BitPerSample);

			}
			else{
				put_str(&huart1, (uint8_t *)"FMT_ERROR\n");
			}

			WaveFile_OK = memcmp((unsigned char *)hWavehdr->Data.ChunkID, "data", 4);

			if(WaveFile_OK != NONE_ERROR){
				put_str(&huart1, (uint8_t *)"DATA_ERROR\n");
			}

//			sprintf(UartTestStr, "%d\r\n", hWavehdr->Data.ChunkSize);
//			put_str(&huart1, UartTestStr);

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
			WaveData.WavLasRepeatDataFlag	= DISABLE_FLAG_BIT;
			WaveData.WavClearDataFlag 		= DISABLE_FLAG_BIT;

			WaveData.WavDataSize = WAV_1KBYTE;


			//BlockAlign Check

			if(WaveHdr.Fmt.BlockAlign == WAVE_BYTE_ALIGN_1B){
				if(f_read(&myFiles, WaveData.WavData_8Bit[0], WaveData.WavDataSize, &myReadBytes) == FR_OK){
					WaveData.WavCrossRepeatDataFlag = FILL_BUFF_0;
				}
				else{
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
				}
			}
			else if(WaveHdr.Fmt.BlockAlign == WAVE_BYTE_ALIGN_1B){
				if(f_read(&myFiles, WaveData.WavData_16Bit[0], WaveData.WavDataSize*2, &myReadBytes) == FR_OK){
					WaveData.WavCrossRepeatDataFlag = FILL_BUFF_0;
				}
				else{
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
				}
			}
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

			if(WaveHdr.Fmt.BlockAlign == WAVE_BYTE_ALIGN_1B){
				if(WaveData.WavCrossRepeatDataFlag == FILL_BUFF_1){
					if(f_read(&myFiles, WaveData.WavData_8Bit[0], WaveData.WavDataSize, &myReadBytes) == FR_OK){
						WaveData.WavRepeatDataFlag = DISABLE_FLAG_BIT;
					}
					else{
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
					}
				}
				else if(WaveData.WavCrossRepeatDataFlag == FILL_BUFF_0){
					if(f_read(&myFiles, WaveData.WavData_8Bit[1], WaveData.WavDataSize, &myReadBytes) == FR_OK){
						WaveData.WavRepeatDataFlag = DISABLE_FLAG_BIT;
					}
					else{
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
					}
				}
			}
			if(WaveHdr.Fmt.BlockAlign == WAVE_BYTE_ALIGN_2B){
				if(WaveData.WavCrossRepeatDataFlag == FILL_BUFF_1){
					if(f_read(&myFiles, WaveData.WavData_16Bit[0], WaveData.WavDataSize*2, &myReadBytes) == FR_OK){
						WaveData.WavRepeatDataFlag = DISABLE_FLAG_BIT;
					}
					else{
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
					}
				}
				else if(WaveData.WavCrossRepeatDataFlag == FILL_BUFF_0){
					if(f_read(&myFiles, WaveData.WavData_16Bit[1], WaveData.WavDataSize*2, &myReadBytes) == FR_OK){
						WaveData.WavRepeatDataFlag = DISABLE_FLAG_BIT;
					}
					else{
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);
					}
				}
			}
		}

	}

	if(WaveData.WavClearDataFlag == ENABLE_FLAG_BIT){
		f_close(&myFiles);

		WaveData.WavClearDataFlag 	= DISABLE_FLAG_BIT;
		WaveFile_Hdr_Var_Init(&WaveHdr);
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















