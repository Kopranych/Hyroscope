//Программа Master reciver to bus i2c and transiver to UART



#include "TWI.h"
#include "UART.h"
#include <util/delay.h>

ISR(TWI_vect)
{
	switch(get_status())
	{
		case TW_BUS_FAIL:
		/*/	ERROR();
			char array[4] = "Error";
			for(int i = 0; i< countdown; i++)
			{
				transiver_UART(array[i]);
			}*/
		break;
		
		case TW_START:
		
			break;

		case TW_MT_AD_ACK:
		
			break;

		case TW_MT_AD_NACK:
			
			break;
		
		case TW_MT_DATA_ACK:

			break;

		case TW_MT_DATA_NACK:
			
			break;

		case TW_MR_AD_ACK:
			
			break;

		case TW_MR_AD_NACK:
			
			break;

		case TW_MR_DATA_ACK:
			
			break;

		case TW_MR_DATA_NACK:
			
			break;


	}
}


void main()
{
	UART_init(bauddivider);// инициализация UART
	I2C_init();// инициализация шины TWI
	MPU_I2C_W(MPU_6050_ADDRESS_W,PWR_MGMT_1, 0x00);
//	_delay_ms(1);
	
		DDRD = 1<<PD5|1<<PD4;
		PORTD = 0<<PB5|0<<PB4;
	

	for(;;)
	{
		
		PORTD = 1<<PD5;
		_delay_ms(1000);	
		PORTD = 0<<PD5;			

////////////////////////////читаем показания акселерометра X,Y,Z и передаем их по UART///////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////				

////////////////////////////читаем показания гироскропа X,Y,Z и передаем их по UART//////////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////	
		

////////////////////////////читаем показания термометра и передаем их по UART////////////////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////
		PORTD = 1<<PD4;
		_delay_ms(500);	
		PORTD = 0<<PD4;
		_delay_ms(500);	
					
	}
}
