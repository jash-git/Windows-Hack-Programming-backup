// RtlCompressBuffer_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


typedef NTSTATUS(WINAPI *typedef_RtlGetCompressionWorkSpaceSize)(
	_In_  USHORT CompressionFormatAndEngine,
	_Out_ PULONG CompressBufferWorkSpaceSize,
	_Out_ PULONG CompressFragmentWorkSpaceSize
	);

typedef NTSTATUS(WINAPI *typedef_RtlCompressBuffer)(
	_In_  USHORT CompressionFormatAndEngine,
	_In_  PUCHAR UncompressedBuffer,
	_In_  ULONG  UncompressedBufferSize,
	_Out_ PUCHAR CompressedBuffer,
	_In_  ULONG  CompressedBufferSize,
	_In_  ULONG  UncompressedChunkSize,
	_Out_ PULONG FinalCompressedSize,
	_In_  PVOID  WorkSpace
	);

typedef NTSTATUS(WINAPI *typedef_RtlDecompressBuffer)(
	_In_  USHORT CompressionFormat,
	_Out_ PUCHAR UncompressedBuffer,
	_In_  ULONG  UncompressedBufferSize,
	_In_  PUCHAR CompressedBuffer,
	_In_  ULONG  CompressedBufferSize,
	_Out_ PULONG FinalUncompressedSize
	);


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
#endif
}


// 数据压缩
BOOL CompressData(BYTE *pUncompressData, DWORD dwUncompressDataLength, BYTE **ppCompressData, DWORD *pdwCompressDataLength)
{
	BOOL bRet = FALSE;
	NTSTATUS status = 0;
	HMODULE hModule = NULL;
	typedef_RtlGetCompressionWorkSpaceSize RtlGetCompressionWorkSpaceSize  = NULL;
	typedef_RtlCompressBuffer RtlCompressBuffer = NULL;
	DWORD dwWorkSpaceSize = 0, dwFragmentWorkSpaceSize = 0;
	BYTE *pWorkSpace = NULL;
	BYTE *pCompressData = NULL;
	DWORD dwCompressDataLength = 4096;
	DWORD dwFinalCompressSize = 0;
	do
	{
		// 加载 ntdll.dll 
		hModule = ::LoadLibrary("ntdll.dll");
		if (NULL == hModule)
		{
			ShowError("LoadLibrary");
			break;
		}

		// 获取 RtlGetCompressionWorkSpaceSize 函数地址
		RtlGetCompressionWorkSpaceSize = (typedef_RtlGetCompressionWorkSpaceSize)::GetProcAddress(hModule, "RtlGetCompressionWorkSpaceSize");
		if (NULL == RtlGetCompressionWorkSpaceSize)
		{
			ShowError("GetProcAddress");
			break;
		}

		// 获取 RtlCompressBuffer 函数地址
		RtlCompressBuffer = (typedef_RtlCompressBuffer)::GetProcAddress(hModule, "RtlCompressBuffer");
		if (NULL == RtlCompressBuffer)
		{
			ShowError("GetProcAddress");
			break;
		}

		// 获取WorkSpqce大小
		status = RtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_LZNT1 | COMPRESSION_ENGINE_STANDARD, &dwWorkSpaceSize, &dwFragmentWorkSpaceSize);
		if (0 != status)
		{
			ShowError("RtlGetCompressionWorkSpaceSize");
			break;
		}

		// 申请动态内存
		pWorkSpace = new BYTE[dwWorkSpaceSize];
		if (NULL == pWorkSpace)
		{
			ShowError("new");
			break;
		}
		::RtlZeroMemory(pWorkSpace, dwWorkSpaceSize);
		
		while (TRUE)
		{
			// 申请动态内存
			pCompressData = new BYTE[dwCompressDataLength];
			if (NULL == pCompressData)
			{
				ShowError("new");
				break;
			}
			::RtlZeroMemory(pCompressData, dwCompressDataLength);

			// 调用RtlCompressBuffer压缩数据
			RtlCompressBuffer(COMPRESSION_FORMAT_LZNT1, pUncompressData, dwUncompressDataLength, pCompressData, dwCompressDataLength, 4096, &dwFinalCompressSize, (PVOID)pWorkSpace);
			if (dwCompressDataLength < dwFinalCompressSize)
			{
				// 释放内存
				if (pCompressData)
				{
					delete[]pCompressData;
					pCompressData = NULL;
				}
				dwCompressDataLength = dwFinalCompressSize;
			}
			else
			{
				break;
			}
		}

		// 返回
		*ppCompressData = pCompressData;
		*pdwCompressDataLength = dwFinalCompressSize;
		bRet = TRUE;

	} while(FALSE);

	// 释放
	if (pWorkSpace)
	{
		delete[]pWorkSpace;
		pWorkSpace = NULL;
	}
	if (hModule)
	{
		::FreeLibrary(hModule);
	}

	return bRet;
}


