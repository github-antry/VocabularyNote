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
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
    TCHAR* buffer = new TCHAR[len + 1];  
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);  
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值  
    result.append(buffer);  
    delete[] buffer;  
    return result;  
}  
  
//将wstring转换成string  
string wstring2string(wstring wstr)  
{  
    string result;  
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);  
    char* buffer = new char[len + 1];  
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);  
    buffer[len] = '\0';  
    //删除缓冲区并返回值  
    result.append(buffer);  
    delete[] buffer;  
    return result;  
}