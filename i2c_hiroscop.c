//Программа Master reciver to bus i2c and transiver to UART



#include "TWI.h"
#include "UART.h"
#include <util/delay.h>
#include <stdio.h>

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
//	_delay_ms(1);
/*	UDR = 1;
	char arr[] = "124";
	UDR = arr;
	UART_write(arr);
*/

		MPU_I2C_W(MPU_6050_ADDRESS_W,PWR_MGMT_1, 0x00);

		
		DDRD = 1<<PD5|1<<PD4;
		PORTD = 0<<PB5|0<<PB4;
	

	for(;;)
	{
		
		PORTD = 1<<PD5;
		_delay_ms(1000);	
		PORTD = 0<<PD5;			

////////////////////////////читаем показания акселерометра X,Y,Z и передаем их по UART///////
		UART_write("ACCEL_X:");
		int ACCEL_XH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_XL = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_L, MPU_6050_ADDRESS_R);
		int ACCEL_X = ACCEL_XH<<8|ACCEL_XL;
		UART_transiever_itoa(ACCEL_X);
		UART_write("\r\n");

		UART_write("ACCEL_Y:");
		int ACCEL_YH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_YL = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_L, MPU_6050_ADDRESS_R);
		int ACCEL_Y = ACCEL_YH<<8|ACCEL_YL;
		UART_transiever_itoa(ACCEL_Y);
		UART_write("\r\n");

		UART_write("ACCEL_Z:");
		int ACCEL_ZH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_ZL = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_L, MPU_6050_ADDRESS_R);
		int ACCEL_Z = ACCEL_ZH<<8|ACCEL_ZL;
		UART_transiever_itoa(ACCEL_Z);
		UART_write("\r\n");
/////////////////////////////////////////////////////////////////////////////////////////////		

////////////////////////////читаем показания гироскропа X,Y,Z и передаем их по UART//////////
		UART_write("GYRO_X:");		
		int GYRO_XH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_XL = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_L, MPU_6050_ADDRESS_R);
		int GYRO_X = GYRO_XH<<8|GYRO_XL;
		UART_transiever_itoa(GYRO_X);
		UART_write("\r\n");

		UART_write("GYRO_Y:");
		int GYRO_YH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_YL = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_L, MPU_6050_ADDRESS_R);
		int GYRO_Y = GYRO_YH<<8|GYRO_YL;
		UART_transiever_itoa(GYRO_Y);
		UART_write("\r\n");

		UART_write("GYRO_Z:");
		int GYRO_ZH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_ZL = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_L, MPU_6050_ADDRESS_R);
		int GYRO_Z = GYRO_ZH<<8|GYRO_ZL;
		UART_transiever_itoa(GYRO_Z);
		UART_write("\r\n");
/////////////////////////////////////////////////////////////////////////////////////////////	
		

////////////////////////////читаем показания термометра и передаем их по UART////////////////
		UART_write("TEMPERATUR:");
		int TEMP_H = MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_H, MPU_6050_ADDRESS_R);
		int TEMP_L = MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_L, MPU_6050_ADDRESS_R);
		int TEMPERATUR = TEMP_H<<8|TEMP_L;
		TEMPERATUR = TEMPERATUR/340+36;
		UART_transiever_itoa(TEMPERATUR);
/////////////////////////////////////////////////////////////////////////////////////////////
		
		UART_write("\r\n");
	
/////////////////////////////////////////////////////////////////////////////////////////////
		PORTD = 1<<PD4;
		_delay_ms(500);
		PORTD = 0<<PD4;
		_delay_ms(500);
					
	}
}
