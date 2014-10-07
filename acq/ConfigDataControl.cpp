#include "StdAfx.h"
#include "ConfigDataControl.h"

CConfigDataControl::CConfigDataControl(int idx,OConfig* config,CWnd * parent) 
{
	  int line=idx/2;
	  int col=idx%2;
	  int Hbtn=20;
	  int Wbtn=70;
      int Hedit=20;
	  int Wedit=80;

	  int top=10;

	  int Vgap=3;
	  int Hgap=3;
	  int VBtngap=Vgap;
	  int HBtngap=Hgap*7+Wedit;

	  int VEditgap=Vgap;
	  int HEditgap=Hgap*7+Wbtn;
	 
	  this->index=idx;
	  this->config=config;
	  this->buton= new CButton();
	  this->buton->Create(config->label, WS_CHILD|BS_DEFPUSHBUTTON|WS_VISIBLE|BS_AUTOCHECKBOX,
		  CRect(10+col*Wbtn+col*HBtngap,  top+line*Hbtn+line*VBtngap,10+(col+1)*Wbtn+col*HBtngap, top+(line+1)*Hbtn+line*VBtngap), parent, 100+index);
	  this->buton->SetCheck(TRUE);


	  this->edit  = new CEdit();
	  this->edit ->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER|WS_EX_TOOLWINDOW,
		  CRect(10+Wbtn+Hgap+col*Wedit+col*HEditgap,  top+line*Hedit+line*VEditgap,10+Wbtn+Hgap+(col+1)*Wedit+col*HEditgap, top+(line+1)*Hedit+line*VEditgap), parent, 1000+index);
	  this->serial=new CCESeries();
}

CConfigDataControl::~CConfigDataControl(void)
{
}
