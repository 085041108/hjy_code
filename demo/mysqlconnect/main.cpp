#include "main.h"

int readCfgIni(char*  pPath)
{
	readIni read_ini;
	
	memset(m_chUser, 0, 64);
	read_ini.getCnfMess("USER", m_chUser, pPath);

	memset(m_chPassword, 0, 64);
	read_ini.getCnfMess("PWD", m_chPassword, pPath);

	memset(m_chDbname, 0, 64);
	read_ini.getCnfMess("DB", m_chDbname, pPath);

	memset(m_chHost, 0, 64);
	read_ini.getCnfMess("SRC", m_chHost, pPath);
	
	char chTem[255];
	memset(chTem, 0, 255);
	read_ini.getCnfMess("PORT", chTem, pPath);
	if(0 == strlen(chTem))
	{
		m_nPort = 3306;
	}
	else
	{
		m_nPort = atoi(chTem);
	}
}

int main()
{
	memset(m_chHost,0,64);
	memset(m_chUser,0,64);
	memset(m_chPassword,0,64);
	memset(m_chDbname,0,64);
	
	char chSysPath[256];
	readIni read_ini;
	memset(chSysPath,0,256);
	read_ini.GetModuleFileName( NULL,chSysPath,256);
	printf("%s",chSysPath);
	if (strlen(chSysPath)==0)
	{
		return -1;
	}
	char *pCh = strrchr(chSysPath,'/');
	int nLen = pCh - chSysPath;
	char chTem[256];
	memset(chTem,0,256);
	memcpy(chTem,chSysPath, nLen);
	memset(chSysPath,0,256);
	pCh = strrchr(chTem,'/');
	nLen = pCh - chTem;
	memset(chSysPath,0,256);
	memcpy(chSysPath, chTem, nLen);
	char chCfgPath[256];
	memset(chCfgPath, 0, 256);
	snprintf(chCfgPath, sizeof(chCfgPath), "%s/config/simdb.ini", chSysPath);
	readCfgIni(chCfgPath);


	memset(m_chUser, 0, 64);
	memset(m_chPassword, 0, 64);
	memset(m_chDbname, 0, 64);
	memset(m_chHost, 0, 64);
	sprintf(m_chUser,"admin");
	sprintf(m_chPassword,"admin");
	sprintf(m_chDbname,"SIMDB");
	sprintf(m_chHost,"127.0.0.1");

	mysqlDb myDb;
	myDb.Init(m_chHost, m_chUser, m_chPassword,m_chDbname,3306);
	if(!myDb.mysql_conn())	//判断数据库连接,若未连接，进行重新连接
	{
		if(!myDb.mysql_reConn())
		return -1;
	}

	string user_name;
	string password;
	user_name.assign("hjyname");
	password.assign("123456");
	myDb.Login(user_name, password);
	user_info_map userMapInfo;
	/*
	myDb.GetUserInfo(1, userMapInfo);
	for (user_info_map::iterator it = userMapInfo.begin(); it != userMapInfo.end(); it++)
	{
		cout << it->second.user_id << endl << it->second.sch_id << endl << it->second.role_id << endl
			<< it->second.tea_id << endl << it->second.put_datetime << endl << it->second.user_name << endl
			<< it->second.user_nation << endl << it->second.user_identity << endl << it->second.birth_date << endl
			<< it->second.user_sex << endl << it->second.tel_number << endl << it->second.email_address << endl
			<< it->second.user_address << endl << it->second.enter_time << endl << it->second.end_time << endl
			<< it->second.class_count << endl << it->second.user_level << endl
			<< it->second.if_base << endl << it->second.base_latin << endl << it->second.base_ballet << endl
			<< it->second.base_folk << endl << it->second.base_other << endl << it->second.if_work << endl
			<< it->second.work_latin << endl << it->second.work_ballet << endl << it->second.work_folk << endl
			<< it->second.work_other << endl << it->second.if_company << endl << it->second.company_count << endl
			<< it->second.future_work << endl << it->second.future_company << endl;
	}
	*/
	return 0;
}