
// AutoUnitTestToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <unordered_map>
#include <string>
#include "afxwin.h"
#include "UnitTestResultMacro.h"
// CAutoUnitTestToolDlg �Ի���
class CAutoUnitTestToolDlg : public CDialogEx
{
// ����
public:
	CAutoUnitTestToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOUNITTESTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
// ʵ��
protected:
	DECLARE_MESSAGE_MAP()

	// ���ɵ���Ϣӳ�亯��
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
