// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyButton.h"


bool g_changle_color1=false;
bool g_changle_color2=false;

CMyButton::CMyButton(void)
{
	m_DownColor = m_UpColor = RGB(0,0,0);
}
CMyButton::~CMyButton(void)
{
}

//CMyButton是CButton派生类，具有CButton的全部成员函数，
//但在创建时需要使用BS_OWNERDRAW风格。
//如果按钮不是动态生成，使用Attach函数使CMyButton代替原来按钮的窗口过程。
BOOL CMyButton::Attach(const UINT nID, CWnd* pParent)
{
	//GetDlgItem(nID)->ModifyStyle(0,BS_OWNERDRAW,0);
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;
	return TRUE;
}
void CMyButton::SetDownColor(COLORREF color)
{
	m_DownColor = color;
}
void CMyButton::SetUpColor(COLORREF color)
{
	m_UpColor = color;
}

void CMyButton::SetTextColor(COLORREF color)
{
	m_TextColor=color;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//得到绘制的设备环境CDC
	VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

	// 得当Button上文字,这里的步骤是:1,先得到在资源里编辑的按钮的文字,
	//然后将此文字重新绘制到按钮上,
	//同时将此文字的背景色设为透明,这样,按钮上仅会显示文字
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	CString tempt(buffer);

	//int size=strlen(buffer);   //得到长度
	int size=tempt.GetLength();

	DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //绘制文字
	dc.SetTextColor(m_TextColor);
	SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);   //透明

	//if (lpDrawItemStruct->itemState &ODS_SELECTED)  //当按下按钮时的处理
	if(lpDrawItemStruct->itemState &ODS_SELECTED)
	{//
		//重绘整个控制
		CBrush brush(m_DownColor);  
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//因为这里进行了重绘,所以文字也要重绘
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);      
	}
	else                       //当按钮不操作或者弹起时
	{
		CBrush brush(m_UpColor);     
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//同上,进行重绘文字
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);    
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
	}

	if ((lpDrawItemStruct->itemState &ODS_SELECTED)&&(lpDrawItemStruct->itemAction &(ODA_SELECT| ODA_DRAWENTIRE)))
	{   //选中了本控件,高亮边框
		//COLORREF fc=RGB(255-GetRValue(m_UpColor),255-GetGValue(m_UpColor), 255- GetBValue(m_UpColor));//
		//CBrush brush(fc);//
		//dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);//

		//绘制按钮背景



		//CRect Rect;
		//Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+1, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom );
		//dc.DrawEdge( &Rect, BDR_RAISEDINNER, BF_RECT );    //画边框

		CRect Rect;
		Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
	    dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框
		Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
		dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框
	}
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//控制的选中状态结束,去掉边框
		//CBrush brush(m_UpColor);
		//dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);//

		//CRect Rect;
		//Rect.SetRect( lpDrawItemStruct->rcItem.left+3, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-3, lpDrawItemStruct->rcItem.bottom-2 );
		//dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框
	}

	//CBrush Brush;
	//Brush.CreateSolidBrush( m_UpColor );    //背景刷
	//dc.SelectObject( &Brush );
	//CPen Pen;
	//Pen.CreatePen(PS_SOLID, 1, m_TextColor );
	//dc.SelectObject( &Pen );
	//dc.RoundRect(&lpDrawItemStruct->rcItem,CPoint(5,5));   //画圆角矩形

	CRect Rect;
	//Rect.SetRect( lpDrawItemStruct->rcItem.left+4, lpDrawItemStruct->rcItem.top+4, lpDrawItemStruct->rcItem.right-4, lpDrawItemStruct->rcItem.bottom-4 );
	//dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框

	//Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
	//dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框

	//Rect.SetRect( lpDrawItemStruct->rcItem.left+1, lpDrawItemStruct->rcItem.top+1, lpDrawItemStruct->rcItem.right-1, lpDrawItemStruct->rcItem.bottom-1 );
	//dc.DrawFocusRect( &Rect );    //画拥有焦点的虚线框

	dc.Detach();//
}

void CMyButton::ChangleColor(bool state,CWnd*pwnd)
{
	//得当Button上文字,这里的步骤是:1,先得到在资源里编辑的按钮的文字,
	//然后将此文字重新绘制到按钮上,
	//同时将此文字的背景色设为透明,这样,按钮上仅会显示文字

	CDC *dc=pwnd->GetDC();
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	CString tempt(buffer);

	//得到长度
	int size = tempt.GetLength();
	CRect rect;
	pwnd->GetClientRect(rect);

	//DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //绘制文字
	//dc->SetTextColor(m_TextColor);
	//SetBkMode((HDC)(*dc),TRANSPARENT);//透明

	if(state)
	{
		//重绘整个控制
		CBrush brush(m_DownColor);  
		dc->FillRect(rect,&brush);
		//因为这里进行了重绘,所以文字也要重绘
/*		DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP); 
		dc->SetTextColor(m_TextColor);
		SetBkMode(*dc,TRANSPARENT); */     
	}
	else //当按钮不操作或者弹起时
	{
		//重绘整个控制
		CBrush brush(m_UpColor);  
		dc->FillRect(rect,&brush);//
		////因为这里进行了重绘,所以文字也要重绘
		//DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP); 
		//dc->SetTextColor(m_TextColor);
		//SetBkMode(*dc,TRANSPARENT);  
	}
}