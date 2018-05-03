#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include <string>
#include <glog/logging.h>

class GlobalConfig {
public:
    static std::string g_db_host;
    static std::string g_db_user;
    static std::string g_db_password;
    static std::string g_db_name;
    static int g_db_port;

    static int Init(const std::string& path);
    static int InitLog();
    static int ReadConf(const std::string& path);

};

#endif
