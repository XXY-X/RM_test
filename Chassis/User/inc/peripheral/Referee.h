/**
 ******************************************************************************
 * @file    referee.h
 * @author  Karolance Future
 * @version V1.3.0
 * @date    2022/03/21
 * @brief   Header file of referee.c
 ******************************************************************************
 * @attention
 *
 *   娓氭繃宓佺憗浣稿灲缁崵绮� 娑撴彃褰涢崡蹇氼唴闂勫嫬缍� V1.3
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __REFEREE_H__
#define __REFEREE_H__

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "protocol.h"
#include "algorithmOfCRC.h"
#include "debug.h"
#include "counter.h"

#include "HeatControl.h"
/*
裁判系统
*/
/* Referee Defines -----------------------------------------------------------*/
/* 濮ｆ棁绂岀猾璇茬€� */
#define Game_Type_RMUC 1	 // 鐡掑懐楠囩€佃濮夌挧锟�
#define Game_Type_RMUT 2	 // 閸楁洟銆嶇挧锟�
#define Game_Type_RMUA 3	 // 娴滃搫浼愰弲楦垮厴閹告垶鍨挧锟�
#define Game_Type_RMUL_3V3 4 // 妤傛ɑ鐗庨懕鏃傛礃鐠э拷3V3
#define Game_Type_RMUL_1V1 5 // 妤傛ɑ鐗庨懕鏃傛礃鐠э拷1V1

/* 濮ｆ棁绂岄梼鑸殿唽 */
#define Game_Progress_Unstart 0	  // 閺堫亜绱戞慨瀣槷鐠э拷
#define Game_Progress_Prepare 1	  // 閸戝棗顦梼鑸殿唽
#define Game_Progress_SelfCheck 2 // 閼奉亝顥呴梼鑸殿唽
#define Game_Progress_5sCount 3	  // 5s閸婃帟顓搁弮锟�
#define Game_Progress_Battle 4	  // 鐎佃鍨稉锟�
#define Game_Progress_Calculate 5 // 濮ｆ棁绂岀紒鎾剁暬娑擄拷

/* 濮ｆ棁绂岀紒鎾寸亯 */
#define Game_Result_Draw 0	  // 楠炲啿鐪�
#define Game_Result_RedWin 1  // 缁俱垺鏌熼懗婊冨焺
#define Game_Result_BlueWin 2 // 閽冩繃鏌熼懗婊冨焺

/* 鐠€锕€鎲℃穱鈩冧紖 */
#define Warning_Yellow 1  // 姒涘嫮澧濈拃锕€鎲�
#define Warning_Red 2	  // 缁俱垻澧濈拃锕€鎲�
#define Warning_Failure 3 // 閸掋倛绀�

/* 閺堝搫娅掓禍绡扗 */
#define Robot_ID_Red_Hero 1			// 缁俱垺鏌熼懟閬嶆碂
#define Robot_ID_Red_Engineer 2		// 缁俱垺鏌熷銉р柤
#define Robot_ID_Red_Infantry3 3	// 缁俱垺鏌熷銉ュ徍3
#define Robot_ID_Red_Infantry4 4	// 缁俱垺鏌熷銉ュ徍4
#define Robot_ID_Red_Infantry5 5	// 缁俱垺鏌熷銉ュ徍5
#define Robot_ID_Red_Aerial 6		// 缁俱垺鏌熼弮鐘辨眽閺堬拷
#define Robot_ID_Red_Sentry 7		// 缁俱垺鏌熼崫銊ュ徍
#define Robot_ID_Red_Darts 8		// 缁俱垺鏌熸鐐烘櫦
#define Robot_ID_Red_Radar 9		// 缁俱垺鏌熼梿鐤彧
#define Robot_ID_Blue_Hero 101		// 閽冩繃鏌熼懟閬嶆碂
#define Robot_ID_Blue_Engineer 102	// 閽冩繃鏌熷銉р柤
#define Robot_ID_Blue_Infantry3 103 // 閽冩繃鏌熷銉ュ徍3
#define Robot_ID_Blue_Infantry4 104 // 閽冩繃鏌熷銉ュ徍4
#define Robot_ID_Blue_Infantry5 105 // 閽冩繃鏌熷銉ュ徍5
#define Robot_ID_Blue_Aerial 106	// 閽冩繃鏌熼弮鐘辨眽閺堬拷
#define Robot_ID_Blue_Sentry 107	// 閽冩繃鏌熼崫銊ュ徍
#define Robot_ID_Blue_Darts 108		// 閽冩繃鏌熸鐐烘櫦
#define Robot_ID_Blue_Radar 109		// 閽冩繃鏌熼梿鐤彧

