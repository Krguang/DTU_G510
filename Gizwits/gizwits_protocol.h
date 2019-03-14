/**
************************************************************
* @file         gizwits_protocol.h
* @brief        Corresponding gizwits_product.c header file (including product hardware and software version definition)
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

#ifndef _GIZWITS_PROTOCOL_H
#define _GIZWITS_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

                                                                                                                  
#define SEND_MAX_TIME       5000                     ///< 200ms resend
#define SEND_MAX_NUM        3                       ///< resend times
                                                    
#define protocol_VERSION    "00000004"              ///< protocol version
#define P0_VERSION          "00000002"              ///< P0 protocol version

/**@name Product Key  
* @{
*/
#define PRODUCT_KEY "36ea0d1c0e38492fa6d1f30cff732daa"
/**@} */
/**@name Product Secret  
* @{
*/
#define PRODUCT_SECRET "a79d12e2430b4f6491a7e40ecfd32586"
               
/**@name Device status data reporting interval
* @{
*/
#define REPORT_TIME_MAX 6000 //6S
/**@} */    

#define CELLNUMMAX 7    


/**@name Whether the device is in the control class, 0 means no, 1 means yes
* @{
*/
#define DEV_IS_GATEWAY   0                    
/**@} */

/**@name Binding time
* @{
*/
#define NINABLETIME  0
/**@} */



#define MAX_PACKAGE_LEN    (sizeof(devStatus_t)+sizeof(dataPointFlags_t)+20)                 ///< Data buffer maximum length                                   ///< Data buffer maximum length

#define RB_MAX_LEN          (MAX_PACKAGE_LEN*2)     ///< Maximum length of ring buffer

/**@name Data point related definition
* @{
*/
#define JK_1_fengJiYiQiDong_LEN                           1
#define JK_1_zhiBanStatus_LEN                           1
#define JK_1_dianJiaRe1_LEN                           1
#define JK_1_dianJiaRe2_LEN                           1
#define JK_1_dianJiaRe3_LEN                           1
#define JK_1_fengJiStatus_LEN                           1
#define JK_1_shouZiDong_LEN                           1
#define JK_1_dongXiaJi_LEN                           1
#define JK_1_zhongXiaoBaoJing_LEN                           1
#define JK_1_dianJiaReGaoWen_LEN                           1
#define JK_1_fengJiQueFeng_LEN                           1
#define JK_1_paiFengJiYiQiDong_LEN                           1
#define JK_1_diWenPanGuan_LEN                           1
#define JK_1_mieJunYunXing_LEN                           1
#define JK_2_fengJiYiQiDong_LEN                           1
#define JK_2_zhiBanStatus_LEN                           1
#define JK_2_dianJiaRe1_LEN                           1
#define JK_2_dianJiaRe2_LEN                           1
#define JK_2_dianJiaRe3_LEN                           1
#define JK_2_fengJiStatus_LEN                           1
#define JK_2_shouZiDong_LEN                           1
#define JK_2_dongXiaJi_LEN                           1
#define JK_2_zhongXiaoBaoJing_LEN                           1
#define JK_2_dianJiaReGaoWen_LEN                           1
#define JK_2_fengJiQueFeng_LEN                           1
#define JK_2_paiFengJiYiQiDong_LEN                           1
#define JK_2_diWenPanGuan_LEN                           1
#define JK_2_mieJunYunXing_LEN                           1
#define JK_3_fengJiYiQiDong_LEN                           1
#define JK_3_zhiBanStatus_LEN                           1
#define JK_3_dianJiaRe1_LEN                           1
#define JK_3_dianJiaRe2_LEN                           1
#define JK_3_dianJiaRe3_LEN                           1
#define JK_3_fengJiStatus_LEN                           1
#define JK_3_shouZiDong_LEN                           1
#define JK_3_dongXiaJi_LEN                           1
#define JK_3_zhongXiaoBaoJing_LEN                           1
#define JK_3_dianJiaReGaoWen_LEN                           1
#define JK_3_fengJiQueFeng_LEN                           1
#define JK_3_paiFengJiYiQiDong_LEN                           1
#define JK_3_diWenPanGuan_LEN                           1
#define JK_3_mieJunYunXing_LEN                           1
#define JK_XF_fengJiYiQiDong_LEN                           1
#define JK_XF_zhiBanStatus_LEN                           1
#define JK_XF_dianJiaRe1_LEN                           1
#define JK_XF_dianJiaRe2_LEN                           1
#define JK_XF_dianJiaRe3_LEN                           1
#define JK_XF_fengJiStatus_LEN                           1
#define JK_XF_shouZiDong_LEN                           1
#define JK_XF_dongXiaJi_LEN                           1
#define JK_XF_zhongXiaoBaoJing_LEN                           1
#define JK_XF_dianJiaReGaoWen_LEN                           1
#define JK_XF_fengJiQueFeng_LEN                           1
#define JK_XF_paiFengJiYiQiDong_LEN                           1
#define JK_XF_diWenPanGuan_LEN                           1
#define JK_XF_mieJunYunXing_LEN                           1

