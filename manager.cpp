#include "manager.h"

manager::manager(int id,string name,int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}

//显示个人信息
void manager::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t  岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}
//获取岗位名称
string  manager::getDeptName()
{
	return string("经理");
}
