
// DAQ_PanalView.cpp : implementation of the CDAQ_PanalView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DAQ_Panal.h"
#endif

#include "DAQ_PanalDoc.h"
#include "DAQ_PanalView.h"
#include "..\DAQ_PlxDll\DAQ_PlxDll.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDAQ_PanalView

IMPLEMENT_DYNCREATE(CDAQ_PanalView, CFormView)

BEGIN_MESSAGE_MAP(CDAQ_PanalView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDAQ_PanalView construction/destruction

CDAQ_PanalView::CDAQ_PanalView()
	: CFormView(CDAQ_PanalView::IDD)
{
	// TODO: add construction code here
}

CDAQ_PanalView::~CDAQ_PanalView()
{
}

void CDAQ_PanalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CDAQ_PanalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CDAQ_PanalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CreateWaveWnd();
	CRect rect;
	GetClientRect(&rect);
	m_controlPanalWidth = 280;
	m_daqControl.Create(IDD_DAQ_CONTROL,this);                     
	m_daqControl.MoveWindow((rect.right - rect.left) - m_controlPanalWidth, 0, m_controlPanalWidth, rect.bottom-rect.top);
	m_daqControl.ShowWindow(SW_SHOW);
	m_daqControl.m_pView = this;

	g_hEventRuning = CreateEvent(NULL,TRUE,FALSE,NULL);
	g_hEventScaning = CreateEvent(NULL,TRUE,FALSE,NULL);
	g_hEventDDRRuning = CreateEvent(NULL,TRUE,FALSE,NULL);
	AfxBeginThread(AquisitionThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL);
	AfxBeginThread(DDRAquisitionThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL);
	AfxBeginThread(ScanThread, this, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL);
	InitializeCriticalSection(&g_criticalSection);//用于保护对硬件的操作
}

void CDAQ_PanalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDAQ_PanalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDAQ_PanalView diagnostics

#ifdef _DEBUG
void CDAQ_PanalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDAQ_PanalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDAQ_PanalDoc* CDAQ_PanalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDAQ_PanalDoc)));
	return (CDAQ_PanalDoc*)m_pDocument;
}
#endif //_DEBUG


// CDAQ_PanalView message handlers


void CDAQ_PanalView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	GetClientRect(m_rectPanal);
	CRect m_waveRect;

	if (IsWindow(m_waveCanvas.GetSafeHwnd()))
	{
		m_waveRect.left = m_rectPanal.left+10;
		m_waveRect.top = m_rectPanal.top+10;
		m_waveRect.right = m_rectPanal.right - m_controlPanalWidth - 10;
		m_waveRect.bottom = m_rectPanal.bottom - 10;

		m_waveCanvas.DestroyWindow();
		m_waveCanvas.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_waveRect, this, 0, NULL);
		m_waveCanvas.DrawWave();
	}

	if (IsWindow(m_aboveStatusWnd.GetSafeHwnd()))
	{
		m_aboveWndRect.left = m_rectPanal.left;
		m_aboveWndRect.top = m_rectPanal.top;
		m_aboveWndRect.right = m_rectPanal.right - m_controlPanalWidth;
		m_aboveWndRect.bottom = m_rectPanal.top + 10;

		m_aboveStatusWnd.DestroyWindow();
		m_aboveStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_aboveWndRect, this, 0, NULL);
	}

	if (IsWindow(m_belowStatusWnd.GetSafeHwnd()))
	{
		m_belowWndRect.left = m_rectPanal.left;
		m_belowWndRect.top = m_rectPanal.bottom - 10;
		m_belowWndRect.right = m_rectPanal.right - m_controlPanalWidth;
		m_belowWndRect.bottom = m_rectPanal.bottom;

		m_belowStatusWnd.DestroyWindow();
		m_belowStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_belowWndRect, this, 0, NULL);
	}
	
	if (IsWindow(m_leftStatusWnd.GetSafeHwnd()))
	{		
		m_leftWndRect.left = m_rectPanal.left;
		m_leftWndRect.top = m_rectPanal.top - 10;
		m_leftWndRect.right = m_rectPanal.left + 10;
		m_leftWndRect.bottom = m_rectPanal.bottom - 10;		
		m_leftStatusWnd.DestroyWindow();
		m_leftStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_leftWndRect, this, 0, NULL);
	}

	if (IsWindow(m_rightStatusWnd.GetSafeHwnd()))
	{		
		m_rightWndRect.left = m_rectPanal.right - m_controlPanalWidth - 10;
		m_rightWndRect.top = m_rectPanal.top - 10;
		m_rightWndRect.right = m_rectPanal.right - m_controlPanalWidth;
		m_rightWndRect.bottom = m_rectPanal.bottom - 10;	
		m_rightStatusWnd.DestroyWindow();
		m_rightStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_rightWndRect, this, 0, NULL);
	}

	if (IsWindow(m_daqControl.GetSafeHwnd()))
	{
		m_daqControl.MoveWindow((m_rectPanal.Width()) - m_controlPanalWidth, 0, m_controlPanalWidth, m_rectPanal.Height());
	}
}

