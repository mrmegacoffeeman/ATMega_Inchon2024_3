/*
 * Test06 - PWM.c
 *
 * Created: 2024-10-23 오전 9:48:50
 * Author : user
 */ 
#define F_CPU 16000000L
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define BUZZER PORTB6
#define DDR   DDRB
#define PORT  PORTB

volatile int period = 10;
volatile int DutyRate = 50;

int CS = 8;	//분주비, Prescaler

enum { DO=130, Do=138, RE=146, Re=155, MI=164, FA=174, Fa=185, SL=196, Sl=207, LA=220, La=233, SI=246 }; //각 음계에 맞는 주파수 리스트
	int song[] = {SL,SL,LA,LA,SL,SL,MI,SL,SL,MI,MI,RE,SL,SL,LA,LA,SL,SL,MI,SL,MI,RE,MI,DO };
	int song1[100];
	
void conv()
{
	for(int i=0; i<25; i++)
	{
		song1[i] = F_CPU / (CS * (long)song[i]*5);   //ICR(song1[i]) 계산 (top(max))  ex)16000000 / 1024 / 130 = 120.07...
		//long으로 오버플로우 방지하고 int CS = 1024, 분주비 1024로 맞춰도 됨
	}
} 



ISR(INT0_vect)
{
	//period -= 10;                                                                            
	//if(period < 0) period = 500;  
}

ISR(INT1_vect)
{

	//DutyRate += 10;
	//if(DutyRate > 90) DutyRate = 10
	; 
}


int led_y_st = 0;
int cnt, cnt_ref = 0;

ISR(TIMER1_COMPB_vect)
{
	//if(++cnt > cnt_ref)
	//{
			//if(led_y_st)	{	PORT &= ~(1<<LED_Y); led_y_st = 0; }
			//else			{	PORT |= (1<<LED_Y);  led_y_st = 1; }
			//cnt = 0;
	//}
	//TCNT0 = 0;
}

ISR(INT2_vect)
{
	//cnt_ref--;
	//if(cnt_ref < 0) cnt_ref = 50;
	//OCR0+=10;
}

int main(void)
{ 
	int ii = 0;
	conv();
	EIMSK |= (1<<INT0) | (1<<INT1) | (1<<INT2);  //0x07;
	EICRA |= 0x2A;
	
	TIMSK |= (1<<OCIE1B);
	
	TCCR1A |= 0xAA;  // COMx : 10b  : normal, WGM : xx10
	TCCR1B |= 0x1A;  // WGM : 11xx, CS : 010 : 분주비 8
	
	
	DDRB |= 0xf0;  //PB4~7 : OUTPUT
	DDR |=(1<<BUZZER);
	sei();
    while (1) 
    {

		ICR1 = song1[ii];
		OCR1B = song1[ii] * 0.5;
		_delay_ms(250);	
		ii++;
		if(ii==24) ii=0;
		
    }
}

