#include <iostream>
using namespace std;
#include <string>

/*��Ԓһ:
��������1�����������ָ��ʵ�ֶ�̬Ч��

ʵ�ִ��麯��

��Ԓһ:
ʵ����������ʵ�� ���ء�
*/
class school
{
public:
	virtual void show() = 0;
};

class highschool :public school
{
public:
	void show()
	{
		cout << "highschool�е�show()" << endl;
	}
};
int main()
{  
	
	highschool h;
	h.show();
	system("pause");
	return 0;
}