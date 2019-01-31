#ifndef _VNCOMMAND_MERGE_H_
#define _VNCOMMAND_MERGE_H_

/********************************************************************
Description : merge two google bookmarks in html format 
time        : 20190130
author      : andy
*********************************************************************/
#pragma once

#include "VnCommand.h"
#include "VnCommonDef.h"

class CVnItem
{
public:
	CVnItem();
	~CVnItem();

public:
	std::string m_add_date;
	std::string m_href;
	std::string m_label;
};

class CVnClassification
{
public:
	CVnClassification();
	~CVnClassification();

public:
	std::list<CVnItem *> GetChildren();
	void AddNode(CVnItem *_node);

public:
	std::string m_add_date;
	std::string m_last_modified;
	std::string m_personal_toolbar_folder;

	std::string m_label;

private:
	std::list<CVnItem *> m_lstChild;
};

class CVnMerge : public CVnCommand
{
public:
	CVnMerge(void);
	virtual ~CVnMerge(void);

	virtual void Run(const struct _INSTRUCTIONS_ &ins) override;

protected:
	//从文件读入到string里
	string CVnMerge::readFileIntoString(const char *filename);

	void WriteToHtml();
	void WriteToHtml_Header(ofstream &result);
	void WriteToHtml_DT_H3(ofstream &result, long add_date,
												 long last_modified,
												 bool toolbar_folder,
												 string text);
	void WriteToHtml_DT_A(ofstream &result,
												string href,
												long date,
												string text);
	void WriteToHtml_DL_DEGIN(ofstream &result);
	void WriteToHtml_DL_END(ofstream &result);

private:
	std::list<CVnClassification *> m_lstClassification;
};

#endif
