//Программа Master reciver to bus i2c and transiver to UART



#include "TWI.h"
#include "UART.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>


	enum measure_mode
	{
		accel_xh,
		accel_xl,
		accel_yh,
		accel_yl,
		accel_zh,
		accel_zl,
		hyro_xh,
		hyro_xl,
		hyro_yh,
		hyro_yl,
		hyro_zh,
		hyro_zl,
		temperature_h,
		temperatyre_l
	};
	int array_adress[] =
	{ 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
			0x41, 0x42 };
	enum measure_mode current = accel_xh;
	char data;

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

			cli();
			I2C_tranciv_byte(MPU_6050_ADDRESS_W);		
			sei();

			break;

		case ReStart:

			cli();
			I2C_tranciv_byte(MPU_6050_ADDRESS_W);
			sei();

			break;

		case TW_MT_AD_ACK:
			
			cli();
			int reg_adress = array_adress[(int)current];
			I2C_tranciv_byte(reg_adress);
			sei();

			break;

		case TW_MT_AD_NACK:
			
			break;
		
		case TW_MT_DATA_ACK:

			cli();
			I2C_start();
			sei();

			break;

		case TW_MT_DATA_NACK:
			
			break;

		case TW_MR_AD_ACK:

			cli();
			data = I2C_receiver_last_byte();			
			sei();

			break;

		case TW_MR_AD_NACK:
			
			break;

		case TW_MR_DATA_ACK:
			
			break;

		case TW_MR_DATA_NACK:

			cli();
			I2C_stop();

			if(current == temperatyre_l)
				
				current = accel_xh;
				else current++;
			
			I2C_start();
			sei();

			break;


	}
}


int main()
{
	UART_init(bauddivider);// инициализация UART
	I2C_init();// инициализация шины TWI
//	_delay_ms(1);	
	DDRD = 1<<PD5|1<<PD4;
	PORTD = 0<<PD5|0<<PD4;


/*		int X_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,XA_TEST,MPU_6050_ADDRESS_R);
		int Y_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,YA_TEST,MPU_6050_ADDRESS_R);
		int Z_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,ZA_TEST,MPU_6050_ADDRESS_R);
		UART_transiever_itoa(X_TEST&0x1F);
		UART_transiever_itoa(Y_TEST&0x1F);
		UART_transiever_itoa(Z_TEST&0x1F);	*/
	sei();	
	I2C_start();
	
	for(;;)
	{
		

/*		PORTD = 1<<PD5;
		_delay_ms(1000);	
		PORTD = 0<<PD5;			
		
		int X_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,XA_TEST,MPU_6050_ADDRESS_R);
		int Y_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,YA_TEST,MPU_6050_ADDRESS_R);
		int Z_TEST = MPU_I2C_R(MPU_6050_ADDRESS_W,ZA_TEST,MPU_6050_ADDRESS_R);
		UART_transiever_itoa(X_TEST&0x1F);
		UART_transiever_itoa(Y_TEST&0x1F);
		UART_transiever_itoa(Z_TEST&0x1F);
		UART_write(" ");
////////////////////////////читаем показания акселерометра X,Y,Z и передаем их по UART///////
		UART_write("ACCEL_X,Y,Z:");
		char ACCEL_XH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_XL = (MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_XOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t ACCEL_X = ACCEL_XH<<8|ACCEL_XL;
		UART_transiever_itoa(ACCEL_X);
		
		UART_write(" ");
		int ACCEL_YH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_YL = (MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_YOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t ACCEL_Y = ACCEL_YH<<8|ACCEL_YL;
		UART_transiever_itoa(ACCEL_Y);
		
		UART_write(" ");
		int ACCEL_ZH = MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_H, MPU_6050_ADDRESS_R);
		int ACCEL_ZL = (MPU_I2C_R(MPU_6050_ADDRESS_W,ACCEL_ZOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t ACCEL_Z = ACCEL_ZH<<8|ACCEL_ZL;
		UART_transiever_itoa(ACCEL_Z);
		
/////////////////////////////////////////////////////////////////////////////////////////////		

////////////////////////////читаем показания гироскропа X,Y,Z и передаем их по UART//////////
		UART_write(" GYRO_X,Y,Z:");		
		int GYRO_XH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_XL = (MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_XOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t GYRO_X = GYRO_XH<<8|GYRO_XL;
		UART_transiever_itoa(GYRO_X);
		

		UART_write(" ");
		int GYRO_YH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_YL = (MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_YOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t GYRO_Y = GYRO_YH<<8|GYRO_YL;
		UART_transiever_itoa(GYRO_Y);
		

		UART_write(" ");
		int GYRO_ZH = MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_H, MPU_6050_ADDRESS_R);
		int GYRO_ZL = (MPU_I2C_R(MPU_6050_ADDRESS_W,GYRO_ZOUT_L, MPU_6050_ADDRESS_R))&0xF0;
		int16_t GYRO_Z = GYRO_ZH<<8|GYRO_ZL;
		UART_transiever_itoa(GYRO_Z);
		
/////////////////////////////////////////////////////////////////////////////////////////////	
		

////////////////////////////читаем показания термометра и передаем их по UART////////////////
		UART_write(" TEMPERATUR:");
		int TEMP_H = MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_H, MPU_6050_ADDRESS_R);
		int TEMP_L = MPU_I2C_R(MPU_6050_ADDRESS_W,TEMP_OUT_L, MPU_6050_ADDRESS_R);
		int16_t TEMPERATUR = TEMP_H<<8|TEMP_L;
		TEMPERATUR = TEMPERATUR/340+36;
		UART_transiever_itoa(TEMPERATUR);
/////////////////////////////////////////////////////////////////////////////////////////////
		
		UART_write("\r\n");
	
/////////////////////////////////////////////////////////////////////////////////////////////
		PORTD = 1<<PD4;
		_delay_ms(500);
		PORTD = 0<<PD4;
		_delay_ms(500);
*/					
	}
	return 0;
}
