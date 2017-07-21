#include "StdAfx.h"
#include "DAQ_PlxDll.h"

PLX_DEVICE_KEY DeviceKey;

void CreateDeviceParam()
{
	g_deviceParam->Command.Offset = 0x0400;
	for (int i = 0; i < 512; i++)
	{
		g_deviceParam->Command.Port[i] = i * 4 + g_deviceParam->Command.Offset;
		g_deviceParam->Command.Word[i] = 0;
	}

	strcpy_s(g_deviceParam->ActualChannel[0].Name, DAQ_VAL_CH0);
	strcpy_s(g_deviceParam->ActualChannel[1].Name, DAQ_VAL_CH1);

	// 定义存数个数，读600次，每次读数可分为4个8位整型数，（参数定义可能不太合适，后期可改正）
	g_deviceParam->Base.MemoryDepth = 512;// 地址数
	g_deviceParam->Base.MemorySize = g_deviceParam->Base.MemoryDepth * 4;//存储数据数
	/*g_deviceParam->Channel[0].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
	memset(g_deviceParam->Channel[0].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
	g_deviceParam->Channel[1].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
	memset(g_deviceParam->Channel[1].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
	g_deviceParam->Channel[2].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
	memset(g_deviceParam->Channel[2].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
	g_deviceParam->Channel[3].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
	memset(g_deviceParam->Channel[3].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));*/
}

void DeleteDeviceParam()
{
	if (g_deviceParam != NULL)
	{
		delete g_deviceParam;
		g_deviceParam = NULL;
	}
}

/************************************************************************/
/* 解析资源名，根据资源名，判断需要打开的设备                           */
/************************************************************************/
void ParseResourceName(ViRsrc ResourceName, PLX_DEVICE_KEY  *pDeviceKey)
{
	pDeviceKey->IsValidTag=0x5f504c58;            // Magic number to determine validity
	pDeviceKey->domain=0x00;                      // Physical device location
	pDeviceKey->bus=0x03;
	pDeviceKey->slot=0x04;
	pDeviceKey->function=0x00;
	pDeviceKey->VendorId=0x10b5;                  // Device Identifier
	pDeviceKey->DeviceId=0x86e1;
	pDeviceKey->SubVendorId=0x10b5;
	pDeviceKey->SubDeviceId=0x8311;
	pDeviceKey->Revision=0xaa;
	pDeviceKey->PlxChip=0x8311;                   // PLX chip type
	pDeviceKey->PlxRevision=0xaa;                 // PLX chip revision
	pDeviceKey->PlxFamily=0x02;                   // PLX chip family
	pDeviceKey->ApiIndex=0x08;                    // Used internally by the API
	pDeviceKey->DeviceNumber=0x0000;              // Used internally by device drivers
	pDeviceKey->ApiMode=0x00;                     // Mode API uses to access device
	pDeviceKey->PlxPort=0x00;                     // PLX port number of device
	pDeviceKey->NTPortType=0x00;                  // If NT port, stores NT port type
	pDeviceKey->NTPortNum=0x00;                   // If NT port exists, store NT port number
	pDeviceKey->DeviceMode=0x00;                  // Device mode used internally by API
	pDeviceKey->ApiInternal[0]=0x00000000;              
	pDeviceKey->ApiInternal[1]=0x00000000;
}

// 配置该系统的四个显示通道对应的通道名称
ViStatus _VI_FUNC DAQ_SetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViConstString AttributeValue)
{
	if (Vi == NULL)
	{
		if (RepCapIdentifier == NULL)
		{
			switch (AttributeID)
			{
			case 0:
				break;
			default:
				break;
			}
		}
		else
		{
			if (_stricmp(RepCapIdentifier, DAQ_VAL_CH0) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_CHANNEL:
					g_deviceParam->Channel[0].ActualName = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH1) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_CHANNEL:
					g_deviceParam->Channel[1].ActualName = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH2) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_CHANNEL:
					g_deviceParam->Channel[2].ActualName = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH3) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_CHANNEL:
					g_deviceParam->Channel[3].ActualName = AttributeValue;
					break;
				default:
					break;
				}
			}
		}
	}
	
	return VI_SUCCESS;
}

