/**
 ******************************************************************************
 * @file    RefereeTask.c
 * @brief   ??????????????λ????????,?????????????
 ******************************************************************************
 * @attention
 ******************************************************************************
 */
#include "RefereeTask.h"

#define Robot_ID_Current Robot_ID_Blue_Infantry4

/* ??????????? */
uint16_t y01 = 455;
uint16_t y02 = 420;
uint16_t y03 = 280;
uint16_t y04 = 230;

uint16_t camera_view_y1 = 100;
uint16_t camera_view_y2 = 860;
uint16_t camera_view_x1 = 320;
uint16_t camera_view_x2 = 1600;

// ?????????????
#define LEG_PLACE_BIAS_X 1630
#define LEG_PLACE_BIAS_Y 644
#define LEG_RATIO 400 // ???????????????????

// ????????н????
#define GIM_CHASSIS_ANGLE_LINE_LEN 70

/**
 * @brief ??ν??????????(????????????)
 * @param[in] void
 */
void Refereetask(void *pvParameters)
{
	portTickType xLastWakeTime;
//	uint16_t UI_PushUp_Counter = 261;

//	static char chassis_state[9][8] = {"OFFLINE", "SHRINK", "RECOVER", "BALANCE", "FOLLOW", "ROTATE", "JUMP", "LAND", "BESIDES"};
//	static char gimbal_state[7][8] = {"OFFLINE", "ACT", "AUTOAIM", "TEST", "SI", "SMA_BUFF", "BIG_BUFF"};

//	int8_t is_fric_offline = 0, is_pc_offline = 0, is_map_offline;
//	uint16_t UI_PushUp_Counter_500;
//	uint16_t UI_PushUp_Counter_20;
//	uint8_t draw_cnt;
//	uint8_t brake_line_draw_cnt; // 刹车线绘制

	while (1)
	{
		Referee_UnpackFifoData();

//		/* UI???? */
//		UI_PushUp_Counter++;
//		UI_PushUp_Counter_500 = UI_PushUp_Counter % 500;
//		UI_PushUp_Counter_20 = UI_PushUp_Counter % 20;

//		// ???UI????(?????)
//		if (UI_PushUp_Counter_500 == 37) // ??????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "001", UI_Graph_Add, 2, UI_Color_Green, 15, 8, 3, 1600, 800, "  FRIC ");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 107) // PC?????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "002", UI_Graph_Add, 2, UI_Color_Green, 15, 8, 3, 1600, 830, "  PC   ");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 157) // ??????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "003", UI_Graph_Add, 2, UI_Color_Green, 15, 8, 3, 1600, 860, "  BAY  ");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 211) // ???????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "100", UI_Graph_Add, 2, UI_Color_Orange, 60, 8, 3, 950, 745, chassis_state[remote_controller.control_mode_action]);
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 263) // ??????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "101", UI_Graph_Add, 2, UI_Color_Purple, 15, 8, 3, 300, 765, gimbal_state[remote_controller.gimbal_action]);
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 293) // ????ID?????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "102", UI_Graph_Add, 2, UI_Color_Green, 15, 8, 3, 600, 880, "ID:   ");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 331) // ?????????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "200", UI_Graph_Add, 2, UI_Color_Green, 15, 10, 3, 1600, 770, "CAP:    %");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 383) // PITCH?????????
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "201", UI_Graph_Add, 2, UI_Color_Green, 15, 8, 3, 1280, 800, "PITCH: ");
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 439) // ???UI??????pitch????????????,?????????ID
//		{
//			// pitch???
//			UI_Draw_Float(&referee_data.UI_Graph7.Graphic[0], "300", UI_Graph_Add, 3, UI_Color_Pink, 15, 2, 4, 1380, 800, gimbal_receiver_pack2.gimbal_pitch / 100.0f); // Pith????

//			// ???????
//			UI_Draw_Float(&referee_data.UI_Graph7.Graphic[1], "301", UI_Graph_Add, 3, UI_Color_Pink, 15, 2, 4, 1655, 770, super_power.actual_vol * 4.3478f);

//			// ?????????
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[2], "302", UI_Graph_Add, 3, UI_Color_Orange, 5, 1620, 790, 1690, 790);

//			// ?????????
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[3], "303", UI_Graph_Add, 3, UI_Color_Orange, 5, 1620, 850, 1690, 850);

//			// PC????
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[4], "304", UI_Graph_Add, 3, UI_Color_Orange, 5, 1620, 820, 1690, 820);

//			// ????ID???
//			UI_Draw_Int(&referee_data.UI_Graph7.Graphic[5], "305", UI_Graph_Add, 3, UI_Color_Cyan, 20, 2, 640, 880, 0);

//			// ???????????н???
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[6], "306", UI_Graph_Add, 3, UI_Color_Orange, 5, 1620, 400, 1690, 400);

//			UI_PushUp_Graphs(7, &referee_data.UI_Graph7, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_500 == 499) // ???????
//		{
//			drawFiveLeg(&referee_data.UI_Graph5, UI_Graph_Add);

