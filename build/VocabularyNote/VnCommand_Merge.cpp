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
}

void CVnMerge::Run(const struct _INSTRUCTIONS_ &ins)
{
	string file = "E:\\W009_GitHub\\GanttSchedule\\bookmarks_google - 副本.html";

	string html = readFileIntoString(file.c_str());
	//string html = UTF8ToGBK(tmp.c_str());

	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

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
		WriteToHtml_DT_H3(result, 1438587971, 1547521805, true, "书签栏");

	DL_BEGIN(result)
		WriteToHtml_DT_A(result, "http://192.168.1.202:8080/wiki/index.php", 1496796886, "常用代码路径 - CAXA");

	WriteToHtml_DT_H3(result, 1547521416, 1547521446, false, "婴幼儿相关");
	DL_BEGIN(result)
		WriteToHtml_DT_A(result, "https://www.19lou.com/forum-16-thread-18478769-1-1.html", 1542092867, "一个髋关节发育不良儿童的求医史兼经验总结");
	WriteToHtml_DT_A(result, "http://www.duokan.com/book/158235", 1525230912, "新手爸妈的岗前培训");
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