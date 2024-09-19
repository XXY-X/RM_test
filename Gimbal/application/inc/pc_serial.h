#ifndef _PC_SERIAL_H
#define _PC_SERIAL_H

#include "algorithmOfCRC.h"
#include "ins_task.h"

#include "ChassisGet.h"

enum AUTOAIM_MODE
{
    AUTO_AIM = 0,
    SMALL_BUFF,
    BIG_BUFF
};

/*   发送数据定义 */

#pragma pack(push, 1)     // 不进行字节对齐
typedef struct PCSendData // 数据顺序不能变,注意32字节对齐
{
    int8_t start_flag;
    uint8_t robot_color : 1;
    uint8_t shoot_level : 2;
    uint8_t mode : 2;
    uint8_t which_balance : 2;
    uint8_t aim_request : 1;
    uint8_t frame_id;
    short pitch;
    float yaw;
    int16_t crc16;
} PCSendData;

typedef struct PCRecvData
{
    int8_t start_flag;
    uint8_t enemy_id : 3;   // 敌方ID，如果是0的话不击打,云台也不动
    uint8_t shoot_flag : 1; // 打击标志位
    uint8_t mode : 2;       // 上位机当前所处模式，将与下位机的模式进行检验
    uint8_t _ : 2;
    uint8_t frame_id;
    short pitch;
    float yaw;
    int16_t crc16;
} PCRecvData;

#pragma pack(pop) // 不进行字节对齐

#define PC_SENDBUF_SIZE sizeof(PCSendData)
#define PC_RECVBUF_SIZE sizeof(PCRecvData)

extern unsigned char PCbuffer[PC_RECVBUF_SIZE];
extern unsigned char SendToPC_Buff[PC_SENDBUF_SIZE];

void PCReceive(unsigned char *PCbuffer);
void SendtoPC(void);

extern PCRecvData pc_recv_data;
extern PCSendData pc_send_data;

#endif // !_PC_SERIAL_H
