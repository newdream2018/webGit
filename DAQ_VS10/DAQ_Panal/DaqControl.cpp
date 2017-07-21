// DaqControl.cpp : implementation file
//

#include "stdafx.h"
#include "DAQ_Panal.h"
#include "DaqControl.h"
#include "afxdialogex.h"
#include "..\DAQ_PlxDll\DAQ_PlxDll.h"
#include "math.h"

// CDaqControl dialog

IMPLEMENT_DYNAMIC(CDaqControl, CDialog)

CDaqControl::CDaqControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDaqControl::IDD, pParent)
{
	m_brush.CreateSolidBrush(RGB(245,250,255));
	m_IsFirstUpDate = true;
	m_strTrigLevel = _T("0.0mV");
	m_strCh1Volt = _T("1V/div");
	m_strCh2Volt = _T("1V/div");
	m_strCh3Volt = _T("1V/div");
	m_strCh4Volt = _T("1V/div");
}

CDaqControl::~CDaqControl()
{
	if (m_brush.GetSafeHandle() != NULL)
	{
		m_brush.DeleteObject();
	}
}

void CDaqControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CH1, m_ch1Button);
	DDX_Control(pDX, IDC_BTN_CH2, m_ch2Button);
	DDX_Control(pDX, IDC_BTN_CH3, m_ch3Button);
	DDX_Control(pDX, IDC_BTN_CH4, m_ch4Button);
	DDX_Control(pDX, IDC_CHECK_CH1, m_chkCh1Enabled);
	DDX_Control(pDX, IDC_CHECK_CH2, m_chkCh2Enabled);
	DDX_Control(pDX, IDC_CHECK_CH3, m_chkCh3Enabled);
	DDX_Control(pDX, IDC_CHECK_CH4, m_chkCh4Enabled);
	DDX_Control(pDX, IDC_STATIC_CH1_MSG, m_staticCh1Msg);
	DDX_Control(pDX, IDC_STATIC_CH2_MSG, m_staticCh2Msg);
	DDX_Control(pDX, IDC_STATIC_CH3_MSG, m_staticCh3Msg);
	DDX_Control(pDX, IDC_STATIC_CH4_MSG, m_staticCh4Msg);
	DDX_Control(pDX, IDC_BTN_DAQ, m_btnDaq);
	DDX_Control(pDX, IDC_LIST_MEAS_RESULTS, m_listMeasResults);
	DDX_Control(pDX, IDC_COMBO_MEMORY_DEPTH, m_cboMemoryDepth);
	DDX_Control(pDX, IDC_COMBO_HORI_TIMEBASE, m_cboHoriTimeBase);
	DDX_Control(pDX, IDC_COMBO_TRIG_TYPE, m_cboTrigType);
	DDX_Control(pDX, IDC_COMBO_TRIG_MODE, m_cboTrigMode);
	DDX_Text(pDX, IDC_EDIT_TRIG_LEVEL, m_strTrigLevel);
	DDX_Control(pDX, IDC_EDIT_CH1_VOLT, m_editCh1Volt);
	DDX_Control(pDX, IDC_EDIT_CH2_VOLT, m_editCh2Volt);
	DDX_Control(pDX, IDC_EDIT_CH3_VOLT, m_editCh3Volt);
	DDX_Control(pDX, IDC_EDIT_CH4_VOLT, m_editCh4Volt);
	DDX_Text(pDX, IDC_EDIT_CH1_VOLT, m_strCh1Volt);
	DDX_Text(pDX, IDC_EDIT_CH2_VOLT, m_strCh2Volt);
	DDX_Text(pDX, IDC_EDIT_CH3_VOLT, m_strCh3Volt);
	DDX_Text(pDX, IDC_EDIT_CH4_VOLT, m_strCh4Volt);
	DDX_Control(pDX, IDC_COMBO_TRIG_CONDITION, m_cboTrigCondition);
	DDX_Control(pDX, IDC_BTN_DDR_ACQ, m_btnDDRAcq);
}


