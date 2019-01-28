
// AutoUnitTestToolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <unordered_map>
#include <string>
#include "afxwin.h"
#include "UnitTestResultMacro.h"
// CAutoUnitTestToolDlg 对话框
class CAutoUnitTestToolDlg : public CDialogEx
{
// 构造
public:
	CAutoUnitTestToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOUNITTESTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
// 实现
protected:
	DECLARE_MESSAGE_MAP()

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	
private:
	void InitResultCtrl();
	void DisplayTestResult();
	void ShowTips(std::unordered_map<std::wstring, bool>& _result,
		ClassMap& _resultString);

private:
	HICON        m_hIcon;
	CListCtrl    m_ctrlResultList;
	CStatic      m_tips;
};
