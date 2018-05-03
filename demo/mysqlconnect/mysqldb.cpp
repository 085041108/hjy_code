#include "mysqldb.h"

mysqlDb::mysqlDb()
{
	m_pMyData = mysql_init((MYSQL *)0);
	m_pUnix_socket = NULL; 
	m_nClient_flag = 0;
}
 
mysqlDb::~mysqlDb()
{
	memset(m_chUser, 0, TEMP_BUF_LEN);
	memset(m_chPassword, 0, TEMP_BUF_LEN);
	memset(m_chDbName, 0, TEMP_BUF_LEN);
	memset(m_chHost, 0, TEMP_BUF_LEN);
	if(m_pMyData!=NULL)
		mysql_close(m_pMyData);
}

//初始化连接Mysql数据库的参数
void mysqlDb::Init(char *strHost, char* strUser, char* strPwd, char* strDbName,unsigned int Port)
{
	strcpy(m_chHost, strHost);
	strcpy(m_chUser, strUser);
	strcpy(m_chPassword, strPwd);
	strcpy(m_chDbName, strDbName);
	m_nPort = Port; 	
}

//连接mysql数据库
bool mysqlDb::mysql_conn()
{
	if(m_pMyData==NULL)
	{
//		sprintf(m_sMsg, "Mysql Database mysql_init failed");
	    return false;
	}
	
    if(mysql_real_connect(m_pMyData, m_chHost,m_chUser,m_chPassword,m_chDbName,m_nPort,m_pUnix_socket,m_nClient_flag)==NULL)
	{
//		sprintf(m_sMsg, "Mysql Database connection failed");
		string strError;
		strError.assign(mysql_error(m_pMyData));
	    return false;
	}
	else 
	{
		mysql_query(m_pMyData,"SET NAMES 'utf8'");
		return true;
	}	
}

//判断是否连接mysql数据库
bool mysqlDb::isConnected()					
{
	if(mysql_ping(m_pMyData)==0)
		return true; 
	else
		return false;
}

//重新连接数据库
bool mysqlDb::mysql_reConn()                  
{
	if(m_pMyData!=NULL)
		mysql_close(m_pMyData);
	
	m_pMyData = mysql_init((MYSQL *)0);
	m_pUnix_socket = NULL; 
	m_nClient_flag = 0;
	
	if(mysql_conn())
	{
//		sprintf(m_sMsg, "To connect to database success");
		return true;
	}
	else 
	{
//		sprintf(m_sMsg, "To connect to database failed");
		return false;
	}
}

int mysqlDb::ExecuteQuery(const char* sql, MYSQL_RES **m_res) {
    if(mysql_query(m_pMyData,sql) != 0) {
 //       LOG(ERROR) << " execute query sql failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);
	return -1;
    }
    *m_res = mysql_store_result(m_pMyData);
    if(*m_res==NULL) {
//       LOG(ERROR) << " store sql result failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);
	   mysql_free_result(*m_res);
       return -1;
    }
    return 0; 
}

int mysqlDb::Login(string user_name,string password) {
    int ret = CODE_DB_ERROR;
    int nRowCount=0;
	
    if (!isConnected()) {
        mysql_reConn();
    }

    char sql[1024];

    try {
        memset(sql, 0, 1024);
	    sprintf(sql, " select user_id, role_id from user_info where name='%s' and pwd='%s'", user_name.c_str(), password.c_str());
        printf("sql: %s\n", sql);
    if(-1 == ExecuteQuery(sql, &m_pResultSet)){
		return CODE_NOT_EXSITS;
	}
	if ((nRowCount = (int)mysql_num_rows(m_pResultSet)) == 0) {
//		LOG(WARNING) << " ExecuteQuery SQL Failed, Data m_row Count:" << nRowCount << sql;
	    mysql_free_result(m_pResultSet);
	    return CODE_NOT_EXSITS;
	}

    if (nRowCount != 1) {
        return CODE_INVALD_SQL_RES;
    }

     while ((m_row = mysql_fetch_row(m_pResultSet))) {
 //       res->user_id = std::atoi(m_row[0]);
 //       res->role_id = std::atoi(m_row[1]);
		  cout<< "aaaa";
	}

	mysql_free_result(m_pResultSet);
	} catch (...) {
//		LOG(WARNING) << " Set Farm Data Exception" ;
	}
	
	return CODE_OK;
}


