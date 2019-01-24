#ifndef _VNCOMMAND_ADD_H_
#define _VNCOMMAND_ADD_H_

/********************************************************************
Description : add 
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommand.h"
#include "VnCommonDef.h"

class CVnAdd : public CVnCommand
{
public:
	CVnAdd(void);
	~CVnAdd(void);

	virtual void Run(const struct _INSTRUCTIONS_ &ins) override; 

};

#endif