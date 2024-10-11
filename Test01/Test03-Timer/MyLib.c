#include <avr/io.h>

int TestBit(char pin, char mask)	//PINx 레지스터의 값의 mask bit가 0인지 1인지 판별
{
	if((pin & mask) != 0) return 1;
	return 0;
}

void StandBy() // PG4 pin으로 프로그램 시작 스위치 연결
{
	DDRG &= ~0x10;  // PG4 : 입력 설정
	PORTG |= 0x10;  // PG4 : pull-up
	
	while(!TestBit(PING, 0x10));
	while(TestBit(PING, 0x10));
}