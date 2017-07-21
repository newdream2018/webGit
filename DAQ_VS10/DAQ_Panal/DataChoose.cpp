// DataChoose.cpp : implementation file
//

#include "stdafx.h"
#include "DAQ_Panal.h"
#include "DataChoose.h"
#include "afxdialogex.h"
#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

// CDataChoose dialog

IMPLEMENT_DYNAMIC(CDataChoose, CDialog)

CDataChoose::CDataChoose(CWnd* pParent /*=NULL*/)
	: CDialog(CDataChoose::IDD, pParent)
{
	m_actualChannel = 0;
}

CDataChoose::~CDataChoose()
{
}

void CDataChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_listDevice);
}


BEGIN_MESSAGE_MAP(CDataChoose, CDialog)
	ON_BN_CLICKED(IDOK, &CDataChoose::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_CH1, &CDataChoose::OnBnClickedRadioChooseCh1)
	ON_BN_CLICKED(IDC_RADIO_CHOOSE_CH2, &CDataChoose::OnBnClickedRadioChooseCh2)
END_MESSAGE_MAP()


// CDataChoose message handlers


BOOL CDataChoose::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	switch (m_actualChannel)
	{
	case 0:
		((CButton *)GetDlgItem(IDC_RADIO_CHOOSE_CH1))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_CHOOSE_CH2))->SetCheck(FALSE);		
		break;
	case 1:
		((CButton *)GetDlgItem(IDC_RADIO_CHOOSE_CH1))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_CHOOSE_CH2))->SetCheck(TRUE);		
		break;	
	default:
		break;
	}

	// 加载所有设备
	// LoadDevice();

	// 供测试	
	for (int i = 0; i<1;i++)
	{
		CString strResourceName = _T("");
		strResourceName.Format(_T("PXI::%d::INSTER"),i+13);
		m_listDevice.AddString(strResourceName);	
		g_deviceParam.Device[i].DeviceNumber = i + 13;

		int nLen = strResourceName.GetLength();
		//g_deviceParam.Device[i].ResourceName = (char *) malloc(strResourceName.GetLength());
	    //memcpy(g_deviceParam.Device[i].ResourceName, strResourceName.GetBuffer(strResourceName.GetLength()), strResourceName.GetLength());
		//g_deviceParam.Device[i].ResourceName = strResourceName.GetBuffer(strResourceName.GetLength());
		// 打开设备，保存其句柄
		char *res = new char[nLen];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)strResourceName.GetBuffer(nLen), -1,res,nLen,NULL,NULL);
		res[nLen] = '\0';
		DAQ_init(res, NULL, NULL, &g_deviceParam.Device[i].hDevice);

		//DAQ_init((ViRsrc)strResourceName.GetBuffer(strResourceName.GetLength()), NULL, NULL, &g_deviceParam.Device[i].hDevice);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataChoose::LoadDevice()
{
	GUID deviceGuid = {0x84c78778, 0x6949, 0x4984, {0xaa, 0x9e, 0x6e, 0x50, 0x66, 0x8e, 0x2d, 0x1c}};

	HDEVINFO deviceInfoSet = SetupDiGetClassDevs (
		(LPGUID)&deviceGuid,
		NULL, 
		NULL, 
		(DIGCF_PRESENT | DIGCF_INTERFACEDEVICE)
		);
	if(deviceInfoSet == INVALID_HANDLE_VALUE)
	{
		return;
	}

	SP_DEVINFO_DATA deviceInfoData;
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	SP_INTERFACE_DEVICE_DATA idd;	
	idd.cbSize = sizeof(idd);

	DWORD	dwIndex, dwLen;
	char	szBuf[64];
	DWORD	dwBusNum;
	char	szEnum[64];
	char	szLocation[64];
	ULONG	nAddr;

	dwIndex = 0;
	while (SetupDiEnumDeviceInterfaces(deviceInfoSet, NULL, (LPGUID)&deviceGuid, dwIndex, &idd))
	{		
		SetupDiEnumDeviceInfo(deviceInfoSet, dwIndex, &deviceInfoData);
		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_FRIENDLYNAME,
			0L,
			(PBYTE)szBuf,
			63,
			0L))
		{
		}
		else if (SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_DEVICEDESC,
			0L,
			(PBYTE)szBuf,
			63,
			0L))
		{
		}
		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_BUSNUMBER,
			0L,
			(PBYTE)&dwBusNum,
			4,
			0L))
		{
		}
		SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_ENUMERATOR_NAME,
			0L,
			(PBYTE)szEnum,
			63,
			0);
		SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_LOCATION_INFORMATION,
			0L,
			(PBYTE)szLocation,
			63,
			0);
		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet,
			&deviceInfoData,
			SPDRP_ADDRESS,
			0L,
			(PBYTE)&nAddr,
			4,
			0L))
		{
		}

		SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &idd, NULL, 0, &dwLen, NULL);
		PSP_INTERFACE_DEVICE_DETAIL_DATA iddd = (PSP_INTERFACE_DEVICE_DETAIL_DATA)(new char[dwLen]);
		if (iddd == NULL)
		{
			break;
		}
		iddd->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &idd, iddd, dwLen, NULL, NULL))
		{
			delete iddd;
			break;
		}

		CString strDevicePath = iddd->DevicePath;

		int nPos1 = strDevicePath.Find(TEXT("#"), 0);
		int nPos2 = strDevicePath.Find(TEXT("#"), nPos1 + 1);
		int nPos3 = strDevicePath.Find(TEXT("#"), nPos2 + 1);

		CString strVendorIdAndProductId = strDevicePath.Mid(nPos1 + 1, nPos2 - nPos1 - 1);		
		CString strSerialPort = strDevicePath.Mid(nPos2 + 1, nPos3 - nPos2 - 1);

		int nPos4 = strVendorIdAndProductId.Find(TEXT("&"), 0);
		CString strVendorId= strVendorIdAndProductId.Left(nPos4);
		strVendorId = strVendorId.Right(strVendorId.GetLength() - 4);

		int nPos5 = strVendorIdAndProductId.Find(TEXT("&"), nPos4 + 1);
		CString strProductId = strVendorIdAndProductId.Mid(nPos4 + 1, nPos5 - nPos4 - 1);
		strProductId = strProductId.Right(strProductId.GetLength() - 4);

		int nPos6 = strVendorIdAndProductId.Find(TEXT("&"), nPos5 + 1);
		CString strSubsysId = strVendorIdAndProductId.Mid(nPos5 + 1, nPos6 - nPos5 - 1);
		strSubsysId = strSubsysId.Right(strSubsysId.GetLength() - 7);

		// 组成资源名
		int busNumber = dwBusNum;
		int functionNumber = (USHORT)(nAddr & 0x0000FFFF);
		int deviceNumber = (USHORT)((nAddr >> 16) & 0x0000FFFF);
		CString strResourceName;
		if (busNumber == 0)
		{
			if (functionNumber == 0)
			{
				strResourceName.Format(_T("PXI0::%d::INSTR"), deviceNumber);
			}
			else
			{
				strResourceName.Format(_T("PXI0::%d.%d::INSTR"), deviceNumber, functionNumber);
			}
		}
		else
		{
			if (functionNumber == 0)
			{
				strResourceName.Format(_T("PXI0::%d-%d::INSTR"), busNumber, deviceNumber);
			}
			else
			{
				strResourceName.Format(_T("PXI0::%d-%d.%d::INSTR"), busNumber, deviceNumber, functionNumber);
			}
		}

		// 将该设备添加到界面的设备列表中
		m_listDevice.AddString(strResourceName);
		// 保存设备号到结构体中，供主界面显示设备信息
		g_deviceParam.Device[dwIndex].DeviceNumber = deviceNumber;
		// g_deviceParam.Device[dwIndex].ResourceName = strResourceName.GetBuffer(strResourceName.GetLength());
		// 打开设备，保存其句柄
		//DAQ_init((char*)(LPCTSTR)strResourceName.GetBuffer(strResourceName.GetLength()), NULL, NULL, &g_deviceParam.Device[dwIndex].hDevice);

		delete iddd;
		dwIndex++;
	}
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

