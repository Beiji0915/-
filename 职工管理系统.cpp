#include <iostream>
#include <string>
#include <fstream>

#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;


int main()
{
	workerManager wm;//创建workerManager对象

	int choice = 0;//初始化用户选择
	while (1)
	{
		wm.show_Menu();//放入循环里，让每一次都显示菜单
		cout << "请输入您想使用的功能：";
		cin >> choice;//等待用户输入
		if (choice >= 0 && choice <= 7)//判断用户输入是不是在0到7之间，如果是执行选择功能语句
		{
			switch (choice)
			{
			case 0:		//退出系统
				wm.exitsystem();
				break;
			case 1:		//增加职工
				wm.AddEmp();
				break;
			case 2:		//显示职工
				wm.show_Emp();
				break;
			case 3:		//删除职工
				wm.del_Emp();
				break;
			case 4:		//修改职工
				wm.mod_Emp();
				break;
			case 5:		//查找职工
				wm.find_Emp();
				break;
			case 6:		//排序职工
				wm.sort_Emp();
				break;
			case 7:		//清空文档
				wm.clean_file();
				break;
			}
		}
		else	//如果输入不是0到7之间
		{
			cout << "输入不合法！" << endl;
			return 0;
		}
	}

	system("pause");
	return 0;
}