#define JK_1_mianBanTongXunZhuangTai1_RATIO                         1
#define JK_1_mianBanTongXunZhuangTai1_ADDITION                      0
#define JK_1_mianBanTongXunZhuangTai1_MIN                           0
#define JK_1_mianBanTongXunZhuangTai1_MAX                           255
#define JK_1_mianBanTongXunZhuangTai1_LEN                           1
#define JK_1_mianBanTongXunZhuangTai2_RATIO                         1
#define JK_1_mianBanTongXunZhuangTai2_ADDITION                      0
#define JK_1_mianBanTongXunZhuangTai2_MIN                           0
#define JK_1_mianBanTongXunZhuangTai2_MAX                           255
#define JK_1_mianBanTongXunZhuangTai2_LEN                           1
#define JK_1_mianBanTongXunZhuangTai3_RATIO                         1
#define JK_1_mianBanTongXunZhuangTai3_ADDITION                      0
#define JK_1_mianBanTongXunZhuangTai3_MIN                           0
#define JK_1_mianBanTongXunZhuangTai3_MAX                           255
#define JK_1_mianBanTongXunZhuangTai3_LEN                           1
#define JK_2_mianBanTongXunZhuangTai1_RATIO                         1
#define JK_2_mianBanTongXunZhuangTai1_ADDITION                      0
#define JK_2_mianBanTongXunZhuangTai1_MIN                           0
#define JK_2_mianBanTongXunZhuangTai1_MAX                           255
#define JK_2_mianBanTongXunZhuangTai1_LEN                           1
#define JK_2_mianBanTongXunZhuangTai2_RATIO                         1
#define JK_2_mianBanTongXunZhuangTai2_ADDITION                      0
#define JK_2_mianBanTongXunZhuangTai2_MIN                           0
#define JK_2_mianBanTongXunZhuangTai2_MAX                           255
#define JK_2_mianBanTongXunZhuangTai2_LEN                           1
#define JK_2_mianBanTongXunZhuangTai3_RATIO                         1
#define JK_2_mianBanTongXunZhuangTai3_ADDITION                      0
#define JK_2_mianBanTongXunZhuangTai3_MIN                           0
#define JK_2_mianBanTongXunZhuangTai3_MAX                           255
#define JK_2_mianBanTongXunZhuangTai3_LEN                           1
#define JK_3_mianBanTongXunZhuangTai1_RATIO                         1
#define JK_3_mianBanTongXunZhuangTai1_ADDITION                      0
#define JK_3_mianBanTongXunZhuangTai1_MIN                           0
#define JK_3_mianBanTongXunZhuangTai1_MAX                           255
#define JK_3_mianBanTongXunZhuangTai1_LEN                           1
#define JK_3_mianBanTongXunZhuangTai2_RATIO                         1
#define JK_3_mianBanTongXunZhuangTai2_ADDITION                      0
#define JK_3_mianBanTongXunZhuangTai2_MIN                           0
#define JK_3_mianBanTongXunZhuangTai2_MAX                           255
#define JK_3_mianBanTongXunZhuangTai2_LEN                           1
#define JK_3_mianBanTongXunZhuangTai3_RATIO                         1
#define JK_3_mianBanTongXunZhuangTai3_ADDITION                      0
#define JK_3_mianBanTongXunZhuangTai3_MIN                           0
#define JK_3_mianBanTongXunZhuangTai3_MAX                           255
#define JK_3_mianBanTongXunZhuangTai3_LEN                           1
#define JK_XF_mianBanTongXunZhuangTai1_RATIO                         1
#define JK_XF_mianBanTongXunZhuangTai1_ADDITION                      0
#define JK_XF_mianBanTongXunZhuangTai1_MIN                           0
#define JK_XF_mianBanTongXunZhuangTai1_MAX                           255
#define JK_XF_mianBanTongXunZhuangTai1_LEN                           1
#define JK_XF_mianBanTongXunZhuangTai2_RATIO                         1
#define JK_XF_mianBanTongXunZhuangTai2_ADDITION                      0
#define JK_XF_mianBanTongXunZhuangTai2_MIN                           0
#define JK_XF_mianBanTongXunZhuangTai2_MAX                           255
#define JK_XF_mianBanTongXunZhuangTai2_LEN                           1
#define JK_XF_mianBanTongXunZhuangTai3_RATIO                         1
#define JK_XF_mianBanTongXunZhuangTai3_ADDITION                      0
#define JK_XF_mianBanTongXunZhuangTai3_MIN                           0
#define JK_XF_mianBanTongXunZhuangTai3_MAX                           255
#define JK_XF_mianBanTongXunZhuangTai3_LEN                           1
#define JK_1_tempReal_RATIO                         1
#define JK_1_tempReal_ADDITION                      0
#define JK_1_tempReal_MIN                           0
#define JK_1_tempReal_MAX                           1000
#define JK_1_tempReal_LEN                           2
#define JK_1_humiReal_RATIO                         1
#define JK_1_humiReal_ADDITION                      0
#define JK_1_humiReal_MIN                           0
#define JK_1_humiReal_MAX                           1000
#define JK_1_humiReal_LEN                           2
#define JK_1_tempSet_RATIO                         1
#define JK_1_tempSet_ADDITION                      0
#define JK_1_tempSet_MIN                           0
#define JK_1_tempSet_MAX                           1000
#define JK_1_tempSet_LEN                           2
#define JK_1_humiSet_RATIO                         1
#define JK_1_humiSet_ADDITION                      0
#define JK_1_humiSet_MIN                           0
#define JK_1_humiSet_MAX                           1000
#define JK_1_humiSet_LEN                           2
#define JK_1_lengShuiFaKaiDu_RATIO                         1
#define JK_1_lengShuiFaKaiDu_ADDITION                      0
#define JK_1_lengShuiFaKaiDu_MIN                           0
#define JK_1_lengShuiFaKaiDu_MAX                           1000
#define JK_1_lengShuiFaKaiDu_LEN                           2
#define JK_1_reShuiFaKaiDu_RATIO                         1
#define JK_1_reShuiFaKaiDu_ADDITION                      0
#define JK_1_reShuiFaKaiDu_MIN                           0
#define JK_1_reShuiFaKaiDu_MAX                           1000
#define JK_1_reShuiFaKaiDu_LEN                           2
#define JK_1_xinFengWenDU_RATIO                         1
#define JK_1_xinFengWenDU_ADDITION                      0
#define JK_1_xinFengWenDU_MIN                           0
#define JK_1_xinFengWenDU_MAX                           1000
#define JK_1_xinFengWenDU_LEN                           2
#define JK_1_jiaShiQIKaiDu_RATIO                         1
#define JK_1_jiaShiQIKaiDu_ADDITION                      0
#define JK_1_jiaShiQIKaiDu_MIN                           0
#define JK_1_jiaShiQIKaiDu_MAX                           1000
#define JK_1_jiaShiQIKaiDu_LEN                           2
#define JK_1_beiYong_RATIO                         1
#define JK_1_beiYong_ADDITION                      0
#define JK_1_beiYong_MIN                           0
#define JK_1_beiYong_MAX                           65535
#define JK_1_beiYong_LEN                           2
#define JK_2_tempReal_RATIO                         1
#define JK_2_tempReal_ADDITION                      0
#define JK_2_tempReal_MIN                           0
#define JK_2_tempReal_MAX                           1000
#define JK_2_tempReal_LEN                           2
#define JK_2_humiReal_RATIO                         1
#define JK_2_humiReal_ADDITION                      0
#define JK_2_humiReal_MIN                           0
#define JK_2_humiReal_MAX                           1000
#define JK_2_humiReal_LEN                           2
#define JK_2_tempSet_RATIO                         1
#define JK_2_tempSet_ADDITION                      0
#define JK_2_tempSet_MIN                           0
#define JK_2_tempSet_MAX                           1000
#define JK_2_tempSet_LEN                           2
#define JK_2_humiSet_RATIO                         1
#define JK_2_humiSet_ADDITION                      0
#define JK_2_humiSet_MIN                           0
#define JK_2_humiSet_MAX                           1000
#define JK_2_humiSet_LEN                           2
#define JK_2_lengShuiFaKaiDu_RATIO                         1
#define JK_2_lengShuiFaKaiDu_ADDITION                      0
#define JK_2_lengShuiFaKaiDu_MIN                           0
#define JK_2_lengShuiFaKaiDu_MAX                           1000
#define JK_2_lengShuiFaKaiDu_LEN                           2
#define JK_2_reShuiFaKaiDu_RATIO                         1
#define JK_2_reShuiFaKaiDu_ADDITION                      0
#define JK_2_reShuiFaKaiDu_MIN                           0
#define JK_2_reShuiFaKaiDu_MAX                           1000
#define JK_2_reShuiFaKaiDu_LEN                           2
#define JK_2_xinFengWenDU_RATIO                         1
#define JK_2_xinFengWenDU_ADDITION                      0
#define JK_2_xinFengWenDU_MIN                           0
#define JK_2_xinFengWenDU_MAX                           1000
#define JK_2_xinFengWenDU_LEN                           2
#define JK_2_jiaShiQIKaiDu_RATIO                         1
#define JK_2_jiaShiQIKaiDu_ADDITION                      0
#define JK_2_jiaShiQIKaiDu_MIN                           0
#define JK_2_jiaShiQIKaiDu_MAX                           1000
#define JK_2_jiaShiQIKaiDu_LEN                           2
#define JK_2_beiYong_RATIO                         1
#define JK_2_beiYong_ADDITION                      0
#define JK_2_beiYong_MIN                           0
#define JK_2_beiYong_MAX                           65535
#define JK_2_beiYong_LEN                           2
#define JK_3_tempReal_RATIO                         1
#define JK_3_tempReal_ADDITION                      0
#define JK_3_tempReal_MIN                           0
#define JK_3_tempReal_MAX                           1000
#define JK_3_tempReal_LEN                           2
#define JK_3_humiReal_RATIO                         1
#define JK_3_humiReal_ADDITION                      0
#define JK_3_humiReal_MIN                           0
#define JK_3_humiReal_MAX                           1000
#define JK_3_humiReal_LEN                           2
#define JK_3_tempSet_RATIO                         1
#define JK_3_tempSet_ADDITION                      0
#define JK_3_tempSet_MIN                           0
#define JK_3_tempSet_MAX                           1000
#define JK_3_tempSet_LEN                           2
#define JK_3_humiSet_RATIO                         1
#define JK_3_humiSet_ADDITION                      0
#define JK_3_humiSet_MIN                           0
#define JK_3_humiSet_MAX                           1000
#define JK_3_humiSet_LEN                           2
#define JK_3_lengShuiFaKaiDu_RATIO                         1
#define JK_3_lengShuiFaKaiDu_ADDITION                      0
#define JK_3_lengShuiFaKaiDu_MIN                           0
#define JK_3_lengShuiFaKaiDu_MAX                           1000
#define JK_3_lengShuiFaKaiDu_LEN                           2
#define JK_3_reShuiFaKaiDu_RATIO                         1
#define JK_3_reShuiFaKaiDu_ADDITION                      0
#define JK_3_reShuiFaKaiDu_MIN                           0
#define JK_3_reShuiFaKaiDu_MAX                           1000
#define JK_3_reShuiFaKaiDu_LEN                           2
#define JK_3_xinFengWenDU_RATIO                         1
#define JK_3_xinFengWenDU_ADDITION                      0
#define JK_3_xinFengWenDU_MIN                           0
#define JK_3_xinFengWenDU_MAX                           1000
#define JK_3_xinFengWenDU_LEN                           2
#define JK_3_jiaShiQIKaiDu_RATIO                         1
#define JK_3_jiaShiQIKaiDu_ADDITION                      0
#define JK_3_jiaShiQIKaiDu_MIN                           0
#define JK_3_jiaShiQIKaiDu_MAX                           1000
#define JK_3_jiaShiQIKaiDu_LEN                           2
#define JK_3_beiYong_RATIO                         1
#define JK_3_beiYong_ADDITION                      0
#define JK_3_beiYong_MIN                           0
#define JK_3_beiYong_MAX                           65535
#define JK_3_beiYong_LEN                           2
#define JK_XF_tempReal_RATIO                         1
#define JK_XF_tempReal_ADDITION                      0
#define JK_XF_tempReal_MIN                           0
#define JK_XF_tempReal_MAX                           1000
#define JK_XF_tempReal_LEN                           2
#define JK_XF_humiReal_RATIO                         1
#define JK_XF_humiReal_ADDITION                      0
#define JK_XF_humiReal_MIN                           0
#define JK_XF_humiReal_MAX                           1000
#define JK_XF_humiReal_LEN                           2
#define JK_XF_tempSet_RATIO                         1
#define JK_XF_tempSet_ADDITION                      0
#define JK_XF_tempSet_MIN                           0
#define JK_XF_tempSet_MAX                           1000
#define JK_XF_tempSet_LEN                           2
#define JK_XF_humiSet_RATIO                         1
#define JK_XF_humiSet_ADDITION                      0
#define JK_XF_humiSet_MIN                           0
#define JK_XF_humiSet_MAX                           1000
#define JK_XF_humiSet_LEN                           2
#define JK_XF_lengShuiFaKaiDu_RATIO                         1
#define JK_XF_lengShuiFaKaiDu_ADDITION                      0
#define JK_XF_lengShuiFaKaiDu_MIN                           0
#define JK_XF_lengShuiFaKaiDu_MAX                           1000
#define JK_XF_lengShuiFaKaiDu_LEN                           2
#define JK_XF_reShuiFaKaiDu_RATIO                         1
#define JK_XF_reShuiFaKaiDu_ADDITION                      0
#define JK_XF_reShuiFaKaiDu_MIN                           0
#define JK_XF_reShuiFaKaiDu_MAX                           1000
#define JK_XF_reShuiFaKaiDu_LEN                           2
#define JK_XF_xinFengWenDU_RATIO                         1
#define JK_XF_xinFengWenDU_ADDITION                      0
#define JK_XF_xinFengWenDU_MIN                           0
#define JK_XF_xinFengWenDU_MAX                           1000
#define JK_XF_xinFengWenDU_LEN                           2
#define JK_XF_jiaShiQIKaiDu_RATIO                         1
#define JK_XF_jiaShiQIKaiDu_ADDITION                      0
#define JK_XF_jiaShiQIKaiDu_MIN                           0
#define JK_XF_jiaShiQIKaiDu_MAX                           1000
#define JK_XF_jiaShiQIKaiDu_LEN                           2
#define JK_XF_beiYong_RATIO                         1
#define JK_XF_beiYong_ADDITION                      0
#define JK_XF_beiYong_MIN                           0
#define JK_XF_beiYong_MAX                           65535
#define JK_XF_beiYong_LEN                           2

