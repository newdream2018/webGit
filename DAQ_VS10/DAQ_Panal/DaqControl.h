#pragma once
#include "MyButton.h"
#include "DataChoose.h"
#include "Global.h"
#include "WaveCanvas.h"
#include "afxwin.h"
// CDaqControl dialog

class CDaqControl : public CDialog
{
	DECLARE_DYNAMIC(CDaqControl)

public:
	CDaqControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDaqControl();

// Dialog Data
	enum { IDD = IDD_DAQ_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

private:
	CMyButton m_ch1Button;
	CMyButton m_ch2Button;
	CMyButton m_ch3Button;
	CMyButton m_ch4Button;
	CBrush m_brush;
	CDataChoose m_dataChoose;
public:
	afx_msg void OnClickedBtnCh1();
	afx_msg void OnBnClickedBtnCh2();
	afx_msg void OnBnClickedBtnCh3();
	afx_msg void OnBnClickedBtnCh4();
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedCheckCh1();
	afx_msg void OnClickedCheckCh2();
	afx_msg void OnClickedCheckCh3();
	afx_msg void OnClickedCheckCh4();
	afx_msg void OnBnClickedBtnDaq();
	afx_msg void OnBnClickedBtnScan();
	LRESULT OnDeviceChanged(WPARAM wParam, LPARAM lParam);
	LRESULT UpdataMeasureResults(WPARAM wParam, LPARAM lParam);

	CButton m_chkCh1Enabled;
	CButton m_chkCh2Enabled;
	CButton m_chkCh3Enabled;
	CButton m_chkCh4Enabled;
	CStatic m_staticCh1Msg;
	CStatic m_staticCh2Msg;
	CStatic m_staticCh3Msg;
	CStatic m_staticCh4Msg;
	CButton m_btnDaq;
	

	PVOID m_pView;
	bool m_IsFirstUpDate;
	DWORD m_updateMeasurementTickCount1;
	DWORD m_updateMeasurementTickCount2;
	double GetChannelRange(int index);
	void UpdateResults();
	void VoltageValueToString(double voltageValue, CString *strValue);
	void TimeValueToString(double timeValue, CString *strValue);
	void FreqValueToString(double freqValue, CString *strValue);
	void PercentageValueToString(double percentageValue, CString *strValue);

	CListBox m_listMeasResults;
	CComboBox m_cboMemoryDepth;
	CComboBox m_cboHoriTimeBase;
	CComboBox m_cboTrigType;
	CComboBox m_cboTrigMode;
	CString m_strTrigLevel;
	CEdit m_editCh1Volt;
	CEdit m_editCh2Volt;
	CEdit m_editCh3Volt;
	CEdit m_editCh4Volt;
	CString m_strCh1Volt;
	CString m_strCh2Volt;
	CString m_strCh3Volt;
	CString m_strCh4Volt;
	afx_msg void OnDeltaposSpinCh1Volt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCh2Volt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCh3Volt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCh4Volt(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cboTrigCondition;
	afx_msg void OnBnClickedBtnDdrAcq();
	CButton m_btnDDRAcq;
	afx_msg void OnCbnSelchangeComboMemoryDepth();
};
