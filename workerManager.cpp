#include "workerManager.h"//与头文件关联

workerManager::workerManager()
{

	//读文件
	fstream ifs;
	ifs.open(filename, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;//测试代码
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_fileisempty = true;

		ifs.close();
		return;
	}

	//文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空！" << endl;	//测试代码
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_fileisempty = true;

		ifs.close();
		return;
	}

	//文件存在并且数据不为空
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl; //测试代码
	this->m_EmpNum = num;
	this->m_EmpArray = new worker * [num];
	init_Emp();

	//测试代码
	//for (int i = 0; i < num; i++)
	//{
	//	cout << "职工编号：" << this->m_EmpArray[i]->m_Id
	//		<< "职工姓名：" << this->m_EmpArray[i]->m_Name
	//		<< "部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

//展示菜单
void workerManager::show_Menu()
{
	cout << "**************************************" << endl;
	cout << "********欢迎使用职工管理系统！********" << endl;
	cout << "*********  0.退出管理程序  ***********" << endl;
	cout << "*********  1.增加职工信息  ***********" << endl;
	cout << "*********  2.显示职工信息  ***********" << endl;
	cout << "*********  3.删除离职职工  ***********" << endl;
	cout << "*********  4.修改职工信息  ***********" << endl;
	cout << "*********  5.查找职工信息  ***********" << endl;
	cout << "*********  6.按照编号排序  ***********" << endl;
	cout << "*********  7.清空所有信息  ***********" << endl;
	cout << endl;
}

//添加职工
void workerManager::AddEmp()
{
	cout << "请输入您想添加的职工数量：";

	int addnum = 0;//保存用户的输入数量
	cin >> addnum;
	if (addnum > 0)
	{
		//添加
		//计算添加新空间的大小
		int newsize = this->m_EmpNum + addnum;//新空间大小等于原来记录的人数 + 新增人数

		//开辟新空间
		worker ** newspace = new worker* [newsize];

		//如果原来有记录，应该先将原来的空间下的数据拷贝到新空间下
		if (this->m_EmpNum != 0)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
			//批量添加数据
		for (int i = 0; i < addnum; i++)
		{
			int id;//编号
			string name;//姓名
			int dept;//部门编号

			cout << "请输入第" << i + 1 << "位职工的编号：";
			cin >> id;

			//判断有没有重复的编号
			int sameid = IsExist(id);//传入用户输入的id，返回-1就是没有相同的,那么返回值只要不是-1那么就是有相同的
			if (sameid != -1)
			{
				cout << "添加的职工与现有职工编号相同，添加失败！" << endl;
				system("pause");   
				system("cls");     
				return;
			}
			cout << endl;
			cout << "请输入第" << i + 1 << "位职工的姓名：";
			cin >> name;
			cout << endl;
			cout << "请输入该职工的部门编号(1:普通职工  2:经理  3:老板)：";
			cin >> dept;
			cout << endl;
			//判断用户输入的部门编号是否合法
			if (dept != 1 && dept != 2 && dept != 3)
			{
				cout << "您输入的部门编号有误！添加失败" << endl;
				system("pause");
				system("cls");
				return;
			}
			worker* worker = NULL;
			switch (dept)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}
				//将创建的职工指针保存到数组中
				newspace[this->m_EmpNum + i] = worker;
			
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newspace;

		//更新职工人数
		this->m_EmpNum = newsize;

		cout << "添加成功，成功添加" << addnum << "位职工" << endl;


		//更新职工文件是否存在
		this->m_fileisempty = false;

		//成功添加后应该做一个保存到文件的操作
		this->save();
	}
	else
	{
		cout << "输入数据有误！" << endl;

	}
	system("pause");
	system("cls");

}

//保存文件
void workerManager::save()
{
	fstream ofs;
	ofs.open(filename, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "\t"
			<< this->m_EmpArray[i]->m_Name << "\t"
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}


	ofs.close();
}

