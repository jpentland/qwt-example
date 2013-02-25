/* This file contains definitions of functions
 * for interacting with the LED output device
 * as part of the volume meter application
 *
 * Author: Joseph Pentland <0804325p@student.gla.ac.uk>
 * Created: 7 March 2013
 */

#ifndef LEDOUT_H
#define LEDOUT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Initialise the ADC
 *
 * Return: Pointer to led structure, or NULL
 */
void led_init(int data_min, int data_max);

/* Write a value to the leds */
void led_write(int value);

#ifdef __cplusplus
}
#endif

#endif /* LEDOUT_H */
