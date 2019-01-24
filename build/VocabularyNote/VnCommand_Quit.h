#ifndef _VNCOMMAND_QUIT_H_
#define _VNCOMMAND_QUIT_H_

/********************************************************************
Description : Quit 
time        : 20190120
author      : andy
*********************************************************************/
#pragma once

#include "VnCommand.h"
#include "VnCommonDef.h"

class CVnQuit : public CVnCommand
{
public:
	CVnQuit(void);
	~CVnQuit(void);

	virtual void Run(const struct _INSTRUCTIONS_ &ins) override; 
};

#endif