/**@} */


/** Writable data points Boolean and enumerated variables occupy byte size */
#define COUNT_BIT 7



/** Read-only data points Boolean and enumerated variables occupy byte size */
#define COUNT_R_BIT 7

#define DATAPOINT_FLAG_LEN sizeof(dataPointFlags_t)		 ///< All data points FLAG occupies the maximum number of bytes


/** Event enumeration */
typedef enum
{
  WIFI_SOFTAP = 0x00,                               ///< WiFi SOFTAP configuration event
  WIFI_AIRLINK,                                     ///< WiFi module AIRLINK configuration event
  WIFI_STATION,                                     ///< WiFi module STATION configuration event
  WIFI_OPEN_BINDING,                                ///< The WiFi module opens the binding event
  WIFI_CLOSE_BINDING,                               ///< The WiFi module closes the binding event
  WIFI_CON_ROUTER,                                  ///< The WiFi module is connected to a routing event
  WIFI_DISCON_ROUTER,                               ///< The WiFi module has been disconnected from the routing event
  WIFI_CON_M2M,                                     ///< The WiFi module has a server M2M event
  WIFI_DISCON_M2M,                                  ///< The WiFi module has been disconnected from the server M2M event
  WIFI_OPEN_TESTMODE,                               ///< The WiFi module turns on the test mode event
  WIFI_CLOSE_TESTMODE,                              ///< The WiFi module turns off the test mode event
  WIFI_CON_APP,                                     ///< The WiFi module connects to the APP event
  WIFI_DISCON_APP,                                  ///< The WiFi module disconnects the APP event
  WIFI_RSSI,                                        ///< WiFi module RSSI event
  WIFI_NTP,                                         ///< Network time event
  MODULE_INFO,                                      ///< Module information event
  TRANSPARENT_DATA,                                 ///< Transparency events
  EVENT_TYPE_MAX                                    ///< Enumerate the number of members to calculate (user accidentally deleted)
} EVENT_TYPE_T;