BEGIN_MESSAGE_MAP(CDaqControl, CDialog)
	ON_BN_CLICKED(IDC_BTN_CH1, &CDaqControl::OnClickedBtnCh1)
	ON_BN_CLICKED(IDC_BTN_CH2, &CDaqControl::OnBnClickedBtnCh2)
	ON_BN_CLICKED(IDC_BTN_CH3, &CDaqControl::OnBnClickedBtnCh3)
	ON_BN_CLICKED(IDC_BTN_CH4, &CDaqControl::OnBnClickedBtnCh4)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_CH1, &CDaqControl::OnClickedCheckCh1)
	ON_BN_CLICKED(IDC_CHECK_CH2, &CDaqControl::OnClickedCheckCh2)
	ON_BN_CLICKED(IDC_CHECK_CH3, &CDaqControl::OnClickedCheckCh3)
	ON_BN_CLICKED(IDC_CHECK_CH4, &CDaqControl::OnClickedCheckCh4)
	ON_BN_CLICKED(IDC_BTN_DAQ, &CDaqControl::OnBnClickedBtnDaq)
	ON_BN_CLICKED(IDC_BTN_SCAN, &CDaqControl::OnBnClickedBtnScan)
	ON_MESSAGE(MSG_DEVICE_CHANGED, &CDaqControl::OnDeviceChanged)
	ON_MESSAGE(MSG_UPDATA_MEASURE_RESULT, &CDaqControl::UpdataMeasureResults)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CH1_VOLT, &CDaqControl::OnDeltaposSpinCh1Volt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CH2_VOLT, &CDaqControl::OnDeltaposSpinCh2Volt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CH3_VOLT, &CDaqControl::OnDeltaposSpinCh3Volt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CH4_VOLT, &CDaqControl::OnDeltaposSpinCh4Volt)
	ON_BN_CLICKED(IDC_BTN_DDR_ACQ, &CDaqControl::OnBnClickedBtnDdrAcq)
	ON_CBN_SELCHANGE(IDC_COMBO_MEMORY_DEPTH, &CDaqControl::OnCbnSelchangeComboMemoryDepth)
END_MESSAGE_MAP()


// CDaqControl message handlers


BOOL CDaqControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ch1Button.SetDownColor(CR_YELLOW);
	m_ch1Button.SetUpColor(CR_YELLOW);
	m_ch1Button.SetTextColor(CR_BLACK);

	m_ch2Button.SetDownColor(CR_BLUE);
	m_ch2Button.SetUpColor(CR_BLUE);
	m_ch2Button.SetTextColor(CR_BLACK);

	m_ch3Button.SetDownColor(CR_PINK);
	m_ch3Button.SetUpColor(CR_PINK);
	m_ch3Button.SetTextColor(CR_BLACK);

	m_ch4Button.SetDownColor(CR_GREEN);
	m_ch4Button.SetUpColor(CR_GREEN);
	m_ch4Button.SetTextColor(CR_BLACK);

	m_dataChoose.Create(IDD_DATA_CHOOSE,this); 
	m_dataChoose.ShowWindow(SW_HIDE);
	m_dataChoose.m_hViewWnd = this->GetSafeHwnd();

	m_cboHoriTimeBase.SetCurSel(0);
	m_cboMemoryDepth.SetCurSel(0);

	m_cboTrigType.SetCurSel(0);
	m_cboTrigMode.SetCurSel(0);
	m_cboTrigCondition.SetCurSel(0);

	m_btnDDRAcq.EnableWindow(FALSE);

	// 初始化结构体参数
	// 通道模块
	g_deviceParam.Channel[0].RangeIndex = 5;
	g_deviceParam.Channel[0].Range = 10.0;
	g_deviceParam.Channel[1].RangeIndex = 5;
	g_deviceParam.Channel[1].Range = 10.0;
	g_deviceParam.Channel[2].RangeIndex = 5;
	g_deviceParam.Channel[2].Range = 10.0;
	g_deviceParam.Channel[3].RangeIndex = 5;
	g_deviceParam.Channel[3].Range = 10.0;


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//HBRUSH CDaqControl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  Change any attributes of the DC here
//	//pDC->SetBkMode(TRANSPARENT);
//	//hbr = m_brush;
//	// TODO:  Return a different brush if the default is not desired
//	return hbr;
//}

void CDaqControl::OnClickedBtnCh1()
{
	// TODO: Add your control notification handler code here
	m_dataChoose.m_showChannel = 0;
	m_dataChoose.ShowWindow(SW_SHOW);
	m_dataChoose.CenterWindow();	
}

void CDaqControl::OnBnClickedBtnCh2()
{
	// TODO: Add your control notification handler code here
	m_dataChoose.m_showChannel = 1;
	m_dataChoose.ShowWindow(SW_SHOW);
	m_dataChoose.CenterWindow();
}

