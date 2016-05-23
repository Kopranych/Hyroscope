// ��������� �������� ������ ����� UART

#include "UART.h"


void UART_init(unsigned int bit_rate)
{
	UBRRH = ((bit_rate)>>8);//���������� �������� �������� ������� �������� ��������
	UBRRL = ((bit_rate)& 0xFF);//���������� �������� �������� ������� �������� ��������
	UCSRA = 0x00;//���������� ��� ����� �������� �� ������ ������
	UCSRB |= 1<<RXEN;//���������� ������ ���������
	UCSRB |=1<<TXEN;//���������� ������ �����������
	UCSRB |=1<<RXCIE;//���������� ���������� �� ���������� ������
	UCSRB |=1<<TXCIE;//���������� ���������� �� ���������� ��������
	UCSRB |=1<<UDRIE;//���������� ���������� ��� �������� �������� ������ UDRE
	UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;//��������� ������� �������: 8 ��� ����� ������ 1 ���� ���
}


char UART_reciever()
{
	while(!(UCSRA&(1<<RXC)));//���� ������� ������
	return UDR;
}
	


char UART_transiever(unsigned char tx)
{
	while (!(UCSRA & (1<<UDRE)));//���� ���� ������� ������ ���������
	UDR = tx;//�������� ���� ������
	return 0;
}

char UART_write(char *p)
{
	while(*p)
	{
		while (!(UCSRA & (1<<UDRE)));//���� ���� ������� ������ ���������
		UDR = *p++;//�������� ���� ������
	}
	return 0;
}

