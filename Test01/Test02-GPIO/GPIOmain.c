#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL //16 MHz    기본 셋팅은 1 MHz라서, 바꿔야 함

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define SW1 PORTG4
#define SW2 PORTD0
#define SW3 PORTD1
#define LED1 PORTG1

volatile int ival = 1000;  

ISR(INT0_vect) //점점 느리게  0번 인터럽트 벡터
{	
	ival +=500;
}

ISR(INT1_vect) //점점 빠르게  1번 인터럽트 벡터
{
	ival -= 200;
	if(ival < 0) ival = 0;
}

int main(void)
{
    DDRG &= ~0x0C;  // 0b 0000 1100 => 0b 1111 0011 입력마스크
	DDRG |= 0x03;   // 0b xxxx xx11 출력마스크
	//DDRG &= ~0x07; // 0b xxxx x000	==>	xxxx x111(not (~)) 헷갈리니까 not 연산 
	
	PORTG |= _BV(LED1); //(1<<LED1);  //0x10; //시작되면 led on, G0 ~ G3 현상태 유지 (pull down)
    StandBy();
	PORTG &= ~_BV(LED1);
	
	// Mask Register : EIMSK
	EIMSK |= 0x03;  // 0b 0000 0011 : 0x03
	// Create register : EICRA
	EICRA |= 0x0A; //0b 0000 111 : 0x0F, 0b xxxx 1010
	
	sei();
    while (1) 
    {

		PORTG |= _BV(LED1); // LED ON
		_delay_ms(ival);		// 1/1000 sec delay
		PORTG &= ~_BV(LED1); // LED OFF
		_delay_ms(ival);
    }
}

