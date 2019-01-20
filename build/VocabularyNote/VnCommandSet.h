/********************************************************************
Description : 所有指令合集及其索引定义
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommonDef.h"

using namespace std;

class CVnCommandSet
{
public:
	CVnCommandSet(void);
	~CVnCommandSet(void);

	static COMMAND_SET_INDEX GetCommandIndex(const tstring& _cmd);
	static COMMAND_SET_INDEX GetCommandIndex(const int& _cmd);

protected:
	static void Initialize();

private:
	static map<tstring, int>  m_mapCommand;	
};

