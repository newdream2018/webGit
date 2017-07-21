#pragma once
#include "afxwin.h"
class CMyButton : public CButton
{
	//DECLARE_DYNAMIC(CMyButton)
public:
	CMyButton();
	virtual ~CMyButton();
	//设置Button Down的背景颜色
	void SetDownColor(COLORREF color);
	//设置Button Up的背景颜色
	void SetUpColor(COLORREF color);

	void SetTextColor(COLORREF color);

	BOOL Attach(const UINT nID, CWnd* pParent);

	//protected:
	//必需重载的函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ChangleColor(bool state,CWnd*pwnd);
public:
	//三种颜色分别为文字，Button Down的背景颜色，Button Up的背景颜色
	COLORREF m_TextColor, m_DownColor, m_UpColor;

};

//extern bool g_changle_color1;
//extern bool g_changle_color2;