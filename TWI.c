#include "TWI.h"


void I2C_init()
{
	TWBR = 0x20;// скорость передачи при 8мГц получается 100кГц
}


void I2C_start()
{
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT))); //ждем установку бита TWIN
}


void I2C_stop()
{
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
}


int I2C_tranciv_byte(unsigned char byte)
{
	TWDR = byte; //записали данные в регистр передачи данных
	TWCR = (1<<TWINT)|(1<<TWEN);//запустили передачу данных
	while(!(TWCR&(1<<TWINT))); //ждем установку бита TWIN
	if((TWSR & 0xF8)!= TW_MT_DATA_ACK)//проверяем данные регистра статуса
	{
		return 0;//если данные неверны возвращаем 0
	}
	return 1;//если верны 1
}


unsigned char I2C_receiver_byte()
{
	int err = 0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);// включили прием данных
	while(!(TWCR&(1<<TWINT))); //ждем установку бита TWIN
	if((TWSR & 0xF8)!= TW_MR_DATA_ACK) err = 1;
	else err = 0;
	return TWDR;
}


unsigned char I2C_receiver_last_byte()
{

	TWCR = (1<<TWINT)|(1<<TWEN);// включили прием данных
	while(!(TWCR&(1<<TWINT))); //ждем установку бита TWIN

	return TWDR;
}

unsigned char get_status()
{
	unsigned char status;
	status = TWSR & 0xF8;// накладываем маску для чтения значения в статусном регистре
	return status;
}

unsigned char MPU_I2C_R(unsigned char w,unsigned char x, unsigned char r)
	{
		char a;
		I2C_start();//отправляем условие СТАРТ
		I2C_tranciv_byte(w);//отправляем адрес модуля на запись
		I2C_tranciv_byte(x);//отправляем адрес регистра откуда будем читать данные
		I2C_start();//отправляем повторный СТАРТ
		I2C_tranciv_byte(r);//отправляем адрес модуля на чтение
		a = I2C_receiver_last_byte();//читаем данные из регистра
		I2C_stop();//отправляем условие СТОП
		return a;
	}
