#include <iostream>
using namespace std;
#include <vector>
#include<string>

using it = int;
class A
{
	friend class school;
public:
	
private:
	it a;

};

class school
{
public:
	string schoolname;
	string schooladress;
	A A1;

	school(string name, string adress, int a1) :schoolname(name), schooladress(adress)
	{                    
		A1.a = a1;
	}
};



int main1()
{
	school sc("aa","ss",10);
    	return 0;
	system("pause");
}


