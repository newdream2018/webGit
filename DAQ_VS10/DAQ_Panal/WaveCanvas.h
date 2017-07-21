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
	void InitialDrawTools();                                                   //��ʼ����ͼ����      
	void InitialBackGround();                                                  //��ʼ������
	void DrawWave();                                                           // ��ͼ
	void DrawScanWave();

private:
	//�����߿��豸����
	CRect m_rcCanvas;                                                          //��ͼ���ľ������
	CBrush m_brushBack;                                                        //������ˢ
	CDC m_dcGrid;	                                                           //���߿��豸����DC
	CBitmap m_bitmapGrid ;                                                     //���߿��豸��������λͼ
	CBitmap *m_pOldBitmapGrid;

	//�������ߵ��豸����
	CDC m_dcLine;  	                                                           //�����豸DC
	CBitmap m_bitmapLine;                                                      //�����豸��������λͼ
	CBitmap *m_pOldBitmapLine;	

	COLORREF m_crGridColor;                                                    //���߿���ɫ:��ɫ
	COLORREF m_crLineColor;                                                    //ͨ��������ɫ:��ɫ
	COLORREF m_crLine1Color;                                                   //1ͨ��������ɫ:��ɫ
	COLORREF m_crLine2Color;                                                   //2ͨ��������ɫ:��ɫ

	double m_dXMaxValue ;                                                      //X�����ֵ
	double m_dXMinValue ;                                                      //X����Сֵ
	double m_dYMaxValue ;                                                      //Y�����ֵ
	double m_dYMinValue ;                                                      //Y����Сֵ

	CPen *m_oldPen; 
	CPen m_penWhite;                                                           //������ͼ����ı��߻���
	CPen m_singlePenCH1;                                                       //ͨ��1���λ���ʱ����
	CPen m_singlePenCH2;                                                       //ͨ��2���λ���ʱ����
	CPen m_singlePenCH3;                                                       //ͨ��1���λ���ʱ����
	CPen m_singlePenCH4;                                                       //ͨ��2���λ���ʱ����

	int m_width;
	int m_height;
	CPoint point1[1000];                                                       //ͨ��1��Ҫ��ʾ��1400���������
	CPoint point2[1000];                                                       //ͨ��2��Ҫ��ʾ��1400���������
	CPoint point3[1000];                                                       //ͨ��1��Ҫ��ʾ��1400���������
	CPoint point4[1000];                                                       //ͨ��2��Ҫ��ʾ��1400���������
};


