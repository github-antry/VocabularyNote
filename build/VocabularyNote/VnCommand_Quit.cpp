#include "VnCommand_Quit.h"

extern bool g_bExit;

CVnQuit::CVnQuit(void)
{
}


CVnQuit::~CVnQuit(void)
{
}

void CVnQuit::Run(const struct _INSTRUCTIONS_ &ins)
{
	g_bExit = true;
}
