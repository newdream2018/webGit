// BelowStatusWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DAQ_Panal.h"
#include "BelowStatusWnd.h"


// CBelowStatusWnd

IMPLEMENT_DYNAMIC(CBelowStatusWnd, CWnd)

CBelowStatusWnd::CBelowStatusWnd()
{
	m_brushBK.CreateSolidBrush(CR_BLACK);
}

CBelowStatusWnd::~CBelowStatusWnd()
{
	m_brushBK.DeleteObject();
}


BEGIN_MESSAGE_MAP(CBelowStatusWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CBelowStatusWnd message handlers




BOOL CBelowStatusWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL result ;
	m_rect = rect;
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = rect.right - rect.left;
	m_rect.bottom = rect.bottom - rect.top;
	//ע�ᴰ����
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;
	//����������
	result = CWnd::CreateEx(NULL, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	return result;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CBelowStatusWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting 
	dc.FillRect(&m_rect, &m_brushBK);
}
