#include "StdAfx.h"
#include "DAQ_Control.h"
#include <sys/timeb.h>
#include<time.h>

#define UPDATE_DISPLAY_SEC              4

void SetBIT(UINT nIndex, UINT* pData)
{
	*pData |= (1 << nIndex);
}

void ResetBIT(UINT nIndex, UINT* pData)
{
	*pData &= ( ~(1 << nIndex));
}

void WriteDWord(PLX_DEVICE_OBJECT *pDevice, U32 address, U32 data)
{
	PlxPci_PciBarSpaceWrite(pDevice, 2, address, &data, 4, BitSize32, TRUE);
	LOG(LOG_TYPE_INFO, "WriteDWord: Adress = 0x%x, Data = 0x%x", address, data);
}

U32 ReadDWord(PLX_DEVICE_OBJECT *pDevice, U32 address)
{
	U32 data;
	PlxPci_PciBarSpaceRead(pDevice, 2, address, &data, 4, BitSize32, TRUE);
	LOG(LOG_TYPE_INFO, "ReadDWord: Adress = 0x%x, Data = 0x%x", address, data);
	return data;
}

// �������໷
void ConfigurePLL(ViSession Vi)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	for(int i = 1; i<7; i++)
	{
		// 0x58c
		WriteDWord(pDevice, g_deviceParam->Command.Port[99], 0x00000001*i);
		Sleep(10);
		// 0x594
		WriteDWord(pDevice, g_deviceParam->Command.Port[101], 0x00000000);
		Sleep(10);
		WriteDWord(pDevice, g_deviceParam->Command.Port[101], 0x00000001);
		Sleep(10);
		WriteDWord(pDevice, g_deviceParam->Command.Port[101], 0x00000000);
		Sleep(10);
	}
}

void ConfigureOffset(ViSession Vi)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;
	// 0x4F4
	WriteDWord(pDevice, g_deviceParam->Command.Port[61], 0x00200B70);
	// 0x504
	WriteDWord(pDevice, g_deviceParam->Command.Port[65], 0x00000000);
	WriteDWord(pDevice, g_deviceParam->Command.Port[65], 0x00000001);
	WriteDWord(pDevice, g_deviceParam->Command.Port[65], 0x00000000);
	WriteDWord(pDevice, g_deviceParam->Command.Port[65], 0x00000001);
}

// ���ò�����
void SetADCbySampleRate(ViSession Vi, ViBoolean ch1Enabled, ViBoolean ch2Enabled)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	// ��ADC���и�λ
	// �˿�70��Port[70] = 70*4 + 0x400 = 280 + 0x400 = 0x118 + 0x400 = 0x518
	WriteDWord(pDevice, g_deviceParam->Command.Port[70], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[70], 0x00000001);
	Sleep(20);

	// ����ͬ���ź�
	// �˿�71��Port[71] = 71*4 = 284 + 0x400 = 0x51c
	WriteDWord(pDevice, g_deviceParam->Command.Port[71], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[71], 0x00000001);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[71], 0x00000000);

	// ���ݲ���������ADC�����ͨ���й�
	// �˿�69��Port[69] = 69*4 + 0x400 = 276 + 0x400 = 0x514
	if (g_deviceParam->Acquisition.AdcSampleRate == 1250000000 && g_deviceParam->Acquisition.HardwareSampleRate == 5000000000)// ����ͨ��5G������		
	{		
		if (ch1Enabled)// CH1ʹ��
		{
			g_deviceParam->Command.Word[69] = 0x810008;
		}
		else if (ch2Enabled)// CH2ʹ��
		{
			g_deviceParam->Command.Word[69] = 0x81000A;
		}		
	}
	else//2.5G˫ͨ������
	{
		g_deviceParam->Command.Word[69] = 0x810004;
	}	
	WriteDWord(pDevice, g_deviceParam->Command.Port[69], g_deviceParam->Command.Word[69]);
	Sleep(1);

	// �����ּ���
	// �˿�72��Port[72] = 72*4 + 0x400 = 288 + 0x400 = 0x520
	WriteDWord(pDevice, g_deviceParam->Command.Port[72], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[72], 0x00000001);
	Sleep(100);
	// ����ͬ���ź�
	// �˿�71��Port[71] = 71*4 = 284 + 0x400 = 0x51c
	WriteDWord(pDevice, g_deviceParam->Command.Port[71], 0x00000001);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[71], 0x00000000);
}

// ����ͨ����ֱ������
void SetChannelRange(ViSession Vi, ViConstString Channel, ViReal64 range)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	// ����˥������ѡ��Ҫ���͵Ŀ�����A����6λ��Ч��
	// �˿�60���ƣ�Port[60] = 60*4 + 0x400 = 0x4f0
	UINT valA = 0;
	if (Equals(range, 0.2))
	{
		// 20mV/div -- ��˥�� ����  0dB    ����    00
		valA = 0x00000000;
	}
	else if (Equals(range, 0.5)) 
	{
		// 20mV/div -- ��˥�� ����  0dB    ����    00
		valA = 0x0000000C;
	}
	else if (Equals(range, 1.0))
	{
		// 100mV/div -- 5��˥��   ���� 14dB   ����  1C
		valA = 0x0000001C;
	}
	else if (Equals(range, 2.0))
	{
		//200mV/div -- 10��˥��  ���� 20dB   ����  28
		valA = 0x00000028;
	}
	else if (Equals(range, 5.0))
	{
		//500mV/div -- 20��˥��  ���� 26dB   ����  34
		valA = 0x00000034;
	}
	else if (Equals(range, 10.0))
	{
		//1V/div    -- 40��˥��  ���� 31.5dB  ���� 3F 
		valA = 0x0000003F;
	}
	g_deviceParam->Command.Word[60] = valA;
	WriteDWord(pDevice, g_deviceParam->Command.Port[60], g_deviceParam->Command.Word[60]);
	Sleep(20);

	// ����Ҫ���õ�ͨ��ѡ��Ҫ���͵Ŀ�����B���ڶ�λ��Ч��0/CH1 ��1/CH2��
	// �˿�67���ƣ�Port[67] = 67*4 + 0x400 = 0x50c
	if (_stricmp(Channel, g_deviceParam->ActualChannel[0].Name) == 0)//CH1
	{
		ResetBIT(2, &g_deviceParam->Command.Word[67]);
	}
	else if (_stricmp(Channel, g_deviceParam->ActualChannel[1].Name) == 0)//CH2
	{
		SetBIT(2, &g_deviceParam->Command.Word[67]);	
	}
	WriteDWord(pDevice, g_deviceParam->Command.Port[67], g_deviceParam->Command.Word[67]);
	Sleep(20);

	// �����ּ���
	// �˿�64���ƣ�Port[64] = 64*4 + 0x400 = 0x500
	WriteDWord(pDevice, g_deviceParam->Command.Port[64], 0x00000000);
	Sleep(20);
	WriteDWord(pDevice, g_deviceParam->Command.Port[64], 0x00000001);
	Sleep(20);
	WriteDWord(pDevice, g_deviceParam->Command.Port[64], 0x00000000);
	Sleep(20);
}

