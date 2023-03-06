#pragma once

class Path
{
public:
	static CString GetAppDir();
	static CString GetAppdataDir();
	static CString GetAppTmpDir();

	static CString GetModuleFilePath(HINSTANCE hInstance);

	static void SplitPath(LPCTSTR szPath, CString& strDrive, CString& strDir = CString(), CString& strFname = CString(), CString& strExt = CString());

	static CString Combine(LPCTSTR szPath1, LPCTSTR szPath2);
};