/** P0 command command code*/
typedef enum
{
    ACTION_CONTROL_DEVICE       = 0x11,             ///< Protocol 4.10 WiFi Module Control Device WiFi Module Send
    ACTION_READ_DEV_STATUS      = 0x12,             ///< Protocol 4.8 WiFi Module Reads the current status of the device WiFi module sent
    ACTION_READ_DEV_STATUS_ACK  = 0x13,             ///< Protocol 4.8 WiFi Module Read Device Current Status Device MCU Reply
    ACTION_REPORT_DEV_STATUS    = 0X14,             ///< Protocol 4.9 device MCU to the WiFi module to actively report the current status of the device to send the MCU
    ACTION_W2D_TRANSPARENT_DATA = 0x05,             ///< WiFi to device MCU transparent
    ACTION_D2W_TRANSPARENT_DATA = 0x06,             ///< Device MCU to WiFi
} actionType_t;

/** Protocol network time structure */
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint32_t ntp;
}protocolTime_t;

     

/** WiFi Module configuration parameters*/
typedef enum
{
  WIFI_RESET_MODE = 0x00,                           ///< WIFI module reset
  WIFI_SOFTAP_MODE,                                 ///< WIFI module softAP modeF
  WIFI_AIRLINK_MODE,                                ///< WIFI module AirLink mode
  WIFI_PRODUCTION_TEST,                             ///< MCU request WiFi module into production test mode
  WIFI_NINABLE_MODE,                                ///< MCU request module to enter binding mode
  WIFI_REBOOT_MODE,                                 ///< MCU request module reboot  
}WIFI_MODE_TYPE_T;                                

/** The protocol event type*/
typedef enum
{
  STATELESS_TYPE = 0x00,                            ///< Stateless type
  ACTION_CONTROL_TYPE,                              ///< Protocol 4.10 :WiFi module control device event
  WIFI_STATUS_TYPE,                                 ///< Protocol 4.5 :WiFi module inform the device MCU of the change event of the WiFi module status
  ACTION_W2D_TRANSPARENT_TYPE,                      ///< Protocol WiFi to device MCU transparent event
  GET_NTP_TYPE,                                     ///< Protocol 4.13 :The MCU requests access to the network time event
  GET_MODULEINFO_TYPE,                              ///< Protocol 4.9 :The MCU get module information event
  PROTOCOL_EVENT_TYPE_MAX                           ///< Count enumerated member (User donot delete)
} PROTOCOL_EVENT_TYPE_T;
     
/** Protocol command code */                                   
typedef enum                               
{                                                   
    CMD_GET_DEVICE_INTO             = 0x01,         ///< Protocol：3.1 
    ACK_GET_DEVICE_INFO             = 0x02,         ///< Protocol：3.1 
            
    CMD_ISSUED_P0                   = 0x03,         ///< Protocol：3.2 3.3 
    ACK_ISSUED_P0                   = 0x04,         ///< Protocol：3.2 3.3 
            
    CMD_REPORT_P0                   = 0x05,         ///< Protocol：3.4 
    ACK_REPORT_P0                   = 0x06,         ///< Protocol：3.4 
            
    CMD_HEARTBEAT                   = 0x07,         ///< Protocol：3.5 
    ACK_HEARTBEAT                   = 0x08,         ///< Protocol：3.5 
            
    CMD_WIFI_CONFIG                 = 0x09,         ///< Protocol：3.6 
    ACK_WIFI_CONFIG                 = 0x0A,         ///< Protocol：3.6 
            
    CMD_SET_DEFAULT                 = 0x0B,         ///< Protocol：3.7 
    ACK_SET_DEFAULT                 = 0x0C,         ///< Protocol：3.7 
            
    CMD_WIFISTATUS                  = 0x0D,         ///< Protocol：3.8 
    ACK_WIFISTATUS                  = 0x0E,         ///< Protocol：3.8 
        
    CMD_MCU_REBOOT                  = 0x0F,         ///< Protocol：4.1 
    ACK_MCU_REBOOT                  = 0x10,         ///< Protocol：4.1 
            
    CMD_ERROR_PACKAGE               = 0x11,         ///< Protocol：3.9 
    ACK_ERROR_PACKAGE               = 0x12,         ///< Protocol：3.9 

    CMD_PRODUCTION_TEST             = 0x13,         ///< Protocol：
    ACK_PRODUCTION_TEST             = 0x14,         ///< Protocol：

    CMD_NINABLE_MODE                = 0x15,         ///< Protocol：3.10
    ACK_NINABLE_MODE                = 0x16,         ///< Protocol：3.10

    CMD_GET_NTP                     = 0x17,         ///< Protocol：4.3 
    ACK_GET_NTP                     = 0x18,         ///< Protocol：4.3 


    CMD_ASK_BIGDATA                 = 0x19,         ///< Protocol：4.4
    ACK_ASK_BIGDATA                 = 0x1A,         ///< Protocol：4.4

    CMD_BIGDATA_READY               = 0x1B,         ///< Protocol：4.5
    ACK_BIGDATA_READY               = 0x1C,         ///< Protocol：4.5

    CMD_BIGDATA_SEND                = 0x1D,         ///< Protocol：4.6
    ACK_BIGDATA_SEND                = 0x1E,         ///< Protocol：4.6

    CMD_S_STOP_BIGDATA_SEND         = 0x1F,         ///< Protocol：4.7
    ACK_S_STOP_BIGDATA_SEND         = 0x20,         ///< Protocol：4.7

    CMD_D_STOP_BIGDATA_SEND         = 0x27,         ///< Protocol：4.8
    ACK_D_STOP_BIGDATA_SEND         = 0x28,         ///< Protocol：4.8

    CMD_ASK_MODULE_INFO             = 0x21,         ///< Protocol：4.9
    ACK_ASK_MODULE_INFO             = 0x22,         ///< Protocol：4.9

    CMD_ASK_AFFAIR_HANDLE           = 0x23,         ///< Protocol：4.10
    ACK_ASK_AFFAIR_HANDLE           = 0x24,         ///< Protocol：4.10

    CMD_AFFAIR_RESULT               = 0x25,         ///< Protocol：4.10
    ACK_AFFAIR_RESULT               = 0x26,         ///< Protocol：4.10

    CMD_REBOOT_MODULE               = 0x29,         ///< Protocol：3.11
    ACK_REBOOT_MODULE               = 0x2A,         ///< Protocol：3.11

    CMD_CONNECT_M2M                 = 0x2D,         ///< Protocol：for Virtualization
    ACK_CONNECT_M2M                 = 0x2E,         ///< Protocol：for Virtualization

    CMD_CONNECT_M2M_BACK            = 0x2F,         ///< Protocol：for Virtualization
    ACK_CONNECT_M2M_BACK            = 0x30,         ///< Protocol：for Virtualization

    CMD_UPLOAD_DATA                 = 0x31,         ///< Protocol：for Virtualization
    ACK_UPLOAD_DATA                 = 0x32,         ///< Protocol：for Virtualization

    CMD_UPLOAD_DATA_BACK            = 0x33,         ///< Protocol：for Virtualization
    ACK_UPLOAD_DATA_BACK            = 0x34,         ///< Protocol：for Virtualization

    CMD_DISCONNECT_M2M              = 0x35,         ///< Protocol：for Virtualization
    ACK_DISCONNECT_M2M              = 0x36,         ///< Protocol：for Virtualization

    CMD_DISCONNECT_M2M_BACK         = 0x37,         ///< Protocol：for Virtualization
    ACK_DISCONNECT_M2M_BACK         = 0x38,         ///< Protocol：for Virtualization

    CMD_RESET_SIMULATOR             = 0x39,         ///< Protocol：for Virtualization
    ACK_RESET_SIMULATOR             = 0x3A,         ///< Protocol：for Virtualization

    CMD_RESET_SIMULATOR_BACK        = 0x3B,         ///< Protocol：for Virtualization
    ACK_RESET_SIMULATOR_BACK        = 0x3C,         ///< Protocol：for Virtualization
} PROTOCOL_CMDTYPE;                                                                                  
                        
