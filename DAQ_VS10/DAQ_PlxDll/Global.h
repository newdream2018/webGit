#ifndef GLOBAL_H
#define GLOBAL_H
#include "IviVisaType.h"


struct DAQ_DEVICEPARAM
{
	struct 
	{
		ViReal64	StartTime;			//从触发事件到波形记录的第一点的时间的长度。单位是秒。如果是正数，波形记录的第一个点在触发事件后。如果为负，波形记录的第一个点在触发事件前。
		ViInt32		Type;				//示波器如何采集数据，并填充波形记录。当设置为“信封”或“峰值检测，示波器采集的最小和最大波形。
		ViInt32		NumberOfPointsMin;	//每个通道的波形记录的点的最小数目。它用于配置波形采集的记录长度。记录长度属性返回记录的实际长度。
		ViInt32		RecordLength;		//示波器每通道实际采集点数。它大于等于水平最小点数属性指定点的最小数目。
		ViReal64	SampleRate;			//有效采样率(单位：赫兹)。
		ViReal64	TimePerRecord;		//示波器每通道实际采集点数对应的采样时间(单位：秒)。
		ViInt32		Interpolation;		//示波器不能采集波形记录中的每个点时使用的插值算法。
		ViInt32		SampleMode;			//示波器当前使用的采样模式。
		ViInt32		NumberOfAverages;	//示波器用于平均的波形记录数。
		ViInt32		NumberOfEnvelopes;	//示波器用于创建最大和最小波形记录所采集的波形记录数。
		ViBoolean	Continuous;			//单次采集
		ViBoolean   ReadDataInIOMode;   // I/O读数,TRUE为真,FALSE为假表示DMA读数

		ViReal64	RequireSampleRate;	//示波器当前设置所需采样率，由NumberOfPointsMin/TimePerRecord计算得出。
		ViUInt32	AdcSampleRate;		//ADC采样率
		ViReal64    HardwareSampleRate; //硬件采样率
		ViChar		TimeBase[16];		//时基档位
		ViInt32		TimeBaseIndex;		//时基档位序号
		ViReal64	TimeBaseValue;		//时基档位数值
		ViReal64	TimeGapOfPoint;		//波形记录中两点间的时间间隔。
		ViReal64	SoftwareMultiple;	//软件抽点倍数
		ViUInt32	HardwareMultiple;	//硬件抽点倍数
		ViUInt32	PeakDetectTimes;	//峰值检测次数
		ViBoolean	DividedBySixteen;	//硬件16分频
		ViBoolean	DividedByEight;	    //硬件8分频
		ViUInt32	FetchMode;			//0-普通方式,1-滚动方式(扫描)	
		ViInt32 InterPolationType;      //插值方法
	}Acquisition;
	struct
	{
		ViChar Name[16];
	}ActualChannel[2];//实体通道，每台设备有两个实体通道
	struct 
	{	
		ViBoolean  Enabled;				// 通道使能	
		ViReal64   Range;				// 垂直灵敏度
		ViReal64   Offset;
		ViSession  DeviceHandle;
		const char* ActualName;         // 在两个实体通道中选择
		ViPByte DataBuffer;
	}Channel[4];// 四个显示通道信息
	struct 
	{
		ViReal64 m_dMax_V;								//最大值
		ViReal64 m_dMin_V;								//最小值
		ViReal64 m_dPeakToPeak_V;						//峰峰值
		ViReal64 m_dHigh_V;								//波形顶端值(波形平顶至GND的电压值)
		ViReal64 m_dLow_V;								//波形底端值(波形平底至GND的电压值)
		ViReal64 m_dAmplitude_V;						//幅值
		ViReal64 m_dAverage_V;							//平均值
		ViReal64 m_dRMS_V;								//均方根值
		ViReal64 m_dPeriod_mS;							//周期
		ViReal64 m_dFrequency_KHz;						//频率
		ViReal64 m_dRiseTime_nS;						//上升时间
		ViReal64 m_dFallTime_nS;					    //下降时间
		ViReal64 m_dWidthPos_mS;						//正脉宽(正脉冲在50%幅度时的脉冲宽度)
		ViReal64 m_dWidthNeg_mS;				    	//负脉宽(负脉冲在50%幅度时的脉冲宽度)
		ViReal64 m_dDutyCyclePos;						//正脉宽占空比(正脉宽与周期的比值)
		ViReal64 m_dDutyCycleNeg;
	}Measurement[4];

	struct {
		UINT Offset;				//端口偏移
		UINT Port[512];				//端口号
		UINT Word[512];				//控制码
	}Command;
	struct 
	{
		ViInt32		MemoryType;						//存储器类别:0-内部,1-外部
		ViInt32		MemorySize;						//存储器大小(字节数)
		ViInt32		MemoryDepth;					//存储深度(地址数)
	}Base;
};


extern DAQ_DEVICEPARAM  *g_deviceParam;
ViBoolean Equals(ViReal64 Data1, ViReal64 Data2);
#endif