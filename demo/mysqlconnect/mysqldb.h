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

	/*���ݿ������ʼ������������*/
	void Init(char *strHost, char* strUser, char* strPwd, char* strDbName,unsigned int strPort);// ��ʼ������
	bool mysql_conn();                   													 //����mysql���ݿ�
	bool mysql_reConn();                													 //�����������ݿ�
  	int ExecuteQuery(const char* sql, MYSQL_RES **m_res);  													 //ִ��Mysql���ݿ�SQL���
	bool OpenResultSet(const char* sql); 													 //�򿪲�ѯ�Ľ����
	bool isConnected();																		 //�ж��Ƿ�����mysql���ݿ�
//	bool GetUserInfo(int tea_id, user_info_map &user_map);
//	bool GetUserExtend(int user_id, UserInfo &user_info);
	int Login(string user_name,string password);

private:		
	MYSQL        *m_pMyData;                      //mysql_init() ����ֵ����mysql_close()���ͷ�
    MYSQL_RES    *m_pResultSet;                   //�����
    MYSQL_FIELD  *m_pFd;						   //����
	MYSQL_ROW 	 m_row;                          //��ֵ


	char   m_chHost[TEMP_BUF_LEN];                        //����mysql���ݿ������
	char   m_chUser[TEMP_BUF_LEN];                    //mysql���ݿ���û���
	char   m_chPassword[TEMP_BUF_LEN];                //mysql���ݿ������
	char   m_chDbName[TEMP_BUF_LEN];                  //���ݿ�����
	unsigned int m_nPort;                         //mysql�����˿�
	const char   *m_pUnix_socket;                 //unix_socket����NULL�����ַ���������Ӧʹ�õ��׽��ֻ������ܵ���ע�⣬��host���������������ӵ����͡� 
	unsigned int m_nClient_flag;                  //client_flag��ֵͨ��Ϊ0
};
#endif