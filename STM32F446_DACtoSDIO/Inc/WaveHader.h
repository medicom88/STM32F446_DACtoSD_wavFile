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

#define NONE_ERROR	0

#define WAVE_FORMAT_MONO	1
#define WAVE_FORMAT_STEREO	2

#define PI	3.141592


typedef struct{
	unsigned char Wav4K_buff_L[4000];
	unsigned char Wav4K_buff_H[4000];
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
void WaveFile_HDR_Read(volatile WAVE_HDR__TypeDef *hWavehdr, const TCHAR* pathFile);
void SinWave(int scale, int SamplingNum, int *SineValue);


#endif /* WAVEHADER_H_ */












