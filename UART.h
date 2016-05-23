#include <avr/io.h>
#include <avr/interrupt.h>

///////макросы для инициализации UART////////////////////
//#define F_CPU 8000000L
#define XTAL 8000000L
#define baudrate 9600L
#define bauddivider (XTAL/(16*baudrate)-1)

////////////////////////////////////////////////




///////////////////////функции///////////////////////////
void UART_init(unsigned int bit_rate);// инициализация UART
char UART_transiever(unsigned char tx);// передача данных по UART
char UART_reciever();//прием данных по UART
char UART_write(char * p);
