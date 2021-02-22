#include <stdio.h>
#include "MKL25Z4.h"

void def()
{
#define RED_LED_PIN 18U
#define GREEN_LED_PIN 19U
#define BLUE_LED_PIN 1U
#define PORT_PCR_MUX_MSK 0x700U
#define PORT_PCR_MUX_SHFT 8U
}

void led_init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;	//clock gating for port B
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;


		PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MSK;			//clear all MUX bits
		PORTB->PCR[RED_LED_PIN] |= (1UL<<PORT_PCR_MUX_SHFT) & (PORT_PCR_MUX_MSK);

		PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MSK;			//clear all MUX bits
		PORTB->PCR[GREEN_LED_PIN] |= (1UL<<PORT_PCR_MUX_SHFT) & (PORT_PCR_MUX_MSK);//set MUX=001; clear other bits

		PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MSK;			//clear all MUX bits
		PORTD->PCR[BLUE_LED_PIN] |= (1UL<<PORT_PCR_MUX_SHFT) & (PORT_PCR_MUX_MSK);//set MUX=001; clear other bits


		GPIOB->PDDR |= (1UL<<RED_LED_PIN);
		GPIOB->PDDR |= (1UL<<GREEN_LED_PIN);
		GPIOD->PDDR |= (1UL<<BLUE_LED_PIN);

}



void led_on(int num)
{
	if(num == 1)      //number for Red Led
	{
		GPIOB->PSOR |= (1<<GREEN_LED_PIN);  //turning green led off
		GPIOD->PSOR |= (1<<BLUE_LED_PIN);	//turning blue led off
		GPIOB->PCOR |= (1<<RED_LED_PIN);	//turning red led on
	}
	if(num == 2)		//number for Green led
	{
		GPIOD->PSOR |= (1<<BLUE_LED_PIN);	//turning blue led off
		GPIOB->PSOR |= (1<<RED_LED_PIN);	//turning red led off
		GPIOB->PCOR |= (1<<GREEN_LED_PIN);	//turning green led on
	}
	if(num == 3)		//number for Blue led
	{
		GPIOB->PSOR |= (1<<GREEN_LED_PIN);	//turning green led off
		GPIOB->PSOR |= (1<<RED_LED_PIN);	//turning red led off
		GPIOD->PCOR |= (1<<BLUE_LED_PIN);	//turning blue led on
	}
	if(num == 4)		//number for white Led
	{
		//turning white led on
		GPIOB->PCOR |= (1<<RED_LED_PIN);
		GPIOB->PCOR |= (1<<GREEN_LED_PIN);
		GPIOD->PCOR |= (1<<BLUE_LED_PIN);
	}
}

void led_off()								//turns off all the leds
{
	GPIOB->PSOR |= (1<<RED_LED_PIN) | (1<<GREEN_LED_PIN);
	GPIOD->PSOR |= (1<<BLUE_LED_PIN);
}
