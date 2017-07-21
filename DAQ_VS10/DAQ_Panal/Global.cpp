#include "stdafx.h"
#include "Global.h"

bool g_isRun = true;
bool g_pauseEnable = true;
DEVICEPARAM  g_deviceParam;
HANDLE g_hEventRuning;
HANDLE g_hEventScaning;
HANDLE g_hEventDDRRuning;
CRITICAL_SECTION g_criticalSection;   //用于保护对硬件的操作
ViSession g_deviceHandle[100];

inline INT32 GetExpoBase2(double Data)
{
	INT32 i = 0;
	((short *)(&i))[0] = (((short *)(&Data))[3] & (short)32752); 
	return (i >> 4) - 1023;
}

bool Equals(double Data1, double Data2)
{
	if (Data1 == Data2)
		return TRUE;
	INT32 e1 = GetExpoBase2(Data1);
	INT32 e2 = GetExpoBase2(Data2);
	INT32 e3 = GetExpoBase2(Data1 - Data2);
	if ((e3 - e2 < -48) && (e3 - e1 < -48))
		return TRUE;
	return FALSE;
}