void CDAQ_PanalView::CreateWaveWnd()
{
	GetClientRect(m_rectPanal);
	
	if (IsWindow(m_waveCanvas.GetSafeHwnd()))
	{
		m_waveCanvas.DestroyWindow();
	}
	m_waveRect.left = m_rectPanal.left + 10;
	m_waveRect.top = m_rectPanal.top + 10;
	m_waveRect.right = m_rectPanal.right - m_controlPanalWidth + 10;
	m_waveRect.bottom = m_rectPanal.bottom - 10;
	m_waveCanvas.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_waveRect, this, 0, NULL);

	if (IsWindow(m_aboveStatusWnd.GetSafeHwnd()))
	{
		m_aboveStatusWnd.DestroyWindow();
	}
	m_aboveWndRect.left = m_rectPanal.left;
	m_aboveWndRect.top = m_rectPanal.top;
	m_aboveWndRect.right = m_rectPanal.right - m_controlPanalWidth;
	m_aboveWndRect.bottom = m_rectPanal.top + 10;
	m_aboveStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_aboveWndRect, this, 0, NULL);

	if (IsWindow(m_belowStatusWnd.GetSafeHwnd()))
	{
		m_belowStatusWnd.DestroyWindow();
	}
	m_belowWndRect.left = m_rectPanal.left;
	m_belowWndRect.top = m_rectPanal.bottom - 10;
	m_belowWndRect.right = m_rectPanal.right - m_controlPanalWidth;
	m_belowWndRect.bottom = m_rectPanal.bottom;		
	m_belowStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_belowWndRect, this, 0, NULL);

	if (IsWindow(m_leftStatusWnd.GetSafeHwnd()))
	{
		m_leftStatusWnd.DestroyWindow();
	}
	m_leftWndRect.left = m_rectPanal.left;
	m_leftWndRect.top = m_rectPanal.top - 10;
	m_leftWndRect.right = m_rectPanal.left + 10;
	m_leftWndRect.bottom = m_rectPanal.bottom - 10;	
	m_leftStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_leftWndRect, this, 0, NULL);

	if (IsWindow(m_rightStatusWnd.GetSafeHwnd()))
	{
		m_rightStatusWnd.DestroyWindow();
	}
	m_rightWndRect.left = m_rectPanal.right - m_controlPanalWidth-10;
	m_rightWndRect.top = m_rectPanal.top - 10;
	m_rightWndRect.right = m_rectPanal.right - m_controlPanalWidth;
	m_rightWndRect.bottom = m_rectPanal.bottom - 10;	
	m_rightStatusWnd.Create(_T(""), _T(""), WS_VISIBLE | WS_CHILD, m_rightWndRect, this, 0, NULL);
}

UINT CDAQ_PanalView::AquisitionThread(LPVOID lParam)
{
	CDAQ_PanalView *pView = (CDAQ_PanalView*)lParam;
	while(g_isRun)
	{		
		WaitForSingleObject(g_hEventRuning, INFINITE); // 等待工作线程

		pView->GetCheckedDevice();

		ViInt32 status = 0;
		EnterCriticalSection(&g_criticalSection);

		do 
		{
			pView->ResetAcquisition();
			pView->AcquisitionStatus(&status);
		} while (status != DAQ_VAL_ACQ_CAN_INIT_ACQ);//可启动下一次采集

		// 启动采集		
		pView->InitAcquisition();
		
		// 查询采集完成状态		
		do 
		{
			pView->AcquisitionStatus(&status);
		} while (status != DAQ_VAL_ACQ_COMPLETE);// 查询采集是否完成

		// 采集数据
		pView->FetchWaveData();

		LeaveCriticalSection(&g_criticalSection);

		Sleep(50);
		// 画图显示
		pView->m_waveCanvas.DrawWave();
		// 读取参数测量结果
		pView->MeasureParamForChannel();
		
		if (!g_isRun)//停止运行
		{
			ResetEvent(g_hEventRuning);
		}
	}
	return TRUE;
}

