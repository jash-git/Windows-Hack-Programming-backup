// RunDllInMem_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MmLoadDll.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szFileName[MAX_PATH] = "TestDll.dll";

	// 打开DLL文件并获取DLL文件大小
	HANDLE hFile = ::CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		ShowError("CreateFile");
		return 1;
	}
	DWORD dwFileSize = ::GetFileSize(hFile, NULL);
	// 申请动态内存并读取DLL到内存中
	BYTE *lpData = new BYTE[dwFileSize];
	if (NULL == lpData)
	{
		ShowError("new");
		return 2;
	}
	DWORD dwRet = 0;
	::ReadFile(hFile, lpData, dwFileSize, &dwRet, NULL);

	// 将内存DLL加载到程序中
	LPVOID lpBaseAddress = MmLoadLibrary(lpData, dwFileSize);
	if (NULL == lpBaseAddress)
	{
		ShowError("MmLoadLibrary");
		return 3;
	}
	printf("DLL加载成功\n");

	// 获取DLL导出函数并调用
	typedef BOOL(*typedef_ShowMessage)(char *lpszText, char *lpszCaption);
	typedef_ShowMessage ShowMessage = (typedef_ShowMessage)MmGetProcAddress(lpBaseAddress, "ShowMessage");
	if (NULL == ShowMessage)
	{
		ShowError("MmGetProcAddress");
		return 4;
	}
	ShowMessage("I am Demon·Gan\n", "Who Are You");

	// 释放从内存加载的DLL
	BOOL bRet = MmFreeLibrary(lpBaseAddress);
	if (FALSE == bRet)
	{
		ShowError("MmFreeLirbary");
	}

	// 释放
	delete[] lpData;
	lpData = NULL;
	::CloseHandle(hFile);

	system("pause");
	return 0;
}