void CDaqControl::OnBnClickedBtnCh3()
{
	// TODO: Add your control notification handler code here
	m_dataChoose.m_showChannel = 2;
	m_dataChoose.ShowWindow(SW_SHOW);
	m_dataChoose.CenterWindow();
}

void CDaqControl::OnBnClickedBtnCh4()
{
	// TODO: Add your control notification handler code here
	m_dataChoose.m_showChannel = 3;
	m_dataChoose.ShowWindow(SW_SHOW);
	m_dataChoose.CenterWindow();
}

void CDaqControl::OnClickedCheckCh1()
{
	// TODO: Add your control notification handler code here
	if (m_chkCh1Enabled.GetCheck())
	{
		g_deviceParam.Channel[0].Enabled = true;
	}
	else
	{
		g_deviceParam.Channel[0].Enabled = false;
	}
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[0].DeviceHandle, g_deviceParam.Channel[0].ActualName, g_deviceParam.Channel[0].Range, g_deviceParam.Channel[0].Offset, g_deviceParam.Channel[0].Coupling, g_deviceParam.Channel[0].ProbeAttention, g_deviceParam.Channel[0].Enabled);
	LeaveCriticalSection(&g_criticalSection);
}


void CDaqControl::OnClickedCheckCh2()
{
	// TODO: Add your control notification handler code here
	if (m_chkCh2Enabled.GetCheck())
	{
		g_deviceParam.Channel[1].Enabled = true;
	}
	else
	{
		g_deviceParam.Channel[1].Enabled = false;
	}
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[1].DeviceHandle, g_deviceParam.Channel[1].ActualName, g_deviceParam.Channel[1].Range, g_deviceParam.Channel[1].Offset, g_deviceParam.Channel[1].Coupling, g_deviceParam.Channel[1].ProbeAttention, g_deviceParam.Channel[1].Enabled);
	LeaveCriticalSection(&g_criticalSection);
}


void CDaqControl::OnClickedCheckCh3()
{
	// TODO: Add your control notification handler code here
	if (m_chkCh3Enabled.GetCheck())
	{
		g_deviceParam.Channel[2].Enabled = true;
	}
	else
	{
		g_deviceParam.Channel[2].Enabled = false;
	}
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[2].DeviceHandle, g_deviceParam.Channel[2].ActualName, g_deviceParam.Channel[2].Range, g_deviceParam.Channel[2].Offset, g_deviceParam.Channel[2].Coupling, g_deviceParam.Channel[2].ProbeAttention, g_deviceParam.Channel[2].Enabled);
	LeaveCriticalSection(&g_criticalSection);
}


void CDaqControl::OnClickedCheckCh4()
{
	// TODO: Add your control notification handler code here
	if (m_chkCh4Enabled.GetCheck())
	{
		g_deviceParam.Channel[3].Enabled = true;
	}
	else
	{
		g_deviceParam.Channel[3].Enabled = false;
	}
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[3].DeviceHandle, g_deviceParam.Channel[3].ActualName, g_deviceParam.Channel[3].Range, g_deviceParam.Channel[3].Offset, g_deviceParam.Channel[3].Coupling, g_deviceParam.Channel[3].ProbeAttention, g_deviceParam.Channel[3].Enabled);
	LeaveCriticalSection(&g_criticalSection);
}


void CDaqControl::OnBnClickedBtnDaq()
{
	// TODO: Add your control notification handler code here
	if (g_deviceParam.Channel[0].Enabled && !g_deviceParam.Channel[0].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH1 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[1].Enabled && !g_deviceParam.Channel[1].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH2 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[2].Enabled && !g_deviceParam.Channel[2].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH3 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[3].Enabled && !g_deviceParam.Channel[3].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH4 没有选择相应的设备"));
		return;
	}
	if (g_pauseEnable)// 暂停
	{
		m_btnDaq.SetWindowText(_T("暂  停"));
		g_pauseEnable = false;
		SetEvent(g_hEventRuning);
	}
	else
	{
		m_btnDaq.SetWindowText(_T("采  集"));
		g_pauseEnable = true;
		ResetEvent(g_hEventRuning);
	}
}

