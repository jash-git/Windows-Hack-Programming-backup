#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_


#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")


// 连接到服务器
BOOL Connection(char *lpszServerIp, int iServerPort);
// 发送数据
void SendMsg(char *pszSend);
// 创建接收数据多线程
void RecvMsg();
// 接收数据多线程
UINT RecvThreadProc(LPVOID lpVoid);


#endif