/* 閺堝搫娅掓禍铏圭搼缁撅拷 */
#define Robot_Level_1 1 // 1缁撅拷
#define Robot_Level_2 2 // 2缁撅拷
#define Robot_Level_3 3 // 3缁撅拷

/* 閹碉綀顢呯猾璇茬€� */
#define Hurt_Type_ArmoredPlate 0	 // 鐟佸懐鏁抽弶澶告縺鐎癸拷
#define Hurt_Type_ModuleOffline 1	 // 濡€虫健缁傝崵鍤�
#define Hurt_Type_OverShootSpeed 2	 // 閺嬵亜褰涚搾鍛殸闁拷
#define Hurt_Type_OverShootHeat 3	 // 閺嬵亞顓哥搾鍛劰闁诧拷
#define Hurt_Type_OverChassisPower 4 // 鎼存洜娲忕搾鍛閻滐拷
#define Hurt_Type_Collision 5		 // 鐟佸懐鏁抽幘鐐插毊

/* 閸欐垵鐨犻張鐑樼€紓鏍у娇 */
#define Shooter_ID1_17mm 1 // 1閸欙拷17mm閸欐垵鐨犻張鐑樼€�
#define Shooter_ID2_17mm 2 // 2閸欙拷17mm閸欐垵鐨犻張鐑樼€�
#define Shooter_ID1_42mm 3 // 1閸欙拷42mm閸欐垵鐨犻張鐑樼€�

/* 妞嬬偤鏅兼穱鈩冧紖 */
#define Dart_State_Open 0	  // 妞嬬偤鏅奸梻鎼佹，瀵偓閸氾拷
#define Dart_State_Close 1	  // 妞嬬偤鏅奸梻鎼佹，閸忔娊妫�
#define Dart_State_Changing 2 // 濮濓絽婀鈧崥顖涘灗閼板懎鍙ч梻顓濊厬
#define Dart_Target_Outpost 0 // 妞嬬偤鏅奸惄顔界垼娑撳搫澧犻崫銊х彲
#define Dart_Target_Base 1	  // 妞嬬偤鏅奸惄顔界垼娑撳搫鐔€閸︼拷

/* 閹垮秳缍旈幍濠璂 */
#define Cilent_ID_Red_Hero 0x0101		// 缁俱垺鏌熼懟閬嶆碂閹垮秳缍旈幍锟�
#define Cilent_ID_Red_Engineer 0x0102	// 缁俱垺鏌熷銉р柤閹垮秳缍旈幍锟�
#define Cilent_ID_Red_Infantry3 0x0103	// 缁俱垺鏌熷銉ュ徍3閹垮秳缍旈幍锟�
#define Cilent_ID_Red_Infantry4 0x0104	// 缁俱垺鏌熷銉ュ徍4閹垮秳缍旈幍锟�
#define Cilent_ID_Red_Infantry5 0x0105	// 缁俱垺鏌熷銉ュ徍5閹垮秳缍旈幍锟�
#define Cilent_ID_Red_Aerial 0x0106		// 缁俱垺鏌熸鐐村
#define Cilent_ID_Blue_Hero 0x0165		// 閽冩繃鏌熼懟閬嶆碂閹垮秳缍旈幍锟�
#define Cilent_ID_Blue_Engineer 0x0166	// 閽冩繃鏌熷銉р柤閹垮秳缍旈幍锟�
#define Cilent_ID_Blue_Infantry3 0x0167 // 閽冩繃鏌熷銉ュ徍3閹垮秳缍旈幍锟�
#define Cilent_ID_Blue_Infantry4 0x0168 // 閽冩繃鏌熷銉ュ徍4閹垮秳缍旈幍锟�
#define Cilent_ID_Blue_Infantry5 0x0169 // 閽冩繃鏌熷銉ュ徍5閹垮秳缍旈幍锟�
#define Cilent_ID_Blue_Aerial 0x016A	// 閽冩繃鏌熸鐐村

