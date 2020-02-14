#include <iostream>
using namespace std;
#include <vector>
class vec{
	int *ve;
public:
	vec(const initializer_list<int>& list)
	{
		cout << "调用初始化列表构造函数" << endl;
		ve = new int[list.size()];
		for (int i = 0; i < list.size();i++)
		{
			ve[i] = *(list.begin() + i);
		}
		for (int i = 0; i <list.size(); i++)
		{
			cout << ve[i] << " " << endl;
		}
	}
	vec(int i1)
	{
		cout << "调用单参数构造函数" << endl;
	}
	vec(int i1, int i2)
	{
		cout << "调用2个参数的构造函数" << endl;
	}
	int& operator[](int index)//重载[]
	{
		return ve[index];
	}
};


int main()
{

	vector<int> v = {1,2,3,4,5};//STL支持初始化列表，自定义的类也支持初始化列表，统一用{}初始化
	//对构造函数的优先级选择，当有初始化列表构造函数时，优先选择初始化列表构造函数
	//没有时再选择其他的构造函数
	vec ve = { 1, 2, 3, 4, 5 };
	cout << ve[2] << endl;
	ve[2] = 19;
	cout << ve[2] << endl;
	vec ve1{ 1 };
	vec ve2{ 1, 2 };
	system("pause");
	return 0;
}
