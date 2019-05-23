#ifndef _ADJUST_TOKEN_PRIVILEGES_H_
#define _ADJUST_TOKEN_PRIVILEGES_H_


#include <Windows.h>


BOOL EnbalePrivileges(HANDLE hProcess, char *pszPrivilegesName);


#endif