void CDataChoose::OnBnClickedRadioChooseCh1()
{
	// TODO: Add your control notification handler code here
	m_actualChannel = 0;
}


void CDataChoose::OnBnClickedRadioChooseCh2()
{
	// TODO: Add your control notification handler code here
	m_actualChannel = 1;
}

// 获取显示通道的信息（ResourceName,及实际通道）
void CDataChoose::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int nSel = m_listDevice.GetCurSel();
	CString strTemp = _T("");
	m_listDevice.GetText(nSel, strTemp);
	if (strTemp != "")
	{
		// 保存显示通道的通道名及设备句柄
		if (m_actualChannel == 0)
		{
			g_deviceParam.Channel[m_showChannel].ActualName = DAQ_VAL_CH0;
		}
		else if (m_actualChannel == 1)
		{
			g_deviceParam.Channel[m_showChannel].ActualName = DAQ_VAL_CH1;
		}
		g_deviceParam.Channel[m_showChannel].DeviceHandle = g_deviceParam.Device[nSel].hDevice;
		g_deviceParam.Channel[m_showChannel].DeviceNumber = g_deviceParam.Device[nSel].DeviceNumber;
		
		// 消息传递，界面显示通道信息
		::SendMessage(m_hViewWnd, MSG_DEVICE_CHANGED, m_showChannel, g_deviceParam.Device[nSel].DeviceNumber);

		// 下发设置通道的设备句柄及通道名称
		if (m_showChannel == 0)
		{
			DAQ_SetAttributeViSession(NULL,DAQ_VAL_CH0, DAQ_ATTR_DEVICE_HANDLE, g_deviceParam.Channel[m_showChannel].DeviceHandle);
			DAQ_SetAttributeViString(NULL, DAQ_VAL_CH0, DAQ_ATTR_DEVICE_CHANNEL,g_deviceParam.Channel[m_showChannel].ActualName);
		}
		else if (m_showChannel == 1)
		{
			DAQ_SetAttributeViSession(NULL,DAQ_VAL_CH1, DAQ_ATTR_DEVICE_HANDLE, g_deviceParam.Channel[m_showChannel].DeviceHandle);
			DAQ_SetAttributeViString(NULL, DAQ_VAL_CH1, DAQ_ATTR_DEVICE_CHANNEL,g_deviceParam.Channel[m_showChannel].ActualName);
		} 
		else if (m_showChannel == 2)
		{
			DAQ_SetAttributeViSession(NULL,DAQ_VAL_CH2, DAQ_ATTR_DEVICE_HANDLE, g_deviceParam.Channel[m_showChannel].DeviceHandle);
			DAQ_SetAttributeViString(NULL, DAQ_VAL_CH2, DAQ_ATTR_DEVICE_CHANNEL,g_deviceParam.Channel[m_showChannel].ActualName);
		}
		else if (m_showChannel == 3)
		{
			DAQ_SetAttributeViSession(NULL,DAQ_VAL_CH3, DAQ_ATTR_DEVICE_HANDLE, g_deviceParam.Channel[m_showChannel].DeviceHandle);
			DAQ_SetAttributeViString(NULL, DAQ_VAL_CH3, DAQ_ATTR_DEVICE_CHANNEL,g_deviceParam.Channel[m_showChannel].ActualName);
		}

		// 配置通道	
		DAQ_ConfigureChannel(g_deviceParam.Channel[m_showChannel].DeviceHandle, g_deviceParam.Channel[m_showChannel].ActualName, g_deviceParam.Channel[m_showChannel].Range, g_deviceParam.Channel[m_showChannel].Offset, g_deviceParam.Channel[m_showChannel].Coupling, g_deviceParam.Channel[m_showChannel].ProbeAttention, g_deviceParam.Channel[m_showChannel].Enabled);
	}
	else
	{
		MessageBox(_T("请确认设备已选择"));
	}	

	CDialog::OnOK();
}