void SetChannelOffset(ViSession Vi, ViConstString Channel, ViReal64 offset)
{

}

// ��ͨ�洢����
void FetchWaveData(ViSession Vi, ViConstString Channel, ViPByte fetchdata)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	ViInt32 *tempData = new ViInt32[g_deviceParam->Base.MemoryDepth];
	memset(tempData,0,g_deviceParam->Base.MemoryDepth*sizeof(ViInt32));

	// ��ȡ����
	int data = 0;
	for (int i = 0; i<650; i++)// ��0x580�˿ڽ���650�ζ������������ǰ600�ζ�����������
	{
		// �����˿�,Port[96] = 96*4 + 0x400 = 0x580		
		data = ReadDWord(pDevice,g_deviceParam->Command.Port[96]);
		if(i<g_deviceParam->Base.MemoryDepth)
		{
			tempData[i] = data;
		}
	}

	// dataΪ32λ�������ݣ��ɷ�Ϊ4��8λ��������
	for (int i = 0; i<g_deviceParam->Base.MemoryDepth; i++)
	{
		fetchdata[4*i + 0] = tempData[i]&0x000000FF;
		fetchdata[4*i + 1] = (tempData[i]&0x0000FF00)>>8;
		fetchdata[4*i + 2] = (tempData[i]&0x00FF0000)>>16;
		fetchdata[4*i + 3] = (tempData[i]&0xFF000000)>>24;
	}
	delete tempData;
	tempData = NULL;
}

