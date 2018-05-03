#include "../include/global_config.h"
#include "../include/util.h"
#include <map>
#include <fstream>
#include <stdlib.h>
using namespace std;
int         GlobalConfig::g_db_port;
std::string GlobalConfig::g_db_user;
std::string GlobalConfig::g_db_password;
std::string GlobalConfig::g_db_host;
std::string GlobalConfig::g_db_name;

int GlobalConfig::Init(const std::string& pPath) {
    return ReadConf(pPath);
}

int GlobalConfig::InitLog() {
    google::InitGoogleLogging("HJY_SERVER");
    FLAGS_log_dir = "./log";
    FLAGS_logbufsecs = 0;//实时刷新日志到硬盘，默认是会缓冲的  
    FLAGS_max_log_size = 1;//日志大小大于1M时，创建新的日志  
    FLAGS_stop_logging_if_full_disk = true;
    FLAGS_alsologtostderr = false;//关闭写日志到err。     
    return 0;
}

int GlobalConfig::ReadConf(const std::string& path) {
    std::ifstream fin;
    fin.open(path.c_str());
    if (!fin) {
        return -1;
     }
    std::map<std::string, std::string> conf_map;
    std::string line;
    while (getline(fin, line)) {
        std::string key;
        std::string value;
        std::vector<std::string> result;
        Util::Split(line, '=', &result);
        if (result.size() != 2) {
            //WARNING("split size is not 2, invalid line : ", line.c_str());
            return -1;
        }
        Util::Trim(result[0], &key, '\x20');
        Util::Trim(result[1], &value, '\x20');
        conf_map.insert(std::pair<std::string, std::string> (key, value.substr(0, value.size()-1)));
    }
   std::map <std::string, std::string>::iterator iter;
   iter = conf_map.find("USER");
   if (iter != conf_map.end()) { 
       g_db_user = iter->second; 
   } else { 
       return -1;
   }
        
   iter = conf_map.find("PWD");
   if (iter != conf_map.end()) { 
       g_db_password = iter->second; 
   } else { 
       return -1;
   }

   iter = conf_map.find("DB");
   if (iter != conf_map.end()) { 
       g_db_name = iter->second; 
   } else { 
       return -1;
   }
 
   iter = conf_map.find("HOST");
   if (iter != conf_map.end()) { 
       g_db_host = iter->second; 
   } else { 
       return -1;
   }
   
   iter = conf_map.find("PORT");
   if (iter != conf_map.end()) { 
       g_db_port = atoi(iter->second.c_str()); 
   } else { 
       return -1;
   }

   return 0;
}
