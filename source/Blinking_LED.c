#include <stdio.h>
#include "MKL25Z4.h"
#include "tsi.h"
#include "led.h"


int min(int x, int y)  		//return smaller of the two arguments
{
	if (x<=y)
		return x;
	else
		return y;
}

void delay(int time_ms)		//delays by time_ms milliseconds
{
	volatile int j = time_ms*2500;

	while(j--);
	j = time_ms*2500;

}

int main()
{
	volatile int i;
	int k;

	int pol_time = 100;		//time for polling in ms
	int scan_val;
	int led_color = 4;
	def();
	led_init();
	TSI_init();
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

	led_on(led_color);	//turning on the white led initially for the infinite loop

	while(1)
	{
		int rem_time[4] = {500, 1000, 2000, 3000};		//array holding delay values
		for(i=0; i<=3; i++)								//recurring blink loop
		{
			while(rem_time[i]>0)
			{
				delay(min(pol_time, rem_time[i]));
				rem_time[i] -= pol_time;
				scan_val = TSI_scan();	//polling for touch
				if((scan_val>=700) && (scan_val<=900))	//if touched at left
				{
					led_color = 1;
#ifdef DEBUG
	printf("Red led turned on, slider value: %d\n",scan_val);
#endif
				}
				if((scan_val>=1000) && (scan_val<=1600)) //if touched at center
				{
					led_color = 2;
#ifdef DEBUG
	printf("Green led turned on, slider value: %d\n",scan_val);
#endif
				}
				if(scan_val>=1700)		//if touched at right
				{
					led_color = 3;
#ifdef DEBUG
	printf("Blue led turned on, slider value: %d\n",scan_val);
#endif
				}
				led_on(led_color);
			}


			led_off();
			rem_time[0] = 500;
			while(rem_time[0]>0)
			{
				delay(min(pol_time, rem_time[0]));
				rem_time[0] -= pol_time;
				scan_val = TSI_scan();
				if((scan_val>=700) && (scan_val<=900))	//if touched at left
								{
									led_color = 1;
#ifdef DEBUG
	printf("Red led turned on, slider value: %d\n",scan_val);
#endif
								}
								if((scan_val>=1000) && (scan_val<=1600)) //if touched at center
								{
									led_color = 2;
#ifdef DEBUG
	printf("Green led turned on, slider value: %d\n",scan_val);
#endif
								}
								if(scan_val>=1700)		//if touched at right
								{
									led_color = 3;
#ifdef DEBUG
	printf("Blue led turned on, slider value: %d\n",scan_val);
#endif
								}
			}
			led_on(led_color);
		}

	}

	return 0;
}
