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
		assert(index>=0&&index<=ve.size());//���ԣ���Ϊfalse��ʱ���ڳ���ִ�е�ʱ���ֹͣ���в��������������
		return ve[index];
	}
};
static_assert(!is_empty<vec>::value,"class vec is not empty");
 //��̬����static_assert(�������ʽ����ʾ�ַ���)�������һ�������������ʽ��ֵΪ��(true���߷���ֵ)��
 //��ôstatic_assert�����κ����飬������������һ������������һ���������
  //����λ�þ��Ǹ�static_assert��������У�������ʾ���ǵڶ���������ʾ�ַ���
int main()
{
	vec ve = { 1, 2, 3, 4, 5 };
	cout << ve[-1] << endl;
	system("pause");
	return 0;
}
