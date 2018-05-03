#include "../include/mysqldb.h"
#include <stdio.h>    
#include <sys/time.h>  
 
mysqlDb::~mysqlDb() {
    if(m_pMyData!=NULL) {
        mysql_close(m_pMyData);
    }
}

bool mysqlDb::Init() {
    return mysql_conn();
}

bool mysqlDb::mysql_conn() {
    if(m_pMyData==NULL) {
        LOG(ERROR) << " Mysql Database mysql_init failed"<< ", msg: " << mysql_error(m_pMyData);
	return false;
    }
	
    if(mysql_real_connect(m_pMyData, m_host.data(), m_user.data(), m_pwd.data(), m_db_name.data(), m_port, m_pUnix_socket, m_nClient_flag) == NULL) {
        LOG(ERROR) << " Mysql Database mysql_real_connect failed"<< ", msg: " << mysql_error(m_pMyData);
	return false;
    } else {
	mysql_query(m_pMyData,"SET NAMES 'utf8'");
        LOG(INFO) << " Mysql Database connection succ";
	return true;
    }	
}

bool mysqlDb::isConnected() {
    if(mysql_ping(m_pMyData)==0) {
        return true; 
    } else {
        LOG(ERROR) << " Mysql is not connected";
	return false;
    }
}

bool mysqlDb::mysql_reConn() {
    if(m_pMyData!=NULL) {
        mysql_close(m_pMyData);
    }
    m_pMyData = mysql_init((MYSQL *)0);
    m_pUnix_socket = NULL; 
    m_nClient_flag = 0;
	
    if(mysql_conn()) {
        LOG(INFO) << " To connect to database success";
	return true;
    } else {
        LOG(ERROR) << " To connect to database failed. " << "msg: " << mysql_error(m_pMyData);
	return false;
    }
}

//Ö´ÐÐMysqlÊý¾Ý¿âSQLÓï¾ä
int mysqlDb::ExecuteQuery(const char* sql, MYSQL_RES **m_res) {
    if(mysql_query(m_pMyData,sql) != 0) {
        LOG(ERROR) << " execute query sql failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);
	return -1;
    }
    *m_res = mysql_store_result(m_pMyData);
    if(*m_res==NULL) {
       LOG(ERROR) << " store sql result failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);
	   mysql_free_result(*m_res);
       return -1;
    }
    return 0; 
}

int mysqlDb::ExecuteInsert(const char* sql) {
    if(mysql_query(m_pMyData,sql) != 0) {
        LOG(ERROR) << " execute insert sql failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);;
        return -1;
    }
    return 0;
}

int mysqlDb::ExecuteUpdate(const char* sql, int affect_num) {
    if(mysql_query(m_pMyData,sql) != 0) {
        LOG(ERROR) << " execute update sql failed: " <<  sql << ", msg: " << mysql_error(m_pMyData);;
        return -1;
    }
    affect_num = (int)mysql_affected_rows(m_pMyData);
    return 0;
}

int mysqlDb::ExecuteDelete(const char* sql) {
    return ExecuteInsert(sql);
}

int mysqlDb::Login(LoginReq req, LoginRes& res) {
    int ret = CODE_DB_ERROR;
    int nRowCount=0;
	
    if (!isConnected()) {
        mysql_reConn();
    }

    char sql[1024];

    try {
        memset(sql, 0, 1024);
	    sprintf(sql, " select user_id, role_id,sch_id from user_info where name='%s' and pwd='%s'", req.user_name.c_str(), req.password.c_str());
        printf("sql: %s\n", sql);
    if(-1 == ExecuteQuery(sql, &m_pResultSet)){
		return CODE_NOT_EXSITS;
	}
	if ((nRowCount = (int)mysql_num_rows(m_pResultSet)) == 0) {
		LOG(WARNING) << " ExecuteQuery SQL Failed, Data m_row Count:" << nRowCount << sql;
	    mysql_free_result(m_pResultSet);
	    return CODE_NOT_EXSITS;
	}

    if (nRowCount != 1) {
        return CODE_INVALD_SQL_RES;
    }

     while ((m_row = mysql_fetch_row(m_pResultSet))) {
        res.user_id = std::atoi(m_row[0]);
        res.role_id = std::atoi(m_row[1]);
		if (m_row[2] != NULL) {
		    res.sch_id = std::atoi(m_row[2]);
		} else {
			res.sch_id = 0;
		}
	}

	mysql_free_result(m_pResultSet);
	} catch (...) {
		LOG(WARNING) << " Set Farm Data Exception" ;
	}
	
	return CODE_OK;
}

