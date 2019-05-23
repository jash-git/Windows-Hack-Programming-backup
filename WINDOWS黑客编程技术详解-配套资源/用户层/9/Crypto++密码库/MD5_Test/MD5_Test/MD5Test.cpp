#include "stdafx.h"
#include "MD5Test.h"


// 计算文件的 MD5 值
string CalMD5_ByFile(char *pszFileName)
{
	string value;
	MD5 md5;
	FileSource(pszFileName, true, new HashFilter(md5, new HexEncoder(new StringSink(value))));
	return value;
}


// 计算数据的 MD5 值
string CalMD5_ByMem(PBYTE pData, DWORD dwDataSize)
{
	string value;
	MD5 md5;
	StringSource(pData, dwDataSize, true, new HashFilter(md5, new HexEncoder(new StringSink(value))));
	return value;
}


/*

MD5 md5;
SHA1 sha1;
SHA256 sha256;
CRC32 crc32;

string src = "Hello World";
string dst;
BYTE pData[] = {1, 2, 3, 4, 5};
DWORD dwDataSize = sizeof(pData);
string file = "520.exe";

StringSource(src, true, new HashFilter(md5, new HexEncoder(new StringSink(dst))));
StringSource(src, true, new HashFilter(sha1, new HexEncoder(new StringSink(dst))));
StringSource(src, true, new HashFilter(sha256, new HexEncoder(new StringSink(dst))));
StringSource(src, true, new HashFilter(crc32, new HexEncoder(new StringSink(dst))));

StringSource(pData, dwDataSize, true, new HashFilter(md5, new HexEncoder(new StringSink(digest))));
StringSource(pData, dwDataSize, true, new HashFilter(sha1, new HexEncoder(new StringSink(digest))));
StringSource(pData, dwDataSize, true, new HashFilter(sha256, new HexEncoder(new StringSink(digest))));
StringSource(pData, dwDataSize, true, new HashFilter(crc32, new HexEncoder(new StringSink(digest))));

FileSource(file, true, new HashFilter(md5, new HexEncoder(new StringSink(dst))));
FileSource(file, true, new HashFilter(sha1, new HexEncoder(new StringSink(dst))));
FileSource(file, true, new HashFilter(sha256, new HexEncoder(new StringSink(dst))));
FileSource(file, true, new HashFilter(crc32, new HexEncoder(new StringSink(dst))));

*/