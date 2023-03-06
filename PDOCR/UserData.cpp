#include "StdAfx.h"
#include "UserData.h"
#include "Path.h"

CUserData::CUserData()
	: m_strConfigFile(Path::Combine(Path::GetAppDir(), _T("softData.ini")))
, m_strAppdataFile(Path::Combine(Path::GetAppdataDir(), _T("userData.ini")))
{
	
}

CUserData& CUserData::instance()
{
	static CUserData inst;
	return inst;
}

CString CUserData::GetAt(LPCTSTR szSection, LPCTSTR szName, LPCTSTR szDefault) const
{
	return GetIniValue(szSection, szName, szDefault);
}

int CUserData::GetAt(LPCTSTR szSection, LPCTSTR szName, int nDefault) const
{
	TCHAR sz[10];
	_itot_s(nDefault, sz, 10);
	const auto result = GetIniValue(szSection, szName, sz);
	return _ttoi(result);
}

double CUserData::GetAt(LPCTSTR szSection, LPCTSTR szName, double fDefault) const
{
	CString strDefault;
	strDefault.Format(_T("%G"), fDefault);

	const auto result = GetIniValue(szSection, szName, strDefault);
	return _ttof(result);
}

void CUserData::SetAt(LPCTSTR szSection, LPCTSTR szName, LPCTSTR szValue)
{
	SetIniValue(szSection, szName, szValue);
}

void CUserData::SetAt(LPCTSTR szSection, LPCTSTR szName, int value)
{
	TCHAR sz[10];
	_itot_s(value, sz, 10);
	SetIniValue(szSection, szName, sz);
}

void CUserData::SetAt(LPCTSTR szSection, LPCTSTR szName, double value)
{
	CString strValue;
	strValue.Format(_T("%G"), value);
	SetIniValue(szSection, szName, strValue);
}

CString CUserData::GetIniValue(LPCTSTR section, LPCTSTR valueName, LPCTSTR sz_default) const
{
	CString value;
	auto dwRs = ::GetPrivateProfileString(section, valueName, sz_default, value.GetBuffer(256), 256, m_strAppdataFile);
	value.ReleaseBuffer();
	if (0x2 != GetLastError())
	{
		// 成功
		return value;
	}

	dwRs = ::GetPrivateProfileString(section, valueName, sz_default, value.GetBuffer(256), 256, m_strConfigFile);
	value.ReleaseBuffer();
	if (0x2 != GetLastError())
	{
		// 
		return value;
	}

	return value = sz_default;
}

void CUserData::SetIniValue(LPCTSTR section, LPCTSTR valueName, LPCTSTR value)
{
	::WritePrivateProfileString(section, valueName, value, m_strAppdataFile);
}
