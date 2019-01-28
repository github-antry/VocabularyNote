#pragma once

#include "UnitTestResultMacro.h"

#include<list>
#include<string>

///
/**************************************************************************************************************************
ע��ԭ��ʹ��ENABLE_CLASS_RUN_TEST���ADD_TEST_CLASS
//���Ӳ�����
#define ADD_TEST_CLASS(ClassName, bExeute) \
{\
	if(bExeute) {\
	CUnitTestCaseBase* pCase = new ClassName; \
	CAutoTestCore::Instance()->InsertTestClass(std::pair<std::wstring, CUnitTestCaseBase*>(L#ClassName, pCase));\
	}\
}
***************************************************************************************************************************/

//���Ӳ��Է���
#define ADD_TEST_FUNCTION(pFunc, bExeute)\
{\
	if(bExeute) {\
	CAutoTestCore::Instance()->InsertTestFunction(std::pair<std::wstring, FUNC>(L#pFunc, pFunc));\
	}\
}


typedef int (*FUNC)();


class CUnitTestCaseBase;
class CAutoTestCore
{
public:
	CAutoTestCore(void);
	virtual ~CAutoTestCore(void);

	static CAutoTestCore* Instance()
	{
		return &s_Instance;
	}

	void InsertTestFunction(std::pair<std::wstring, FUNC> _key_func_pair)
	{
		m_mapTestFunctions.insert(_key_func_pair);
	}

	void InsertTestClass(std::pair<std::wstring, CUnitTestCaseBase*> _key_class_pair)
	{
		m_mapTestClasses.insert(_key_class_pair);
	}

	std::unordered_map<std::wstring, bool> Run(ClassMap* _result);

private:
	static CAutoTestCore s_Instance;


private:
	std::unordered_map<std::wstring, FUNC>                       m_mapTestFunctions; // <�������ַ���, ����ָ��>
	std::unordered_map<std::wstring, CUnitTestCaseBase*>          m_mapTestClasses;   // <�����ַ���, ��ʵ��ָ��>

	std::unordered_map<std::wstring, bool>                        m_mapResultBool;    // <��������ַ���, ����ִ�н��>

	ClassMap m_mapResultString;  // <�����ַ���, <���Ա����, ��Ա����ִ�н��>>
};


class  TestClassRegister { \
public: \
		TestClassRegister( \
		const std::wstring& _class, \
		CUnitTestCaseBase* _test_class){ \
		CAutoTestCore::Instance()->InsertTestClass(std::make_pair(_class, _test_class));} \
}; 

#define ENABLE_CLASS_RUN_TEST(CLASS_NAME) \
	static TestClassRegister g_##CLASS_NAME##_register(L###CLASS_NAME, new CLASS_NAME);
