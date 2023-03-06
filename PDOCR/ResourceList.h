#pragma once
#include "stdAfx.h"

struct tResourceName
{
	tResourceName(bool _isInteger, CString _name) { isInteger = _isInteger; name = _name; }

	bool isInteger;
	CString name;
};

struct tResourceType
{
	tResourceType(bool _isInteger, CString _type) { isInteger = _isInteger; type = _type; }

	bool isInteger;
	CString type;    // Custom resource type or predefined resource type (https://msdn.microsoft.com/en-us/library/ms648009%28v=vs.85%29.aspx).  

	CArray<tResourceName*> resNames;
};

struct tResourceLCID
{
	tResourceLCID(WORD _lcid) { lcid = _lcid; }

	WORD lcid; // "Locale Culture Identifier" from National Language Support Information (https://msdn.microsoft.com/en-us/goglobal/bb896001.aspx).
	CArray<tResourceType*> resTypes;
};

extern int g_resType;
extern CArray<tResourceLCID*> g_resLangs;

class CResourceList
{
public:
	CResourceList() { g_resType = RESOURCE_ALL; };
	~CResourceList() { release(); }
	enum resourceType { RESOURCE_IMAGE = -1, RESOURCE_ALL }; // or predefined resource type (https://msdn.microsoft.com/en-us/library/ms648009%28v=vs.85%29.aspx)
	
	void setResourceType(int resourceType) { g_resType = resourceType; }
	CArray<tResourceLCID*>* getResourceList(HMODULE hModule);
	
private:
	void release();

	static BOOL EnumTypesFunc(HMODULE hModule, LPTSTR lpType, LONG lParam);                              // Resource type callback function.
	static BOOL EnumNamesFunc(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam);              // Resource name callback function.
	static BOOL EnumLangsFunc(HMODULE hModule, LPCTSTR lpType, LPCTSTR lpName, WORD wLang, LONG lParam); // Resource language callback function.
};