//获取文件中人数
int workerManager::get_EmpNum()
{
	fstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}

	ifs.close();

	return num;
}

//初始化职工
void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	
	int id;
	string name;
	int did;

	int temp = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;

		//根据不同的部门id来创建不同的对象
		if (did == 1)
		{
			worker = new employee(id, name, 1);
		}
		else if (did == 2)
		{
			worker = new manager(id, name, 2);
		}
		else
		{
			worker = new boss(id, name, 3);
		} 
		this->m_EmpArray[temp] = worker;
		temp++;
	}



	ifs.close();
}

//显示职工信息
void workerManager::show_Emp()
{
	//首先判断文件存不存在或者数据是不是为空
	if (this->m_EmpNum == 0)	//这里直接判断当前数量是可以的，因为我们在文件不存在或者文件为空的时候将数量初始化为0
	{
		cout << "当前不存在任何职工，无法显示，请先添加职工再使用本功能" << endl;
	}
	else
	{
		//cout << "编号\t姓名\t职位" << endl;
		//for (int i = 0; i < this->m_EmpNum; i++)
		//{
		//	cout << this->m_EmpArray[i]->m_Id << "\t"
		//		<< this->m_EmpArray[i]->m_Name << "\t"
		//		<< this->m_EmpArray[i]->getDeptName() << endl;
		//}
		//这里还有第二种方法
		//我们之前在worker类中声明了一个showInfo()的函数，并分别在三个子类中进行了重写
		//所以在这里我们可以使用多态来显示
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void workerManager::del_Emp()
{
	//首先判断还有没有人
	if (this->m_EmpNum == 0)
	{
		cout << "当前不存在任何职工，无法删除，请先添加职工再使用本功能" << endl;
	}
	else
	{
		//判断职工是否存在
		cout << "请输入您想删除的职工编号：";
		int delid;
		cin >> delid;
		int temp = IsExist(delid);
		if (temp == -1)
		{
			cout << "您输入的职工编号有误！" << endl;
		}
		else
		{
			int a = 0;
			cout << "请确认您的操作，您将要删除" << delid << "号职工" << endl;
			cout << "输入1来确认操作，输入其他数返回" << endl;
			cin >> a;
			if(a == 1)
			{
				for (int i = temp; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}

				this->m_EmpNum--;
				this->save();
				cout << "删除成功！当前剩余" << this->m_EmpNum << "位职工" << endl;
			}
			else
			{
				cout << "退出删除操作" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}


//修改职工
void workerManager::mod_Emp()
{
	//还是一样，先进行判断有没有数据
	if (this->m_fileisempty)
	{
		cout << "当前不存在任何职工，无法修改，请先添加职工再使用本功能" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		//然后判断有没有对应的职工编号
		cout << "请输入您想修改的职工编号：";
		int modid;
		cin >> modid;
		int temp = IsExist(modid);
		if (temp == -1)
		{
			cout << "您输入的职工编号有误！" << endl;
		}
		else
		{
			int id;
			string name;
			int empid;
			delete this->m_EmpArray[temp];

			cout << "请输入修改后的职工编号：";
			cin >> id;
			cout << endl;

			cout << "请输入修改后的职工姓名：";
			cin >> name;
			cout << endl;

			cout << "请输入修改后的职工职位编号(1.普通员工  2.经理  3.老板)：";
			cin >> modid;
			cout << endl;

			worker* worker = NULL;
			switch (modid)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}

			this->m_EmpArray[temp] = worker;

			this->save();
			cout << "修改成功！" << endl;
		}
		system("pause");
		system("cls");
	}
}


//查找职工
void workerManager::find_Emp()
{
	//一样，首先判断当前还有没有人
	if (this->m_fileisempty)
	{
		cout << "当前不存在任何职工，无法查找，请先添加职工再使用本功能" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		//两种查找方式
		cout << "请选择您想要使用的查询方式：" << endl;
		cout << "1、按照编号查询" << endl;
		cout << "2、按照姓名查询" << endl;		//按照姓名查询有可能有多个人，因此待会得注意一下
		int usercin;
		cin >> usercin;
		if (usercin != 1 && usercin != 2)//首先做一下不是1和2的，这个简单
		{
			cout << "输入有误！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else if(usercin == 1)//按照编号查询
		{
			//判断有没有对应的职工编号
			cout << "请输入您想查找的职工编号：";
			int findid;
			cin >> findid;
			int temp = IsExist(findid);
			if (temp == -1)
			{
				cout << "您输入的职工编号有误！" << endl;
			}
			else
			{
				this->m_EmpArray[temp]->showInfo();
			}
			system("pause");
			system("cls");
		}
		else if (usercin == 2)//按照姓名查询
		{
			cout << "请输入您想查找的职工姓名：";
			string findname;
			cin >> findname;
			bool found = false; //设置一个标记
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == findname)
				{
					this->m_EmpArray[i]->showInfo();
					found = true;//如果打印了信息，把这个标记置为真
				}
			}
			if (found == false)//在for循环结束后，如果打印了信息，found应该为真，那么就不执行下面的语句；如果没有打印任何信息，found应该不会被影响，为假，就会执行下面的语句
			{
				cout << "未查询到" << findname << "的信息，请检查您输入的姓名是否有误！" << endl;
			}
			system("pause");
			system("cls");
			return;
		}
	}
}

//排序职工
void workerManager::sort_Emp()
{
	//先判断有没有
	if (this->m_fileisempty)
	{
		cout << "当前不存在任何职工，无法排序，请先添加职工再使用本功能" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照编号正序排序" << endl;
		cout << "2、按照编号逆序排序" << endl;
		int userchoice = 0;
		cin >> userchoice;

		if (userchoice != 1 && userchoice != 2)//还是一样的，先做不是1和2的
		{
			cout << "输入有误！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else if (userchoice == 1)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for(int j = 0;j < this->m_EmpNum-i-1; j++)
				{
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id)
					{
						worker* temp;
						temp = this->m_EmpArray[j];
						this->m_EmpArray[j] = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = temp;
					}
				}
			}
			cout << "排序已完成！排序后所有信息如下：" << endl;
			this->save();//排序完成后保存
			show_Emp();
		}
		else if (userchoice == 2)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for (int j = 0; j < this->m_EmpNum - i - 1; j++)
				{
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id)
					{
						worker* temp;
						temp = this->m_EmpArray[j];
						this->m_EmpArray[j] = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = temp;
					}
				}
			}
			cout << "排序已完成！排序后所有信息如下：" << endl;
			this->save();//排序完成后保存
			show_Emp();
		}
	}

}

//清空文件
void workerManager::clean_file()
{
	//有没有
	if (this->m_fileisempty)
	{
		cout << "当前记录为空，无须再清空！" << endl;
	}
	else
	{
		//首先要给用户加一层确认
		int usersure = 0;
		cout << "您将清空所有数据，本操作不可中断和撤销，请确保您并非误操作！" << endl;
		cout << "输入10086来确认清空，输入其他返回。" << endl;
		cin >> usersure;
		if (usersure != 10086)
		{
			cout << "操作已取消!" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "您将要清空所有数据，请输入管理员密码：";
			int secondsure = 0;
			cin >> secondsure;
			if (secondsure != 20040915)
			{
				cout << "密码验证错误！" << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{
				cout << "数据已清空！" << endl;
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_fileisempty = true;
				fstream ofs;
				ofs.open(filename, ios::trunc);// trunc 表示清空内容
				ofs.close();
				this->save();

			}
			system("pause");
			system("cls");
			return;
		}
	}
}

//退出程序
void workerManager::exitsystem()
{
	cout << "系统即将退出，感谢您的使用，期待与您的下次见面！" << endl;
	system("pause");//请按任意键继续
	exit(0);//退出程序函数
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}