void CDaqControl::OnBnClickedBtnDdrAcq()
{
	// TODO: Add your control notification handler code here
	if (g_pauseEnable)// 暂停
	{
		m_btnDDRAcq.SetWindowText(_T("暂  停"));
		g_pauseEnable = false;
		SetEvent(g_hEventDDRRuning);
	}
	else
	{
		m_btnDaq.SetWindowText(_T("DDR采集"));
		g_pauseEnable = true;
		ResetEvent(g_hEventDDRRuning);
	}
}

void CDaqControl::OnBnClickedBtnScan()
{
	// TODO: Add your control notification handler code here
	if (g_deviceParam.Channel[0].Enabled && !g_deviceParam.Channel[0].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH1 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[1].Enabled && !g_deviceParam.Channel[1].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH2 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[2].Enabled && !g_deviceParam.Channel[2].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH3 没有选择相应的设备"));
		return;
	}
	if (g_deviceParam.Channel[3].Enabled && !g_deviceParam.Channel[3].DeviceHandle)
	{
		MessageBox(_T("显示通道 CH4 没有选择相应的设备"));
		return;
	}
	SetEvent(g_hEventScaning);
}

LRESULT CDaqControl::OnDeviceChanged(WPARAM wParam, LPARAM lParam)// 显示通道，设备号
{
	int deviceNum = (int)lParam;
	int showChannel = (int)wParam;
	int actualChannel = 0;
	CString strTemp = _T("");

	if (_stricmp(g_deviceParam.Channel[showChannel].ActualName, DAQ_VAL_CH0) == 0)
	{
		actualChannel = 0;
	}
	else if (_stricmp(g_deviceParam.Channel[showChannel].ActualName, DAQ_VAL_CH1) == 0)
	{
		actualChannel = 1;
	}
	strTemp.Format(_T("板号 %d，通道 %d"), deviceNum, actualChannel + 1);

	if (showChannel == 0)//显示通道CH1
	{
		m_staticCh1Msg.SetWindowText(strTemp);
	}
	else if (showChannel == 1)//显示通道CH2
	{
		m_staticCh2Msg.SetWindowText(strTemp);
	}
	else if (showChannel == 2)//显示通道CH3
	{
		m_staticCh3Msg.SetWindowText(strTemp);
	}
	else if (showChannel == 3)//显示通道CH4
	{
		m_staticCh4Msg.SetWindowText(strTemp);
	}
	return 0;
}


LRESULT CDaqControl::UpdataMeasureResults(WPARAM wParam, LPARAM lParam)
{
	m_listMeasResults.ResetContent();
	UpdateResults();
	/*if (m_IsFirstUpDate)
	{
		UpdateResults();
		m_updateMeasurementTickCount1 = GetTickCount();
		m_IsFirstUpDate = FALSE;
	}
	m_updateMeasurementTickCount2 = GetTickCount();
	if (m_updateMeasurementTickCount2 - m_updateMeasurementTickCount1 >= 1000)
	{
		UpdateResults();
		m_updateMeasurementTickCount1 = m_updateMeasurementTickCount2;
	}*/

	return 0;
}

