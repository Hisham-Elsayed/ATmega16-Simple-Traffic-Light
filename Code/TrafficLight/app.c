/*******************************************************************************
 *  [FILE NAME]: app.c
 *
 *  [Author]: Hisham Elsayed
 *
 *  [DATE CREATED]: Sep 14, 2022
 *
 *  [DESCRIPTION]: Application file
 *******************************************************************************/
#include "avr/delay.h"
#include "avr/io.h"
#include "gpio.h"
#include "led.h"
#include "timer.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/
uint8 g_tick1=0;
uint8 g_tick2=0;
uint8 num=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void timerCallBack(void)
{
	g_tick1++;
}

void timerCallBack2(void)
{
	g_tick2++;
}

/* Function for Enabling Leds Only without the 7-segment */
void Leds_On()
{
	g_tick2=0;
	LED_ON(LED_PORT_ID,RED_LED_PIN);

	while(g_tick1 < 138);
	g_tick2=0;
	LED_OFF(LED_PORT_ID,RED_LED_PIN);
	LED_ON(LED_PORT_ID,GREEN_LED_PIN);

	while(g_tick1 < 138);
	g_tick2 =0;
	LED_OFF(LED_PORT_ID,GREEN_LED_PIN);
	LED_ON(LED_PORT_ID,YELLOW_LED_PIN);
	while(g_tick1 < 138);
	g_tick2=0;
	LED_OFF(LED_PORT_ID,YELLOW_LED_PIN);
}


/* Function for Enabling 7-segment Only without the Leds */
void Sev_seg()
{
	if((PORTD & 0x0F) == 0)
	{
		num = 9;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	else
	{
		// decrement 7-segment every interrupt
		num--;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	g_tick2=0;
	while (g_tick2 < 4);
	g_tick2 = 0;
	if((PORTD & 0x0F) == 0)
	{
		num = 9;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	else
	{
		// decrement 7-segment every interrupt
		num--;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	while (g_tick2 < 4);
	g_tick2 = 0;
	if((PORTD & 0x0F) == 0)
	{
		num = 3;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	else
	{
		// decrement 7-segment every interrupt
		num--;
		PORTD = (PORTD & 0xF0) | (num & 0x0F);
	}
	while (g_tick2 < 4);
	g_tick2 = 0;
}

/* Function for Enabling the entire Traffic light system */
void Traffic_On(void)
{
	if((PORTD & 0x0F) == 9)
	{
		LED_ON(LED_PORT_ID, GREEN_LED_PIN);
	}
	if(GPIO_readPin(LED_PORT_ID, GREEN_LED_PIN) == LOGIC_HIGH)
	{
		/* check the 7-segment if is count is 0 */
		if((PORTD & 0x0F) == 0)
		{
			num = 9;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		else
		{
			// decrement 7-segment every interrupt
			num--;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		g_tick2=0;        /* reset the ticks counter */

		while (g_tick2 < 4);
		g_tick2 = 0;       /* reset the ticks counter */
	}
	if((PORTD & 0x0F) == 0)
	{
		LED_OFF(LED_PORT_ID, GREEN_LED_PIN);
		LED_ON(LED_PORT_ID, YELLOW_LED_PIN);
	}
	while(g_tick1 < 4);
	g_tick1=0;            /* reset the ticks counter */
	if(GPIO_readPin(LED_PORT_ID, YELLOW_LED_PIN) == LOGIC_HIGH)
	{
		/* check the 7-segment if is count is 0 */
		if((PORTD & 0x0F) == 0)
		{
			num = 3;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		else
		{
			// decrement 7-segment every interrupt
			num--;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		g_tick2=0;          /* reset the ticks counter */

		while (g_tick2 < 4);
		g_tick2 = 0;          /* reset the ticks counter */
	}
	if((PORTD & 0x0F) == 0)
	{
		LED_OFF(LED_PORT_ID, YELLOW_LED_PIN);
		LED_ON(LED_PORT_ID, RED_LED_PIN);
	}
	if(GPIO_readPin(LED_PORT_ID, RED_LED_PIN) == LOGIC_HIGH)
	{
		/* check the 7-segment if is count is 0 */
		if((PORTD & 0x0F) == 0)
		{
			num = 7;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		else
		{
			// decrement 7-segment every interrupt
			num--;
			PORTD = (PORTD & 0xF0) | (num & 0x0F);
		}
		g_tick2=0;           /* reset the ticks counter */

		while (g_tick2 < 4);
		g_tick2 = 0;         /* reset the ticks counter */
	}
	if((PORTD & 0x0F) == 0)
	{
		LED_OFF(LED_PORT_ID, RED_LED_PIN);
		LED_ON(LED_PORT_ID, GREEN_LED_PIN);
	}
}

int main()
{
	SREG |= (1<<7);      /* Enable global interrupts in MC */
	DDRD  |= 0x0F;      /* Configure the first four pins in PORTD as output pins.*/
	PORTD &= 0xF0;      /* Initialize the 7-seg display zero at the beginning. */

	/* Initialize Led Driver */
	LED_Init();

	/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
	 * so put initial timer counter = 0 so 0 --> 255 (256ms per overflow)
	 */
	Timer_Config timer_config_normal = {Timer0,Normal,0,0,Prescale_1024,timerCallBack};
	Timer_init(&timer_config_normal);

	/* For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
	 * so we just need 250 counts to get 250ms every compare match.
	 * put initial timer counter=0 and output compare register=249 0 --> 250 (250ms per compare match)
	 * so we need timer to make 4 compare matches to get 1 second
	 */
	Timer_Config timer_config_compare = {Timer1,CTC,0,250,Prescale_1024,timerCallBack2};
	Timer_init(&timer_config_compare);

	while(1)
	{
		Traffic_On();
	}
}