/** Illegal message type*/  
typedef enum
{
    ERROR_ACK_SUM = 0x01,                           ///< check error
    ERROR_CMD     = 0x02,                           ///< Command code error
    ERROR_OTHER   = 0x03,                           ///< other
} errorPacketsType_t;

typedef enum
{
    EXE_SUCESS                      = 0x00,
    EXE_FAILE                       = 0x01,
} execute_result;  

#pragma pack(1)

/** User Area Device State Structure */
typedef struct {
  bool valueJK_1_fengJiYiQiDong;
  bool valueJK_1_zhiBanStatus;
  bool valueJK_1_dianJiaRe1;
  bool valueJK_1_dianJiaRe2;
  bool valueJK_1_dianJiaRe3;
  bool valueJK_1_fengJiStatus;
  bool valueJK_1_shouZiDong;
  bool valueJK_1_dongXiaJi;
  bool valueJK_1_zhongXiaoBaoJing;
  bool valueJK_1_dianJiaReGaoWen;
  bool valueJK_1_fengJiQueFeng;
  bool valueJK_1_paiFengJiYiQiDong;
  bool valueJK_1_diWenPanGuan;
  bool valueJK_1_mieJunYunXing;
  bool valueJK_2_fengJiYiQiDong;
  bool valueJK_2_zhiBanStatus;
  bool valueJK_2_dianJiaRe1;
  bool valueJK_2_dianJiaRe2;
  bool valueJK_2_dianJiaRe3;
  bool valueJK_2_fengJiStatus;
  bool valueJK_2_shouZiDong;
  bool valueJK_2_dongXiaJi;
  bool valueJK_2_zhongXiaoBaoJing;
  bool valueJK_2_dianJiaReGaoWen;
  bool valueJK_2_fengJiQueFeng;
  bool valueJK_2_paiFengJiYiQiDong;
  bool valueJK_2_diWenPanGuan;
  bool valueJK_2_mieJunYunXing;
  bool valueJK_3_fengJiYiQiDong;
  bool valueJK_3_zhiBanStatus;
  bool valueJK_3_dianJiaRe1;
  bool valueJK_3_dianJiaRe2;
  bool valueJK_3_dianJiaRe3;
  bool valueJK_3_fengJiStatus;
  bool valueJK_3_shouZiDong;
  bool valueJK_3_dongXiaJi;
  bool valueJK_3_zhongXiaoBaoJing;
  bool valueJK_3_dianJiaReGaoWen;
  bool valueJK_3_fengJiQueFeng;
  bool valueJK_3_paiFengJiYiQiDong;
  bool valueJK_3_diWenPanGuan;
  bool valueJK_3_mieJunYunXing;
  bool valueJK_XF_fengJiYiQiDong;
  bool valueJK_XF_zhiBanStatus;
  bool valueJK_XF_dianJiaRe1;
  bool valueJK_XF_dianJiaRe2;
  bool valueJK_XF_dianJiaRe3;
  bool valueJK_XF_fengJiStatus;
  bool valueJK_XF_shouZiDong;
  bool valueJK_XF_dongXiaJi;
  bool valueJK_XF_zhongXiaoBaoJing;
  bool valueJK_XF_dianJiaReGaoWen;
  bool valueJK_XF_fengJiQueFeng;
  bool valueJK_XF_paiFengJiYiQiDong;
  bool valueJK_XF_diWenPanGuan;
  bool valueJK_XF_mieJunYunXing;
  uint32_t valueJK_1_mianBanTongXunZhuangTai1;
  uint32_t valueJK_1_mianBanTongXunZhuangTai2;
  uint32_t valueJK_1_mianBanTongXunZhuangTai3;
  uint32_t valueJK_2_mianBanTongXunZhuangTai1;
  uint32_t valueJK_2_mianBanTongXunZhuangTai2;
  uint32_t valueJK_2_mianBanTongXunZhuangTai3;
  uint32_t valueJK_3_mianBanTongXunZhuangTai1;
  uint32_t valueJK_3_mianBanTongXunZhuangTai2;
  uint32_t valueJK_3_mianBanTongXunZhuangTai3;
  uint32_t valueJK_XF_mianBanTongXunZhuangTai1;
  uint32_t valueJK_XF_mianBanTongXunZhuangTai2;
  uint32_t valueJK_XF_mianBanTongXunZhuangTai3;
  uint32_t valueJK_1_tempReal;
  uint32_t valueJK_1_humiReal;
  uint32_t valueJK_1_tempSet;
  uint32_t valueJK_1_humiSet;
  uint32_t valueJK_1_lengShuiFaKaiDu;
  uint32_t valueJK_1_reShuiFaKaiDu;
  uint32_t valueJK_1_xinFengWenDU;
  uint32_t valueJK_1_jiaShiQIKaiDu;
  uint32_t valueJK_1_beiYong;
  uint32_t valueJK_2_tempReal;
  uint32_t valueJK_2_humiReal;
  uint32_t valueJK_2_tempSet;
  uint32_t valueJK_2_humiSet;
  uint32_t valueJK_2_lengShuiFaKaiDu;
  uint32_t valueJK_2_reShuiFaKaiDu;
  uint32_t valueJK_2_xinFengWenDU;
  uint32_t valueJK_2_jiaShiQIKaiDu;
  uint32_t valueJK_2_beiYong;
  uint32_t valueJK_3_tempReal;
  uint32_t valueJK_3_humiReal;
  uint32_t valueJK_3_tempSet;
  uint32_t valueJK_3_humiSet;
  uint32_t valueJK_3_lengShuiFaKaiDu;
  uint32_t valueJK_3_reShuiFaKaiDu;
  uint32_t valueJK_3_xinFengWenDU;
  uint32_t valueJK_3_jiaShiQIKaiDu;
  uint32_t valueJK_3_beiYong;
  uint32_t valueJK_XF_tempReal;
  uint32_t valueJK_XF_humiReal;
  uint32_t valueJK_XF_tempSet;
  uint32_t valueJK_XF_humiSet;
  uint32_t valueJK_XF_lengShuiFaKaiDu;
  uint32_t valueJK_XF_reShuiFaKaiDu;
  uint32_t valueJK_XF_xinFengWenDU;
  uint32_t valueJK_XF_jiaShiQIKaiDu;
  uint32_t valueJK_XF_beiYong;
} dataPoint_t;