void CDaqControl::UpdateResults()
{
	CString strResults = _T("");
	int count = 0;
	if (g_deviceParam.Channel[0].Enabled)
	{
		// 最大值
		VoltageValueToString(g_deviceParam.Measurement[0].Max, &strResults);
		m_listMeasResults.InsertString(count++, _T("最大值 （1） =  ") + strResults);
		// 最小值
		VoltageValueToString(g_deviceParam.Measurement[0].Min, &strResults);
		m_listMeasResults.InsertString(count++,_T("最小值 （1） =  ") + strResults);
		// 峰峰值
		VoltageValueToString(g_deviceParam.Measurement[0].PeakToPeak, &strResults);
		m_listMeasResults.InsertString(count++,_T("峰峰值 （1） =  ") + strResults);
		// 幅度
		VoltageValueToString(g_deviceParam.Measurement[0].Amplitude, &strResults);
		m_listMeasResults.InsertString(count++, _T("幅    值 （1） =  ") + strResults);
		// 频率
		FreqValueToString(g_deviceParam.Measurement[0].Frequency, &strResults);
		m_listMeasResults.InsertString(count++, _T("频    率 （1） =  ") + strResults);
		// 周期
		TimeValueToString(g_deviceParam.Measurement[0].Period, &strResults);
		m_listMeasResults.InsertString(count++, _T("周    期 （1） =  ") + strResults);
	}

	if (g_deviceParam.Channel[1].Enabled)
	{
		// 最大值
		VoltageValueToString(g_deviceParam.Measurement[1].Max, &strResults);
		m_listMeasResults.InsertString(count++, _T("最大值 （2） =  ") + strResults);
		// 最小值
		VoltageValueToString(g_deviceParam.Measurement[1].Min, &strResults);
		m_listMeasResults.InsertString(count++, _T("最小值 （2） =  ") + strResults);
		// 峰峰值
		VoltageValueToString(g_deviceParam.Measurement[1].PeakToPeak, &strResults);
		m_listMeasResults.InsertString(count++, _T("峰峰值 （2） =  ") + strResults);
		// 幅度
		VoltageValueToString(g_deviceParam.Measurement[1].Amplitude, &strResults);
		m_listMeasResults.InsertString(count++, _T("幅    值 （2） =  ") + strResults);
		// 频率
		FreqValueToString(g_deviceParam.Measurement[1].Frequency, &strResults);
		m_listMeasResults.InsertString(count++, _T("频    率 （2） =  ") + strResults);
		// 周期
		TimeValueToString(g_deviceParam.Measurement[1].Period, &strResults);
		m_listMeasResults.InsertString(count++, _T("周    期 （2） =  ") + strResults);
	}

	if (g_deviceParam.Channel[2].Enabled)
	{
		// 最大值
		VoltageValueToString(g_deviceParam.Measurement[2].Max, &strResults);
		m_listMeasResults.InsertString(count++, _T("最大值 （3） =  ") + strResults);
		// 最小值
		VoltageValueToString(g_deviceParam.Measurement[2].Min, &strResults);
		m_listMeasResults.InsertString(count++, _T("最小值 （3） =  ") + strResults);
		// 峰峰值
		VoltageValueToString(g_deviceParam.Measurement[2].PeakToPeak, &strResults);
		m_listMeasResults.InsertString(count++, _T("峰峰值 （3） =  ") + strResults);
		// 幅度
		VoltageValueToString(g_deviceParam.Measurement[2].Amplitude, &strResults);
		m_listMeasResults.InsertString(count++, _T("幅    值 （3） =  ") + strResults);
		// 频率
		FreqValueToString(g_deviceParam.Measurement[2].Frequency, &strResults);
		m_listMeasResults.InsertString(count++, _T("频    率 （3） =  ") + strResults);
		// 周期
		TimeValueToString(g_deviceParam.Measurement[2].Period, &strResults);
		m_listMeasResults.InsertString(count++, _T("周    期 （3） =  ") + strResults);
	}

	if (g_deviceParam.Channel[3].Enabled)
	{
		// 最大值
		VoltageValueToString(g_deviceParam.Measurement[3].Max, &strResults);
		m_listMeasResults.InsertString(count++, _T("最大值 （4） =  ") + strResults);
		// 最小值
		VoltageValueToString(g_deviceParam.Measurement[3].Min, &strResults);
		m_listMeasResults.InsertString(count++, _T("最小值 （4） =  ") + strResults);
		// 峰峰值
		VoltageValueToString(g_deviceParam.Measurement[3].PeakToPeak, &strResults);
		m_listMeasResults.InsertString(count++, _T("峰峰值 （4） =  ") + strResults);
		// 幅度
		VoltageValueToString(g_deviceParam.Measurement[3].Amplitude, &strResults);
		m_listMeasResults.InsertString(count++, _T("幅    值 （4） =  ") + strResults);
		// 频率
		FreqValueToString(g_deviceParam.Measurement[3].Frequency, &strResults);
		m_listMeasResults.InsertString(count++, _T("频    率 （4） =  ") + strResults);
		// 周期
		TimeValueToString(g_deviceParam.Measurement[3].Period, &strResults);
		m_listMeasResults.InsertString(count++, _T("周    期 （4） =  ") + strResults);
	}
}

