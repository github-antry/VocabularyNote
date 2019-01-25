#include "VnCommand_Add.h"
#include "VnCommonDef.h"
#include "VnIOFileTool.h"
#include "VnVersatileTool.h"
#include "include/AwOSTool.h"
#include "include/testLib.h"

#pragma comment(lib, "AwUltilities.lib")
#pragma comment(lib, "test.lib")


using namespace std;

CVnAdd::CVnAdd(void)
{
}


CVnAdd::~CVnAdd(void)
{
}

void CVnAdd::Run(const struct _INSTRUCTIONS_ &ins)
{
	TestDLL(2);

	string vnFile;
	int nRet;// = GetAwOSToolInstance()->GetCurrentWorkDir(vnFile);;
	if(nRet >= 0)
	{
		vnFile += "\\VacabularyNote.DAT";

		for(auto itr=ins.lstParam.begin(); itr!=ins.lstParam.end(); ++itr)
		{
			CIOFileTool::AppendByLine(vnFile, CVersatileTool::wstring2string(itr->option));
		}
	}
}
