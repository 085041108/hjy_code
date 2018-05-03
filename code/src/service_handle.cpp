#include  "../include/service_handle.h"
#include  "../include/mysqldb.h"
#include  "../include/data_define.h"
#include  "../include/global_config.h"
#include  "../json/json.h"

ServiceHandle::~ServiceHandle() {
    //if(m_db_access != null) {
    //   delete m_db_access;
    //}
}

int ServiceHandle::Init() {
    //m_db_access =
    return 0; 
}

//need para: string name, string password
int ServiceHandle::LoginByNameAndPw(const hjy_request& req, hjy_respose& _return) {
     int ret = CODE_OK;
     std::string body = req.req_string;
     LOG(INFO) << req.logid << " request body is: " << body;
     Json::Reader reader;
     Json::Value value;
     LoginReq login_req;
     LoginRes login_res;
     if (reader.parse(body, value)) {
     std::string user_name = value["name"].asString();
     std::string password = value["pwd"].asString();
     login_req.user_name = user_name;
     login_req.password = password;
     LOG(INFO) << req.logid << "username: " <<  user_name;
     LOG(INFO) << req.logid << "password: " <<  password;
     mysqlDb *m_db_access = new mysqlDb(GlobalConfig::g_db_host, GlobalConfig::g_db_port, GlobalConfig::g_db_user, GlobalConfig::g_db_password, GlobalConfig::g_db_name);
     if (!m_db_access->Init()) {
         LOG(WARNING) << req.logid << " init database failed, will return CODE_DB_ERROR";
         ret = CODE_DB_ERROR;
		 _return.ret = ret;
		 delete m_db_access;
		 return ret;
     }
     ret = m_db_access->Login(login_req, login_res);
     if (ret != CODE_OK) {
         LOG(WARNING) << req.logid << " get info from db failed, ret: " << ret;
		 _return.ret = ret;
		 delete m_db_access;
		 return ret;
     } 
      delete m_db_access;
         
     } else {
         LOG(WARNING) << req.logid << " parse request string error, will return CODE_INVAID_PARAS";
         ret = CODE_INVALID_PARAS;
		 _return.ret = ret;
		 return ret;
     }
    _return.ret = ret;
	Json::Value res1; 
    Json::FastWriter writer;  
    Json::Value res2;  

    res2["user_id"] = login_res.user_id;
    res2["role_id"] = login_res.role_id;
    res2["sch_id"]  = login_res.sch_id;	
    res1.append(res2);  
   
    std::string res_json = writer.write(res1); 
    _return.res_string = res_json;
    return ret;
}

