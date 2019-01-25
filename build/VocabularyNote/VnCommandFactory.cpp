#include "VnCommandFactory.h"
#include "VnCommand.h"
#include "VnCommandSet.h"
#include "VnCommonDef.h"
#include "VnCommand_Add.h"
#include "VnCommand_Quit.h"

CVnCommandFactory::CVnCommandFactory(void)
{
}

CVnCommandFactory::~CVnCommandFactory(void)
{
}

CVnCommand *CVnCommandFactory::Create(const tstring &_cmd)
{
	int index = CVnCommandSet::GetCommandIndex(_cmd);
	return Create(index);
}

CVnCommand *CVnCommandFactory::Create(const int &_index)
{
	CVnCommand *pCmd = nullptr;

	switch (_index)
	{
	case VnADD:
	{
		pCmd = new CVnAdd();
	};	break;
	case VnDELETE:break;
	case VnMODIFY:break;
	case VnVIEW:break;
	case VnQUIT:
	{
		pCmd = new CVnQuit();
	};break;
	default:
		/*assert(false)*/;
	}

	return pCmd;
}
