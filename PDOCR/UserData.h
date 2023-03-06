#pragma once

/// <summary>
/// 用户数据，放置在安装目录和%appdata%目录下
/// </summary>
class CUserData
{
	CUserData();

public:
	static CUserData& instance();
public:
	/// <summary>
	/// 读取用户数据
	/// 数据格式为ini文件
	/// [Section]
	/// Name=Value

	/// </summary>
	/// <param name="szSection">节点</param>
	/// <param name="szName">值名称</param>
	/// <param name="szDefault">默认值</param>
	/// <returns>返回读取到的值，如果读取不到，则得到默认值</returns>
	CString GetAt(LPCTSTR szSection, LPCTSTR szName, LPCTSTR szDefault = nullptr) const;
	int GetAt(LPCTSTR szSection, LPCTSTR szName, int nDefault) const;
	double GetAt(LPCTSTR szSection, LPCTSTR szName, double fDefault) const;

	void SetAt(LPCTSTR szSection, LPCTSTR szName, LPCTSTR szValue);
	void SetAt(LPCTSTR szSection, LPCTSTR szName, int value);
	void SetAt(LPCTSTR szSection, LPCTSTR szName, double value);

private:
	
	CString GetIniValue(LPCTSTR section, LPCTSTR valueName, LPCTSTR sz_default) const;

	void SetIniValue(LPCTSTR section, LPCTSTR valueName, LPCTSTR value);

private:
	CString m_strConfigFile;	// 安装目录路径
	CString m_strAppdataFile;	// 放置在appdata目录下
};

/// <summary>
/// 用户数据使用接口
/// 使用方法为 
/// 1. 读取：
/// double fDiameter = G_UserData.GetAt(_T("Circle"), _T("Diameter"), 20.0);
/// 2. 写入
/// G_UserData.SetAt(_T("Circle"), _T("Diameter"), 20.0);
/// 
/// </summary>
#define G_UserData (CUserData::instance())
