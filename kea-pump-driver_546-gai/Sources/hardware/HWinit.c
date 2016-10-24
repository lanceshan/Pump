/*
 * HWinit.c
 * version 1.0
 */
#include "../hardware/gpio.h"
#include "../hardware/uart.h"
#include "../hardware/uart0_master.h"
#include "../hardware/adc.h"
#include "../hardware/led.h"
#include "../hardware/HWInit.h"
#include "../hardware/timer.h"
#include "../hardware/flash.h"
#include "../hardware/i2c.h"
#include "../user/globalvars.h"
void sys_init(void)
{
	gpio_init();
	led_init();
	adc_init();
	timer_init();
	pwm_init();
	//uart1_init();
	//uart1_clear_Rxbuf();
	uart0_master_init();
	i2c_init();
	
	globalParameter_init();
}

void SaveVers(const uint8 *version)
{
	uint8 buf[6] = {0};
	uint8 i = 0;
	uint8 wr_flag = 0;
	
	Flash_init();
	Flash_GetBytes(FLASH_ADDR_VERSION, buf, 6);		//如果Flash已写入版本信息，将不写版本信息到Flash中
	for(i=0; i<6; i++)
	{
		if(buf[i] != version[i])
		{
			buf[i] = version[i];
			wr_flag = 1;
		}
	}
	if(wr_flag == 1)
	{
		Flash_EraseSector(FLASH_SECTOR_PARAM);
		Flash_SetBytes(FLASH_ADDR_VERSION, buf, 6);
	}
	Flash_Disable();
}
