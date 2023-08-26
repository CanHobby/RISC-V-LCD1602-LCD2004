/*
 * CHobby_GPIO.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: moun
 */

#ifndef INC_CHOBBY_GPIO_H_
#define INC_CHOBBY_GPIO_H_

#define LED_PORT GPIOC	//  LED on C13
#define LED_PIN  0x2000

void CHobby_GPIO_INIT( GPIO_TypeDef *Port, uint16_t Pins );

#endif /* INC_CHOBBY_GPIO_H_ */
