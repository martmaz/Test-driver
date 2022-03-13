#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


// ZMIENNE
volatile int liczBledy = 0;			//liczba bledow zwiekszana gdy wykrycie bledu
volatile uint8_t tablicaWynikow[7];		//tablica do ktorej bd zapisywane wyniki
volatile uint8_t czasMin = 0;		//minimalny czas reakcji z tablicy wynikow
volatile uint8_t czasMax = 0;
volatile int licznik = 0;
volatile unsigned long counter = 0;
volatile unsigned long loop = 0;

// FUNKCJE
void test1(void);
void test2(void);
void test3(void);
void _delay3000ms(void);
void timer_setup(void);
void timer_start(void);
void timer_stop(void);

// OBSLUGA PRZERWAN
ISR(TIMER0_COMPA_vect)
{
	counter++;
	if (counter > 1500)
	{
		counter = 0;
		loop ++ ;
		
	}
	
}


int main(void)
{
	// WE: 13, 12, 11 pin Arduino: PB5, PB4, PB3 -> 0
	
	//WY: -> 1
	//LCD : 10 (RS), 8 (E), 2 (DB4), 3 (DB5), 4 (DB6), 7 (DB7) piny Arduino:
	//      PB2,	 PB0,	PD2,	 PD3,	  PD4,	   PD7
	//DIODY: 5 (GRE), 6 (RED), 9 (YEL) piny Arduino:
	//		 PD5,	  PD6,	   PB1
	
	DDRB = 0b00000111;
	DDRD = 0b11111100;
	
	// USTAWIENIE TIMER:
	 timer_setup();
	
	//KOMUNIKAT ROZPOCZYNAJACY NA LCD :
	
	
	//WYBOR PROGRAMU 1-3
//	int wybor = rand()%3 ;
	
//	switch(wybor)
//	{
//		case 0: test1(); break;
//		case 1: test2(); break;
//		case 2: test3(); break;		
//	}
	 
	 
	// NA RAZIE DO TESTOW  
	test1();
	
	
	
	//OBLICZ WYNIKI : min i max t i lb b³êdów
	
	
	//WYSWIETL WYNIKI NA WYSWIETLACZU
	
    while (1) 
    {
			
		
    }
}

void timer_setup()
{
	TCNT0 = 0;
	TCCR0A |= (1<<WGM12); // CTC
	TCCR0A |= (1<<CS02); //1024 preskaler
	TIMSK0|=(1<<OCIE0A); //odblokowanie przerwan dla TIMER1
	OCR0A = 31250;
	sei();
}
void timer_start()
{
	TCCR0B |= (1<<CS00) ;
}
void timer_stop()
{
	TCCR0A &= ~ ( (1<<CS00));
	TCNT0 = 0;
	loop=0;
}


void _delay3000ms()
{
	loop = 0;
	timer_start();
	while(loop!=100)
	{
		
	}
	
	timer_stop();
	//_delay_ms(3000);
	
	return;
}

void test1()
{
	printf("test 1");
	//kolejnoœæ œwiecenia: R G Y R Y G R G R Y 
	// RED - PD6, YELLOW - PB1, GREEN - PD5
	
	int kolejnosc1[10] = {6, 5, 1, 6, 1, 5, 6, 5, 6, 1};
	//int kolejnosc2[10] = {PIND6, PIND5, PINB1, PIND6, PINB1, PIND5, PIND6, PIND5, PIND6, PINB1};
	
	//pêtla po ka¿dej diodzie: zaœwieæ diodê, czekaj 3 sekundy, zgaœ - idŸ dalej
	for(int i=0;i<10;i++)
	{
		if (kolejnosc1[i] == 1)
		{
			PORTB |= 1<<kolejnosc1[i];
			_delay3000ms();
			PORTB &= ~(1<<kolejnosc1[i]);
		} 
		else
		{
			PORTD |= 1<<kolejnosc1[i];
			_delay3000ms();
			PORTD &= ~(1<<kolejnosc1[i]);
		}
	}
	
	
	
	
	return;
}

void test2()
{
	printf("test 2");
	//kolejnoœæ œwiecenia: Y R Y G R R G Y G R
	// RED - PD6, YELLOW - PB1, GREEN - PD5
	int kolejnosc2[10] = {1, 6, 1, 5, 6, 5, 6, 1, 5, 6};
	
	for(int i=0;i<10;i++)
	{
		if (kolejnosc2[i] == 1)
		{
			PORTB |= 1<<kolejnosc2[i];
			_delay_ms(3000);
			PORTB &= ~(1<<kolejnosc2[i]);
		}
		else
		{
			PORTD |= 1<<kolejnosc2[i];
			_delay_ms(3000);
			PORTD &= ~(1<<kolejnosc2[i]);
		}
	}
		
	return;
}

void test3()
{
	printf("test 3");
	//kolejnoœæ œwiecenia: G Y G R G R Y R Y G
	// RED - PD6, YELLOW - PB1, GREEN - PD5
	int kolejnosc3[10] = {5, 1, 5, 6, 5, 6, 1, 6, 1, 5};
		
	for(int i=0;i<10;i++)
	{
		if (kolejnosc3[i] == 1)
		{
			PORTB |= 1<<kolejnosc3[i];
			_delay_ms(3000);
			PORTB &= ~(1<<kolejnosc3[i]);
		}
		else
		{
			PORTD |= 1<<kolejnosc3[i];
			_delay_ms(3000);
			PORTD &= ~(1<<kolejnosc3[i]);
		}
	}
	return;
}