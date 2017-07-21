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

//CMyButton��CButton�����࣬����CButton��ȫ����Ա������
//���ڴ���ʱ��Ҫʹ��BS_OWNERDRAW���
//�����ť���Ƕ�̬���ɣ�ʹ��Attach����ʹCMyButton����ԭ����ť�Ĵ��ڹ��̡�
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
	dc.Attach(lpDrawItemStruct->hDC);//�õ����Ƶ��豸����CDC
	VERIFY(lpDrawItemStruct->CtlType==ODT_BUTTON);

	// �õ�Button������,����Ĳ�����:1,�ȵõ�����Դ��༭�İ�ť������,
	//Ȼ�󽫴��������»��Ƶ���ť��,
	//ͬʱ�������ֵı���ɫ��Ϊ͸��,����,��ť�Ͻ�����ʾ����
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	CString tempt(buffer);

	//int size=strlen(buffer);   //�õ�����
	int size=tempt.GetLength();

	DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //��������
	dc.SetTextColor(m_TextColor);
	SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);   //͸��

	//if (lpDrawItemStruct->itemState &ODS_SELECTED)  //�����°�ťʱ�Ĵ���
	if(lpDrawItemStruct->itemState &ODS_SELECTED)
	{//
		//�ػ���������
		CBrush brush(m_DownColor);  
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//��Ϊ����������ػ�,��������ҲҪ�ػ�
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);      
	}
	else                       //����ť���������ߵ���ʱ
	{
		CBrush brush(m_UpColor);     
		dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);//
		//ͬ��,�����ػ�����
		DrawText(lpDrawItemStruct->hDC,buffer,size,&lpDrawItemStruct->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);    
		SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT);
	}

	if ((lpDrawItemStruct->itemState &ODS_SELECTED)&&(lpDrawItemStruct->itemAction &(ODA_SELECT| ODA_DRAWENTIRE)))
	{   //ѡ���˱��ؼ�,�����߿�
		//COLORREF fc=RGB(255-GetRValue(m_UpColor),255-GetGValue(m_UpColor), 255- GetBValue(m_UpColor));//
		//CBrush brush(fc);//
		//dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);//

		//���ư�ť����



		//CRect Rect;
		//Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+1, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom );
		//dc.DrawEdge( &Rect, BDR_RAISEDINNER, BF_RECT );    //���߿�

		CRect Rect;
		Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
	    dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�
		Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
		dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�
	}
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//���Ƶ�ѡ��״̬����,ȥ���߿�
		//CBrush brush(m_UpColor);
		//dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);//

		//CRect Rect;
		//Rect.SetRect( lpDrawItemStruct->rcItem.left+3, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-3, lpDrawItemStruct->rcItem.bottom-2 );
		//dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�
	}

	//CBrush Brush;
	//Brush.CreateSolidBrush( m_UpColor );    //����ˢ
	//dc.SelectObject( &Brush );
	//CPen Pen;
	//Pen.CreatePen(PS_SOLID, 1, m_TextColor );
	//dc.SelectObject( &Pen );
	//dc.RoundRect(&lpDrawItemStruct->rcItem,CPoint(5,5));   //��Բ�Ǿ���

	CRect Rect;
	//Rect.SetRect( lpDrawItemStruct->rcItem.left+4, lpDrawItemStruct->rcItem.top+4, lpDrawItemStruct->rcItem.right-4, lpDrawItemStruct->rcItem.bottom-4 );
	//dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�

	//Rect.SetRect( lpDrawItemStruct->rcItem.left+2, lpDrawItemStruct->rcItem.top+2, lpDrawItemStruct->rcItem.right-2, lpDrawItemStruct->rcItem.bottom-2 );
	//dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�

	//Rect.SetRect( lpDrawItemStruct->rcItem.left+1, lpDrawItemStruct->rcItem.top+1, lpDrawItemStruct->rcItem.right-1, lpDrawItemStruct->rcItem.bottom-1 );
	//dc.DrawFocusRect( &Rect );    //��ӵ�н�������߿�

	dc.Detach();//
}

void CMyButton::ChangleColor(bool state,CWnd*pwnd)
{
	//�õ�Button������,����Ĳ�����:1,�ȵõ�����Դ��༭�İ�ť������,
	//Ȼ�󽫴��������»��Ƶ���ť��,
	//ͬʱ�������ֵı���ɫ��Ϊ͸��,����,��ť�Ͻ�����ʾ����

	CDC *dc=pwnd->GetDC();
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	CString tempt(buffer);

	//�õ�����
	int size = tempt.GetLength();
	CRect rect;
	pwnd->GetClientRect(rect);

	//DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP);   //��������
	//dc->SetTextColor(m_TextColor);
	//SetBkMode((HDC)(*dc),TRANSPARENT);//͸��

	if(state)
	{
		//�ػ���������
		CBrush brush(m_DownColor);  
		dc->FillRect(rect,&brush);
		//��Ϊ����������ػ�,��������ҲҪ�ػ�
/*		DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP); 
		dc->SetTextColor(m_TextColor);
		SetBkMode(*dc,TRANSPARENT); */     
	}
	else //����ť���������ߵ���ʱ
	{
		//�ػ���������
		CBrush brush(m_UpColor);  
		dc->FillRect(rect,&brush);//
		////��Ϊ����������ػ�,��������ҲҪ�ػ�
		//DrawText(*dc,buffer,size,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_TABSTOP); 
		//dc->SetTextColor(m_TextColor);
		//SetBkMode(*dc,TRANSPARENT);  
	}
}