// 配置该系统的四个显示通道对应的设备句柄
ViStatus _VI_FUNC DAQ_SetAttributeViSession(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViSession AttributeValue)
{
	if (Vi == NULL)
	{
		if (RepCapIdentifier == NULL)
		{
			switch (AttributeID)
			{
			case 0:
				break;
			default:
				break;
			}
		}
		else
		{
			if (_stricmp(RepCapIdentifier, DAQ_VAL_CH0) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_HANDLE:
					g_deviceParam->Channel[0].DeviceHandle = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH1) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_HANDLE:
					g_deviceParam->Channel[1].DeviceHandle = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH2) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_HANDLE:
					g_deviceParam->Channel[2].DeviceHandle = AttributeValue;
					break;
				default:
					break;
				}
			}
			else if (_stricmp(RepCapIdentifier, DAQ_VAL_CH3) == 0)
			{
				switch (AttributeID)
				{
				case DAQ_ATTR_DEVICE_HANDLE:
					g_deviceParam->Channel[3].DeviceHandle = AttributeValue;
					break;
				default:
					break;
				}
			}
		}
	}

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_SetAttributeViInt32(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValue)
{
	if (Vi == NULL)
	{
		if (RepCapIdentifier == NULL)
		{
			switch (AttributeID)
			{
			case DAQ_ATTR_MEMORY_SIZE://改变存储深度属性
				g_deviceParam->Base.MemorySize = AttributeValue;
				g_deviceParam->Base.MemoryDepth = g_deviceParam->Base.MemorySize/4;
				// CH1
				/*delete[] g_deviceParam->Channel[0].DataBuffer;
				g_deviceParam->Channel[0].DataBuffer = NULL;
				g_deviceParam->Channel[0].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
				memset(g_deviceParam->Channel[0].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));

				// CH2
				delete[] g_deviceParam->Channel[1].DataBuffer;
				g_deviceParam->Channel[1].DataBuffer = NULL;
				g_deviceParam->Channel[1].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
				memset(g_deviceParam->Channel[1].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
				
				// CH3
				delete[] g_deviceParam->Channel[2].DataBuffer;
				g_deviceParam->Channel[2].DataBuffer = NULL;
				g_deviceParam->Channel[2].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
				memset(g_deviceParam->Channel[2].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
	
				// CH4				
				delete[] g_deviceParam->Channel[3].DataBuffer;
				g_deviceParam->Channel[3].DataBuffer = NULL;
				g_deviceParam->Channel[3].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
				memset(g_deviceParam->Channel[3].DataBuffer,0,g_deviceParam->Base.MemorySize*sizeof(ViByte));
				*/
				if (g_deviceParam->Base.MemorySize > 2048)//选择ＤＭＡ读数
				{
					// DMA读数
					S16  DeviceSelected =
						SelectDevice_DMA(
						&DeviceKey
						);

					if (DeviceSelected == -1)
					{
						ConsoleEnd();
						exit(0);
					}
				}
				break;
			default:
				break;
			}
		}
	}

	return VI_SUCCESS;
}
ViStatus _VI_FUNC DAQ_init(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViSession *Vi)
{
	return DAQ_InitWithOptions(ResourceName, IdQuery, Reset, NULL, Vi);
}

