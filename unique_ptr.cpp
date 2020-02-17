#include <iostream>
using namespace std;
#include <memory>
/*任务1：unique_ptr练习实现
任务2：shared_ptr实现，weak_ptr实现*/
class A
{
public:
	A()
	{
		cout << "A构造了" << endl;
	}
	~A()
	{
		cout << "A析构了" << endl;
	}
};
int main()
{
	unique_ptr<A>ptr1(new A());
	unique_ptr<A>ptr2(move(ptr1)); //可以移动构造
	unique_ptr<A>ptr3 = move(ptr2);//可以移动赋值
	return 0;
	system("pause");
}
