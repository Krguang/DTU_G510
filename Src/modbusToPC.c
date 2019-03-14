#include "modbusToPC.h"
#include "usart.h"
#include "gizwits_product.h"

uint8_t slaveAdd = 20;
uint16_t sendQueue = 0;
uint8_t a;

static uint16_t GetCRC16(uint8_t *arr_buff, uint16_t len) {  //CRCУ�����
	uint16_t crc = 0xFFFF;
	uint16_t i, j;
	for (j = 0; j < len; j++) {
		crc = crc ^*arr_buff++;
		for (i = 0; i < 8; i++) {
			if ((crc & 0x0001) > 0) {
				crc = crc >> 1;
				crc = crc ^ 0xa001;
			}
			else
				crc = crc >> 1;
		}
	}
	return (crc);
}


static void sendDataMaster03(uint8_t start,uint8_t num) {
	uint8_t txBuf[10];
	uint16_t temp;
	txBuf[0] = slaveAdd;
	txBuf[1] = 0x03;
	txBuf[2] = 0x00;
	txBuf[3] = start;
	txBuf[4] = 0x00;
	txBuf[5] = num;
	temp = GetCRC16(txBuf, 6);
	txBuf[6] = (uint8_t)(temp & 0xff);
	txBuf[7] = (uint8_t)(temp >> 8);

	HAL_UART_Transmit(&huart1, txBuf, 8, 0xffff);
}


static void ModbusDecode(uint8_t *MDbuf, uint16_t len) {

	uint16_t  crc;
	uint8_t crch, crcl;


	if (MDbuf[0] != slaveAdd) return;								//��ַ���ʱ���ٶԱ�֡���ݽ���У��
	if (MDbuf[1] != 0x03) return;									//���鹦����
	crc = GetCRC16(MDbuf, len - 2);								//����CRCУ��ֵ
	crch = crc >> 8;
	crcl = crc & 0xFF;
	if ((MDbuf[len - 1] != crch) || (MDbuf[len - 2] != crcl)) return;	//��CRCУ�鲻��ʱֱ���˳�
	for (uint8_t i = 0; i < MDbuf[2] / 2; i++)
	{
		localArray[i + sendQueue] = (uint16_t)(MDbuf[3 + 2 * i] << 8) + MDbuf[4 + 2 * i];
	}
}


void modbusReceive() {
	if (Usart1ReceiveState)
	{
		Usart1ReceiveState = 0;
		ModbusDecode(Usart1ReceiveBuffer.BufferArray, Usart1ReceiveBuffer.BufferLen);
		Usart1ReceiveBuffer.BufferLen = 0;
	}
}


void modbusPull() {

	if (modbusPullFlag01 == 1)
	{
		modbusPullFlag01 = 0;
		sendDataMaster03(0,120);
	}
}

