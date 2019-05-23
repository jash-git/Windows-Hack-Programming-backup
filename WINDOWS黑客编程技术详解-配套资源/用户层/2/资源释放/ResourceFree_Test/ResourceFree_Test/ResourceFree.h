#ifndef _RESOURCE_FREE_H_
#define _RESOURCE_FREE_H_


#include <windows.h>


BOOL FreeMyResource(UINT uiResouceName, char *lpszResourceType, char *lpszSaveFileName);

BOOL GetResourceInfo(UINT uiResouceName, char *lpszResourceType, PVOID *ppVoid, DWORD *pdwResSize);

BOOL ChangeIcon(char *pszChangedIconExeFileName, char *pszSrcIconExeFileName);

BOOL ChangeExeRes(char *pszSrcFileName, char *pszInstallFileName, UINT uiDestResId, char *pszDestResType);

#endif