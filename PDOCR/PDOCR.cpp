// PDOCR.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PDOCR.h"
#include "PDOCRDlg.h"
#include <string>
#include <VersionHelpers.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPDOCRApp

BEGIN_MESSAGE_MAP(CPDOCRApp, CBCGPWinApp)
	ON_COMMAND(ID_HELP, CBCGPWinApp::OnHelp)
END_MESSAGE_MAP()


// CPDOCRApp construction

CPDOCRApp::CPDOCRApp()
{
	// Support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// Enable VS 2019 look (Blue theme)
	//SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2019_COLORFUL);

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPDOCRApp object

CPDOCRApp theApp;


// CPDOCRApp initialization

BOOL CPDOCRApp::InitInstance()
{
	//system("chcp 65001");
	this->m_hMutex = ::CreateMutexW(NULL, FALSE, this->m_pszAppName);//m_hMutex是新增的成员变量
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		::CloseHandle(m_hMutex);
		HWND hPre = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (::IsWindow(hPre))
		{
			if (::GetPropW(hPre, this->m_pszAppName))
			{
				::ShowWindow(hPre, SW_SHOWNORMAL);
				::SetForegroundWindow(hPre);
				::SetForegroundWindow(::GetLastActivePopup(hPre));
				return false;
			}
			hPre = ::GetWindow(hPre, GW_HWNDNEXT);
		}
	}


// TODO: 调用 AfxInitRichEdit2() 以初始化 richedit2 库。\n"	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	AfxInitRichEdit2();
	InitCommonControls();

	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
// 	IsWindows7OrGreater() ? SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)) :
// 		SetThreadLocale(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));


	CPDOCRDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.


	return FALSE;
}


int CPDOCRApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	::CloseHandle(this->m_hMutex);
	return CBCGPWinApp::ExitInstance();
}
