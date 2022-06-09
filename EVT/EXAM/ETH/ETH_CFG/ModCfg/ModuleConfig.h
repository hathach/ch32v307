
/********************************** (C) COPYRIGHT *********************************
* File Name          : Moduleconfig.H
* Description        :��λ��ͨ�����ݽṹ����
*                      
**********************************************************************************/
#ifndef __MODULECONFIG_H__
#define __MODULECONFIG_H__

#include "debug.h"

/*�洢������Ϣ�ĵ�ַ*/
#define PAGE_WRITE_START_ADDR     ((uint32_t)0x0803FF00) /* Start from (256K - 256B) */
#define PAGE_WRITE_END_ADDR       ((uint32_t)0x08040000) /* End at 256K */
#define FLASH_PAGE_SIZE           256

#define NET_MODULE_DATA_LENGTH    60                     //��ģ��ͨ��ʱ����������󳤶�
#define MODULE_CFG_LEN            44                     //����buff����
                                                                                      
//ͨ��������                                                                          
#define NET_MODULE_CMD_SET        0X01                   //���������е�ģ��
#define NET_MODULE_CMD_GET        0X02                   //��ȡĳ��ģ�������
#define NET_MODULE_CMD_RESET      0X03                   //��ȡĳ��ģ�������
#define NET_MODULE_CMD_SEARCH     0X04                   //���������е�ģ��
                                                                                      
//Ӧ��������                                                                          
#define NET_MODULE_ACK_SET        0X81                   //��Ӧ����������
#define NET_MODULE_ACK_GET        0X82                   //��Ӧ��ȡ������
#define NET_MODULE_ACK_RESET      0X83                   //��ȡĳ��ģ�������
#define NET_MODULE_ACK_SEARCH     0X84                   //��Ӧ����������
                                                                                      
#define NET_MODULE_FLAG           "WCHNET_MODULE"        //������ʶ��λ��ͨ��
#define checkcode1                0X11                   //������ʶ������Ϣ
#define checkcode2                0x22

//����ͨ�Žṹ��
typedef struct NET_COMM {
  unsigned char flag[16];                                //ͨ�ű�ʶ����Ϊ�����ù㲥��ʽ����ͨ�ŵģ����������һ���̶�ֵ
  unsigned char cmd;                                     //����ͷ
  unsigned char id[6];                                   //��ʶ��CH563MAC��ַ
  unsigned char len;                                     //����������
  unsigned char dat[NET_MODULE_DATA_LENGTH];             //������������
}net_comm,*pnet_comm;

//ģ���ʶ
#define  NET_MODULE_TYPE_TCP_S    0X00                   //ģ����ΪTCP SERVER
#define  NET_MODULE_TYPE_TCP_C    0X01                   //ģ����ΪTCP CLIENT
#define  NET_MODULE_TYPE_UDP_S    0X02                   //ģ����ΪUDP SERVER
#define  NET_MODULE_TYPE_UDP_C    0X03                   //ģ����ΪUDP CLIENT
#define  NET_MODULE_TYPE_NONE     0X04                   //ģ���Ĭ�����ã��������κ�ģʽ

//ģ������ýṹ
typedef struct MODULE_CFG {
  unsigned char module_name[21];                         //ģ�鱾����IP��ַ
  unsigned char type;                                    //��ʶģ�鴦����ģʽ(TCP/UDP server/client)
  unsigned char src_ip[4];                               //ģ�鱾����IP��ַ
  unsigned char mask[4];                                 //ģ�鱾������������
  unsigned char getway[4];                               //ģ���Ӧ�����ص�ַ
  unsigned char src_port[2];                             //ģ��Դ�˿�
  unsigned char dest_ip[4];                              //Ŀ��IP��ַ
  unsigned char dest_port[2];                            //Ŀ�Ķ˿�
  unsigned char cfg_flag[2];                             //���ڶ�ȡEEEPROMʱ��֤������Ϣ
}module_cfg,*pmodule_cfg;

extern u8 MACAddr[6];
extern u8 Configbuf[MODULE_CFG_LEN];
extern u8  brocastIp[4];                                 /*�㲥IP��ַ�����ɸ�*/
extern u16 brocastPort;                                  /*��λ��ͨѶ�˿ں�*/

/*erase Data-Flash block, minimal block is 256B, return SUCCESS if success*/
extern void EEPROM_ERASE(uint32_t Page_Address, u32 Length );

/*write Data-Flash data block, return FLASH_Status*/
extern FLASH_Status EEPROM_WRITE( u32 StartAddr, u8 *Buffer, u32 Length );

/*read Data-Flash data block */
extern void EEPROM_READ( u32 StartAddr, u8 *Buffer, u32 Length );

extern u8 Default_cfg[MODULE_CFG_LEN];
extern pmodule_cfg CFG;
extern u8 ParseConfigbuf(u8 *buf);
#endif