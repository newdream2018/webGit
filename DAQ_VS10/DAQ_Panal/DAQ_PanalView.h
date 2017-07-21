
// DAQ_PanalView.h : interface of the CDAQ_PanalView class
//

#pragma once

#include "resource.h"
#include "Global.h"
#include "WaveCanvas.h"
#include "AboveStatusWnd.h"
#include "BelowStatusWnd.h"
#include "LeftStatusWnd.h"
#include "RightStatusWnd.h"
#include "DaqControl.h"
#include "FileLogger.h"

class CDAQ_PanalView : public CFormView
{
protected: // create from serialization only
	CDAQ_PanalView();
	DECLARE_DYNCREATE(CDAQ_PanalView)

public:
	enum{ IDD = IDD_DAQ_PANAL_FORM };

// Attributes
public:
	CDAQ_PanalDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CDAQ_PanalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

private:
	CWaveCanvas m_waveCanvas;
	CAboveStatusWnd m_aboveStatusWnd;
	CBelowStatusWnd m_belowStatusWnd;
	CLeftStatusWnd m_leftStatusWnd;
	CRightStatusWnd m_rightStatusWnd;
	CRect m_rectPanal;
	CRect m_waveRect;
	CRect m_aboveWndRect;
	CRect m_belowWndRect;
	CRect m_leftWndRect;
	CRect m_rightWndRect;
	CDaqControl m_daqControl;
	int m_controlPanalWidth;

	void CreateWaveWnd();
	static UINT AquisitionThread(LPVOID pParam);                                    //采集数据线程
	void FetchWaveData();
	static UINT ScanThread(LPVOID pParam);                                          
	void FetchScanWaveData();
	static UINT DDRAquisitionThread(LPVOID pParam);                                    //DDR采集数据线程
	void FetchWaveDataInDDR();

	void MeasureParamForChannel();
	void GetCheckedDevice();
	void InitAcquisition();
	void AcquisitionStatus(ViInt32 *Status);
	void ResetAcquisition();
};

#ifndef _DEBUG  // debug version in DAQ_PanalView.cpp
inline CDAQ_PanalDoc* CDAQ_PanalView::GetDocument() const
   { return reinterpret_cast<CDAQ_PanalDoc*>(m_pDocument); }
#endif

