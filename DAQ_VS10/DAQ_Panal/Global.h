#ifndef GLOBAL_H
#define GLOBAL_H
#include "Struct.h"
#include "stdafx.h"

extern bool g_isRun;
extern bool g_pauseEnable;
extern DEVICEPARAM  g_deviceParam;
extern HANDLE g_hEventRuning;   //���е��߳̾��
extern HANDLE g_hEventScaning;
extern HANDLE g_hEventDDRRuning;
extern CRITICAL_SECTION g_criticalSection;   //���ڱ�����Ӳ���Ĳ���
extern ViSession g_deviceHandle[100];
bool Equals(double Data1, double Data2);

#endif