void CDaqControl::VoltageValueToString(double voltageValue, CString *strValue)
{
	if (fabs(voltageValue) >= 10000.0)
	{
		(*strValue).Format(_T("%.1fKV"), voltageValue/1000);
	}
	else if (fabs(voltageValue) >= 1000.0)
	{
		(*strValue).Format(_T("%.2fKV"), voltageValue/1000);
	}
	else if (fabs(voltageValue) >= 100.0)
	{
		(*strValue).Format(_T("%.0fV"), voltageValue);
	}
	else if (fabs(voltageValue) >= 10.0)
	{
		(*strValue).Format(_T("%.1fV"), voltageValue);
	}
	else if (fabs(voltageValue) >= 1.0)
	{
		(*strValue).Format(_T("%.2fV"), voltageValue);
	}
	else if (fabs(voltageValue) >= 0.1)
	{
		(*strValue).Format(_T("%.0fmV"), voltageValue * 1000);
	}
	else if (fabs(voltageValue) >= 0.01)
	{
		(*strValue).Format(_T("%.1fmV"), voltageValue * 1000);
	}
	else if (fabs(voltageValue) >= 0.001)
	{
		(*strValue).Format(_T("%.2fmV"), voltageValue * 1000);
	}
	else if (fabs(voltageValue) >= 0.0001)
	{
		(*strValue).Format(_T("%.0fuV"), voltageValue * 1000000);
	}
	else if (fabs(voltageValue) >= 0.00001)
	{
		(*strValue).Format(_T("%.1fuV"), voltageValue * 1000000);
	}
	else
	{
		(*strValue).Format(_T("%.2fuV"), voltageValue * 1000000);
	}
}

void CDaqControl::TimeValueToString(double timeValue, CString *strValue)
{
	if (fabs(timeValue) >= 10.0)
	{
		(*strValue).Format(_T("%.1fs"), timeValue);
	}
	else if (fabs(timeValue) >= 1.0)
	{
		(*strValue).Format(_T("%.2fs"), timeValue);
	}
	else if (fabs(timeValue) >= 0.1)
	{
		(*strValue).Format(_T("%.0fms"), timeValue * 1000);
	}
	else if (fabs(timeValue) >= 0.01)
	{
		(*strValue).Format(_T("%.1fms"), timeValue * 1000);
	}
	else if (fabs(timeValue) >= 0.001)
	{
		(*strValue).Format(_T("%.2fms"), timeValue * 1000);
	}
	else if (fabs(timeValue) >= 0.0001)
	{
		(*strValue).Format(_T("%.0fus"), timeValue * 1000000);
	}
	else if (fabs(timeValue) >= 0.00001)
	{
		(*strValue).Format(_T("%.1fus"), timeValue * 1000000);
	}
	else if (fabs(timeValue) >= 0.000001)
	{
		(*strValue).Format(_T("%.2fus"), timeValue * 1000000);
	}
	else if (fabs(timeValue) >= 0.0000001)
	{
		(*strValue).Format(_T("%.0fns"), timeValue * 1000000000);
	}
	else if (fabs(timeValue) >= 0.00000001)
	{
		(*strValue).Format(_T("%.1fns"), timeValue * 1000000000);
	}
	else if (fabs(timeValue) >= 0.000000001)
	{
		(*strValue).Format(_T("%.2fns"), timeValue * 1000000000);
	}
	else if (fabs(timeValue) >= 0.0000000001)
	{
		(*strValue).Format(_T("%.0fps"), timeValue * 1000000000000);
	}
	else if (fabs(timeValue) >= 0.00000000001)
	{
		(*strValue).Format(_T("%.1fps"), timeValue * 1000000000000);
	}
	else
	{
		(*strValue).Format(_T("%.2fps"), timeValue * 1000000000000);
	}
}

void CDaqControl::FreqValueToString(double freqValue, CString *strValue)
{
	if (fabs(freqValue) >= 1000000000.0)
	{
		(*strValue).Format(_T("%.2fGHz"), freqValue/1000000000.0);
	}
	else if (fabs(freqValue) >= 100000000.0)
	{
		(*strValue).Format(_T("%.0fMHz"), freqValue/1000000.0);
	}
	else if (fabs(freqValue) >= 10000000.0)
	{
		(*strValue).Format(_T("%.1fMHz"), freqValue/1000000.0);
	}
	else if (fabs(freqValue) >= 1000000.0)
	{
		(*strValue).Format(_T("%.2fMHz"), freqValue/1000000.0);
	}
	else if (fabs(freqValue) >= 100000.0)
	{
		(*strValue).Format(_T("%.0fKHz"), freqValue/1000.0);
	}
	else if (fabs(freqValue) >= 10000.0)
	{
		(*strValue).Format(_T("%.1fKHz"), freqValue/1000.0);
	}
	else if (fabs(freqValue) >= 1000.0)
	{
		(*strValue).Format(_T("%.2fKHz"), freqValue/1000.0);
	}
	else if (fabs(freqValue) >= 100.0)
	{
		(*strValue).Format(_T("%.0fHz"), freqValue);
	}
	else if (fabs(freqValue) >= 10.0)
	{
		(*strValue).Format(_T("%.1fHz"), freqValue);
	}
	else
	{
		(*strValue).Format(_T("%.2fHz"), freqValue);
	}
}

