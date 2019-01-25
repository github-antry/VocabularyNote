// VocabularyNote.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream> 
#include<string> 
#include <Windows.h>

#include "VnInstructionParser.h"
#include "VnCommandFactory.h"
#include "VnCommand.h"
#include "VnVersatileTool.h"

using namespace std;

bool g_bExit = false;

int _tmain(int argc, _TCHAR* argv[])
{

	do
	{
		cout<<">>";
		std::string input;
		getline(cin, input);

		std::wstring wInput = CVersatileTool::string2wstring(input);

		CVnInstructionParser parser;
		VnINSTRUCTIONS ins = parser.Parse(wInput);

		CVnCommandFactory factory;
		CVnCommand* pCmd = factory.Create(ins.index);

		if(pCmd == nullptr)
		{
			cout<<"Invalid Input!"<<endl;
			continue;
		}

		pCmd->Run(ins);

	}while(!g_bExit);

	return 0;
}
