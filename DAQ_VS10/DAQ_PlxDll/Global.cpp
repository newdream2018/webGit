#include "stdafx.h"
#include "Global.h"

DAQ_DEVICEPARAM  *g_deviceParam = new DAQ_DEVICEPARAM();

inline ViInt32 GetExpoBase2(ViReal64 Data)
{
	ViInt32 i = 0;
	((short *)(&i))[0] = (((short *)(&Data))[3] & (short)32752); 
	return (i >> 4) - 1023;
}

ViBoolean Equals(ViReal64 Data1, ViReal64 Data2)
{
	if (Data1 == Data2)
		return VI_TRUE;
	ViInt32 e1 = GetExpoBase2(Data1);
	ViInt32 e2 = GetExpoBase2(Data2);
	ViInt32 e3 = GetExpoBase2(Data1 - Data2);
	if ((e3 - e2 < -48) && (e3 - e1 < -48))
		return VI_TRUE;
	return VI_FALSE;
}