ViStatus _VI_FUNC DAQ_InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession *Vi)
{	
	LOG(LOG_TYPE_INFO, "DAQ_InitWithOptions, ResourceName = %s", ResourceName);
	ConsoleInitialize();
	Cons_clear();

	CreateDeviceParam();
	// 解析ResourceName,选择打开的设备
	PLX_DEVICE_KEY *pDeviceKey = new PLX_DEVICE_KEY();
	ParseResourceName(ResourceName, pDeviceKey);
	DeviceKey = *pDeviceKey;
	// 打开设备
	PLX_DEVICE_OBJECT *pDevice = new PLX_DEVICE_OBJECT();
	PLX_STATUS Status = PlxPci_DeviceOpen(pDeviceKey, pDevice);
	if (Status != ApiSuccess)
	{
		LOG(LOG_TYPE_INFO, "DAQ_InitWithOptions, ResourceName = %s, 打开失败！", ResourceName);
		Cons_printf("\n   ERROR: Unable to find or select a PLX device\n");
		PlxSdkErrorDisplay(Status);

		// 释放分配的资源
		//DeleteObject(pDeviceKey);
		//pDeviceKey = NULL;
		//DeleteObject(pDevice);
		//pDevice = NULL;

		//return VI_FALSE;
	}
	Cons_clear();

	// 译码验证:
	// PORT5*4:读数0x55555555
	// PORT2*4:写数，PORT4*4读数
	// PORT9*4:写数，PORT3*4读数
	//U32 DATA = ReadDWord(pDevice, 20);
	//WriteDWord(pDevice, 8, 0xffff5555);
	//DATA = ReadDWord(pDevice, 16);
	//WriteDWord(pDevice, 36, 0x0000aaaa);
	//DATA = ReadDWord(pDevice, 12);
	
	// 保存仪器句柄
	*Vi = (ViSession)pDevice;
	LOG(LOG_TYPE_INFO, "DAQ_InitWithOptions, ResourceName = %s, Vi = %d", ResourceName, Vi);

	// 配置锁相环
	ConfigurePLL(*Vi);

	// 配置偏置
	ConfigureOffset(*Vi);

	// 0x5b4，触发？
	WriteDWord(pDevice, g_deviceParam->Command.Port[109], 0x00000080);

	// 释放分配的资源
	DeleteObject(pDeviceKey);
	pDeviceKey = NULL;
	DeleteObject(pDevice);
	pDevice = NULL;
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_close(ViSession Vi)
{
	LOG(LOG_TYPE_INFO, "DAQ_close, Vi = %d", Vi);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	PLX_NOTIFY_OBJECT *NotifyObject = NULL;
	PLX_STATUS Status = PlxPci_NotificationCancel(pDevice, NotifyObject);
	if (Status != ApiSuccess)
	{
		Cons_printf("*ERROR* - API failed\n");
		PlxSdkErrorDisplay(Status);
	}

	// Close DMA Channel
	Status = PlxPci_DmaChannelClose(pDevice, (U8)0);
	if (Status != ApiSuccess)
	{
		Cons_printf("*ERROR* - API failed\n");
		PlxSdkErrorDisplay(Status);
	}

	// Release user buffer
	//if (pUserBuffer != NULL)
	//	free(pUserBuffer);

	// 关闭仪器
	PlxPci_DeviceClose(pDevice);

	// 释放动态删除的内存
	/*delete[] g_deviceParam->Channel[0].DataBuffer;
	g_deviceParam->Channel[0].DataBuffer = NULL;
	delete[] g_deviceParam->Channel[1].DataBuffer;
	g_deviceParam->Channel[1].DataBuffer = NULL;
	delete[] g_deviceParam->Channel[2].DataBuffer;
	g_deviceParam->Channel[2].DataBuffer = NULL;
	delete[] g_deviceParam->Channel[3].DataBuffer;
	g_deviceParam->Channel[3].DataBuffer = NULL;*/
	DeleteDeviceParam();
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ConfigureAcquisitionType(ViSession Vi, ViInt32 AcquisitionType)
{
	LOG(LOG_TYPE_INFO, "DAQ_ConfigureAcquisitionType, Vi = %d, AcquisitionType = %d", Vi, AcquisitionType);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}


	return VI_SUCCESS;
}
/************************************************************************************
 该档位所需要的采样率：RequireSampleRate = MinNumPts / TimePerRecord 
 Freq(ADC)/分频数/硬件抽点比例 = Freq(档位需要的时钟频率) * 软件抽点比例
************************************************************************************/
ViStatus _VI_FUNC DAQ_ConfigureAcquisitionRecord(ViSession Vi, ViReal64 TimePerRecord, ViInt32 MinNumPts, ViReal64 AcquisitionStartTime)
{
	LOG(LOG_TYPE_INFO, "DAQ_ConfigureAcquisitionRecord, Vi = %d, TimePerRecord = %.3f, MinNumPts = %d, AcquisitionStartTime = %.3f", Vi, TimePerRecord, MinNumPts, AcquisitionStartTime);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	// 遍历四个显示通道，该设备有几个通道工作，若一个通道几个通道工作工作，是CH1还是CH2
	bool ch1Enabled = false;
	bool ch2Enabled = false;
	int index = 0;

	// 首先找到该设备
	for (int i = 0; i<4; i++)
	{
		if (g_deviceParam->Channel[i].DeviceHandle == Vi)
		{
			index = i;
		}
	}
	// 判断该设备有几个通道工作
	for (int i = 0; i<4; i++)
	{
		if (g_deviceParam->Channel[i].DeviceHandle == g_deviceParam->Channel[index].DeviceHandle)
		{
			if (_stricmp(g_deviceParam->Channel[i].ActualName, g_deviceParam->ActualChannel[0].Name) == 0)
			{
				ch1Enabled = g_deviceParam->Channel[i].Enabled;
			}
			if (_stricmp(g_deviceParam->Channel[i].ActualName, g_deviceParam->ActualChannel[1].Name) == 0)
			{
				ch2Enabled = g_deviceParam->Channel[i].Enabled;
			}
		}
	}

	// 根据该设备ch1Enabled以及ch2Enabled，来判断adc及硬件采样率、软件采样率、抽点/插值倍数等
	// 计算采样率，Freq(ADC)/分频数/硬件抽点比例 = Freq(档位需要的时钟频率) * 软件抽点比例
	ViReal64 RequireSampleRate = MinNumPts / TimePerRecord;
	if (Equals(RequireSampleRate, 5000000000.0))// 10ns/div，要求：5G
	{		
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 5000000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 1;
		g_deviceParam->Acquisition.SoftwareMultiple = 1;
	}
	else if (Equals(RequireSampleRate, 2500000000.0))// 20ns/div，要求：2.5G
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 2500000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 1;
		g_deviceParam->Acquisition.SoftwareMultiple = 1;
	}
	else if (Equals(RequireSampleRate, 1000000000.0))// 50ns/div，要求：1G
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 1;
		g_deviceParam->Acquisition.SoftwareMultiple = 1.25;
	}
	else if (Equals(RequireSampleRate, 500000000.0))// 100ns/div，要求：500M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 1;
		g_deviceParam->Acquisition.SoftwareMultiple = 2.5;
	}
	else if (Equals(RequireSampleRate, 250000000.0))// 200ns/div，要求：250M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 1;
		g_deviceParam->Acquisition.SoftwareMultiple = 5;
	}
	else if (Equals(RequireSampleRate, 100000000.0))// 500ns/div，要求：100M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 5;
		g_deviceParam->Acquisition.SoftwareMultiple = 2.5;
	}
	else if (Equals(RequireSampleRate, 50000000.0))// 1us/div，要求：50M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 5;
		g_deviceParam->Acquisition.SoftwareMultiple = 5;
	}
	else if (Equals(RequireSampleRate, 25000000.0))// 2us/div，要求：25M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 5;
		g_deviceParam->Acquisition.SoftwareMultiple = 10;
	}
	else if (Equals(RequireSampleRate, 10000000.0))// 5us/div，要求：10M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;		
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 50;
		g_deviceParam->Acquisition.SoftwareMultiple = 2.5;
	}
	else if (Equals(RequireSampleRate, 5000000.0))// 10us/div，要求：5M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;		
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 50;
		g_deviceParam->Acquisition.SoftwareMultiple = 5;
	}
	else if (Equals(RequireSampleRate, 2500000.0))// 20us/div，要求：2.5M
	{
		g_deviceParam->Acquisition.RequireSampleRate = RequireSampleRate;		
		g_deviceParam->Acquisition.AdcSampleRate = 1250000000;		
		g_deviceParam->Acquisition.HardwareMultiple = 50;
		g_deviceParam->Acquisition.SoftwareMultiple = 10;
	}
	
	// 配置锁相环
	ConfigurePLL(Vi);

	// 配置ADC
