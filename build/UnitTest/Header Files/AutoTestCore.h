#pragma once

#include "UnitTestResultMacro.h"

#include<list>
#include<string>

///
/**************************************************************************************************************************
注释原因：使用ENABLE_CLASS_RUN_TEST替代ADD_TEST_CLASS
//增加测试类
#define ADD_TEST_CLASS(ClassName, bExeute) \
{\
	if(bExeute) {\
	CUnitTestCaseBase* pCase = new ClassName; \
	CAutoTestCore::Instance()->InsertTestClass(std::pair<std::wstring, CUnitTestCaseBase*>(L#ClassName, pCase));\
	}\
}
***************************************************************************************************************************/

//增加测试方法
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
	std::unordered_map<std::wstring, FUNC>                       m_mapTestFunctions; // <函数名字符串, 函数指针>
	std::unordered_map<std::wstring, CUnitTestCaseBase*>          m_mapTestClasses;   // <类名字符串, 类实例指针>

	std::unordered_map<std::wstring, bool>                        m_mapResultBool;    // <类或函数名字符串, 整体执行结果>

	ClassMap m_mapResultString;  // <类名字符串, <类成员函数, 成员函数执行结果>>
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
