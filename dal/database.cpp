#include "database.h"
#include "gbk.h"

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }//添加的部分
#else
extern "C" { int __afxForceUSRDLL; }
#endif 
//原有的dllmain函数
BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
      )
{
    return TRUE;
}

std::vector<OUser> DataBaseTool::loadUsers(){
	std::vector<OUser> vec;
	statement st(*db);
	OUser tempUser;
    st << "select id, name,loginid,pwd,isadmin,status from tb_user", into(tempUser.id), 
		    into(tempUser.name,U2G(utf(L"name").c_str())), into(tempUser.pwd), into(tempUser.isadmin), into(tempUser.status);
	while ( st.exec() )
	{
		    OUser user;
			memcpy(&user, &tempUser, sizeof(OUser));
			vec.push_back(user);
	}
	return vec;

}

std::vector<OConfig> DataBaseTool::loadConfigs(){
	std::vector<OConfig> vec;
	statement st(*db);
	OConfig tempConfig;
    st << "select id,name,label,port,baud,databit,stopbit,pority,status,datatype,deviceno,readonly,timer,reg from tb_config",
		into(tempConfig.id), 
		into(tempConfig.name,U2G(utf(L"name").c_str())), 
		into(tempConfig.label,U2G(utf(L"label").c_str())), 
		into(tempConfig.port), 
		into(tempConfig.baud), 
		into(tempConfig.databit),
		into(tempConfig.stopbit), 
		into(tempConfig.pority), 
		into(tempConfig.status),
		into(tempConfig.datatype), 
		into(tempConfig.deviceno), 
		into(tempConfig.readonly),
		into(tempConfig.timer), 
		into(tempConfig.reg);
	while ( st.exec() )
	{
		    OConfig config;
			memcpy(&config, &tempConfig, sizeof(OConfig));
			vec.push_back(config);
	}
	return vec;

}

std::vector<OData> DataBaseTool::loadDatas(){
	std::vector<OData> vec;
	statement st(*db);
	OData tempData;
    st << "select id, value,configid,rdate,rtime tb_data", into(tempData.id), 
		    into(tempData.value), into(tempData.configid), into(tempData.rdate), into(tempData.rtime);
	while ( st.exec() )
	{
		    OData data;
			memcpy(&data, &tempData, sizeof(OData));
			vec.push_back(data);
	}
	return vec;

}