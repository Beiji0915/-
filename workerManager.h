#pragma once	//防止头文件重复包含
#include <iostream>//包含输入输出流头文件
#include <fstream> // 包含文件交互头文件

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#define filename "appdata.txt"

using namespace std;//使用标准命名空间

//创建管理类
class workerManager
{
public:
	workerManager();//构造函数的声明

	//展示菜单
	void show_Menu();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	worker** m_EmpArray;

	//添加职工函数
	void AddEmp();

	//保存文件
	void save();

	//标志文件是否为空
	bool m_fileisempty;

	//获取文件人数
	int get_EmpNum();

	//初始化职工
	void init_Emp();

	//显示职工信息
	void show_Emp();

	//删除职工
	void del_Emp();

	//修改职工
	void mod_Emp();

	//查找职工
	void find_Emp();

	//排序职工
	void sort_Emp();

	//判断职工是否存在
	int IsExist(int id);

	//清空文件
	void clean_file();
	
	//退出程序
	void exitsystem();

	~workerManager();//析构函数的声明

};