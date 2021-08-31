/*
 * Task1, main.c
 * Purpose: write a program to blink a LED using while() loops.
 *
 * @author Oleksandr Ushkarenko
 * @version 1.0 30/08/2021
 */

#include "stm32f3xx.h"

/*
 * The definitions are used to simplify the configuration of the RCC and GPIO registers.
 * All the values are obtained from the stm32f303 reference manual and
 * discovery kit with stm32f303 user manual.
 */
#define LED_PORT 			GPIOE
#define LED_PORT_CLOCK_EN 	(1U<<21)

#define LED_RED_PIN_9 		(1U << 9)
#define LED_RED_PIN_13 		(1U << 13)
#define LED_BLUE_PIN_8		(1U << 8)
#define LED_BLUE_PIN_12		(1U << 12)
#define LED_ORANGE_PIN_10 	(1U << 10)
#define LED_ORANGE_PIN_14 	(1U << 14)
#define LED_GREEN_PIN_11 	(1U << 11)
#define LED_GREEN_PIN_15 	(1U << 15)

#define LED_RED_MODE_PIN_9 			(0x01U << 18)
#define LED_RED_MODE_PIN_13 		(0x01U << 26)
#define BLUE_LED_MODE_PIN_8			(0x01U << 16)
#define BLUE_LED_MODE_PIN_12		(0x01U << 24)
#define ORANGE_LED_MODE_PIN_10 		(0x01U << 20)
#define ORANGE_LED_MODE_PIN_14 		(0x01U << 28)
#define GREEN_LED_MODE_PIN_11 		(0x01U << 22)
#define GREEN_LED_MODE_PIN_15 		(0x01U << 30)

/*
 * Function prototypes.
 */
void port_clock_init(void);
void port_init(void);
void delay(void);
void led_on(int pin);
void led_off(int pin);

/*
 * The entry point of the program. he program demonstrates the periodic
 * blinking of LEDs - turning on LEDs LD3, LD6, LD7, LD10,
 * and then LD4, LD5, LD8, LD9 that are on the discovery board.
 */
int main(void)
{

	port_clock_init();
	port_init();

	while(1) {
		led_on(LED_RED_PIN_9 | LED_RED_PIN_13 | LED_GREEN_PIN_11 | LED_GREEN_PIN_15);
		delay();

		led_off(LED_RED_PIN_9 | LED_RED_PIN_13 | LED_GREEN_PIN_11 | LED_GREEN_PIN_15);
		led_on(LED_ORANGE_PIN_10 | LED_ORANGE_PIN_14 | LED_BLUE_PIN_8 | LED_BLUE_PIN_12);
		delay();

		led_off(LED_ORANGE_PIN_10 | LED_ORANGE_PIN_14 | LED_BLUE_PIN_8 | LED_BLUE_PIN_12);
	}

	return 0;
}

/*
 * Function enables clocking of the port (GPIOE) to which the LEDs are connected.
 */
void port_clock_init(void)
{
	RCC->AHBENR |= LED_PORT_CLOCK_EN;
}

/*
 * The pins to which the LEDs are connected are set to output.
 */
void port_init(void)
{
	LED_PORT->MODER |= LED_RED_MODE_PIN_9;
	LED_PORT->MODER |= LED_RED_MODE_PIN_13;
	LED_PORT->MODER |= BLUE_LED_MODE_PIN_8;
	LED_PORT->MODER |= BLUE_LED_MODE_PIN_12;
	LED_PORT->MODER |= ORANGE_LED_MODE_PIN_10;
	LED_PORT->MODER |= ORANGE_LED_MODE_PIN_14;
	LED_PORT->MODER |= GREEN_LED_MODE_PIN_11;
	LED_PORT->MODER |= GREEN_LED_MODE_PIN_15;
}

/*
 * This function makes time delay.
 */
void delay(void)
{
	for(int i = 0; i < 500000; i++) { }
}

/*
 * The function switches on the LED connected to the pin by setting at the pin
 * high level of the signal.
 */
void led_on(int pin)
{
	LED_PORT->ODR |= pin;
}

/*
 * The function switches off the LED connected to the pin by setting at the pin
 * low level of the signal.
 */
void led_off(int pin)
{
	LED_PORT->ODR &= ~pin;
}
