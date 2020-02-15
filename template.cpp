#include <iostream>
using namespace std;
#include <vector>
/*练习模板函数，掌握显式推导，隐式推导，指定模板推导。实现swap函数，解决swap的浅拷贝问题*/


template<class T,class T2>
void swap1(T& a, T2& b)
{
	T temp = a;
	a = b;
	b = temp;
	cout << "调用了函数模板函数" << endl;
}

void swap1(int& a, double &b)
{
	int temp = a;
	a = b;
	b = temp;
	cout << "调用了普通函数" << endl;
}
class A
{
public:
	int* num;
	A(int n)
	{
		num = new int(n);
	}
	//A(const A&temp)//防止调用构造函数浅拷贝
	//{
	//	this->num = new int(*(temp.num));
	//}
	//void operator=(const A&temp) //防止复制赋值‘=’的时候浅拷贝。
	//{
	//	delete num;
	//	this->num = new int(*(temp.num));
	//}
	~A()
	{
		delete num;
		cout << "析构了" << endl;
	}
};
int main()
{
	int x1 = 2;
	double y1 = 1.2;
	swap1(x1,y1); //隐式推导出模板的参数类型（x1,y1的数值类型）若是函数模板参数中只有一个（template<class T>）
	               //则x1,y1需是相同的类型,
	swap1<int, double>(x1, y1);//显示方式指出模板参数的类型，模板中的参数类型需与x1,y1相同
	swap1<>(x1,y1);//若是有相同的普通函数，与函数模板实现了相同的功能则优先调用普通函数。
	cout << x1 << " " << y1 << endl;

	A* a1 = new A(6);    //向函数模板中传入自定义的数据类也同普通类型一样。
	A*a2=new A(7); 
	swap1(a1,a2);
	cout << *(a1->num )<< " " << *(a2->num) << endl;
	delete a1;
	delete a2;
	system("pause");
	return 0;
}