UINT CDAQ_PanalView::DDRAquisitionThread(LPVOID lParam)
{
	CDAQ_PanalView *pView = (CDAQ_PanalView*)lParam;
	while(g_isRun)
	{		
		WaitForSingleObject(g_hEventDDRRuning, INFINITE); // 等待工作线程
		pView->GetCheckedDevice();

		ViInt32 status = 0;
		EnterCriticalSection(&g_criticalSection);

		// 复位
		pView->ResetAcquisition();

		// 查询状态
		//pView->AcquisitionStatus(&status);
		//if (status != DAQ_VAL_ACQ_DDR_RESET)// 复位不成功
		//{
		//	ResetEvent(g_hEventDDRRuning);
		//	pView->MessageBox(_T("ddr3复位失败，跳出深存储模式"));
		//	break;
		//}

		// 启动采集		
		pView->InitAcquisition();

		do 
		{
			pView->AcquisitionStatus(&status);
		} while (status != DAQ_VAL_ACQ_DDR_IN_PROGRESS); // 正在写
		Sleep(100);// 采数时间

		do 
		{
			pView->AcquisitionStatus(&status);
		} while (status != DAQ_VAL_ACQ_DDR_COMPLETE); // 采集是否完成

		do 
		{
			pView->AcquisitionStatus(&status);
		} while (status != DAQ_VAL_ACQ_DDR_CAN_READ);

		// 采集数据
		pView->FetchScanWaveData();
		LeaveCriticalSection(&g_criticalSection);

		if (!g_isRun)//停止运行
		{
			ResetEvent(g_hEventDDRRuning);
		}
	}

	return TRUE;
}

UINT CDAQ_PanalView::ScanThread(LPVOID lParam)
{
	CDAQ_PanalView *pView = (CDAQ_PanalView*)lParam;
	while(1)
	{		
		WaitForSingleObject(g_hEventScaning, INFINITE);//等待工作线程

		EnterCriticalSection(&g_criticalSection);
		pView->FetchScanWaveData();
		Sleep(500);

		//pView->m_waveCanvas.DrawWave();
		ResetEvent(g_hEventScaning);
		LeaveCriticalSection(&g_criticalSection);
	}
	return TRUE;
}

// 遍历四个通道选择的设备，看总共占据几台设备
void CDAQ_PanalView::GetCheckedDevice()
{
	int count = 0;
	int n = 0;

	for (int i = 0; i<4; i++)
	{
		if (g_deviceParam.Channel[i].DeviceHandle != 0)// 找到第一台设备
		{
			g_deviceParam.CheckedDevice.DeviceHandle[count] = g_deviceParam.Channel[i].DeviceHandle;
			n = i;
			break;
		}
	}

	for (int i = n+1; i<4; i++)
	{
		if (g_deviceParam.Channel[i].DeviceHandle != 0)
		{
			int j = 0;
			for (j = 0;j < count+1; j++)
			{
				if (g_deviceParam.CheckedDevice.DeviceHandle[j] == g_deviceParam.Channel[i].DeviceHandle)//已经存储了该通道的设备句柄，break，跳转到下一通道
				{
					break;
				}
				else //该句柄不是该通道的句柄，查询下一个已存储句柄
				{
					continue;
				}
			}

			if (j == count+1)// 没有在已存储句柄中找到该通道的句柄，将其添加到以存储句柄中，count加1
			{
				count += 1;
				g_deviceParam.CheckedDevice.DeviceHandle[count] = g_deviceParam.Channel[i].DeviceHandle;
			}
		}
	}
	g_deviceParam.CheckedDevice.DeviceCount = count + 1;
}

// 启动采集
void CDAQ_PanalView::InitAcquisition()
{
	for (int m = 0; m<g_deviceParam.CheckedDevice.DeviceCount; m++)
	{
		DAQ_InitiateAcquisition(g_deviceParam.CheckedDevice.DeviceHandle[m]);
	}
}

