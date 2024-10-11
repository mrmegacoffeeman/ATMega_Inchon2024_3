#define F_CPU 16000000UL  //16 MHz
#include <avr/io.h> // AVR 기본 헤더
#include <util/delay.h> //delay함수 헤더
//  SW PORT : PG3, Input
// LED Port : PG4, Output
int Check()
{
		    char v = PING & 0x08;  // v = G그룹 3번 bit의 값 1000 = 8
		    if( v == 0 ) return 1; // Pushed !!!
			return 0;
}

int main(void)
{

   DDRG |= 0x10;		// xxxx xxxx ==> xxx1 xxxx: 1=출력   |= 비트 or로 두면 출력만 1이면 된다는 뜻
   DDRG &= ~0x08;		// xxxx xxxx ==> xxxx 0xxx: 0=입력   &= ~0x00 출력 0으로 만든다는 뜻
						//DDG3 = 1; //bit에 직접 접근, but const (상수), read only write는 안된다 ==> 0x10 = 1 과 같다
   
   char mode = 0;		//mod==0 : disable, mode = 1 : active
						//char v = 1;			//변수 외부 선언
   while(1)				//loop until Switch press
   {
	   if(Check() == 1) { mode = 1; break; }		//check가 1이면 모드를 1로 두고 빠져나간다
	      }
   while (1)
    {
		if(Check())
		{
			if(mode ==0) mode = 1;
			else         mode = 0;
			_delay_ms(200);
		}
		if(mode == 1)
		{
			
		PORTG |= 0x10;		// 해당 bit on
		_delay_ms(200);		// 2/10초 (200ms)
		PORTG &= ~0x10;		// 해당 bit OFF
		_delay_ms(200);		// 2/10초 (200ms)
		}
		if(Check())
		{
			if(mode == 1 ) mode = 0;
			else mode = 1;
		}
		_delay_ms(100);		//적절한 딜레이 (튜닝)
   }
}