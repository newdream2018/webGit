
// DAQ_Panal.h : main header file for the DAQ_Panal application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDAQ_PanalApp:
// See DAQ_Panal.cpp for the implementation of this class
//

class CDAQ_PanalApp : public CWinAppEx
{
public:
	CDAQ_PanalApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDAQ_PanalApp theApp;
