
// AutoUnitTestTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoUnitTestToolApp:
// �йش����ʵ�֣������ AutoUnitTestTool.cpp
//

class CAutoUnitTestToolApp : public CWinApp
{
public:
	CAutoUnitTestToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoUnitTestToolApp theApp;