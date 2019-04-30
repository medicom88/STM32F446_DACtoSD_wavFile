/*
 * Drv_SDRAM.h
 *
 *  Created on: 2019. 1. 29.
 *      Author: Hybus_EDU_3
 */

#ifndef DRV_SDRAM_H_
#define DRV_SDRAM_H_

#include "stm32f4xx.h"

#define REFRESH_COUNT       ((uint32_t)0x0569)   /* SDRAM refresh counter (90MHz SD clock) */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define MAX_FILL_SIZE_16B	0x3fffff

#define SDRAM_8MB_HEX	0xd0800000

extern SDRAM_HandleTypeDef hsdram1;
extern FMC_SDRAM_CommandTypeDef command;
extern uint16_t *sdram_read_data;


void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

uint32_t SDRAM_Fill_16B_TEST_Function(uint16_t *sdramAddr);

#endif /* DRV_SDRAM_H_ */
