#ifndef _STRUCT_H
#define _STRUCT_H
#include <mysql/mysql.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

typedef struct _UserInfo    
{
	int      user_id;
	int      sch_id;
	int      role_id;
	int      tea_id;
	int      put_datetime;
	string   user_name;
	string   user_nation;
	string   user_identity;
	int      birth_date;
	int      user_sex;
	string   tel_number;
	string   email_address;
	string   user_address;
	int      enter_time;
	int      end_time;
	int      class_count;
	int      user_level;
	int      if_base;
	int      base_latin;
	int      base_ballet;
	int      base_folk;
	string   base_other;
	int      if_work;
	int      work_latin;
	int      work_ballet;
	int      work_folk;
	string   work_other;
	int      if_company;
	int      company_count;
	int      future_work;
	int      future_company;

	_UserInfo()
	{
		user_id        = 0;
		sch_id         = 0;
		role_id        = 0;
		tea_id         = 0;
		put_datetime   = 0;
		user_name      = "";
		user_nation    = "";
		user_identity  = "";
		birth_date     = 0;
		user_sex       = 0;
		tel_number     = "";
		email_address  = "";
		user_address   = "";
		enter_time     = 0;
		end_time       = 0;
		class_count    = 0;
		user_level     = 0;
	    if_base        = 0;
	    base_latin     = 0;
		base_ballet    = 0;
	    base_folk      = 0;
	    base_other     = "";
	    if_work        = 0;
	    work_latin     = 0;
	    work_ballet    = 0;
	    work_folk      = 0;
	    work_other     = "";
	    if_company     = 0;
	    company_count  = 0;
	    future_work    = 0;
	    future_company = 0;
	}
}UserInfo;
typedef map<int, UserInfo> user_info_map;
#endif

