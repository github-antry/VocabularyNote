#include "VnCommandFactory.h"
#include "VnCommand.h"
#include "VnCommandSet.h"
#include "VnCommonDef.h"


CVnCommandFactory::CVnCommandFactory(void)
{
}


CVnCommandFactory::~CVnCommandFactory(void)
{
}

CVnCommand* CVnCommandFactory::Create(const tstring& _cmd)
{
	int index = CVnCommandSet::GetCommandIndex(_cmd);
	return Create(index);
}

CVnCommand* CVnCommandFactory::Create(const int& _index)
{
	CVnCommand* pCmd = nullptr;

	switch(_index)
	{
	case VnADD:;
	case VnDELETE:;
	case VnMODIFY:;
	case VnVIEW:;
	default:assert(false);
	}

	return pCmd;
}
