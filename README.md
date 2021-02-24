# PES_3_BlinkenLights
Assignment -3 , PES

PRINCIPLES OF EMBEDDED SOFTWARE – ASSIGNMENT 3 (BLINKENLIGHTS)

Introduction:
The assignment contains a program that involves blinking red, green, blue, and white LEDs with certain (specified) delays. A capacitive touch sensor has also been used to make a specific pattern (color) of LEDs. 
Programing Environment:
MCUXpresso IDE with KL25Z128VLK4 board SDK is used for programing. The project contains two build targets, DEBUG and RUN. Apart from the files that IDE uses for building a project, Blinking_LED.c contains the primary code for the project.
The Code:
There are, in total, three .c files (blinking_LED.c, tsi.c, and led.c) and two .h files (tsi.h, led.h)

1.	led.c
This file contains the initializing functions of LEDs as well as functions to turn the LEDs on and off. Following functions are present in the file:
a.	Void led_init()
This function initializes the LED pin by providing the clock, setting the MUX for GPIO, and setting direction as output, for each LED (red, green, and blue). It uses some masks which are defined in the function void def() and also from the library MKL25Z4.
b.	Void led_on(int num)
This function turns the respective LEDs on by setting the PCOR register in GPIO modules. The num values used are – 1 for RED, 2 for GREEN, 3 for BLUE, and 4 for WHITE.
c.	Void led_off()
This function turns all the LEDs off by setting PSOR register in GPIO modules.

2.	tsi.c
This .c file contains the initialization as well as polling functions of the capacitive touch slider. Following functions are present in the file:
a.	void TSI_init()
This function initializes the touch slider by setting the values of operating mode, oscillator voltage, oscillator charge and discharge value, number of time to scan the electrode in the GENCS register of TSI0 module. It also sets the clock gating and enables the TSI module. 
b.	Int TSI_scan()
This function polls for the input. It uses channel 10 for sensing and returns the received data. 

3.	Blinking_led.c
This is the primary  .c file that contains the main function along with few more functions. Following functions are contained in the file.
a.	int min(int x, int y)
This function returns the smallest of the two integers passed as arguments. This function is used in the main function where polling of touch sensor and delaying in the blinking pattern were the two tasks happening concurrently.
b.	Void delay(int time_ms)
This function produces delay for specified amount of time (milliseconds). The function uses an empty loop for certain number of iterations to produce specified delay.
c.	Int main()
This function contains the main logic. Initially, LEDs are blinked as specified in part one of the assignment provided. Then it enters the infinite loop where there are two while loops each used to manage the blinking of LEDs and polling by the touch slider. The while loops basically produce delay by the smaller of the two (polling interval and delays for blinking). This way, the loops is able to poll the input of the slider every 100 ms. Then the loop compares value scanned by the slider with the values specified for left, right, and center region of the slider.

4.	.h Files
Tsi.h and led.h contain the prototypes of the functions defined in led.c and tsi.c


EXTRA CREDIT:
1.	Address of the main() function is  00000440.
2.	The size of delay function is 28 bytes.
3.	Disassembly of the dealy() function:

17       	volatile int j = time_ms*2500;
00000418:   ldr     r3, [r7, #4]    //loads the data in the address (r7+4) into r3

0000041a:   ldr     r2, [pc, #32]   ; (0x43c <delay+44>) //load data in address pc+32 in r2

0000041c:   muls    r3, r2	//multiply data in r2 with data in r3 

0000041e:   str     r3, [r7, #12]	//store the data in address location r7+12 in r3

19       	while(j--);

00000420:   nop     ; (mov r8, r8) // does nothing

00000422:   ldr     r3, [r7, #12]	// loads the data in the address location r7+12 into r3

00000424:   subs    r2, r3, #1	//subtracts data in r3 by 1 and stores in r2

00000426:   str     r2, [r7, #12]	//stores data in location r7+12 in r2

00000428:   cmp     r3, #0	//compares data in r3 with 0

0000042a:   bne.n   0x422 <delay+18>//if data in r3 is not equal to 0 go to the loop start

20       	j = time_ms*2500;

0000042c:   ldr     r3, [r7, #4]  // loads the data in the address (r7+4) into r3

0000042e:   ldr     r2, [pc, #12]   ; (0x43c <delay+44>) //loads data in address pc+32 in r2

00000430:   muls    r3, r2	//multiply data in r2 with data in r3

00000432:   str     r3, [r7, #12]	//store the data in address location r7+12 in r3
22       }

