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

///测试堆数据强制被delete是否报异常
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