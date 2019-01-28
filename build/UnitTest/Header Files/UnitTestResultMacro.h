#pragma once

#include<unordered_map>


#define NOT_FAILURE     0
#define PASS            1
#define FAILURE        -1

/*
½â¾ö:Compiler Warning (level 1) C4503
*/
struct MapOfMemberFunction {
   std::unordered_map<std::wstring, int> member;
};

typedef std::unordered_map<std::wstring, MapOfMemberFunction>   ClassMap; 