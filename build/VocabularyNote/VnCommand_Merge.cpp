#include <iostream>
#include <fstream>
#include <sstream>


#include "VnCommand_Merge.h"
#include "VnCommonDef.h"
#include "VnIOFileTool.h"
#include "VnVersatileTool.h"

#include "AwOSTool.h"
#include "ParserDom.h"
using namespace htmlcxx;

#define DL_BEGIN(out)  { WriteToHtml_DL_DEGIN(out);
#define DL_END(out)   WriteToHtml_DL_END(out);}


CVnMerge::CVnMerge(void)
{
}

CVnMerge::~CVnMerge(void)
{
	// LIST �ڴ��ͷ�
}


std::wstring string2wstring(std::string str)  
{  
	std::wstring result;  
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);  
	wchar_t* buffer = new wchar_t[len + 1];  
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);  
	buffer[len] = '\0';             //�����ַ�����β  
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

string UTF82WCS(const char* szU8)
{
	//Ԥת�����õ�����ռ�Ĵ�С;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//������'\0'
	wszString[wcsLen] = '\0';

	wstring wtmp = wszString;

	delete[] wszString;
	wszString = NULL;

	return wstring2string(wtmp);
}


void CVnMerge::Run(const struct _INSTRUCTIONS_ &ins)
{
	string file = "E:\\W009_GitHub\\GanttSchedule\\bookmarks_google.html";

	string tmp = readFileIntoString(file.c_str());
	string html = UTF82WCS(tmp.c_str());

	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

	tree<HTML::Node>::pre_order_iterator it = dom.begin();
	tree<HTML::Node>::pre_order_iterator end = dom.end();

	//��ǩ��	
	bool bRootTurned = false;
	CVnClassification *pH3Root = new CVnClassification;
	m_lstClassification.push_back(pH3Root);

	CVnClassification *pNewClassification = nullptr;
	CVnItem *pNewItem = nullptr;

	bool bLastNewIsClass = false;
	for (; it != end; ++it)
	{
		it->parseAttributes();

		string tmpText = it->text();
		string tmpTagName = it->tagName();

		if (strcmp(tmpTagName.c_str(), "H3") == 0 )
		{
			if(it->attribute("folder").first)
			{	
				pH3Root->m_add_date = it->attribute("date").second;
				pH3Root->m_last_modified = it->attribute("modified").second;
				pH3Root->m_personal_toolbar_folder = it->attribute("folder").second;

				bRootTurned = true;
			}
			else
			{				
				pNewClassification = new CVnClassification;
				m_lstClassification.push_back(pNewClassification);

				pNewClassification->m_add_date = it->attribute("date").second;
				pNewClassification->m_last_modified = it->attribute("modified").second;

				bLastNewIsClass = true;
			}
		}
		else if (strcmp(tmpTagName.c_str(), "A") == 0 )
		{
			pNewItem = new CVnItem;
			pNewItem->m_href = it->attribute("href").second;
			pNewItem->m_add_date = it->attribute("date").second;

			if(pNewClassification)
			{
				pNewClassification->AddNode(pNewItem);
			}
			else
			{
				pH3Root->AddNode(pNewItem);
			}			

			bLastNewIsClass = false;
		}
		else if(!it->isTag() && !it->isComment())
		{
			if(pNewItem == nullptr && pNewClassification == nullptr)
			{
				if(bRootTurned && pH3Root->m_label.empty() && pH3Root->m_label.size() == 0)
				{
					pH3Root->m_label = tmpText;
				}
			}
			else
			{
				if(!bLastNewIsClass)
				{
					if(pNewItem->m_label.empty())
					{
						pNewItem->m_label = tmpText;
					}
				}
				else
				{
					if(pNewClassification->m_label.empty())
					{
						pNewClassification->m_label = tmpText;
					}
				}
			}
		}
		else
		{

		}
	}

	std::cout << dom << endl;
}

string CVnMerge::readFileIntoString(const char * filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
	{
		buf.put(ch);
	}
	return buf.str();
}

void CVnMerge::WriteToHtml()
{
	string file = ".\\result.html";
	ofstream result;
	result.open(file, ios::out | ios::trunc);

	WriteToHtml_Header(result);

	DL_BEGIN(result)
		WriteToHtml_DT_H3(result, 1438587971, 1547521805, true, "��ǩ��");

	DL_BEGIN(result)
		WriteToHtml_DT_A(result, "http://192.168.1.202:8080/wiki/index.php", 1496796886, "���ô���·�� - CAXA");

	WriteToHtml_DT_H3(result, 1547521416, 1547521446, false, "Ӥ�׶����");
	DL_BEGIN(result)
		WriteToHtml_DT_A(result, "https://www.19lou.com/forum-16-thread-18478769-1-1.html", 1542092867, "һ���Źؽڷ���������ͯ����ҽʷ�澭���ܽ�");
	WriteToHtml_DT_A(result, "http://www.duokan.com/book/158235", 1525230912, "���ְ���ĸ�ǰ��ѵ");
	DL_END(result)

		DL_END(result)

		DL_END(result)
}

void CVnMerge::WriteToHtml_Header(ofstream &result)
{
	result << "<!DOCTYPE NETSCAPE-Bookmark-file-1>"<<endl;
	result << "<!-- This is an automatically generated file.\
			  It will be read and overwritten.\
			  DO NOT EDIT! -->"<<endl;
	result << "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\">"<<endl;
	result << "<TITLE>Bookmarks</TITLE>"<<endl;
	result << "<H1>Bookmarks</H1>"<<endl;
}

void CVnMerge::WriteToHtml_DT_H3(ofstream &result, long add_date,
	long last_modified,
	bool toolbar_folder,
	string text)
{
	result<< "<DT><H3"

		<< " ADD_DATE=\""
		<< add_date
		<< "\""

		<< " LAST_MODIFIED=\""
		<< last_modified
		<< "\"";

	if (toolbar_folder)
	{
		result << " PERSONAL_TOOLBAR_FOLDER=\""
			<< toolbar_folder
			<< "\"";
	}

	result << ">"
		<< text
		<< "</H3>"<<endl;
}

void CVnMerge::WriteToHtml_DT_A(ofstream &result,
	string href,
	long date,
	string text)
{
	result << "<DT><A"
		<< " HREF=\""
		<< href
		<< "\""

		<< " ADD_DATE=\""
		<< date
		<< "\""

		<< ">"
		<< text
		<< "</A>"<<endl;
}

void CVnMerge::WriteToHtml_DL_DEGIN(ofstream &result)
{
	result << "<DL><p>"<<endl;
}

void CVnMerge::WriteToHtml_DL_END(ofstream &result)
{
	result << "</DL><p>"<<endl;
}


//////////////////////////////////////////////////////////////
//                 CVnItem
//////////////////////////////////////////////////////////////

CVnItem::CVnItem()
{
}

CVnItem::~CVnItem()
{
}


//////////////////////////////////////////////////////////////
//                CVnClassification
//////////////////////////////////////////////////////////////

CVnClassification::CVnClassification()
{
}

CVnClassification::~CVnClassification()
{
	// LIST �ڴ��ͷ�
}

std::list<CVnItem *> CVnClassification::GetChildren()
{
	return m_lstChild;
}

void CVnClassification::AddNode(CVnItem *_node)
{
	m_lstChild.push_back(_node);
}