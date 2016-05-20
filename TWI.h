#include <avr/io.h>
#include <avr/interrupt.h>

////////////////////////////////////////���������������/////////////////////////////////////////////
#define TW_BUS_FAIL        0x00//���������� ������ ����
#define TW_START    	   0x08//���������� ������� �����
#define TW_MT_AD_ACK       0x18//������� ������ ����� �������� � ����� ��� ������ ������� ���������
#define TW_MT_AD_NACK      0x20//������� ������ ����� �������� � ����� ��� ������ ������� �� ���������
#define TW_MT_DATA_ACK     0x28//������� ������ ������ � ������ ������������� 
#define TW_MT_DATA_NACK    0x30//������� ������ ������ � �� ������ ������������� 
#define TW_MR_AD_ACK       0x40//������� ������ ����� �������� � ����� ��� ������ ������� ���������
#define TW_MR_AD_NACK      0x48//������� ������ ����� �������� � ����� ��� ������ ������� �� ���������
#define TW_MR_DATA_ACK     0x50//������� ������ ������ � ������� �������������
#define TW_MR_DATA_NACK    0x58//������� ������ ��������� ���� � ������� NACK
#define MPU_6050_ADDRESS_W 0xD0//����� ��������� � ������ ������
#define MPU_6050_ADDRESS_R 0xD1//����� ��������� � ������ ������
#define PWR_MGMT_1         0x6B
#define TEMP_OUT_H         0x41//����� �������� ����� ������� ��������� �����������
#define TEMP_OUT_L         0x42//����� �������� ����� ������� ��������� �����������
#define ACCEL_XOUT_H       0x3B//����� �������� ����� ������� ��������� X �������������
#define ACCEL_XOUT_L       0x3C//����� �������� ����� ������� ��������� X �������������
#define ACCEL_YOUT_H       0x3D//����� �������� ����� ������� ��������� Y �������������
#define ACCEL_YOUT_L       0x3E//����� �������� ����� ������� ��������� Y �������������
#define ACCEL_ZOUT_H       0x3F//����� �������� ����� ������� ��������� Z �������������
#define ACCEL_ZOUT_L       0x40//����� �������� ����� ������� ��������� Z �������������
#define GYRO_XOUT_H        0x43//����� �������� ����� ������� ��������� X ���������
#define GYRO_XOUT_L        0x44//����� �������� ����� ������� ��������� X ���������
#define GYRO_YOUT_H        0x45//����� �������� ����� ������� ��������� Y ���������
#define GYRO_YOUT_L        0x46//����� �������� ����� ������� ��������� Y ���������
#define GYRO_ZOUT_H        0x47//����� �������� ����� ������� ��������� Z ���������
#define GYRO_ZOUT_L        0x48//����� �������� ����� ������� ��������� Z ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////�������//////////////////////////////////////////////////////
void I2C_init();// ������������� ���� I2c ������ ������ ������ ��������
void I2C_start();  // ��������� ������� �����
void I2C_stop(); // ��������� ������� ����
int I2C_tranciv_byte(unsigned char byte); // �������� ������
unsigned char I2C_receiver_byte();// ����� ������
unsigned char I2C_receiver_last_byte();// ����� ���������� �����
unsigned char get_status();//������ ��������� �������
unsigned char MPU_I2C_R(unsigned char addrw,unsigned char ra, unsigned char addrr);//�������� ������ ������ �� ������ MPU-6050
unsigned char MPU_I2C_W(unsigned char addrw,unsigned char ra, unsigned char data);//�������� ������
/////////////////////////////////////////////////////////////////////////////////////////////////////
