/*
 * Test07-UART.c
 *
 * Created: 2024-10-25 오전 9:41:40
 * Author : user
 */ 
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU	16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void UART_init()
{
	    // UART Register setting 1 - Baud rate : 9600
	    
	    UCSR0A |= (1<<U2X0); //UCSRnA 레지스터 1번 비트 U2Xn에 1을 넣어 2배속 설정
	    UBRR0L = 207;		 //baud rate : 9600
	    UBRR0H = 0;
	    
	    UCSR0C &= ~((1<<UPM01)|(1<<UPM00));  // Parity - 00:None(default)  10:Even  11:Odd
	    
	    UCSR0B &= ~(1<<UCSZ02);
	    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // Data bits - 011 : 8bit(default), 111 : 9 bit, 010 : 7bit .....
	    
	    UCSR0C &= ~(1<<USBS0);				 // Stop bit - 0 : 1bit(default),   1 : 2bit
	    
	    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);   // UART Open
}

void UART0_putc(char c)
{
	while(1)
	{
		if(UCSR0A & (1<<UDRE0)) break;    // 입출력 버퍼가 준비될 때까지 대기
	}
	UDR0 = c;	//send 동작
}

void UART0_puts(char *str)
{
	while(*str) UART0_putc(*str++);
}

char buf[256];  //buffer 공간
 char *str = "Button Pushed!!\r\n";
 int n = 0;
ISR(INT0_vect)
{
	n++;
	sprintf(buf, "button Pushed %d times.\r\n", n);
	UART0_puts(buf); 
}

int main(void)
{
	UART_init();
	UART0_puts("\033[2J");						// screen clear - ESC[2J                   escape sequancee
	UART0_puts("\033[;0H");						// move cursor to Lefttop - ESC[0;0H
	EIMSK |= (1<<INT0);
	EICRA |= 0x02;
	
	
	sei();
	
    while (1) 
    {
    }
}

