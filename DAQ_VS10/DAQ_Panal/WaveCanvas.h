#pragma once
#include "Global.h"

// CWaveCanvas

class CWaveCanvas : public CWnd
{
	DECLARE_DYNAMIC(CWaveCanvas)

public:
	CWaveCanvas();
	virtual ~CWaveCanvas();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnPaint();

public:
	void InitialDrawTools();                                                   //初始化画图工具      
	void InitialBackGround();                                                  //初始化背景
	void DrawWave();                                                           // 画图
	void DrawScanWave();

private:
	//画表格边框设备环境
	CRect m_rcCanvas;                                                          //绘图区的矩形面积
	CBrush m_brushBack;                                                        //背景画刷
	CDC m_dcGrid;	                                                           //表格边框设备环境DC
	CBitmap m_bitmapGrid ;                                                     //表格边框设备环境缓冲位图
	CBitmap *m_pOldBitmapGrid;

	//用来画线的设备环境
	CDC m_dcLine;  	                                                           //画线设备DC
	CBitmap m_bitmapLine;                                                      //画线设备环境缓冲位图
	CBitmap *m_pOldBitmapLine;	

	COLORREF m_crGridColor;                                                    //表格边框颜色:白色
	COLORREF m_crLineColor;                                                    //通道曲线颜色:黄色
	COLORREF m_crLine1Color;                                                   //1通道曲线颜色:黄色
	COLORREF m_crLine2Color;                                                   //2通道曲线颜色:青色

	double m_dXMaxValue ;                                                      //X轴最大值
	double m_dXMinValue ;                                                      //X轴最小值
	double m_dYMaxValue ;                                                      //Y轴最大值
	double m_dYMinValue ;                                                      //Y轴最小值

	CPen *m_oldPen; 
	CPen m_penWhite;                                                           //绘制作图区域的边线画笔
	CPen m_singlePenCH1;                                                       //通道1波形绘制时画笔
	CPen m_singlePenCH2;                                                       //通道2波形绘制时画笔
	CPen m_singlePenCH3;                                                       //通道1波形绘制时画笔
	CPen m_singlePenCH4;                                                       //通道2波形绘制时画笔

	int m_width;
	int m_height;
	CPoint point1[1000];                                                       //通道1的要显示的1400个点的坐标
	CPoint point2[1000];                                                       //通道2的要显示的1400个点的坐标
	CPoint point3[1000];                                                       //通道1的要显示的1400个点的坐标
	CPoint point4[1000];                                                       //通道2的要显示的1400个点的坐标
};


