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
void DataBaseTool::delConfig(int configid){
	try{
		*db<<"delete from tb_config where id= :id",use(configid);
	}
	catch (std::runtime_error const& err)
	{
		std::cerr << err.what();
	}
 
}

void DataBaseTool::addConfig(OConfig config){
	try{
		*db<<"insert into tb_config values(null, :name, :label,:port,:baud,:databit,:stopbit,:pority,:status,:datatype,:deviceno,:readonly,:timer,:reg,:bytecount)",
			use((LPCTSTR)(config.name)),use((LPCTSTR)(config.label)),use((LPCTSTR)(config.port)),
			use(config.baud),use(config.databit),use(config.stopbit),use((LPCTSTR)(config.pority)),
			use(config.status),use((LPCTSTR)(config.datatype)),use(config.deviceno),use(config.readonly),
			use(config.timer),use(config.reg),use(config.bytecount);
	 // <<  (LPCTSTR)(config.name)<< "' ,'" << config.label<< "', '" 
    //  << config.port<< "' ," << config.baud<< ", " 
	 // << config.databit<< " ," << config.stopbit<< ", " 
	 // << config.pority<< " ," << config.status<< ", '" 
	 // << config.datatype<< "' ," << config.deviceno<< ", " 
	 // << config.readonly<< " ," << config.timer<< ", " 
	  //<< config.reg<< " ," << config.bytecount<< ")";
}
	catch (std::runtime_error const& err)
	{
		std::cerr << err.what();
	}

}

void DataBaseTool::updateConfig(OConfig config){
	try{
		*db<<"update  tb_config set name = :name, label=:label, port=:port,baud=:baud,databit=:databit,stopbit=:stopbit,pority=:pority,status=:status,datatype=:datatype,deviceno=:deviceno,readonly=:readonly,timer=:timer,reg=:reg,bytecount=:bytecount where id=:id",
			use((LPCTSTR)(config.name)),use((LPCTSTR)(config.label)),use((LPCTSTR)(config.port)),
			use(config.baud),use(config.databit),use(config.stopbit),use((LPCTSTR)(config.pority)),
			use(config.status),use((LPCTSTR)(config.datatype)),use(config.deviceno),use(config.readonly),
			use(config.timer),use(config.reg),use(config.bytecount),use(config.id);
	 // <<  (LPCTSTR)(config.name)<< "' ,'" << config.label<< "', '" 
    //  << config.port<< "' ," << config.baud<< ", " 
	 // << config.databit<< " ," << config.stopbit<< ", " 
	 // << config.pority<< " ," << config.status<< ", '" 
	 // << config.datatype<< "' ," << config.deviceno<< ", " 
	 // << config.readonly<< " ," << config.timer<< ", " 
	  //<< config.reg<< " ," << config.bytecount<< ")";
}
	catch (std::runtime_error const& err)
	{
		std::cerr << err.what();
	}

}

std::vector<OConfig> DataBaseTool::loadConfigs(){
	std::vector<OConfig> vec;
	statement st(*db);
 OConfig  tempConfig;
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
     st << "select id,name,label,port,baud,databit,stopbit,pority,status,datatype,deviceno,readonly,timer,reg ,bytecount from tb_config",
		into( id), 
		into(name), 
		into(label), 
		into(port), 
		into( baud), 
		into( databit),
		into( stopbit), 
		into(pority), 
		into( status),
		into(datatype), 
		into(deviceno), 
		into( readonly),
		into( timer), 
		into( reg),
	    into( bytecount); 
	    
	while ( st.exec() )
	{
		     OConfig  config;
			config.id=id;
			config.name=name;
			config.label=  label;
			config.port= port;
			config.baud= baud;
			config.databit= databit;
			config.stopbit= stopbit;
			config.pority= pority;
			config.status= status;
			config.datatype= datatype;
			config.deviceno= deviceno;
			config.readonly= readonly;
			config.timer= timer;
			config.reg= reg;
			config.bytecount= bytecount;
			//memcpy(&config, &tempConfig, sizeof(tempConfig));
			vec.push_back(config);
	}
	return vec;

}
OConfig* DataBaseTool::loadConfigById(int configid){
 
	statement st(*db);
    OConfig*  config=new OConfig;
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
	st << "select id,name,label,port,baud,databit,stopbit,pority,status,datatype,deviceno,readonly,timer,reg ,bytecount from tb_config where id= :1",
		
		into( id), 
		into(name), 
		into(label), 
		into(port), 
		into( baud), 
		into( databit),
		into( stopbit), 
		into(pority), 
		into( status),
		into(datatype), 
		into(deviceno), 
		into( readonly),
		into( timer), 
		into( reg),
	    into( bytecount),
		use(configid); 
	    
	while ( st.exec() )
	{
		    
			config->id=id;
			config->name=name;
			config->label=  label;
			config->port= port;
			config->baud= baud;
			config->databit= databit;
			config->stopbit= stopbit;
			config->pority= pority;
			config->status= status;
			config->datatype= datatype;
			config->deviceno= deviceno;
			config->readonly= readonly;
			config->timer= timer;
			config->reg= reg;
			config->bytecount= bytecount;
			//memcpy(&config, &tempConfig, sizeof(tempConfig));
			 
	}
	return config;
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