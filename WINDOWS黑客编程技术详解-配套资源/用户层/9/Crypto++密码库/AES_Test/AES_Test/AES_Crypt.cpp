#include "stdafx.h"
#include "AES_Crypt.h"


// 密钥生成
// 输出：AES密钥、AES密钥长度
BOOL GenerateAESKey(BYTE *pAESKey, DWORD *pdwAESKeyLength, DWORD dwBufferSize)
{
	srand(time(NULL));

	if (AES::MIN_KEYLENGTH > *pdwAESKeyLength)
	{
		*pdwAESKeyLength = AES::MIN_KEYLENGTH;
	}
	else if (AES::MAX_KEYLENGTH < *pdwAESKeyLength)
	{
		*pdwAESKeyLength = AES::MAX_KEYLENGTH;
	}
	

	// 密钥长度大于缓冲区
	if (dwBufferSize < *pdwAESKeyLength)
	{
		return FALSE;
	}

	// 随机生成密钥(大小写字母、数字、字符等可显示字符)
	// 33 - 126
	int i = 0;
	::RtlZeroMemory(pAESKey, dwBufferSize);
	for (i = 0; i < *pdwAESKeyLength; i++)
	{
		pAESKey[i] = 33 + (rand() % 94);
	}

	return TRUE;
}


// 加密
// 输入：原文内容、原文内容长度、密钥内容、密钥内容长度
// 输出：密文内容、密文内容长度
BOOL AES_Encrypt(BYTE *pOriginalData, DWORD dwOriginalDataSize, BYTE *pAESKey, DWORD dwAESKeySize, BYTE **ppEncryptData, DWORD *pdwEncryptData)
{
	// 加密器
	AESEncryption aesEncryptor;			
	// 加密原文数据块
	unsigned char inBlock[AES::BLOCKSIZE];	
	// 加密后密文数据块
	unsigned char outBlock[AES::BLOCKSIZE];	
	// 必须设定全为0
	unsigned char xorBlock[AES::BLOCKSIZE];	

	DWORD dwOffset = 0;
	BYTE *pEncryptData = NULL;
	DWORD dwEncryptDataSize = 0;

	// 计算原文长度, 并按 128位 即 16字节 对齐, 不够则 填充0 对齐
	// 商
	DWORD dwQuotient = dwOriginalDataSize / AES::BLOCKSIZE;  
	// 余数
	DWORD dwRemaind = dwOriginalDataSize % AES::BLOCKSIZE;		
	if (0 != dwRemaind)
	{
		dwQuotient++;
	}

	// 申请动态内存
	dwEncryptDataSize = dwQuotient * AES::BLOCKSIZE;
	pEncryptData = new BYTE[dwEncryptDataSize];
	if (NULL == pEncryptData)
	{
		return FALSE;
	}

	// 设置密钥
	aesEncryptor.SetKey(pAESKey, dwAESKeySize);

	do
	{
		// 置零
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		// 获取加密块
		if (dwOffset <= (dwOriginalDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), (dwOriginalDataSize - dwOffset));
		}

		// 加密
		aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);

		// 构造
		::RtlCopyMemory((PVOID)(pEncryptData + dwOffset), outBlock, AES::BLOCKSIZE);

		// 更新数据
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (0 < dwQuotient);

	// 返回数据
	*ppEncryptData = pEncryptData;
	*pdwEncryptData = dwEncryptDataSize;

	return TRUE;
}


// 解密
// 输入：密文内容、密文内容长度、密钥内容、密钥内容长度
// 输出：解密后明文内容、解密后明文内容长度
BOOL AES_Decrypt(BYTE *pEncryptData, DWORD dwEncryptData, BYTE *pAESKey, DWORD dwAESKeySize, BYTE **ppDecryptData, DWORD *pdwDecryptData)
{
	// 解密器
	AESDecryption aesDecryptor;				
	// 解密密文数据块
	unsigned char inBlock[AES::BLOCKSIZE];		
	// 解密后后明文数据块
	unsigned char outBlock[AES::BLOCKSIZE];			
	// 必须设定全为0
	unsigned char xorBlock[AES::BLOCKSIZE];						
	DWORD dwOffset = 0;
	BYTE *pDecryptData = NULL;
	DWORD dwDecryptDataSize = 0;

	// 计算密文长度, 并按 128位 即 16字节 对齐, 不够则填充0对齐
	// 商
	DWORD dwQuotient = dwEncryptData / AES::BLOCKSIZE;
	// 余数
	DWORD dwRemaind = dwEncryptData % AES::BLOCKSIZE;		
	if (0 != dwRemaind)
	{
		dwQuotient++;
	}

	// 申请动态内存
	dwDecryptDataSize = dwQuotient * AES::BLOCKSIZE;
	pDecryptData = new BYTE[dwDecryptDataSize];
	if (NULL == pDecryptData)
	{
		return FALSE;
	}

	// 设置密钥
	aesDecryptor.SetKey(pAESKey, dwAESKeySize);

	do
	{
		// 置零
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		// 获取解密块
		if (dwOffset <= (dwDecryptDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), (dwEncryptData - dwOffset));
		}

		// 解密
		aesDecryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);

		// 构造
		::RtlCopyMemory((PVOID)(pDecryptData + dwOffset), outBlock, AES::BLOCKSIZE);

		// 更新数据
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (0 < dwQuotient);

	// 返回数据
	*ppDecryptData = pDecryptData;
	*pdwDecryptData = dwDecryptDataSize;

	return TRUE;
}


// 显示数据
// 输入：输出数据内容、输出数据内容长度
void ShowData(BYTE *pData, DWORD dwSize)
{
	for (int i = 0; i < dwSize; i++)
	{
		if ((0 != i) &&
			(0 == i % 16))
		{
			printf("\n");
		}
		else if ((0 != i) &&
			(0 == i % 8))
		{
			printf(" ");
		}

		printf("%02X ", pData[i]);
	}
	printf("\n");
}