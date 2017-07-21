// RightStatusWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DAQ_Panal.h"
#include "RightStatusWnd.h"


// CRightStatusWnd

IMPLEMENT_DYNAMIC(CRightStatusWnd, CWnd)

CRightStatusWnd::CRightStatusWnd()
{
	m_brushBK.CreateSolidBrush(CR_BLACK);
}

CRightStatusWnd::~CRightStatusWnd()
{
	m_brushBK.DeleteObject();
}


BEGIN_MESSAGE_MAP(CRightStatusWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CRightStatusWnd message handlers




BOOL CRightStatusWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL result ;
	m_rect = rect;
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = rect.right - rect.left;
	m_rect.bottom = rect.bottom - rect.top;
	//注册窗体类
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;
	//创建窗体类
	result = CWnd::CreateEx(NULL, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	return result;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CRightStatusWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	dc.FillRect(&m_rect, &m_brushBK);
}
