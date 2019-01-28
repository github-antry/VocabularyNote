#include "stdafx.h"
#include "AutoTestCore.h"
#include "UnitTestCaseByMethod.h"
#include "UnitTestResultMacro.h"

void CallbyHelloTesting(CHelloTesting *pShell)
{
	if(pShell)
	{
		delete pShell;
		pShell = nullptr;
	}
}

///���Զ�����ǿ�Ʊ�delete�Ƿ��쳣
int HelloTesting()
{
	try
	{
		CHelloTesting shell;
		CallbyHelloTesting(&shell);
	}
	catch(...)
	{
		return FAILURE;
	}

	return PASS;
};