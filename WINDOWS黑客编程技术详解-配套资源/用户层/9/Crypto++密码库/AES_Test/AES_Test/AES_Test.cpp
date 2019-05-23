// AES_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AES_Crypt.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE *pEncryptData = NULL;
	DWORD dwEncryptDataSize = 0;
	BYTE *pDecryptData = NULL;
	DWORD dwDecryptDataSize = 0;
	char szOriginalData[] = "I am DemonGan";
	char szAESKey[] = "DemonGanDemonGan";
	BOOL  bRet = FALSE;

	// 加密
	bRet = AES_Encrypt((BYTE *)szOriginalData, (1 + ::lstrlen(szOriginalData)), (BYTE *)szAESKey, ::lstrlen(szAESKey), &pEncryptData, &dwEncryptDataSize);
	if (FALSE == bRet)
	{
		return 1;
	}

	// 解密
	bRet = AES_Decrypt(pEncryptData, dwEncryptDataSize, (BYTE *)szAESKey, ::lstrlen(szAESKey), &pDecryptData, &dwDecryptDataSize);
	if (FALSE == bRet)
	{
		return 2;
	}

	// 显示
	printf("原文数据:\n");
	ShowData((BYTE *)szOriginalData, (1 + ::lstrlen(szOriginalData)));
	printf("密文数据:\n");
	ShowData(pEncryptData, dwEncryptDataSize);
	printf("解密后数据:\n");
	ShowData(pDecryptData, dwDecryptDataSize);

	// 释放内存
	delete[]pEncryptData;
	pEncryptData = NULL;
	delete[]pDecryptData;
	pDecryptData = NULL;

	system("pause");
	return 0;
}

