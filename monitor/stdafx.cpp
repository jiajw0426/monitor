// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// monitor.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

LONG getHCenterStart(CRect* crect,LONG offset){
 
	return (crect->right-offset)/2;

 
}

LONG getVCenterStart(CRect* crect,LONG offset){

	return (crect->bottom-offset)/2;
}