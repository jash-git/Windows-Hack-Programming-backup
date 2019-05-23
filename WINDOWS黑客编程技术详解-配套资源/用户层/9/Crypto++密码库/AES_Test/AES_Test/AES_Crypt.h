#ifndef _AES_CRYPT_H_
#define _AES_CRYPT_H_


#include <time.h>
#include <Windows.h>
//*************************************************
//         crypt++加密库的头文件和静态库
//*************************************************
#include "crypt\\include\\aes.h"
using namespace CryptoPP;         // 命名空间

#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "crypt\\lib\\x64\\debug\\cryptlib.lib")
	#else
		#pragma comment(lib, "crypt\\lib\\x86\\debug\\cryptlib.lib")
	#endif
#else
	#ifdef _WIN64
		#pragma comment(lib, "crypt\\lib\\x64\\release\\cryptlib.lib")
	#else
		#pragma comment(lib, "crypt\\lib\\x86\\release\\cryptlib.lib")
	#endif
#endif
//*************************************************


// 密钥生成
// 输出：AES密钥、AES密钥长度
BOOL GenerateAESKey(BYTE *pAESKey, DWORD *pdwAESKeyLength, DWORD dwBufferSize);


// 加密
// 输入：原文内容、原文内容长度、密钥内容、密钥内容长度
// 输出：密文内容、密文内容长度
BOOL AES_Encrypt(BYTE *pOriginalData, DWORD dwOriginalDataSize, BYTE *pAESKey, DWORD dwAESKeySize, BYTE **ppEncryptData, DWORD *pdwEncryptData);

// 解密
// 输入：密文内容、密文内容长度、密钥内容、密钥内容长度
// 输出：解密后明文内容、解密后明文内容长度
BOOL AES_Decrypt(BYTE *pEncryptData, DWORD dwEncryptData, BYTE *pAESKey, DWORD dwAESKeySize, BYTE **ppDecryptData, DWORD *pdwDecryptData);

// 显示数据
// 输入：输出数据内容、输出数据内容长度
void ShowData(BYTE *pData, DWORD dwSize);



#endif