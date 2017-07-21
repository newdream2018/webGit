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
  ���ƣ�SetBIT
  ���ܣ��趨BITλΪ1
  ������
		nIndex		λ��
		pData		�����õ���
************************************************************/
void SetBIT(UINT nIndex, UINT* pData);
/***********************************************************
  ���ƣ�ResetBIT
  ���ܣ��趨BITλΪ0
  ������
		nIndex		λ��
		pData		�����õ���
************************************************************/
void ResetBIT(UINT nIndex, UINT* pData);
/***********************************************************
  ���ƣ�WriteDWord
  ���ܣ���Ӳ��ĳ��ַд������ 
  ������
       pDevice      �������
	   address      �˿ڵ�ַ
	   data         д�������
/**********************************************************/
void WriteDWord(PLX_DEVICE_OBJECT *pDevice, U32 address, U32 data);
/***********************************************************
  ���ƣ�ReadDWord
  ���ܣ���Ӳ��ĳ��ַ��ȡ����    
  ������
       pDevice      �������
	   address      �˿ڵ�ַ
  ����ֵ��
       ��ȡ��������
/**********************************************************/
U32 ReadDWord(PLX_DEVICE_OBJECT *pDevice, U32 address);

/***********************************************************
  ���ƣ�ConfigurePLL(��ʱ�ڳ�ʼ������ã��Ժ�������òɼ������У�����λ����ʼ��ʱ��ʱֱ������)
  ���ܣ��������໷   
  ������
       Vi      �������
/**********************************************************/
void ConfigurePLL(ViSession Vi);

/***********************************************************
  ���ƣ�ConfigureOffset(��ʱ�ڳ�ʼ������ã��Ժ��������ͨ�������У�����λ����ʼ��ͨ��ʱֱ������)
  ���ܣ�����ͨ��ƫ��
  ������
		Vi      �������
/**********************************************************/
void ConfigureOffset(ViSession Vi);

/***********************************************************
  ���ƣ�SetADCbySampleRate
  ���ܣ����ݲ���������ADC   
  ������
       Vi          �������
	   ch1Enabled  ���豸ͨ��1ʹ��
	   ch2Enabled  ���豸ͨ��2ʹ��
/**********************************************************/
void SetADCbySampleRate(ViSession Vi, ViBoolean ch1Enabled, ViBoolean ch2Enabled);

/***********************************************************
  ���ƣ�SetChannelRange
  ���ܣ�����ͨ����ֱ������   
  ������
       Vi      �������
	   Channel ͨ������
	   range   ��ֱ������*10
/**********************************************************/
void SetChannelRange(ViSession Vi, ViConstString Channel, ViReal64 range);

/***********************************************************
  ���ƣ�SetChannelOffset
  ���ܣ�����ͨ��ƫ��   
  ������
       Vi      �������
	   Channel ͨ������
	   offset  ͨ��ƫ��
/**********************************************************/
void SetChannelOffset(ViSession Vi, ViConstString Channel, ViReal64 offset);

/***********************************************************
  ���ƣ�FetchWaveData
  ���ܣ���ȡ���ݣ���ͨģʽ��   
  ������
       Vi        �������
	   Channel   ͨ������
	   fetchdata ��������
/**********************************************************/
void FetchWaveData(ViSession Vi, ViConstString Channel, ViPByte fetchdata);

/***********************************************************
  ���ƣ�FetchWaveDataDDR
  ���ܣ���ȡ���ݣ�DDR�洢��   
  ������
       Vi        �������
	   Channel   ͨ������
	   fetchdata ��������
/**********************************************************/
void FetchWaveDataDDR(ViSession Vi, ViConstString Channel, ViPByte fetchdata);

/***********************************************************
  ���ƣ�MeasureBaseParam
  ���ܣ���������   
  ������
       Vi              �������
	   waveformArray   ��������
	   Channel         ͨ������
	   wameformSize    ���ݸ���
	   range           ��ֱ������*10
       offset          ͨ��ƫ��
	   attenuation     ˥������
	   timePerRecord   һ������ʱ�䣬ʱ��*10
/**********************************************************/
void MeasureBaseParam(ViSession Vi, ViByte waveformArray[], ViConstString Channel, ViInt32 wameformSize, ViReal64 range, ViReal64 offset, ViReal64 attenuation, ViReal64 timePerRecord);

/***********************************************************
  ���ƣ�GetVoltValue
  ���ܣ�����ȡ�Ĳ�������ת���ɵ�ѹֵ   
  ������
       data            0~255��������
	   range_V         ��ֱ������*10
	   offset_V        ͨ��ƫ��
	   attenuation     ˥������
/**********************************************************/
ViReal64 GetVoltValue(ViInt32 data,ViReal64 range_V,ViReal64 offset_V, ViReal64 attenuation);

/***********************************************************
  ���ƣ�ExtractionAndInterpolation
  ���ܣ�����ֵ����   
  ������
       type            ��ֵ���ͣ�0-���Ҳ�ֵ��1-���Բ�ֵ
	   pSrc            Դ����
	   length          Դ���ݳ���
	   multiples       ��ֵ����
	   pDst            Ŀ������
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