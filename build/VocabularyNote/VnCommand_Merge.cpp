#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <time.h>

#include "VnCommand_Merge.h"
#include "VnCommonDef.h"
#include "VnIOFileTool.h"
#include "VnVersatileTool.h"

#include "AwOSTool.h"
#include "ParserDom.h"
using namespace htmlcxx;

#define DL_BEGIN(out) \
	{                 \
		WriteToHtml_DL_DEGIN(out);
#define DL_END(out)          \
	WriteToHtml_DL_END(out); \
	}

#define MAX_PATH 260

CVnMerge::CVnMerge(void)
{
}

CVnMerge::~CVnMerge(void)
{
	// LIST 内存释放
}

std::wstring string2wstring(std::string str)
{
	std::wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	wchar_t *buffer = new wchar_t[len + 1];
	//多字节编码转换成宽字节编码
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0'; //添加字符串结尾
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
	char *buffer = new char[len + 1];
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值
	result.append(buffer);
	delete[] buffer;
	return result;
}

string UTF82WCS(const char *szU8)
{
	//预转换，得到所需空间的大小;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t *wszString = new wchar_t[wcsLen + 1];

	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//最后加上'\0'
	wszString[wcsLen] = '\0';

	wstring wtmp = wszString;

	delete[] wszString;
	wszString = NULL;

	return wstring2string(wtmp);
}

std::string CVnMerge::GetDateTimeString()
{
	time_t tt = time(NULL);

	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d_%H_%M_%S",localtime(&tt) );

	string str;
	str = tmp;

	return std::move(str);
}

void CVnMerge::Run(const struct _INSTRUCTIONS_ &ins)
{
	std::string strPath = GetCurrentDir();

	std::list<std::string> lstFiles;
	GetAwOSToolInstance()->GetFiles(lstFiles, strPath, "html");
	for(auto itrFile=lstFiles.begin(); itrFile!=lstFiles.end(); ++itrFile)
	{
		std::list<CVnClassification *> lstClassify; //need to free memory
		ParseHtmlFile(*itrFile, lstClassify);
		Mix(lstClassify);
	}

	if(m_lstResult.size() > 0)
	{
		WriteToHtml(m_lstResult, strPath+"\\bookmark_merge_"+GetDateTimeString()+".html");
	}
}

void CVnMerge::Mix(const std::list<CVnClassification *> &lstClassify)
{
	for(auto itrClassify=lstClassify.begin(); itrClassify!=lstClassify.end(); ++itrClassify)	
	{
		CVnClassification* pClassify = FindInMap(**itrClassify);
		if(pClassify == nullptr)
		{
			pClassify = NewToMap(**itrClassify);
			m_lstResult.push_back(pClassify);
		}

		assert(pClassify != nullptr);

		std::list<CVnItem*> lstItem = (*itrClassify)->GetChildren();
		for(auto itrItem=lstItem.begin(); itrItem!=lstItem.end(); ++itrItem)
		{
			if(FindInMap(**itrItem))
			{
				continue;
			}
			else
			{
				CVnItem* pNewItem =  NewToMap(**itrItem);
				assert(pNewItem != nullptr);

				pClassify->AddNode(pNewItem);
			}
		}

	}
}

CVnItem* CVnMerge::NewToMap(const CVnItem& _item)
{
	CVnItem* pItem = new CVnItem;
	*pItem = _item;

	std::string key = pItem->m_href;
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	m_mapItem.insert(std::make_pair(key, pItem));

	return pItem;
}

bool CVnMerge::FindInMap(const CVnItem &_item)
{
	std::string key = _item.m_href;
	transform(key.begin(), key.end(), key.begin(), ::tolower);

	auto itrFind = m_mapItem.find(key);
	if(itrFind != m_mapItem.end())
	{
		return true;
	}

	return false;
}

CVnClassification *CVnMerge::NewToMap(const CVnClassification& _classify)
{
	CVnClassification *pClassify = new CVnClassification;
	pClassify->m_add_date = _classify.m_add_date;
	pClassify->m_label = _classify.m_label;
	pClassify->m_last_modified = _classify.m_last_modified;
	pClassify->m_personal_toolbar_folder = _classify.m_personal_toolbar_folder;

	std::string key = pClassify->m_label;
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	m_mapClassify.insert(std::make_pair(key, pClassify));

	return pClassify;
}

CVnClassification *CVnMerge::FindInMap(const CVnClassification &_classify)
{
	std::string key = _classify.m_label;
	transform(key.begin(), key.end(), key.begin(), ::tolower);

	auto itrFind = m_mapClassify.find(key);
	if (itrFind != m_mapClassify.end())
	{
		return itrFind->second;
	}

	return nullptr;
}

void CVnMerge::RemoveMark(std::string& _text, const string _mark)
{
	std::string mark = _mark;
	unsigned int nSize = mark.size();
	while(1)
	{
		unsigned int pos = _text.find(mark);
		if(pos == string::npos)
		{
			return;
		}

		_text.erase(pos, nSize);
	}
}

void CVnMerge::Format(std::string& _text)
{
	RemoveMark(_text, "\r");
	RemoveMark(_text, "\n");
	RemoveMark(_text, " ");
}

int CVnMerge::ParseHtmlFile(const string &file,
							std::list<CVnClassification *> &lstClassification)
{
	string html = readFileIntoString(file.c_str());
	//string html = UTF82WCS(tmp.c_str());

	return ParseHtmlString(html, lstClassification);
}