//	SetADCbySampleRate(Vi);

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ConfigureChannel(ViSession Vi, ViConstString Channel, ViReal64 Range, ViReal64 Offset, ViInt32 Coupling,	ViReal64 ProbeAttenuation, ViBoolean Enabled)
{
	LOG(LOG_TYPE_INFO, "DAQ_ConfigureChannel, Vi = %d, Channel = %s, Range = %.3f, Enabled = %d", Vi, Channel, Range, Enabled);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;
	if (
		!Equals(Range, 0.05) && // 5mv/div
		!Equals(Range, 0.1) &&	// 10mv/div
		!Equals(Range, 0.2) &&	// 20mv/div
		!Equals(Range, 0.5) &&	// 50mv/div
		!Equals(Range, 1.0) &&	// 100mv/div
		!Equals(Range, 2.0) &&	// 200mv/div
		!Equals(Range, 5.0) &&	// 500mv/div
		!Equals(Range, 10.0) && // 1v/div
		!Equals(Range, 20.0) && // 2v/div
		!Equals(Range, 50.0))   // 5v/div
	{
		return IVI_ERROR_VALUE_NOT_SUPPORTED;
	}

	for (int i = 0; i<4; i++)
	{
		if ((g_deviceParam->Channel[i].DeviceHandle == Vi) && (_stricmp(Channel, g_deviceParam->Channel[i].ActualName) == 0))
		{
			// 配置通道Range
			if (!Equals(Range, g_deviceParam->Channel[i].Range))
			{
				g_deviceParam->Channel[i].Range = Range;
				// 设置硬件参数
				SetChannelRange(Vi, Channel, Range);
			}

			// 配置偏移
			if (!Equals(Offset, g_deviceParam->Channel[i].Offset))
			{
				g_deviceParam->Channel[i].Offset = Offset;
				// 设置硬件参数
				SetChannelOffset(Vi, Channel, Offset);
			}

			// 配置通道Enabled
			if (!Equals(Enabled, g_deviceParam->Channel[i].Enabled))
			{
				g_deviceParam->Channel[i].Enabled = Enabled;
			}
		}
	}

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ConfigureTrigger(ViSession Vi, ViInt32 TriggerType, ViReal64 Holdoff)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ConfigureEdgeTriggerSource(ViSession Vi, ViConstString Source, ViReal64 Level, ViInt32 Slope)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ConfigureTriggerModifier(ViSession Vi, ViInt32 TriggerModifier)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_SampleRate(ViSession Vi,	ViReal64 *SampleRate)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	return VI_SUCCESS;
}

