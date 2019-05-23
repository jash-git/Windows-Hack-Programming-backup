// Zlib_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "zlib_compress.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	BYTE *pCompressData = NULL;
	DWORD dwCompressDataSize = 0;
	BYTE *pUncompressData = NULL;
	DWORD dwUncompressDataSize = 0;


	// 压缩文件
	bRet = Zlib_CompressData("520.exe", &pCompressData, &dwCompressDataSize);
	if (FALSE == bRet)
	{
		return 1;
	}

	// 保存压缩数据为文件
	bRet = SaveToOriginalFile("520.myzip", pCompressData, dwCompressDataSize);
	if (FALSE == bRet)
	{
		return 2;
	}

	// 解压缩压缩文件
	bRet = Zlib_UncompressData("520.myzip", &pUncompressData, &dwUncompressDataSize);
	if (FALSE == bRet)
	{
		return 3;
	}

	// 保存压缩数据为文件
	bRet = SaveToOriginalFile("520_Uncompress.exe", pUncompressData, dwUncompressDataSize);
	if (FALSE == bRet)
	{
		return 4;
	}
	
	// 释放内存
	delete []pUncompressData;
	pUncompressData = NULL;
	delete []pCompressData;
	pCompressData = NULL;

	system("pause");
	return 0;
}

