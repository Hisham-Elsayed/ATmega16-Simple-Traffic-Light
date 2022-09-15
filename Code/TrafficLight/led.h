/*******************************************************************************
 *  [FILE NAME]: led.h
 *
 *  [Author]: Hisham Elsayed
 *
 *  [DESCRIPTION]: Header file LED Driver
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define   LED_PORT_ID            PORTC_ID
#define   RED_LED_PIN            PIN1_ID
#define   YELLOW_LED_PIN         PIN2_ID
#define   GREEN_LED_PIN          PIN3_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function used to initialize LEDs.
 */
void LED_Init(void);

/*
 * Description :
 * Function used to turn on LEDs.
 */
void LED_ON(uint8 port_id,uint8 pin_id);

/*
 * Description :
 * Function used to turn off LEDs.
 */
void LED_OFF(uint8 port_id,uint8 pin_id);

#endif /* LED_H_ */