/*
//执行Mysql数据库SQL语句
bool mysqlDb::ExecuteQuery(const char* sql)   
{
	if(!mysql_query(m_pMyData,sql))
	{
//		sprintf(m_sMsg, "ExecuteQuery SQL Success:%s",sql);
		return true;
	}
	else
	{
//		sprintf(m_sMsg, "ExecuteQuery SQL Failed:%s", sql);
		return false;
	}
}


bool mysqlDb::GetUserInfo(int tea_id, user_info_map &user_map)
{

	char sql[1024];
	bool ret=false;
	int nRowCount=0;
	
	if(!isConnected())
	{
		mysql_reConn();
	}
	if(!isConnected())
	{
//		sprintf(m_sMsg, "ExecuteQuery SQL Failed:%s",sql);	
		return ret;
	}
	

	try
	{
		memset(sql, 0, 1024);
		sprintf(sql, "select userid,schid,roleid,datetime,name,nation,identity,birtime,sex,telnumber,emailaddr,address,entertime,endtime,count,level from userinfo where teaid=%d", tea_id);

		if (mysql_query(m_pMyData, sql))
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed:%s",sql);	
			return ret;
		}
		m_pResultSet = mysql_store_result(m_pMyData);
		if (m_pResultSet == NULL)
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed, Can not store data into RESULTSET SQL:%s", sql);
			mysql_free_result(m_pResultSet);
			return ret;
		}
		if ((nRowCount = mysql_num_rows(m_pResultSet)) < 1)
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed, Data m_row Count:%d SQL:%s", nRowCount,sql);
			mysql_free_result(m_pResultSet);
			return ret;
		}

		while ((m_row = mysql_fetch_row(m_pResultSet)))
		{
			UserInfo user_info;
			user_info.tea_id = tea_id;
			if (m_row[0] != NULL)
				user_info.user_id = atoi(m_row[0]);

			if (m_row[1] != NULL)
				user_info.sch_id = atoi(m_row[1]);

			if (m_row[2] != NULL)
				user_info.role_id = atoi(m_row[2]);

			if (m_row[3] != NULL)
				user_info.put_datetime = atoi(m_row[3]);

			if (m_row[8] != NULL)
				user_info.user_name = m_row[4];

			if (m_row[4] != NULL)
				user_info.user_nation = m_row[5];

			if (m_row[5] != NULL)
				user_info.user_identity = m_row[6];

			if (m_row[6] != NULL)
				user_info.birth_date = atoi(m_row[7]);

			if (m_row[7] != NULL)
				user_info.user_sex = atoi(m_row[8]);

			if (m_row[8] != NULL)
				user_info.tel_number = m_row[9];

			if (m_row[9] != NULL)
				user_info.email_address = m_row[10];

			if (m_row[10] != NULL)
				user_info.user_address = m_row[11];

			if (m_row[11] != NULL)
				user_info.enter_time = atoi(m_row[12]);

			if (m_row[12] != NULL)
				user_info.end_time = atoi(m_row[13]);

			if (m_row[13] != NULL)
				user_info.class_count = atoi(m_row[14]);

			if (m_row[14] != NULL)
				user_info.user_level = atoi(m_row[15]);

			GetUserExtend(user_info.user_id, user_info);

			user_map[user_info.user_id] = user_info;
		}

		ret = true;
		mysql_free_result(m_pResultSet);
	}
	catch (...)
	{
//		sprintf(m_sMsg, "Set Farm Data Exception\n");
	}
	

	return ret;
}

bool mysqlDb::GetUserExtend(int user_id, UserInfo &user_info)
{

	char sql[1024];
	bool ret = false;
	int nRowCount = 0;

	if (!isConnected())
	{
		mysql_reConn();
	}
	if (!isConnected())
	{
		//		sprintf(m_sMsg, "ExecuteQuery SQL Failed:%s",sql);	
		return ret;
	}

	try
	{
		memset(sql, 0, 1024);
		sprintf(sql, "select ifbase,baselatin,baseballet,basefolk,baseother,ifwork,worklatin,workballet,workfolk,workother,ifcompany,count,futurework,futercompany from userextend  where userid=%d", user_id);

		if (mysql_query(m_pMyData, sql))
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed:%s",sql);	
			return ret;
		}
		MYSQL_RES *pResultSet = mysql_store_result(m_pMyData);
		if (pResultSet == NULL)
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed, Can not store data into RESULTSET SQL:%s", sql);
			mysql_free_result(pResultSet);
			return ret;
		}
		if ((nRowCount = mysql_num_rows(pResultSet)) < 1)
		{
			//		sprintf(m_sMsg, "ExecuteQuery SQL Failed, Data m_row Count:%d SQL:%s", nRowCount,sql);
			mysql_free_result(pResultSet);
			return ret;
		}

		m_row = mysql_fetch_row(pResultSet);

		if (m_row[0] != NULL)
			user_info.if_base = atoi(m_row[0]);

		if (m_row[1] != NULL)
			user_info.base_latin = atoi(m_row[1]);

		if (m_row[2] != NULL)
			user_info.base_ballet = atoi(m_row[2]);

		if (m_row[3] != NULL)
			user_info.base_folk = atoi(m_row[3]);

		if (m_row[4] != NULL)
			user_info.base_other = m_row[4];

		if (m_row[5] != NULL)
			user_info.if_work = atoi(m_row[5]);

		if (m_row[6] != NULL)
			user_info.work_latin = atoi(m_row[6]);

		if (m_row[7] != NULL)
			user_info.work_ballet = atoi(m_row[7]);

		if (m_row[8] != NULL)
			user_info.work_folk = atoi(m_row[8]);

		if (m_row[9] != NULL)
			user_info.work_other = m_row[9];

		if (m_row[10] != NULL)
			user_info.if_company = atoi(m_row[10]);

		if (m_row[11] != NULL)
			user_info.company_count = atoi(m_row[11]);

		if (m_row[12] != NULL)
			user_info.future_work = atoi(m_row[12]);

		if (m_row[13] != NULL)
			user_info.future_company = atoi(m_row[13]);

		ret = true;
		mysql_free_result(pResultSet);

		return ret;
	}
	catch (...)
	{
		//		sprintf(m_sMsg, "Set Farm Data Exception\n");
	}
}
*/