/********************************************************************
Description : ����ָ�������
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommonDef.h"

class CVnInstructionParser
{
public:
	CVnInstructionParser(void);
	/*virtual*/ ~CVnInstructionParser(void);

	VnINSTRUCTIONS Parse(std::tstring);
};

