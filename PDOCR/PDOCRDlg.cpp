// PDOCRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PDOCR.h"
#include "PDOCRDlg.h"
#include <string>
#include "RunOcr.hpp"
#include "UserData.h"
#include <vector>
#include <set>
#include "Path.h"
#include "Encoding.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SHOWTASK (WM_USER + 100)
#define ID_EXIT	(WM_USER + 101)
#define ID_MENU_OPEN	(WM_USER + 102)
#define ID_MENU_PASTE	(WM_USER + 103)
#define ID_MENU_SCREENCLIP (WM_USER + 104)
#define ID_MENU_FEEDBACK (WM_USER + 105)

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(IDD_ABOUTBOX)
{
	//EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CPDOCRDlg dialog


CPDOCRDlg::CPDOCRDlg(CWnd* pParent /*=NULL*/)
: CBCGPDialog(IDD_PDOCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//EnableVisualManagerStyle(TRUE, TRUE);
}

void CPDOCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREVIEW, m_wndPreview);
	DDX_Control(pDX, IDC_RICHEDIT21, m_wndEdit);
	DDX_Control(pDX, IDC_BTN_PASTE, m_btnPaste);
	DDX_Control(pDX, IDOK, m_btnOpen);
	DDX_Control(pDX, IDC_BTN_1_1, m_btn11);
	DDX_Control(pDX, IDC_BTN_SCREENCLIP, m_btnScreenclip);
	DDX_Control(pDX, IDC_COMBO1, m_cmbMode);
}

BEGIN_MESSAGE_MAP(CPDOCRDlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPDOCRDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PASTE, &CPDOCRDlg::OnBnClickedPaste)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SHOWTASK, &CPDOCRDlg::OnShowtask)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EXIT, &CPDOCRDlg::OnExit)
	ON_COMMAND(ID_MENU_OPEN, &CPDOCRDlg::OnBnClickedOk)
	ON_COMMAND(ID_MENU_PASTE, &CPDOCRDlg::OnBnClickedPaste)
	ON_COMMAND(ID_MENU_SCREENCLIP, &CPDOCRDlg::OnBnClickedBtnScreenclip)
	ON_COMMAND(ID_MENU_FEEDBACK, &CPDOCRDlg::OnFeedback)
	ON_BN_CLICKED(IDC_BTN_1_1, &CPDOCRDlg::OnBnClickedBtn11)
	ON_BN_CLICKED(IDC_BTN_SCREENCLIP, &CPDOCRDlg::OnBnClickedBtnScreenclip)
	ON_WM_DRAWCLIPBOARD()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPDOCRDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

void InitBtn(CBCGPButton &btn, LPCTSTR strPrompt, int pngId, int pngHotId)
{
	btn.SetImageAutoScale();
	btn.m_bTopImage = TRUE;
	btn.m_bDrawFocus = FALSE;
	btn.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_NOBORDERS;
	btn.m_bTransparent = TRUE;
	btn.SetTooltip(strPrompt);
	btn.SetImage(pngId, pngHotId);
	btn.Invalidate();
	btn.UpdateWindow();
}
// CPDOCRDlg message handlers