/** User Area Device State Structure */
typedef struct {
  uint8_t flagJK_1_fengJiYiQiDong:1;
  uint8_t flagJK_1_zhiBanStatus:1;
  uint8_t flagJK_1_dianJiaRe1:1;
  uint8_t flagJK_1_dianJiaRe2:1;
  uint8_t flagJK_1_dianJiaRe3:1;
  uint8_t flagJK_1_fengJiStatus:1;
  uint8_t flagJK_1_shouZiDong:1;
  uint8_t flagJK_1_dongXiaJi:1;
  uint8_t flagJK_1_zhongXiaoBaoJing:1;
  uint8_t flagJK_1_dianJiaReGaoWen:1;
  uint8_t flagJK_1_fengJiQueFeng:1;
  uint8_t flagJK_1_paiFengJiYiQiDong:1;
  uint8_t flagJK_1_diWenPanGuan:1;
  uint8_t flagJK_1_mieJunYunXing:1;
  uint8_t flagJK_2_fengJiYiQiDong:1;
  uint8_t flagJK_2_zhiBanStatus:1;
  uint8_t flagJK_2_dianJiaRe1:1;
  uint8_t flagJK_2_dianJiaRe2:1;
  uint8_t flagJK_2_dianJiaRe3:1;
  uint8_t flagJK_2_fengJiStatus:1;
  uint8_t flagJK_2_shouZiDong:1;
  uint8_t flagJK_2_dongXiaJi:1;
  uint8_t flagJK_2_zhongXiaoBaoJing:1;
  uint8_t flagJK_2_dianJiaReGaoWen:1;
  uint8_t flagJK_2_fengJiQueFeng:1;
  uint8_t flagJK_2_paiFengJiYiQiDong:1;
  uint8_t flagJK_2_diWenPanGuan:1;
  uint8_t flagJK_2_mieJunYunXing:1;
  uint8_t flagJK_3_fengJiYiQiDong:1;
  uint8_t flagJK_3_zhiBanStatus:1;
  uint8_t flagJK_3_dianJiaRe1:1;
  uint8_t flagJK_3_dianJiaRe2:1;
  uint8_t flagJK_3_dianJiaRe3:1;
  uint8_t flagJK_3_fengJiStatus:1;
  uint8_t flagJK_3_shouZiDong:1;
  uint8_t flagJK_3_dongXiaJi:1;
  uint8_t flagJK_3_zhongXiaoBaoJing:1;
  uint8_t flagJK_3_dianJiaReGaoWen:1;
  uint8_t flagJK_3_fengJiQueFeng:1;
  uint8_t flagJK_3_paiFengJiYiQiDong:1;
  uint8_t flagJK_3_diWenPanGuan:1;
  uint8_t flagJK_3_mieJunYunXing:1;
  uint8_t flagJK_XF_fengJiYiQiDong:1;
  uint8_t flagJK_XF_zhiBanStatus:1;
  uint8_t flagJK_XF_dianJiaRe1:1;
  uint8_t flagJK_XF_dianJiaRe2:1;
  uint8_t flagJK_XF_dianJiaRe3:1;
  uint8_t flagJK_XF_fengJiStatus:1;
  uint8_t flagJK_XF_shouZiDong:1;
  uint8_t flagJK_XF_dongXiaJi:1;
  uint8_t flagJK_XF_zhongXiaoBaoJing:1;
  uint8_t flagJK_XF_dianJiaReGaoWen:1;
  uint8_t flagJK_XF_fengJiQueFeng:1;
  uint8_t flagJK_XF_paiFengJiYiQiDong:1;
  uint8_t flagJK_XF_diWenPanGuan:1;
  uint8_t flagJK_XF_mieJunYunXing:1;
  uint8_t flagJK_1_mianBanTongXunZhuangTai1:1;
  uint8_t flagJK_1_mianBanTongXunZhuangTai2:1;
  uint8_t flagJK_1_mianBanTongXunZhuangTai3:1;
  uint8_t flagJK_2_mianBanTongXunZhuangTai1:1;
  uint8_t flagJK_2_mianBanTongXunZhuangTai2:1;
  uint8_t flagJK_2_mianBanTongXunZhuangTai3:1;
  uint8_t flagJK_3_mianBanTongXunZhuangTai1:1;
  uint8_t flagJK_3_mianBanTongXunZhuangTai2:1;
  uint8_t flagJK_3_mianBanTongXunZhuangTai3:1;
  uint8_t flagJK_XF_mianBanTongXunZhuangTai1:1;
  uint8_t flagJK_XF_mianBanTongXunZhuangTai2:1;
  uint8_t flagJK_XF_mianBanTongXunZhuangTai3:1;
  uint8_t flagJK_1_tempReal:1;
  uint8_t flagJK_1_humiReal:1;
  uint8_t flagJK_1_tempSet:1;
  uint8_t flagJK_1_humiSet:1;
  uint8_t flagJK_1_lengShuiFaKaiDu:1;
  uint8_t flagJK_1_reShuiFaKaiDu:1;
  uint8_t flagJK_1_xinFengWenDU:1;
  uint8_t flagJK_1_jiaShiQIKaiDu:1;
  uint8_t flagJK_1_beiYong:1;
  uint8_t flagJK_2_tempReal:1;
  uint8_t flagJK_2_humiReal:1;
  uint8_t flagJK_2_tempSet:1;
  uint8_t flagJK_2_humiSet:1;
  uint8_t flagJK_2_lengShuiFaKaiDu:1;
  uint8_t flagJK_2_reShuiFaKaiDu:1;
  uint8_t flagJK_2_xinFengWenDU:1;
  uint8_t flagJK_2_jiaShiQIKaiDu:1;
  uint8_t flagJK_2_beiYong:1;
  uint8_t flagJK_3_tempReal:1;
  uint8_t flagJK_3_humiReal:1;
  uint8_t flagJK_3_tempSet:1;
  uint8_t flagJK_3_humiSet:1;
  uint8_t flagJK_3_lengShuiFaKaiDu:1;
  uint8_t flagJK_3_reShuiFaKaiDu:1;
  uint8_t flagJK_3_xinFengWenDU:1;
  uint8_t flagJK_3_jiaShiQIKaiDu:1;
  uint8_t flagJK_3_beiYong:1;
  uint8_t flagJK_XF_tempReal:1;
  uint8_t flagJK_XF_humiReal:1;
  uint8_t flagJK_XF_tempSet:1;
  uint8_t flagJK_XF_humiSet:1;
  uint8_t flagJK_XF_lengShuiFaKaiDu:1;
  uint8_t flagJK_XF_reShuiFaKaiDu:1;
  uint8_t flagJK_XF_xinFengWenDU:1;
  uint8_t flagJK_XF_jiaShiQIKaiDu:1;
  uint8_t flagJK_XF_beiYong:1;
} dataPointFlags_t;

