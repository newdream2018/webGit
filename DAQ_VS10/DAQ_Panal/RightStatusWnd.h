#pragma once


// CRightStatusWnd

class CRightStatusWnd : public CWnd
{
	DECLARE_DYNAMIC(CRightStatusWnd)

public:
	CRightStatusWnd();
	virtual ~CRightStatusWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnPaint();
public:
	CRect m_rect;                                                          //����״̬��ͼ����ľ�����
	CBrush m_brushBK;                                                      //������ˢ
};


