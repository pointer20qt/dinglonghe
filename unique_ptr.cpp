#include <iostream>
using namespace std;
#include <memory>
/*����1��unique_ptr��ϰʵ��
����2��shared_ptrʵ�֣�weak_ptrʵ��*/
class A
{
public:
	A()
	{
		cout << "A������" << endl;
	}
	~A()
	{
		cout << "A������" << endl;
	}
};
int main()
{
	unique_ptr<A>ptr1(new A());
	unique_ptr<A>ptr2(move(ptr1)); //�����ƶ�����
	unique_ptr<A>ptr3 = move(ptr2);//�����ƶ���ֵ
	return 0;
	system("pause");
}
