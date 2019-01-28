#include "AutoTestCore.h"
#include "UnitTestCaseBase.h"
#include "UnitTestResultMacro.h"
#include "CxAutoClean.h"

///
CAutoTestCore* CAutoTestCore::s_pInstance = nullptr;

CAutoTestCore::CAutoTestCore(void)
{
	CPtrAutoClean<CAutoTestCore> clr(s_pInstance);
}

CAutoTestCore::~CAutoTestCore(void)
{
	CUnorderedMapAutoClean<std::wstring, CUnitTestCaseBase> clr(m_mapTestClasses);
}

std::unordered_map<std::wstring, bool> CAutoTestCore::Run(ClassMap* _result)
{
	//执行测试类
	for(auto itr=m_mapTestClasses.begin(); itr!=m_mapTestClasses.end(); ++itr)
	{
		int nRet =itr->second->RunTesting();
		m_mapResultBool.insert(std::make_pair(itr->first, nRet>=NOT_FAILURE?true:false));
		m_mapResultString.insert(std::make_pair(itr->first, itr->second->GetResultString()));
	}

	//执行测试函数
	for(auto itr=m_mapTestFunctions.begin(); itr!=m_mapTestFunctions.end(); ++itr)
	{
		int nRet = ((FUNC)(*(itr->second)))();
		m_mapResultBool.insert(std::make_pair(itr->first, nRet>=NOT_FAILURE?true:false));
	}


	if(_result != nullptr)
	{//仅测试类才有ResultString
		*_result = m_mapResultString;
	}

	return m_mapResultBool;
}
