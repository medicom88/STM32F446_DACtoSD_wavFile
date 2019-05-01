/*
 * WaveHader.h
 *
 *  Created on: 2019. 4. 26.
 *      Author: Hybus_EDU_3
 */

#ifndef WAVEHADER_H_
#define WAVEHADER_H_

#include "stm32f4xx.h"
#include "fatfs.h"

#define WAVE_FORMAT_UNKNOWN			0X0000
#define WAVE_FORMAT_PCM				0X0001
#define WAVE_FORMAT_MS_ADPCM		0X0002
#define WAVE_FORMAT_IEEE_FLOAT		0X0003
#define WAVE_FORMAT_ALAW			0X0006
#define WAVE_FORMAT_MULAW			0X0007
#define WAVE_FORMAT_IMA_ADPCM		0X0011
#define WAVE_FORMAT_YAMAHA_ADPCM 	0X0016
#define WAVE_FORMAT_GSM 			0X0031
#define WAVE_FORMAT_ITU_ADPCM 		0X0040
#define WAVE_FORMAT_MPEG 			0X0050
#define WAVE_FORMAT_EXTENSIBLE 		0XFFFE

#define WAVE_SAMPLE_RATE_22050		22050
#define WAVE_SAMPLE_RATE_44100		44100
#define WAVE_SAMPLE_RATE_192000		192000

#define WAVE_BYTE_ALIGN_1B	1
#define WAVE_BYTE_ALIGN_2B	2
#define WAVE_BYTE_ALIGN_3B	3
#define WAVE_BYTE_ALIGN_4B	4

//BitPerSample
#define WAVE_BPS_8		8		//0 ~ 255			(1Byte)
#define WAVE_BPS_16		16		//0 ~ 65,535		(2Byte)
#define WAVE_BPS_24		24		//0 ~ 16,777,215	(3Byte)
#define WAVE_BPS_32		32		//0 ~ 4,294,967,295	(4Byte)

#define Scale_16Bto12B	0.0625	//4096/65535

#define NONE_ERROR	0

#define WAVE_FORMAT_MONO	1
#define WAVE_FORMAT_STEREO	2

#define PI	3.141592

#define WAV_4KBYTE	65535

#define ENABLE_FLAG_BIT		1
#define DISABLE_FLAG_BIT	0


extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim4;


typedef struct{
	unsigned char 	WavData_8Bit[65535];
	unsigned short 	WavData_16Bit;
	unsigned short	WavDataSize;
	unsigned char 	WavHdrClearFlag;
	unsigned char 	WavOperateDataFlag;
	unsigned char 	WavRepeatDataFlag;
	unsigned char 	WavClearDataFlag;
	unsigned char 	WavLasRepeattDataFlag;
}WAV_DATA_TypeDef;


typedef struct
{
	unsigned char	ChunkID[4];		//Contains the letters "RIFF" in ASCII form
	unsigned int	ChunkSize;		// This is the size of the rest of the chunk following this number
	unsigned char	Format[4];		// Contains the letters "WAVE" in ASCII form


}RIFF_TypeDef;

typedef struct
{
	unsigned char	ChunkID[4];		// Contains the letters "fmt " in ASCII form

	unsigned int	ChunkSize;		// 16 for PCM. This is the size of the rest of the Subchunk which follows this number
	unsigned short	AudioFormat;	// PCM = 1
	unsigned short	NumChannels;	// Mono = 1, Stereo = 2, etc.
	unsigned int	SampleRate;		// 8000, 44100, etc.
	unsigned int	AvgByteRate;	// SampleRate * NumChannels * BitsPerSample/8
	unsigned short	BlockAlign;		// NumChannels * BitsPerSample/8
	unsigned short	BitPerSample;	// 8 bits = 8, 16 bits = 16, etc } FMT;
}FMT_TypeDef;

typedef struct
{
	unsigned char	ChunkID[4];		// Contains the letters "data" in ASCII form
	unsigned int	ChunkSize;		// NumSamples * NumChannels * BitsPerSample/8
}DATA_TypeDef;

typedef struct
{
	RIFF_TypeDef	Riff;
	FMT_TypeDef		Fmt;
	DATA_TypeDef	Data;
}WAVE_HDR__TypeDef;

extern volatile WAVE_HDR__TypeDef	WaveHdr;
extern volatile WAV_DATA_TypeDef	WaveData;

void WaveFile_Hdr_Var_Init(volatile WAVE_HDR__TypeDef *hWavehdr);
void Audio_Format_Check(unsigned short AudioFormat);
void SampleRate_Check(unsigned int SampleRate);
void BitPerSample_Check(unsigned short BPS);

void WaveFile_HDR_Read(volatile WAVE_HDR__TypeDef *hWavehdr, const TCHAR* pathFile);
void WaveDataRead();

void SinWave(int scale, int SamplingNum, int *SineValue);


#endif /* WAVEHADER_H_ */












