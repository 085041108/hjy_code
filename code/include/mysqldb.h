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

	/*���ݿ������ʼ������������*/
	bool Init();// ��ʼ������
	bool mysql_conn();                   													 //����mysql���ݿ�
	bool mysql_reConn();                													 //�����������ݿ�
  	int ExecuteQuery(const char* sql, MYSQL_RES **m_res);  											 //ִ��Mysql���ݿ�SQL���
  	int ExecuteInsert(const char* sql);  											 //ִ��Mysql���ݿ�SQL���
  	int ExecuteUpdate(const char* sql, int affect_num);  											 //ִ��Mysql���ݿ�SQL���
  	int ExecuteDelete(const char* sql);  											 //ִ��Mysql���ݿ�SQL���
	bool OpenResultSet(const char* sql); 													 //�򿪲�ѯ�Ľ����
	bool isConnected();																		 //�ж��Ƿ�����mysql���ݿ�
	int Login(LoginReq req, LoginRes& res);
	int Register(RegisterReq &req, RegisterRes* res);
	int ShowMainCour(ShowMainCourReq req, ShowMainCourRes& res);
	int PubMainCour(PubMainCourReq req, PubMainCourRes& res);

private:		
	MYSQL        *m_pMyData;                      //mysql_init() ����ֵ����mysql_close()���ͷ�
        MYSQL_RES    *m_pResultSet;                   //�����
        MYSQL_FIELD  *m_pFd;						   //����
	MYSQL_ROW 	 m_row;                          //��ֵ

	std::string   m_host;                        //����mysql���ݿ������
	std::string   m_user;                        //����mysql���ݿ������
	std::string   m_pwd;                        //����mysql���ݿ������
	std::string   m_db_name;                        //����mysql���ݿ������
	unsigned int  m_port;                         //mysql�����˿�
	const char   *m_pUnix_socket;                 //unix_socket����NULL�����ַ���������Ӧʹ�õ��׽��ֻ������ܵ���ע�⣬��host���������������ӵ����͡� 
	unsigned int m_nClient_flag;                  //client_flag��ֵͨ��Ϊ0
};
#endif