// DDR����
void FetchWaveDataDDR(ViSession Vi, ViConstString Channel, ViPByte fetchdata)
{
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

/*	ViInt32 *tempData = new ViInt32[g_deviceParam->Base.MemoryDepth];
	memset(tempData,0,g_deviceParam->Base.MemoryDepth*sizeof(ViInt32));

	// ��ȡ����
	int data = 0;
	for (int i = 0; i<12000; i++)
	{
		// �����˿�,Port[3] = 3*4 + 0x400 = 0x40c	
		data = ReadDWord(pDevice,g_deviceParam->Command.Port[3]);
		if(i<g_deviceParam->Base.MemoryDepth)
		{
			tempData[i] = data;
		}
	}

	// ��λ
	WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000000);
	Sleep(1);
	// dataΪ32λ�������ݣ��ɷ�Ϊ4��8λ��������
	for (int i = 0; i<g_deviceParam->Base.MemoryDepth; i++)
	{
		fetchdata[4*i + 0] = tempData[i]&0x000000FF;
		fetchdata[4*i + 1] = (tempData[i]&0x0000FF00)>>8;
		fetchdata[4*i + 2] = (tempData[i]&0x00FF0000)>>16;
		fetchdata[4*i + 3] = (tempData[i]&0xFF000000)>>24;
	}
	delete tempData;
	tempData = NULL;
*/
	// DMA����
	PerformDma_9000(pDevice);

	// ��λ
	WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000000);
	Sleep(1);
	WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000000);
	Sleep(1);
	
}
/************************************************************************/
/*                               ��������                               */
/************************************************************************/
void MeasureBaseParam(ViSession Vi, ViByte waveformArray[], ViConstString Channel, ViInt32 wameformSize, ViReal64 range, ViReal64 offset, ViReal64 attenuation, ViReal64 timePerRecord)
{
	double maximum = 0.0;
	double minimum = 0.0;
	double peaktopeak = 0.0;
	double high = 0.0;
	double low = 0.0;
	double amplitude = 0.0;
	double average = 0.0;
	double rms = 0.0;
	double period = 0.0;
	double frequency = 0.0;
	double riseTime = 0.0;
	double fallTime = 0.0;
	double positiveWidth = 0.0;
	double negativeWidth = 0.0;
	double positiveDutyCycle = 0.0;

	int i;
	int theMaximum = 0;
	int theMinimum = 0;
	int adcMaximum = 255;
	double lowRef = 0.1; 
	double midRef = 0.5;
	double highRef = 0.9;
	int theLow = 0;
	int theHigh = 0;
	double theSum = 0.0;
	int theMean = 0;
	double thePowSum = 0.0;
	double thePowMean = 0.0; 
	int theLength = 0;

	int theTempVal = 0;
	double theTempVal2 = 0.0;
	double theLowRef = 0.0;
	double theMidRef = 0.0;
	double theHighRef = 0.0;
	int theLowThreshold = 0;
	int theMidThreshold = 0;
	int theHighThreshold = 0;
	double preshoot = 0.0;
	double overshoot = 0.0;

	int theIndex = 0;
	bool theFirstEdgeExists = false;
	int theFirstEdgeSlope = 0;
	int theFirstEdgeBeginIndex = 0;
	int theFirstEdgeMidIndex = 0;
	int theFirstEdgeEndIndex = 0;
	bool theSecondEdgeExists = false;
	int theSecondEdgeSlope = 0;
	int theSecondEdgeBeginIndex = 0;
	int theSecondEdgeMidIndex = 0;
	int theSecondEdgeEndIndex = 0;
	bool theThirdEdgeExists = false;
	int theThirdEdgeSlope = 0;
	int theThirdEdgeBeginIndex = 0;
	int theThirdEdgeMidIndex = 0;
	int theThirdEdgeEndIndex = 0;
	int *waveformMeanArray = NULL;
	int *waveformHistogramArray = NULL;

	// �������ֵ����Сֵ�����ֵ
	theMaximum = ViInt32(waveformArray[0]);
	theMinimum = ViInt32(waveformArray[0]);
	for ( i=1; i<wameformSize; i++)
	{
		if (theMaximum < ViInt32(waveformArray[i]))
		{
			theMaximum = ViInt32(waveformArray[i]);
		}
		if (theMinimum > ViInt32(waveformArray[i]))
		{
			theMinimum = ViInt32(waveformArray[i]);
		}
	}	
	//��0~255��Χ�ĵ�ѹֵ�任Ϊʵ�ʵ�ѹֵ�����洢���������Ľṹ��
	maximum = GetVoltValue(theMaximum , range, offset, attenuation);
	minimum = GetVoltValue(theMinimum , range, offset, attenuation);
	peaktopeak = maximum - minimum;	 

	// ����ƽ��ֵ
	theSum = 0.0;
	for ( i=0; i < wameformSize; i++)
	{
		theSum += waveformArray[i];
	}

	theMean = (ViInt32)(theSum / wameformSize);
	average = GetVoltValue(theMean, range, offset, attenuation);

	// ���㲨�������ֵ����
	theLength = wameformSize;
	waveformMeanArray = new int[theLength];  
	ZeroMemory(waveformMeanArray, theLength * sizeof(int));
	for (i = 0; i < theLength; i++)
	{
		waveformMeanArray[i] = waveformArray[i];
	}	

	// ���㲨�������ֵ����ֱ��ͼ
	theLength = adcMaximum + 1;
	waveformHistogramArray = new int[theLength];     
	ZeroMemory(waveformHistogramArray, theLength * sizeof(int));
	for (i = 0; i < wameformSize; i++)
	{
		waveformHistogramArray[waveformMeanArray[i]]++;
	}

	// ����׶�ֵ�Ͷ���ֵ������ֵ
	theLowRef = 0.4;
	theHighRef = 0.6;
	theLowThreshold = ViInt32(theMinimum + (theMaximum - theMinimum) * theLowRef);
	theHighThreshold = ViInt32(theMinimum + (theMaximum - theMinimum) * theHighRef);
	theTempVal = 0;
	for (i = 0; i < theLowThreshold; i++)
	{
		if (waveformHistogramArray[i] > theTempVal)
		{
			theTempVal = waveformHistogramArray[i];
			theLow = i;
		}
	}
	theLength = adcMaximum + 1;
	theTempVal = 0;
	for (i = theHighThreshold; i < theLength; i++)
	{
		if (waveformHistogramArray[i] > theTempVal)
		{
			theTempVal = waveformHistogramArray[i];
			theHigh = i;
		}
	}	

	// �׶�ֵ�Ͷ���ֵ��Ӧֱ��ͼ��ֵ������ڵ��ڲ������� * 5%
	theTempVal = ViInt32(wameformSize * 0.05);
	if (waveformHistogramArray[theLow] < theTempVal)
	{
		theLow = theMinimum;
	}
	if (waveformHistogramArray[theHigh] < theTempVal)
	{
		theHigh = theMaximum;
	}

	low = GetVoltValue(theLow, range, offset, attenuation);
	high = GetVoltValue(theHigh, range, offset, attenuation);
	amplitude = high - low;

	// ����ǰ�����
	theLowRef = lowRef;
	theMidRef = midRef;
	theHighRef = highRef;
	theLowThreshold = ViInt32(theLow + (theHigh - theLow) * theLowRef);
	theMidThreshold = ViInt32(theLow + (theHigh - theLow) * theMidRef);
	theHighThreshold = ViInt32(theLow + (theHigh - theLow) * theHighRef);
	theFirstEdgeBeginIndex = 0;
	theFirstEdgeEndIndex = 0;
	theSecondEdgeBeginIndex = 0;
	theSecondEdgeEndIndex = 0;
	theThirdEdgeBeginIndex = 0;
	theThirdEdgeEndIndex = 0;
	theLength = wameformSize -1;

	//�����һ������
	theFirstEdgeExists = false;
	theFirstEdgeSlope = 0;
	for (i = 0; i < theLength; i++)
	{
		if ((theFirstEdgeBeginIndex == 0) && (((waveformMeanArray[i] <= theLowThreshold) && (waveformMeanArray[i + 1] > theLowThreshold)) || ((waveformMeanArray[i] >= theHighThreshold) && (waveformMeanArray[i + 1] < theHighThreshold))))
		{
			theFirstEdgeBeginIndex = i;
		}
		else if ((theFirstEdgeBeginIndex != 0) && 
			(((waveformMeanArray[theFirstEdgeBeginIndex] <= theLowThreshold) && (waveformMeanArray[i] > theHighThreshold)) || 
			((waveformMeanArray[theFirstEdgeBeginIndex] >= theHighThreshold) && (waveformMeanArray[i] < theLowThreshold))))
		{
			theFirstEdgeEndIndex = i;
			break;
		}
	}  
	//�ж��Ƿ���ڵ�һ������
	theFirstEdgeExists = false;
	theFirstEdgeSlope = 0;
	if (theFirstEdgeBeginIndex != 0 && theFirstEdgeEndIndex!= 0)
	{
		theFirstEdgeExists = true;
		if (waveformMeanArray[theFirstEdgeBeginIndex] < waveformMeanArray[theFirstEdgeEndIndex])
		{
			theFirstEdgeSlope = 1;
		}
		//�����һ�����м�ֵ��ַ
		for (i = theFirstEdgeBeginIndex; i < theFirstEdgeEndIndex; i++)
		{
			if ((((waveformMeanArray[i] <= theMidThreshold) && (waveformMeanArray[i + 1] > theMidThreshold)) || ((waveformMeanArray[i] >= theMidThreshold) && (waveformMeanArray[i + 1] < theMidThreshold))))
			{
				theFirstEdgeMidIndex = i;
				break;
			}
		}  
		if (theFirstEdgeMidIndex == 0)
		{
			theFirstEdgeMidIndex = theFirstEdgeBeginIndex;
		}
	}        	                               
	//����ڶ�������
	if (theFirstEdgeExists)
	{
		for (i = theFirstEdgeEndIndex; i < theLength; i++)
		{
			if ((theSecondEdgeBeginIndex == 0) &&
				(((waveformMeanArray[i] <= theLowThreshold) && (waveformMeanArray[i + 1] > theLowThreshold)) ||
				((waveformMeanArray[i] >= theHighThreshold) && (waveformMeanArray[i + 1] < theHighThreshold))))
			{
				theSecondEdgeBeginIndex = i;
			}
			else if ((theSecondEdgeBeginIndex != 0) &&
				(((waveformMeanArray[theSecondEdgeBeginIndex] <= theLowThreshold) && (waveformMeanArray[i] > theHighThreshold)) || 
				((waveformMeanArray[theSecondEdgeBeginIndex] >= theHighThreshold) && (waveformMeanArray[i] < theLowThreshold))))
			{
				theSecondEdgeEndIndex = i;
				break;
			}
		}
		//�ж��Ƿ���ڵڶ�������
		theSecondEdgeExists = false;
		theSecondEdgeSlope = 0;
		if (theSecondEdgeBeginIndex != 0 && theSecondEdgeEndIndex != 0)
		{
			theSecondEdgeExists = true;
			if (waveformMeanArray[theSecondEdgeBeginIndex] < waveformMeanArray[theSecondEdgeEndIndex])
			{
				theSecondEdgeSlope = 1;
			}	  
			//������������м�ֵ��ַ
			for (i = theSecondEdgeBeginIndex; i < theSecondEdgeEndIndex; i++)
			{
				if ((((waveformMeanArray[i] <= theMidThreshold) && (waveformMeanArray[i + 1] > theMidThreshold)) || ((waveformMeanArray[i] >= theMidThreshold) && (waveformMeanArray[i + 1] < theMidThreshold))))
				{
					theSecondEdgeMidIndex = i;
					break;
				}
			} 
			if (theSecondEdgeMidIndex == 0)
			{
				theSecondEdgeMidIndex = theSecondEdgeBeginIndex;
			}
		}           
	}	 
	//�������������
	if (theSecondEdgeExists)
	{
		for (i = theSecondEdgeEndIndex; i < theLength; i++)
		{
			if ((theThirdEdgeBeginIndex == 0) &&
				(((waveformMeanArray[i] <= theLowThreshold) && (waveformMeanArray[i + 1] > theLowThreshold)) ||
				((waveformMeanArray[i] >= theHighThreshold) && (waveformMeanArray[i + 1] < theHighThreshold))))
			{
				theThirdEdgeBeginIndex = i;
			}
			else if ((theThirdEdgeBeginIndex != 0) &&
				(((waveformMeanArray[theThirdEdgeBeginIndex] <= theLowThreshold) && (waveformMeanArray[i] > theHighThreshold)) || 
				((waveformMeanArray[theThirdEdgeBeginIndex] >= theHighThreshold) && (waveformMeanArray[i] < theLowThreshold))))
			{
				theThirdEdgeEndIndex = i;
				break;
			}
		}    	 
		//�ж��Ƿ���ڵ���������
		theThirdEdgeExists = false;
		theThirdEdgeSlope = 0;
		if (theThirdEdgeBeginIndex != 0 && theThirdEdgeEndIndex != 0)
		{
			theThirdEdgeExists = true;
			if (waveformMeanArray[theThirdEdgeBeginIndex] < waveformMeanArray[theThirdEdgeEndIndex])
			{
				theThirdEdgeSlope = 1;
			}	        
			//������������м�ֵ��ַ
			for (i = theThirdEdgeBeginIndex; i < theThirdEdgeEndIndex; i++)
			{
				if ((((waveformMeanArray[i] <= theMidThreshold) && (waveformMeanArray[i + 1] > theMidThreshold)) || ((waveformMeanArray[i] >= theMidThreshold) && (waveformMeanArray[i + 1] < theMidThreshold))))
				{
					theThirdEdgeMidIndex = i;
					break;
				}
			}
			if (theThirdEdgeMidIndex == 0)
			{
				theThirdEdgeMidIndex = theThirdEdgeBeginIndex;
			}
		}
	}	 

	//��������Ƶ��
	if (!theThirdEdgeExists)
	{
		period = 0.0;
		frequency = 0.0;
	}
	else
	{
		period = (theThirdEdgeMidIndex - theFirstEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) *1000;
		frequency = 1 / period;
	}		  

	//���������½�ʱ��	 
	if (!theFirstEdgeExists)
	{
		riseTime = 0.0;
		fallTime = 0.0;
	}
	else if (theFirstEdgeExists && !theSecondEdgeExists)
	{
		if (theFirstEdgeSlope == 1)
		{
			riseTime = (theFirstEdgeEndIndex - theFirstEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1.0e+9;
			fallTime = 0.0;
		}
		else
		{
			riseTime = 0.0;
			fallTime = (theFirstEdgeEndIndex - theFirstEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1.0e+9;
		}
	}	 
	else if (theFirstEdgeExists && theSecondEdgeExists)
	{
		if (theFirstEdgeSlope == 1)
		{
			riseTime = (theFirstEdgeEndIndex - theFirstEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1.0e+9;
			fallTime = (theSecondEdgeEndIndex - theSecondEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1.0e+9;
		}
		else
		{
			riseTime = (theSecondEdgeEndIndex - theSecondEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500)* 1.0e+9;
			fallTime = (theFirstEdgeEndIndex - theFirstEdgeBeginIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1.0e+9;
		}
	}	 

	//��������ռ�ձ�
	if (!theSecondEdgeExists)
	{
		positiveWidth = 0.0;
		negativeWidth = 0.0;
		positiveDutyCycle = 0.0;
	}
	else if (theSecondEdgeExists && !theThirdEdgeExists)
	{
		if (theFirstEdgeSlope == 1)
		{
			positiveWidth = (theSecondEdgeMidIndex - theFirstEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			negativeWidth = 0.0;
			positiveDutyCycle = 0.0;
		}
		else
		{
			positiveWidth = 0.0;
			negativeWidth = (theSecondEdgeMidIndex - theFirstEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			positiveDutyCycle = 0.0;
		}
	}
	else if (theSecondEdgeExists && theThirdEdgeExists)
	{
		if (theFirstEdgeSlope == 1)
		{
			positiveWidth = (theSecondEdgeMidIndex - theFirstEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			negativeWidth = (theThirdEdgeMidIndex - theSecondEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			positiveDutyCycle = positiveWidth * 100 / period;
		}
		else
		{
			positiveWidth = (theThirdEdgeMidIndex - theSecondEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			negativeWidth = (theSecondEdgeMidIndex - theFirstEdgeMidIndex) / g_deviceParam->Acquisition.SoftwareMultiple * (timePerRecord / 500) * 1000;
			positiveDutyCycle = positiveWidth * 100 / period;
		}
	}	 
	//���������(AC)
	theSum = 0.0;
	thePowSum = 0.0;
	for (i = 0; i < wameformSize; i++)
	{
		theTempVal2 = ((waveformMeanArray[i] - (adcMaximum / 2.0)) * (range / adcMaximum)) * attenuation;
		theSum += theTempVal2;
		thePowSum += theTempVal2 * theTempVal2;
	}
	theMean = (ViInt32)theSum / (wameformSize);
	thePowMean = thePowSum / (wameformSize);
	rms = sqrt(thePowMean - theMean * theMean);	 


	int index = 0;
	for (int i = 0; i<4; i++)
	{
		if ((g_deviceParam->Channel[i].DeviceHandle == Vi) && (_stricmp(Channel, g_deviceParam->Channel[i].ActualName) == 0))
		{
			index = i;
			break;
		}
	}

	g_deviceParam->Measurement[index].m_dMax_V = maximum;
	g_deviceParam->Measurement[index].m_dMin_V = minimum;
	g_deviceParam->Measurement[index].m_dPeakToPeak_V = peaktopeak;
	g_deviceParam->Measurement[index].m_dLow_V = low;
	g_deviceParam->Measurement[index].m_dHigh_V = high;
	g_deviceParam->Measurement[index].m_dAmplitude_V = amplitude;
	g_deviceParam->Measurement[index].m_dPeriod_mS = period;
	g_deviceParam->Measurement[index].m_dFrequency_KHz = frequency;
	g_deviceParam->Measurement[index].m_dRMS_V = rms;
	g_deviceParam->Measurement[index].m_dAverage_V = average;
	g_deviceParam->Measurement[index].m_dRiseTime_nS = riseTime;
	g_deviceParam->Measurement[index].m_dFallTime_nS = fallTime;
	g_deviceParam->Measurement[index].m_dWidthPos_mS = positiveWidth;
	g_deviceParam->Measurement[index].m_dWidthNeg_mS = negativeWidth;		
	g_deviceParam->Measurement[index].m_dDutyCyclePos = positiveDutyCycle;


	delete waveformMeanArray;
	waveformMeanArray = NULL;
	delete waveformHistogramArray;
	waveformHistogramArray = NULL;
}

ViReal64 GetVoltValue(ViInt32 data,ViReal64 range_V,ViReal64 offset_V, ViReal64 attenuation)
{
	ViReal64 val_V = (data - 127.5) / 25.5;  //�õ����ٸ�
	val_V *= range_V / 10;                   //����ÿ����ٷ����õ���ѹֵ
	val_V -= offset_V;                       //ƫ��ƫ��Ϊ����ƫ��Ϊ��������ƫ�Ƶ�ѹ���õ���ѹֵ
	val_V *= attenuation;                    //����˥���������õ���ѹֵ
	return val_V;
}

void ExtractionAndInterpolation(int type, ViPByte pSrc, ViInt32 length, ViReal64 multiples,ViPByte pDst)
{
	if (type == 0)//���Ҳ�ֵ
	{
		if ((multiples > 0.019) && (multiples < 0.021))//0.02  1->50   50����ֵ 
		{
			SinxKenerl50(pDst,pSrc,length);
		}
		else if ((multiples > 0.024) && (multiples < 0.026))//0.025  1->40   40����ֵ 20����ֵ,Ȼ��2����ֵ
		{
			ViPByte tempData = new ViByte[length * 20];
			memset(tempData,0,length * 20 );
			SinxKenerl20(tempData,pSrc,length);
			SinxKenerl2(pDst,tempData,length * 20);
			delete []tempData;
			tempData = NULL;
		}
		else if ((multiples > 0.039) && (multiples < 0.041))//0.04  1->25   25����ֵ
		{
			SinxKenerl25(pDst,pSrc,length);
		}
		else if ((multiples >0.049) && (multiples < 0.051))//0.05  1->20   20����ֵ 
		{
			SinxKenerl20(pDst,pSrc,length);
		}
		else if ((multiples >0.079) && (multiples < 0.081))//0.08  1->12.5  ��25����ֵ,Ȼ��2�����  12.5����ֵ
		{
			ViPByte tempData = new ViByte[length * 25];
			memset(tempData,0,length * 25 );
			SinxKenerl25(tempData,pSrc,length);
			SampleData(tempData, pDst, length*25 / 2, 2);
			delete []tempData;
			tempData = NULL;
		}
		else if ((multiples >0.09) && (multiples < 0.11))//0.1  1->10   10����ֵ
		{
			SinxKenerl10(pDst,pSrc,length);
		}
		else if ((multiples >0.124) && (multiples < 0.126))//0.125  1->8   8����ֵ
		{
			SinxKenerl8(pDst,pSrc,length);
		}
		else if ((multiples >0.19) && (multiples < 0.21))//0.2  1->5     5����ֵ
		{
			SinxKenerl5(pDst,pSrc,length);
		}
		else if ((multiples >0.249) && (multiples < 0.251))//0.25  1->4   ��20����ֵ��5�����
		{
			SinxKenerl4(pDst,pSrc,length);
		}
		else if ((multiples > 0.399) && (multiples < 0.401))//0.4   1->2.5   ��10����ֵ��4����� 
		{
			ViPByte tempData = new ViByte[length * 10];
			memset(tempData,0,length * 10 );
			SinxKenerl10(tempData,pSrc,length);
			SampleData(tempData, pDst, length*10 / 4, 4);
			delete []tempData;
			tempData = NULL;
		}
		else if ((multiples >0.49) && (multiples < 0.51))//0.5  1->2  10����ֵ5�����
		{
			SinxKenerl2(pDst,pSrc,length);
		}
		else if ((multiples >0.9) && (multiples < 1.1))//1�����
		{
			SampleData(pSrc, pDst, (ViInt32)length , 1);
		}
		else if ((multiples > 1.24) && (multiples < 1.26))//1.25�����    8����ֵ,10�����
		{
			ViPByte pData = new ViByte[length * 8];
			SinxKenerl8(pData, pSrc, length);
			SampleData(pData, pDst, length * 8 / 10, 10);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples > 1.9) && (multiples < 2.1))// 2�����
		{
			SampleData(pSrc, pDst, length / 2, 2);
		}
		else if ((multiples > 2.4) && (multiples < 2.6))//2.5�����      8����ֵ,20�����
		{
			ViPByte pData = new ViByte[length * 8];
			SinxKenerl8(pData, pSrc, length);
			SampleData(pData, pDst, length * 8 / 20, 20);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples >4.9) && (multiples < 5.1))//5�����
		{
			SampleData(pSrc, pDst, length / 5, 5);
		}
		else if ((multiples >9.9) && (multiples < 10.1))//10�����
		{
			SampleData(pSrc, pDst, length / 10, 10);
		}
		else if ((multiples > 12.4) && (multiples < 12.6))//12.5�����    4����ֵ,50����� 
		{
			ViPByte pData = new ViByte[length * 4];
			SinxKenerl4(pDst,pSrc,length);
			SampleData(pData, pDst, length * 4 / 50, 50);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples >19.9) && (multiples < 20.1))//20�����
		{
			SampleData(pSrc, pDst, length / 20, 20);
		}
		else if ((multiples >24.9) && (multiples < 25.1))//25�����
		{
			SampleData(pSrc, pDst, length / 25, 25);
		}
		else if ((multiples >39.9) && (multiples < 40.1))//40�����
		{
			SampleData(pSrc, pDst, length / 40, 40);
		}
		else if ((multiples >49.9) && (multiples < 50.1))//50�����
		{
			SampleData(pSrc, pDst, length / 50, 50);
		}
		else if ((multiples >79.9) && (multiples < 80.1))//80�����
		{
			SampleData(pSrc, pDst, (ViInt32)length / 80, 80);
		}
	} 
	else if (type == 1)//���Բ�ֵ
	{
		if ((multiples > 0.019) && (multiples < 0.021))//0.02  1->50   50����ֵ 
		{
			LineInterpolation(pSrc, length, 50, pDst);
		}
		else if ((multiples > 0.024) && (multiples < 0.026))//0.025  1->40   40����ֵ 20����ֵ,Ȼ��2����ֵ
		{
			LineInterpolation(pSrc, length, 40, pDst);
		}
		else if ((multiples > 0.039) && (multiples < 0.041))//0.04  1->25   25����ֵ
		{
			LineInterpolation(pSrc, length, 25, pDst);
		}
		else if ((multiples >0.049) && (multiples < 0.051))//0.05  1->20   20����ֵ
		{
			LineInterpolation(pSrc, length, 20, pDst);
		}
		else if ((multiples >0.079) && (multiples < 0.081))//0.08  1->12.5  ��25����ֵ,Ȼ��2�����  12.5����ֵ
		{
			ViPByte tempData = new ViByte[length * 25];
			memset(tempData,0,length * 25 );
			LineInterpolation(pSrc, length, 25, tempData);
			SampleData(tempData, pDst, length*25 / 2, 2);
			delete []tempData;
			tempData = NULL;
		}
		else if ((multiples >0.09) && (multiples < 0.11))//0.1  1->10   10����ֵ
		{
			LineInterpolation(pSrc, length, 10, pDst);
		}
		else if ((multiples >0.124) && (multiples < 0.126))//0.125  1->8   8����ֵ 
		{
			LineInterpolation(pSrc, length, 8, pDst);
		}
		else if ((multiples >0.19) && (multiples < 0.21))//0.2  1->5     5����ֵ 
		{
			LineInterpolation(pSrc, length, 5, pDst);
		}
		else if ((multiples >0.249) && (multiples < 0.251))//0.25  1->4   ��20����ֵ��5�����      
		{
			LineInterpolation(pSrc, length, 4, pDst);
		}
		else if ((multiples > 0.399) && (multiples < 0.401))//0.4   1->2.5   ��10����ֵ��4�����    
		{
			ViPByte tempData = new ViByte[length * 10];
			memset(tempData,0,length * 10 );
			LineInterpolation(pSrc, length, 10, tempData);
			SampleData(tempData, pDst, length*10 / 4, 4);
			delete []tempData;
			tempData = NULL;
		}
		else if ((multiples >0.49) && (multiples < 0.51))//0.5  1->2  10����ֵ5�����
		{
			LineInterpolation(pSrc, length, 2, pDst);
		}
		else if ((multiples >0.9) && (multiples < 1.1))//1�����
		{
			SampleData(pSrc, pDst, (ViInt32)length , 1);
		}
		else if ((multiples > 1.24) && (multiples < 1.26))//1.25�����    8����ֵ,10����� 
		{
			ViPByte pData = new ViByte[length * 8];
			SinxKenerl8(pData, pSrc, length);
			LineInterpolation(pSrc, length, 8, pData);
			SampleData(pData, pDst, length * 8 / 10, 10);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples > 1.9) && (multiples < 2.1))// 2�����
		{
			SampleData(pSrc, pDst, length / 2, 2);
		}
		else if ((multiples > 2.4) && (multiples < 2.6))//2.5�����      8����ֵ,20�����
		{
			ViPByte pData = new ViByte[length * 8];
			LineInterpolation(pSrc, length, 8, pData);
			SampleData(pData, pDst, length * 8 / 20, 20);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples >4.9) && (multiples < 5.1))//5�����
		{
			SampleData(pSrc, pDst, length / 5, 5);
		}
		else if ((multiples >9.9) && (multiples < 10.1))//10�����
		{
			SampleData(pSrc, pDst, length / 10, 10);
		}
		else if ((multiples > 12.4) && (multiples < 12.6))//12.5�����    4����ֵ,50�����
		{
			ViPByte pData = new ViByte[length * 4];
			LineInterpolation(pSrc, length, 4, pData);
			SampleData(pData, pDst, length * 4 / 50, 50);
			delete []pData;
			pData = NULL;
		}
		else if ((multiples >19.9) && (multiples < 20.1))//20�����
		{
			SampleData(pSrc, pDst, length / 20, 20);
		}
		else if ((multiples >24.9) && (multiples < 25.1))//25�����
		{
			SampleData(pSrc, pDst, length / 25, 25);
		}
		else if ((multiples >39.9) && (multiples < 40.1))//40�����
		{
			SampleData(pSrc, pDst, length / 40, 40);
		}
		else if ((multiples >49.9) && (multiples < 50.1))//50�����
		{
			SampleData(pSrc, pDst, length / 50, 50);
		}
		else if ((multiples >79.9) && (multiples < 80.1))//80�����
		{
			SampleData(pSrc, pDst, (ViInt32)length / 80, 80);
		}
	}
}

//2016-9-6ʵ��us������ʱ����
ULONG GetTimeDis(SYSTEMTIME first, SYSTEMTIME second)    //  
{  
	return abs((first.wHour * 3600 * 1000 + first.wMinute * 60 * 1000 + first.wSecond * 1000 + first.wMilliseconds)  
		- (second.wHour * 3600 * 1000 + second.wMinute * 60 * 1000 + second.wSecond * 1000 + second.wMilliseconds));  
}  

void us_Delay(ULONG ulMicroSeconds)  
{  
	LARGE_INTEGER  timeStop;   
	LARGE_INTEGER  timeStart;   
	LARGE_INTEGER  Freq;   
	LONGLONG  ulTimeToWait;  

	if (!QueryPerformanceFrequency( &Freq ))  
		return;  

	QueryPerformanceCounter ( &timeStart );  

	ulTimeToWait = Freq.QuadPart * ulMicroSeconds / 1000 / 1000;   

	timeStop = timeStart;   

	while((timeStop.QuadPart - timeStart.QuadPart) < ulTimeToWait )   
	{   
		QueryPerformanceCounter( &timeStop );   
	}  
}

/*********************************************************************
 *
 * Function   : SelectDevice_DMA
 *
 * Description: Asks the user which PLX DMA device to select
 *
 * Returns    : Total devices found
 *              -1,  if user cancelled the selection
 *
 ********************************************************************/
S16 SelectDevice_DMA(PLX_DEVICE_KEY *pKey)
{
	S32               i;
	S32               NumDevices;
	BOOLEAN           bAddDevice;
	PLX_STATUS        status;
	PLX_DEVICE_KEY    DevKey;
	PLX_DEVICE_KEY    DevKey_DMA[MAX_DEVICES_TO_LIST];
	PLX_DRIVER_PROP   DriverProp;
	PLX_DEVICE_OBJECT Device;


	Cons_printf("\n");

	i          = 0;
	NumDevices = 0;

	do
	{
		// Setup for next device
		memset(&DevKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY));

		// Check if device exists
		status =
			PlxPci_DeviceFind(
			&DevKey,
			(U16)i
			);

		if (status == ApiSuccess)
		{
			// Default to add device
			bAddDevice = TRUE;

			if (bAddDevice)
			{
				// Verify supported chip type
				switch (DevKey.PlxChip)
				{
				case 0x9080:
				case 0x9054:
				case 0x9056:
				case 0x9656:
				case 0x8311:
					break;

				default:
					if ((DevKey.PlxChip & 0xF000) == 0x8000)
					{
						// DMA is always function 1 or higher
						if (DevKey.function == 0)
							bAddDevice = FALSE;
					}
					else
					{
						bAddDevice = FALSE;
					}
					break;
				}
			}

			if (bAddDevice)
			{
				// Open device to get its properties
				PlxPci_DeviceOpen(
					&DevKey,
					&Device
					);
			}

			// Verify driver used is PnP and not Service driver
			if (bAddDevice)
			{
				PlxPci_DriverProperties(
					&Device,
					&DriverProp
					);

				if (DriverProp.bIsServiceDriver)
				{
					bAddDevice = FALSE;
				}
			}

			// Close device
			PlxPci_DeviceClose(
				&Device
				);

			if (bAddDevice)
			{
				// Copy device key info
				DevKey_DMA[NumDevices] = DevKey;

				Cons_printf(
					"\t\t  %2d. %04x [b:%02x s:%02x f:%x]\n",
					(NumDevices + 1), DevKey.PlxChip,
					DevKey.bus, DevKey.slot, DevKey.function
					);

				// Increment device count
				NumDevices++;
			}
		}

		// Go to next devices
		i++;
	}
	while ((status == ApiSuccess) && (NumDevices < MAX_DEVICES_TO_LIST));

	if (NumDevices == 0)
		return 0;

	Cons_printf(
		"\t\t   0. Cancel\n\n"
		);

	//do
	//{
	//    Cons_printf("\t  Device Selection --> ");
	//    Cons_scanf("%d", &i);
	//}
	//while (i > NumDevices);
	i = 1;
	if (i == 0)
		return -1;

	// Return selected device information
	*pKey = DevKey_DMA[i - 1];

	return (S16)NumDevices;
}

void PerformDma_9000(PLX_DEVICE_OBJECT *pDevice)
{
    U8                DmaChannel;
    U8               *pUserBuffer = NULL;
    U16               ChannelInput;
    U32               LocalAddress;
    PLX_STATUS        rc;
    PLX_DMA_PROP      DmaProp;
    PLX_INTERRUPT     PlxInterrupt;
    PLX_DMA_PARAMS    DmaParams;
    PLX_PHYSICAL_MEM  PciBuffer;
    PLX_NOTIFY_OBJECT NotifyObject;
	struct timeb      StartTime, EndTime;
	U32               ElapsedTime_ms;
	double            Stat_TxTotalCount;
    double            Stat_TxTotalBytes;
	U32               LoopCount;


   /* Cons_printf(
        "Description:\n"
        "     This sample demonstrates usage of the PLX DMA API by\n"
        "     performing DMA transfers and waiting for DMA completion.\n"
        );

    Cons_printf(
        "\n"
        " WARNING: There is no safeguard mechanism to protect against invalid\n"
        "          local bus addresses.  Please be careful when selecting local\n"
        "          addresses to transfer data to/from.  The DMA engine will hang\n"
        "          if an invalid address is accessed.\n"
        "\n\n"
        );

    Cons_printf("Please enter a valid local address ----> ");
    Cons_scanf("%x", &LocalAddress);

    Cons_printf("Please select a DMA channel (0 or 1) --> ");
    Cons_scanf("%hd", &ChannelInput);
    Cons_printf("\n");
	*/

	LocalAddress = 0x40c;
	ChannelInput = 0;
    if ((ChannelInput != 0) && (ChannelInput != 1))
    {
        Cons_printf("ERROR: Unsupported DMA channel, test aborted\n");
        return;
    }

    DmaChannel = (U8)ChannelInput;

    // Get DMA buffer parameters
    PlxPci_CommonBufferProperties(
        pDevice,
        &PciBuffer
        );


    // Clear DMA structure
    memset(&DmaProp, 0, sizeof(PLX_DMA_PROP));

    // Initialize the DMA channel
    DmaProp.LocalBusWidth	= 3;   // 32-bit
    DmaProp.Burst		= 1;
	DmaProp.ConstAddrLocal	= 1;
	DmaProp.BurstInfinite = 1;
//	DmaProp.DemandMode= 1;


    Cons_printf("  Open Channel %i for DMA......... ", DmaChannel);
    rc =
        PlxPci_DmaChannelOpen(
            pDevice,
            DmaChannel,
            &DmaProp
            );

    if (rc == ApiSuccess)
    {
        Cons_printf("Ok\n");
    }
    else
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }


    Cons_printf("  Register for notification...... ");

    // Clear interrupt fields
    memset(&PlxInterrupt, 0, sizeof(PLX_INTERRUPT));

    // Setup to wait for selected DMA channel
    PlxInterrupt.DmaDone = (1 << DmaChannel);
//	int a=0;
    rc =
        PlxPci_NotificationRegisterFor(
            pDevice,
            &PlxInterrupt,
            &NotifyObject
            );

    if (rc != ApiSuccess)
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }
    else
    {
        Cons_printf("Ok\n");
    }


    // Transfer the Data
    Cons_printf("  Perform Block DMA transfer..... ");

    // Clear DMA data
    memset(&DmaParams, 0, sizeof(PLX_DMA_PARAMS));

    DmaParams.PciAddr   = PciBuffer.PhysicalAddr;
    DmaParams.LocalAddr = LocalAddress;
    DmaParams.ByteCount = 0x10;
    DmaParams.Direction = PLX_DMA_LOC_TO_PCI;

    rc =
        PlxPci_DmaTransferBlock(
            pDevice,
            DmaChannel,
            &DmaParams,
            0          // Don't wait for completion
            );

    if (rc == ApiSuccess)
    {
        Cons_printf("Ok\n");

        Cons_printf("  Wait for interrupt event....... ");

        rc =
            PlxPci_NotificationWait(
                pDevice,
                &NotifyObject,
                5 * 1000
                );

        switch (rc)
        {
            case ApiSuccess:
                Cons_printf("Ok (DMA Int received)\n");
                break;

            case ApiWaitTimeout:
                Cons_printf("*ERROR* - Timeout waiting for Int Event\n");
                break;

            case ApiWaitCanceled:
                Cons_printf("*ERROR* - Interrupt event cancelled\n");
                break;

            default:
                Cons_printf("*ERROR* - API failed\n");
                PlxSdkErrorDisplay(rc);
                break;
        }
    }
    else
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }


    Cons_printf("  Check notification status...... ");
    rc =
        PlxPci_NotificationStatus(
            pDevice,
            &NotifyObject,
            &PlxInterrupt
            );

    if (rc == ApiSuccess)
    {
        Cons_printf("Ok (triggered ints:");

        if (PlxInterrupt.DmaDone & (1 << 0))
            Cons_printf(" DMA_0");

        if (PlxInterrupt.DmaDone & (1 << 1))
            Cons_printf(" DMA_1");

        Cons_printf(")\n");
    }
    else
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }


    // Transfer a user-mode buffer using DMA
    Cons_printf("  Transfer a user-mode buffer.... ");

    // Allocate a buffer
   /* pUserBuffer = malloc(0x10);

    // Clear DMA data
    memset(&DmaParams, 0, sizeof(PLX_DMA_PARAMS));

    DmaParams.UserVa    = (PLX_UINT_PTR)pUserBuffer;
    DmaParams.LocalAddr = LocalAddress;
    DmaParams.ByteCount = 0x10;
    DmaParams.Direction = PLX_DMA_LOC_TO_PCI;

    rc =
        PlxPci_DmaTransferUserBuffer(
            pDevice,
            DmaChannel,
            &DmaParams,
            200         // Specify a timeout to let API perform wait
            );

    if (rc == ApiSuccess)
    {
        Cons_printf("Ok\n");
    }
    else
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }
	free(pUserBuffer);*/



	// Allocate a buffer
	pUserBuffer = (U8*)malloc(4 * 1024 * 1024);
	
	// Clear DMA data
	memset(&DmaParams, 0, sizeof(PLX_DMA_PARAMS));
	memset(pUserBuffer, 0, sizeof(pUserBuffer));
	
	DmaParams.UserVa    = (PLX_UINT_PTR)pUserBuffer;
	DmaParams.LocalAddr = LocalAddress;
	DmaParams.ByteCount = 2*4*32*1024;
	DmaParams.Direction = PLX_DMA_LOC_TO_PCI;

		
	rc = PlxPci_DmaTransferUserBuffer( pDevice,DmaChannel, &DmaParams,200);
		

 	FILE *file0=fopen("dataDMA.txt","w+"); 
	U32  *data=(U32*)pUserBuffer;
	U32  a = 0;
	char strbuffer[9];
 	for (int myj=0;myj<32*1024;myj++)
 	{
 		a=*(data+myj);
 		itoa(a,strbuffer,16);
		fprintf(file0,"%s\n",strbuffer);
 		//fprintf(file0,"%u\n",a);
	}
 	fclose(file0);

    // Release the interrupt wait object
    Cons_printf("  Cancelling Int Notification.... ");
    rc =
        PlxPci_NotificationCancel(
            pDevice,
            &NotifyObject
            );

    if (rc != ApiSuccess)
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }
    else
    {
        Cons_printf("Ok\n");
    }

    // Close DMA Channel
    Cons_printf("  Close DMA Channel.............. ");
    rc =
        PlxPci_DmaChannelClose(
            pDevice,
            DmaChannel
            );

    if (rc == ApiSuccess)
    {
        Cons_printf("Ok\n");
    }
    else
    {
        Cons_printf("*ERROR* - API failed\n");
        PlxSdkErrorDisplay(rc);
    }

    // Release user buffer
    if (pUserBuffer != NULL)
        free(pUserBuffer);
}