/* UI缂佹ê鍩楅崘鍛啇cmdID */
#define UI_DataID_Delete 0x100	 // 鐎广垺鍩涚粩顖氬灩闂勩倕娴樿ぐ锟�
#define UI_DataID_Draw1 0x101	 // 鐎广垺鍩涚粩顖滅帛閸掞拷1娑擃亜娴樿ぐ锟�
#define UI_DataID_Draw2 0x102	 // 鐎广垺鍩涚粩顖滅帛閸掞拷2娑擃亜娴樿ぐ锟�
#define UI_DataID_Draw5 0x103	 // 鐎广垺鍩涚粩顖滅帛閸掞拷5娑擃亜娴樿ぐ锟�
#define UI_DataID_Draw7 0x104	 // 鐎广垺鍩涚粩顖滅帛閸掞拷7娑擃亜娴樿ぐ锟�
#define UI_DataID_DrawChar 0x110 // 鐎广垺鍩涚粩顖滅帛閸掕泛鐡х粭锕€娴樿ぐ锟�

/* UI閸掔娀娅庨幙宥勭稊 */
#define UI_Delete_Invalid 0 // 缁岀儤鎼锋担锟�
#define UI_Delete_Layer 1	// 閸掔娀娅庨崶鎯х湴
#define UI_Delete_All 2		// 閸掔娀娅庨幍鈧張锟�

/* UI閸ユ儳鑸伴幙宥勭稊 */
#define UI_Graph_invalid 0 // 缁岀儤鎼锋担锟�
#define UI_Graph_Add 1	   // 婢х偛濮為崶鎯ц埌
#define UI_Graph_Change 2  // 娣囶喗鏁奸崶鎯ц埌
#define UI_Graph_Delete 3  // 閸掔娀娅庨崶鎯ц埌

/* UI閸ユ儳鑸扮猾璇茬€� */
#define UI_Graph_Line 0		 // 閻╁鍤�
#define UI_Graph_Rectangle 1 // 閻晛鑸�
#define UI_Graph_Circle 2	 // 閺佹潙娓�
#define UI_Graph_Ellipse 3	 // 濡烆厼娓�
#define UI_Graph_Arc 4		 // 閸﹀棗濮�
#define UI_Graph_Float 5	 // 濞搭喚鍋ｉ崹锟�
#define UI_Graph_Int 6		 // 閺佹潙鑸�
#define UI_Graph_String 7	 // 鐎涙顑侀崹锟�

/* UI閸ユ儳鑸版０婊嗗 */
#define UI_Color_Main 0	  // 缁俱垼鎽戞稉鏄忓
#define UI_Color_Yellow 1 // 姒涘嫯澹�
#define UI_Color_Green 2  // 缂佽儻澹�
#define UI_Color_Orange 3 // 濮楁瑨澹�
#define UI_Color_Purple 4 // 缁鳖偉澹�
#define UI_Color_Pink 5	  // 缁澹�
#define UI_Color_Cyan 6	  // 闂堟帟澹�
#define UI_Color_Black 7  // 姒涙垼澹�
#define UI_Color_White 8  // 閻у€熷

#pragma pack(push, 1)

/* 0x000X --------------------------------------------------------------------*/
typedef struct // 0x0001 濮ｆ棁绂岄悩鑸碘偓浣规殶閹癸拷
{
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
	uint64_t SyncTimeStamp;
} ext_game_status_t;

typedef struct // 0x0002 濮ｆ棁绂岀紒鎾寸亯閺佺増宓�
{
	uint8_t winner;
} ext_game_result_t;

typedef struct // 0x0003 閺堝搫娅掓禍楦款攨闁插繑鏆熼幑锟�
{
	uint16_t red_1_robot_HP;
	uint16_t red_2_robot_HP;
	uint16_t red_3_robot_HP;
	uint16_t red_4_robot_HP;
	uint16_t red_5_robot_HP;
	uint16_t red_7_robot_HP;
	uint16_t red_base_HP;
	uint16_t blue_1_robot_HP;
	uint16_t blue_2_robot_HP;
	uint16_t blue_3_robot_HP;
	uint16_t blue_4_robot_HP;
	uint16_t blue_5_robot_HP;
	uint16_t blue_7_robot_HP;
	uint16_t blue_base_HP;
} ext_game_robot_HP_t;

