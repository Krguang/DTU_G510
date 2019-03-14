/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "common.h"
#include "usart.h"
#include "tim.h"

static uint32_t timerMsCount;
uint8_t aRxBuffer;

volatile uint16_t localArray[256];
volatile uint8_t modbusPullFlag01;

/** User area the current device state structure*/
dataPoint_t currentDataPoint;

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {

      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{

	currentDataPoint.valueJK_1_fengJiYiQiDong = localArray[8];
	currentDataPoint.valueJK_1_zhiBanStatus = localArray[9];
	currentDataPoint.valueJK_1_dianJiaRe1 = localArray[10];
	currentDataPoint.valueJK_1_dianJiaRe2 = localArray[11];
	currentDataPoint.valueJK_1_dianJiaRe3 = localArray[12];
	currentDataPoint.valueJK_1_fengJiStatus = localArray[13];
	currentDataPoint.valueJK_1_shouZiDong = localArray[14];
	currentDataPoint.valueJK_1_dongXiaJi = localArray[15];
	currentDataPoint.valueJK_1_zhongXiaoBaoJing = localArray[16];
	currentDataPoint.valueJK_1_dianJiaReGaoWen = localArray[17];
	currentDataPoint.valueJK_1_fengJiQueFeng = localArray[18];
	currentDataPoint.valueJK_1_paiFengJiYiQiDong = localArray[19];
	currentDataPoint.valueJK_1_diWenPanGuan = localArray[27];
	currentDataPoint.valueJK_1_mieJunYunXing = localArray[28];
	currentDataPoint.valueJK_2_fengJiYiQiDong = localArray[38];
	currentDataPoint.valueJK_2_zhiBanStatus = localArray[39];
	currentDataPoint.valueJK_2_dianJiaRe1 = localArray[40];
	currentDataPoint.valueJK_2_dianJiaRe2 = localArray[41];
	currentDataPoint.valueJK_2_dianJiaRe3 = localArray[42];
	currentDataPoint.valueJK_2_fengJiStatus = localArray[43];
	currentDataPoint.valueJK_2_shouZiDong = localArray[44];
	currentDataPoint.valueJK_2_dongXiaJi = localArray[45];
	currentDataPoint.valueJK_2_zhongXiaoBaoJing = localArray[46];
	currentDataPoint.valueJK_2_dianJiaReGaoWen = localArray[47];
	currentDataPoint.valueJK_2_fengJiQueFeng = localArray[48];
	currentDataPoint.valueJK_2_paiFengJiYiQiDong = localArray[49];
	currentDataPoint.valueJK_2_diWenPanGuan = localArray[57];
	currentDataPoint.valueJK_2_mieJunYunXing = localArray[58];
	currentDataPoint.valueJK_3_fengJiYiQiDong = localArray[68];
	currentDataPoint.valueJK_3_zhiBanStatus = localArray[69];
	currentDataPoint.valueJK_3_dianJiaRe1 = localArray[70];
	currentDataPoint.valueJK_3_dianJiaRe2 = localArray[71];
	currentDataPoint.valueJK_3_dianJiaRe3 = localArray[72];
	currentDataPoint.valueJK_3_fengJiStatus = localArray[73];
	currentDataPoint.valueJK_3_shouZiDong = localArray[74];
	currentDataPoint.valueJK_3_dongXiaJi = localArray[75];
	currentDataPoint.valueJK_3_zhongXiaoBaoJing = localArray[76];
	currentDataPoint.valueJK_3_dianJiaReGaoWen = localArray[77];
	currentDataPoint.valueJK_3_fengJiQueFeng = localArray[78];
	currentDataPoint.valueJK_3_paiFengJiYiQiDong = localArray[79];
	currentDataPoint.valueJK_3_diWenPanGuan = localArray[87];
	currentDataPoint.valueJK_3_mieJunYunXing = localArray[88];
	currentDataPoint.valueJK_XF_fengJiYiQiDong = localArray[98];
	currentDataPoint.valueJK_XF_zhiBanStatus = localArray[99];
	currentDataPoint.valueJK_XF_dianJiaRe1 = localArray[100];
	currentDataPoint.valueJK_XF_dianJiaRe2 = localArray[101];
	currentDataPoint.valueJK_XF_dianJiaRe3 = localArray[102];
	currentDataPoint.valueJK_XF_fengJiStatus = localArray[103];
	currentDataPoint.valueJK_XF_shouZiDong = localArray[104];
	currentDataPoint.valueJK_XF_dongXiaJi = localArray[105];
	currentDataPoint.valueJK_XF_zhongXiaoBaoJing = localArray[106];
	currentDataPoint.valueJK_XF_dianJiaReGaoWen = localArray[107];
	currentDataPoint.valueJK_XF_fengJiQueFeng = localArray[108];
	currentDataPoint.valueJK_XF_paiFengJiYiQiDong = localArray[109];
	currentDataPoint.valueJK_XF_diWenPanGuan = localArray[117];
	currentDataPoint.valueJK_XF_mieJunYunXing = localArray[118];

	currentDataPoint.valueJK_1_mianBanTongXunZhuangTai1 = localArray[20];
	currentDataPoint.valueJK_1_mianBanTongXunZhuangTai2 = localArray[21];
	currentDataPoint.valueJK_1_mianBanTongXunZhuangTai3 = localArray[22];
	currentDataPoint.valueJK_2_mianBanTongXunZhuangTai1 = localArray[50];
	currentDataPoint.valueJK_2_mianBanTongXunZhuangTai2 = localArray[51];
	currentDataPoint.valueJK_2_mianBanTongXunZhuangTai3 = localArray[52];
	currentDataPoint.valueJK_3_mianBanTongXunZhuangTai1 = localArray[80];
	currentDataPoint.valueJK_3_mianBanTongXunZhuangTai2 = localArray[81];
	currentDataPoint.valueJK_3_mianBanTongXunZhuangTai3 = localArray[82];
	currentDataPoint.valueJK_XF_mianBanTongXunZhuangTai1 = localArray[110];
	currentDataPoint.valueJK_XF_mianBanTongXunZhuangTai2 = localArray[111];
	currentDataPoint.valueJK_XF_mianBanTongXunZhuangTai3 = localArray[112];

	currentDataPoint.valueJK_1_tempReal = localArray[0];
	currentDataPoint.valueJK_1_humiReal = localArray[1];
	currentDataPoint.valueJK_1_tempSet = localArray[2];
	currentDataPoint.valueJK_1_humiSet = localArray[3];
	currentDataPoint.valueJK_1_lengShuiFaKaiDu = localArray[4];
	currentDataPoint.valueJK_1_reShuiFaKaiDu = localArray[5];
	currentDataPoint.valueJK_1_xinFengWenDU = localArray[6];
	currentDataPoint.valueJK_1_jiaShiQIKaiDu = localArray[7];
	//currentDataPoint.valueJK_1_beiYong = localArray[29];		//这个数据点改为机组数量
	currentDataPoint.valueJK_2_tempReal = localArray[30];
	currentDataPoint.valueJK_2_humiReal = localArray[31];
	currentDataPoint.valueJK_2_tempSet = localArray[32];
	currentDataPoint.valueJK_2_humiSet = localArray[33];
	currentDataPoint.valueJK_2_lengShuiFaKaiDu = localArray[34];
	currentDataPoint.valueJK_2_reShuiFaKaiDu = localArray[35];
	currentDataPoint.valueJK_2_xinFengWenDU = localArray[36];
	currentDataPoint.valueJK_2_jiaShiQIKaiDu = localArray[37];
	currentDataPoint.valueJK_2_beiYong = localArray[59];
	currentDataPoint.valueJK_3_tempReal = localArray[60];
	currentDataPoint.valueJK_3_humiReal = localArray[61];
	currentDataPoint.valueJK_3_tempSet = localArray[62];
	currentDataPoint.valueJK_3_humiSet = localArray[63];
	currentDataPoint.valueJK_3_lengShuiFaKaiDu = localArray[64];
	currentDataPoint.valueJK_3_reShuiFaKaiDu = localArray[65];
	currentDataPoint.valueJK_3_xinFengWenDU = localArray[66];
	currentDataPoint.valueJK_3_jiaShiQIKaiDu = localArray[67];
	currentDataPoint.valueJK_3_beiYong = localArray[89];
	currentDataPoint.valueJK_XF_tempReal = localArray[90];
	currentDataPoint.valueJK_XF_humiReal = localArray[91];
	currentDataPoint.valueJK_XF_tempSet = localArray[92];
	currentDataPoint.valueJK_XF_humiSet = localArray[93];
	currentDataPoint.valueJK_XF_lengShuiFaKaiDu = localArray[94];
	currentDataPoint.valueJK_XF_reShuiFaKaiDu = localArray[95];
	currentDataPoint.valueJK_XF_xinFengWenDU = localArray[96];
	currentDataPoint.valueJK_XF_jiaShiQIKaiDu = localArray[97];
	currentDataPoint.valueJK_XF_beiYong = localArray[119]; 
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 

	currentDataPoint.valueJK_1_beiYong = 4;

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
}


int _write(int fd, char *pBuffer, int size)
{
	HAL_UART_Transmit(&huart3, pBuffer, size, 0xff);
	return size;
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t count = 0;
	if(htim==&htim2)
	{
		gizTimerMs();
		count++;
		if (count > 3000)
		{
			count = 0;
			modbusPullFlag01 = 1;
		}
	}
}

/**
* @brief Timer TIM3 init function

* @param none
* @return none
*/
void timerInit(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  This function handles USART IDLE interrupt.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)  
{  
    if(UartHandle->Instance == USART2)  
    {  
		gizPutData((uint8_t *)&aRxBuffer, 1);
        HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
    }  
}  

/**
* @brief USART init function

* Serial communication between WiFi modules and device MCU
* @param none
* @return none
*/
void uartInit(void)
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
}

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
		uint8_t crc[1] = {0x55};
    uint32_t i = 0;
	
    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)&buf[i], 1);
				while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission

        if(i >=2 && buf[i] == 0xFF)
        {
						HAL_UART_Transmit_IT(&huart2, (uint8_t *)&crc, 1);
						while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif
		
		return len;
}  