int ServiceHandle::Register(const hjy_request& req, hjy_respose& _return) {
    int ret = CODE_OK;
    std::string body = req.req_string;
    LOG(INFO) << req.logid << " request body is: " << body;
    Json::Reader reader;
    Json::Value value;
    RegisterReq register_req;
    RegisterRes register_res;
    if (reader.parse(body, value)) {
        std::string name;
        std::string pwd;
        std::string tel;
        std::string email;
        int role_id = 1;
        int sex = 0;
        std::string nation = "default";
        std::string identity = "default";
        int64_t bir_time = 0;
        std::string address = "default";
        if(value["name"].isNull()) {
           ret =  CODE_INVALID_PARAS;
           _return.ret = ret;
           return ret;
        } else {
               name = value["name"].asString();
        }

        if(value["pwd"].isNull()) {
           ret =  CODE_INVALID_PARAS;
           _return.ret = ret;
           return ret;
        } else {
               pwd = value["pwd"].asString();
        }

        if(value["tel"].isNull()) {
           ret =  CODE_INVALID_PARAS;
           _return.ret = ret;
           return ret;
        } else {
               tel = value["tel"].asString();
        }

        if(value["email"].isNull()) {
           ret =  CODE_INVALID_PARAS;
           _return.ret = ret;
           return ret;
        } else {
           email = value["email"].asString();
        }

        if(!value["role_id"].isNull()) {
           role_id = value["role_id"].asInt();
        } 

        if(!value["bir_time"].isNull()) {
           bir_time = int64_t(value["bir_time"].asDouble());
        } 

        if(!value["nation"].isNull()) {
           nation = value["nation"].asString();
        } 

        if(!value["identity"].isNull()) {
           identity = value["idetity"].asString();
        } 

        if(!value["address"].isNull()) {
           address = value["address"].asString();
        } 
        register_req.Init(name, pwd, tel, email, nation, identity, bir_time, address, role_id, sex);

     mysqlDb *m_db_access = new mysqlDb(GlobalConfig::g_db_host, GlobalConfig::g_db_port, GlobalConfig::g_db_user, GlobalConfig::g_db_password, GlobalConfig::g_db_name);
     if (!m_db_access->Init()) {
         LOG(WARNING) << req.logid << " init database failed, will return CODE_DB_ERROR";
         ret = CODE_DB_ERROR;
     }
     LOG(INFO) << req.logid << "user_id: " << " " << register_req.user_id; 
     ret = m_db_access->Register(register_req, &register_res);
     if (ret != CODE_OK) {
         LOG(WARNING) << req.logid << " register failed while process db , ret: " << ret;
         ret = CODE_USER_ALREADY_EXSITS;
     } 
      delete m_db_access;
     }else {
         LOG(WARNING) << req.logid << " parse request string error, will return CODE_INVAID_PARAS";
         ret = CODE_INVALID_PARAS;
     }
	 
    Json::Value res1; 
    Json::FastWriter writer;  
    Json::Value res2;  
    LOG(INFO) << req.logid << "user_id: " << " " << register_req.user_id; 
    res2["user_id"] = register_req.user_id;  
    res1.append(res2);  
   
    std::string res_json = writer.write(res1); 
      _return.ret = ret;
      _return.res_string = res_json;
      // other json response    
      return ret;
}

int ServiceHandle::ShowMainCour(const hjy_request& req, hjy_respose& _return) {
	int ret = CODE_OK;
    std::string body = req.req_string;
    LOG(INFO) << req.logid << " request body is: " << body;
    Json::Reader reader;
    Json::Value value;
    ShowMainCourReq s_req;
    ShowMainCourRes s_res;
	if (reader.parse(body, value)) {

	    // get role_id from req
	    if(value["role_id"].isNull()) {
            ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
        } else {
               s_req.role_id = value["role_id"].asInt();
        }
	    // get sch_id from req
	    if(value["sch_id"].isNull()) {
            ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
        } else {
               s_req.sch_id = value["sch_id"].asInt();
        }		
        if (s_req.role_id != ROLE_SCH) {
			LOG(ERROR) << req.logid << " invalid roleid, only school user could execute this request, " << s_req.role_id;
			ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
		}
    // execute sql query from db
	    mysqlDb *m_db_access = new mysqlDb(GlobalConfig::g_db_host, GlobalConfig::g_db_port, GlobalConfig::g_db_user, GlobalConfig::g_db_password, GlobalConfig::g_db_name);
        if (!m_db_access->Init()) {
            LOG(WARNING) << req.logid << " init database failed, will return CODE_DB_ERROR";
            ret = CODE_DB_ERROR;
		    _return.ret = ret;
		    delete m_db_access;
		    return ret;
        }
        ret = m_db_access->ShowMainCour(s_req, s_res);
        if (ret != CODE_OK) {
            LOG(WARNING) << req.logid << " select failed while process db , ret: " << ret;
            ret = CODE_DB_ERROR;
		    _return.ret = ret;
		    delete m_db_access;
		    return ret;
        } 
        delete m_db_access;
	} else {
         LOG(WARNING) << req.logid << " parse request string error, will return CODE_INVAID_PARAS";
		 _return.ret = ret;
         ret = CODE_INVALID_PARAS;		
	}
	
	_return.ret = ret;
	Json::Value res1; 
    Json::FastWriter writer;  
    Json::Value res2;  

    res2["cour_id"] = s_res.cour_id;
	res2["cour_type"] = s_res.cour_type;
    res2["cour_count"] = s_res.cour_count;
	res2["start_time"] = s_res.start_time;
	res2["create_time"] = s_res.create_time;
    res2["teacher_id"] = s_res.teacher_id;
	res2["name"] = s_res.name;
	res2["remark"] = s_res.remark;
	
    res1.append(res2);  
   
    std::string res_json = writer.write(res1); 
    _return.res_string = res_json;
    return ret;	
}

