#ifndef _AUTORUN_REG_H_
#define _AUTORUN_REG_H_


#include <Windows.h>


BOOL Reg_CurrentUser(char *lpszFileName, char *lpszValueName);
BOOL Reg_LocalMachine(char *lpszFileName, char *lpszValueName);


#endif