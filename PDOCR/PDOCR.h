// PDOCR.h : main header file for the PDOCR application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CPDOCRApp:
// See PDOCR.cpp for the implementation of this class
//

class CPDOCRApp : public CBCGPWinApp
{
public:
	CPDOCRApp();

// Overrides
public:
	virtual BOOL InitInstance();

	HANDLE m_hMutex;
// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CPDOCRApp theApp;