void CDAQ_PanalView::AcquisitionStatus(ViInt32 *Status)
{
	ViStatus status[4] = {-1};

	while(g_isRun)// 加条件限制，以免造成死循环
	{
		for (int m = 0; m<g_deviceParam.CheckedDevice.DeviceCount; m++)
		{
			DAQ_AcquisitionStatus(g_deviceParam.CheckedDevice.DeviceHandle[m], &status[m]);
		}

		*Status = status[0];
		int n = 0;
		for (n = 1; n<g_deviceParam.CheckedDevice.DeviceCount; n++)
		{
			if (status[n] != *Status)
			{
				break;
			}
		}
		if (n == g_deviceParam.CheckedDevice.DeviceCount)
		{
			break;
		}
	}
}

void CDAQ_PanalView::ResetAcquisition()
{
	for (int m = 0; m<g_deviceParam.CheckedDevice.DeviceCount; m++)
	{
		DAQ_ResetAcquisition(g_deviceParam.CheckedDevice.DeviceHandle[m]);
	}
}

void CDAQ_PanalView::FetchWaveData()
{
	ViInt32 WaveformSize = 500;
	ViInt32 ActualPoints = 500; 
	ViReal64 InitialX = 0,XIncrement = 0;
	if (g_deviceParam.Channel[0].Enabled)//若通道1有效
	{
		ViReal64 *WaveformArray = new ViReal64[ActualPoints];
		memset(WaveformArray,0,ActualPoints*sizeof(ViReal64));
		DAQ_FetchWaveform(g_deviceParam.Channel[0].DeviceHandle, g_deviceParam.Channel[0].ActualName, WaveformSize, WaveformArray, &ActualPoints, &InitialX, &XIncrement);
		memcpy(g_deviceParam.DisplayData[0].MaxData, WaveformArray, 500*sizeof(ViReal64));
		memcpy(g_deviceParam.DisplayData[0].MinData, WaveformArray, 500*sizeof(ViReal64));
		delete WaveformArray;
		WaveformArray = NULL;
	}

	if (g_deviceParam.Channel[1].Enabled)//若通道2有效
	{
		ViReal64 *WaveformArray = new ViReal64[ActualPoints];
		memset(WaveformArray,0,ActualPoints*sizeof(ViReal64));
		DAQ_FetchWaveform(g_deviceParam.Channel[1].DeviceHandle, g_deviceParam.Channel[1].ActualName, WaveformSize, WaveformArray, &ActualPoints, &InitialX, &XIncrement);
		memcpy(g_deviceParam.DisplayData[1].MaxData, WaveformArray, 500*sizeof(ViReal64));
		memcpy(g_deviceParam.DisplayData[1].MinData, WaveformArray, 500*sizeof(ViReal64));
		delete WaveformArray;
		WaveformArray = NULL;
	}

/*	if (g_deviceParam.Channel[2].Enabled)//若通道3有效
	{
		ViInt32 *WaveformArray = new ViInt32[ActualPoints];
		memset(WaveformArray,0,ActualPoints*sizeof(ViInt32));
		//DAQ_FetchWaveform(g_deviceParam.Channel[2].DeviceHandle, g_deviceParam.Channel[2].ActualName, WaveformSize, WaveformArray, &ActualPoints, &InitialX, &XIncrement);
		memcpy(g_deviceParam.DisplayData[2].MaxData, WaveformArray, 500*sizeof(ViInt32));
		memcpy(g_deviceParam.DisplayData[2].MinData, WaveformArray, 500*sizeof(ViInt32));
		delete WaveformArray;
		WaveformArray = NULL;
	}

	if (g_deviceParam.Channel[3].Enabled)//若通道4有效
	{
		ViInt32 *WaveformArray = new ViInt32[ActualPoints];
		memset(WaveformArray,0,ActualPoints*sizeof(ViInt32));
		//DAQ_FetchWaveform(g_deviceParam.Channel[3].DeviceHandle, g_deviceParam.Channel[3].ActualName, WaveformSize, WaveformArray, &ActualPoints, &InitialX, &XIncrement);
		memcpy(g_deviceParam.DisplayData[3].MaxData, WaveformArray, 500*sizeof(ViInt32));
		memcpy(g_deviceParam.DisplayData[3].MinData, WaveformArray, 500*sizeof(ViInt32));
		delete WaveformArray;
		WaveformArray = NULL;
	}*/
}

