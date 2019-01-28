
// AutoUnitTestToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoUnitTestTool.h"
#include "AutoUnitTestToolDlg.h"
#include "afxdialogex.h"
#include "AutoTestShell.h"

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


// CAutoUnitTestToolDlg 对话框




CAutoUnitTestToolDlg::CAutoUnitTestToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoUnitTestToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoUnitTestToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_BK, m_grid);
	//DDX_Control(pDX, IDC_STATIC_Target, m_TargetCtrl);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ctrlResultList);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_tips);
}

BEGIN_MESSAGE_MAP(CAutoUnitTestToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAutoUnitTestToolDlg 消息处理程序

BOOL CAutoUnitTestToolDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitResultCtrl();
	DisplayTestResult();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoUnitTestToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoUnitTestToolDlg::OnPaint()
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

void CAutoUnitTestToolDlg::InitResultCtrl()
{
	m_ctrlResultList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_BORDERSELECT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);

	m_ctrlResultList.InsertColumn(0, L"序号", LVCFMT_CENTER, 40);
	m_ctrlResultList.InsertColumn(1, L"单元名称", LVCFMT_LEFT, 300);
	m_ctrlResultList.InsertColumn(2, L"执行结果", LVCFMT_CENTER, 80);

	
}

void CAutoUnitTestToolDlg::DisplayTestResult()
{
	CAutoTestShell autoTest;

	ClassMap resultString;
	std::unordered_map<std::wstring, bool> result = autoTest.Run(&resultString);

	int nIndex = -1;
	for(auto itr=result.begin(); itr!=result.end(); ++itr)
	{
		++nIndex;
		nIndex = m_ctrlResultList.InsertItem(LVIF_TEXT|LVIF_STATE|LVNI_TOLEFT, nIndex, L"", 0, LVIS_SELECTED, 0, 0);
	
		CString nSerialNo;
		nSerialNo.Format(L"%d", nIndex+1);
		m_ctrlResultList.SetItemText(nIndex, 0, nSerialNo);
		m_ctrlResultList.SetItemText(nIndex, 1, CString(itr->first.c_str()));
		m_ctrlResultList.SetItemText(nIndex, 2, itr->second ? L"通过" : L"执行失败");

		auto itrFind = resultString.find(itr->first);
		if(itrFind != resultString.end())
		{
			for(auto itrSub=itrFind->second.member.begin(); itrSub!=itrFind->second.member.end(); ++itrSub)
			{
				++nIndex;
				nIndex = m_ctrlResultList.InsertItem(LVIF_TEXT | LVIF_STATE, nIndex, L"", 0, LVIS_SELECTED, 0, 0);

				nSerialNo.Format(L"%d", nIndex+1);
				m_ctrlResultList.SetItemText(nIndex, 0, nSerialNo);
				m_ctrlResultList.SetItemText(nIndex, 1, CString(L"*")+CString(itrSub->first.c_str()));
				m_ctrlResultList.SetItemText(nIndex, 2, itrSub->second ? L"通过" : L"执行失败");
			}
		}
	}

	ShowTips(result, resultString);
}

void CAutoUnitTestToolDlg::ShowTips(std::unordered_map<std::wstring, bool>& _result, ClassMap& _resultString)
{
	int nFailedClass = 0;
	int nFailedFunction = 0;
	int nFailedFucntionInClass = 0;
	
	for(auto itr=_result.begin(); itr!=_result.end(); ++itr)
	{
		if(!itr->second)
		{
			auto itrFind = _resultString.find(itr->first);
			if(itrFind != _resultString.end())
			{
				++nFailedClass;

				for(auto itrSub=itrFind->second.member.begin(); itrSub!=itrFind->second.member.end(); ++itrSub)
				{
					if(!itrSub->second)
					{
						++nFailedFucntionInClass;
					}
				}
			}
			else
			{
				++nFailedFunction;
			}
		}
	}

	CString strTips;
	strTips.Format(L"执行失败统计： \n测试类【%d】\n类的测试方法【%d】\n独立的测试方法【%d】", 
		nFailedClass,
		nFailedFucntionInClass,
		nFailedFunction);

	m_tips.SetWindowText(strTips);
}
