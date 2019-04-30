/*
 * sd_user_code.h
 *
 *  Created on: 2019. 1. 22.
 *      Author: Hybus_EDU_3
 */

#ifndef SD_USER_CODE_H_
#define SD_USER_CODE_H_

#include "stm32f4xx.h"
#include "fatfs.h"

extern SD_HandleTypeDef hsd;

extern FATFS 	myFatFS;
extern FIL		myFiles;
extern UINT		myWriteBytes;
extern UINT		myReadBytes;
extern char myFileName[];
extern  char myWriteData[83];
extern volatile char myReadData[320];
extern volatile uint16_t picdata[160];
extern volatile uint16_t sdramdata[160];
extern const uint16_t Embed_Logo[20480];

void sd_FileWrite(
		const TCHAR* pathFile,	/* Pointer to the file name */
		const void* writeData,		/* Pointer to the data to be written */
		UINT DataSize			/* Number of bytes to write */
);

void sd_FileRead(
		const TCHAR* pathFile,	/* Pointer to the file name */
		const void* ReadData,		/* Pointer to the data to be written */
		UINT DataSize			/* Number of bytes to write */
);

//void sd_FileRead_Image(			//160x128 image
//		const TCHAR* pathFile		/* Pointer to the file name */
//);
//
//void sd_File_Read_To_sdram_Write(
//		uint16_t *sdramMemory,		/* Pointer to the sdram memory addr */
//		const TCHAR* pathFile		/* Pointer to the file name */
//);
//
//void sdram_Read_To_Image(uint16_t *sdramMemory);


#endif /* SD_USER_CODE_H_ */
