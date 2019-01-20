// VocabularyNote.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream> 
#include<string> 
#include <Windows.h>

#include "VnInstructionParser.h"
#include "VnCommandFactory.h"
#include "VnCommand.h"

using namespace std;

wstring string2wstring(string str);
string wstring2string(wstring wstr);

int _tmain(int argc, _TCHAR* argv[])
{
	do
	{
		std::string input;
		getline(cin, input);

		std::wstring wInput = string2wstring(input);

		CVnInstructionParser parser;
		VnINSTRUCTIONS ins = parser.Parse(wInput);

		CVnCommandFactory factory;
		CVnCommand* pCmd = factory.Create(ins.index);

		pCmd->Run(ins);

	}while(true);

	return 0;
}


wstring string2wstring(string str)  
{  
    wstring result;  
    //��ȡ��������С��������ռ䣬��������С���ַ�����  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
    TCHAR* buffer = new TCHAR[len + 1];  
    //���ֽڱ���ת���ɿ��ֽڱ���  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);  
    buffer[len] = '\0';             //����ַ�����β  
    //ɾ��������������ֵ  
    result.append(buffer);  
    delete[] buffer;  
    return result;  
}  
  
//��wstringת����string  
string wstring2string(wstring wstr)  
{  
    string result;  
    //��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);  
    char* buffer = new char[len + 1];  
    //���ֽڱ���ת���ɶ��ֽڱ���  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);  
    buffer[len] = '\0';  
    //ɾ��������������ֵ  
    result.append(buffer);  
    delete[] buffer;  
    return result;  
}