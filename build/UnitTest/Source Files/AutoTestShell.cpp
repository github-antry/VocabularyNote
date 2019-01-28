#include "StdAfx.h"
#include "AutoTestShell.h"
#include "UnitTestCaseBase.h"
#include "UnitTestCaseByMethod.h"
#include "UnitTestCaseByClass.h"
/**********************Testing For Method END*************************/

///
void CAutoTestShell::InsertUnitMethod()
{	
	ADD_TEST_FUNCTION(HelloTesting, false);

	//ADD_TEST_CLASS(CUnitTestCaseByClass, true);
	//ADD_TEST_CLASS(COctothorpeTesting, true);
	//ADD_TEST_CLASS(CLambdaTesting, true);
	//ADD_TEST_CLASS(CCRCTesting, true);
	//ADD_TEST_CLASS(CTemplateTesting, true);
}