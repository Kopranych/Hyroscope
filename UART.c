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
	while(*p!='\0')
	{
		while (!(UCSRA & (1<<UDRE)));//���� ���� ������� ������ ���������
		char temp = *p;
		p++;
		UDR = temp;//�������� ���� ������
	
	}
	return 0;
}

char UART_transiever_itoa(unsigned char tx)//������� ��������� ����� � ������ � ������� � UART
{	
	char buf[20];
	itoa(tx, buf, 10);
	UART_write(buf);
	return 0;
}


/*char UART_write(char *p)
{
	int i = strlen(p);
	int t;
	for(t = 0; t<i;t++)
	{
		while (!(UCSRA & (1<<UDRE)));//���� ���� ������� ������ ���������
		UDR = p[t];
	}
	return 0;
}*/


