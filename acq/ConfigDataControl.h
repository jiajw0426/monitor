#pragma once
#include <windows.h>
#include "../dal/database.h"
#include "../modserial/CESeries.h"
 

class CConfigDataControl
{
 
public:
	CButton* buton;
	CCESeries* serial;
	CEdit*   edit ;
	int index;
	OConfig* config;
	CConfigDataControl(int index,OConfig* config,CWnd * parent);
	~CConfigDataControl(void);
};
