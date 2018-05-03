/**
*@file     service.h
*@author   wjy
*@date      2016.09.11
*
**/

#ifndef  HJY_DATA_DEFINE_H
#define HJY_DATA_DEFINE_H

#include "string"

typedef enum {
	ROLE_TEA  =  0,
	ROLE_STU  =  1,
	ROLE_SCH  =  2
}hjy_user_role;

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


typedef enum {
    HJY_LOGIN                    =  1000,
    HJY_REGISTER                 =  1001,
    HJY_SHOW_MAIN_COUR           =  1002,
    HJY_PUB_MAIN_COUR            =  1003,
    //HJY_GET_USER_INFO            =  1001,
    //HJY_GET_COURSE_BY_STUID      =  1002,
    //HJY_PUT_NEW_STUDENT          =  1003,
    //HJY_PUT_NEW_TEACHER          =  1004,
    HJY_PUT_NEW_COURCE           =  1005
}hjy_api_type;

// for login
struct LoginReq {
    LoginReq() {}
    LoginReq(std::string name, std::string pwd) {
        user_name = name;
        password = pwd;
    }    
    int64_t logid; 
    std::string user_name; 
    std::string password;
};

struct LoginRes {
    int32_t user_id;
    int     role_id;
    int     sch_id; 	
};

// for register
struct RegisterReq {
    RegisterReq() {}
    void Init(const std::string m_user_name, const std::string m_pwd, const std::string m_tel, const std::string m_email, const std::string m_nation, const std::string m_identity, int64_t m_birth_time, const std::string m_address, int m_role_id, int m_sex) {
        user_name = m_user_name;
        pwd = m_pwd;
        tel = m_tel;
        email = m_email;
        nation = m_nation;
        identity = m_identity;
        bir_time = m_birth_time;
        address = m_address;
        role_id = m_role_id;
        sex = m_sex;
        user_id = 0;
}
    int64_t logid; 
    int32_t user_id; 
    std::string user_name;
    std::string pwd;
    std::string tel;
    std::string email;
    int role_id;
    std::string nation;
    std::string identity;
    int64_t bir_time;
    int sex;
    std::string address;
};

struct RegisterRes {
    int32_t user_id;
};

struct ShowMainCourReq {
	int32_t sch_id;	
    int32_t role_id;	
	int64_t logid;
};

struct ShowMainCourRes {
	int cour_id;
	int cour_type;
	std::string start_time;
	std::string end_time;
	int cour_count;
	std::string create_time;
	int32_t teacher_id;
	std::string name;
	std::string remark;
};

struct PubMainCourReq {
	int32_t sch_id;	
    int32_t role_id;	
	int64_t logid;
	int32_t cour_type;
	std::string start_time;
	std::string end_time;
	int32_t cour_count;
	int32_t teacher_id;
	std::string name;
	std::string remark;
	PubMainCourReq(){
		cour_count = 0;
		teacher_id = 0;
		name = "";
		remark = "";
	}
};

struct PubMainCourRes {
	int cour_id;
};
#endif
