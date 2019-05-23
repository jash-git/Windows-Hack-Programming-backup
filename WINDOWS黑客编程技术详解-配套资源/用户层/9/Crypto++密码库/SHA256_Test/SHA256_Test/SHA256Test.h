#ifndef _SHA1_TEST_H_
#define _SHA1_TEST_H_


#include <Windows.h>
using namespace std;
//*************************************************
//         crypt++加密库的头文件和静态库
//*************************************************
#include "crypt\\include\\sha.h"
#include "crypt\\include\\files.h"
#include "crypt\\include\\hex.h"
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


// 计算文件的 SHA256 值
string CalSHA256_ByFile(char *pszFileName);

// 计算数据的 SHA256 值
string CalSHA256_ByMem(PBYTE pData, DWORD dwDataSize);


#endif