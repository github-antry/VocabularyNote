#ifndef _VNVERSATILETOOL_H_
#define _VNVERSATILETOOL_H_


/********************************************************************
Description : 通用工具类
time        : 20190124
author      : andy
*********************************************************************/
#pragma once

#include <Windows.h>
#include "VnCommonDef.h"

class CVersatileTool
{
public:
	CVersatileTool(void);
	~CVersatileTool(void);

	static wstring string2wstring(string str);
	static string wstring2string(wstring wstr);
};


#endif
