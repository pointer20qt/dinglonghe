#include <iostream>
using namespace std;
#include <vector>
/*��ϰģ�庯����������ʽ�Ƶ�����ʽ�Ƶ���ָ��ģ���Ƶ���ʵ��swap���������swap��ǳ��������*/


template<class T,class T2>
void swap1(T& a, T2& b)
{
	T temp = a;
	a = b;
	b = temp;
	cout << "�����˺���ģ�庯��" << endl;
}

void swap1(int& a, double &b)
{
	int temp = a;
	a = b;
	b = temp;
	cout << "��������ͨ����" << endl;
}
class A
{
public:
	int* num;
	A(int n)
	{
		num = new int(n);
	}
	//A(const A&temp)//��ֹ���ù��캯��ǳ����
	//{
	//	this->num = new int(*(temp.num));
	//}
	//void operator=(const A&temp) //��ֹ���Ƹ�ֵ��=����ʱ��ǳ������
	//{
	//	delete num;
	//	this->num = new int(*(temp.num));
	//}
	~A()
	{
		delete num;
		cout << "������" << endl;
	}
};
int main()
{
	int x1 = 2;
	double y1 = 1.2;
	swap1(x1,y1); //��ʽ�Ƶ���ģ��Ĳ������ͣ�x1,y1����ֵ���ͣ����Ǻ���ģ�������ֻ��һ����template<class T>��
	               //��x1,y1������ͬ������,
	swap1<int, double>(x1, y1);//��ʾ��ʽָ��ģ����������ͣ�ģ���еĲ�����������x1,y1��ͬ
	swap1<>(x1,y1);//��������ͬ����ͨ�������뺯��ģ��ʵ������ͬ�Ĺ��������ȵ�����ͨ������
	cout << x1 << " " << y1 << endl;

	A* a1 = new A(6);    //����ģ���д����Զ����������Ҳͬ��ͨ����һ����
	A*a2=new A(7); 
	swap1(a1,a2);
	cout << *(a1->num )<< " " << *(a2->num) << endl;
	delete a1;
	delete a2;
	system("pause");
	return 0;
}
