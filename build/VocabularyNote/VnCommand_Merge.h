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
	//���ļ����뵽string��
	string CVnMerge::readFileIntoString(const char *filename);

	void WriteToHtml(const std::list<CVnClassification *> &lstClassifyResult);
	void WriteToHtml_Header(ofstream &result);
	void WriteToHtml_DT_H3(ofstream &result,
						   string add_date,
						   string last_modified,
						   bool toolbar_folder,
						   string text);
	void WriteToHtml_DT_A(ofstream &result,
						  string href,
						  string date,
						  string text);
	void WriteToHtml_DL_DEGIN(ofstream &result);
	void WriteToHtml_DL_END(ofstream &result);

	int ParseHtmlString(const string &html,
						std::list<CVnClassification *> &lstClassification);

	int ParseHtmlFile(const string &file,
					  std::list<CVnClassification *> &lstClassification);

	void Merge(const std::list<CVnClassification *> &lstClassifyA,
			   const std::list<CVnClassification *> &lstClassifyB,
			   std::list<CVnClassification *> &lstClassifyResult);

  private:
};

#endif
