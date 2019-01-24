#ifndef _VNCOMMANDFACTORY_H_
#define _VNCOMMANDFACTORY_H_


/********************************************************************
Description : ����ָ����󴴽�����
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommonDef.h"

using namespace std;

class CVnCommand;
class CVnCommandFactory
{
public:
	CVnCommandFactory(void);
	~CVnCommandFactory(void);

	CVnCommand* Create(const tstring& _cmd);
	CVnCommand* Create(const int& _index);
};

#endif
