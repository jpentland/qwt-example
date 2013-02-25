/* This file contains definitions of functions
 * for interacting with the ADC used in the 
 * volume meter application
 *
 * Author: Joseph Pentland <0804325p@student.gla.ac.ul>
 * Created: 7 March 2013
 */

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Initialise the ADC
 *
 * Return: Pointer to adc structure, or NULL
 */
void adc_init();

/* Read latest value from ADC */
unsigned short adc_read();

#ifdef __cplusplus
}
#endif

#endif /* ADC_H */