// 初始化采集
ViStatus _VI_FUNC DAQ_InitiateAcquisition(ViSession Vi)
{
	LOG(LOG_TYPE_INFO, "DAQ_InitiateAcquisition, Vi = %d", Vi);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	if (g_deviceParam->Base.MemorySize == 2048)// 普通存储
	{
		// 开始采集使能0x5AC 端口写0x0000 0001
		// 端口107，Port[107] = 107*4 + 0x400 = 0x5AC
		WriteDWord(pDevice, g_deviceParam->Command.Port[107], 0x00000001);
		Sleep(5);
		WriteDWord(pDevice, g_deviceParam->Command.Port[107], 0x00000001);
		Sleep(5);
		WriteDWord(pDevice, g_deviceParam->Command.Port[107], 0x00000001);
		Sleep(5);
	}
	else// DDR存储
	{
		// 0x5B8  写 0x0000 0001
		WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000001);
		Sleep(5);
		WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000001);
		Sleep(5);
		WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000001);
		Sleep(5);
	}
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_AcquisitionStatus(ViSession Vi, ViInt32 *Status)
{
	LOG(LOG_TYPE_INFO, "DAQ_AcquisitionStatus, Vi = %d", Vi);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	if (g_deviceParam->Base.MemorySize == 2048)// 普通存储
	{
		// 查询采集状态
		// 端口98，Port[98] = 98*4 +0x400 = 0x588
		int data = ReadDWord(pDevice, g_deviceParam->Command.Port[98]);

		if (data == 0x00000001) // 可以开始下一次采集
		{
			*Status = DAQ_VAL_ACQ_CAN_INIT_ACQ;
			return *Status;
		}

		if (data == 0x00000020) // 完成数据采集
		{
			WriteDWord(pDevice, g_deviceParam->Command.Port[107], 0x00000000);
			*Status = DAQ_VAL_ACQ_COMPLETE;
			return *Status;
		}
	}
	else// DDR存储
	{
		// 查询采集状态
		// 端口86，Port[86] = 86*4 +0x400 = 0x558
		int data = ReadDWord(pDevice, g_deviceParam->Command.Port[86]);

		if ((data&0x0000000F) == 0x00000004) // 正在写
		{
			//0x528 写 0x0000 0001  ,0x0000 0000,相当于触发信号
			WriteDWord(pDevice, g_deviceParam->Command.Port[74], 0x00000001);
			WriteDWord(pDevice, g_deviceParam->Command.Port[74], 0x00000000);
			
			*Status = DAQ_VAL_ACQ_DDR_IN_PROGRESS;
			return *Status;
		}

		if ((data&0x0000000F) == 0x00000002) //完成
		{
			// 0x5B8 写 0x0000 0000 //关闭写使能
			// 0x5Bc 写 0x0000 0002 //开启读使能
			WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000000);
			WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000002);

			*Status = DAQ_VAL_ACQ_DDR_COMPLETE;
			return *Status;
		}

		if ((data&0x0000000F) == 0x00000008)// 可读数
		{
			// 0x5B8写0x0000 0000
			WriteDWord(pDevice, g_deviceParam->Command.Port[110], 0x00000000);

			*Status = DAQ_VAL_ACQ_DDR_CAN_READ;
			return *Status;
		}
	}
	
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_ResetAcquisition(ViSession Vi)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;
	// 复位（每次采集都要复位，后期要改善）
	if (g_deviceParam->Base.MemorySize == 2048)// 普通存储
	{
		// 0x4dc
		WriteDWord(pDevice, g_deviceParam->Command.Port[55], 0x00000001);
		Sleep(1);
		WriteDWord(pDevice, g_deviceParam->Command.Port[55], 0x00000000);
		Sleep(1);
	}
	else// DDR存储
	{
		//  0x480   0x4bc 写 0x0000 00001
		WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000001);
		Sleep(1);
		WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000001);
		Sleep(1);
		//  0x480   0x4bc 写 0x0000 00001
		WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000001);
		Sleep(1);
		WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000001);
		Sleep(1);
		//  0x480   0x4bc 写 0x0000 00001
		WriteDWord(pDevice, g_deviceParam->Command.Port[32], 0x00000001);
		Sleep(1);
		WriteDWord(pDevice, g_deviceParam->Command.Port[47], 0x00000001);
		Sleep(1);
	}
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_FetchWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize,	ViReal64 WaveformArray[], ViInt32 *ActualPoints, ViReal64 *InitialX, ViReal64 *XIncrement)
{
	LOG(LOG_TYPE_INFO, "DAQ_FetchWaveform, Vi = %d, Channel = %s", Vi, Channel);
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}

	int index = 0;
	for (int i = 0; i<4; i++)
	{
		if ((g_deviceParam->Channel[i].DeviceHandle == Vi) && (_stricmp(Channel, g_deviceParam->Channel[i].ActualName) == 0))
		{
			index = i;
		}
	}
	g_deviceParam->Channel[index].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];
	// 读取数据
	FetchWaveData(Vi, Channel, g_deviceParam->Channel[index].DataBuffer);

	ViPByte tempBuffer = new ViByte[WaveformSize];
	// 从中间取500个数
	for (int i = 0; i<WaveformSize; i++)
	{
		tempBuffer[i] = g_deviceParam->Channel[index].DataBuffer[g_deviceParam->Base.MemorySize/2 - WaveformSize/2 + i];
	}
	// 存储原始数据
	char d[4] = {0};
	FILE *pFile = fopen("data.txt", "w+");

	for (int m = 0; m < g_deviceParam->Base.MemorySize; m++)
	{		
		itoa(g_deviceParam->Channel[index].DataBuffer[m], d, 10);
		fwrite(d, 1, strlen(d), pFile);
		fwrite("\n", 1, 2, pFile);				
	}
	fclose(pFile);

	// 模拟数据显示
	//FILE *file = NULL;
	//if (_stricmp(Channel, DAQ_VAL_CH0) == 0)
	//{
	//	file = fopen("1.txt","r");
	//}
	//else if (_stricmp(Channel, DAQ_VAL_CH1) == 0)
	//{
	//	file = fopen("2.txt","r");
	//}
	//if (file != NULL)
	//{
	//	for (int i=0;i<500;i++)
	//	{
	//		fscanf(file,"%d",&tempBuffer[i]);
	//	}
	//	fclose(file);
	//}

	// 参数测量

	// 返回采集点数（根据垂直灵敏度及偏移换算成电压值）
	for (int i = 0; i<WaveformSize;i++)
	{
		WaveformArray[i] = (ViReal64)((tempBuffer[i] - 127.5)*g_deviceParam->Channel[index].Range/255); 
	}

	delete tempBuffer;
	tempBuffer = NULL;
	delete g_deviceParam->Channel[index].DataBuffer;
	g_deviceParam->Channel[index].DataBuffer = NULL;
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_FetchMinMaxWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize, ViReal64 MinWaveform[], ViReal64 MaxWaveform[], ViInt32 *ActualPoints, ViReal64 *InitialX, ViReal64 *XIncrement)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_FetchWholeWaveform(ViSession Vi, ViConstString Channel, ViInt32 WaveformSize, ViByte WaveformArray[])
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}
	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;

	// 模拟数据
	//FILE *file = NULL;
	//if (_stricmp(Channel, DAQ_VAL_CH0) == 0)
	//{
	//	file = fopen("1.txt","r");
	//}
	//else if (_stricmp(Channel, DAQ_VAL_CH1) == 0)
	//{
	//	file = fopen("2.txt","r");
	//}
	//if (file != NULL)
	//{
	//	for (int i=0;i<16384;i++)
	//	{
	//		fscanf(file,"%d",&WaveformArray[i]);
	//	}
	//	fclose(file);
	//}

	int index = 0;
	for (int i = 0; i<4; i++)
	{
		if ((g_deviceParam->Channel[i].DeviceHandle == Vi) && (_stricmp(Channel, g_deviceParam->Channel[i].ActualName) == 0))
		{
			index = i;
		}
	}
	g_deviceParam->Channel[index].DataBuffer = new ViByte[g_deviceParam->Base.MemorySize];	
	if (g_deviceParam->Base.MemorySize == 2048)//普通存储
	{
		FetchWaveData(Vi, Channel, g_deviceParam->Channel[index].DataBuffer);
	}
	else// DDR存储
	{
		FetchWaveDataDDR(Vi, Channel, g_deviceParam->Channel[index].DataBuffer);
	}
	// 存储原始数据
	char d[4] = {0};
	FILE *pFile = fopen("dataDDR.txt", "w+");

	for (int m = 0; m < g_deviceParam->Base.MemorySize; m++)
	{		
		itoa(g_deviceParam->Channel[index].DataBuffer[m], d, 10);
		fwrite(d, 1, strlen(d), pFile);
		fwrite("\n", 1, 2, pFile);				
	}
	fclose(pFile);

	memcpy(WaveformArray, g_deviceParam->Channel[index].DataBuffer, WaveformSize);

	delete g_deviceParam->Channel[index].DataBuffer;
	g_deviceParam->Channel[index].DataBuffer = NULL;

	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_FetchWaveformMeasurement(ViSession Vi, ViConstString Channel, ViInt32 MeasFunction, ViReal64 *Measurement)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}

	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;
	int index = 0;
	for (int i = 0; i<4; i++)
	{
		if ((g_deviceParam->Channel[i].DeviceHandle == Vi) && (_stricmp(Channel, g_deviceParam->Channel[i].ActualName) == 0))
		{
			index = i;
			break;
		}
	}

	if (!g_deviceParam->Channel[index].Enabled)
	{
		return DAQ_ERROR_CHANNEL_NOT_ENABLED;
	}

	switch (MeasFunction)
	{
	case DAQ_VAL_RISE_TIME:
		*Measurement = g_deviceParam->Measurement[index].m_dRiseTime_nS;
		break;
	case DAQ_VAL_FALL_TIME:
		*Measurement = g_deviceParam->Measurement[index].m_dFallTime_nS;
		break;
	case DAQ_VAL_FREQUENCY:
		*Measurement = g_deviceParam->Measurement[index].m_dFrequency_KHz;
		break;
	case DAQ_VAL_PERIOD:
		*Measurement = g_deviceParam->Measurement[index].m_dPeriod_mS;
		break;
	case DAQ_VAL_VOLTAGE_RMS:
		*Measurement = g_deviceParam->Measurement[index].m_dRMS_V;
		break;
	case DAQ_VAL_VOLTAGE_PEAK_TO_PEAK:
		*Measurement = g_deviceParam->Measurement[index].m_dPeakToPeak_V;
		break;
	case DAQ_VAL_VOLTAGE_MAX:
		*Measurement = g_deviceParam->Measurement[index].m_dMax_V;
		break;
	case DAQ_VAL_VOLTAGE_MIN:
		*Measurement = g_deviceParam->Measurement[index].m_dMin_V;
		break;
	case DAQ_VAL_VOLTAGE_HIGH:
		*Measurement = g_deviceParam->Measurement[index].m_dHigh_V;
		break;
	case DAQ_VAL_VOLTAGE_LOW:
		*Measurement = g_deviceParam->Measurement[index].m_dLow_V;
		break;
	case DAQ_VAL_VOLTAGE_AVERAGE:
		*Measurement = g_deviceParam->Measurement[index].m_dAverage_V;
		break;
	case DAQ_VAL_WIDTH_NEG:
		*Measurement = g_deviceParam->Measurement[index].m_dWidthNeg_mS;
		break;
	case DAQ_VAL_WIDTH_POS:
		*Measurement = g_deviceParam->Measurement[index].m_dWidthPos_mS;
		break;
	case DAQ_VAL_DUTY_CYCLE_NEG:
		*Measurement = g_deviceParam->Measurement[index].m_dDutyCycleNeg;
		break;
	case DAQ_VAL_DUTY_CYCLE_POS:
		*Measurement = g_deviceParam->Measurement[index].m_dDutyCyclePos;
		break;
	case DAQ_VAL_AMPLITUDE:
		*Measurement = g_deviceParam->Measurement[index].m_dAmplitude_V;
		break;
	default:
		*Measurement = 0;
		break;
	}
	return VI_SUCCESS;
}

ViStatus _VI_FUNC DAQ_Abort(ViSession Vi)
{
	if (Vi == NULL)
	{
		return IVI_ERROR_NOT_INITIALIZED;
	}

	PLX_DEVICE_OBJECT *pDevice = (PLX_DEVICE_OBJECT*)Vi;


	return VI_SUCCESS;
}