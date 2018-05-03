#ifndef INCLUDE_UTIL_H
#define INCLUDE_UTIL_H

#include <string>
#include <sys/time.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

class Util{
public:
   static int Split(const std::string &str, char delimiter, std::vector<std::string> *result);
   static int Trim(const std::string &src, std::string *out, char c = '\n');
   static std::string GetCurrTime();
   static int32_t GetRandomId();
   static int32_t GetMainCourseId(int32_t sch_id);
   static int32_t GetSubCourseId(int32_t sch_id, int32_t main_cour_id);
};

#endif
