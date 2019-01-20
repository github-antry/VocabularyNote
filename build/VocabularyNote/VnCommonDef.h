/********************************************************************
Description : ͨ�ý϶��ͷ�ļ�����
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

//����
typedef struct _PARAMETER_
{
    std::tstring option;
	std::tstring arguments;
}VnPARAMETER;

//ָ��
typedef struct _INSTRUCTIONS_
{
	int index;//����

	std::list<VnPARAMETER>  lstParam;

}VnINSTRUCTIONS;

//����ָ��
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