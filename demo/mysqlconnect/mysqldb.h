#ifndef _MYSQLDB_H
#define _MYSQLDB_H
#include "struct.h"

#define TEMP_BUF_LEN  64

class mysqlDb
{
public:
typedef enum {
    CODE_OK                          =  0,
    CODE_NOT_EXSITS                  =  -1001,
    CODE_INVALID_PARAS               =  -1002,
    CODE_TIME_OUT                    =  -1003,
    CODE_OTHER_ERROS                 =  -1004,
    CODE_INVALD_SQL_RES              =  -1005,
    CODE_DB_ERROR                    =  -1006,
    CODE_USER_ALREADY_EXSITS         =  -1007
}hjy_error_code;

	mysqlDb();
	~mysqlDb();

	/*数据库参数初始化及基础操作*/
	void Init(char *strHost, char* strUser, char* strPwd, char* strDbName,unsigned int strPort);// 初始化参数
	bool mysql_conn();                   													 //连接mysql数据库
	bool mysql_reConn();                													 //重新连接数据库
  	int ExecuteQuery(const char* sql, MYSQL_RES **m_res);  													 //执行Mysql数据库SQL语句
	bool OpenResultSet(const char* sql); 													 //打开查询的结果集
	bool isConnected();																		 //判断是否连接mysql数据库
//	bool GetUserInfo(int tea_id, user_info_map &user_map);
//	bool GetUserExtend(int user_id, UserInfo &user_info);
	int Login(string user_name,string password);

private:		
	MYSQL        *m_pMyData;                      //mysql_init() 返回值，在mysql_close()中释放
    MYSQL_RES    *m_pResultSet;                   //结果集
    MYSQL_FIELD  *m_pFd;						   //列名
	MYSQL_ROW 	 m_row;                          //列值


	char   m_chHost[TEMP_BUF_LEN];                        //运行mysql数据库的主机
	char   m_chUser[TEMP_BUF_LEN];                    //mysql数据库的用户名
	char   m_chPassword[TEMP_BUF_LEN];                //mysql数据库的密码
	char   m_chDbName[TEMP_BUF_LEN];                  //数据库名称
	unsigned int m_nPort;                         //mysql主机端口
	const char   *m_pUnix_socket;                 //unix_socket不是NULL，该字符串描述了应使用的套接字或命名管道。注意，“host”参数决定了连接的类型。 
	unsigned int m_nClient_flag;                  //client_flag的值通常为0
};
#endif