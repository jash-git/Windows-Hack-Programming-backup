
// DelayLoadDll_TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DelayLoadDll_Test.h"
#include "DelayLoadDll_TestDlg.h"
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


// CDelayLoadDll_TestDlg 对话框



CDelayLoadDll_TestDlg::CDelayLoadDll_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDelayLoadDll_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDelayLoadDll_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDelayLoadDll_TestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDelayLoadDll_TestDlg 消息处理程序


void FreeRes_ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}


// 释放资源
BOOL FreeMyResource(UINT uiResouceName, char *lpszResourceType, char *lpszSaveFileName)
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (NULL == hRsrc)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	FILE *fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (NULL == fp)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);

	return TRUE;
}


// 获取当前目录
void GetCurrentPath(char *lpszCurrentPath, DWORD dwSize)
{
	::GetModuleFileName(NULL, lpszCurrentPath, dwSize);
	char *p = ::strrchr(lpszCurrentPath, '\\');
	p[0] = '\0';
}


// 加载界面皮肤
void LoadSkin()
{
	// 加载皮肤
	// 获取当前目录
	char szCurrentPath[MAX_PATH] = { 0 };
	GetCurrentPath(szCurrentPath, MAX_PATH);
	// 构造路径
	::lstrcat(szCurrentPath, "\\Skins\\");
	::lstrcat(szCurrentPath, "dogmax2.ssk");
	// 加载皮肤
	::skinppLoadSkin(szCurrentPath);
}


BOOL CDelayLoadDll_TestDlg::OnInitDialog()
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

	// 释放DLL
	// 获取当前目录
	char szCurrentPath[MAX_PATH] = { 0 };
	GetCurrentPath(szCurrentPath, MAX_PATH);
	// 构造路径
	::lstrcat(szCurrentPath, "\\skinppwtl.dll");
	FreeMyResource(IDR_MY_BIN1, "MY_BIN", szCurrentPath);

	// 加载皮肤
	LoadSkin();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDelayLoadDll_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDelayLoadDll_TestDlg::OnPaint()
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
HCURSOR CDelayLoadDll_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

