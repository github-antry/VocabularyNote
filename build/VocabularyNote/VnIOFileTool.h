#ifndef _VNIOFILE_H_
#define _VNIOFILE_H_

/********************************************************************
Description : 读写文件工具类
time        : 20190124
author      : andy
*********************************************************************/

#include "VnCommonDef.h"

using namespace std;

class CIOFileTool
{
public:	
    static int AppendByLine(const string& file, const string& content);

    static int ReadAllLine(list<string>& list, const string& file);
    static int SaveAllLine(const list<string>& list, const string& file);

private:
	static int AppendByLine(ofstream& out, const string& content);
};

#endif