/* 0x010X --------------------------------------------------------------------*/
typedef struct // 0x0101 閸﹀搫婀存禍瀣╂閺佺増宓�
{
	// uint32_t event_type;
	uint8_t self_supply_status : 3;
	uint8_t self_Buff_status : 3;
	uint8_t self_highland_status : 6;
	uint8_t self_BaseShield : 7;
	uint16_t last_dart_time : 9;
	uint8_t dart_target : 2;
	uint8_t gain_point_statuss : 2;
	// uint8_t _ : 3;
} ext_event_data_t;

typedef struct // 0x0102 鐞涖儳绮扮粩娆忓З娴ｆ粍鐖ｇ拠锟�
{
	uint8_t reserved;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;

typedef struct // 0x0103 鐠囬攱鐪扮悰銉х舶缁旀瑨藟瀵鏆熼幑顕嗙礉閻㈠崬寮挧娑㈡Е閸欐垿鈧緤绱橰M 鐎佃濮夌挧娑樼毣閺堫亜绱戦弨鎾呯礆
{
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_num;
} ext_supply_projectile_booking_t;

typedef struct // 0x0104 鐟佷礁鍨界拃锕€鎲℃穱鈩冧紖
{
	uint8_t level;
	uint8_t foul_robot_id;
	uint8_t count;
} ext_referee_warning_t;

typedef struct // 0x0105 妞嬬偤鏅奸崣鎴濈殸閸欙絽鈧帟顓搁弮锟�
{
	uint8_t dart_remaining_time;
	uint16_t dart_info;
} ext_dart_remaining_time_t;

/* 0x020X --------------------------------------------------------------------*/
typedef struct // 0x0201 濮ｆ棁绂岄張鍝勬珤娴滆櫣濮搁幀锟�
{
	uint8_t robot_id;
	uint8_t robot_level;
	uint16_t remain_HP;
	uint16_t max_HP;
	uint16_t shooter_barrel_cooling_value;
	uint16_t shooter_barrel_heat_limit;
	uint16_t chassis_power_limit;
	uint8_t mains_power_gimbal_output : 1;
	uint8_t mains_power_chassis_output : 1;
	uint8_t mains_power_shooter_output : 1;
} ext_game_robot_state_t;

typedef struct // 0x0202 鐎圭偞妞傞崝鐔哄芳閻戭參鍣洪弫鐗堝祦
{
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t buffer_energy;
	uint16_t shooter_id1_17mm_cooling_heat;
	uint16_t shooter_id2_17mm_cooling_heat;
	uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;

typedef struct // 0x0203 閺堝搫娅掓禍杞扮秴缂冿拷
{
	float x;
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;

typedef struct // 0x0204 閺堝搫娅掓禍鍝勵杻閻╋拷
{
	uint8_t recovery_buff;
	uint8_t cooling_buff;
	uint8_t defence_buff;
	uint8_t vulnerability_buff;
	uint16_t attack_buff;
} ext_buff_musk_t;

typedef struct // 0x205 閿熸枻鎷烽敓鍙紮鎷烽敓鏂ゆ嫹閿熸枻鎷风姸鎬�
{
	uint8_t airforce_status;
	uint8_t time_remain;
} air_support_data_t;

typedef struct // 0x0206 娴笺倕顔婇悩鑸碘偓锟�
{
	uint8_t armor_type : 4;
	uint8_t hurt_type : 4;
} ext_robot_hurt_t;

typedef struct // 0x0207 鐎圭偞妞傜亸鍕毊娣団剝浼�
{
	uint8_t bullet_type;
	uint8_t shooter_id;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;

typedef struct // 0x0208 鐎涙劕鑴婇崜鈺€缍戦崣鎴濈殸閺侊拷
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm;
	uint16_t coin_remaining_num;
} ext_bullet_remaining_t;

// typedef struct // 0x0209 閺堝搫娅掓禍绡烣ID閻樿埖鈧拷
// {
// 	uint32_t rfid_status;
// } ext_rfid_status_t;

// typedef struct // 0x020A 妞嬬偤鏅奸張鍝勬珤娴滃搫顓归幋椋庮伂閹稿洣鎶ら弫鐗堝祦
// {
// 	uint8_t dart_launch_opening_status;
// 	uint8_t dart_attack_target;
// 	uint16_t target_change_time;
// 	uint16_t operate_launch_cmd_time;
// } ext_dart_client_cmd_t;

typedef struct // 0x20B 閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷蜂綅閿熸枻鎷�
{
	float hero_x;
	float hero_y;
	float engineer_x;
	float engineer_y;
	float standard_3_x;
	float standard_3_y;
	float standard_4_x;
	float standard_4_y;
	float standard_5_x;
	float standard_5_y;
} ground_robot_position_t;

typedef struct // 0x20D
{
	uint16_t Sentry_convert_bullet : 11;
	uint8_t Sentry_convert_bullet_sum : 4;
	uint8_t Sentry_convert_blood_sum : 4;
	uint16_t _ : 13;
} sentry_info_t;

typedef struct
{
	uint8_t radar_double_hurt_chance : 2;
	uint8_t radar_if_double_hurt : 1;
	uint8_t _ : 5;
} radar_info_t;

/* 0x030X --------------------------------------------------------------------*/
typedef struct // 0x0301 閺堝搫娅掓禍娲？闁矮淇� 婢跺绮ㄩ弸鍕秼
{
	uint16_t data_cmd_id;
	uint16_t sender_ID;
	uint16_t receiver_ID;
	// uint8_t *data;
} ext_student_interactive_header_data_t;

typedef struct // 0x0301 閺堝搫娅掓禍娲？闁矮淇� 閺佺増宓佺紒鎾寸€担锟�
{
	uint8_t *data;
} robot_interactive_data_t;

typedef struct // 0x0303 鐏忓繐婀撮崶鍙ョ瑓閸欐垳淇婇幁顖涚垼鐠囷拷
{
	float target_position_x;
	float target_position_y;
	float target_position_z;
	uint8_t commd_keyboard;
	uint16_t target_robot_ID;
} ext_robot_command_t;

typedef struct // 0x0305 鐏忓繐婀撮崶鐐复閺€鏈典繆閹垱鐖ｇ拠锟�
{
	uint16_t target_robot_ID;
	float target_position_x;
	float target_position_y;
} ext_client_map_command_t;

typedef struct
{
	uint8_t is_game_start : 1;
	uint8_t Heat_update : 1;
	uint8_t Robot_Red_Blue : 1;			// 1 -> red ; 0 -> blue
	uint8_t Enemy_Sentry_shootable : 1; // 閿熷彨鍑ゆ嫹閿熻妭鎲嬫嫹閿熻鍑ゆ嫹閿熺潾纰夋嫹
	uint16_t self_outpost : 11;
	uint8_t Sentry_HomeReturned_flag : 1;
	uint16_t shooter1_heat;
	uint16_t bullet_remaining_num_17mm; // 0x208
	uint16_t stage_remain_time;			// 0x0001
} JudgeData_ForSend1_t;

typedef struct
{
	uint16_t x; // 閿熸枻鎷烽敓鏂ゆ嫹绯荤粺閿熸枻鎷烽敓渚ヤ紮鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�(閿熸枻鎷穎loat 鏄犻敓鎴掑埌 uint16_t : float*100 -> uint16_t)
	uint16_t y;
	uint8_t commd_keyboard; // 閿熸枻鎷峰彴閿熸枻鎷锋寚閿熸枻鎷�
	uint8_t Base_Shield;
	uint8_t KeyBoard_Update : 1;
	uint8_t _ : 7;
	uint8_t __;
} JudgeData_ForSend2_t;

/* 閼奉亜鐣炬稊澶岀帛閸掔ΚI缂佹挻鐎担锟� -------------------------------------------------------*/
typedef struct // 缂佹ê鍩桿I UI閸ユ儳鑸伴弫鐗堝祦
{
	uint8_t graphic_name[3];
	uint32_t operate_tpye : 3;
	uint32_t graphic_tpye : 3;
	uint32_t layer : 4;
	uint32_t color : 4;
	uint32_t start_angle : 9;
	uint32_t end_angle : 9;
	uint32_t width : 10;
	uint32_t start_x : 11;
	uint32_t start_y : 11;
	uint32_t radius : 10;
	uint32_t end_x : 11;
	uint32_t end_y : 11;
} graphic_data_struct_t;

typedef struct // 缂佹ê鍩桿I UI鐎涙顑佹稉鍙夋殶閹癸拷
{
	uint8_t string_name[3];
	uint32_t operate_tpye : 3;
	uint32_t graphic_tpye : 3;
	uint32_t layer : 4;
	uint32_t color : 4;
	uint32_t start_angle : 9;
	uint32_t end_angle : 9;
	uint32_t width : 10;
	uint32_t start_x : 11;
	uint32_t start_y : 11;
	uint32_t null;
	uint8_t stringdata[30];
} string_data_struct_t;

typedef struct // 缂佹ê鍩桿I UI閸掔娀娅庨崶鎯ц埌閺佺増宓�
{
	uint8_t operate_tpye;
	uint8_t layer;
} delete_data_struct_t;

typedef struct // 缂佹ê鍩桿I 缂佹ê鍩�1娑擃亜娴樿ぐ銏犵暚閺佸绮ㄩ弸鍕秼
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	graphic_data_struct_t Graphic[1];
	uint16_t CRC16;
} UI_Graph1_t;

typedef struct // 缂佹ê鍩桿I 缂佹ê鍩�2娑擃亜娴樿ぐ銏犵暚閺佸绮ㄩ弸鍕秼
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	graphic_data_struct_t Graphic[2];
	uint16_t CRC16;
} UI_Graph2_t;

typedef struct // 缂佹ê鍩桿I 缂佹ê鍩�5娑擃亜娴樿ぐ銏犵暚閺佸绮ㄩ弸鍕秼
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	graphic_data_struct_t Graphic[5];
	uint16_t CRC16;
} UI_Graph5_t;