int mysqlDb::Register(RegisterReq &req, RegisterRes* res) {
    int ret = CODE_DB_ERROR;
	
    if(!isConnected()) {
        mysql_reConn();
    }

    char sql[1024];
        LOG(INFO) << req.user_id;
        int32_t userid = Util::GetRandomId();
        req.user_id = userid;
        LOG(INFO) << userid;
        LOG(INFO) << req.user_id;
        std::string register_time = Util::GetCurrTime();
        struct timeval now;
        gettimeofday(&now, NULL);
        int64_t curr =  now.tv_sec * 1000;
        memset(sql, 0, 1024);
	sprintf(sql, "insert into user_info values(%d, %s, %d, FROM_UNIXTIME(%lld), '%s', '%s', '%s', FROM_UNIXTIME(%lld), %d, '%s', '%s', '%s', 0 ,0 ,0, '0', '0')",
                userid, req.pwd.c_str(), req.role_id, curr, req.user_name.c_str(), req.nation.c_str(),
                req.identity.c_str(), req.bir_time, req.sex, req.tel.c_str(), req.email.c_str(), req.address.c_str());
        LOG(INFO) << req.logid << "execute sql: " <<  sql;
        ret = ExecuteInsert(sql);
        if (ret != 0) {	
            LOG(ERROR) << req.logid << "execute insert sql error" ;
	    return CODE_DB_ERROR;
        }
	return CODE_OK;
}

int mysqlDb::ShowMainCour(ShowMainCourReq req, ShowMainCourRes& res) {
	int ret = CODE_DB_ERROR;
	
	if(!isConnected()) {
        mysql_reConn();
    }

	try {
        char sql[1024];

        memset(sql, 0, 1024);
	    sprintf(sql, "select cour_id,cour_type,start_time,end_time,cour_count,create_time,teacher_id,name,remark from course where sch_id=%d; ", req.sch_id);
        LOG(INFO) << req.logid << " execute sql: " <<  sql;
        ret = ExecuteQuery(sql, &m_pResultSet);
        if (ret != 0) {
            int nRowCount = 0;
            if ((nRowCount = (int)mysql_num_rows(m_pResultSet)) == 0) {
                LOG(WARNING) << "no such key: " <<  nRowCount << sql;
                mysql_free_result(m_pResultSet);
                return CODE_NOT_EXSITS;
            }
	
            LOG(ERROR) << req.logid << " execute query sql error" ;
	        return CODE_DB_ERROR;
        }
	    while ((m_row = mysql_fetch_row(m_pResultSet))) {
            res.cour_id = std::atoi(m_row[0]);
            res.cour_type = std::atoi(m_row[1]);
			res.start_time = m_row[2];
			res.end_time = m_row[3];
			res.cour_count = std::atoi(m_row[4]);
			res.create_time = m_row[5];
			res.teacher_id = std::atoi(m_row[6]);
			res.name = m_row[7];
			res.remark = m_row[8];
	    }
	    mysql_free_result(m_pResultSet);
	} catch (...) {
		LOG(WARNING) << req.logid << " Set Farm Data Exception" ;
		return ret;
	}
	return CODE_OK;
	
}

int mysqlDb::PubMainCour(PubMainCourReq req, PubMainCourRes& res) {
	int ret = CODE_DB_ERROR;
	
    if(!isConnected()) {
        mysql_reConn();
    }

    char sql[1024];
	int32_t main_cour_id = Util::GetMainCourseId(req.sch_id);
	struct timeval now;
    gettimeofday(&now, NULL);
    int64_t curr =  now.tv_sec * 1000;
    memset(sql, 0, 1024);
	sprintf(sql, "insert into course(sch_id, cour_id, sub_cour_id, cour_type, start_time,end_time, cour_count, create_time, teacher_id, name, cour_leve, remark) values (%d, %d, 0, %d, '%s', '%s', %d, FROM_UNIXTIME(%lld), %d, '%s', 0, '%s')",
    req.sch_id, main_cour_id, req.cour_type, req.start_time.c_str(), req.end_time.c_str(), req.cour_count, curr, req.teacher_id, req.name.c_str(), req.remark.c_str());
    LOG(INFO) << req.logid << "execute sql: " <<  sql;
    ret = ExecuteInsert(sql);
    if (ret != 0) {	
        LOG(ERROR) << req.logid << "execute insert sql error" ;
	    return CODE_DB_ERROR;
    }
	res.cour_id = main_cour_id;
	return CODE_OK;
}


