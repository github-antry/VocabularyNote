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
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
	wchar_t* buffer = new wchar_t[len + 1];  
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);  
	buffer[len] = '\0';             //����ַ�����β  
	//ɾ��������������ֵ  
	result.append(buffer);  
	delete[] buffer;  
	return result;  
}  

//��wstringת����string  
std::string wstring2string(std::wstring wstr)  
{  
	std::string result;  
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


