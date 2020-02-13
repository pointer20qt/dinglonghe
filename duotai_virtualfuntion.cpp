#include <iostream>
using namespace std;
#include <string>

/*兰話一:
今天任务1：子类对象父类指针实现多态效果

兰話一:
实现虚析构。实现 隐藏。
*/
class school
{
public:
	string schoolname;
	string schooladress;
	school() = default;

	void show()
	{
		cout << "这是学校的基类"<< endl;
	}
	void show(string str)
	{
		cout<<str << "这是学校的基类" << endl;
	}
};

class university :public school
{
public:
	university(string name, string adress)
	{
		this->schoolname = name;
		this->schooladress = adress;
	}
	void show()  //当子类中有和父类中函数名字相同的函数时，会隐藏掉父类中所有该函数名的函数；
		         //可以通过显示的方法掉用父类中被隐藏掉的函数（u.school::show("大学");）
	{
		cout << schoolname << "在" << schooladress << endl;
	}
};

class highschool :public school
{
public:
	highschool(string name, string adress)
	{
		this->schoolname = name;
		this->schooladress = adress;
	}
	void show()
	{
		cout << schoolname << "在" << schooladress << endl;
	}
};

int main1()
{
	university u("东游","大庆");
	u.show();
	u.school::show("大学");
	system("pause");
	return 0;
}