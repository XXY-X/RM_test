/**********************************************************************************************************
 * @文件     usart4.c
 * @说明     uart初始化,VOFA
 * @版本  	 V1.0
 **********************************************************************************************************/
#include "main.h"

float VOFA_justfloat[VOFA_MAX_CHANNEL];
uint8_t VOFA_send_Data[VOFA_MAX_CHANNEL * 4 + 4];
uint8_t VOFA_recv_Data[RECV_LEN + 5] = {0};

/*
	@brief VOFA串口初始化
	@param none
	@return none
*/
void VOFA_Configuration(void)
{
	USART_InitTypeDef usart;
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;
	DMA_InitTypeDef dma;

	// 写入结尾数据
	VOFA_send_Data[VOFA_MAX_CHANNEL * 4] = 0x00;
	VOFA_send_Data[VOFA_MAX_CHANNEL * 4 + 1] = 0x00;
	VOFA_send_Data[VOFA_MAX_CHANNEL * 4 + 2] = 0x80;
	VOFA_send_Data[VOFA_MAX_CHANNEL * 4 + 3] = 0x7f;

	nvic.NVIC_IRQChannel = VOFA_DMA_TX_IRQ;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	nvic.NVIC_IRQChannel = VOFA_DMA_RX_IRQ;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	// USART
	VOFA_USART_GPIO_APBxClock_FUN(VOFA_USART_GPIO_CLK, ENABLE);
	VOFA_USART_APBxClock_FUN(VOFA_USART_CLK, ENABLE);

	GPIO_PinAFConfig(VOFA_USART_TX_PORT, VOFA_USART_TX_SOURCE, VOFA_USART_TX_AF);
	GPIO_PinAFConfig(VOFA_USART_RX_PORT, VOFA_USART_RX_SOURCE, VOFA_USART_RX_AF);

	gpio.GPIO_Pin = VOFA_USART_TX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(VOFA_USART_TX_PORT, &gpio);

	gpio.GPIO_Pin = VOFA_USART_RX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(VOFA_USART_RX_PORT, &gpio);

	usart.USART_BaudRate = VOFA_USART_BAUD_RATE;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(VOFA_USARTx, &usart);

	// USART_ITConfig(VOFA_USARTx,USART_IT_IDLE, ENABLE); //空闲中断，DMA接收///////////////////////////
	USART_Cmd(VOFA_USARTx, ENABLE);
	USART_DMACmd(VOFA_USARTx, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(VOFA_USARTx, USART_DMAReq_Rx, ENABLE);
	USART_ClearFlag(VOFA_USARTx, USART_FLAG_TC);

	// DMA
	{
		// TX
		VOFA_DMA_TX_AHBxClock_FUN(VOFA_DMA_TX_CLK, ENABLE);
		DMA_DeInit(VOFA_DMA_TX_STREAM);
		dma.DMA_Channel = VOFA_DMA_TX_CHANNEL;
		dma.DMA_PeripheralBaseAddr = (uint32_t) & (VOFA_USARTx->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)VOFA_send_Data;
		dma.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		dma.DMA_BufferSize = (VOFA_MAX_CHANNEL * 4 + 4);
		dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma.DMA_Mode = DMA_Mode_Normal;
		dma.DMA_Priority = DMA_Priority_VeryHigh;
		dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
		dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
		dma.DMA_MemoryBurst = DMA_Mode_Normal;
		dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(VOFA_DMA_TX_STREAM, &dma);
		DMA_ClearFlag(VOFA_DMA_TX_STREAM, VOFA_DMA_TX_FLAG_TCIF); // clear all DMA flags
		DMA_ITConfig(VOFA_DMA_TX_STREAM, DMA_IT_TC, ENABLE);	  // open DMA send inttrupt
		DMA_Cmd(VOFA_DMA_TX_STREAM, DISABLE);
		// RX
		DMA_DeInit(VOFA_DMA_RX_STREAM);
		dma.DMA_Channel = VOFA_DMA_RX_CHANNEL;
		dma.DMA_PeripheralBaseAddr = (uint32_t) & (VOFA_USARTx->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)VOFA_recv_Data;
		dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
		dma.DMA_BufferSize = (RECV_LEN);
		dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma.DMA_Mode = DMA_Mode_Circular;
		dma.DMA_Priority = DMA_Priority_Medium;
		dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
		dma.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
		dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(VOFA_DMA_RX_STREAM, &dma);
		DMA_ClearFlag(VOFA_DMA_RX_STREAM, VOFA_DMA_RX_FLAG_TCIF); // clear all DMA flags
		DMA_SetCurrDataCounter(VOFA_DMA_RX_STREAM, RECV_LEN);
		DMA_ITConfig(VOFA_DMA_RX_STREAM, DMA_IT_TC, ENABLE);
		DMA_Cmd(VOFA_DMA_RX_STREAM, ENABLE);
	}
}

void VOFA_DMA_TX_INT_FUN(void)
{
	if (DMA_GetITStatus(VOFA_DMA_TX_STREAM, VOFA_DMA_TX_IT_STATUS))
	{
		DMA_ClearITPendingBit(VOFA_DMA_TX_STREAM, VOFA_DMA_TX_IT_STATUS);
		DMA_Cmd(VOFA_DMA_TX_STREAM, DISABLE);
	}
}

// extern float target_roll;
// extern float output;
extern float len_dec;
extern float anti_tor[4];
void VOFA_Send(void)
{
	// 需转为float型数据存储

//	// state_vector
//	VOFA_justfloat[0] = (float)(infantry.state_vector[0]);
//	VOFA_justfloat[1] = (float)(infantry.state_vector[1]);
//	VOFA_justfloat[2] = (float)(infantry.state_vector[2]);
//	VOFA_justfloat[3] = (float)(infantry.state_vector[3]);
//	VOFA_justfloat[4] = (float)(infantry.state_vector[4]);
//	VOFA_justfloat[5] = (float)(infantry.state_vector[5]);

//	// Output
//	VOFA_justfloat[6] = (float)(infantry.excute_info.wheels_torque[LEFT_WHEEL_ID]);
//	VOFA_justfloat[7] = (float)(infantry.excute_info.wheels_torque[RIGHT_WHEEL_ID]);
//	VOFA_justfloat[8] = (float)(infantry.excute_info.knee_torque[LEFT_KNEE_LEFT]);
//	VOFA_justfloat[9] = (float)(infantry.excute_info.knee_torque[LEFT_KNEE_RIGHT]);
//	VOFA_justfloat[10] = (float)(infantry.excute_info.knee_torque[RIGHT_KNEE_LEFT]);
//	VOFA_justfloat[11] = (float)(infantry.excute_info.knee_torque[RIGHT_KNEE_RIGHT]);

//	// Leg_length
//	VOFA_justfloat[12] = (float)(infantry.L_left[0]);
//	VOFA_justfloat[13] = (float)(infantry.L_right[0]);
//	VOFA_justfloat[14] = (float)(infantry.target_L_left);
//	VOFA_justfloat[15] = (float)(infantry.target_L_right);
//	VOFA_justfloat[16] = (float)(infantry.extra_leg_force_l);
//	VOFA_justfloat[17] = (float)(infantry.extra_leg_force_r);

	//	VOFA_justfloat[18] = remote_controller.control_mode_action;
	//	VOFA_justfloat[19] = infantry.FN_l;
	//	VOFA_justfloat[20] = infantry.FN_r;

	// 压弯,压重心
	//	VOFA_justfloat[18] = (float)target_roll;
	//	VOFA_justfloat[19] = (float)output;
	//	VOFA_justfloat[20] = (float)(infantry.yaw_v);
	//	VOFA_justfloat[21] = (float)(len_dec);

	// 关节电机软限位
	//		VOFA_justfloat[18] = (float)anti_tor[0];
	//		VOFA_justfloat[19] = (float)anti_tor[1];
	//		VOFA_justfloat[20] = (float)anti_tor[2];
	//		VOFA_justfloat[21] = (float)anti_tor[3];

	// 打滑
	//	VOFA_justfloat[18] = (float)(infantry.slide_ck[LEFT_WHEEL_ID].a);
	//	VOFA_justfloat[19] = (float)(infantry.slide_ck[LEFT_WHEEL_ID].a_fore);
	//	VOFA_justfloat[20] = (float)(infantry.slide_ck[LEFT_WHEEL_ID].w_last);
	//	VOFA_justfloat[21] = (float)(infantry.slide_ck[LEFT_WHEEL_ID].tor_dec);
	//	VOFA_justfloat[22] = (float)(infantry.output_torque_l[0]);

	//   功控
	//		VOFA_justfloat[18] = (float)referee_data.Power_Heat_Data.buffer_energy;
	//		VOFA_justfloat[19] = (float)super_power.actual_vol;
	//		VOFA_justfloat[20] = (float)referee_data.Power_Heat_Data.chassis_power;
	//		VOFA_justfloat[21] = (float)buffer_energy.buffering_energy;
	//		VOFA_justfloat[22] = (float)super_power.power_limit_state;

	//		// 热量
	//		VOFA_justfloat[19] = (float)referee_data.Shoot_Data.bullet_freq;
	VOFA_justfloat[20] = (float)referee_data.Shoot_Data.bullet_speed;
	//  	VOFA_justfloat[21] = (float)referee_data.Power_Heat_Data.shooter_id1_17mm_cooling_heat;
	//   	VOFA_justfloat[22] = (float)referee_data.Game_Robot_State.shooter_barrel_heat_limit;

	// 将32位的浮点数转换为4个8位的整型
	memcpy(VOFA_send_Data, (uint8_t *)VOFA_justfloat, sizeof(VOFA_justfloat));
	VOFA_DMA_TX_STREAM->NDTR = VOFA_MAX_CHANNEL * 4 + 4;
	DMA_Cmd(VOFA_DMA_TX_STREAM, ENABLE);
}
