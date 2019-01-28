#ifndef _AWOSTOOL_H_
#define _AWOSTOOL_H_



#define _STATIC_LIB_

#ifdef _STATIC_LIB_
#define DLL_API __declspec(dllexport)
#else
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#endif

#include <string>

class DLL_API IAwOSTool
{
public:
	virtual int GetCurrentWorkDir(std::string& dir) = 0;
	virtual int GetCurrentWorkDir(std::wstring& dir) = 0;
};

extern "C" DLL_API IAwOSTool*  GetAwOSToolInstance();

#ifdef DLL_EXPORTS
class CAwOSTool : public IAwOSTool
{
public:
	CAwOSTool(void);
	~CAwOSTool(void);

	int GetCurrentWorkDir(std::string& dir);
	int GetCurrentWorkDir(std::wstring& dir);

private:
	std::wstring string2wstring(std::string str);
	std::string wstring2string(std::wstring wstr);
};
#endif

#endif

