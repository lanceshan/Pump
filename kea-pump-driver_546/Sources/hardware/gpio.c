/*
 * gpio.c
 * version 1.0
 */
#include "gpio.h"

static LDD_TDeviceData *gpio1;
static LDD_TDeviceData *gpio2;
static LDD_TDeviceData *gpio3;
/*
 * Function:void gpio_init(void)
 * Param: void
 * Return: void
 * Description: GPIO device initialization
 */
void gpio_init(void)
{
	  gpio1 = GPIO1_Init(NULL);
	  gpio2 = GPIO2_Init(NULL);
	  gpio3 = GPIO3_Init(NULL);
	  
	  AHI_SetOutput();
	  ALO_SetOutput();
	  BHI_SetOutput();
	  BLO_SetOutput();
	  CHI_SetOutput();
	  CLO_SetOutput();
}

/*
 * Function:uint32_t gpio_rd(GPIO_PORT port, LDD_GPIO_TBitField pin)
 * Param: GPIO_PORT port, LDD_GPIO_TBitField pin
 * Return: pin value
 * Description: read certain port pin value
 */
uint32_t gpio_rd(GPIO_PORT port, LDD_GPIO_TBitField pin)
{
	uint32_t ret_val = 0;
	
	switch(port)
	{
		case GPIO1:
			ret_val = GPIO1_GetFieldValue(gpio1, pin);
			break;
		case GPIO2:
			ret_val = GPIO2_GetFieldValue(gpio2, pin);
			break;
		case GPIO3:
			ret_val = GPIO3_GetFieldValue(gpio3, pin);
			break;
		default:
			break;
	}

	return ret_val;
}

//GPIO write function
void gpio_wr(GPIO_PORT port, LDD_GPIO_TBitField pin, GPIO1_TFieldValue value)
{
	switch(port)
	{
		case GPIO1:
			GPIO1_SetFieldValue(gpio1, pin, value);
			break;
		case GPIO2:
			GPIO2_SetFieldValue(gpio2, pin, value);
			break;
		case GPIO3:
			GPIO3_SetFieldValue(gpio3, pin, value);
			break;
		default:
			break;
	}
}
