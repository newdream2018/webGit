#pragma once
#include "afxwin.h"
#include "Global.h"

// CDataChoose dialog

class CDataChoose : public CDialog
{
	DECLARE_DYNAMIC(CDataChoose)

public:
	CDataChoose(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataChoose();

// Dialog Data
	enum { IDD = IDD_DATA_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedOk();
	CListBox m_listDevice;

public:
	void LoadDevice();
	int m_showChannel;// 主界面显示通道（0,1,2,3）
	int m_actualChannel; // 设备的时基通道（0,1）
	afx_msg void OnBnClickedRadioChooseCh1();
	afx_msg void OnBnClickedRadioChooseCh2();

	HWND m_hViewWnd;
};
