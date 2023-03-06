#include "stdafx.h"
#include "Resourcelist.h"

int g_resType;                     // Resource type.
CArray<tResourceLCID*> g_resLangs; // Languages (or more precisely - locale culture identifiers).

void CResourceList::release()
{
	int i, j, k;

	for (i = 0; i < g_resLangs.GetSize(); i++)
	{
		for (j = 0; j < g_resLangs.GetAt(i)->resTypes.GetSize(); j++)
		{
			for (k = 0; k < g_resLangs.GetAt(i)->resTypes.GetAt(j)->resNames.GetSize(); k++)
				delete g_resLangs.GetAt(i)->resTypes.GetAt(j)->resNames.GetAt(k);
			g_resLangs.GetAt(i)->resTypes.GetAt(j)->resNames.RemoveAll();
			delete g_resLangs.GetAt(i)->resTypes.GetAt(j);
		}
		g_resLangs.GetAt(i)->resTypes.RemoveAll(); delete g_resLangs.GetAt(i);
	}
	g_resLangs.RemoveAll();
}

CArray<tResourceLCID*>* CResourceList::getResourceList(HMODULE hModule)
{
	release(); EnumResourceTypes(hModule, (ENUMRESTYPEPROC)EnumTypesFunc, 0); return &g_resLangs;
}

//
// Resource type callback function.
//
//    hModule ... module handle
//    lpType  ... address of resource type
//    lParam  ... extra parameter, could be used for error checking
// 
BOOL CResourceList::EnumTypesFunc(HMODULE hModule, LPTSTR lpType, LONG lParam)
{
	bool ok = false;

	if (g_resType > 0) // Predefined resource type (https://msdn.microsoft.com/en-us/library/ms648009%28v=vs.85%29.aspx).
	{
		if (IS_INTRESOURCE(lpType) && (INT)lpType == g_resType) ok = true;
	}
	else if (g_resType == resourceType::RESOURCE_IMAGE)
	{
		if (!IS_INTRESOURCE(lpType) || lpType == RT_BITMAP || lpType == RT_GROUP_ICON || lpType == RT_RCDATA) ok = true;
	}
	else ok = true;

	if (ok) EnumResourceNames(hModule, lpType, (ENUMRESNAMEPROC)EnumNamesFunc, 0);  // Get names of all resources of type lpType.

	return TRUE;
}

//
// Resource name callback function.
//
//    hModule ... module handle
//    lpType  ... address of resource type
//    lpName  ... address of resource name
//    lParam  ... extra parameter, could be used for error checking
//
BOOL CResourceList::EnumNamesFunc(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam)
{
	EnumResourceLanguages(hModule, lpType, lpName, (ENUMRESLANGPROC)EnumLangsFunc, 0); return TRUE; // Get languages of all resources of type lpType with name lpName.
}

//
// Resource language callback function.
//
//    hModule ... module handle
//    lpType  ... address of resource type
//    wlang   ... resource language
//    lpName  ... address of resource name
// 
BOOL CResourceList::EnumLangsFunc(HMODULE hModule, LPCTSTR lpType, LPCTSTR lpName, WORD wLang, LONG lParam)
{
	int i, j; bool isTypeInt = true, isNameInt = true; CString type, name; tResourceType *t = NULL; tResourceLCID *l = NULL;

	if (IS_INTRESOURCE(lpType)) type.Format(_T("%u"), (UINT)lpType); else { type = CString(lpType); isTypeInt = false; }
	if (IS_INTRESOURCE(lpName)) name.Format(_T("%u"), (UINT)lpName); else { name = CString(lpName); isNameInt = false; }

	for (i = 0; i < g_resLangs.GetSize(); i++)
		if (g_resLangs.GetAt(i)->lcid == wLang)
		{
			for (j = 0; j < g_resLangs.GetAt(i)->resTypes.GetSize(); j++)
				if (g_resLangs.GetAt(i)->resTypes.GetAt(j)->type == type)
				{
					g_resLangs.GetAt(i)->resTypes.GetAt(j)->resNames.Add(new tResourceName(isNameInt, name)); return TRUE;
				}
			g_resLangs.GetAt(i)->resTypes.Add(t = new tResourceType(isTypeInt, type)); t->resNames.Add(new tResourceName(isNameInt, name)); return TRUE;
		}
	g_resLangs.Add(l = new tResourceLCID(wLang)); l->resTypes.Add(t = new tResourceType(isTypeInt, type)); t->resNames.Add(new tResourceName(isNameInt, name)); return TRUE;
}


