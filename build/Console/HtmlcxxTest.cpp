#include "HtmlcxxTest.h"
#include "ParserDom.h"

#include <string.h>
#include <iostream>

using namespace std;
using namespace htmlcxx;

#pragma comment(lib, "htmlcxx.lib")

CHtmlcxxTest::CHtmlcxxTest(void)
{
}


CHtmlcxxTest::~CHtmlcxxTest(void)
{
}

int CHtmlcxxTest::Test()
{
	//string html = "<html><body>hey</body></html>";
	//HTML::ParserDom parser;
	//tree<HTML::Node> dom = parser.parseTree(html);

	////Print whole DOM tree
	//cout << dom << endl;

	////Dump all links in the tree
	//tree<HTML::Node>::iterator it = dom.begin();
	//tree<HTML::Node>::iterator end = dom.end();
	//for (; it != end; ++it)
	//{
	//	if (strcmp(it->tagName().c_str(), "A") == 0)
	//	{
	//		it->parseAttributes();
	//		cout << it->attribute("href").second << endl;
	//	}
	//}

	////Dump all text of the document
	//it = dom.begin();
	//end = dom.end();
	//for (; it != end; ++it)
	//{
	//	if ((!it->isTag()) && (!it->isComment()))
	//	{
	//		cout << it->text();
	//	}
	//}
	//cout << endl;

	return PASS;
}
