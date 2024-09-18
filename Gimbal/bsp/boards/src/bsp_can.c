#include "bsp_can.h"
#include "can_send_config.h"

/**********************************************************************************************************
 *�� �� ��: can_filter_init
 *����˵��: can����
 *��    ��: ��
 *�� �� ֵ: ��
 **********************************************************************************************************/
void can_filter_init(void)
{
	CAN_FilterTypeDef can_filter_st;
	// CAN 1 FIFO0 �����ж�
	can_filter_st.FilterBank = 0;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN1_FIFO0_ID0 << 5;
	can_filter_st.FilterIdLow = CAN1_FIFO0_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN1_FIFO0_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN1_FIFO0_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	// CAN 1 FIFO1 �����ж�
	can_filter_st.FilterBank = 1;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN1_FIFO1_ID0 << 5;
	can_filter_st.FilterIdLow = CAN1_FIFO1_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN1_FIFO1_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN1_FIFO1_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO1;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
	// CAN 2 FIFO0 �����ж�
	can_filter_st.FilterBank = 15;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN2_FIFO0_ID0 << 5;
	can_filter_st.FilterIdLow = CAN2_FIFO0_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN2_FIFO0_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN2_FIFO0_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	// CAN 2 FIFO1 �����ж�
	can_filter_st.FilterBank = 16;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN2_FIFO1_ID0 << 5;
	can_filter_st.FilterIdLow = CAN2_FIFO1_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN2_FIFO1_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN2_FIFO1_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO1;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);
	// CAN 1 �����ж�
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY);
	// CAN 2 �����ж�
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_TX_MAILBOX_EMPTY);
}

void MotorReceive(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef *rx_header, uint8_t *data)
{
	if (hcan->Instance == PITCH_MOTOR_CAN && rx_header->StdId == PITCH_MOTOR_CAN_ID)
	{
		// Pitch����
		gimbal_controller.pitch_recv.angle = (data[0] << 8) | (data[1]);
		gimbal_controller.pitch_recv.speed = (data[2] << 8) | (data[3]);
		gimbal_controller.pitch_recv.torque_current = (data[4] << 8) | (data[5]);
		gimbal_controller.pitch_recv.temp = data[6];

		LossUpdate(&global_debugger.gimbal_debugger[0], 0.0015f);
	}
	else if (hcan->Instance == FRICTION_WHEEL_CAN && rx_header->StdId == LEFT_FRICTION_WHEEL_CAN_ID)
	{
		// ��Ħ���ֽ���
		friction_wheels.friction_motor_recv[LEFT_FRICTION_WHEEL].angle = (data[0] << 8) | (data[1]);
		friction_wheels.friction_motor_recv[LEFT_FRICTION_WHEEL].speed = (data[2] << 8) | (data[3]);
		friction_wheels.friction_motor_recv[LEFT_FRICTION_WHEEL].torque_current = (data[4] << 8) | (data[5]);
		friction_wheels.friction_motor_recv[LEFT_FRICTION_WHEEL].temp = (data[6]);

		LossUpdate(&global_debugger.friction_debugger[LEFT_FRICTION_WHEEL], 0.0015f);
	}
	else if (hcan->Instance == FRICTION_WHEEL_CAN && rx_header->StdId == RIGHT_FRICTION_WHEEL_CAN_ID)
	{
		// ��Ħ���ֽ���
		friction_wheels.friction_motor_recv[RIGHT_FRICTION_WHEEL].angle = (data[0] << 8) | (data[1]);
		friction_wheels.friction_motor_recv[RIGHT_FRICTION_WHEEL].speed = (data[2] << 8) | (data[3]);
		friction_wheels.friction_motor_recv[RIGHT_FRICTION_WHEEL].torque_current = (data[4] << 8) | (data[5]);
		friction_wheels.friction_motor_recv[RIGHT_FRICTION_WHEEL].temp = (data[6]);

		LossUpdate(&global_debugger.friction_debugger[RIGHT_FRICTION_WHEEL], 0.0015f);
	}
	else if (hcan->Instance == YAW_MOTOR_CAN && rx_header->StdId == YAW_MOTOR_CAN_ID)
	{
		// 6020
		if (motor_communication[YAW_MOTOR].motor_type == GM6020)
		{
			gimbal_controller.yaw_recv.angle = (data[0] << 8) | (data[1]);
			gimbal_controller.yaw_recv.speed = (data[2] << 8) | (data[3]);
			gimbal_controller.yaw_recv.torque_current = (data[4] << 8) | (data[5]);
			gimbal_controller.yaw_recv.temp = data[6];
		}
		else if (motor_communication[YAW_MOTOR].motor_type == DM_MOTOR)
		{
			DM_Motor_Receive(data, &gimbal_controller.DM_Yaw_Motor);
		}

		LossUpdate(&global_debugger.gimbal_debugger[1], 0.0015f); // 1KHZ
	}
	else if (hcan->Instance == TOGGLE_MOTOR_CAN && rx_header->StdId == TOGGLE_MOTOR_CAN_ID)
	{
		// ����������ݽ���
		toggle_controller.toggle_recv.angle = (data[0] << 8) | (data[1]);
		toggle_controller.toggle_recv.speed = (data[2] << 8) | (data[3]);
		toggle_controller.toggle_recv.torque_current = (data[4] << 8) | (data[5]);

		LossUpdate(&global_debugger.toggle_debugger, 0.0015f);
	}
	else if (hcan->Instance == CHASSIS_CAN_COMM_CANx && rx_header->StdId == GET_FROM_CHASSIS_CAN_ID_1)
	{
		memcpy(&chassis_pack_get_1, data, 8);

		LossUpdate(&global_debugger.receive_chassis_debugger[0], 0.0055f);
	}
	else if (hcan->Instance == CHASSIS_CAN_COMM_CANx && rx_header->StdId == GET_FROM_CHASSIS_CAN_ID_2)
	{
		memcpy(&chassis_pack_get_2, data, 8);
		LossUpdate(&global_debugger.receive_chassis_debugger[1], 0.0055f);
	}
}

