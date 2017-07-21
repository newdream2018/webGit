#ifndef _DAQ_CONTROL_H
#define _DAQ_CONTROL_H

#include "PlxApi.h"
#include "PlxInit.h"
#include "ConsFunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Global.h"
#include "Sinx.h"
#include "FileLogger.h"

/***********************************************************
  名称：SetBIT
  功能：设定BIT位为1
  参数：
		nIndex		位数
		pData		待设置的数
************************************************************/
void SetBIT(UINT nIndex, UINT* pData);
/***********************************************************
  名称：ResetBIT
  功能：设定BIT位为0
  参数：
		nIndex		位数
		pData		待设置的数
************************************************************/
void ResetBIT(UINT nIndex, UINT* pData);
/***********************************************************
  名称：WriteDWord
  功能：向硬件某地址写入数据 
  参数：
       pDevice      仪器句柄
	   address      端口地址
	   data         写入的数据
/**********************************************************/
void WriteDWord(PLX_DEVICE_OBJECT *pDevice, U32 address, U32 data);
/***********************************************************
  名称：ReadDWord
  功能：从硬件某地址读取数据    
  参数：
       pDevice      仪器句柄
	   address      端口地址
  返回值：
       读取到的数据
/**********************************************************/
U32 ReadDWord(PLX_DEVICE_OBJECT *pDevice, U32 address);

/***********************************************************
  名称：ConfigurePLL(临时在初始化后调用，以后放在配置采集函数中，由上位机初始化时基时直接配置)
  功能：配置锁相环   
  参数：
       Vi      仪器句柄
/**********************************************************/
void ConfigurePLL(ViSession Vi);

/***********************************************************
  名称：ConfigureOffset(临时在初始化后调用，以后放在配置通道函数中，由上位机初始化通道时直接配置)
  功能：配置通道偏置
  参数：
		Vi      仪器句柄
/**********************************************************/
void ConfigureOffset(ViSession Vi);

/***********************************************************
  名称：SetADCbySampleRate
  功能：根据采样率配置ADC   
  参数：
       Vi          仪器句柄
	   ch1Enabled  该设备通道1使能
	   ch2Enabled  该设备通道2使能
/**********************************************************/
void SetADCbySampleRate(ViSession Vi, ViBoolean ch1Enabled, ViBoolean ch2Enabled);

/***********************************************************
  名称：SetChannelRange
  功能：设置通道垂直灵敏度   
  参数：
       Vi      仪器句柄
	   Channel 通道名称
	   range   垂直灵敏度*10
/**********************************************************/
void SetChannelRange(ViSession Vi, ViConstString Channel, ViReal64 range);

/***********************************************************
  名称：SetChannelOffset
  功能：设置通道偏移   
  参数：
       Vi      仪器句柄
	   Channel 通道名称
	   offset  通道偏移
/**********************************************************/
void SetChannelOffset(ViSession Vi, ViConstString Channel, ViReal64 offset);

/***********************************************************
  名称：FetchWaveData
  功能：读取数据（普通模式）   
  参数：
       Vi        仪器句柄
	   Channel   通道名称
	   fetchdata 波形数据
/**********************************************************/
void FetchWaveData(ViSession Vi, ViConstString Channel, ViPByte fetchdata);

/***********************************************************
  名称：FetchWaveDataDDR
  功能：读取数据（DDR存储）   
  参数：
       Vi        仪器句柄
	   Channel   通道名称
	   fetchdata 波形数据
/**********************************************************/
void FetchWaveDataDDR(ViSession Vi, ViConstString Channel, ViPByte fetchdata);

/***********************************************************
  名称：MeasureBaseParam
  功能：参数测量   
  参数：
       Vi              仪器句柄
	   waveformArray   波形数据
	   Channel         通道名称
	   wameformSize    数据个数
	   range           垂直灵敏度*10
       offset          通道偏移
	   attenuation     衰减倍数
	   timePerRecord   一屏数据时间，时基*10
/**********************************************************/
void MeasureBaseParam(ViSession Vi, ViByte waveformArray[], ViConstString Channel, ViInt32 wameformSize, ViReal64 range, ViReal64 offset, ViReal64 attenuation, ViReal64 timePerRecord);

/***********************************************************
  名称：GetVoltValue
  功能：将读取的波形数据转化成电压值   
  参数：
       data            0~255的整型数
	   range_V         垂直灵敏度*10
	   offset_V        通道偏移
	   attenuation     衰减倍数
/**********************************************************/
ViReal64 GetVoltValue(ViInt32 data,ViReal64 range_V,ViReal64 offset_V, ViReal64 attenuation);

/***********************************************************
  名称：ExtractionAndInterpolation
  功能：抽点插值函数   
  参数：
       type            插值类型，0-正弦插值，1-线性插值
	   pSrc            源数据
	   length          源数据长度
	   multiples       插值倍数
	   pDst            目标数据
/**********************************************************/
void ExtractionAndInterpolation(int type, ViPByte pSrc, ViInt32 length, ViReal64 multiples,ViPByte pDst);


S16
	SelectDevice_DMA(
	PLX_DEVICE_KEY *pKey
	);

void
	PerformDma_9000(
	PLX_DEVICE_OBJECT *pDevice
	);

#endif