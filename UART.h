#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>

///////������� ��� ������������� UART////////////////////
//#define F_CPU 8000000L
#define XTAL 8000000L
#define baudrate 9600L
#define bauddivider (XTAL/(16*baudrate)-1)

////////////////////////////////////////////////




///////////////////////�������///////////////////////////
void UART_init(unsigned int bit_rate);// ������������� UART
char UART_transiever(unsigned char tx);// �������� ������ ����� �� UART
char UART_reciever();//����� ������ ����� �� UART
char UART_write(char *p);//�������� ������ �� UART
char UART_transiever_itoa(unsigned char tx);//������� ��������� ����� � ������ � ������� � UART
