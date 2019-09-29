#ifndef MODBUS_CRC16_H_INCLUDED
#define MODBUS_CRC16_H_INCLUDED
#include "stdint.h"

/*
����Modbusʹ�õ�CRC16��
�������Ϊ:
arr_buff ��������ַ��������ָ�롣
len ��������ַ������������ݳ��ȡ�
����ֵ:
16λCRC16ֵ��ע��ʵ��ʹ��ʱ�߰�λ��Ͱ�λ��modbus�е�λ�ã�
*/
uint16_t CRC16(uint8_t *arr_buff,uint16_t len);//����Modbus��CRC16


/*
����Modbusʹ�õ�CRC16��
�������Ϊ:
arr_buff ��������ַ��������ָ�롣
len ��������ַ������������ݳ��ȡ�
crc_arry ��������ڱ���CRC16ֵ���ַ�������ָ�룬һ���ֱ�ӽ������ݺ�����ʵ��CRC16����д��
����ֵ:
��������ڱ���CRC16ֵ���ַ�������ָ��
*/
uint8_t *CRC16_Arry(uint8_t *arr_buff,uint16_t len,uint8_t *crc_arry);//����Modbus��CRC16

#endif // MODBUS_CRC16_H_INCLUDED