/** Corresponding to the protocol "4.9 device MCU to WiFi module active reporting of the current state" in the device state "dev_status (11B)" */ 
typedef struct {
  uint8_t bitFeildBuf[COUNT_BIT];
  uint8_t valueJK_1_mianBanTongXunZhuangTai1;
  uint8_t valueJK_1_mianBanTongXunZhuangTai2;
  uint8_t valueJK_1_mianBanTongXunZhuangTai3;
  uint8_t valueJK_2_mianBanTongXunZhuangTai1;
  uint8_t valueJK_2_mianBanTongXunZhuangTai2;
  uint8_t valueJK_2_mianBanTongXunZhuangTai3;
  uint8_t valueJK_3_mianBanTongXunZhuangTai1;
  uint8_t valueJK_3_mianBanTongXunZhuangTai2;
  uint8_t valueJK_3_mianBanTongXunZhuangTai3;
  uint8_t valueJK_XF_mianBanTongXunZhuangTai1;
  uint8_t valueJK_XF_mianBanTongXunZhuangTai2;
  uint8_t valueJK_XF_mianBanTongXunZhuangTai3;
  uint16_t valueJK_1_tempReal;
  uint16_t valueJK_1_humiReal;
  uint16_t valueJK_1_tempSet;
  uint16_t valueJK_1_humiSet;
  uint16_t valueJK_1_lengShuiFaKaiDu;
  uint16_t valueJK_1_reShuiFaKaiDu;
  uint16_t valueJK_1_xinFengWenDU;
  uint16_t valueJK_1_jiaShiQIKaiDu;
  uint16_t valueJK_1_beiYong;
  uint16_t valueJK_2_tempReal;
  uint16_t valueJK_2_humiReal;
  uint16_t valueJK_2_tempSet;
  uint16_t valueJK_2_humiSet;
  uint16_t valueJK_2_lengShuiFaKaiDu;
  uint16_t valueJK_2_reShuiFaKaiDu;
  uint16_t valueJK_2_xinFengWenDU;
  uint16_t valueJK_2_jiaShiQIKaiDu;
  uint16_t valueJK_2_beiYong;
  uint16_t valueJK_3_tempReal;
  uint16_t valueJK_3_humiReal;
  uint16_t valueJK_3_tempSet;
  uint16_t valueJK_3_humiSet;
  uint16_t valueJK_3_lengShuiFaKaiDu;
  uint16_t valueJK_3_reShuiFaKaiDu;
  uint16_t valueJK_3_xinFengWenDU;
  uint16_t valueJK_3_jiaShiQIKaiDu;
  uint16_t valueJK_3_beiYong;
  uint16_t valueJK_XF_tempReal;
  uint16_t valueJK_XF_humiReal;
  uint16_t valueJK_XF_tempSet;
  uint16_t valueJK_XF_humiSet;
  uint16_t valueJK_XF_lengShuiFaKaiDu;
  uint16_t valueJK_XF_reShuiFaKaiDu;
  uint16_t valueJK_XF_xinFengWenDU;
  uint16_t valueJK_XF_jiaShiQIKaiDu;
  uint16_t valueJK_XF_beiYong;
} devStatus_t;


                
/** Event queue structure */                               
typedef struct {                           
    uint8_t num;                                    ///< Number of queue member
    uint8_t event[EVENT_TYPE_MAX];                  ///< Queue member event content
}eventInfo_t;


                            
/** wifiSignal strength structure */                       
typedef struct {                           
    uint8_t rssi;                                   ///< WIFI signal strength
}moduleStatusInfo_t;                                

/** Protocol standard header structure */
typedef struct
{
    uint8_t                 head[2];                ///< The head is 0xFFFF
    uint16_t                len;                    ///< From cmd to the end of the entire packet occupied by the number of bytes
    uint8_t                 cmd;                    ///< command
    uint8_t                 sn;                     ///< 
    uint8_t                 flags[2];               ///< flag,default is 0
} protocolHead_t;

