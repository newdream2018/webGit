// WaveCanvas.cpp : implementation file
//

#include "stdafx.h"
#include "DAQ_Panal.h"
#include "WaveCanvas.h"


// CWaveCanvas

IMPLEMENT_DYNAMIC(CWaveCanvas, CWnd)

CWaveCanvas::CWaveCanvas()
{
	m_crGridColor = CR_WHITE;
	m_crLineColor = CR_YELLOW;

	m_dXMaxValue = 500;
	m_dXMinValue = 0;
	m_dYMaxValue = 229.5;
	m_dYMinValue = 25.5; 

	m_pOldBitmapGrid = NULL;
	m_pOldBitmapLine = NULL;

	m_brushBack.CreateSolidBrush(CR_BLACK);
	m_penWhite.CreatePen(PS_SOLID, 1,m_crGridColor);
	m_singlePenCH1.CreatePen(PS_SOLID, 1, CR_YELLOW);//初始化画笔
	m_singlePenCH2.CreatePen(PS_SOLID, 1, CR_BLUE);	
	m_singlePenCH3.CreatePen(PS_SOLID, 1, CR_PINK);
	m_singlePenCH4.CreatePen(PS_SOLID, 1, CR_GREEN);
}

CWaveCanvas::~CWaveCanvas()
{
	m_brushBack.DeleteObject();
	m_penWhite.DeleteObject();
	m_singlePenCH1.DeleteObject();
	m_singlePenCH2.DeleteObject();
	m_singlePenCH3.DeleteObject();
	m_singlePenCH4.DeleteObject();
	//m_dcGrid.DeleteDC();
	//m_bitmapGrid.DeleteObject();
	//m_dcLine.DeleteDC();
	//m_bitmapLine.DeleteObject();
}


BEGIN_MESSAGE_MAP(CWaveCanvas, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CWaveCanvas message handlers

BOOL CWaveCanvas::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL result ;
	//注册窗体类
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;
	//创建窗体类
	result = CWnd::CreateEx(NULL, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	m_rcCanvas = CRect(rect);

	InitialDrawTools();
	InitialBackGround();
	return result;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CWaveCanvas::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	//InitialBackGround();
	dc.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),
		m_rcCanvas.Height(),&m_dcLine,0,0,SRCCOPY);
}

void CWaveCanvas::InitialDrawTools()
{
	CClientDC dc(this);

	//创建表格设备环境以及创建相应缓冲区
	if (m_dcGrid.GetSafeHdc() == NULL)
	{
		m_dcGrid.CreateCompatibleDC(&dc);
		m_bitmapGrid.CreateCompatibleBitmap(&dc,m_rcCanvas.Width(),m_rcCanvas.Height());
		m_pOldBitmapGrid = m_dcGrid.SelectObject(&m_bitmapGrid);
	}
	else
	{
		m_dcGrid.DeleteDC();
		m_bitmapGrid.DeleteObject();

		m_dcGrid.CreateCompatibleDC(&dc);
		m_bitmapGrid.CreateCompatibleBitmap(&dc,m_rcCanvas.Width(),m_rcCanvas.Height());
		m_pOldBitmapGrid = m_dcGrid.SelectObject(&m_bitmapGrid);
	}
	//创建画图设备环境以及创建相应缓冲区
	if (m_dcLine.GetSafeHdc() == NULL)
	{
		m_dcLine.CreateCompatibleDC(&dc);
		m_bitmapLine.CreateCompatibleBitmap(&dc,m_rcCanvas.Width(),m_rcCanvas.Height());
		m_pOldBitmapLine = m_dcLine.SelectObject(&m_bitmapLine);
	}
	else
	{
		m_dcLine.DeleteDC();
		m_bitmapLine.DeleteObject();

		m_dcLine.CreateCompatibleDC(&dc);
		m_bitmapLine.CreateCompatibleBitmap(&dc,m_rcCanvas.Width(),m_rcCanvas.Height());
		m_pOldBitmapLine = m_dcLine.SelectObject(&m_bitmapLine);
	}
}

void CWaveCanvas::InitialBackGround()
{	
	//中间填黑
	GetClientRect(m_rcCanvas);	
	m_dcGrid.FillRect(m_rcCanvas, &m_brushBack);

	//每格的宽度和高度
	int xCount = 10;
	int yCount = 8;
	int width = (int)((m_rcCanvas.Width())/xCount * 1.0);
	int height = (int)((m_rcCanvas.Height())/yCount * 1.0);
	m_width = width;
	m_height = height;

	//画网格边框
	m_oldPen = m_dcGrid.SelectObject(&m_penWhite);
	int left = m_rcCanvas.left;
	int top = m_rcCanvas.top;
	m_dcGrid.MoveTo(left, top);
	m_dcGrid.LineTo(left + xCount*width - 1, top);
	m_dcGrid.LineTo(left + xCount*width - 1, top + yCount*height - 1);
	m_dcGrid.LineTo(left, top + yCount*height - 1);
	m_dcGrid.LineTo(left, top);

	//画内部网格线
	m_oldPen = m_dcGrid.SelectObject(&m_penWhite);
	for (int i = 1; i<yCount; i++)
	{
		m_dcGrid.MoveTo(left, top + i*height);
		m_dcGrid.LineTo(left + xCount*width, top + i*height);
	}
	for (int j = 1; j<xCount; j++)
	{
		m_dcGrid.MoveTo(left + j*width, top);
		m_dcGrid.LineTo(left + j*width, top + yCount*height);
	}
	
	m_dcGrid.SelectObject(m_oldPen);
	//从背景DC拷贝图像到做图dc
	m_dcLine.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),m_rcCanvas.Height(),
		&m_dcGrid,0,0,SRCCOPY);
}

