#include <algorithm>

#include "VnCommandSet.h"
#include "VnCommonDef.h"


map<tstring, int>  CVnCommandSet::m_mapCommand;

CVnCommandSet::CVnCommandSet(void)
{
}


CVnCommandSet::~CVnCommandSet(void)
{
}

COMMAND_SET_INDEX CVnCommandSet::GetCommandIndex(const tstring& _cmd)
{
	if(m_mapCommand.size() == 0)
	{
		Initialize();
	}

	tstring cmd = _cmd;

	transform(cmd.begin(), cmd.end(), cmd.begin(), ::towlower);
	
	auto itrFind = m_mapCommand.find(cmd);
	if(itrFind != m_mapCommand.end())
	{
		return static_cast<COMMAND_SET_INDEX>(itrFind->second);
	}

	return VnNONE;
}

COMMAND_SET_INDEX CVnCommandSet::GetCommandIndex(const int& _cmd)
{
	try
	{
		return static_cast<COMMAND_SET_INDEX>(_cmd);
	}
	catch(...)
	{
		return VnNONE;
	}
}


void CVnCommandSet::Initialize()
{
	m_mapCommand.insert(make_pair(L"add", VnADD));
	m_mapCommand.insert(make_pair(L"delete", VnDELETE));
	m_mapCommand.insert(make_pair(L"view", VnVIEW));
	m_mapCommand.insert(make_pair(L"modify", VnMODIFY));
	m_mapCommand.insert(make_pair(L"quit", VnQuit));
	m_mapCommand.insert(make_pair(L"q", VnQuit));
}