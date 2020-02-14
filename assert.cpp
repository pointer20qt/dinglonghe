#include <iostream>
using namespace std;
#include <vector>
#define NDEBUG
#include<assert.h>

class vec{
	vector<int> ve;
public:
	vec(const initializer_list<int>& list) :ve(list)
	{	
	}
	int& operator[](int index)
	{
		assert(index>=0&&index<=ve.size());//断言，当为false的时候在程序执行的时候会停止运行并报告错误在哪里
		return ve[index];
	}
};
static_assert(!is_empty<vec>::value,"class vec is not empty");
 //静态断言static_assert(常量表达式，提示字符串)，如果第一个参数常量表达式的值为真(true或者非零值)，
 //那么static_assert不做任何事情，就像它不存在一样，否则会产生一条编译错误
  //错误位置就是该static_assert语句所在行，错误提示就是第二个参数提示字符串
int main()
{
	vec ve = { 1, 2, 3, 4, 5 };
	cout << ve[-1] << endl;
	system("pause");
	return 0;
}
