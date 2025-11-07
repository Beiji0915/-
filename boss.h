#pragma once
#include <iostream>


#include "worker.h"
using namespace std;

class boss :public worker
{
public:
	boss(int id, string name, int deptid);

	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};