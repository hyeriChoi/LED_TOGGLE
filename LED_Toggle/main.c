/*
 * LED_Toggle.c
 *
 * Created: 2018-11-07 오후 5:01:55
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define LED_TOGGLE(x,y)      x ^= (1<<y)
#define LED_SET(x,y)      x |= (1<<y)
#define LED_CLEAR(x,y)      x &= ~(1<<y)




volatile int int_tim = 0;
ISR(TIMER0_OVF_vect)
{
	int_tim++;
	int_tim %= 64;
}


int AVR_init()
{
	DDRD |= 0xff;
	PORTD = 0x00;
	TCCR0 |= ((1<<CS02) | (1<<CS01) | (1<<CS00)); //1024 64 1초
	TIMSK |= (1 << TOIE0);
}
int main(void)
{
	 AVR_init();
	 sei();
	 char ledNumber[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
	
	 
    /* Replace with your application code */
    while (1) 
    {
		 for(int i = 0; i<16; i++)
		 {
			 //LED_TOGGLE(PORTA, i);
			 if(i<8)
			 {
				 LED_SET(PORTD,i);
				 _delay_ms(300);
				 LED_CLEAR(PORTD,i);
			 }
			 else
			 {
				 LED_SET(PORTD,((i%8)-7)*(-1));
				 _delay_ms(300);
				 LED_CLEAR(PORTD,((i%8)-7)*(-1));
			 }

		
    }
	}
	
}