void CDAQ_PanalView::FetchScanWaveData()
{
	int waveformSize = 40*1024;
	ViByte *WaveformArray1 = new ViByte[waveformSize];
	memset(WaveformArray1, 0, waveformSize*sizeof(ViByte));
	ViByte *WaveformArray2 = new ViByte[waveformSize];
	memset(WaveformArray2, 0, waveformSize*sizeof(ViByte));
	ViByte *WaveformArray3 = new ViByte[waveformSize];
	memset(WaveformArray3, 0, waveformSize*sizeof(ViByte));
	ViByte *WaveformArray4 = new ViByte[waveformSize];
	memset(WaveformArray4, 0, waveformSize*sizeof(ViByte));
	// 数据采集
	if (g_deviceParam.Channel[0].Enabled)
	{
		DAQ_FetchWholeWaveform(g_deviceParam.Channel[0].DeviceHandle, g_deviceParam.Channel[0].ActualName, waveformSize, WaveformArray1);
	}
	if (g_deviceParam.Channel[1].Enabled)
	{
		DAQ_FetchWholeWaveform(g_deviceParam.Channel[1].DeviceHandle, g_deviceParam.Channel[1].ActualName, waveformSize, WaveformArray2);
	}
	if (g_deviceParam.Channel[2].Enabled)
	{
		DAQ_FetchWholeWaveform(g_deviceParam.Channel[2].DeviceHandle, g_deviceParam.Channel[2].ActualName, waveformSize, WaveformArray3);
	}
	if (g_deviceParam.Channel[3].Enabled)
	{
		DAQ_FetchWholeWaveform(g_deviceParam.Channel[3].DeviceHandle, g_deviceParam.Channel[3].ActualName, waveformSize, WaveformArray4);
	}
	// 滚动显示
	for (int i = 0;i<16384-500; i++)
	{
		for (int j = 0; j<500;j++)
		{
			g_deviceParam.DisplayData[0].ScanMaxData[j] = WaveformArray1[j + i];
			g_deviceParam.DisplayData[0].ScanMinData[j] = WaveformArray1[j + i];

			g_deviceParam.DisplayData[1].ScanMaxData[j] = WaveformArray2[j + i];
			g_deviceParam.DisplayData[1].ScanMinData[j] = WaveformArray2[j + i];

			g_deviceParam.DisplayData[2].ScanMaxData[j] = WaveformArray3[j + i];
			g_deviceParam.DisplayData[2].ScanMinData[j] = WaveformArray3[j + i];

			g_deviceParam.DisplayData[3].ScanMaxData[j] = WaveformArray4[j + i];
			g_deviceParam.DisplayData[3].ScanMinData[j] = WaveformArray4[j + i];
		}
		m_waveCanvas.DrawScanWave();


	}

	delete WaveformArray1;
	WaveformArray1 = NULL;
	delete WaveformArray2;
	WaveformArray2 = NULL;
	delete WaveformArray3;
	WaveformArray3 = NULL;
	delete WaveformArray4;
	WaveformArray4 = NULL;
}

void CDAQ_PanalView::MeasureParamForChannel()
{
	if (g_deviceParam.Channel[0].Enabled)
	{
		DAQ_FetchWaveformMeasurement(g_deviceParam.Channel[0].DeviceHandle,g_deviceParam.Channel[0].ActualName, DAQ_VAL_FREQUENCY, &g_deviceParam.Measurement[0].Frequency);
		DAQ_FetchWaveformMeasurement(g_deviceParam.Channel[0].DeviceHandle,g_deviceParam.Channel[0].ActualName, DAQ_VAL_AMPLITUDE, &g_deviceParam.Measurement[0].Amplitude);
	}
	if (g_deviceParam.Channel[1].Enabled)
	{
	}
	if (g_deviceParam.Channel[2].Enabled)
	{
	}
	if (g_deviceParam.Channel[3].Enabled)
	{
	}
	//::SendMessage(m_daqControl.GetSafeHwnd(), MSG_UPDATA_MEASURE_RESULT, 0, 0);	
}


void CDAQ_PanalView::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: Add your message handler code here
	g_isRun = false;

	EnterCriticalSection(&g_criticalSection);
	for (int i = 0; i<g_deviceParam.CheckedDevice.DeviceCount; i++)
	{
		DAQ_close(g_deviceParam.CheckedDevice.DeviceHandle[i]);
	}	
	LeaveCriticalSection(&g_criticalSection);
	if (g_hEventRuning != NULL)
	{
		CloseHandle(g_hEventRuning);
	}
	if (g_hEventScaning != NULL)
	{
		CloseHandle(g_hEventScaning);
	}

	DeleteCriticalSection(&g_criticalSection);
}
