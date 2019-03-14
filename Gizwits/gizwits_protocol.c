/**
************************************************************
* @file         gizwits_protocol.c
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
#include "ringBuffer.h"
#include "gizwits_product.h"
#include "dataPointTools.h"

/** Protocol global variables **/
gizwitsProtocol_t gizwitsProtocol;


/**@name The serial port receives the ring buffer implementation
* @{
*/
rb_t pRb;                                               ///< Ring buffer structure variable
static uint8_t rbBuf[RB_MAX_LEN];                       ///< Ring buffer data cache buffer


/**@} */

/**
* @brief Write data to the ring buffer
* @param [in] buf        : buf adress
* @param [in] len        : byte length
* @return   correct : Returns the length of the written data
            failure : -1
*/
int32_t gizPutData(uint8_t *buf, uint32_t len)
{
    int32_t count = 0;

    if(NULL == buf)
    {
        GIZWITS_LOG("ERR: gizPutData buf is empty \n");
        return -1;
    }

    count = rbWrite(&pRb, buf, len);
    if(count != len)
    {
        GIZWITS_LOG("ERR: Failed to rbWrite \n");
        return -1;
    }

    return count;
}



/**
* @brief Protocol header initialization
*
* @param [out] head         : Protocol header pointer
*
* @return 0， success; other， failure    
*/
static int8_t gizProtocolHeadInit(protocolHead_t *head)
{
    if(NULL == head)
    {
        GIZWITS_LOG("ERR: gizProtocolHeadInit head is empty \n");
        return -1;
    }

    memset((uint8_t *)head, 0, sizeof(protocolHead_t));
    head->head[0] = 0xFF;
    head->head[1] = 0xFF;

    return 0;
}

/**
* @brief Protocol ACK check processing function
*
* @param [in] data            : data adress
* @param [in] len             : data length
*
* @return 0， suceess; other， failure
*/
static int8_t gizProtocolWaitAck(uint8_t *gizdata, uint32_t len)
{
    if(NULL == gizdata)
    {
        GIZWITS_LOG("ERR: data is empty \n");
        return -1;
    }

    memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
    memcpy((uint8_t *)gizwitsProtocol.waitAck.buf, gizdata, len);
    gizwitsProtocol.waitAck.dataLen = (uint16_t)len;
    
    gizwitsProtocol.waitAck.flag = 1;
    gizwitsProtocol.waitAck.sendTime = gizGetTimerCount();

    return 0;
}
/**
* @brief Calculates the byte size occupied by the bit
*
* @param [in] aFlag: P0 flag data
*
* @return: byte size
*/
uint32_t ICACHE_FLASH_ATTR calculateDynamicBitPartLen(dataPointFlags_t *aFlag)
{
    uint32_t bitFieldBitLen = 0,bytetmpLen= 0;
    /* Processing only writable bool Enum type data */

    if(0 == bitFieldBitLen)
    {
        bytetmpLen = 0;
    }
    else
    {
        if(0 == bitFieldBitLen%8)
        {
            bytetmpLen = bitFieldBitLen/8;
        }
        else
        {
            bytetmpLen = bitFieldBitLen/8 + 1;
        }
    }
    return bytetmpLen;
}

/**
* @brief generates "controlled events" according to protocol

* @param [in] issuedData: Controlled data
* @param [out] info: event queue
* @param [out] dataPoints: data point data
* @return 0, the implementation of success, non-0, failed
*/
static int8_t ICACHE_FLASH_ATTR gizDataPoint2Event(uint8_t *issuedData, eventInfo_t *info, dataPoint_t *dataPoints)
{

    return 0;
}


