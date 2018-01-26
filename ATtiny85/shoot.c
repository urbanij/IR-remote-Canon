/* 
 * shoot.c -- Atmel ATtiny85
 * v1.0
 * Created: May 14, 2017 11:48:07 AM
 * Author: Francesco Urbani
 *
 * demo: https://youtu.be/q3RMTaMhEME
 */


#define F_CPU           1000000     // 1 MHz
#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>

#define PERIOD          0.027       // 30.48 us	but it's proved to work also in the interval [24 - 31] us!
#define DUTY            0.5         // 50% duty-cycle but it's proved to work also in the interval [0.4 - 0.7]
#define NPULSES         16          // 16 PULSES but also works in the interval [12 - 25]!
#define INSTANT         7.33        // 7.33 ms but also works in the interval [ 7.2 - 8]
#define DELAYED         5.36        // 5.36 ms

#define VISIBLE_LED     0b00000001  //PB0
#define BUTTON1         0b00000010  //PB1 -- BUTTON1 = INSTANT BUTTON
#define BUTTON2         0b00000100  //PB2 -- BUTTON2 = DELAYED BUTTON
#define IRLED           0b00001000  //PB3
#define VCC             0b00010000  //PB4


void
setup(void)
{
	/* setup IOs */
	PORTB |= (BUTTON1 | BUTTON2);   /* pull-high BUTTON1 and BUTTON2 */
	DDRB |= IRLED;	                /* set IRLED as output */
	DDRB |= (VCC | VISIBLE_LED);    /* set VCC and VISIBLE_LED as output */
	PORTB |= VCC;	                /* set VCC high (forever) */
	PORTB &= ~IRLED;                /* set IRLED low on startup (thoguh not mandatory) */
	
	/* Reduce power consumption */
	ADCSRA &= ~_BV(ADEN);           /* Disable ADC */
	ACSR &= ~_BV(ACD); 		        /* Disable the analog comparator */
}


void 
flashIRLED(void)
{
	/* pulse NPULSES times on and off with 50% duty-cycle */
	for (uint8_t i=0; i<NPULSES; i++)
	{
		PORTB |= IRLED;
		_delay_ms(PERIOD*DUTY);
		PORTB &= ~IRLED;
		_delay_ms(PERIOD*(1-DUTY));
	}
}


void
flashArduinoLED()
{
	PORTB |= VISIBLE_LED;
	_delay_ms(30);
	PORTB &= ~VISIBLE_LED;
}


void
shootInstant(void)
{
	flashIRLED();
	_delay_ms(INSTANT);
	flashIRLED();
}


void
shootDelayed(void)
{
	flashIRLED();
	_delay_ms(DELAYED);
	flashIRLED();
}


int
main(void)
{
	setup();

	while (1)
	{
		if (!(PINB & BUTTON1))
		{
			shootInstant();
			flashArduinoLED();
			_delay_ms(300);
		}
		else if (!(PINB & BUTTON2))
		{
			shootDelayed();
			flashArduinoLED();
			_delay_ms(300);
		}
	}

	return 0;
}
