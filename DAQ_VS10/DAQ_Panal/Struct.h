#ifndef _STRUCT_H
#define _STRUCT_H

#include "StdAfx.h"
#include "..\DAQ_PlxDll\DAQ_PlxDll.h"

struct DEVICEPARAM
{	
	struct
	{
		ViSession hDevice;            // �豸���
		DWORD	  BusNumber;          // ���ߺ�
		USHORT	  DeviceNumber;       // �豸��
		ViRsrc    ResourceName;       // ��Դ��
	}Device[100];// �����������ӵ��豸�ľ������Դ��

	struct 
	{
		double	TimeBase;		      // ʱ��ֵ
		double  SampleRate;           // ������
	}Acquisition;

	struct 
	{	
		ViSession DeviceHandle;         // ����ʾͨ����Ӧ���豸���
		int       DeviceNumber;
		const char* ActualName;         // ʵ��ͨ��
		bool	  Enabled;				// ͨ��ʹ��	
		double	  Range;				// ��ֱ������*10
		int       RangeIndex;           // ��ֱ���������
		double    Offset;               // ͨ��ƫ��
		int       Coupling;             // ͨ�����
		int       ProbeAttention;		
	}Channel[4];//��ʾͨ��

	struct 
	{
		
	}Trigger;

	struct 
	{
		double Max;						//���ֵ
		double Min;						//��Сֵ
		double PeakToPeak;				//���ֵ
		double Top;						//���ζ���ֵ(����ƽ����GND�ĵ�ѹֵ)
		double Base;					//���ε׶�ֵ(����ƽ����GND�ĵ�ѹֵ)
		double Amplitude;				//��ֵ
		double Average;					//ƽ��ֵ
		double Period;					//����
		double Frequency;				//Ƶ��
	}Measurement[4];

	struct
	{
		ViReal64 MinData[500];                //���ڴ����ʾ����Сֵ
		ViReal64 MaxData[500];                //���ڴ����ʾ����Сֵ

		ViByte ScanMinData[500];                //���ڴ����ʾ����Сֵ
		ViByte ScanMaxData[500];                //���ڴ����ʾ����Сֵ
	}DisplayData[4];// ��ʾͨ��

	struct
	{
		ViSession DeviceHandle[4];
		ViInt32   DeviceCount;
	}CheckedDevice;// ��ѡ���ͨ�������ѡ����̨
};
#endif