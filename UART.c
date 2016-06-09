// Программа передает данные через UART

#include "UART.h"


void UART_init(unsigned int bit_rate)
{
	UBRRH = ((bit_rate)>>8);//вычисление значения старшего разряда регистра скорости
	UBRRL = ((bit_rate)& 0xFF);//вычисление значения младшего разряда регистра скорости
	UCSRA = 0x00;//сбрасываем все флаги регистра до начала работы
	UCSRB |= 1<<RXEN;//разрешение работы приемника
	UCSRB |=1<<TXEN;//разрешение работы передатчика
	UCSRB |=1<<RXCIE;//разрешение прерываний по завершению приема
	UCSRB |=1<<TXCIE;//разрешение прерываний по завершению передачи
	UCSRB |=1<<UDRIE;//разрешение прерываний при отчистке регистра данных UDRE
	UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;//установка формата посылки: 8 бит пакет данных 1 стоп бит
}


char UART_reciever()
{
	while(!(UCSRA&(1<<RXC)));//ждем прихода данных
	return UDR;
}
	


char UART_transiever(unsigned char tx)
{
	while (!(UCSRA & (1<<UDRE)));//ждем пока регистр данных очистится
 	UDR = tx;//передаем байт данных
	return 0;
}

char UART_write(char *p)
{
	while(*p!='\0')
	{
		while (!(UCSRA & (1<<UDRE)));//ждем пока регистр данных очистится
		char temp = *p;
		p++;
		UDR = temp;//передаем байт данных
	
	}
	return 0;
}

char UART_transiever_itoa(unsigned char tx)//функция переводит число в строку и выводит в UART
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
		while (!(UCSRA & (1<<UDRE)));//ждем пока регистр данных очистится
		UDR = p[t];
	}
	return 0;
}*/


