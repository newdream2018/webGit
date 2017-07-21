#ifndef GLOBAL_H
#define GLOBAL_H
#include "Struct.h"
#include "stdafx.h"

extern bool g_isRun;
extern bool g_pauseEnable;
extern DEVICEPARAM  g_deviceParam;
extern HANDLE g_hEventRuning;   //运行的线程句柄
extern HANDLE g_hEventScaning;
extern HANDLE g_hEventDDRRuning;
extern CRITICAL_SECTION g_criticalSection;   //用于保护对硬件的操作
extern ViSession g_deviceHandle[100];
bool Equals(double Data1, double Data2);

#endif