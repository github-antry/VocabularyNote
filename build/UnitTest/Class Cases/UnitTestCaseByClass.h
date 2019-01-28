#pragma once
#include "unittestcasebase.h"

class CUnitTestCaseByClass :
	public CUnitTestCaseBase
{
public:
	CUnitTestCaseByClass(void);
	~CUnitTestCaseByClass(void);

	virtual int RunTesting() override
	{
		ADD_TO_RUNTESTING(TestTempalte);

		return PASS;
	}

	int TestTempalte(){return PASS;}
};