int CVnMerge::ParseHtmlString(const string &html,
							  std::list<CVnClassification *> &lstClassification)
{
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

	tree<HTML::Node>::pre_order_iterator it = dom.begin();
	tree<HTML::Node>::pre_order_iterator end = dom.end();

	//书签栏
	bool bRootTurned = false;
	CVnClassification *pH3Root = new CVnClassification;
	lstClassification.push_back(pH3Root);

	CVnClassification *pNewClassification = nullptr;
	CVnItem *pNewItem = nullptr;

	bool bLastNewIsClass = false;
	for (; it != end; ++it)
	{
		it->parseAttributes();

		string tmpText = it->text();
		string tmpTagName = it->tagName();

		if (strcmp(tmpTagName.c_str(), "H3") == 0)
		{
			if (it->attribute("folder").first)
			{
				pH3Root->m_add_date = it->attribute("date").second;
				pH3Root->m_last_modified = it->attribute("modified").second;
				pH3Root->m_personal_toolbar_folder = it->attribute("folder").second;

				bRootTurned = true;
			}
			else
			{
				pNewClassification = new CVnClassification;
				lstClassification.push_back(pNewClassification);

				pNewClassification->m_add_date = it->attribute("date").second;
				pNewClassification->m_last_modified = it->attribute("modified").second;

				bLastNewIsClass = true;
			}
		}
		else if (strcmp(tmpTagName.c_str(), "A") == 0)
		{
			pNewItem = new CVnItem;
			pNewItem->m_href = it->attribute("href").second;
			pNewItem->m_add_date = it->attribute("date").second;

			if (pNewClassification)
			{
				pNewClassification->AddNode(pNewItem);
			}
			else
			{
				pH3Root->AddNode(pNewItem);
			}

			bLastNewIsClass = false;
		}
		else if (!it->isTag() && !it->isComment())
		{
			if (pNewItem == nullptr && pNewClassification == nullptr)
			{
				if (bRootTurned && pH3Root->m_label.empty() && pH3Root->m_label.size() == 0)
				{
					pH3Root->m_label = tmpText;
				}
			}
			else
			{
				Format(tmpText);

				if (!bLastNewIsClass)
				{
					if (pNewItem->m_label.empty())
					{
						pNewItem->m_label = tmpText;
					}
				}
				else
				{
					if (pNewClassification->m_label.empty())
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

	return 1;
}

string CVnMerge::readFileIntoString(const char *filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
	{
		buf.put(ch);
	}
	return buf.str();
}

std::string CVnMerge::GetCurrentDir()
{
	char buffer[MAX_PATH];
	_getcwd(buffer, MAX_PATH);

	std::string strPath = buffer;

	return std::move(strPath);
}

void CVnMerge::WriteToHtml(const std::list<CVnClassification *> &lstClassifyResult, const std::string _file)
{
	string file = _file;
	ofstream result;
	result.open(file, ios::out | ios::trunc);

	WriteToHtml_Header(result);

	DL_BEGIN(result)
	auto itrBookMarkBar = lstClassifyResult.begin();
	WriteToHtml_DT_H3(result, (*itrBookMarkBar)->m_add_date, (*itrBookMarkBar)->m_last_modified, true, (*itrBookMarkBar)->m_label);

	DL_BEGIN(result)
	std::list<CVnItem *> lstItem = (*itrBookMarkBar)->GetChildren();
	for (auto itrItem = lstItem.begin(); itrItem != lstItem.end(); ++itrItem)
	{
		WriteToHtml_DT_A(result, (*itrItem)->m_href, (*itrItem)->m_add_date, (*itrItem)->m_label);
	}

	auto itrClassify = lstClassifyResult.begin();
	for (++itrClassify; itrClassify != lstClassifyResult.end(); ++itrClassify)
	{
		WriteToHtml_DT_H3(result, (*itrClassify)->m_add_date, (*itrClassify)->m_last_modified, false, (*itrClassify)->m_label);
		DL_BEGIN(result)
		lstItem = (*itrClassify)->GetChildren();
		for (auto itrItem = lstItem.begin(); itrItem != lstItem.end(); ++itrItem)
		{
			WriteToHtml_DT_A(result, (*itrItem)->m_href, (*itrItem)->m_add_date, (*itrItem)->m_label);
		}
		DL_END(result)
	}

	DL_END(result)

	DL_END(result)

	result.close();
}

void CVnMerge::WriteToHtml_Header(ofstream &result)
{
	result << "<!DOCTYPE NETSCAPE-Bookmark-file-1>" << endl;
	result << "<!-- This is an automatically generated file.\
			  It will be read and overwritten.\
			  DO NOT EDIT! -->"
		   << endl;
	result << "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\">" << endl;
	result << "<TITLE>Bookmarks</TITLE>" << endl;
	result << "<H1>Bookmarks</H1>" << endl;
}

void CVnMerge::WriteToHtml_DT_H3(ofstream &result,
								 string add_date,
								 string last_modified,
								 bool toolbar_folder,
								 string text)
{
	result << "<DT><H3"

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
		   << "</H3>" << endl;
}

void CVnMerge::WriteToHtml_DT_A(ofstream &result,
								string href,
								string date,
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
		   << "</A>" << endl;
}

void CVnMerge::WriteToHtml_DL_DEGIN(ofstream &result)
{
	result << "<DL><p>" << endl;
}

void CVnMerge::WriteToHtml_DL_END(ofstream &result)
{
	result << "</DL><p>" << endl;
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
	// LIST 内存释放
}

std::list<CVnItem *> CVnClassification::GetChildren()
{
	return m_lstChild;
}

void CVnClassification::AddNode(CVnItem *_node)
{
	m_lstChild.push_back(_node);
}
