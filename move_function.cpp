#include <iostream>
using namespace std;
#include <vector>

class B
{
public:
	int *a;
	B(int*a1 )
	{
		cout << "�����вι��캯��" << endl;
		this->a = a1;
	}

	B(B&&temp)
	{
		this->a = temp.a;
		temp.a = NULL;
		cout << "�����ƶ����캯��" << endl;
	}
};

B fun()
{
	B b(new int(10));
	return b;
}


int main()
{
	B b1(fun());
	system("pause");
	return 0;
}