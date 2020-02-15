#include <iostream>
using namespace std;
#include <vector>
/*兰話一:
作业2：类模板封装vector实现stack

兰話一 :
作业3：模板参数包的递归拆包*/

template<class T>
class stack{
	vector<T> vec;
public:
	void push(T&&num) //利用‘&&’可以传入常数的引用
	{
		vec.push_back(num);
	}
	void pop()
	{
		vec.pop_back();
	}
	T top()
	{
		return vec.back();//返回数组的最后一个元素
	}
	size_t size()  //'size_t' 相当于 unsigned int 类型
	{
		return vec.size();
	}
};
int main1()
{
	stack<int> s;
	s.push(5);
	s.push(6);
	s.push(7);
	cout << s.top() << endl;
	s.pop();
	cout << s.size() << endl;
	system("pause");
	return 0;
}
