#pragma once
#include "unittestcasebase.h"

class CHtmlcxxTest :
	public CUnitTestCaseBase
{
public:
	CHtmlcxxTest(void);
	~CHtmlcxxTest(void);

	virtual int RunTesting() override
	{
		ADD_TO_RUNTESTING(Test);

		return PASS;
	}

private:
	int Test();
};

ENABLE_CLASS_RUN_TEST(CHtmlcxxTest)