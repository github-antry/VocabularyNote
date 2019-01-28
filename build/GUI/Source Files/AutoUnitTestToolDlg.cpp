
// AutoUnitTestToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoUnitTestTool.h"
#include "AutoUnitTestToolDlg.h"
#include "afxdialogex.h"
#include "AutoTestShell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAutoUnitTestToolDlg �Ի���




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


// CAutoUnitTestToolDlg ��Ϣ�������

BOOL CAutoUnitTestToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	InitResultCtrl();
	DisplayTestResult();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoUnitTestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

	m_ctrlResultList.InsertColumn(0, L"���", LVCFMT_CENTER, 40);
	m_ctrlResultList.InsertColumn(1, L"��Ԫ����", LVCFMT_LEFT, 300);
	m_ctrlResultList.InsertColumn(2, L"ִ�н��", LVCFMT_CENTER, 80);

	
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
		m_ctrlResultList.SetItemText(nIndex, 2, itr->second ? L"ͨ��" : L"ִ��ʧ��");

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
				m_ctrlResultList.SetItemText(nIndex, 2, itrSub->second ? L"ͨ��" : L"ִ��ʧ��");
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
	strTips.Format(L"ִ��ʧ��ͳ�ƣ� \n�����ࡾ%d��\n��Ĳ��Է�����%d��\n�����Ĳ��Է�����%d��", 
		nFailedClass,
		nFailedFucntionInClass,
		nFailedFunction);

	m_tips.SetWindowText(strTips);
}
