#include <iostream>
using namespace std;
#include <string>

/*兰話一:
今天任务1：子类对象父类指针实现多态效果

实现纯虚函数

兰話一:
实现虚析构。实现 隐藏。
*/
class school
{
public:
	virtual void show() = 0;
};

class highschool :public school
{
public:
	void show()
	{
		cout << "highschool中的show()" << endl;
	}
};
int main()
{  
	
	highschool h;
	h.show();
	system("pause");
	return 0;
}