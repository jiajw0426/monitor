#pragma once
#include<vector>
#include <string>
#include <iostream>

#include "../sqlitepp/sqlitepp.hpp"
#include "../sqlitepp/dllexport.hpp"

  #include <afx.h>  // 添加，加在这里
  #include <windows.h>//原来默认有的
 
  //添加的
  #ifdef _DEBUG
   #pragma comment(lib, "libcmtd.lib")//crt多线程debug库
  #else
   #pragma comment(lib, "libcmt.lib")//crt多线程库
  #endif
using namespace sqlitepp;

template<>
struct converter<CString >
{
	typedef string_t base_type;
	
	static string_t from(CString const& src)
	{
	 
		return (LPSTR)(LPCTSTR)src;;
	}
	
	static CString to(string_t const& src)
	{
		
		
         CString str(utf8(src).c_str()); 
 
         return str;
 
	}
};

#define  TABLE_USER  "create table if not exists tb_user( id integer primary key"\
													 ",name text"\
													   ",loginid text"\
													   ",pwd text"\
													   ",isadmin integer"\
												   ",status integer)"

 

struct DllExport OUser {
	int id;
  	std::string name;
	std::string pwd;
	std::string loginid;
	int isadmin;
	int status;
};

#define TABLE_CONFIG   "create table if not exists tb_config(id integer primary key"\
														 ",name text"\
														 ",label text"\
														 ",port text"\
														 ",baud integer"\
														 ",databit integer"\
														 ",stopbit integer"\
														 ",pority text"\
														 ",status integer"\
														 ",datatype text"\
														 ",deviceno integer"\
														 ",readonly integer"\
														 ",timer integer"\
														 ",reg integer"\
														 ",bytecount integer)"

 
struct DllExport OConfig {
	 
	int id;
  	CString name;
	CString  label;
	CString port;
	int baud;
	int databit;
	int stopbit;
	CString pority;
	int status;
	CString datatype;
	int deviceno;
	int readonly;
	int timer;
	int reg;
	int bytecount;
	void dump(){
		printf("id:%d,name:%S,label:%S,port:%S,baud:%d,databit:%d,stopbit:%d,pority:%S,status:%d,datatype:%s,deviceno:%d"\
			"readonly:%d,timer:%d,reg:%d,bytecount:%d\n",id,(LPSTR)(LPCTSTR)name,(LPCTSTR)label,(LPCTSTR)port,baud,databit,stopbit,(LPCTSTR)pority,
			status,(LPCTSTR)datatype,deviceno,readonly,timer,reg,bytecount);
	};

};

#define  TABLE_DATA "create table if not exists tb_data(id integer primary key"\
														",configid integer"\
														",value text"\
														",rdate text"\
														",rtime text)"
 
struct DllExport OData{
	int id;
  	std::string value;
	std::string rdate;
	std::string rtime;
	int configid;
};
#define  TABLE_DATA_IDX  "create index  if not exists idxdata on tb_data(configid,rdate,rtime)"

class DllExport DataBaseTool{

	private:
	 
		session* db;
	public:
		DataBaseTool( ){
 
		this->db=new session("./Program Files/monitor/sqlite.db");

		*db <<TABLE_USER;
		*db <<TABLE_CONFIG;
		*db <<TABLE_DATA;
		*db <<TABLE_DATA_IDX;
		}
		OConfig* loadConfigById(int id);
		void addConfig(OConfig config);
		void updateConfig(OConfig config);
		void delConfig(int configid);
		std::vector<OUser> loadUsers();
		std::vector<OConfig> loadConfigs();
		std::vector<OData> loadDatas();

};