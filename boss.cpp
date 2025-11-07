#include "boss.h"

boss::boss(int id, string name, int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}

//显示个人信息
void boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t  岗位职责：管理公司所有事务" << endl;
}
//获取岗位名称
string  boss::getDeptName()
{
	return string("老板");
}
