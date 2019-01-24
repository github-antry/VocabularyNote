#include <sstream>
#include <iostream>
#include <fstream>
#include <ostream>

#include "VnIOFileTool.h"

int CIOFileTool::AppendByLine(ofstream& out, const string& content)
{
	out<<content<<endl;

	return 1;
}

int CIOFileTool::AppendByLine(const string& file, const string& content)
{
	ofstream out;
	out.open(file, ios::app);
	if (!out.is_open())
	{
		cout << "open File Failed." << endl;
		return 1;
	}

	out<<content<<endl;

	out.close();

	return 1;
}

int CIOFileTool::ReadAllLine(list<string>& list, const string& file)
{
	ifstream in;
	in.open(file, ios::in);
	if (!in.is_open())
	{
		cout << "open File Failed." << endl;
		return 1;
	}
		
	string line;
	while(getline(in, line))
	{
		list.push_back(line);
	} 

	in.close();

	return 1;
}


int CIOFileTool::SaveAllLine(const list<string>& list, const string& file)
{
	ofstream out;
	out.open(file, ios::trunc);
	if (!out.is_open())
	{
		cout << "open File Failed." << endl;
		return 1;
	}

	for(auto itr=list.begin(); itr!=list.end(); ++itr)
	{
		AppendByLine(out, *itr);
	}

	out.close();

	return 1;
}
