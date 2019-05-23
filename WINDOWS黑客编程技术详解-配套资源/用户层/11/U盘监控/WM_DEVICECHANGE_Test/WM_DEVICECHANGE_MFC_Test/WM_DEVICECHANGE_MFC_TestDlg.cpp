
// WM_DEVICECHANGE_MFC_TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WM_DEVICECHANGE_MFC_Test.h"
#include "WM_DEVICECHANGE_MFC_TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWM_DEVICECHANGE_MFC_TestDlg 对话框



CWM_DEVICECHANGE_MFC_TestDlg::CWM_DEVICECHANGE_MFC_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWM_DEVICECHANGE_MFC_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWM_DEVICECHANGE_MFC_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWM_DEVICECHANGE_MFC_TestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_DEVICECHANGE, OnDeviceChange)

END_MESSAGE_MAP()


// CWM_DEVICECHANGE_MFC_TestDlg 消息处理程序

BOOL CWM_DEVICECHANGE_MFC_TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWM_DEVICECHANGE_MFC_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWM_DEVICECHANGE_MFC_TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWM_DEVICECHANGE_MFC_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CWM_DEVICECHANGE_MFC_TestDlg::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		// 设备已经插入
	case DBT_DEVICEARRIVAL:
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		// 逻辑卷
		if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
		{
			// 根据 dbcv_unitmask 计算出设备盘符
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			DWORD dwDriverMask = lpdbv->dbcv_unitmask;
			DWORD dwTemp = 1;
			char szDriver[4] = "A:\\";
			for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
			{
				if (0 < (dwTemp & dwDriverMask))
				{
					// 获取设备盘符
					::MessageBox(NULL, szDriver, "设备已插入", MB_OK);
				}
				// 左移1位, 接着判断下一个盘符
				dwTemp = (dwTemp << 1);
			}
		}
		break;
	}
	// 设备已经移除
	case DBT_DEVICEREMOVECOMPLETE:
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		// 逻辑卷
		if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
		{
			// 根据 dbcv_unitmask 计算出设备盘符
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			DWORD dwDriverMask = lpdbv->dbcv_unitmask;
			DWORD dwTemp = 1;
			char szDriver[4] = "A:\\";
			for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
			{
				if (0 < (dwTemp & dwDriverMask))
				{
					// 获取设备盘符
					::MessageBox(NULL, szDriver, "设备已移除", MB_OK);
				}
				// 左移1位, 接着判断下一个盘符
				dwTemp = (dwTemp << 1);
			}
		}
		break;
	}
	default:
		break;
	}

	return 0;
}