#ifndef MODBUS_CRC16_H_INCLUDED
#define MODBUS_CRC16_H_INCLUDED
#include "stdint.h"

/*
计算Modbus使用的CRC16。
输入参数为:
arr_buff 待计算的字符串数组的指针。
len 待计算的字符串数组中内容长度。
返回值:
16位CRC16值（注意实际使用时高八位与低八位在modbus中的位置）
*/
uint16_t CRC16(uint8_t *arr_buff,uint16_t len);//计算Modbus的CRC16


/*
计算Modbus使用的CRC16。
输入参数为:
arr_buff 待计算的字符串数组的指针。
len 待计算的字符串数组中内容长度。
crc_arry 传入的用于保存CRC16值得字符串数组指针，一般可直接接在内容后面以实现CRC16的填写。
返回值:
传入的用于保存CRC16值得字符串数组指针
*/
uint8_t *CRC16_Arry(uint8_t *arr_buff,uint16_t len,uint8_t *crc_arry);//计算Modbus的CRC16

#endif // MODBUS_CRC16_H_INCLUDED