typedef struct // 缂佹ê鍩桿I 缂佹ê鍩�7娑擃亜娴樿ぐ銏犵暚閺佸绮ㄩ弸鍕秼
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	graphic_data_struct_t Graphic[7];
	uint16_t CRC16;
} UI_Graph7_t;

typedef struct // 缂佹ê鍩桿I 缂佹ê鍩�1鐎涙顑佹稉鎻掔暚閺佸绮ㄩ弸鍕秼
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	string_data_struct_t String;
	uint16_t CRC16;
} UI_String_t;

#define N sizeof(graphic_data_struct_t)

typedef struct // 缂佹ê鍩桿I UI閸掔娀娅庨崶鎯ц埌鐎瑰本鏆ｇ紒鎾寸€担锟�
{
	frame_header_struct_t Referee_Transmit_Header;
	uint16_t CMD_ID;
	ext_student_interactive_header_data_t Interactive_Header;
	delete_data_struct_t Delete;
	uint16_t CRC16;
} UI_Delete_t;

#pragma pack(pop)

/* Functions -----------------------------------------------------------------*/
void Referee_StructInit(void);
void Referee_UARTInit(uint8_t *Buffer0, uint8_t *Buffer1, uint16_t BufferLength);

void Referee_UnpackFifoData(void);
void Referee_SolveFifoData(uint8_t *frame);

