#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_


#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")


// 绑定端口并监听
BOOL SocketBindAndListen(char *lpszIp, int iPort);
// 发送数据
void SendMsg(char *pszSend);
// 创建接收数据多线程
void AcceptRecvMsg();
// 接收数据多线程
UINT RecvThreadProc(LPVOID lpVoid);


#endif