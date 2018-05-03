#ifndef _MYSQLDB_H
#define _MYSQLDB_H
#include <mysql.h>
#include "data_define.h"
#include "util.h"
#include "../gen-cpp/HjyService.h"
#include <glog/logging.h>

#define TEMP_BUF_LEN  64

class mysqlDb
{
public:
    mysqlDb(std::string host, unsigned int port, std::string user, std::string pwd, std::string db) {
printf("begin");
        m_host = host;        
        m_port = port;        
        m_user = user;        
        m_pwd  = pwd;        
        m_db_name  = db;        
	m_pMyData = mysql_init((MYSQL *)0);
	m_pUnix_socket = NULL; 
	m_nClient_flag = 0;
    }
	~mysqlDb();

	/*数据库参数初始化及基础操作*/
	bool Init();// 初始化参数
	bool mysql_conn();                   													 //连接mysql数据库
	bool mysql_reConn();                													 //重新连接数据库
  	int ExecuteQuery(const char* sql, MYSQL_RES **m_res);  											 //执行Mysql数据库SQL语句
  	int ExecuteInsert(const char* sql);  											 //执行Mysql数据库SQL语句
  	int ExecuteUpdate(const char* sql, int affect_num);  											 //执行Mysql数据库SQL语句
  	int ExecuteDelete(const char* sql);  											 //执行Mysql数据库SQL语句
	bool OpenResultSet(const char* sql); 													 //打开查询的结果集
	bool isConnected();																		 //判断是否连接mysql数据库
	int Login(LoginReq req, LoginRes& res);
	int Register(RegisterReq &req, RegisterRes* res);
	int ShowMainCour(ShowMainCourReq req, ShowMainCourRes& res);
	int PubMainCour(PubMainCourReq req, PubMainCourRes& res);

private:		
	MYSQL        *m_pMyData;                      //mysql_init() 返回值，在mysql_close()中释放
        MYSQL_RES    *m_pResultSet;                   //结果集
        MYSQL_FIELD  *m_pFd;						   //列名
	MYSQL_ROW 	 m_row;                          //列值

	std::string   m_host;                        //运行mysql数据库的主机
	std::string   m_user;                        //运行mysql数据库的主机
	std::string   m_pwd;                        //运行mysql数据库的主机
	std::string   m_db_name;                        //运行mysql数据库的主机
	unsigned int  m_port;                         //mysql主机端口
	const char   *m_pUnix_socket;                 //unix_socket不是NULL，该字符串描述了应使用的套接字或命名管道。注意，“host”参数决定了连接的类型。 
	unsigned int m_nClient_flag;                  //client_flag的值通常为0
};
#endif