/**
* @brief contrasts the current data with the last data
*
* @param [in] cur: current data point data
* @param [in] last: last data point data
*
* @return: 0, no change in data; 1, data changes
*/
static int8_t ICACHE_FLASH_ATTR gizCheckReport(dataPoint_t *cur, dataPoint_t *last)
{
    int8_t ret = 0;
    static uint32_t lastReportTime = 0;
    uint32_t currentTime = 0;

    if((NULL == cur) || (NULL == last))
    {
        GIZWITS_LOG("gizCheckReport Error , Illegal Param\n");
        return -1;
    }
    currentTime = gizGetTimerCount();

    if(last->valueJK_1_fengJiYiQiDong != cur->valueJK_1_fengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_1_fengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_1_zhiBanStatus != cur->valueJK_1_zhiBanStatus)
    {
        GIZWITS_LOG("valueJK_1_zhiBanStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_zhiBanStatus = 1;
        ret = 1;
    }
    if(last->valueJK_1_dianJiaRe1 != cur->valueJK_1_dianJiaRe1)
    {
        GIZWITS_LOG("valueJK_1_dianJiaRe1 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe1 = 1;
        ret = 1;
    }
    if(last->valueJK_1_dianJiaRe2 != cur->valueJK_1_dianJiaRe2)
    {
        GIZWITS_LOG("valueJK_1_dianJiaRe2 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe2 = 1;
        ret = 1;
    }
    if(last->valueJK_1_dianJiaRe3 != cur->valueJK_1_dianJiaRe3)
    {
        GIZWITS_LOG("valueJK_1_dianJiaRe3 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe3 = 1;
        ret = 1;
    }
    if(last->valueJK_1_fengJiStatus != cur->valueJK_1_fengJiStatus)
    {
        GIZWITS_LOG("valueJK_1_fengJiStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiStatus = 1;
        ret = 1;
    }
    if(last->valueJK_1_shouZiDong != cur->valueJK_1_shouZiDong)
    {
        GIZWITS_LOG("valueJK_1_shouZiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_shouZiDong = 1;
        ret = 1;
    }
    if(last->valueJK_1_dongXiaJi != cur->valueJK_1_dongXiaJi)
    {
        GIZWITS_LOG("valueJK_1_dongXiaJi Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dongXiaJi = 1;
        ret = 1;
    }
    if(last->valueJK_1_zhongXiaoBaoJing != cur->valueJK_1_zhongXiaoBaoJing)
    {
        GIZWITS_LOG("valueJK_1_zhongXiaoBaoJing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_zhongXiaoBaoJing = 1;
        ret = 1;
    }
    if(last->valueJK_1_dianJiaReGaoWen != cur->valueJK_1_dianJiaReGaoWen)
    {
        GIZWITS_LOG("valueJK_1_dianJiaReGaoWen Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaReGaoWen = 1;
        ret = 1;
    }
    if(last->valueJK_1_fengJiQueFeng != cur->valueJK_1_fengJiQueFeng)
    {
        GIZWITS_LOG("valueJK_1_fengJiQueFeng Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiQueFeng = 1;
        ret = 1;
    }
    if(last->valueJK_1_paiFengJiYiQiDong != cur->valueJK_1_paiFengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_1_paiFengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_paiFengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_1_diWenPanGuan != cur->valueJK_1_diWenPanGuan)
    {
        GIZWITS_LOG("valueJK_1_diWenPanGuan Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_diWenPanGuan = 1;
        ret = 1;
    }
    if(last->valueJK_1_mieJunYunXing != cur->valueJK_1_mieJunYunXing)
    {
        GIZWITS_LOG("valueJK_1_mieJunYunXing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mieJunYunXing = 1;
        ret = 1;
    }
    if(last->valueJK_2_fengJiYiQiDong != cur->valueJK_2_fengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_2_fengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_2_zhiBanStatus != cur->valueJK_2_zhiBanStatus)
    {
        GIZWITS_LOG("valueJK_2_zhiBanStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_zhiBanStatus = 1;
        ret = 1;
    }
    if(last->valueJK_2_dianJiaRe1 != cur->valueJK_2_dianJiaRe1)
    {
        GIZWITS_LOG("valueJK_2_dianJiaRe1 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe1 = 1;
        ret = 1;
    }
    if(last->valueJK_2_dianJiaRe2 != cur->valueJK_2_dianJiaRe2)
    {
        GIZWITS_LOG("valueJK_2_dianJiaRe2 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe2 = 1;
        ret = 1;
    }
    if(last->valueJK_2_dianJiaRe3 != cur->valueJK_2_dianJiaRe3)
    {
        GIZWITS_LOG("valueJK_2_dianJiaRe3 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe3 = 1;
        ret = 1;
    }
    if(last->valueJK_2_fengJiStatus != cur->valueJK_2_fengJiStatus)
    {
        GIZWITS_LOG("valueJK_2_fengJiStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiStatus = 1;
        ret = 1;
    }
    if(last->valueJK_2_shouZiDong != cur->valueJK_2_shouZiDong)
    {
        GIZWITS_LOG("valueJK_2_shouZiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_shouZiDong = 1;
        ret = 1;
    }
    if(last->valueJK_2_dongXiaJi != cur->valueJK_2_dongXiaJi)
    {
        GIZWITS_LOG("valueJK_2_dongXiaJi Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dongXiaJi = 1;
        ret = 1;
    }
    if(last->valueJK_2_zhongXiaoBaoJing != cur->valueJK_2_zhongXiaoBaoJing)
    {
        GIZWITS_LOG("valueJK_2_zhongXiaoBaoJing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_zhongXiaoBaoJing = 1;
        ret = 1;
    }
    if(last->valueJK_2_dianJiaReGaoWen != cur->valueJK_2_dianJiaReGaoWen)
    {
        GIZWITS_LOG("valueJK_2_dianJiaReGaoWen Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaReGaoWen = 1;
        ret = 1;
    }
    if(last->valueJK_2_fengJiQueFeng != cur->valueJK_2_fengJiQueFeng)
    {
        GIZWITS_LOG("valueJK_2_fengJiQueFeng Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiQueFeng = 1;
        ret = 1;
    }
    if(last->valueJK_2_paiFengJiYiQiDong != cur->valueJK_2_paiFengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_2_paiFengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_paiFengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_2_diWenPanGuan != cur->valueJK_2_diWenPanGuan)
    {
        GIZWITS_LOG("valueJK_2_diWenPanGuan Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_diWenPanGuan = 1;
        ret = 1;
    }
    if(last->valueJK_2_mieJunYunXing != cur->valueJK_2_mieJunYunXing)
    {
        GIZWITS_LOG("valueJK_2_mieJunYunXing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mieJunYunXing = 1;
        ret = 1;
    }
    if(last->valueJK_3_fengJiYiQiDong != cur->valueJK_3_fengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_3_fengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_3_zhiBanStatus != cur->valueJK_3_zhiBanStatus)
    {
        GIZWITS_LOG("valueJK_3_zhiBanStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_zhiBanStatus = 1;
        ret = 1;
    }
    if(last->valueJK_3_dianJiaRe1 != cur->valueJK_3_dianJiaRe1)
    {
        GIZWITS_LOG("valueJK_3_dianJiaRe1 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe1 = 1;
        ret = 1;
    }
    if(last->valueJK_3_dianJiaRe2 != cur->valueJK_3_dianJiaRe2)
    {
        GIZWITS_LOG("valueJK_3_dianJiaRe2 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe2 = 1;
        ret = 1;
    }
    if(last->valueJK_3_dianJiaRe3 != cur->valueJK_3_dianJiaRe3)
    {
        GIZWITS_LOG("valueJK_3_dianJiaRe3 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe3 = 1;
        ret = 1;
    }
    if(last->valueJK_3_fengJiStatus != cur->valueJK_3_fengJiStatus)
    {
        GIZWITS_LOG("valueJK_3_fengJiStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiStatus = 1;
        ret = 1;
    }
    if(last->valueJK_3_shouZiDong != cur->valueJK_3_shouZiDong)
    {
        GIZWITS_LOG("valueJK_3_shouZiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_shouZiDong = 1;
        ret = 1;
    }
    if(last->valueJK_3_dongXiaJi != cur->valueJK_3_dongXiaJi)
    {
        GIZWITS_LOG("valueJK_3_dongXiaJi Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dongXiaJi = 1;
        ret = 1;
    }
    if(last->valueJK_3_zhongXiaoBaoJing != cur->valueJK_3_zhongXiaoBaoJing)
    {
        GIZWITS_LOG("valueJK_3_zhongXiaoBaoJing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_zhongXiaoBaoJing = 1;
        ret = 1;
    }
    if(last->valueJK_3_dianJiaReGaoWen != cur->valueJK_3_dianJiaReGaoWen)
    {
        GIZWITS_LOG("valueJK_3_dianJiaReGaoWen Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaReGaoWen = 1;
        ret = 1;
    }
    if(last->valueJK_3_fengJiQueFeng != cur->valueJK_3_fengJiQueFeng)
    {
        GIZWITS_LOG("valueJK_3_fengJiQueFeng Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiQueFeng = 1;
        ret = 1;
    }
    if(last->valueJK_3_paiFengJiYiQiDong != cur->valueJK_3_paiFengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_3_paiFengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_paiFengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_3_diWenPanGuan != cur->valueJK_3_diWenPanGuan)
    {
        GIZWITS_LOG("valueJK_3_diWenPanGuan Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_diWenPanGuan = 1;
        ret = 1;
    }
    if(last->valueJK_3_mieJunYunXing != cur->valueJK_3_mieJunYunXing)
    {
        GIZWITS_LOG("valueJK_3_mieJunYunXing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mieJunYunXing = 1;
        ret = 1;
    }
    if(last->valueJK_XF_fengJiYiQiDong != cur->valueJK_XF_fengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_XF_fengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_XF_zhiBanStatus != cur->valueJK_XF_zhiBanStatus)
    {
        GIZWITS_LOG("valueJK_XF_zhiBanStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_zhiBanStatus = 1;
        ret = 1;
    }
    if(last->valueJK_XF_dianJiaRe1 != cur->valueJK_XF_dianJiaRe1)
    {
        GIZWITS_LOG("valueJK_XF_dianJiaRe1 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe1 = 1;
        ret = 1;
    }
    if(last->valueJK_XF_dianJiaRe2 != cur->valueJK_XF_dianJiaRe2)
    {
        GIZWITS_LOG("valueJK_XF_dianJiaRe2 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe2 = 1;
        ret = 1;
    }
    if(last->valueJK_XF_dianJiaRe3 != cur->valueJK_XF_dianJiaRe3)
    {
        GIZWITS_LOG("valueJK_XF_dianJiaRe3 Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe3 = 1;
        ret = 1;
    }
    if(last->valueJK_XF_fengJiStatus != cur->valueJK_XF_fengJiStatus)
    {
        GIZWITS_LOG("valueJK_XF_fengJiStatus Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiStatus = 1;
        ret = 1;
    }
    if(last->valueJK_XF_shouZiDong != cur->valueJK_XF_shouZiDong)
    {
        GIZWITS_LOG("valueJK_XF_shouZiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_shouZiDong = 1;
        ret = 1;
    }
    if(last->valueJK_XF_dongXiaJi != cur->valueJK_XF_dongXiaJi)
    {
        GIZWITS_LOG("valueJK_XF_dongXiaJi Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dongXiaJi = 1;
        ret = 1;
    }
    if(last->valueJK_XF_zhongXiaoBaoJing != cur->valueJK_XF_zhongXiaoBaoJing)
    {
        GIZWITS_LOG("valueJK_XF_zhongXiaoBaoJing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_zhongXiaoBaoJing = 1;
        ret = 1;
    }
    if(last->valueJK_XF_dianJiaReGaoWen != cur->valueJK_XF_dianJiaReGaoWen)
    {
        GIZWITS_LOG("valueJK_XF_dianJiaReGaoWen Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaReGaoWen = 1;
        ret = 1;
    }
    if(last->valueJK_XF_fengJiQueFeng != cur->valueJK_XF_fengJiQueFeng)
    {
        GIZWITS_LOG("valueJK_XF_fengJiQueFeng Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiQueFeng = 1;
        ret = 1;
    }
    if(last->valueJK_XF_paiFengJiYiQiDong != cur->valueJK_XF_paiFengJiYiQiDong)
    {
        GIZWITS_LOG("valueJK_XF_paiFengJiYiQiDong Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_paiFengJiYiQiDong = 1;
        ret = 1;
    }
    if(last->valueJK_XF_diWenPanGuan != cur->valueJK_XF_diWenPanGuan)
    {
        GIZWITS_LOG("valueJK_XF_diWenPanGuan Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_diWenPanGuan = 1;
        ret = 1;
    }
    if(last->valueJK_XF_mieJunYunXing != cur->valueJK_XF_mieJunYunXing)
    {
        GIZWITS_LOG("valueJK_XF_mieJunYunXing Changed\n");
        gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mieJunYunXing = 1;
        ret = 1;
    }

    if(last->valueJK_1_mianBanTongXunZhuangTai1 != cur->valueJK_1_mianBanTongXunZhuangTai1)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_mianBanTongXunZhuangTai1 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai1 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_mianBanTongXunZhuangTai2 != cur->valueJK_1_mianBanTongXunZhuangTai2)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_mianBanTongXunZhuangTai2 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai2 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_mianBanTongXunZhuangTai3 != cur->valueJK_1_mianBanTongXunZhuangTai3)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_mianBanTongXunZhuangTai3 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai3 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_mianBanTongXunZhuangTai1 != cur->valueJK_2_mianBanTongXunZhuangTai1)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_mianBanTongXunZhuangTai1 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai1 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_mianBanTongXunZhuangTai2 != cur->valueJK_2_mianBanTongXunZhuangTai2)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_mianBanTongXunZhuangTai2 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai2 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_mianBanTongXunZhuangTai3 != cur->valueJK_2_mianBanTongXunZhuangTai3)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_mianBanTongXunZhuangTai3 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai3 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_mianBanTongXunZhuangTai1 != cur->valueJK_3_mianBanTongXunZhuangTai1)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_mianBanTongXunZhuangTai1 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai1 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_mianBanTongXunZhuangTai2 != cur->valueJK_3_mianBanTongXunZhuangTai2)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_mianBanTongXunZhuangTai2 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai2 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_mianBanTongXunZhuangTai3 != cur->valueJK_3_mianBanTongXunZhuangTai3)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_mianBanTongXunZhuangTai3 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai3 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_mianBanTongXunZhuangTai1 != cur->valueJK_XF_mianBanTongXunZhuangTai1)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_mianBanTongXunZhuangTai1 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai1 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_mianBanTongXunZhuangTai2 != cur->valueJK_XF_mianBanTongXunZhuangTai2)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_mianBanTongXunZhuangTai2 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai2 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_mianBanTongXunZhuangTai3 != cur->valueJK_XF_mianBanTongXunZhuangTai3)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_mianBanTongXunZhuangTai3 Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai3 = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_tempReal != cur->valueJK_1_tempReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_tempReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_tempReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_humiReal != cur->valueJK_1_humiReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_humiReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_humiReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_tempSet != cur->valueJK_1_tempSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_tempSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_tempSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_humiSet != cur->valueJK_1_humiSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_humiSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_humiSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_lengShuiFaKaiDu != cur->valueJK_1_lengShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_lengShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_lengShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_reShuiFaKaiDu != cur->valueJK_1_reShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_reShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_reShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_xinFengWenDU != cur->valueJK_1_xinFengWenDU)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_xinFengWenDU Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_xinFengWenDU = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_jiaShiQIKaiDu != cur->valueJK_1_jiaShiQIKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_jiaShiQIKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_jiaShiQIKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_1_beiYong != cur->valueJK_1_beiYong)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_1_beiYong Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_1_beiYong = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_tempReal != cur->valueJK_2_tempReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_tempReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_tempReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_humiReal != cur->valueJK_2_humiReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_humiReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_humiReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_tempSet != cur->valueJK_2_tempSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_tempSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_tempSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_humiSet != cur->valueJK_2_humiSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_humiSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_humiSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_lengShuiFaKaiDu != cur->valueJK_2_lengShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_lengShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_lengShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_reShuiFaKaiDu != cur->valueJK_2_reShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_reShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_reShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_xinFengWenDU != cur->valueJK_2_xinFengWenDU)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_xinFengWenDU Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_xinFengWenDU = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_jiaShiQIKaiDu != cur->valueJK_2_jiaShiQIKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_jiaShiQIKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_jiaShiQIKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_2_beiYong != cur->valueJK_2_beiYong)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_2_beiYong Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_2_beiYong = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_tempReal != cur->valueJK_3_tempReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_tempReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_tempReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_humiReal != cur->valueJK_3_humiReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_humiReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_humiReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_tempSet != cur->valueJK_3_tempSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_tempSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_tempSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_humiSet != cur->valueJK_3_humiSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_humiSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_humiSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_lengShuiFaKaiDu != cur->valueJK_3_lengShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_lengShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_lengShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_reShuiFaKaiDu != cur->valueJK_3_reShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_reShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_reShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_xinFengWenDU != cur->valueJK_3_xinFengWenDU)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_xinFengWenDU Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_xinFengWenDU = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_jiaShiQIKaiDu != cur->valueJK_3_jiaShiQIKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_jiaShiQIKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_jiaShiQIKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_3_beiYong != cur->valueJK_3_beiYong)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_3_beiYong Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_3_beiYong = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_tempReal != cur->valueJK_XF_tempReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_tempReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_tempReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_humiReal != cur->valueJK_XF_humiReal)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_humiReal Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_humiReal = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_tempSet != cur->valueJK_XF_tempSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_tempSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_tempSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_humiSet != cur->valueJK_XF_humiSet)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_humiSet Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_humiSet = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_lengShuiFaKaiDu != cur->valueJK_XF_lengShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_lengShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_lengShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_reShuiFaKaiDu != cur->valueJK_XF_reShuiFaKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_reShuiFaKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_reShuiFaKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_xinFengWenDU != cur->valueJK_XF_xinFengWenDU)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_xinFengWenDU Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_xinFengWenDU = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_jiaShiQIKaiDu != cur->valueJK_XF_jiaShiQIKaiDu)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_jiaShiQIKaiDu Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_jiaShiQIKaiDu = 1;
            ret = 1;
        }
    }
    if(last->valueJK_XF_beiYong != cur->valueJK_XF_beiYong)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueJK_XF_beiYong Changed\n");
            gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_beiYong = 1;
            ret = 1;
        }
    }

    if(1 == ret)
    {
        lastReportTime = gizGetTimerCount();
    }

    return ret;
}

/**
* @brief User data point data is converted to wit the cloud to report data point data
*
* @param [in] dataPoints: user data point data address
* @param [out] devStatusPtr: wit the cloud data point data address
*
* @return 0, the correct return; -1, the error returned
*/
static int8_t ICACHE_FLASH_ATTR gizDataPoints2ReportData(dataPoint_t *dataPoints , uint8_t *outData,uint32_t *outDataLen)
{
    uint32_t bitFieldByteLen= 0;//Bit byte size
    uint32_t bitFieldOffset = 0;//Bit offset
    uint32_t byteFieldOffset = 0;//Byte offset
	devStatus_t devStatusTmp;//Temporary device data point variable
    uint8_t allDatapointByteBuf[sizeof(gizwitsElongateP0Form_t)];//Open up the largest data point space
    gizMemset(allDatapointByteBuf,0,sizeof(gizwitsElongateP0Form_t));

    gizMemcpy(allDatapointByteBuf,(uint8_t *)&gizwitsProtocol.waitReportDatapointFlag,DATAPOINT_FLAG_LEN);
    if(DATAPOINT_FLAG_LEN > 1)
    {
        gizByteOrderExchange(allDatapointByteBuf,DATAPOINT_FLAG_LEN);
    }
    byteFieldOffset += DATAPOINT_FLAG_LEN;//First offset the flag size of the location
        
   
    if((NULL == dataPoints) || (NULL == outData))
    {
        GIZWITS_LOG("gizDataPoints2ReportData Error , Illegal Param\n");
        return -1;
    }

    /*** Fill the bit ***/
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_fengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_fengJiYiQiDong);
        bitFieldOffset += JK_1_fengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_zhiBanStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_zhiBanStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_zhiBanStatus);
        bitFieldOffset += JK_1_zhiBanStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe1)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_dianJiaRe1_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_dianJiaRe1);
        bitFieldOffset += JK_1_dianJiaRe1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe2)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_dianJiaRe2_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_dianJiaRe2);
        bitFieldOffset += JK_1_dianJiaRe2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaRe3)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_dianJiaRe3_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_dianJiaRe3);
        bitFieldOffset += JK_1_dianJiaRe3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_fengJiStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_fengJiStatus);
        bitFieldOffset += JK_1_fengJiStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_shouZiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_shouZiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_shouZiDong);
        bitFieldOffset += JK_1_shouZiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dongXiaJi)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_dongXiaJi_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_dongXiaJi);
        bitFieldOffset += JK_1_dongXiaJi_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_zhongXiaoBaoJing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_zhongXiaoBaoJing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_zhongXiaoBaoJing);
        bitFieldOffset += JK_1_zhongXiaoBaoJing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_dianJiaReGaoWen)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_dianJiaReGaoWen_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_dianJiaReGaoWen);
        bitFieldOffset += JK_1_dianJiaReGaoWen_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_fengJiQueFeng)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_fengJiQueFeng_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_fengJiQueFeng);
        bitFieldOffset += JK_1_fengJiQueFeng_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_paiFengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_paiFengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_paiFengJiYiQiDong);
        bitFieldOffset += JK_1_paiFengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_diWenPanGuan)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_diWenPanGuan_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_diWenPanGuan);
        bitFieldOffset += JK_1_diWenPanGuan_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mieJunYunXing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_1_mieJunYunXing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_1_mieJunYunXing);
        bitFieldOffset += JK_1_mieJunYunXing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_fengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_fengJiYiQiDong);
        bitFieldOffset += JK_2_fengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_zhiBanStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_zhiBanStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_zhiBanStatus);
        bitFieldOffset += JK_2_zhiBanStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe1)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_dianJiaRe1_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_dianJiaRe1);
        bitFieldOffset += JK_2_dianJiaRe1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe2)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_dianJiaRe2_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_dianJiaRe2);
        bitFieldOffset += JK_2_dianJiaRe2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaRe3)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_dianJiaRe3_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_dianJiaRe3);
        bitFieldOffset += JK_2_dianJiaRe3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_fengJiStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_fengJiStatus);
        bitFieldOffset += JK_2_fengJiStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_shouZiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_shouZiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_shouZiDong);
        bitFieldOffset += JK_2_shouZiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dongXiaJi)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_dongXiaJi_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_dongXiaJi);
        bitFieldOffset += JK_2_dongXiaJi_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_zhongXiaoBaoJing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_zhongXiaoBaoJing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_zhongXiaoBaoJing);
        bitFieldOffset += JK_2_zhongXiaoBaoJing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_dianJiaReGaoWen)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_dianJiaReGaoWen_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_dianJiaReGaoWen);
        bitFieldOffset += JK_2_dianJiaReGaoWen_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_fengJiQueFeng)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_fengJiQueFeng_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_fengJiQueFeng);
        bitFieldOffset += JK_2_fengJiQueFeng_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_paiFengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_paiFengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_paiFengJiYiQiDong);
        bitFieldOffset += JK_2_paiFengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_diWenPanGuan)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_diWenPanGuan_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_diWenPanGuan);
        bitFieldOffset += JK_2_diWenPanGuan_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mieJunYunXing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_2_mieJunYunXing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_2_mieJunYunXing);
        bitFieldOffset += JK_2_mieJunYunXing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_fengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_fengJiYiQiDong);
        bitFieldOffset += JK_3_fengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_zhiBanStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_zhiBanStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_zhiBanStatus);
        bitFieldOffset += JK_3_zhiBanStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe1)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_dianJiaRe1_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_dianJiaRe1);
        bitFieldOffset += JK_3_dianJiaRe1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe2)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_dianJiaRe2_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_dianJiaRe2);
        bitFieldOffset += JK_3_dianJiaRe2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaRe3)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_dianJiaRe3_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_dianJiaRe3);
        bitFieldOffset += JK_3_dianJiaRe3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_fengJiStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_fengJiStatus);
        bitFieldOffset += JK_3_fengJiStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_shouZiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_shouZiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_shouZiDong);
        bitFieldOffset += JK_3_shouZiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dongXiaJi)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_dongXiaJi_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_dongXiaJi);
        bitFieldOffset += JK_3_dongXiaJi_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_zhongXiaoBaoJing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_zhongXiaoBaoJing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_zhongXiaoBaoJing);
        bitFieldOffset += JK_3_zhongXiaoBaoJing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_dianJiaReGaoWen)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_dianJiaReGaoWen_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_dianJiaReGaoWen);
        bitFieldOffset += JK_3_dianJiaReGaoWen_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_fengJiQueFeng)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_fengJiQueFeng_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_fengJiQueFeng);
        bitFieldOffset += JK_3_fengJiQueFeng_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_paiFengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_paiFengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_paiFengJiYiQiDong);
        bitFieldOffset += JK_3_paiFengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_diWenPanGuan)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_diWenPanGuan_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_diWenPanGuan);
        bitFieldOffset += JK_3_diWenPanGuan_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mieJunYunXing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_3_mieJunYunXing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_3_mieJunYunXing);
        bitFieldOffset += JK_3_mieJunYunXing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_fengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_fengJiYiQiDong);
        bitFieldOffset += JK_XF_fengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_zhiBanStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_zhiBanStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_zhiBanStatus);
        bitFieldOffset += JK_XF_zhiBanStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe1)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_dianJiaRe1_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_dianJiaRe1);
        bitFieldOffset += JK_XF_dianJiaRe1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe2)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_dianJiaRe2_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_dianJiaRe2);
        bitFieldOffset += JK_XF_dianJiaRe2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaRe3)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_dianJiaRe3_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_dianJiaRe3);
        bitFieldOffset += JK_XF_dianJiaRe3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiStatus)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_fengJiStatus_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_fengJiStatus);
        bitFieldOffset += JK_XF_fengJiStatus_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_shouZiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_shouZiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_shouZiDong);
        bitFieldOffset += JK_XF_shouZiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dongXiaJi)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_dongXiaJi_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_dongXiaJi);
        bitFieldOffset += JK_XF_dongXiaJi_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_zhongXiaoBaoJing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_zhongXiaoBaoJing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_zhongXiaoBaoJing);
        bitFieldOffset += JK_XF_zhongXiaoBaoJing_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_dianJiaReGaoWen)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_dianJiaReGaoWen_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_dianJiaReGaoWen);
        bitFieldOffset += JK_XF_dianJiaReGaoWen_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_fengJiQueFeng)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_fengJiQueFeng_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_fengJiQueFeng);
        bitFieldOffset += JK_XF_fengJiQueFeng_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_paiFengJiYiQiDong)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_paiFengJiYiQiDong_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_paiFengJiYiQiDong);
        bitFieldOffset += JK_XF_paiFengJiYiQiDong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_diWenPanGuan)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_diWenPanGuan_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_diWenPanGuan);
        bitFieldOffset += JK_XF_diWenPanGuan_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mieJunYunXing)
    {
        gizVarlenCompressValue(bitFieldOffset,JK_XF_mieJunYunXing_LEN,(uint8_t *)&allDatapointByteBuf[byteFieldOffset],dataPoints->valueJK_XF_mieJunYunXing);
        bitFieldOffset += JK_XF_mieJunYunXing_LEN;
    }

    /* The bit segment is assembled and the offset of the value segment is calculated */
    if(0 == bitFieldOffset)
    {
        bitFieldByteLen = 0;
    }
    else
    {
        if(0 == bitFieldOffset%8)
        {
            bitFieldByteLen = bitFieldOffset/8;
        }
        else
        {
            bitFieldByteLen = bitFieldOffset/8 + 1;
        }
    }
    /** Bitwise byte order conversion **/
    if(bitFieldByteLen > 1)
    {
        gizByteOrderExchange((uint8_t *)&allDatapointByteBuf[byteFieldOffset],bitFieldByteLen);
    }
    
    byteFieldOffset += bitFieldByteLen;//Offset the number of bytes occupied by the bit segment

    /*** Handle the value segment ***/

    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai1)
    {
        devStatusTmp.valueJK_1_mianBanTongXunZhuangTai1 = gizY2X(JK_1_mianBanTongXunZhuangTai1_RATIO,  JK_1_mianBanTongXunZhuangTai1_ADDITION, dataPoints->valueJK_1_mianBanTongXunZhuangTai1); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_mianBanTongXunZhuangTai1,JK_1_mianBanTongXunZhuangTai1_LEN);
        byteFieldOffset += JK_1_mianBanTongXunZhuangTai1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai2)
    {
        devStatusTmp.valueJK_1_mianBanTongXunZhuangTai2 = gizY2X(JK_1_mianBanTongXunZhuangTai2_RATIO,  JK_1_mianBanTongXunZhuangTai2_ADDITION, dataPoints->valueJK_1_mianBanTongXunZhuangTai2); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_mianBanTongXunZhuangTai2,JK_1_mianBanTongXunZhuangTai2_LEN);
        byteFieldOffset += JK_1_mianBanTongXunZhuangTai2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_mianBanTongXunZhuangTai3)
    {
        devStatusTmp.valueJK_1_mianBanTongXunZhuangTai3 = gizY2X(JK_1_mianBanTongXunZhuangTai3_RATIO,  JK_1_mianBanTongXunZhuangTai3_ADDITION, dataPoints->valueJK_1_mianBanTongXunZhuangTai3); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_mianBanTongXunZhuangTai3,JK_1_mianBanTongXunZhuangTai3_LEN);
        byteFieldOffset += JK_1_mianBanTongXunZhuangTai3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai1)
    {
        devStatusTmp.valueJK_2_mianBanTongXunZhuangTai1 = gizY2X(JK_2_mianBanTongXunZhuangTai1_RATIO,  JK_2_mianBanTongXunZhuangTai1_ADDITION, dataPoints->valueJK_2_mianBanTongXunZhuangTai1); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_mianBanTongXunZhuangTai1,JK_2_mianBanTongXunZhuangTai1_LEN);
        byteFieldOffset += JK_2_mianBanTongXunZhuangTai1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai2)
    {
        devStatusTmp.valueJK_2_mianBanTongXunZhuangTai2 = gizY2X(JK_2_mianBanTongXunZhuangTai2_RATIO,  JK_2_mianBanTongXunZhuangTai2_ADDITION, dataPoints->valueJK_2_mianBanTongXunZhuangTai2); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_mianBanTongXunZhuangTai2,JK_2_mianBanTongXunZhuangTai2_LEN);
        byteFieldOffset += JK_2_mianBanTongXunZhuangTai2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_mianBanTongXunZhuangTai3)
    {
        devStatusTmp.valueJK_2_mianBanTongXunZhuangTai3 = gizY2X(JK_2_mianBanTongXunZhuangTai3_RATIO,  JK_2_mianBanTongXunZhuangTai3_ADDITION, dataPoints->valueJK_2_mianBanTongXunZhuangTai3); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_mianBanTongXunZhuangTai3,JK_2_mianBanTongXunZhuangTai3_LEN);
        byteFieldOffset += JK_2_mianBanTongXunZhuangTai3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai1)
    {
        devStatusTmp.valueJK_3_mianBanTongXunZhuangTai1 = gizY2X(JK_3_mianBanTongXunZhuangTai1_RATIO,  JK_3_mianBanTongXunZhuangTai1_ADDITION, dataPoints->valueJK_3_mianBanTongXunZhuangTai1); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_mianBanTongXunZhuangTai1,JK_3_mianBanTongXunZhuangTai1_LEN);
        byteFieldOffset += JK_3_mianBanTongXunZhuangTai1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai2)
    {
        devStatusTmp.valueJK_3_mianBanTongXunZhuangTai2 = gizY2X(JK_3_mianBanTongXunZhuangTai2_RATIO,  JK_3_mianBanTongXunZhuangTai2_ADDITION, dataPoints->valueJK_3_mianBanTongXunZhuangTai2); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_mianBanTongXunZhuangTai2,JK_3_mianBanTongXunZhuangTai2_LEN);
        byteFieldOffset += JK_3_mianBanTongXunZhuangTai2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_mianBanTongXunZhuangTai3)
    {
        devStatusTmp.valueJK_3_mianBanTongXunZhuangTai3 = gizY2X(JK_3_mianBanTongXunZhuangTai3_RATIO,  JK_3_mianBanTongXunZhuangTai3_ADDITION, dataPoints->valueJK_3_mianBanTongXunZhuangTai3); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_mianBanTongXunZhuangTai3,JK_3_mianBanTongXunZhuangTai3_LEN);
        byteFieldOffset += JK_3_mianBanTongXunZhuangTai3_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai1)
    {
        devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai1 = gizY2X(JK_XF_mianBanTongXunZhuangTai1_RATIO,  JK_XF_mianBanTongXunZhuangTai1_ADDITION, dataPoints->valueJK_XF_mianBanTongXunZhuangTai1); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai1,JK_XF_mianBanTongXunZhuangTai1_LEN);
        byteFieldOffset += JK_XF_mianBanTongXunZhuangTai1_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai2)
    {
        devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai2 = gizY2X(JK_XF_mianBanTongXunZhuangTai2_RATIO,  JK_XF_mianBanTongXunZhuangTai2_ADDITION, dataPoints->valueJK_XF_mianBanTongXunZhuangTai2); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai2,JK_XF_mianBanTongXunZhuangTai2_LEN);
        byteFieldOffset += JK_XF_mianBanTongXunZhuangTai2_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_mianBanTongXunZhuangTai3)
    {
        devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai3 = gizY2X(JK_XF_mianBanTongXunZhuangTai3_RATIO,  JK_XF_mianBanTongXunZhuangTai3_ADDITION, dataPoints->valueJK_XF_mianBanTongXunZhuangTai3); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_mianBanTongXunZhuangTai3,JK_XF_mianBanTongXunZhuangTai3_LEN);
        byteFieldOffset += JK_XF_mianBanTongXunZhuangTai3_LEN;
    }

    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_tempReal)
    {
        devStatusTmp.valueJK_1_tempReal = exchangeBytes(gizY2X(JK_1_tempReal_RATIO,  JK_1_tempReal_ADDITION, dataPoints->valueJK_1_tempReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_tempReal,JK_1_tempReal_LEN);
        byteFieldOffset += JK_1_tempReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_humiReal)
    {
        devStatusTmp.valueJK_1_humiReal = exchangeBytes(gizY2X(JK_1_humiReal_RATIO,  JK_1_humiReal_ADDITION, dataPoints->valueJK_1_humiReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_humiReal,JK_1_humiReal_LEN);
        byteFieldOffset += JK_1_humiReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_tempSet)
    {
        devStatusTmp.valueJK_1_tempSet = exchangeBytes(gizY2X(JK_1_tempSet_RATIO,  JK_1_tempSet_ADDITION, dataPoints->valueJK_1_tempSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_tempSet,JK_1_tempSet_LEN);
        byteFieldOffset += JK_1_tempSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_humiSet)
    {
        devStatusTmp.valueJK_1_humiSet = exchangeBytes(gizY2X(JK_1_humiSet_RATIO,  JK_1_humiSet_ADDITION, dataPoints->valueJK_1_humiSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_humiSet,JK_1_humiSet_LEN);
        byteFieldOffset += JK_1_humiSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_lengShuiFaKaiDu)
    {
        devStatusTmp.valueJK_1_lengShuiFaKaiDu = exchangeBytes(gizY2X(JK_1_lengShuiFaKaiDu_RATIO,  JK_1_lengShuiFaKaiDu_ADDITION, dataPoints->valueJK_1_lengShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_lengShuiFaKaiDu,JK_1_lengShuiFaKaiDu_LEN);
        byteFieldOffset += JK_1_lengShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_reShuiFaKaiDu)
    {
        devStatusTmp.valueJK_1_reShuiFaKaiDu = exchangeBytes(gizY2X(JK_1_reShuiFaKaiDu_RATIO,  JK_1_reShuiFaKaiDu_ADDITION, dataPoints->valueJK_1_reShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_reShuiFaKaiDu,JK_1_reShuiFaKaiDu_LEN);
        byteFieldOffset += JK_1_reShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_xinFengWenDU)
    {
        devStatusTmp.valueJK_1_xinFengWenDU = exchangeBytes(gizY2X(JK_1_xinFengWenDU_RATIO,  JK_1_xinFengWenDU_ADDITION, dataPoints->valueJK_1_xinFengWenDU)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_xinFengWenDU,JK_1_xinFengWenDU_LEN);
        byteFieldOffset += JK_1_xinFengWenDU_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_jiaShiQIKaiDu)
    {
        devStatusTmp.valueJK_1_jiaShiQIKaiDu = exchangeBytes(gizY2X(JK_1_jiaShiQIKaiDu_RATIO,  JK_1_jiaShiQIKaiDu_ADDITION, dataPoints->valueJK_1_jiaShiQIKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_jiaShiQIKaiDu,JK_1_jiaShiQIKaiDu_LEN);
        byteFieldOffset += JK_1_jiaShiQIKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_1_beiYong)
    {
        devStatusTmp.valueJK_1_beiYong = exchangeBytes(gizY2X(JK_1_beiYong_RATIO,  JK_1_beiYong_ADDITION, dataPoints->valueJK_1_beiYong)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_1_beiYong,JK_1_beiYong_LEN);
        byteFieldOffset += JK_1_beiYong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_tempReal)
    {
        devStatusTmp.valueJK_2_tempReal = exchangeBytes(gizY2X(JK_2_tempReal_RATIO,  JK_2_tempReal_ADDITION, dataPoints->valueJK_2_tempReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_tempReal,JK_2_tempReal_LEN);
        byteFieldOffset += JK_2_tempReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_humiReal)
    {
        devStatusTmp.valueJK_2_humiReal = exchangeBytes(gizY2X(JK_2_humiReal_RATIO,  JK_2_humiReal_ADDITION, dataPoints->valueJK_2_humiReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_humiReal,JK_2_humiReal_LEN);
        byteFieldOffset += JK_2_humiReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_tempSet)
    {
        devStatusTmp.valueJK_2_tempSet = exchangeBytes(gizY2X(JK_2_tempSet_RATIO,  JK_2_tempSet_ADDITION, dataPoints->valueJK_2_tempSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_tempSet,JK_2_tempSet_LEN);
        byteFieldOffset += JK_2_tempSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_humiSet)
    {
        devStatusTmp.valueJK_2_humiSet = exchangeBytes(gizY2X(JK_2_humiSet_RATIO,  JK_2_humiSet_ADDITION, dataPoints->valueJK_2_humiSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_humiSet,JK_2_humiSet_LEN);
        byteFieldOffset += JK_2_humiSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_lengShuiFaKaiDu)
    {
        devStatusTmp.valueJK_2_lengShuiFaKaiDu = exchangeBytes(gizY2X(JK_2_lengShuiFaKaiDu_RATIO,  JK_2_lengShuiFaKaiDu_ADDITION, dataPoints->valueJK_2_lengShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_lengShuiFaKaiDu,JK_2_lengShuiFaKaiDu_LEN);
        byteFieldOffset += JK_2_lengShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_reShuiFaKaiDu)
    {
        devStatusTmp.valueJK_2_reShuiFaKaiDu = exchangeBytes(gizY2X(JK_2_reShuiFaKaiDu_RATIO,  JK_2_reShuiFaKaiDu_ADDITION, dataPoints->valueJK_2_reShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_reShuiFaKaiDu,JK_2_reShuiFaKaiDu_LEN);
        byteFieldOffset += JK_2_reShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_xinFengWenDU)
    {
        devStatusTmp.valueJK_2_xinFengWenDU = exchangeBytes(gizY2X(JK_2_xinFengWenDU_RATIO,  JK_2_xinFengWenDU_ADDITION, dataPoints->valueJK_2_xinFengWenDU)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_xinFengWenDU,JK_2_xinFengWenDU_LEN);
        byteFieldOffset += JK_2_xinFengWenDU_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_jiaShiQIKaiDu)
    {
        devStatusTmp.valueJK_2_jiaShiQIKaiDu = exchangeBytes(gizY2X(JK_2_jiaShiQIKaiDu_RATIO,  JK_2_jiaShiQIKaiDu_ADDITION, dataPoints->valueJK_2_jiaShiQIKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_jiaShiQIKaiDu,JK_2_jiaShiQIKaiDu_LEN);
        byteFieldOffset += JK_2_jiaShiQIKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_2_beiYong)
    {
        devStatusTmp.valueJK_2_beiYong = exchangeBytes(gizY2X(JK_2_beiYong_RATIO,  JK_2_beiYong_ADDITION, dataPoints->valueJK_2_beiYong)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_2_beiYong,JK_2_beiYong_LEN);
        byteFieldOffset += JK_2_beiYong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_tempReal)
    {
        devStatusTmp.valueJK_3_tempReal = exchangeBytes(gizY2X(JK_3_tempReal_RATIO,  JK_3_tempReal_ADDITION, dataPoints->valueJK_3_tempReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_tempReal,JK_3_tempReal_LEN);
        byteFieldOffset += JK_3_tempReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_humiReal)
    {
        devStatusTmp.valueJK_3_humiReal = exchangeBytes(gizY2X(JK_3_humiReal_RATIO,  JK_3_humiReal_ADDITION, dataPoints->valueJK_3_humiReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_humiReal,JK_3_humiReal_LEN);
        byteFieldOffset += JK_3_humiReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_tempSet)
    {
        devStatusTmp.valueJK_3_tempSet = exchangeBytes(gizY2X(JK_3_tempSet_RATIO,  JK_3_tempSet_ADDITION, dataPoints->valueJK_3_tempSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_tempSet,JK_3_tempSet_LEN);
        byteFieldOffset += JK_3_tempSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_humiSet)
    {
        devStatusTmp.valueJK_3_humiSet = exchangeBytes(gizY2X(JK_3_humiSet_RATIO,  JK_3_humiSet_ADDITION, dataPoints->valueJK_3_humiSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_humiSet,JK_3_humiSet_LEN);
        byteFieldOffset += JK_3_humiSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_lengShuiFaKaiDu)
    {
        devStatusTmp.valueJK_3_lengShuiFaKaiDu = exchangeBytes(gizY2X(JK_3_lengShuiFaKaiDu_RATIO,  JK_3_lengShuiFaKaiDu_ADDITION, dataPoints->valueJK_3_lengShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_lengShuiFaKaiDu,JK_3_lengShuiFaKaiDu_LEN);
        byteFieldOffset += JK_3_lengShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_reShuiFaKaiDu)
    {
        devStatusTmp.valueJK_3_reShuiFaKaiDu = exchangeBytes(gizY2X(JK_3_reShuiFaKaiDu_RATIO,  JK_3_reShuiFaKaiDu_ADDITION, dataPoints->valueJK_3_reShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_reShuiFaKaiDu,JK_3_reShuiFaKaiDu_LEN);
        byteFieldOffset += JK_3_reShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_xinFengWenDU)
    {
        devStatusTmp.valueJK_3_xinFengWenDU = exchangeBytes(gizY2X(JK_3_xinFengWenDU_RATIO,  JK_3_xinFengWenDU_ADDITION, dataPoints->valueJK_3_xinFengWenDU)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_xinFengWenDU,JK_3_xinFengWenDU_LEN);
        byteFieldOffset += JK_3_xinFengWenDU_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_jiaShiQIKaiDu)
    {
        devStatusTmp.valueJK_3_jiaShiQIKaiDu = exchangeBytes(gizY2X(JK_3_jiaShiQIKaiDu_RATIO,  JK_3_jiaShiQIKaiDu_ADDITION, dataPoints->valueJK_3_jiaShiQIKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_jiaShiQIKaiDu,JK_3_jiaShiQIKaiDu_LEN);
        byteFieldOffset += JK_3_jiaShiQIKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_3_beiYong)
    {
        devStatusTmp.valueJK_3_beiYong = exchangeBytes(gizY2X(JK_3_beiYong_RATIO,  JK_3_beiYong_ADDITION, dataPoints->valueJK_3_beiYong)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_3_beiYong,JK_3_beiYong_LEN);
        byteFieldOffset += JK_3_beiYong_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_tempReal)
    {
        devStatusTmp.valueJK_XF_tempReal = exchangeBytes(gizY2X(JK_XF_tempReal_RATIO,  JK_XF_tempReal_ADDITION, dataPoints->valueJK_XF_tempReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_tempReal,JK_XF_tempReal_LEN);
        byteFieldOffset += JK_XF_tempReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_humiReal)
    {
        devStatusTmp.valueJK_XF_humiReal = exchangeBytes(gizY2X(JK_XF_humiReal_RATIO,  JK_XF_humiReal_ADDITION, dataPoints->valueJK_XF_humiReal)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_humiReal,JK_XF_humiReal_LEN);
        byteFieldOffset += JK_XF_humiReal_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_tempSet)
    {
        devStatusTmp.valueJK_XF_tempSet = exchangeBytes(gizY2X(JK_XF_tempSet_RATIO,  JK_XF_tempSet_ADDITION, dataPoints->valueJK_XF_tempSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_tempSet,JK_XF_tempSet_LEN);
        byteFieldOffset += JK_XF_tempSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_humiSet)
    {
        devStatusTmp.valueJK_XF_humiSet = exchangeBytes(gizY2X(JK_XF_humiSet_RATIO,  JK_XF_humiSet_ADDITION, dataPoints->valueJK_XF_humiSet)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_humiSet,JK_XF_humiSet_LEN);
        byteFieldOffset += JK_XF_humiSet_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_lengShuiFaKaiDu)
    {
        devStatusTmp.valueJK_XF_lengShuiFaKaiDu = exchangeBytes(gizY2X(JK_XF_lengShuiFaKaiDu_RATIO,  JK_XF_lengShuiFaKaiDu_ADDITION, dataPoints->valueJK_XF_lengShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_lengShuiFaKaiDu,JK_XF_lengShuiFaKaiDu_LEN);
        byteFieldOffset += JK_XF_lengShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_reShuiFaKaiDu)
    {
        devStatusTmp.valueJK_XF_reShuiFaKaiDu = exchangeBytes(gizY2X(JK_XF_reShuiFaKaiDu_RATIO,  JK_XF_reShuiFaKaiDu_ADDITION, dataPoints->valueJK_XF_reShuiFaKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_reShuiFaKaiDu,JK_XF_reShuiFaKaiDu_LEN);
        byteFieldOffset += JK_XF_reShuiFaKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_xinFengWenDU)
    {
        devStatusTmp.valueJK_XF_xinFengWenDU = exchangeBytes(gizY2X(JK_XF_xinFengWenDU_RATIO,  JK_XF_xinFengWenDU_ADDITION, dataPoints->valueJK_XF_xinFengWenDU)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_xinFengWenDU,JK_XF_xinFengWenDU_LEN);
        byteFieldOffset += JK_XF_xinFengWenDU_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_jiaShiQIKaiDu)
    {
        devStatusTmp.valueJK_XF_jiaShiQIKaiDu = exchangeBytes(gizY2X(JK_XF_jiaShiQIKaiDu_RATIO,  JK_XF_jiaShiQIKaiDu_ADDITION, dataPoints->valueJK_XF_jiaShiQIKaiDu)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_jiaShiQIKaiDu,JK_XF_jiaShiQIKaiDu_LEN);
        byteFieldOffset += JK_XF_jiaShiQIKaiDu_LEN;
    }
    if(gizwitsProtocol.waitReportDatapointFlag.flagJK_XF_beiYong)
    {
        devStatusTmp.valueJK_XF_beiYong = exchangeBytes(gizY2X(JK_XF_beiYong_RATIO,  JK_XF_beiYong_ADDITION, dataPoints->valueJK_XF_beiYong)); 
        gizMemcpy((uint8_t *)&allDatapointByteBuf[byteFieldOffset],(uint8_t *)&devStatusTmp.valueJK_XF_beiYong,JK_XF_beiYong_LEN);
        byteFieldOffset += JK_XF_beiYong_LEN;
    }




    gizMemset((uint8_t *)&gizwitsProtocol.waitReportDatapointFlag,0,DATAPOINT_FLAG_LEN);//Clear the flag
    *outDataLen = byteFieldOffset;
    gizMemcpy(outData,allDatapointByteBuf,*outDataLen);
    return 0;
}


/**
* @brief This function is called by the Gagent module to receive the relevant protocol data from the cloud or APP
* @param [in] inData The protocol data entered
* @param [in] inLen Enter the length of the data
* @param [out] outData The output of the protocol data
* @param [out] outLen The length of the output data
* @return 0, the implementation of success, non-0, failed
*/
static int8_t gizProtocolIssuedProcess(char *did, uint8_t *inData, uint32_t inLen, uint8_t *outData, uint32_t *outLen)
{
    uint8_t issuedAction = inData[0];

    if((NULL == inData)||(NULL == outData)||(NULL == outLen))
    {
        GIZWITS_LOG("gizProtocolIssuedProcess Error , Illegal Param\n");
        return -1;
    }

    if(NULL == did)
    {
    memset((uint8_t *)&gizwitsProtocol.issuedProcessEvent, 0, sizeof(eventInfo_t));
    switch(issuedAction)
    {
        case ACTION_CONTROL_DEVICE:
            outData = NULL;
            *outLen = 0;
            break;
        
        case ACTION_READ_DEV_STATUS:
            GIZWITS_LOG("ACTION_ELONGATE_READ_DEV_STATUS \n");          
            memcpy((uint8_t *)&gizwitsProtocol.waitReportDatapointFlag,&inData[1],DATAPOINT_FLAG_LEN);//拷贝查询FLAG               
            if(DATAPOINT_FLAG_LEN > 1)
            {
                    gizByteOrderExchange((uint8_t *)&gizwitsProtocol.waitReportDatapointFlag,DATAPOINT_FLAG_LEN);
            }
                        
            if(0 == gizDataPoints2ReportData(&gizwitsProtocol.gizLastDataPoint,gizwitsProtocol.reportData,(uint32_t *)&gizwitsProtocol.reportDataLen))
            {  
                memcpy(outData+1, (uint8_t *)&gizwitsProtocol.reportData, gizwitsProtocol.reportDataLen);
                outData[0] = ACTION_READ_DEV_STATUS_ACK;
                *outLen = DATAPOINT_FLAG_LEN + sizeof(gizwitsReport_t)+1;
            }
            else
            {
                return -1;
            }
            break;
        case ACTION_W2D_TRANSPARENT_DATA:
            memcpy(gizwitsProtocol.transparentBuff, &inData[1], inLen-1);
            gizwitsProtocol.transparentLen = inLen - 1;
            
            gizwitsProtocol.issuedProcessEvent.event[gizwitsProtocol.issuedProcessEvent.num] = TRANSPARENT_DATA;
            gizwitsProtocol.issuedProcessEvent.num++;
            gizwitsProtocol.issuedFlag = ACTION_W2D_TRANSPARENT_TYPE;
            outData = NULL;
            *outLen = 0;
            break;
        
        default:
                    break;
        }
    }

    return 0;
}

/**
* @brief The protocol sends data back , P0 ACK
*
* @param [in] head                  : Protocol head pointer
* @param [in] data                  : Payload data 
* @param [in] len                   : Payload data length
* @param [in] proFlag               : DID flag ,1 for Virtual sub device did ,0 for single product or gateway 
*
* @return : 0,Ack success;
*           -1，Input Param Illegal
*           -2，Serial send faild
*/
static int32_t gizProtocolIssuedDataAck(protocolHead_t *head, uint8_t *gizdata, uint32_t len, uint8_t proFlag)
{
    int32_t ret = 0;
    uint8_t tx_buf[RB_MAX_LEN];
    uint32_t offset = 0;
    uint8_t sDidLen = 0;
    uint16_t data_len = 0;
	uint8_t *pTxBuf = tx_buf;
    if(NULL == gizdata)
    {
        GIZWITS_LOG("[ERR]  data Is Null \n");
        return -1;
    }
    

    if(0x1 == proFlag)
    {
        sDidLen = *((uint8_t *)head + sizeof(protocolHead_t));
        data_len = 5 + 1 + sDidLen + len;   
    }
    else
    {
        data_len = 5 + len;
    }
    GIZWITS_LOG("len = %d , sDidLen = %d ,data_len = %d\n", len,sDidLen,data_len);
    *pTxBuf ++= 0xFF;
    *pTxBuf ++= 0xFF;
    *pTxBuf ++= (uint8_t)(data_len>>8);//len
    *pTxBuf ++= (uint8_t)(data_len);
    *pTxBuf ++= head->cmd + 1;
    *pTxBuf ++= head->sn;
    *pTxBuf ++= 0x00;
    *pTxBuf ++= proFlag;//flag
    offset = 8;
    if(0x1 == proFlag)
    {
        *pTxBuf ++= sDidLen;//didlen
        offset += 1;
        memcpy(&tx_buf[offset],(uint8_t *)head+sizeof(protocolHead_t)+1,sDidLen);
        offset += sDidLen;
        pTxBuf += sDidLen;

    }
    if(0 != len)
    {
        memcpy(&tx_buf[offset],gizdata,len);
    }
    tx_buf[data_len + 4 - 1 ] = gizProtocolSum( tx_buf , (data_len+4));

    ret = uartWrite(tx_buf, data_len+4);
    if(ret < 0)
    {
        GIZWITS_LOG("uart write error %d \n", ret);
        return -2;
    }

    return 0;
}
/**
* @brief Report data interface
*
* @param [in] action            : PO action
* @param [in] data              : Payload data
* @param [in] len               : Payload data length
*
* @return : 0,Ack success;
*           -1，Input Param Illegal
*           -2，Serial send faild
*/
static int32_t gizReportData(uint8_t action, uint8_t *gizdata, uint32_t len)
{
    int32_t ret = 0;
    uint8_t tx_buf[MAX_PACKAGE_LEN];
	uint8_t *pTxBuf = tx_buf;
    uint16_t data_len = 6 + len;
    if(NULL == gizdata)
    {
        GIZWITS_LOG("gizReportData Error , Illegal Param\n");
        return -1;
    }

    *pTxBuf ++= 0xFF;
    *pTxBuf ++= 0xFF;
    *pTxBuf ++= (uint8_t)(data_len>>8);
    *pTxBuf ++= (uint8_t)(data_len);
    *pTxBuf ++= CMD_REPORT_P0;
    *pTxBuf ++= gizwitsProtocol.sn++;
    *pTxBuf ++= 0x00;
    *pTxBuf ++= 0x00;
    *pTxBuf ++= action;

    memcpy(&tx_buf[9],gizdata,len);
    
    tx_buf[data_len + 4 - 1 ] = gizProtocolSum( tx_buf , (data_len+4));
    
    ret = uartWrite(tx_buf, data_len+4);
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
        return -2;
    }

    gizProtocolWaitAck(tx_buf, data_len+4);

    return 0;
}/**
* @brief Datapoints reporting mechanism
*
* 1. Changes are reported immediately

* 2. Data timing report , 600000 Millisecond
* 
*@param [in] currentData       : Current datapoints value
* @return : NULL
*/
static void gizDevReportPolicy(dataPoint_t *currentData)
{
    static uint32_t lastRepTime = 0;
    uint32_t timeNow = gizGetTimerCount();
    uint8_t *waitReportDataPtr = NULL;

    if((1 == gizCheckReport(currentData, (dataPoint_t *)&gizwitsProtocol.gizLastDataPoint)))
    {
        GIZWITS_LOG("changed, report data\n");
        if(0 == gizDataPoints2ReportData(currentData,gizwitsProtocol.reportData,(uint32_t *)&gizwitsProtocol.reportDataLen))
        {
            gizReportData(ACTION_REPORT_DEV_STATUS, gizwitsProtocol.reportData, gizwitsProtocol.reportDataLen);        }
        memcpy((uint8_t *)&gizwitsProtocol.gizLastDataPoint, (uint8_t *)currentData, sizeof(dataPoint_t));
    }

    if((0 == (timeNow % (600000))) && (lastRepTime != timeNow))
    {
        GIZWITS_LOG("Info: 600S report data\n");
        memset((uint8_t *)&gizwitsProtocol.waitReportDatapointFlag,0xFF,DATAPOINT_FLAG_LEN);
        if(0 == gizDataPoints2ReportData(currentData,gizwitsProtocol.reportData,(uint32_t *)&gizwitsProtocol.reportDataLen))
        {
            gizReportData(ACTION_REPORT_DEV_STATUS, gizwitsProtocol.reportData, gizwitsProtocol.reportDataLen);        }
        memcpy((uint8_t *)&gizwitsProtocol.gizLastDataPoint, (uint8_t *)currentData, sizeof(dataPoint_t));

        lastRepTime = timeNow;
    }
    free(waitReportDataPtr);
}

/**
* @brief Get a packet of data from the ring buffer
*
* @param [in]  rb                  : Input data address
* @param [out] data                : Output data address
* @param [out] len                 : Output data length
*
* @return : 0,Return correct ;-1，Return failure;-2，Data check failure
*/
static int8_t gizProtocolGetOnePacket(rb_t *rb, uint8_t *gizdata, uint16_t *len)
{
    int32_t ret = 0;
    uint8_t sum = 0;
    int32_t i = 0;
    uint8_t tmpData;
    uint8_t tmpLen = 0;
    uint16_t tmpCount = 0;
    static uint8_t protocolFlag = 0;
    static uint16_t protocolCount = 0;
    static uint8_t lastData = 0;
    static uint8_t debugCount = 0;
    uint8_t *protocolBuff = gizdata;
    protocolHead_t *head = NULL;

    if((NULL == rb) || (NULL == gizdata) ||(NULL == len))
    {
        GIZWITS_LOG("gizProtocolGetOnePacket Error , Illegal Param\n");
        return -1;
    }

    tmpLen = rbCanRead(rb);
    if(0 == tmpLen)
    {
        return -1;
    }

    for(i=0; i<tmpLen; i++)
    {
        ret = rbRead(rb, &tmpData, 1);
        if(0 != ret)
        {
            if((0xFF == lastData) && (0xFF == tmpData))
            {
                if(0 == protocolFlag)
                {
                    protocolBuff[0] = 0xFF;
                    protocolBuff[1] = 0xFF;
                    protocolCount = 2;
                    protocolFlag = 1;
                }
                else
                {
                    if((protocolCount > 4) && (protocolCount != tmpCount))
                    {
                        protocolBuff[0] = 0xFF;
                        protocolBuff[1] = 0xFF;
                        protocolCount = 2;
                    }
                }
            }
            else if((0xFF == lastData) && (0x55 == tmpData))
            {
            }
            else
            {
                if(1 == protocolFlag)
                {
                    protocolBuff[protocolCount] = tmpData;
                    protocolCount++;

                    if(protocolCount > 4)
                    {
                        head = (protocolHead_t *)protocolBuff;
                        tmpCount = exchangeBytes(head->len)+4;
                        if(protocolCount == tmpCount)
                        {
                            break;
                        }
                    }
                }
            }

            lastData = tmpData;
            debugCount++;
        }
    }

    if((protocolCount > 4) && (protocolCount == tmpCount))
    {
        sum = gizProtocolSum(protocolBuff, protocolCount);

        if(protocolBuff[protocolCount-1] == sum)
        {
            memcpy(gizdata, protocolBuff, tmpCount);
            *len = tmpCount;
            protocolFlag = 0;

            protocolCount = 0;
            debugCount = 0;
            lastData = 0;

            return 0;
        }
        else
        {
            return -2;
        }
    }

    return 1;
}



/**
* @brief Protocol data resend

* The protocol data resend when check timeout and meet the resend limiting

* @param none    
*
* @return none
*/
static void gizProtocolResendData(void)
{
    int32_t ret = 0;

    if(0 == gizwitsProtocol.waitAck.flag)
    {
        return;
    }

    GIZWITS_LOG("Warning: timeout, resend data \n");
    
    ret = uartWrite(gizwitsProtocol.waitAck.buf, gizwitsProtocol.waitAck.dataLen);
    if(ret != gizwitsProtocol.waitAck.dataLen)
    {
        GIZWITS_LOG("ERR: resend data error\n");
    }

    gizwitsProtocol.waitAck.sendTime = gizGetTimerCount();
}

/**
* @brief Clear the ACK protocol message
*
* @param [in] head : Protocol header address
*
* @return 0， success; other， failure
*/
static int8_t gizProtocolWaitAckCheck(protocolHead_t *head)
{
    protocolHead_t *waitAckHead = (protocolHead_t *)gizwitsProtocol.waitAck.buf;

    if(NULL == head)
    {
        GIZWITS_LOG("ERR: data is empty \n");
        return -1;
    }

    if(waitAckHead->cmd+1 == head->cmd)
    {
        memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
    }

    return 0;
}

/**
* @brief Send general protocol message data
* 
* @param [in] head              : Protocol header address
*
* @return : Return effective data length;-1，return failure
*/
static int32_t gizProtocolCommonAck(protocolHead_t *head)
{
    int32_t ret = 0;
    protocolCommon_t ack;

    if(NULL == head)
    {
        GIZWITS_LOG("ERR: gizProtocolCommonAck data is empty \n");
        return -1;
    }
    memcpy((uint8_t *)&ack, (uint8_t *)head, sizeof(protocolHead_t));
    ack.head.cmd = ack.head.cmd+1;
    ack.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
    ack.sum = gizProtocolSum((uint8_t *)&ack, sizeof(protocolCommon_t));

    ret = uartWrite((uint8_t *)&ack, sizeof(protocolCommon_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    return ret;
}

/**
* @brief ACK processing function

* Time-out 200ms no ACK resend，resend two times at most

* @param none 
*
* @return none
*/
static void gizProtocolAckHandle(void)
{
    if(1 == gizwitsProtocol.waitAck.flag)
    {
        if(SEND_MAX_NUM > gizwitsProtocol.waitAck.num)
        {
            // Time-out no ACK resend
            if(SEND_MAX_TIME < (gizGetTimerCount() - gizwitsProtocol.waitAck.sendTime))
            {
                GIZWITS_LOG("Warning:gizProtocolResendData %d %d %d\n", gizGetTimerCount(), gizwitsProtocol.waitAck.sendTime, gizwitsProtocol.waitAck.num);
                gizProtocolResendData();
                gizwitsProtocol.waitAck.num++;
            }
        }
        else
        {
            memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
	        mcuRestart();
        }
    }
}

/**
* @brief Protocol 4.1 WiFi module requests device information
*
* @param[in] head : Protocol header address
*
* @return Return effective data length;-1，return failure
*/
static int32_t gizProtocolGetDeviceInfo(protocolHead_t * head)
{
    int32_t ret = 0;
    protocolDeviceInfo_t deviceInfo;

    if(NULL == head)
    {
        GIZWITS_LOG("gizProtocolGetDeviceInfo Error , Illegal Param\n");
        return -1;
    }

    gizProtocolHeadInit((protocolHead_t *)&deviceInfo);
    deviceInfo.head.cmd = ACK_GET_DEVICE_INFO;
    deviceInfo.head.sn = head->sn;
    memcpy((uint8_t *)deviceInfo.protocolVer, protocol_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.p0Ver, P0_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.softVer, SOFTWARE_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.hardVer, HARDWARE_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.productKey, PRODUCT_KEY, strlen(PRODUCT_KEY));
    memcpy((uint8_t *)deviceInfo.productSecret, PRODUCT_SECRET, strlen(PRODUCT_SECRET));
    memset((uint8_t *)deviceInfo.devAttr, 0, 8);
    deviceInfo.devAttr[7] |= DEV_IS_GATEWAY<<0;
    deviceInfo.devAttr[7] |= (0x01<<1);
    deviceInfo.ninableTime = exchangeBytes(NINABLETIME);
    deviceInfo.head.len = exchangeBytes(sizeof(protocolDeviceInfo_t)-4);
    deviceInfo.sum = gizProtocolSum((uint8_t *)&deviceInfo, sizeof(protocolDeviceInfo_t));

    ret = uartWrite((uint8_t *)&deviceInfo, sizeof(protocolDeviceInfo_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }
    
    return ret;
}

/**
* @brief Protocol 4.7 Handling of illegal message notification

* @param[in] head  : Protocol header address
* @param[in] errno : Illegal message notification type
* @return 0， success; other， failure
*/
static int32_t gizProtocolErrorCmd(protocolHead_t *head,errorPacketsType_t errno)
{
    int32_t ret = 0;
    protocolErrorType_t errorType;

    if(NULL == head)
    {
        GIZWITS_LOG("gizProtocolErrorCmd Error , Illegal Param\n");
        return -1;
    }
    gizProtocolHeadInit((protocolHead_t *)&errorType);
    errorType.head.cmd = ACK_ERROR_PACKAGE;
    errorType.head.sn = head->sn;
    
    errorType.head.len = exchangeBytes(sizeof(protocolErrorType_t)-4);
    errorType.error = errno;
    errorType.sum = gizProtocolSum((uint8_t *)&errorType, sizeof(protocolErrorType_t));
    
    ret = uartWrite((uint8_t *)&errorType, sizeof(protocolErrorType_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    return ret;
}

/**
* @brief Protocol 4.13 Get and process network time
*
* @param [in] head : Protocol header address
*
* @return 0， success; other， failure
*/
static int8_t gizProtocolNTP(protocolHead_t *head)
{  
    protocolUTT_t *UTTInfo = (protocolUTT_t *)head;
    
    if(NULL == head)
    {
        GIZWITS_LOG("ERR: NTP is empty \n");
        return -1;
    }
    
    memcpy((uint8_t *)&gizwitsProtocol.TimeNTP,(uint8_t *)UTTInfo->time, (7 + 4));
    gizwitsProtocol.TimeNTP.year = exchangeBytes(gizwitsProtocol.TimeNTP.year);
    gizwitsProtocol.TimeNTP.ntp =exchangeWord(gizwitsProtocol.TimeNTP.ntp);

    gizwitsProtocol.NTPEvent.event[gizwitsProtocol.NTPEvent.num] = WIFI_NTP;
    gizwitsProtocol.NTPEvent.num++;
    
    gizwitsProtocol.issuedFlag = GET_NTP_TYPE;
    
    
    return 0;
}

/**
* @brief Protocol 4.4 Device MCU restarts function

* @param none
* @return none
*/
static void gizProtocolReboot(void)
{
    uint32_t timeDelay = gizGetTimerCount();
    
    /*Wait 600ms*/
    while((gizGetTimerCount() - timeDelay) <= 600);
    mcuRestart();
}

/**
* @brief Protocol 4.5 :The WiFi module informs the device MCU of working status about the WiFi module

* @param[in] status WiFi module working status
* @return none
*/
static int8_t gizProtocolModuleStatus(protocolWifiStatus_t *status)
{
    static wifiStatus_t lastStatus;

    if(NULL == status)
    {
        GIZWITS_LOG("gizProtocolModuleStatus Error , Illegal Param\n");
        return -1;
    }

    status->ststus.value = exchangeBytes(status->ststus.value);
   
    //OnBoarding mode status
    if(lastStatus.types.onboarding != status->ststus.types.onboarding)
    {
        if(1 == status->ststus.types.onboarding)
        {
            if(1 == status->ststus.types.softap)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_SOFTAP;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: SoftAP or Web mode\n");
            }

            if(1 == status->ststus.types.station)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_AIRLINK;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: AirLink mode\n");
            }
        }
        else
        {
            if(1 == status->ststus.types.softap)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_SOFTAP;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: SoftAP or Web mode\n");
            }

            if(1 == status->ststus.types.station)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_STATION;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: Station mode\n");
            }
        }
    }

    //binding mode status
    if(lastStatus.types.binding != status->ststus.types.binding)
    {
        lastStatus.types.binding = status->ststus.types.binding;
        if(1 == status->ststus.types.binding)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_OPEN_BINDING;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: in binding mode\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CLOSE_BINDING;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: out binding mode\n");
        }
    }

    //router status
    if(lastStatus.types.con_route != status->ststus.types.con_route)
    {
        lastStatus.types.con_route = status->ststus.types.con_route;
        if(1 == status->ststus.types.con_route)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_ROUTER;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: connected router\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_ROUTER;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: disconnected router\n");
        }
    }

    //M2M server status
    if(lastStatus.types.con_m2m != status->ststus.types.con_m2m)
    {
        lastStatus.types.con_m2m = status->ststus.types.con_m2m;
        if(1 == status->ststus.types.con_m2m)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_M2M;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: connected m2m\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_M2M;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: disconnected m2m\n");
        }
    }

    //APP status
    if(lastStatus.types.app != status->ststus.types.app)
    {
        lastStatus.types.app = status->ststus.types.app;
        if(1 == status->ststus.types.app)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_APP;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: app connect\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_APP;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: no app connect\n");
        }
    }

    //test mode status
    if(lastStatus.types.test != status->ststus.types.test)
    {
        lastStatus.types.test = status->ststus.types.test;
        if(1 == status->ststus.types.test)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_OPEN_TESTMODE;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: in test mode\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CLOSE_TESTMODE;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: out test mode\n");
        }
    }

    gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_RSSI;
    gizwitsProtocol.wifiStatusEvent.num++;
    gizwitsProtocol.wifiStatusData.rssi = status->ststus.types.rssi;
    GIZWITS_LOG("RSSI is %d \n", gizwitsProtocol.wifiStatusData.rssi);

    gizwitsProtocol.issuedFlag = WIFI_STATUS_TYPE;

    return 0;
}


/**@name Gizwits User API interface
* @{
*/

/**
* @brief gizwits Protocol initialization interface

* Protocol-related timer, serial port initialization

* Datapoint initialization

* @param none
* @return none
*/
void gizwitsInit(void)
{    
    pRb.rbCapacity = RB_MAX_LEN;
    pRb.rbBuff = rbBuf;
    if(0 == rbCreate(&pRb))
	{
		GIZWITS_LOG("rbCreate Success \n");
	}
	else
	{
		GIZWITS_LOG("rbCreate Faild \n");
	}
    
    memset((uint8_t *)&gizwitsProtocol, 0, sizeof(gizwitsProtocol_t));
}

/**
* @brief WiFi configure interface

* Set the WiFi module into the corresponding configuration mode or reset the module

* @param[in] mode ：0x0， reset the module ;0x01， SoftAp mode ;0x02， AirLink mode ;0x03， Production test mode; 0x04:allow users to bind devices

* @return Error command code
*/
int32_t gizwitsSetMode(uint8_t mode)
{
    int32_t ret = 0;
    protocolCfgMode_t cfgMode;
    protocolCommon_t setDefault;

    switch(mode)
    {
        case WIFI_RESET_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_SET_DEFAULT;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t));   
            break;
        case WIFI_SOFTAP_MODE:
            gizProtocolHeadInit((protocolHead_t *)&cfgMode);
            cfgMode.head.cmd = CMD_WIFI_CONFIG;
            cfgMode.head.sn = gizwitsProtocol.sn++;
            cfgMode.cfgMode = mode;
            cfgMode.head.len = exchangeBytes(sizeof(protocolCfgMode_t)-4);
            cfgMode.sum = gizProtocolSum((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            ret = uartWrite((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }
            gizProtocolWaitAck((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t)); 
            break;
        case WIFI_AIRLINK_MODE:
            gizProtocolHeadInit((protocolHead_t *)&cfgMode);
            cfgMode.head.cmd = CMD_WIFI_CONFIG;
            cfgMode.head.sn = gizwitsProtocol.sn++;
            cfgMode.cfgMode = mode;
            cfgMode.head.len = exchangeBytes(sizeof(protocolCfgMode_t)-4);
            cfgMode.sum = gizProtocolSum((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            ret = uartWrite((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }
            gizProtocolWaitAck((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t)); 
            break;
        case WIFI_PRODUCTION_TEST:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_PRODUCTION_TEST;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            break;
        case WIFI_NINABLE_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_NINABLE_MODE;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t)); 
            break;
        case WIFI_REBOOT_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_REBOOT_MODULE;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t)); 
            break;
        default:
            GIZWITS_LOG("ERR: CfgMode error!\n");
            break;
    }

    return ret;
}

/**
* @brief Get the the network time

* Protocol 4.13:"Device MCU send" of "the MCU requests access to the network time"

* @param[in] none
* @return none
*/
void gizwitsGetNTP(void)
{
    int32_t ret = 0;
    protocolCommon_t getNTP;

    gizProtocolHeadInit((protocolHead_t *)&getNTP);
    getNTP.head.cmd = CMD_GET_NTP;
    getNTP.head.sn = gizwitsProtocol.sn++;
    getNTP.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
    getNTP.sum = gizProtocolSum((uint8_t *)&getNTP, sizeof(protocolCommon_t));
    ret = uartWrite((uint8_t *)&getNTP, sizeof(protocolCommon_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR[NTP]: uart write error %d \n", ret);
    }

    gizProtocolWaitAck((uint8_t *)&getNTP, sizeof(protocolCommon_t));
}


/**
* @brief Get Module Info

* 

* @param[in] none
* @return none
*/
void gizwitsGetModuleInfo(void)
{
    int32_t ret = 0;
    protocolGetModuleInfo_t getModuleInfo;

    gizProtocolHeadInit((protocolHead_t *)&getModuleInfo);
    getModuleInfo.head.cmd = CMD_ASK_MODULE_INFO;
    getModuleInfo.head.sn = gizwitsProtocol.sn++;
    getModuleInfo.type = 0x0;
    getModuleInfo.head.len = exchangeBytes(sizeof(protocolGetModuleInfo_t)-4);
    getModuleInfo.sum = gizProtocolSum((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
    ret = uartWrite((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR[NTP]: uart write error %d \n", ret);
    }

    gizProtocolWaitAck((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
}


/**
* @brief Module Info Analyse
*
* @param [in] head : 
*
* @return 0, Success， , other,Faild
*/
static int8_t gizProtocolModuleInfoHandle(protocolHead_t *head)
{
    protocolModuleInfo_t *moduleInfo = (protocolModuleInfo_t *)head;

    if(NULL == head)
    {
        GIZWITS_LOG("NTP is empty \n");
        return -1;
    }

    memcpy((uint8_t *)&gizwitsProtocol.wifiModuleNews,(uint8_t *)&moduleInfo->wifiModuleInfo, sizeof(moduleInfo_t));

    gizwitsProtocol.moduleInfoEvent.event[gizwitsProtocol.moduleInfoEvent.num] = MODULE_INFO;
    gizwitsProtocol.moduleInfoEvent.num++;

    gizwitsProtocol.issuedFlag = GET_MODULEINFO_TYPE;


    return 0;
}

/**
* @brief Protocol handling function

* 

* @param [in] currentData :The protocol data pointer
* @return none
*/
int32_t gizwitsHandle(dataPoint_t *currentData)
{
    int8_t ret = 0;
#ifdef PROTOCOL_DEBUG
    uint16_t i = 0;
#endif
    uint8_t ackData[RB_MAX_LEN];
    uint16_t protocolLen = 0;
    uint32_t ackLen = 0;
    protocolHead_t *recvHead = NULL;
    char *didPtr = NULL;
    uint16_t offset = 0;


    if(NULL == currentData)
    {
        GIZWITS_LOG("GizwitsHandle Error , Illegal Param\n");
        return -1;
    }

    /*resend strategy*/
    gizProtocolAckHandle();
    ret = gizProtocolGetOnePacket(&pRb, gizwitsProtocol.protocolBuf, &protocolLen);

    if(0 == ret)
    {
        GIZWITS_LOG("Get One Packet!\n");
        
#ifdef PROTOCOL_DEBUG
        GIZWITS_LOG("WiFi2MCU[%4d:%4d]: ", gizGetTimerCount(), protocolLen);
        for(i=0; i<protocolLen;i++)
        {
            GIZWITS_LOG("%02x ", gizwitsProtocol.protocolBuf[i]);
        }
        GIZWITS_LOG("\n");
#endif

        recvHead = (protocolHead_t *)gizwitsProtocol.protocolBuf;
        switch (recvHead->cmd)
        {
            case CMD_GET_DEVICE_INTO:
                gizProtocolGetDeviceInfo(recvHead);
                break;
            case CMD_ISSUED_P0:
                GIZWITS_LOG("flag %x %x \n", recvHead->flags[0], recvHead->flags[1]);
                //offset = 1;
               
                if(0 == gizProtocolIssuedProcess(didPtr, gizwitsProtocol.protocolBuf+sizeof(protocolHead_t)+offset, protocolLen-(sizeof(protocolHead_t)+offset+1), ackData, &ackLen))
                {
                    gizProtocolIssuedDataAck(recvHead, ackData, ackLen,recvHead->flags[1]);
                    GIZWITS_LOG("AckData : \n");
                }
                break;
            case CMD_HEARTBEAT:
                gizProtocolCommonAck(recvHead);
                break;
            case CMD_WIFISTATUS:
                gizProtocolCommonAck(recvHead);
                gizProtocolModuleStatus((protocolWifiStatus_t *)recvHead);
                break;
            case ACK_REPORT_P0:
            case ACK_WIFI_CONFIG:
            case ACK_SET_DEFAULT:
            case ACK_NINABLE_MODE:
            case ACK_REBOOT_MODULE:
                gizProtocolWaitAckCheck(recvHead);
                break;
            case CMD_MCU_REBOOT:
                gizProtocolCommonAck(recvHead);
                GIZWITS_LOG("report:MCU reboot!\n");
                
                gizProtocolReboot();
                break;
            case CMD_ERROR_PACKAGE:
                break;
            case ACK_PRODUCTION_TEST:
                gizProtocolWaitAckCheck(recvHead);
                GIZWITS_LOG("Ack PRODUCTION_MODE success \n");
                break;           
            case ACK_GET_NTP:
                gizProtocolWaitAckCheck(recvHead);
                gizProtocolNTP(recvHead);
                GIZWITS_LOG("Ack GET_UTT success \n");
                break; 
            case ACK_ASK_MODULE_INFO:
                gizProtocolWaitAckCheck(recvHead);
                gizProtocolModuleInfoHandle(recvHead);
                GIZWITS_LOG("Ack GET_Module success \n");
            break;
 
            default:
                gizProtocolErrorCmd(recvHead,ERROR_CMD);
                GIZWITS_LOG("ERR: cmd code error!\n");
                break;
        }
    }
    else if(-2 == ret)
    {
        //Check failed, report exception
        recvHead = (protocolHead_t *)gizwitsProtocol.protocolBuf;
        gizProtocolErrorCmd(recvHead,ERROR_ACK_SUM);
        GIZWITS_LOG("ERR: check sum error!\n");
        return -2;
    }
    
    switch(gizwitsProtocol.issuedFlag)
    {
        case ACTION_CONTROL_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.issuedProcessEvent, (uint8_t *)&gizwitsProtocol.gizCurrentDataPoint, sizeof(dataPoint_t));
            memset((uint8_t *)&gizwitsProtocol.issuedProcessEvent,0x0,sizeof(gizwitsProtocol.issuedProcessEvent));  
            break;
        case WIFI_STATUS_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.wifiStatusEvent, (uint8_t *)&gizwitsProtocol.wifiStatusData, sizeof(moduleStatusInfo_t));
            memset((uint8_t *)&gizwitsProtocol.wifiStatusEvent,0x0,sizeof(gizwitsProtocol.wifiStatusEvent));
            break;
        case ACTION_W2D_TRANSPARENT_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.issuedProcessEvent, (uint8_t *)gizwitsProtocol.transparentBuff, gizwitsProtocol.transparentLen);
            break;
        case GET_NTP_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.NTPEvent, (uint8_t *)&gizwitsProtocol.TimeNTP, sizeof(protocolTime_t));
            memset((uint8_t *)&gizwitsProtocol.NTPEvent,0x0,sizeof(gizwitsProtocol.NTPEvent));
            break;
        case GET_MODULEINFO_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.moduleInfoEvent, (uint8_t *)&gizwitsProtocol.wifiModuleNews, sizeof(moduleInfo_t));
            memset((uint8_t *)&gizwitsProtocol.moduleInfoEvent,0x0,sizeof(moduleInfo_t));
            break;
        default:
            break;      
    }

    gizDevReportPolicy(currentData);

    return 0;
}

/**
* @brief gizwits report transparent data interface

* The user can call the interface to complete the reporting of private protocol data

* @param [in] data :Private protocol data
* @param [in] len  :Private protocol data length
* @return 0，success ;other，failure
*/
int32_t gizwitsPassthroughData(uint8_t * gizdata, uint32_t len)
{
	int32_t ret = 0;
	uint8_t tx_buf[MAX_PACKAGE_LEN];
	uint8_t *pTxBuf = tx_buf;
	uint16_t data_len = 6+len;
    if(NULL == gizdata)
    {
        GIZWITS_LOG("[ERR] gizwitsPassthroughData Error \n");
        return (-1);
    }

	*pTxBuf ++= 0xFF;
	*pTxBuf ++= 0xFF;
	*pTxBuf ++= (uint8_t)(data_len>>8);//len
	*pTxBuf ++= (uint8_t)(data_len);
	*pTxBuf ++= CMD_REPORT_P0;//0x1b cmd
	*pTxBuf ++= gizwitsProtocol.sn++;//sn
	*pTxBuf ++= 0x00;//flag
	*pTxBuf ++= 0x00;//flag
	*pTxBuf ++= ACTION_D2W_TRANSPARENT_DATA;//P0_Cmd

    memcpy(&tx_buf[9],gizdata,len);
    tx_buf[data_len + 4 - 1 ] = gizProtocolSum( tx_buf , (data_len+4));
    
	ret = uartWrite(tx_buf, data_len+4);
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    gizProtocolWaitAck(tx_buf, data_len+4);

    return 0;
}

/**@} */
