#include <iostream>
using namespace std;
#include <vector>
/*��Ԓһ:
��ҵ2����ģ���װvectorʵ��stack

��Ԓһ :
��ҵ3��ģ��������ĵݹ���*/

template<class T>
class stack{
	vector<T> vec;
public:
	void push(T&&num) //���á�&&�����Դ��볣��������
	{
		vec.push_back(num);
	}
	void pop()
	{
		vec.pop_back();
	}
	T top()
	{
		return vec.back();//������������һ��Ԫ��
	}
	size_t size()  //'size_t' �൱�� unsigned int ����
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