void UI_Draw_Line(graphic_data_struct_t *Graph,		 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
				  char GraphName[3],				 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
				  uint8_t GraphOperate,				 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
				  uint8_t Layer,					 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
				  uint8_t Color,					 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
				  uint16_t Width,					 // 缁惧灝顔�
				  uint16_t StartX,					 // 鐠у嘲顫愰崸鎰垼X
				  uint16_t StartY,					 // 鐠у嘲顫愰崸鎰垼Y
				  uint16_t EndX,					 // 閹搭亝顒涢崸鎰垼X
				  uint16_t EndY);					 // 閹搭亝顒涢崸鎰垼Y
void UI_Draw_Rectangle(graphic_data_struct_t *Graph, // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
					   char GraphName[3],			 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
					   uint8_t GraphOperate,		 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
					   uint8_t Layer,				 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
					   uint8_t Color,				 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
					   uint16_t Width,				 // 缁惧灝顔�
					   uint16_t StartX,				 // 鐠у嘲顫愰崸鎰垼X
					   uint16_t StartY,				 // 鐠у嘲顫愰崸鎰垼Y
					   uint16_t EndX,				 // 閹搭亝顒涢崸鎰垼X
					   uint16_t EndY);				 // 閹搭亝顒涢崸鎰垼Y