int ServiceHandle::PubMainCour(const hjy_request& req, hjy_respose& _return) {
	int ret = CODE_OK;
    std::string body = req.req_string;
    LOG(INFO) << req.logid << " request body is: " << body;
    Json::Reader reader;
    Json::Value value;
    PubMainCourReq s_req;
    PubMainCourRes s_res;
	if (reader.parse(body, value)) {

	    // get role_id from req
	    if(value["sch_id"].isNull()) {
            ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
        } else {
               s_req.sch_id = value["sch_id"].asInt();
        }
	    // get sch_id from req
	    if(value["role_id"].isNull()) {
            ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
        } else {
               s_req.role_id = value["role_id"].asInt();
			   if (s_req.role_id != ROLE_SCH) {
				   LOG(ERROR) << req.logid << " invalid role_id: " << s_req.role_id << " , only sch user could pub course";
				    ret =  CODE_INVALID_PARAS;
                   _return.ret = ret;
                   return ret;
			   }
        }

        if (value["start_time"].isNull()) {
			ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
		} else {
			s_req.start_time = value["start_time"].asString();
		}
		if (value["end_time"].isNull()) {
			ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
		} else {
			s_req.end_time = value["end_time"].asString();
		}
		
        if (value["cour_type"].isNull()) {
            ret =  CODE_INVALID_PARAS;
            _return.ret = ret;
            return ret;
        } else {
               s_req.cour_type = value["cour_type"].asInt();
        }
		if (!value["name"].isNull()) {
			s_req.name = value["name"].asString();
		}
		if (!value["remark"].isNull()) {
			s_req.remark = value["remark"].asString();
		}
		if (!value["teacher_id"].isNull()) {
			s_req.teacher_id = value["teacher_id"].asInt();
		}
		if (!value["cour_count"].isNull()) {
			s_req.cour_count = value["cour_count"].asInt();
		}
    // execute sql query from db
	    mysqlDb *m_db_access = new mysqlDb(GlobalConfig::g_db_host, GlobalConfig::g_db_port, GlobalConfig::g_db_user, GlobalConfig::g_db_password, GlobalConfig::g_db_name);
        if (!m_db_access->Init()) {
            LOG(WARNING) << req.logid << " init database failed, will return CODE_DB_ERROR";
            ret = CODE_DB_ERROR;
		    _return.ret = ret;
		    delete m_db_access;
		    return ret;
        }
        ret = m_db_access->PubMainCour(s_req, s_res);
        if (ret != CODE_OK) {
            LOG(WARNING) << req.logid << " insert failed while process db , ret: " << ret;
            ret = CODE_DB_ERROR;
		    _return.ret = ret;
		    delete m_db_access;
		    return ret;
        } 
        delete m_db_access;
	} else {
         LOG(WARNING) << req.logid << " parse request string error, will return CODE_INVAID_PARAS";
		 _return.ret = ret;
         ret = CODE_INVALID_PARAS;		
	}
	
	_return.ret = ret;
	Json::Value res1; 
    Json::FastWriter writer;  
    Json::Value res2;  

    res2["cour_id"] = s_res.cour_id;

    res1.append(res2);  
   
    std::string res_json = writer.write(res1); 
    _return.res_string = res_json;
    return ret;	
}

	

