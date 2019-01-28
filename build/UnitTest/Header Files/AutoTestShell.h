#pragma once

#include "AutoTestCore.h"

class CAutoTestShell
{
public:
	CAutoTestShell(void){};
	~CAutoTestShell(void){};

	std::unordered_map<std::wstring, bool> Run(ClassMap* _result)
	{
		InsertUnitMethod();

		return CAutoTestCore::Instance()->Run(_result);
	}

private:
	void InsertUnitMethod();
};

