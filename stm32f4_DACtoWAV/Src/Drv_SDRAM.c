/*
 * Drv_SDRAM.c
 *
 *  Created on: 2019. 1. 29.
 *      Author: Hybus_EDU_3
 */

#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "main.h"

#include "Drv_SDRAM.h"

FMC_SDRAM_CommandTypeDef command;
//use example--> sdram_dat[0]=0xFFFF; for 16bit acess and write
//uint16_t *sdram_dat = (uint16_t *)0xD0000000;
uint16_t *sdram_read_data;

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
	__IO uint32_t tmpmrd =0;

	/* Step 3:  Configure a clock configuration enable command */
	Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

	/* Step 4: Insert 100 ms delay */
	HAL_Delay(100);

	/* Step 5: Configure a PALL (precharge all) command */
	Command->CommandMode = FMC_SDRAM_CMD_PALL;
	Command->CommandTarget     = FMC_SDRAM_CMD_TARGET_BANK2;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

	/* Step 6 : Configure a Auto-Refresh command */
	Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	Command->AutoRefreshNumber = 4;
	Command->ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

	/* Step 7: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
			SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
			SDRAM_MODEREG_CAS_LATENCY_3           |
			SDRAM_MODEREG_OPERATING_MODE_STANDARD |
			SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}


uint32_t SDRAM_Fill_16B_TEST_Function(uint16_t *sdramAddr)
{
	uint32_t addrIndex = 0;
	uint16_t sdramAddrTemp = 0;

	for(addrIndex = 0; addrIndex <= MAX_FILL_SIZE_16B; addrIndex++)
	{
		if(addrIndex % 2){
			*(sdramAddr + addrIndex) = 0xaaaa;
			sdramAddrTemp = *(sdramAddr + addrIndex);

			if(sdramAddrTemp != 0xaaaa){
				return addrIndex;
			}
		}
		else{
			*(sdramAddr + addrIndex) = 0x5555;
			sdramAddrTemp = *(sdramAddr + addrIndex);

			if(sdramAddrTemp != 0x5555){
				return addrIndex;
			}
		}
	}
}












