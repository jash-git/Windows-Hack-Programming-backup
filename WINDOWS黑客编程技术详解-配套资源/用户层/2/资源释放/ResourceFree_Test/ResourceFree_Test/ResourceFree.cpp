#include "stdafx.h"
#include "ResourceFree.h"


void FreeRes_ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}


BOOL FreeMyResource(UINT uiResouceName, char *lpszResourceType, char *lpszSaveFileName)
{
	// 获取指定模块里的指定资源
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (NULL == hRsrc)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	// 获取资源的大小
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	// 将资源加载到内存里
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	// 锁定资源
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	// 保存资源为文件
	FILE *fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (NULL == fp)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);

	return TRUE;
}


BOOL GetResourceInfo(UINT uiResouceName, char *lpszResourceType, PVOID *ppVoid, DWORD *pdwResSize)
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (NULL == hRsrc)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	// 返回
	*ppVoid = lpVoid;
	*pdwResSize = dwSize;

	return TRUE;
}


BOOL ChangeIcon(char *pszChangedIconExeFileName, char *pszSrcIconExeFileName)
{
	// 将在其他程序，并获取程序模块句柄
	HMODULE hEXE = ::LoadLibrary(pszSrcIconExeFileName);
	if (NULL == hEXE)
	{
		FreeRes_ShowError("LoadLibrary");
		return FALSE;
	}
	// 获取其他EXE程序图标资源数据
	HRSRC hRsrc = ::FindResource(hEXE, (LPCSTR)1, RT_ICON);
	if (NULL == hRsrc)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	// 获取资源大小
	DWORD dwSize = ::SizeofResource(hEXE, hRsrc);
	if (0 >= dwSize)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	// 加载资源到程序内存
	HGLOBAL hGlobal = ::LoadResource(hEXE, hRsrc);
	if (NULL == hGlobal)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	// 锁定资源内存
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	// 开始修改图标
	HANDLE hUpdate = ::BeginUpdateResource(pszChangedIconExeFileName, FALSE);
	if (NULL == hUpdate)
	{
		FreeRes_ShowError("BeginUpdateResource");
		return FALSE;
	}
	// 如果资源ID存在, 则替换资源; 否则创建资源
	// 程序把ICON的最小的资源ID作为程序图标, 所以从1开始, 1最小
	BOOL bRet = ::UpdateResource(hUpdate, RT_ICON, (LPCSTR)1, LANG_NEUTRAL, lpVoid, dwSize);
	if (FALSE == bRet)
	{
		FreeRes_ShowError("UpdateResource");
		return FALSE;
	}

	::EndUpdateResource(hUpdate, FALSE);
	// 释放模块
	::FreeLibrary(hEXE);

	return TRUE;
}


BOOL ChangeExeRes(char *pszSrcFileName, char *pszInstallFileName, UINT uiDestResId, char *pszDestResType)
{
	BYTE *pData = NULL;
	DWORD dwDataSize = 0;
	// 打开目标文件获取数据
	HANDLE hFile = ::CreateFile(pszInstallFileName, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		FreeRes_ShowError("CreateFile");
		return FALSE;
	}
	// 获取文件大小
	dwDataSize = ::GetFileSize(hFile, NULL);
	// 申请动态内存
	pData = new BYTE[dwDataSize];
	if (NULL == pData)
	{
		FreeRes_ShowError("new");
		return FALSE;
	}
	// 读取数据
	DWORD dwRet = 0;
	if (FALSE == ::ReadFile(hFile, pData, dwDataSize, &dwRet, NULL))
	{
		FreeRes_ShowError("ReadFile");
		return FALSE;
	}
	// 关闭文件句柄
	::CloseHandle(hFile);

	// 更改资源
	HANDLE hUpdate = ::BeginUpdateResource(pszSrcFileName, FALSE);
	if (NULL == hUpdate)
	{
		FreeRes_ShowError("BeginUpdateResource");
		return FALSE;
	}

	// 如果资源ID存在, 则替换资源; 否则创建资源
	BOOL bRet = ::UpdateResource(hUpdate, pszDestResType, (LPCSTR)uiDestResId, LANG_NEUTRAL, pData, dwDataSize);
	if (FALSE == bRet)
	{
		FreeRes_ShowError("UpdateResource");
		return FALSE;
	}

	::EndUpdateResource(hUpdate, FALSE);

	// 释放内存
	delete[]pData;
	pData = NULL;

	return TRUE;
}
