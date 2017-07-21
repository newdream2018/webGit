#ifndef GLOBAL_H
#define GLOBAL_H
#include "IviVisaType.h"


struct DAQ_DEVICEPARAM
{
	struct 
	{
		ViReal64	StartTime;			//�Ӵ����¼������μ�¼�ĵ�һ���ʱ��ĳ��ȡ���λ���롣��������������μ�¼�ĵ�һ�����ڴ����¼������Ϊ�������μ�¼�ĵ�һ�����ڴ����¼�ǰ��
		ViInt32		Type;				//ʾ������βɼ����ݣ�����䲨�μ�¼��������Ϊ���ŷ⡱�򡰷�ֵ��⣬ʾ�����ɼ�����С������Ρ�
		ViInt32		NumberOfPointsMin;	//ÿ��ͨ���Ĳ��μ�¼�ĵ����С��Ŀ�����������ò��βɼ��ļ�¼���ȡ���¼�������Է��ؼ�¼��ʵ�ʳ��ȡ�
		ViInt32		RecordLength;		//ʾ����ÿͨ��ʵ�ʲɼ������������ڵ���ˮƽ��С��������ָ�������С��Ŀ��
		ViReal64	SampleRate;			//��Ч������(��λ������)��
		ViReal64	TimePerRecord;		//ʾ����ÿͨ��ʵ�ʲɼ�������Ӧ�Ĳ���ʱ��(��λ����)��
		ViInt32		Interpolation;		//ʾ�������ܲɼ����μ�¼�е�ÿ����ʱʹ�õĲ�ֵ�㷨��
		ViInt32		SampleMode;			//ʾ������ǰʹ�õĲ���ģʽ��
		ViInt32		NumberOfAverages;	//ʾ��������ƽ���Ĳ��μ�¼����
		ViInt32		NumberOfEnvelopes;	//ʾ�������ڴ���������С���μ�¼���ɼ��Ĳ��μ�¼����
		ViBoolean	Continuous;			//���βɼ�
		ViBoolean   ReadDataInIOMode;   // I/O����,TRUEΪ��,FALSEΪ�ٱ�ʾDMA����

		ViReal64	RequireSampleRate;	//ʾ������ǰ������������ʣ���NumberOfPointsMin/TimePerRecord����ó���
		ViUInt32	AdcSampleRate;		//ADC������
		ViReal64    HardwareSampleRate; //Ӳ��������
		ViChar		TimeBase[16];		//ʱ����λ
		ViInt32		TimeBaseIndex;		//ʱ����λ���
		ViReal64	TimeBaseValue;		//ʱ����λ��ֵ
		ViReal64	TimeGapOfPoint;		//���μ�¼��������ʱ������
		ViReal64	SoftwareMultiple;	//�����㱶��
		ViUInt32	HardwareMultiple;	//Ӳ����㱶��
		ViUInt32	PeakDetectTimes;	//��ֵ������
		ViBoolean	DividedBySixteen;	//Ӳ��16��Ƶ
		ViBoolean	DividedByEight;	    //Ӳ��8��Ƶ
		ViUInt32	FetchMode;			//0-��ͨ��ʽ,1-������ʽ(ɨ��)	
		ViInt32 InterPolationType;      //��ֵ����
	}Acquisition;
	struct
	{
		ViChar Name[16];
	}ActualChannel[2];//ʵ��ͨ����ÿ̨�豸������ʵ��ͨ��
	struct 
	{	
		ViBoolean  Enabled;				// ͨ��ʹ��	
		ViReal64   Range;				// ��ֱ������
		ViReal64   Offset;
		ViSession  DeviceHandle;
		const char* ActualName;         // ������ʵ��ͨ����ѡ��
		ViPByte DataBuffer;
	}Channel[4];// �ĸ���ʾͨ����Ϣ
	struct 
	{
		ViReal64 m_dMax_V;								//���ֵ
		ViReal64 m_dMin_V;								//��Сֵ
		ViReal64 m_dPeakToPeak_V;						//���ֵ
		ViReal64 m_dHigh_V;								//���ζ���ֵ(����ƽ����GND�ĵ�ѹֵ)
		ViReal64 m_dLow_V;								//���ε׶�ֵ(����ƽ����GND�ĵ�ѹֵ)
		ViReal64 m_dAmplitude_V;						//��ֵ
		ViReal64 m_dAverage_V;							//ƽ��ֵ
		ViReal64 m_dRMS_V;								//������ֵ
		ViReal64 m_dPeriod_mS;							//����
		ViReal64 m_dFrequency_KHz;						//Ƶ��
		ViReal64 m_dRiseTime_nS;						//����ʱ��
		ViReal64 m_dFallTime_nS;					    //�½�ʱ��
		ViReal64 m_dWidthPos_mS;						//������(��������50%����ʱ��������)
		ViReal64 m_dWidthNeg_mS;				    	//������(��������50%����ʱ��������)
		ViReal64 m_dDutyCyclePos;						//������ռ�ձ�(�����������ڵı�ֵ)
		ViReal64 m_dDutyCycleNeg;
	}Measurement[4];

	struct {
		UINT Offset;				//�˿�ƫ��
		UINT Port[512];				//�˿ں�
		UINT Word[512];				//������
	}Command;
	struct 
	{
		ViInt32		MemoryType;						//�洢�����:0-�ڲ�,1-�ⲿ
		ViInt32		MemorySize;						//�洢����С(�ֽ���)
		ViInt32		MemoryDepth;					//�洢���(��ַ��)
	}Base;
};


extern DAQ_DEVICEPARAM  *g_deviceParam;
ViBoolean Equals(ViReal64 Data1, ViReal64 Data2);
#endif