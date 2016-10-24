/*!
**  gpio.h
**  version 1.1
*/         

#ifndef _GPIO_
#define _GPIO_

#include "GPIO1.h"
#include "GPIO2.h"
#include "GPIO3.h"
#include "dbgPort1.h"
#include "PE_Types.h"
//#define AHI(value) ((value==1)?(GPIOx_PSOR|=0x00000001<<1):(GPIOx_PSOR&=~(0x00000001<<1)))
#define AHI_SetOutput() (GPIOC_PDDR |= ((uint32)1<<6))//PTI6
#define AHI_ClrVal()    (GPIOC_PCOR |= ((uint32)1<<6)) 
#define AHI_SetVal()    (GPIOC_PSOR |= ((uint32)1<<6))

#define ALO_SetOutput() (GPIOC_PDDR |= ((uint32)1<<5))//PTI5
#define ALO_ClrVal()    (GPIOC_PCOR |= ((uint32)1<<5)) 
#define ALO_SetVal()    (GPIOC_PSOR |= ((uint32)1<<5))

#define BHI_SetOutput() (GPIOA_PDDR |= ((uint32)1<<29))//PTD5
#define BHI_ClrVal()    (GPIOA_PCOR |= ((uint32)1<<29))
#define BHI_SetVal()    (GPIOA_PSOR |= ((uint32)1<<29))

#define BLO_SetOutput() (GPIOA_PDDR |= ((uint32)1<<30))//PTD6
#define BLO_ClrVal()    (GPIOA_PCOR |= ((uint32)1<<30))
#define BLO_SetVal()    (GPIOA_PSOR |= ((uint32)1<<30))

#define CHI_SetOutput() (GPIOA_PDDR |= ((uint32)1<<18))//PTC2
#define CHI_ClrVal()    (GPIOA_PCOR |= ((uint32)1<<18))
#define CHI_SetVal()    (GPIOA_PSOR |= ((uint32)1<<18))

#define CLO_SetOutput() (GPIOA_PDDR |= ((uint32)1<<31))//PTD7
#define CLO_ClrVal()    (GPIOA_PCOR |= ((uint32)1<<31))
#define CLO_SetVal()    (GPIOA_PSOR |= ((uint32)1<<31))

#define REDLED_SetOutput() (GPIOA_PDDR |= ((uint32)1<<6))//PTA6
#define REDLED_ClrVal()    (GPIOA_PCOR |= ((uint32)1<<6))
#define REDLED_SetVal()    (GPIOA_PSOR |= ((uint32)1<<6))
#define REDLED_Toggle()    (GPIOA_PTOR |= ((uint32)1<<6))

#define GREENLED_SetOutput() (GPIOB_PDDR |= ((uint32)1<<4))//PTE4
#define GREENLED_ClrVal()    (GPIOB_PCOR |= ((uint32)1<<4))
#define GREENLED_SetVal()    (GPIOB_PSOR |= ((uint32)1<<4))
#define GREENLED_Toggle()    (GPIOB_PTOR |= ((uint32)1<<4))

typedef  enum{	
	GPIO1 = 0, 
	GPIO2, 
	GPIO3
}GPIO_PORT;

void gpio_init(void);
uint32_t gpio_rd(GPIO_PORT port, LDD_GPIO_TBitField pin);
void gpio_wr(GPIO_PORT port, LDD_GPIO_TBitField pin, GPIO1_TFieldValue value);


#endif
