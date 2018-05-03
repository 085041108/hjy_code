#include "../include/util.h"
#include <sstream>
#include "string"

int Util::Split(const std::string &str, char delimiter, std::vector<std::string> *result) {
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result->push_back(item);
    }
     return 0;
}

int Util::Trim(const std::string &src, std::string *out, char c) {
    int start_pos = 0;
    int length = src.size();

    for (std::string::const_iterator it = src.begin(); it != src.end(); it++) {
        if (*it != c) {
            break;
        }

        start_pos++;
        length--;
    }

    for (std::string::const_reverse_iterator it = src.rbegin(); it != src.rend(); it++) {
        if (*it != c) {
            break;
        }

        length--;
    }

    *out = src.substr(start_pos, length);

    return 0;
}

std::string Util::GetCurrTime() {
    time_t timep;  
    struct tm *p;  
    time(&timep);  
    p =localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  
  
    char time_c[1024];
    memset(time_c, 0, 1024);
    sprintf(time_c, "%d-%d-%d %d:%d:%d", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    std::string time_current(time_c);
    return time_current;
}

int32_t Util::GetRandomId() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec % 1000000000;
}

int32_t Util::GetMainCourseId(int32_t sch_id) {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec + sch_id;
}

int32_t Util::GetSubCourseId(int32_t sch_id, int32_t main_cour_id) {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec + sch_id + main_cour_id;
}