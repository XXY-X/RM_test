#ifndef __ALGORITHMOFCRC_H
#define __ALGORITHMOFCRC_H

#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
数据传输错误检测
*/
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength, unsigned char ucCRC8);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);

#endif
