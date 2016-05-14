//��������� Master reciver to bus i2c and transiver to UART



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
	UART_init(bauddivider);// ������������� UART
	I2C_init();// ������������� ���� TWI


	for(;;)
	{
		
////////////////////////////������ ��������� ������������� X,Y,Z � �������� �� �� UART///////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////				

////////////////////////////������ ��������� ���������� X,Y,Z � �������� �� �� UART//////////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_L, MPU_6050_ADDRESS_R));

		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////	
		

////////////////////////////������ ��������� ���������� � �������� �� �� UART////////////////
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_H, MPU_6050_ADDRESS_R));
		UART_transiever(MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_L, MPU_6050_ADDRESS_R));
/////////////////////////////////////////////////////////////////////////////////////////////

		_delay_ms(1000);					
	}
}