//			UI_PushUp_Graphs(5, &referee_data.UI_Graph5, referee_data.Game_Robot_State.robot_id);
//		}
//		if (UI_PushUp_Counter_20 == 7)
//		{
//			drawFiveLeg(&referee_data.UI_Graph5, UI_Graph_Change);

//			UI_PushUp_Graphs(5, &referee_data.UI_Graph5, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_20 == 16)
//		{
//			UI_Draw_String(&referee_data.UI_String.String, "100", UI_Graph_Change, 2, UI_Color_Green, 30, 8, 3, 850, 820, chassis_state[remote_controller.control_mode_action]);
//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		}
//		//		else if (UI_PushUp_Counter_20 == 19)
//		//		{
//		//			UI_Draw_String(&referee_data.UI_String.String, "101", UI_Graph_Change, 2, UI_Color_Purple, 15, 8, 3, 300, 765, gimbal_state[remote_controller.control_mode_action]);
//		//			UI_PushUp_String(&referee_data.UI_String, referee_data.Game_Robot_State.robot_id);
//		//		}
//		else if (UI_PushUp_Counter_20 == 5)
//		{
//			if (draw_cnt == 5)
//			{
//				UI_Draw_Line(&referee_data.UI_Graph2.Graphic[0], "010", UI_Graph_Add, 3, UI_Color_White, 3, 588, 0, 801, 395);
//				UI_Draw_Line(&referee_data.UI_Graph2.Graphic[1], "011", UI_Graph_Add, 3, UI_Color_White, 3, 1359, 0, 1169, 395);
//				draw_cnt = 0;
//			}
//			else
//				draw_cnt++;
//			UI_PushUp_Graphs(2, &referee_data.UI_Graph2, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_20 == 12)
//		{
//			if (brake_line_draw_cnt == 5)
//			{
//				UI_Draw_Line(&referee_data.UI_Graph2.Graphic[0], "015", UI_Graph_Add, 3, UI_Color_White, 3, 820, 310, 1100, 310); // 加速到最大距离，不刹车的安全缓冲长度
//				UI_Draw_Line(&referee_data.UI_Graph2.Graphic[1], "016", UI_Graph_Add, 3, UI_Color_White, 6, 745, 215, 1175, 215);
//				brake_line_draw_cnt = 0;
//			}
//			else
//				brake_line_draw_cnt++;
//			UI_PushUp_Graphs(2, &referee_data.UI_Graph2, referee_data.Game_Robot_State.robot_id);
//		}
//		else if (UI_PushUp_Counter_20 == 0) // ???UI???? ???
//		{
//			// pitch???
//			UI_Draw_Float(&referee_data.UI_Graph7.Graphic[0], "300", UI_Graph_Change, 3, UI_Color_Pink, 15, 2, 4, 1380, 800, gimbal_receiver_pack2.gimbal_pitch / 100.0f); // Pith????

//			/* ???????? */
//			UI_Draw_Float(&referee_data.UI_Graph7.Graphic[1], "301", UI_Graph_Change, 3, UI_Color_Pink, 15, 2, 4, 1655, 770, super_power.actual_vol * 4.3478f);

//			// ?????????,??????????????????
//			is_fric_offline = remote_controller.shoot_action == SHOOT_POWERDOWN_MODE || remote_controller.shoot_action == SHOOT_SUPPLY_MODE;
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[2], "302", UI_Graph_Change, 3, UI_Color_Green + is_fric_offline, 5, 1620, 790, 1690, 790);

//			// ?????????????????????????
//			//			is_map_offline = (remote_controller.shoot_action == SHOOT_SUPPLY_MODE || remote_controller.shoot_action == SHOOT_TEST_MODE) ? 0 : 1;
//			//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[3], "303", UI_Graph_Change, 3, UI_Color_Green + is_map_offline, 5, 1620, 850, 1690, 850);
//			is_map_offline = remote_controller.cover_state ? 0 : 1;
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[3], "303", UI_Graph_Change, 3, UI_Color_Green + is_map_offline, 5, 1620, 850, 1690, 850);

//			// PC????
//			is_pc_offline = !gimbal_receiver_pack1.is_pc_on;
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[4], "304", UI_Graph_Change, 3, UI_Color_Green + is_pc_offline, 5, 1620, 820, 1690, 820);

//			// ????ID???
//			UI_Draw_Int(&referee_data.UI_Graph7.Graphic[5], "305", UI_Graph_Change, 3, UI_Color_Cyan, 20, 2, 640, 880, gimbal_receiver_pack1.autoaim_id);

//			//  ??????????н?
//			UI_Draw_Line(&referee_data.UI_Graph7.Graphic[6], "306", UI_Graph_Change, 3, UI_Color_Orange, 5, 1620, 400, (uint16_t)(1620 - (int16_t)(GIM_CHASSIS_ANGLE_LINE_LEN * infantry.sin_dir)), (uint16_t)(400 + (int16_t)(GIM_CHASSIS_ANGLE_LINE_LEN * infantry.cos_dir)));

//			UI_PushUp_Graphs(7, &referee_data.UI_Graph7, referee_data.Game_Robot_State.robot_id);
//		}

		xEventGroupSetBits(xCreatedEventGroup, REFEREE_TASK_BIT); // 标志位置一

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
	}
}
