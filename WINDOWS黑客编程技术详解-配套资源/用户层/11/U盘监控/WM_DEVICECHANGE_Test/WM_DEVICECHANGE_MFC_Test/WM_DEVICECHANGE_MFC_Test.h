
// WM_DEVICECHANGE_MFC_Test.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CWM_DEVICECHANGE_MFC_TestApp: 
// 有关此类的实现，请参阅 WM_DEVICECHANGE_MFC_Test.cpp
//

class CWM_DEVICECHANGE_MFC_TestApp : public CWinApp
{


public:
	CWM_DEVICECHANGE_MFC_TestApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CWM_DEVICECHANGE_MFC_TestApp theApp;