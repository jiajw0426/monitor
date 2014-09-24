// stdafx.cpp : 只包括标准包含文件的源文件
// monitor.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

LONG getHCenterStart(CRect* crect,LONG offset){
 
	return (crect->right-offset)/2;

 
}

LONG getVCenterStart(CRect* crect,LONG offset){

	return (crect->bottom-offset)/2;
}