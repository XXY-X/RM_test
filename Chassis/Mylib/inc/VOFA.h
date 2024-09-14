#ifndef _USART2_H_
#define _USART2_H_

#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define VOFA_MAX_CHANNEL 26 // 最大支持的变量数

/******************************** VOFA 串口+DMA定义 ***********************************/
// 串口波特率
#define VOFA_USART_BAUD_RATE 115200
// 所用串口
#define VOFA_USARTx USART2
// 串口时钟
#define VOFA_USART_APBxClock_FUN RCC_APB1PeriphClockCmd
#define VOFA_USART_CLK RCC_APB1Periph_USART2
// 串口GPIO口时钟
#define VOFA_USART_GPIO_APBxClock_FUN RCC_AHB1PeriphClockCmd
#define VOFA_USART_GPIO_CLK RCC_AHB1Periph_GPIOA

// TX口
#define VOFA_USART_TX_PORT GPIOA
#define VOFA_USART_TX_PIN GPIO_Pin_2
#define VOFA_USART_TX_AF GPIO_AF_USART2
#define VOFA_USART_TX_SOURCE GPIO_PinSource2

// RX口
#define VOFA_USART_RX_PORT GPIOA
#define VOFA_USART_RX_PIN GPIO_Pin_3
#define VOFA_USART_RX_AF GPIO_AF_USART2
#define VOFA_USART_RX_SOURCE GPIO_PinSource3

// TX_DMA时钟
#define VOFA_DMA_TX_AHBxClock_FUN RCC_AHB1PeriphClockCmd
#define VOFA_DMA_TX_CLK RCC_AHB1Periph_DMA1

// TX_DMA通道
#define VOFA_DMA_TX_STREAM DMA1_Stream6
#define VOFA_DMA_TX_CHANNEL DMA_Channel_4
#define VOFA_DMA_TX_IRQ DMA1_Stream6_IRQn
#define VOFA_DMA_TX_INT_FUN DMA1_Stream6_IRQHandler
#define VOFA_DMA_TX_FLAG_TCIF DMA_FLAG_TCIF6
#define VOFA_DMA_TX_IT_STATUS DMA_IT_TCIF6

// RX_DMA通道
#define VOFA_DMA_RX_STREAM DMA1_Stream5
#define VOFA_DMA_RX_CHANNEL DMA_Channel_4
#define VOFA_DMA_RX_IRQ DMA1_Stream5_IRQn
#define VOFA_DMA_RX_INT_FUN DMA1_Stream5_IRQHandler
#define VOFA_DMA_RX_FLAG_TCIF DMA_FLAG_TCIF5 // 传输完成标志位
#define VOFA_DMA_RX_IT_STATUS DMA_IT_TCIF5

/******************************** TOF(暂时) ***********************************/
#define HEADER 0xAA			   /* ÆðÊ¼·û */
#define device_address 0x00	   /* Éè±¸µØÖ· */
#define chunk_offset 0x00	   /* Æ«ÒÆµØÖ·ÃüÁî */
#define PACK_GET_DISTANCE 0x02 /* »ñÈ¡²âÁ¿Êý¾ÝÃüÁî */
#define PACK_RESET_SYSTEM 0x0D /* ¸´Î»ÃüÁî */
#define PACK_STOP 0x0F		   /* Í£Ö¹²âÁ¿Êý¾Ý´«ÊäÃüÁî */
#define PACK_ACK 0x10		   /* Ó¦´ðÂëÃüÁî */
#define PACK_VERSION 0x14	   /* »ñÈ¡´«¸ÐÆ÷ÐÅÏ¢ÃüÁî */

#define RECV_LEN 195

typedef struct
{
	int16_t distance;	/* ¾àÀëÊý¾Ý£º²âÁ¿Ä¿±ê¾àÀëµ¥Î» mm */
	uint16_t noise;		/* »·¾³ÔëÉù£ºµ±Ç°²âÁ¿»·¾³ÏÂµÄÍâ²¿»·¾³ÔëÉù£¬Ô½´óËµÃ÷ÔëÉùÔ½´ó */
	uint32_t peak;		/* ½ÓÊÕÇ¿¶ÈÐÅÏ¢£º²âÁ¿Ä¿±ê·´Éä»ØµÄ¹âÇ¿¶È */
	uint8_t confidence; /* ÖÃÐÅ¶È£ºÓÉ»·¾³ÔëÉùºÍ½ÓÊÕÇ¿¶ÈÐÅÏ¢ÈÚºÏºóµÄ²âÁ¿µãµÄ¿ÉÐÅ¶È */
	uint32_t intg;		/* »ý·Ö´ÎÊý£ºµ±Ç°´«¸ÐÆ÷²âÁ¿µÄ»ý·Ö´ÎÊý */
	int16_t reftof;		/* ÎÂ¶È±íÕ÷Öµ£º²âÁ¿Ð¾Æ¬ÄÚ²¿ÎÂ¶È±ä»¯±íÕ÷Öµ£¬Ö»ÊÇÒ»¸öÎÂ¶È±ä»¯Á¿ÎÞ·¨ÓëÕæÊµÎÂ¶È¶ÔÓ¦ */
} LidarPointTypedef;

struct AckResultData
{
	uint8_t ack_cmd_id; /* ´ð¸´µÄÃüÁî id */
	uint8_t result;		/* 1±íÊ¾³É¹¦,0±íÊ¾Ê§°Ü */
};

struct LiManuConfig
{
	uint32_t version;		   /* Èí¼þ°æ±¾ºÅ */
	uint32_t hardware_version; /* Ó²¼þ°æ±¾ºÅ */
	uint32_t manufacture_date; /* Éú²úÈÕÆÚ */
	uint32_t manufacture_time; /* Éú²úÊ±¼ä */
	uint32_t id1;			   /* Éè±¸ id1 */
	uint32_t id2;			   /* Éè±¸ id2 */
	uint32_t id3;			   /* Éè±¸ id3 */
	uint8_t sn[8];			   /* sn */
	uint16_t pitch_angle[4];   /* ½Ç¶ÈÐÅÏ¢ */
	uint16_t blind_area[2];	   /* Ã¤ÇøÐÅÏ¢ */
	uint32_t frequence;		   /* Êý¾ÝµãÆµ */
};

void VOFA_Configuration(void);
void VOFA_Send(void);

#endif