void CWaveCanvas::DrawWave()
{
	// 从背景DC拷贝图像到做图dc
	m_dcLine.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),m_rcCanvas.Height(),
		&m_dcGrid,0,0,SRCCOPY);

	if (g_deviceParam.Channel[0].Enabled)
	{
		for (int i = 0;i < 500*2;i++)
		{
			point1[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point1[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[0].MinData[i / 2] * 10*m_height / g_deviceParam.Channel[0].Range));
			}
			else
			{
				point1[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[0].MaxData[i / 2] * 10*m_height / g_deviceParam.Channel[0].Range));
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH1);
		CRgn rgn1;
		rgn1.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn1, RGN_AND);	
		Polyline(m_dcLine, point1, 500*2);
	}

	if (g_deviceParam.Channel[1].Enabled)
	{
		for (int i = 0;i < 500*2;i++)
		{
			point2[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point2[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.00 - g_deviceParam.DisplayData[1].MinData[i / 2] * 10*m_height / g_deviceParam.Channel[1].Range));
			}
			else
			{
				point2[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.00 - g_deviceParam.DisplayData[1].MaxData[i / 2] * 10*m_height / g_deviceParam.Channel[1].Range));
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH2);
		CRgn rgn2;
		rgn2.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn2, RGN_AND);	
		Polyline(m_dcLine, point2, 500*2);
	}

	if (g_deviceParam.Channel[2].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point3[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point3[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[2].MinData[i / 2] * 10*m_height / g_deviceParam.Channel[2].Range));
			}
			else
			{
				point3[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[2].MaxData[i / 2] * 10*m_height /g_deviceParam.Channel[2].Range));
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH3);
		CRgn rgn3;
		rgn3.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn3, RGN_AND);	
		Polyline(m_dcLine, point3, 500*2);
	}

	if (g_deviceParam.Channel[3].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point4[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point4[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[3].MinData[i / 2] * 10*m_height / g_deviceParam.Channel[3].Range));
			}
			else
			{
				point4[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (0.0 - g_deviceParam.DisplayData[3].MaxData[i / 2] * 10*m_height / g_deviceParam.Channel[3].Range));
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH4);
		CRgn rgn4;
		rgn4.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn4, RGN_AND);	
		Polyline(m_dcLine, point4, 500*2);
	}

	CClientDC dc(this);
	dc.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),m_rcCanvas.Height(), 
		&m_dcLine, 0, 0, SRCCOPY);
}

void CWaveCanvas::DrawScanWave()
{
	// 从背景DC拷贝图像到做图dc
	m_dcLine.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),m_rcCanvas.Height(),
		&m_dcGrid,0,0,SRCCOPY);

	if (g_deviceParam.Channel[0].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point1[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point1[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[0].ScanMinData[i / 2]) * 10*m_height / 255.0);
			}
			else
			{
				point1[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[0].ScanMaxData[i / 2]) * 10*m_height / 255.0);
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH1);
		CRgn rgn1;
		rgn1.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn1, RGN_AND);	
		Polyline(m_dcLine, point1, 500*2);
	}

	if (g_deviceParam.Channel[1].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point2[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point2[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[1].ScanMinData[i / 2]) * 10*m_height / 255.0);
			}
			else
			{
				point2[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[1].ScanMaxData[i / 2]) * 10*m_height / 255.0);
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH2);
		CRgn rgn2;
		rgn2.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn2, RGN_AND);	
		Polyline(m_dcLine, point2, 500*2);
	}

	if (g_deviceParam.Channel[2].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point3[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point3[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[2].ScanMinData[i / 2]) * 10*m_height / 255.0);
			}
			else
			{
				point3[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[2].ScanMaxData[i / 2]) * 10*m_height / 255.0);
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH3);
		CRgn rgn3;
		rgn3.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn3, RGN_AND);	
		Polyline(m_dcLine, point3, 500*2);
	}

	if (g_deviceParam.Channel[3].Enabled)
	{
		for (int i = 0;i < 500*2;++i)
		{
			point4[i].x =(LONG) (m_rcCanvas.left + ((m_width*i /50) / 2*1.0));

			if (0 == i % 2)
			{
				point4[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[3].ScanMinData[i / 2]) * 10*m_height / 255.0);
			}
			else
			{
				point4[i].y = (LONG)(m_rcCanvas.top + 4*m_height + (127.0 - g_deviceParam.DisplayData[3].ScanMaxData[i / 2]) * 10*m_height / 255.0);
			}
		}

		m_dcLine.SelectObject(&m_singlePenCH4);
		CRgn rgn4;
		rgn4.CreateRectRgn(m_rcCanvas.left, m_rcCanvas.top, m_rcCanvas.Width(),m_rcCanvas.Height());
		m_dcLine.SelectClipRgn(&rgn4, RGN_AND);	
		Polyline(m_dcLine, point4, 500*2);
	}

	CClientDC dc(this);
	dc.BitBlt(m_rcCanvas.left,m_rcCanvas.top,m_rcCanvas.Width(),m_rcCanvas.Height(), 
		&m_dcLine, 0, 0, SRCCOPY);
}