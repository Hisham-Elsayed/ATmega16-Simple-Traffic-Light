/*******************************************************************************
 *  [FILE NAME]: led.c
 *
 *  [Author]: Hisham Elsayed
 *
 *  [DESCRIPTION]: Source file LED Driver
 *******************************************************************************/
#include "gpio.h"
#include "led.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LED_Init(void)
{
	/* Red LED */
	GPIO_setupPinDirection(LED_PORT_ID, RED_LED_PIN, PIN_OUTPUT);
	/* Yellow LED */
	GPIO_setupPinDirection(LED_PORT_ID, YELLOW_LED_PIN, PIN_OUTPUT);
	/* Green LED */
	GPIO_setupPinDirection(LED_PORT_ID, GREEN_LED_PIN, PIN_OUTPUT);
}

void LED_ON(uint8 port_id,uint8 pin_id)
{
	port_id=LED_PORT_ID;
	switch (pin_id)
		{
	case(RED_LED_PIN):
			GPIO_writePin(LED_PORT_ID, RED_LED_PIN, LOGIC_HIGH);
	break;
	case(YELLOW_LED_PIN):
			GPIO_writePin(LED_PORT_ID, YELLOW_LED_PIN, LOGIC_HIGH);
	break;
	case(GREEN_LED_PIN):
			GPIO_writePin(LED_PORT_ID, GREEN_LED_PIN, LOGIC_HIGH);
	break;
		}
}

void LED_OFF(uint8 port_id,uint8 pin_id)
{
	port_id=LED_PORT_ID;
	switch (pin_id)
		{
	case(RED_LED_PIN):
			GPIO_writePin(LED_PORT_ID, RED_LED_PIN, LOGIC_LOW);
	break;
	case(YELLOW_LED_PIN):
			GPIO_writePin(LED_PORT_ID, YELLOW_LED_PIN, LOGIC_LOW);
	break;
	case(GREEN_LED_PIN):
			GPIO_writePin(LED_PORT_ID, GREEN_LED_PIN, LOGIC_LOW);
	break;
		}
}
