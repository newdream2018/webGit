#pragma once


// CLeftStatusWnd

class CLeftStatusWnd : public CWnd
{
	DECLARE_DYNAMIC(CLeftStatusWnd)

public:
	CLeftStatusWnd();
	virtual ~CLeftStatusWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnPaint();

public:
	CRect m_rect;                                                          //上面状态作图区域的矩形区
	CBrush m_brushBK;                                                      //背景画刷
};


