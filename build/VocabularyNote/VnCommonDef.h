/********************************************************************
Description : 通用较多的头文件定义
time        : 20190120
author      : andy
*********************************************************************/
#ifndef _VNCOMMONDEF_H_
#define _VNCOMMONDEF_H_

#include <assert.h>
#include <list>
#include <map>
#include <algorithm>
#include <string>

#ifndef _UNICODE
#define tstring string
#else
#define tstring wstring
#endif

//参数
typedef struct _PARAMETER_
{
    std::tstring option;
	std::tstring arguments;
}VnPARAMETER;

//指令
typedef struct _INSTRUCTIONS_
{
	int index;//命令

	std::list<VnPARAMETER>  lstParam;

}VnINSTRUCTIONS;

//所有指令
typedef enum _COMMAND_SET_INDEX_
{
	VnNONE = 1,
	VnADD,
	VnDELETE,
	VnMODIFY,
	VnVIEW,
	VnQuit
}COMMAND_SET_INDEX;

#endif