BOOL CPDOCRDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: add extra initialization here
	::SetPropW(this->m_hWnd, ::AfxGetAppName(), (HANDLE)1);

	m_wndPreview.setZoomMode(true);
	m_wndPreview.setPanMode(true);

	InitBtn(m_btnOpen, _T("选择图片OCR识别"), IDB_PNG_OPEN, IDB_PNG_OPEN_HOT);
	InitBtn(m_btnPaste, _T("粘贴图片OCR识别"), IDB_PNG_PASTE, IDB_PNG_PASTE_HOT);
	InitBtn(m_btnScreenclip, _T("屏幕截图OCR识别"), IDB_PNG_SCREENCLIP, IDB_PNG_SCREENCLIP_HOT);
	InitBtn(m_btn11, _T("图片原始大小"), IDB_PNG_1_1, IDB_PNG_1_1_hot);

	m_wndPreview.setSizeType(CImageCtrl::SIZE_SCALETOFIT);

	CRect rect;
	GetWindowRect(rect);
	int x = G_UserData.GetAt(_T("DLG_SIZE"), _T("x"), -1);
	int y = G_UserData.GetAt(_T("DLG_SIZE"), _T("y"), -1);
	int cx = G_UserData.GetAt(_T("DLG_SIZE"), _T("cx"), rect.Width());
	int cy = G_UserData.GetAt(_T("DLG_SIZE"), _T("cy"), rect.Height());
	if(x > 0)
		SetWindowPos(NULL, x, y, cx, cy, SWP_SHOWWINDOW);

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpyW(nid.szTip, _T("PDOCR"));//信息提示条 
	StrCpyW(nid.szInfo, _T("PDOCR"));//信息提示条 
	StrCpyW(nid.szInfoTitle, _T("PDOCR"));//信息提示条 
	
	Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标
	SetClipboardViewer();

	m_mapRecModes = { 
		{L"中英文、数字识别", L"ch_PP-OCRv3_rec_slim_infer"},
		{L"韩文识别", L"korean_PP-OCRv3_rec_infer"},
		{L"日文识别", L"japan_PP-OCRv3_rec_infer"},
		{L"中文繁体识别", L"chinese_cht_PP-OCRv3_rec_infer"},
		{L"泰卢固文识别", L"te_PP-OCRv3_rec_infer"},
		{L"卡纳达文识别", L"ka_PP-OCRv3_rec_infer"},
		{L"泰米尔文识别", L"ta_PP-OCRv3_rec_infer"},
		{L"拉丁文识别", L"latin_PP-OCRv3_rec_infer"},
		{L"阿拉伯字母", L"arabic_PP-OCRv3_rec_infer"},
		{L"斯拉夫字母", L"cyrillic_PP-OCRv3_rec_infer"},
		{L"梵文字母", L"devanagari_PP-OCRv3_rec_infer"}
	};

	m_mapRecChar = {
		{L"中英文、数字识别", L"ppocr_keys_v1.txt"},
		{L"韩文识别", L"korean_dict.txt"},
		{L"日文识别", L"japan_dict.txt"},
		{L"中文繁体识别", L"chinese_cht_dict.txt"},
		{L"泰卢固文识别", L"te_dict.txt"},
		{L"卡纳达文识别", L"ka_dict.txt"},
		{L"泰米尔文识别", L"ta_dict.txt"},
		{L"拉丁文识别", L"latin_dict.txt"},
		{L"阿拉伯字母", L"arabic_dict.txt"},
		{L"斯拉夫字母", L"cyrillic_dict.txt"},
		{L"梵文字母", L"devanagari_dict.txt"}
	};

	for (auto &it : m_mapRecModes)
	{
		m_cmbMode.AddString(it.first);
	}
	
	m_cmbMode.SetCurSel(m_cmbMode.FindString(0, L"中英文、数字识别"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPDOCRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPDOCRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBCGPDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPDOCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPDOCRDlg::OnExit()
{
	CBCGPDialog::OnCancel();
}

std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP)
{
	std::string str;
	int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char	*m_char = new char[len + 1];
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

void CPDOCRDlg::OnBnClickedOk()
{
	if (!this->IsWindowVisible())
	{
		ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
	}
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CString strFolder;
	CString strFilter = _T("Picture File(*.jpg; *.png; *.bmp)|*.jpg; *.png; *.bmp||");
	CFileDialog openFileDlg(TRUE, _T(".png"), strFolder, 6UL, strFilter, theApp.GetMainWnd());
	auto res = openFileDlg.DoModal();

	if (res != IDOK)
	{
		return;
	}

	BOOL bres = m_wndPreview.load(openFileDlg.GetPathName());
	if (!bres)
	{
		BCGPMessageBox(_T("LOAD IMAGE FAILED!"));
		return;
	}

	//OnBnClickedBtn11();

	m_strPath = openFileDlg.GetPathName();
	std::thread th(&CPDOCRDlg::Run, this, m_strPath);
	//Run(strPath);
	th.detach();
	
}

void CPDOCRDlg::Run(CString strPath)
{
	m_wndEdit.Clear();
	m_wndEdit.SetWindowText(_T("识别中，请稍后..."));

	CString strModel;
	m_cmbMode.GetWindowText(strModel);

	std::string imageDir = "--image_dir=" + WcharToChar(strPath);
	std::string recModelDir = "--rec_model_dir=.\\" + WcharToChar(m_mapRecModes[strModel]);
	std::string recCharDir = "--rec_char_dict_path=.\\dict\\" + WcharToChar(m_mapRecChar[strModel]);
	char* argv[6] = { "ppocr.exe",
		"system",
		"--det_model_dir=.\\ch_PP-OCRv3_det_slim_infer",
		const_cast<char*>(recModelDir.c_str()),
		const_cast<char*>(recCharDir.c_str()),
		const_cast<char*>(imageDir.c_str())
	};

	run(6, argv);

// 	CString strName = strPath.Right(strPath.GetLength() - strPath.ReverseFind('\\') - 1);
// 	strName = _T(".\\output\\") + strName;
// 	m_wndPreview.load(strName);
}

void CPDOCRDlg::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_wndPreview.isImageShown())
	{
		m_wndPreview.update();
	}
}

