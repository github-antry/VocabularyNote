#pragma once

#include "AutoTestShell.h"
#include "UnitTestResultMacro.h"
#include <unordered_map>
#include <string>

#define ADD_TO_RUNTESTING(method)  {\
	int nRet = method(); \
	m_mapResultString.member.insert(std::pair<std::wstring, int>(L#method, nRet));\
	if(nRet < NOT_FAILURE) return nRet; \
}

class CUnitTestCaseBase
{
public:
	CUnitTestCaseBase(void);
	virtual ~CUnitTestCaseBase(void);

	virtual int RunTesting() = 0;

	virtual MapOfMemberFunction GetResultString()
	{	
		return m_mapResultString;
	};

protected:
	MapOfMemberFunction  m_mapResultString;
};

