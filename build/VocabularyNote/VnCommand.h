#ifndef _VNCOMMAND_H_
#define _VNCOMMAND_H_

/********************************************************************
Description : 
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommonDef.h"


class CVnCommand
{
public:
	CVnCommand(void);
	virtual ~CVnCommand(void);

	virtual void Run(const struct _INSTRUCTIONS_ &ins);
};

#endif