#include <iostream>
using namespace std;
#include <vector>
class vec{
	int *ve;
public:
	vec(const initializer_list<int>& list)
	{
		cout << "���ó�ʼ���б��캯��" << endl;
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
		cout << "���õ��������캯��" << endl;
	}
	vec(int i1, int i2)
	{
		cout << "����2�������Ĺ��캯��" << endl;
	}
	int& operator[](int index)//����[]
	{
		return ve[index];
	}
};


int main()
{

	vector<int> v = {1,2,3,4,5};//STL֧�ֳ�ʼ���б��Զ������Ҳ֧�ֳ�ʼ���б�ͳһ��{}��ʼ��
	//�Թ��캯�������ȼ�ѡ�񣬵��г�ʼ���б��캯��ʱ������ѡ���ʼ���б��캯��
	//û��ʱ��ѡ�������Ĺ��캯��
	vec ve = { 1, 2, 3, 4, 5 };
	cout << ve[2] << endl;
	ve[2] = 19;
	cout << ve[2] << endl;
	vec ve1{ 1 };
	vec ve2{ 1, 2 };
	system("pause");
	return 0;
}
