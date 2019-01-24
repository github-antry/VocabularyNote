#include <sstream>
#include <iostream>
#include <fstream>
#include <ostream>

#include "VnInstructionParser.h"
#include "VnVersatileTool.h"
#include "VnCommandSet.h"

using namespace std;


CVnInstructionParser::CVnInstructionParser(void)
{
}


CVnInstructionParser::~CVnInstructionParser(void)
{
}

VnINSTRUCTIONS CVnInstructionParser::Parse(std::tstring input)
{
	VnINSTRUCTIONS tmp;
	tmp.index = VnNONE;

	string strline = CVersatileTool::wstring2string(input);
	stringstream ss;
	ss << strline;

	string  oper;
	ss>>oper;

	if(!oper.empty())
	{
		oper.erase(0,oper.find_first_not_of(" "));
		oper.erase(oper.find_last_not_of(" ") + 1);

		tstring strTmp = CVersatileTool::string2wstring(oper);
		tmp.index = (int)CVnCommandSet::GetCommandIndex(strTmp);
	}
	
	VnPARAMETER param;	
	string opt;
	ss>>opt;
	if(!opt.empty())
	{
		param.option = CVersatileTool::string2wstring(opt);
	}

	string arg;
	ss>>arg;
	if(!arg.empty())
	{
		param.arguments = CVersatileTool::string2wstring(arg);
	}

	tmp.lstParam.push_back(param);

    return tmp;
}