// 数据解压缩
BOOL UncompressData(BYTE *pCompressData, DWORD dwCompressDataLength, BYTE **ppUncompressData, DWORD *pdwUncompressDataLength)
{
	BOOL bRet = FALSE;
	HMODULE hModule = NULL;
	typedef_RtlDecompressBuffer RtlDecompressBuffer = NULL;
	BYTE *pUncompressData = NULL;
	DWORD dwUncompressDataLength = 4096;
	DWORD dwFinalUncompressSize = 0;
	do
	{
		// 加载 ntdll.dll 
		hModule = ::LoadLibrary("ntdll.dll");
		if (NULL == hModule)
		{
			ShowError("LoadLibrary");
			break;
		}

		// 获取 RtlDecompressBuffer 函数地址
		RtlDecompressBuffer = (typedef_RtlDecompressBuffer)::GetProcAddress(hModule, "RtlDecompressBuffer");
		if (NULL == RtlDecompressBuffer)
		{
			ShowError("GetProcAddress");
			break;
		}

		while (TRUE)
		{
			// 申请动态内存
			pUncompressData = new BYTE[dwUncompressDataLength];
			if (NULL == pUncompressData)
			{
				ShowError("new");
				break;
			}
			::RtlZeroMemory(pUncompressData, dwUncompressDataLength);

			// 调用RtlCompressBuffer压缩数据
			RtlDecompressBuffer(COMPRESSION_FORMAT_LZNT1, pUncompressData, dwUncompressDataLength, pCompressData, dwCompressDataLength, &dwFinalUncompressSize);
			if (dwUncompressDataLength < dwFinalUncompressSize)
			{
				// 释放内存
				if (pUncompressData)
				{
					delete[]pUncompressData;
					pUncompressData = NULL;
				}
				dwUncompressDataLength = dwFinalUncompressSize;
			}
			else
			{
				break;
			}
		}

		// 返回
		*ppUncompressData = pUncompressData;
		*pdwUncompressDataLength = dwFinalUncompressSize;
		bRet = TRUE;

	} while (FALSE);

	// 释放
	if (hModule)
	{
		::FreeLibrary(hModule);
	}

	return bRet;
}



int _tmain(int argc, _TCHAR* argv[])
{
	DWORD i = 0;
	BOOL bRet = FALSE;
	char szBuffer[] = "DDDDDDDDDDGGGGGGGGGGGG";
	DWORD dwBufferLength = ::lstrlen(szBuffer);
	BYTE *pCompressData = NULL;
	DWORD dwCompressDataLength = 0;
	BYTE *pUncompressData = NULL;
	DWORD dwUncompressDataLength = 0;

	// 压缩数据
	CompressData((BYTE *)szBuffer, dwBufferLength, &pCompressData, &dwCompressDataLength);

	// 解压数据
	UncompressData(pCompressData, dwCompressDataLength, &pUncompressData, &dwUncompressDataLength);

	// 显示
	printf("原数据为:\n");
	for (i = 0; i < dwBufferLength; i++)
	{
		printf("%X ", szBuffer[i]);
	}
	printf("\n\n压缩数据为:\n");
	for (i = 0; i < dwCompressDataLength; i++)
	{
		printf("%X ", pCompressData[i]);
	}
	printf("\n\n解压缩数据为:\n");
	for (i = 0; i < dwUncompressDataLength; i++)
	{
		printf("%X ", pUncompressData[i]);
	}
	printf("\n");

	// 释放
	if (pUncompressData)
	{
		delete[]pUncompressData;
		pUncompressData = NULL;
	}
	if (pCompressData)
	{
		delete[]pCompressData;
		pCompressData = NULL;
	}
	system("pause");
	return 0;
}








