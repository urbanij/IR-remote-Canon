/* 
 * shoot.c -- ARDUINO PRO MINI code
 * v1.0
 * Created: Jul 2, 2017 10:22 AM
 * Author: Francesco Urbani
 * demo aruino uno: https://youtu.be/ytz441CO3a4
 * 
 *
 *	note:
 *	it just works. plug the IR pcb into pin [1, 3] of 
 *	the arduino uno and upload the code.
 *	there is no control whatsoever, so the camera will 
 *	shoot as long as the IR beams reach the receiver of the DSLR.
 *
 */



#define F_CPU           16000000UL 	// 16 MHz
#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>

#define HPERIOD         0.01524     // 15.24 us
#define NPULSES         16
#define INSTANT         7.33        // 7.77 ms
#define DELAYED         5.36        // 5.36 ms

#define VCC             0b00000100  // PD2
#define IRLED           0b00001000  // PD3

#define ARDUINOLED      0b00100000  // PB5


void 
setup(void)
{
	/* setup IOs */
	DDRD  |= IRLED;         /* set IRLED as output */
	DDRD  |= VCC;           /* set VCC as output */
	PORTD |= VCC;           /* set VCC high */
	DDRB  |= ARDUINOLED;    /* set arduino led (pin 13) as output */

	/* Reduce power consumption */
	ADCSRA 	&= ~_BV(ADEN);  /* Disable ADC */
	ACSR 	&= ~_BV(ACD);   /* Disable the analog comparator */
}


void 
flashIRLED(void)
{
	for(uint8_t i=0; i<NPULSES; i++)
	{
		PORTD |= IRLED;
		_delay_ms(HPERIOD);
		PORTD &= ~IRLED;
		_delay_ms(HPERIOD);
	}
	return;
}


void
flashArduinoLED()
{
	PORTB |= ARDUINOLED;
	_delay_ms(20);
	PORTB &= ~ARDUINOLED;
	return;
}


void 
shoot(void)
{
	flashIRLED();
	_delay_ms(INSTANT);
	flashIRLED();
	return;
}



int 
main(void)
{
	setup();
	while (1)
	{
		shoot();
		flashArduinoLED();

		_delay_ms(2020);
	}

	return 0;
}
