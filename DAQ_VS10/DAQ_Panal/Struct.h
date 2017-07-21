#ifndef _STRUCT_H
#define _STRUCT_H

#include "StdAfx.h"
#include "..\DAQ_PlxDll\DAQ_PlxDll.h"

struct DEVICEPARAM
{	
	struct
	{
		ViSession hDevice;            // 设备句柄
		DWORD	  BusNumber;          // 总线号
		USHORT	  DeviceNumber;       // 设备号
		ViRsrc    ResourceName;       // 资源名
	}Device[100];// 保存所有连接的设备的句柄及资源名

	struct 
	{
		double	TimeBase;		      // 时基值
		double  SampleRate;           // 采样率
	}Acquisition;

	struct 
	{	
		ViSession DeviceHandle;         // 该显示通道对应的设备句柄
		int       DeviceNumber;
		const char* ActualName;         // 实际通道
		bool	  Enabled;				// 通道使能	
		double	  Range;				// 垂直灵敏度*10
		int       RangeIndex;           // 垂直灵敏度序号
		double    Offset;               // 通道偏移
		int       Coupling;             // 通道耦合
		int       ProbeAttention;		
	}Channel[4];//显示通道

	struct 
	{
		
	}Trigger;

	struct 
	{
		double Max;						//最大值
		double Min;						//最小值
		double PeakToPeak;				//峰峰值
		double Top;						//波形顶端值(波形平顶至GND的电压值)
		double Base;					//波形底端值(波形平底至GND的电压值)
		double Amplitude;				//幅值
		double Average;					//平均值
		double Period;					//周期
		double Frequency;				//频率
	}Measurement[4];

	struct
	{
		ViReal64 MinData[500];                //用于存放显示的最小值
		ViReal64 MaxData[500];                //用于存放显示的最小值

		ViByte ScanMinData[500];                //用于存放显示的最小值
		ViByte ScanMaxData[500];                //用于存放显示的最小值
	}DisplayData[4];// 显示通道

	struct
	{
		ViSession DeviceHandle[4];
		ViInt32   DeviceCount;
	}CheckedDevice;// 被选择的通道，最多选择四台
};
#endif