void CDaqControl::PercentageValueToString(double percentageValue, CString *strValue)
{
	if (fabs(percentageValue) > 100.0)
	{
		(*strValue).Format(_T("%.0f"),percentageValue);
	}
	else if (fabs(percentageValue) > 10.0)
	{
		(*strValue).Format(_T("%.1f"),percentageValue);
	}
	else if (fabs(percentageValue) > 0.0)
	{
		(*strValue).Format(_T("%.2f"),percentageValue);
	}
	else
	{
		(*strValue).Format(_T("%.2f"),0.00);
	}
	(*strValue) += _T("%");
}

// 切换垂直灵敏度
void CDaqControl::OnDeltaposSpinCh1Volt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta == -1)//点击了向上箭头
	{
		g_deviceParam.Channel[0].RangeIndex -= 1;
	}
	else if (pNMUpDown->iDelta == 1)//点击了向下箭头
	{
		g_deviceParam.Channel[0].RangeIndex += 1;
	}

	if (g_deviceParam.Channel[0].RangeIndex == -1)
	{
		g_deviceParam.Channel[0].RangeIndex = 0;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	if (g_deviceParam.Channel[0].RangeIndex == 6)
	{
		g_deviceParam.Channel[0].RangeIndex = 5;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	g_deviceParam.Channel[0].Range = GetChannelRange(g_deviceParam.Channel[0].RangeIndex);

	// 更新显示信息
	VoltageValueToString(g_deviceParam.Channel[0].Range/10, &m_strCh1Volt);
	m_editCh1Volt.SetWindowText(m_strCh1Volt + _T("/div"));
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[0].DeviceHandle, g_deviceParam.Channel[0].ActualName, g_deviceParam.Channel[0].Range, g_deviceParam.Channel[0].Offset, g_deviceParam.Channel[0].Coupling, g_deviceParam.Channel[0].ProbeAttention, g_deviceParam.Channel[0].Enabled);
	LeaveCriticalSection(&g_criticalSection);

	*pResult = 0;
}


void CDaqControl::OnDeltaposSpinCh2Volt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta == -1)//点击了向上箭头
	{
		g_deviceParam.Channel[1].RangeIndex -= 1;
	}
	else if (pNMUpDown->iDelta == 1)//点击了向下箭头
	{
		g_deviceParam.Channel[1].RangeIndex += 1;
	}

	if (g_deviceParam.Channel[1].RangeIndex == -1)
	{
		g_deviceParam.Channel[1].RangeIndex = 0;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	if (g_deviceParam.Channel[1].RangeIndex == 6)
	{
		g_deviceParam.Channel[1].RangeIndex = 5;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	g_deviceParam.Channel[1].Range = GetChannelRange(g_deviceParam.Channel[1].RangeIndex);

	// 更新显示信息
	VoltageValueToString(g_deviceParam.Channel[1].Range/10, &m_strCh2Volt);
	m_editCh2Volt.SetWindowText(m_strCh2Volt + _T("/div"));
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[1].DeviceHandle, g_deviceParam.Channel[1].ActualName, g_deviceParam.Channel[1].Range, g_deviceParam.Channel[1].Offset, g_deviceParam.Channel[1].Coupling, g_deviceParam.Channel[1].ProbeAttention, g_deviceParam.Channel[1].Enabled);
	LeaveCriticalSection(&g_criticalSection);

	*pResult = 0;
}


void CDaqControl::OnDeltaposSpinCh3Volt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta == -1)//点击了向上箭头
	{
		g_deviceParam.Channel[2].RangeIndex -= 1;
	}
	else if (pNMUpDown->iDelta == 1)//点击了向下箭头
	{
		g_deviceParam.Channel[2].RangeIndex += 1;
	}

	if (g_deviceParam.Channel[2].RangeIndex == -1)
	{
		g_deviceParam.Channel[2].RangeIndex = 0;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	if (g_deviceParam.Channel[2].RangeIndex == 6)
	{
		g_deviceParam.Channel[2].RangeIndex = 5;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	g_deviceParam.Channel[2].Range = GetChannelRange(g_deviceParam.Channel[2].RangeIndex);

	// 更新显示信息
	VoltageValueToString(g_deviceParam.Channel[2].Range/10, &m_strCh3Volt);
	m_editCh3Volt.SetWindowText(m_strCh3Volt + _T("/div"));
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[2].DeviceHandle, g_deviceParam.Channel[2].ActualName, g_deviceParam.Channel[2].Range, g_deviceParam.Channel[2].Offset, g_deviceParam.Channel[2].Coupling, g_deviceParam.Channel[2].ProbeAttention, g_deviceParam.Channel[2].Enabled);
	LeaveCriticalSection(&g_criticalSection);

	*pResult = 0;
}


