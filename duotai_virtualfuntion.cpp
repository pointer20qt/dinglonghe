#include <iostream>
using namespace std;
#include <string>

/*��Ԓһ:
��������1�����������ָ��ʵ�ֶ�̬Ч��

��Ԓһ:
ʵ����������ʵ�� ���ء�
*/
class school
{
public:
	string schoolname;
	string schooladress;
	school() = default;

	void show()
	{
		cout << "����ѧУ�Ļ���"<< endl;
	}
	void show(string str)
	{
		cout<<str << "����ѧУ�Ļ���" << endl;
	}
};

class university :public school
{
public:
	university(string name, string adress)
	{
		this->schoolname = name;
		this->schooladress = adress;
	}
	void show()  //���������к͸����к���������ͬ�ĺ���ʱ�������ص����������иú������ĺ�����
		         //����ͨ����ʾ�ķ������ø����б����ص��ĺ�����u.school::show("��ѧ");��
	{
		cout << schoolname << "��" << schooladress << endl;
	}
};

class highschool :public school
{
public:
	highschool(string name, string adress)
	{
		this->schoolname = name;
		this->schooladress = adress;
	}
	void show()
	{
		cout << schoolname << "��" << schooladress << endl;
	}
};

int main1()
{
	university u("����","����");
	u.show();
	u.school::show("��ѧ");
	system("pause");
	return 0;
}