void UI_Draw_Circle(graphic_data_struct_t *Graph,	 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
					char GraphName[3],				 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
					uint8_t GraphOperate,			 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
					uint8_t Layer,					 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
					uint8_t Color,					 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
					uint16_t Width,					 // 缁惧灝顔�
					uint16_t CenterX,				 // 閸﹀棗绺鹃崸鎰垼X
					uint16_t CenterY,				 // 閸﹀棗绺鹃崸鎰垼Y
					uint16_t Radius);				 // 閸楀﹤绶�
void UI_Draw_Ellipse(graphic_data_struct_t *Graph,	 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
					 char GraphName[3],				 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
					 uint8_t GraphOperate,			 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
					 uint8_t Layer,					 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
					 uint8_t Color,					 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
					 uint16_t Width,				 // 缁惧灝顔�
					 uint16_t CenterX,				 // 閸﹀棗绺鹃崸鎰垼X
					 uint16_t CenterY,				 // 閸﹀棗绺鹃崸鎰垼Y
					 uint16_t XHalfAxis,			 // X閸楀﹨閰遍梹锟�
					 uint16_t YHalfAxis);			 // Y閸楀﹨閰遍梹锟�
void UI_Draw_Arc(graphic_data_struct_t *Graph,		 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
				 char GraphName[3],					 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
				 uint8_t GraphOperate,				 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
				 uint8_t Layer,						 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
				 uint8_t Color,						 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
				 uint16_t StartAngle,				 // 鐠у嘲顫愮憴鎺戝 [0,360]
				 uint16_t EndAngle,					 // 閹搭亝顒涚憴鎺戝 [0,360]
				 uint16_t Width,					 // 缁惧灝顔�
				 uint16_t CenterX,					 // 閸﹀棗绺鹃崸鎰垼X
				 uint16_t CenterY,					 // 閸﹀棗绺鹃崸鎰垼Y
				 uint16_t XHalfAxis,				 // X閸楀﹨閰遍梹锟�
				 uint16_t YHalfAxis);				 // Y閸楀﹨閰遍梹锟�
void UI_Draw_Float(graphic_data_struct_t *Graph,	 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
				   char GraphName[3],				 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
				   uint8_t GraphOperate,			 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
				   uint8_t Layer,					 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
				   uint8_t Color,					 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
				   uint16_t NumberSize,				 // 鐎涙ぞ缍嬫径褍鐨�
				   uint16_t Significant,			 // 閺堝鏅ユ担宥嗘殶
				   uint16_t Width,					 // 缁惧灝顔�
				   uint16_t StartX,					 // 鐠у嘲顫愰崸鎰垼X
				   uint16_t StartY,					 // 鐠у嘲顫愰崸鎰垼Y
				   float FloatData);				 // 閺佹澘鐡ч崘鍛啇
void UI_Draw_Int(graphic_data_struct_t *Graph,		 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
				 char GraphName[3],					 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
				 uint8_t GraphOperate,				 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
				 uint8_t Layer,						 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
				 uint8_t Color,						 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
				 uint16_t NumberSize,				 // 鐎涙ぞ缍嬫径褍鐨�
				 uint16_t Width,					 // 缁惧灝顔�
				 uint16_t StartX,					 // 鐠у嘲顫愰崸鎰垼X
				 uint16_t StartY,					 // 鐠у嘲顫愰崸鎰垼Y
				 int32_t IntData);					 // 閺佹澘鐡ч崘鍛啇
void UI_Draw_String(string_data_struct_t *String,	 // UI閸ユ儳鑸伴弫鐗堝祦缂佹挻鐎担鎾村瘹闁斤拷
					char StringName[3],				 // 閸ユ儳鑸伴崥锟� 娴ｆ粈璐熺€广垺鍩涚粩顖滄畱缁便垹绱�
					uint8_t StringOperate,			 // UI閸ユ儳鑸伴幙宥勭稊 鐎电懓绨睻I_Graph_XXX閻拷4缁夊秵鎼锋担锟�
					uint8_t Layer,					 // UI閸ユ儳鑸伴崶鎯х湴 [0,9]
					uint8_t Color,					 // UI閸ユ儳鑸版０婊嗗 鐎电懓绨睻I_Color_XXX閻拷9缁夊秹顤侀懝锟�
					uint16_t CharSize,				 // 鐎涙ぞ缍嬫径褍鐨�
					uint16_t StringLength,			 // 鐎涙顑佹稉鏌ユ毐鎼达拷
					uint16_t Width,					 // 缁惧灝顔�
					uint16_t StartX,				 // 鐠у嘲顫愰崸鎰垼X
					uint16_t StartY,				 // 鐠у嘲顫愰崸鎰垼Y
					char *StringData);				 // 鐎涙顑佹稉鎻掑敶鐎癸拷

