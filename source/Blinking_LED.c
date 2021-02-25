#include <stdio.h>
#include "MKL25Z4.h"
#include "tsi.h"
#include "led.h"

//Following function returns the smaller the of two integers
//This function is used later as a delay function argument to get the minimum delay time.
int min(int x, int y)
{
	if (x<=y)
		return x;
	else
		return y;
}

//Following function produces a delay of time_ms(argument provided)
//Uses empty loop iterations to produce the delay
void delay(int time_ms)		//delays by time_ms milliseconds
{
	volatile int j = time_ms*2500;

	while(j--);

}

//the main function
int main()
{
	volatile int i;
	int k;

	int pol_time = 100;		//time for polling in ms
	int scan_val;
	int led_color = 4;		//initial color is white
	def();					//function defined in led.c and contains macros
	led_init();				//function defined in led.c and provides clock, intializes gpio ports and their directions
	TSI_init();				//function defined in tsi.c and does the initial setup (like setting TSI0_GENCS values) for tsi scan
	//printf("just to see");

	//turning red, green, and blue leds on for 500ms each and off for 100ms
	for(k=1; k<=3; k++)
	{
		led_on(k);
		delay(500);
		led_off();
		delay(100);
	}

	led_on(4);		//blinking white led
	delay(100);
	led_off();
	delay(100);
	led_on(4);		//blinking white led
	delay(100);
	led_off();
	delay(100);

	led_on(led_color);	//turning on the white led initially for the infinite loop

	while(1)
	{
		int rem_time[4] = {500, 1000, 2000, 3000};		//array holding delay values
		for(i=0; i<=3; i++)								//recurring blink loop
		{
			while(rem_time[i]>0)
			{
				delay(min(pol_time, rem_time[i]));		//poll after each 100ms and change led state/color if rem_time is zero
				rem_time[i] -= pol_time;
				scan_val = TSI_scan();					//polling for touch
				if((scan_val>=700) && (scan_val<=900))	//if touched at left
				{
					led_color = 1;						//color variable is set for red
#ifdef DEBUG
	printf("Red led turned on, slider value: %d\n",scan_val);
#endif
				}
				if((scan_val>=1000) && (scan_val<=1600)) //if touched at center
				{
					led_color = 2;						 //color variable is set for green
#ifdef DEBUG
	printf("Green led turned on, slider value: %d\n",scan_val);
#endif
				}
				if(scan_val>=1700)						//if touched at right
				{
					led_color = 3;						 //color variable is set for blue
#ifdef DEBUG
	printf("Blue led turned on, slider value: %d\n",scan_val);
#endif
				}
				led_on(led_color);						//Turn on the led of current color immediately
			}


			led_off();
			rem_time[0] = 500;
			while(rem_time[0]>0)						//500ms delay when led off
			{
				delay(min(pol_time, rem_time[0]));
				rem_time[0] -= pol_time;
				scan_val = TSI_scan();
				if((scan_val>=700) && (scan_val<=900))	//if touched at left
								{
									led_color = 1;		//color variable is set for red
#ifdef DEBUG
	printf("Red led turned on, slider value: %d\n",scan_val);
#endif
								}
								if((scan_val>=1000) && (scan_val<=1600)) //if touched at center
								{
									led_color = 2;		//color variable is set for green
#ifdef DEBUG
	printf("Green led turned on, slider value: %d\n",scan_val);
#endif
								}
								if(scan_val>=1700)		//if touched at right
								{
									led_color = 3;		//color variable is set for blue
#ifdef DEBUG
	printf("Blue led turned on, slider value: %d\n",scan_val);
#endif
								}
			}
			led_on(led_color);						//turn on the led of current color after the led_off delay is complete
		}

	}

	return 0;
}
