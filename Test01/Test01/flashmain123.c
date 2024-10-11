#define F_CPU 16000000UL
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

int push()
{
	char v1 = PING & 0x01; //0번핀
	char v2 = PING & 0x02; //1번핀
	char v3 = PING & 0x04; //2번핀
	if( v1 == 0 ) return 1;
	if( v2 == 0 ) return 2;
	if( v3 == 0 ) return 3;
	return 0;
}

int main(void) 
{
	DDRG |= 0x00;		// xxxx xxxx ==> xxx1 xxxx: 1=출력   |= 비트 or로 두면 출력만 1이면 된다는 뜻
	DDRG &= ~0x02;		// xxxx xxxx ==> xxxx 0xxx: 0=입력   &= ~0x00 출력 0으로 만든다는 뜻
	DDRG &= ~0x04;
	
	char mode = 0
	
	int delay1 = 200
	
	
	while (1)
	{
		if(push(0))
		{
			if(mode == 0) mode = 1;
			else          mode = 0;
			_delay_ms(200);
		}
		if(mode == 1)
		{
			
			PORTG |= 0x01;		// 해당 bit on
			_delay_ms(200);		// 2/10초 (200ms)
			PORTG &= ~0x01;		// 해당 bit OFF
					}
		if(push(2))
		{
			mode = 1; }
		{
			
			PORTG |= 0x02;
			_delay_ms(delay1);
			PORTG &= ~0x02;
			_delay_ms(delay1);
		}
		
		if(push(3))
		{ mode =1;		
		}
		{
			
			PORTG |= 0x04;
			_delay_ms(delay2);
			PORTG &= ~0x04;
			_delay_ms(delay2);
		}
		_delay_ms(100);		//적절한 딜레이 (튜닝)
	}
	
	
} //내가짠거 제대로 동작안함