void UI_PushUp_Graphs(uint8_t Counter, void *Graphs, uint8_t RobotID);
void UI_PushUp_String(UI_String_t *String, uint8_t RobotID);
void UI_PushUp_Delete(UI_Delete_t *Delete, uint8_t RobotID);

/* 鐟佷礁鍨界化鑽ょ埠閺佺増宓佺憴锝囩垳閸ｏ拷 */
typedef struct Referee_Decoder
{
	uint64_t receive_data_arr;	 // 閹恒儲鏁归崚鎵畱閺佺増宓佺€靛嫬鐡ㄩ崳锟�
	uint16_t judgementFullCount; // FIFO 閸﹀牊鏆�
	uint64_t decode_data_arr;	 // 瀹歌尙绮＄憴锝嗙€介惃鍕殶閹诡喖鐦庣€涙ê娅�
	uint16_t decodeFullCount;	 // 鐟欙絾鐎介崷鍫熸殶

	uint8_t judgementStep; // 鐟欙絿鐖滃銉╊€�
	uint16_t index;		   // 瑜版挸澧犵憴锝呭瘶娴ｅ秶鐤�
	uint16_t data_len;	   // 閺佺増宓佺敮褔鏆辨惔锟�

} Referee_Decoder;

typedef struct Referee_t
{
	/* protocol閸栧懎銇旂紒鎾寸€担锟� */
	frame_header_struct_t Referee_Receive_Header;

	/* 0x000X */
	ext_game_status_t Game_Status;
	ext_game_result_t Game_Result;
	ext_game_robot_HP_t Game_Robot_HP;

	/* 0x010X */
	ext_event_data_t Event_Data;
	ext_supply_projectile_action_t Supply_Projectile_Action;
	ext_supply_projectile_booking_t Supply_Projectile_Booking;
	ext_referee_warning_t Referee_Warning;
	ext_dart_remaining_time_t Dart_Remaining_Time;

	/* 0x020X */
	// ext_game_robot_state_t Game_Robot_State;
	// ext_power_heat_data_t Power_Heat_Data;
	// ext_game_robot_pos_t Game_Robot_Pos;
	// ext_buff_musk_t Buff_Musk;
	// aerial_robot_energy_t Aerial_Robot_Energy;
	// ext_robot_hurt_t Robot_Hurt;
	// ext_shoot_data_t Shoot_Data;
	// ext_bullet_remaining_t Bullet_Remaining;
	// ext_rfid_status_t RFID_Status;
	// ext_dart_client_cmd_t Dart_Client_Cmd;
	ext_game_robot_state_t Game_Robot_State; // 0x0201
	ext_power_heat_data_t Power_Heat_Data;	 // 0x0202
	ext_game_robot_pos_t Game_Robot_Pos;	 // 0x0203
	ext_buff_musk_t Buff_Musk;				 // 0x0204
	ext_robot_hurt_t Robot_Hurt;			 // 0x0206
	ext_shoot_data_t Shoot_Data;			 // 0x0207
	ext_bullet_remaining_t Bullet_Remaining; // 0x0208

	/* 0x030X */
	ext_student_interactive_header_data_t Student_Interactive_Header_Data;
	robot_interactive_data_t Robot_Interactive_Data;
	ext_robot_command_t Robot_Command;
	ext_client_map_command_t Client_Map_Command;

	/* 缂佹ê鍩桿I娑撴挾鏁ょ紒鎾寸€担锟� */
	UI_Graph1_t UI_Graph1;
	UI_Graph2_t UI_Graph2;
	UI_Graph5_t UI_Graph5;
	UI_Graph7_t UI_Graph7;
	UI_String_t UI_String;
	UI_Delete_t UI_Delete;

	Referee_Decoder decoder;

} Referee_t;

typedef struct RefereeDataUpdate
{
	int8_t is_max_power_data_update;
	int8_t is_power_data_update;
} RefereeDataUpdate;

extern RefereeDataUpdate referee_data_updater;

extern Referee_t referee_data;

#define MAX_REFEREE_DATA_LEN 45

#endif /* __REFEREE_H__ */
