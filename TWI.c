#include "TWI.h"


void I2C_init()
{
	TWBR = 0x20;// �������� �������� ��� 8��� ���������� 100���
}


void I2C_start()
{
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT))); //���� ��������� ���� TWIN
}


void I2C_stop()
{
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
}


int I2C_tranciv_byte(unsigned char byte)
{
	TWDR = byte; //�������� ������ � ������� �������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//��������� �������� ������
	while(!(TWCR&(1<<TWINT))); //���� ��������� ���� TWIN
	if((TWSR & 0xF8)!= TW_MT_DATA_ACK)//��������� ������ �������� �������
	{
		return 0;//���� ������ ������� ���������� 0
	}
	return 1;//���� ����� 1
}


unsigned char I2C_receiver_byte()
{
	int err = 0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);// �������� ����� ������
	while(!(TWCR&(1<<TWINT))); //���� ��������� ���� TWIN
	if((TWSR & 0xF8)!= TW_MR_DATA_ACK) err = 1;
	else err = 0;
	return TWDR;
}


unsigned char I2C_receiver_last_byte()
{

	TWCR = (1<<TWINT)|(1<<TWEN);// �������� ����� ������
	while(!(TWCR&(1<<TWINT))); //���� ��������� ���� TWIN

	return TWDR;
}

unsigned char get_status()
{
	unsigned char status;
	status = TWSR & 0xF8;// ����������� ����� ��� ������ �������� � ��������� ��������
	return status;
}

unsigned char MPU_I2C_R(unsigned char w,unsigned char x, unsigned char r)
	{
		char a;
		I2C_start();//���������� ������� �����
		I2C_tranciv_byte(w);//���������� ����� ������ �� ������
		I2C_tranciv_byte(x);//���������� ����� �������� ������ ����� ������ ������
		I2C_start();//���������� ��������� �����
		I2C_tranciv_byte(r);//���������� ����� ������ �� ������
		a = I2C_receiver_last_byte();//������ ������ �� ��������
		I2C_stop();//���������� ������� ����
		return a;
	}
