#include "StdAfx.h"
#include "Sinx.h"


void LineInterpolation(ViPByte pSrc, ViInt32 length, ViInt32 rate,ViPByte pDst)//整数倍线性插值
{
	ViInt32 delta = 0;
	for (int i = 0; i<length-1; i++)
	{
		delta = (pSrc[i+1] - pSrc[i])/rate;

		for (int j = 0; j<rate; j++)
		{	
			pDst[i*rate + j] = pSrc[i] + delta * j;
		}		
	}
}

//2倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl2(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_2DOTS; j++)				//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h2_blm[j][i];
			Sum*= 2;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//4倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl4(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_4DOTS; j++)				//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h4_blm[j][i];
			Sum*= 4;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//5倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl5(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_5DOTS; j++)				//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h5_blm[j][i];
			Sum*= 5;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
} 

//8倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl8(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_8DOTS; j++)				//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h8_blm[j][i];
			Sum*= 8;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
} 

//10倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl10(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_10DOTS; j++)			//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h10_blm[j][i];
			Sum*= 10;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
} 

//20倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl20(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_20DOTS; j++)			//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h20_blm[j][i];
			Sum*= 20;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//25倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl25(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_25DOTS; j++)			//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h25_blm[j][i];
			Sum*= 25;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//50倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl50(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_50DOTS; j++)			//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h50_blm[j][i];
			Sum*= 50;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//100倍插值函数的实现,OutBuffer为插值后的数组，InBuffer为插值前的数组，Len为插值前数组的长度
void SinxKenerl100(unsigned char *OutBuffer, const unsigned char *InBuffer, int Len)
{
	int i, j, k, Sum, Index;
	const unsigned char *InPointer;

	InPointer=InBuffer+7;
	Index=0;
	for(k=0; k<Len; k++)						//对Len个输入插值；
	{
		for(j=0; j<SINX_100DOTS; j++)			//计算分支滤波器的输出；
		{
			Sum=0;
			for(i=0; i<8; i++)					//计算各分支滤波器抽头的乘加；
				Sum+=InPointer[k-i]*h100_blm[j][i];
			Sum*= 100;
			Sum/=MAX_COEFFICIENT;
			if(Sum>255)
				Sum=255;
			else if(Sum<0)
				Sum=0;

			OutBuffer[Index++]=(unsigned char)Sum;		
		}
	}
}

//抽点
void SampleData(const ViPByte pSrc, ViPByte pDst, ViInt32 nSizeAfterSample, ViInt32 nRate)
{
	ViInt32 i;
	for (i = 0; i < nSizeAfterSample; i++)
	{
		pDst[i] = pSrc[i * nRate];
	}
}

//得到一个数组中的最大值和最小值 
void GetMaxMin(const ViPByte data,ViInt32 len,ViPByte max,ViPByte min)     
{
	int i = 0;
	*max = data[0];
	*min = data[0];
	for(i = 1;i<len;i++)
	{
		if(data[i] > *max)   *max = data[i];
		if(data[i] < *min)   *min = data[i];
	}
	return;
}

//抽点时要做峰值检测
void SamplePeak(const ViPByte pSorc,ViInt32 nRate,ViPByte pDestMin,ViPByte pDestMax,ViInt32 nSizeAfterSample)		   
{
	int i = 0;
	unsigned char max,min;
	for(i = 0;i < nSizeAfterSample;i++)
	{
		GetMaxMin(pSorc + (i * nRate),nRate,&max,&min);
		*(pDestMin + i) = min;
		*(pDestMax + i) = max;   
	}
}

//抽点时要做峰值检测
void SamplePeakInNormal(const ViPByte pSorc,ViInt32 nRate,ViPByte pDestMin,ViPByte pDestMax,ViInt32 nSizeAfterSample)		   
{
	double sum1 = 0.0;
	double sum2 = 0.0;
	double average1 = 0.0;
	double average2 = 0.0;
	int tempRate1 = nRate / 2;
	int tempRate2 = nRate - tempRate1;

	for (int i = 0; i < nSizeAfterSample; ++i)
	{
		if (nRate < 2)//不抽值不插点的时候
		{
			pDestMin[i] = pSorc[i];
			pDestMax[i] = pSorc[i];
		}
		else
		{
			sum1 = 0;
			sum2 = 0;
			for (int j=0;j < tempRate1;j++)
			{
				sum1 += pSorc[i*nRate + j];
			}
			average1 = sum1 / tempRate1;

			for (int j = 0;j < tempRate2;j++)
			{
				sum2 += pSorc[i*nRate + tempRate1 + j];
			}
			average2 = sum2 / tempRate2;

			if (average1 > average2)
			{
				pDestMin[i] = (ViByte)average2;
				pDestMax[i] = (ViByte)average1;
			}
			else
			{
				pDestMin[i] = (ViByte)average1;
				pDestMax[i] = (ViByte)average2;
			}
		}
	}
}