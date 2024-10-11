#include <avr/io.h>
#include <avr/interrupt.h>

#define DDR DDRG
#define LED PORTG1
#define PORT PORTG
#define F_CPU 16000000UL //16 MHz    기본 셋팅은 1 MHz라서, 바꿔야 함

int cnt = 0, st = 0, cnt1=0, cntEx = 5;
ISR(TIMER0_OVF_vect)  //255를 넘어서는 오버플로우가 발생하면 인터럽트
{

	cnt++;
	if(cnt > 25)  //(1/16M) * 256 * 256 * 25 = 0.102 sec
	{
		cnt = 0;
		cnt1++;
		if(cnt1 >= cntEx)
		{
			cnt1 = 0;
		if(st) {  PORT &= ~_BV(LED); st=0;} //켜져있다면 포트해당핀을 끄고
		else   {  PORT |= _BV(LED); st=1;} //꺼져있다면 포트핀을 stable 1상태로 만든다
	  }
	}
}

ISR(INT0_vect) //slower
{
	cntEx++;
}
ISR(INT1_vect) //faster
{
	cntEx--;
	if(cntEx < 1) cntEx = 1;
}
int main(void)
{
	DDR |= _BV(LED); // LED Port 설정
	PORTG |= _BV(LED);
	StandBy();
	PORTG &= ~_BV(LED);
	// Timer Interrupt 0 설정
	TIMSK |= 0x01; // TOIE0(Timer Overflow Interrupt Enable)
	TCCR0 |= 0x06; // 0x06 = 1 1 0  --> 분주비 256
	// External Interrupt 설정
	EIMSK |= 0x03;
	EICRA |= 0x0F;  //riging edge
	sei();
	
    while (1) 
    {
    }
}

