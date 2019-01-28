// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoTestShell.h"
#include <iostream>
#include <Windows.h>

using namespace std;

std::wstring string2wstring(std::string str);
std::string wstring2string(std::wstring wstr);

int _tmain(int argc, _TCHAR* argv[])
{
	CAutoTestShell autoTest;

	ClassMap resultString;
	std::unordered_map<std::wstring, bool> result = autoTest.Run(&resultString);

	int nIndex = 1;
	for(auto itr=result.begin(); itr!=result.end(); ++itr)
	{
		auto itrFind = resultString.find(itr->first);
		if(itrFind != resultString.end())
		{
			for(auto itrSub=itrFind->second.member.begin(); itrSub!=itrFind->second.member.end(); ++itrSub)
			{
			    cout<<nIndex++<<"\t"
					<<wstring2string(itr->first)
					<<"::"
					<<wstring2string(itrSub->first)<<"\t"
					<<wstring2string(itrSub->second ? L"pass." : L"failed !!!")<<endl;
			}
		}
	}

	system("pause");

	return 0;
}



std::wstring string2wstring(std::string str)  
{  
	std::wstring result;  
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
	wchar_t* buffer = new wchar_t[len + 1];  
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);  
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);  
	delete[] buffer;  
	return result;  
}  

//将wstring转换成string  
std::string wstring2string(std::wstring wstr)  
{  
	std::string result;  
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