/**********************************************************************************************************
 *�� �� ��: HAL_CAN_RxFifo0MsgPendingCallback
 *����˵��:FIFO 0�����жϻص�����
 *��    ��:
 *�� �� ֵ: ��
 **********************************************************************************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
	__HAL_CAN_CLEAR_FLAG(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	MotorReceive(hcan, &rx_header, rx_data);
}
/**********************************************************************************************************
 *�� �� ��: HAL_CAN_RxFifo1MsgPendingCallback
 *����˵��:FIFO 1�����жϻص�����
 *��    ��:
 *�� �� ֵ: ��
 **********************************************************************************************************/
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) // FIFO 1�����жϻص�����
{
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &rx_header, rx_data);
	__HAL_CAN_CLEAR_FLAG(hcan, CAN_IT_RX_FIFO1_MSG_PENDING);

	MotorReceive(hcan, &rx_header, rx_data);
}

int8_t CanSend(CAN_HandleTypeDef *hcan, int8_t *data, uint32_t std_id, CAN_TxHeaderTypeDef *Motor_Send, uint32_t *wait_time)
{
	float dwt_start = DWT_GetTimeline_us();
	while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0) // �ȴ��������
	{
		if (DWT_GetTimeline_us() - dwt_start > 200) // ��ʱ200us
		{
			global_debugger.can_send_wait++;
			return FALSE;
		}
	}
	*wait_time = DWT_GetTimeline_us() - dwt_start;

	uint32_t send_mail_box;
	Motor_Send->StdId = std_id;
	Motor_Send->IDE = CAN_ID_STD;
	Motor_Send->RTR = CAN_RTR_DATA;
	Motor_Send->DLC = 0x08;
	if (HAL_CAN_AddTxMessage(hcan, Motor_Send, data, &send_mail_box))
	{
		global_debugger.can_send_wait++;
		return FALSE;
	}

	return TRUE;
}