/** 4.1 WiFi module requests the device information protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 protocolVer[8];         ///< Protocol version
    uint8_t                 p0Ver[8];               ///< p0 Protocol version
    uint8_t                 hardVer[8];             ///< Hardware version
    uint8_t                 softVer[8];             ///< Software version
    uint8_t                 productKey[32];         ///< Product key
    uint16_t                ninableTime;            ///< Binding time(second)
    uint8_t                 devAttr[8];             ///< Device attribute
    uint8_t                 productSecret[32];      ///< Product secret
    uint8_t                 sum;                    ///< checksum
} protocolDeviceInfo_t;

/** Protocol common data frame(4.2、4.4、4.6、4.9、4.10) protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 sum;                    ///< checksum
} protocolCommon_t;

/** 4.3 The device MCU informs the WiFi module of the configuration mode  protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 cfgMode;                ///< Configuration parameters
    uint8_t                 sum;                    ///< checksum
} protocolCfgMode_t;

/** 4.13 The MCU requests the network time  protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 time[7];                ///< Hardware version
    uint8_t                 ntp_time[4];            ///< Software version
    uint8_t                 sum;                    ///< checksum
} protocolUTT_t;

/** WiFi module working status*/
typedef union
{
    uint16_t                value;
    struct
    {
        uint16_t            softap:1;     
        uint16_t            station:1;    
        uint16_t            onboarding:1; 
        uint16_t            binding:1;    
        uint16_t            con_route:1;  
        uint16_t            con_m2m:1;    
        uint16_t            reserve1:2;   
        uint16_t            rssi:3;       
        uint16_t            app:1;        
        uint16_t            test:1;       
        uint16_t            reserve2:3;   
    }types; 
    
} wifiStatus_t;

/** WiFi status type :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    wifiStatus_t            ststus;                 ///< WIFI status
    uint8_t                 sum;                    ///< checksum
} protocolWifiStatus_t;

/** Protocol common data frame(4.9) :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 type;                   ///< Information Type
    uint8_t                 sum;                    ///< checksum
} protocolGetModuleInfo_t;

typedef struct
{
    uint8_t                 moduleType;             ///< Information Type
    uint8_t                 serialVer[8];           ///< Serial port protocol version
    uint8_t                 hardVer[8];             ///< Hardware version
    uint8_t                 softVer[8];             ///< Software version
    uint8_t                 mac[16];                ///< mac 
    uint8_t                 ip[16];                 ///< ip
    uint8_t                 devAttr[8];             ///< Device attribute
} moduleInfo_t;

/** Protocol common data frame(4.9) :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    moduleInfo_t            wifiModuleInfo;         ///< WIFI module information
    uint8_t                 sum;                    ///< checksum
} protocolModuleInfo_t;


/** GPRS information of base station */
typedef struct
{
    uint16_t                    LAC_ID;             ///<LAC area ID
    uint16_t                    CellID;             ///<Base station ID
    uint8_t                     RSSI;               ///<Signal strength of base station
} gprsCellInfo_t;


/** 3.19 The basic information of the GPRS communication module  */
typedef struct
{
    uint8_t                 Type;//2G/3g/4g
    uint8_t                 Pro_ver[8];//Universal serial port protocol version
    uint8_t                 Hard_ver[8];//Hardware version
    uint8_t                 Soft_ver[8];//Software version
    uint8_t                 Device_attribute[8];//Device attribute
    uint8_t                 IMEI[16];//string
    uint8_t                 IMSI[16];//string
    uint8_t                 MCC[8];//Mobile country code
    uint8_t                 MNC[8];//Mobile network code
    uint8_t                 CellNum;//Number of base station
    uint8_t                 CellInfoLen;//Information length of base station 
    gprsCellInfo_t          GPRS_CellINFO[CELLNUMMAX];
}gprsInfo_t;

/** 4.7 Illegal message notification :protocol structure*/
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 error;                  ///< error value
    uint8_t                 sum;                    ///< checksum
} protocolErrorType_t;


/** P0 message header */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 action;                 ///< p0 command 
} protocolP0Head_t;


/** protocol “4.9 The device MCU reports the current status to the WiFi module” device status "dev_status(11B)"  */ 
typedef struct {
                     
    devStatus_t devStatus;                          ///< Stores the device status data
}gizwitsReport_t;

/** resend strategy structure */
typedef struct {
    uint8_t                 num;                    ///< resend times
    uint8_t                 flag;                   ///< 1,Indicates that there is a need to wait for the ACK;0,Indicates that there is no need to wait for the ACK
    uint8_t                 buf[MAX_PACKAGE_LEN];   ///< resend data buffer
    uint16_t                dataLen;                ///< resend data length
    uint32_t                sendTime;               ///< resend time
} protocolWaitAck_t;
                                                                                


typedef struct {                           
    dataPointFlags_t  devDatapointFlag;             ///< Datapoint Flag , All datapoints 
    devStatus_t devStatus;                          ///< All datapoints data
}gizwitsElongateP0Form_t;  

typedef struct {                           
    uint8_t action;                                 ///< P0 action 
    uint8_t gizdata[sizeof(gizwitsElongateP0Form_t)];  ///< Max buffer ,  Can hold all datapoints value 
}gizwitsP0Max_t;        

/** Protocol main and very important struct */
typedef struct
{
    uint8_t issuedFlag;                             ///< P0 action type
    uint8_t protocolBuf[MAX_PACKAGE_LEN];           ///< Protocol data handle buffer
    uint8_t transparentBuff[MAX_PACKAGE_LEN];       ///< Transparent data storage area
    uint32_t transparentLen;                        ///< Transmission data length
    
    uint32_t sn;                                    ///< Message SN
    uint32_t timerMsCount;                          ///< Timer Count 
    protocolWaitAck_t waitAck;                      ///< Protocol wait ACK data structure
    
    eventInfo_t issuedProcessEvent;                 ///< Control events
    eventInfo_t wifiStatusEvent;                    ///< WIFI Status events
    eventInfo_t NTPEvent;                           ///< NTP events
    eventInfo_t moduleInfoEvent;                    ///< Module Info events

    dataPointFlags_t  waitReportDatapointFlag;      ///< Store the data points to be reported flag
    uint8_t reportData[sizeof(gizwitsElongateP0Form_t)];    ///< Reporting actual data , Max , Can hold all datapoints value
    uint32_t reportDataLen;                         ///< Reporting actual data length

    dataPoint_t gizCurrentDataPoint;                ///< Current device datapoints status
    dataPoint_t gizLastDataPoint;                   ///< Last device datapoints status
    moduleStatusInfo_t wifiStatusData;              ///< WIFI signal intensity
    protocolTime_t TimeNTP;                         ///< Network time information
#if MODULE_TYPE
    gprsInfo_t   gprsInfoNews;
#else  
    moduleInfo_t  wifiModuleNews;                   ///< WIFI module Info
#endif
    
}gizwitsProtocol_t;

#pragma pack()

/**@name Gizwits user API interface
* @{
*/

extern uint32_t gizGetTimerCount(void);

void gizwitsInit(void);
int32_t gizwitsSetMode(uint8_t mode);
void gizwitsGetNTP(void);
int32_t gizwitsHandle(dataPoint_t *currentData);
int32_t gizwitsPassthroughData(uint8_t * gizdata, uint32_t len);
void gizwitsGetModuleInfo(void);
int32_t gizPutData(uint8_t *buf, uint32_t len);

/**@} */
#ifdef __cplusplus
}
#endif 

#endif
