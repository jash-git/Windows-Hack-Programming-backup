
// DelayLoadDll_TestDlg.h : 头文件
//

#pragma once

#include "Skins\\SkinPPWTL.h"
#pragma comment(lib, "Skins\\SkinPPWTL.lib")


// CDelayLoadDll_TestDlg 对话框
class CDelayLoadDll_TestDlg : public CDialogEx
{
// 构造
public:
	CDelayLoadDll_TestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DELAYLOADDLL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