// bitmap 位图CBitmap对象指针
// lpFileName 为位图文件名  
bool SaveBitmapToFile(CBitmap* bitmap, LPCTSTR lpFileName)
{
	HBITMAP hBitmap;	// 为刚才的屏幕位图句柄
	HDC hDC; //设备描述表  
	int iBits; //当前显示分辨率下每个像素所占字节数  
	WORD wBitCount; //位图中每个像素所占字节数	
	DWORD dwPaletteSize = 0, //定义调色板大小
		dwBmBitsSize,  //位图中像素字节大小   
		dwDIBSize,	 //位图文件大小
		dwWritten;  //写入文件字节数
	BITMAP Bitmap; //位图属性结构  
	BITMAPFILEHEADER bmfHdr; //位图文件头结构  
	BITMAPINFOHEADER bi; //位图信息头结构    
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构  
	HANDLE fh,	 //定义文件
		hDib,	 //分配内存句柄
		hPal,	//调色板句柄
		hOldPal = NULL;

	//计算位图文件每个像素所占字节数  
	hBitmap = (HBITMAP)*bitmap;
	hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);

	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else if (iBits <= 32)
		wBitCount = 32;

	//计算调色板大小  
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//设置位图信息头结构  
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存  
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	// 处理调色板 	   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//	 获取该调色板下新的像素值  
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	//恢复调色板		
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//创建位图文件			
	fh = CreateFile(lpFileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	//	 设置位图文件头  
	bmfHdr.bfType = 0x4D42; 	//	 "BM"  
	dwDIBSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)
		+ (DWORD)sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize;

	//	 写入位图文件头  
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	//	 写入位图文件其余内容  
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize,
		&dwWritten, NULL);

	//清除		  
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return TRUE;
}

BOOL CPDOCRDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
// 	if (pMsg->message == WM_KEYDOWN && GetKeyState(VK_CONTROL) < 0)
// 	{
// 		switch (pMsg->wParam)
// 		{
// 		case 'v':
// 		case 'V':
// 			OnBnClickedPaste();
// 			return TRUE;
// 			break;
// 		case 'o':
// 		case 'O':
// 			OnBnClickedOk();
// 			return TRUE;
// 			break;
// 		}
// 	}

	return CBCGPDialog::PreTranslateMessage(pMsg);
}

BOOL IsPathExist(LPCTSTR szPath)
{
	int nRet = _taccess(szPath, 0);
	return 0 == nRet || EACCES == nRet;
}

CString GetNewTmpName()
{
	CString strDir = Path::GetAppTmpDir();
	CString strName = _T("TMP_FILE.png");
	CString strPath = Path::Combine(strDir, strName);
	
	int i = 1;
	while (IsPathExist(strPath))
	{
		strName.Format(_T("TMP_FILE%d.png"), i++);
		strPath = Path::Combine(strDir, strName);
	}

	return strPath;
}

void CPDOCRDlg::OnBnClickedPaste()
{
	if (!this->IsWindowVisible())
	{
		ShowWindow(SW_SHOWNORMAL);
	}
	// TODO: 在此添加控件通知处理程序代码
	if (OpenClipboard())
	{
		CString strPath;
		HDROP hDrop = (HDROP)GetClipboardData(CF_HDROP);
		TCHAR szFileName[MAX_PATH + 1] = { 0 };
		DragQueryFile(hDrop, 0, szFileName, MAX_PATH);
		strPath = szFileName;
		int nFind = strPath.ReverseFind('.');
		CString strSuffix = strPath.Right(strPath.GetLength() - nFind);
		std::set<CString> setFilter = { _T(".jpg"), _T(".png"), _T(".bmp") };

		if (setFilter.find(strSuffix) == setFilter.end())
		{
			strPath = "";
			//获得剪贴板数据
			HBITMAP handle = (HBITMAP)GetClipboardData(CF_BITMAP);
			if (!handle)
			{
				CloseClipboard();
				return;
			}
			CBitmap * bm = CBitmap::FromHandle(handle);
			strPath = GetNewTmpName();
			SaveBitmapToFile(bm, strPath);
			
		}

		CloseClipboard();

		if (strPath.IsEmpty())
		{
			return;
		}

		//Run(_T(".\\TMP_FILE.bmp"));
		m_wndPreview.load(strPath);
		std::thread th(&CPDOCRDlg::Run, this, strPath);
		th.detach();

		m_strPath = strPath;
	}
}


void CPDOCRDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetWindowRect(rect);
	G_UserData.SetAt(_T("DLG_SIZE"), _T("x"), rect.left);
	G_UserData.SetAt(_T("DLG_SIZE"), _T("y"), rect.top);
	G_UserData.SetAt(_T("DLG_SIZE"), _T("cx"), rect.Width());
	G_UserData.SetAt(_T("DLG_SIZE"), _T("cy"), rect.Height());

	ShowWindow(SW_HIDE);
}


afx_msg LRESULT CPDOCRDlg::OnShowtask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
	{
		return   1;
	}
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单
	{
		LPPOINT   lpoint = new   tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置 
		CMenu   menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单 
 		menu.AppendMenu(MF_STRING, ID_MENU_OPEN, _T("选择图片OCR识别"));
		menu.AppendMenu(MF_STRING, ID_MENU_PASTE, _T("粘贴图片OCR识别"));
		menu.AppendMenu(MF_STRING, ID_MENU_SCREENCLIP, _T("屏幕截图OCR识别"));
		menu.AppendMenu(MF_STRING, ID_MENU_FEEDBACK, _T("意见反馈"));
		menu.AppendMenu(MF_STRING, ID_EXIT, _T("退出")); //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏）将程序结束。 
		SetForegroundWindow();
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //确定弹出式菜单的位置
		HMENU   hmenu = menu.Detach();  //资源回收 
		menu.DestroyMenu();
		delete   lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		this->ShowWindow(SW_SHOWNORMAL);
		TRACE0("WM_LBUTTONDBLCLK");
	}
	break;
	case  WM_LBUTTONDOWN:
		this->ShowWindow(SW_SHOWNORMAL);
		TRACE0("WM_LBUTTONDOWN");
		break;
	}

	return 0;
}



void CPDOCRDlg::DisplayOcrRes(const std::string &str)
{
// 	m_wndEdit.Clear();
// 	std::wstring strRes = string2wstring(UTF8ToANSI(str));
// 	BCGPMessageBox(strRes.c_str());
// 	m_wndEdit.SetWindowText(string2wstring(UTF8ToANSI(str)).c_str());
// 	return;
// 
// 	CString strModel;
// 	m_cmbMode.GetWindowText(strModel);
// 	if (strModel == L"中英文、数字识别")
// 	{
// 		m_wndEdit.SetWindowText(string2wstring(UTF8ToANSI(str)).c_str());
// 	}
// 	else
// 	{
// 		m_wndEdit.SetWindowText(CString(string2wstring(str).c_str()));
// 	}
}

void CPDOCRDlg::OnDestroy()
{
	CBCGPDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &nid);
	::RemovePropW(this->m_hWnd, ::AfxGetAppName());
}


void CPDOCRDlg::OnBnClickedBtn11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wndPreview.setSizeType(CImageCtrl::SIZE_ORIGINAL);
	m_wndPreview.update();
	m_wndPreview.setSizeType(CImageCtrl::SIZE_SCALETOFIT);
}


void CPDOCRDlg::OnBnClickedBtnScreenclip()
{
	// TODO: 在此添加控件通知处理程序代码	
	ShowWindow(SW_HIDE);
	m_bScreenclip = TRUE;
	ShellExecute(NULL, _T("open"), _T("ms-screenclip:screenclip"), _T(""), NULL, 0);

}


void CPDOCRDlg::OnFeedback()
{
	ShellExecute(0, 0, _T("https://www.progdomain.com/PDOCR/"), 0, 0, 0);
}

void CPDOCRDlg::OnDrawClipboard()
{
	CBCGPDialog::OnDrawClipboard();

	// TODO: 在此处添加消息处理程序代码
	if (m_bScreenclip)
	{
		m_bScreenclip = FALSE;
		Sleep(200);
		OnBnClickedPaste();
	}
}


void CPDOCRDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strPath.IsEmpty())
	{
		return;
	}

	std::thread th(&CPDOCRDlg::Run, this, m_strPath);
	//Run(strPath);
	th.detach();
}