void CDaqControl::OnDeltaposSpinCh4Volt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta == -1)//点击了向上箭头
	{
		g_deviceParam.Channel[3].RangeIndex -= 1;
	}
	else if (pNMUpDown->iDelta == 1)//点击了向下箭头
	{
		g_deviceParam.Channel[3].RangeIndex += 1;
	}

	if (g_deviceParam.Channel[3].RangeIndex == -1)
	{
		g_deviceParam.Channel[3].RangeIndex = 0;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	if (g_deviceParam.Channel[3].RangeIndex == 6)
	{
		g_deviceParam.Channel[3].RangeIndex = 5;
		MessageBox(_T("垂直灵敏度调到极限"),_T(""));
	}
	g_deviceParam.Channel[3].Range = GetChannelRange(g_deviceParam.Channel[3].RangeIndex);

	// 更新显示信息
	VoltageValueToString(g_deviceParam.Channel[3].Range/10, &m_strCh4Volt);
	m_editCh4Volt.SetWindowText(m_strCh4Volt + _T("/div"));
	// 配置通道	
	EnterCriticalSection(&g_criticalSection);
	DAQ_ConfigureChannel(g_deviceParam.Channel[3].DeviceHandle, g_deviceParam.Channel[3].ActualName, g_deviceParam.Channel[3].Range, g_deviceParam.Channel[3].Offset, g_deviceParam.Channel[3].Coupling, g_deviceParam.Channel[3].ProbeAttention, g_deviceParam.Channel[3].Enabled);
	LeaveCriticalSection(&g_criticalSection);

	*pResult = 0;
}

// 由垂直灵敏度序号得到垂直灵敏度的值
double CDaqControl::GetChannelRange(int index)
{
	double range = 0.0;
	switch (index)
	{
	case 0:// 20mV/div
		range = 0.2;
		break;
	case 1:// 50mV/div
		range = 0.5;
		break;
	case 2:// 100mV/div
		range = 1.0;
		break;
	case 3:// 200mV/div
		range = 2.0;
		break;
	case 4:// 500mV/div
		range = 5.0;
		break;
	case 5:// 1V/div
		range = 10.0;
		break;
	default:
		break;
	}

	return range;
}

// 改变存储深度
void CDaqControl::OnCbnSelchangeComboMemoryDepth()
{
	// TODO: Add your control notification handler code here
	int index = m_cboMemoryDepth.GetCurSel();
	if (index > 0)//DDR采集
	{
		m_btnDaq.EnableWindow(FALSE);
		m_btnDDRAcq.EnableWindow(TRUE);
	}
	else// 普通采集
	{
		m_btnDaq.EnableWindow(TRUE);
		m_btnDDRAcq.EnableWindow(FALSE);
	}
	UINT memoryDepth = 2;//2K
	switch (index)
	{
	case 0:// 2K
		memoryDepth = 0x800;
		break;
	case 1:// 2M
		memoryDepth = 0x200000;
		break;
	case 2:// 4M
		memoryDepth = 0x400000;
		break;
	case 3:// 32M
		memoryDepth = 0x2000000;
		break;
	case 4:// 64M
		memoryDepth = 0x4000000;
		break;
	case 5:// 256M
		memoryDepth = 0x10000000;
		break;
	case 6:// 512M
		memoryDepth = 0x20000000;
		break;
	case 7:// 1G
		memoryDepth = 0x40000000;
		break;
	case 8:// 2G
		memoryDepth = 0x80000000;
		break;
	case 9:// 任意（测试）//40K
		memoryDepth = 0x0000A000;
		break;
	default:
		break;
	}
	// 配置存储深度
	DAQ_SetAttributeViInt32(NULL, NULL, DAQ_ATTR_MEMORY_SIZE, memoryDepth);
}
