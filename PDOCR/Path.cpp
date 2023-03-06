#include "stdafx.h"
#include "Path.h"
#include "String.h"

CString Path::GetAppDir()
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString strDir = szFilePath;
	int nLast = strDir.ReverseFind('\\');
	strDir = strDir.Left(nLast);//Dir为exe文件的绝对路径
	return strDir;
}

//用户信息目录
CString Path::GetAppdataDir()
{
	TCHAR szPath[_MAX_PATH];
	::SHGetSpecialFolderPath(nullptr, szPath, CSIDL_APPDATA, TRUE);
	TCHAR szDir[MAX_PATH];
	PathCombine(szDir, szPath, _T("PDOCR\\"));
	::CreateDirectory(szDir, nullptr);

	PathCombine(szDir, szDir, _T("Datas"));
	::CreateDirectory(szDir, nullptr);
	CString strDir = szDir;
	return strDir;
}

CString Path::GetAppTmpDir()
{
	TCHAR strTmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, strTmpPath);
	::CreateDirectory(strTmpPath + CString("PDOCR\\"), nullptr);
	return strTmpPath + CString("PDOCR\\");
}


CString Path::GetModuleFilePath(HINSTANCE hInstance)
{
	if (nullptr == hInstance)
	{
		hInstance = AfxGetInstanceHandle();
	}

	CString strPath;
	::AfxGetModuleFileName(hInstance, strPath);
	return strPath;
}

void Path::SplitPath(LPCTSTR szPath, CString& strDrive, CString& strDir, CString& strFname, CString& strExt)
{
	_tsplitpath_s(szPath,
		strDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE,
		strDir.GetBuffer(_MAX_DIR), _MAX_DIR,
		strFname.GetBuffer(_MAX_FNAME), _MAX_FNAME,
		strExt.GetBuffer(_MAX_EXT), _MAX_EXT);

	strDrive.ReleaseBuffer();
	strDir.ReleaseBuffer();
	strFname.ReleaseBuffer();
	strExt.ReleaseBuffer();
}

CString Path::Combine(LPCTSTR szPath1, LPCTSTR szPath2)
{
	TCHAR szPath[MAX_PATH];
	PathCombine(szPath, szPath1, szPath2);
	CString strPath = szPath;
	return strPath;
}
