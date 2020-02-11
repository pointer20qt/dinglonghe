#include <iostream>
using namespace std;
#include <vector>
#include<string>

class school
{
public:
	string schoolname;
	string schooladress;
	int * master=new int;
	school() = default;
	 school(string name, string adress,int master)
	{
		
		this->schoolname = name;
		this->schooladress = adress;
		*this->master = master;
	}
	 school(const school&sc)
	 {
		 cout << "走了拷贝构造函数" << endl;
		 this->schooladress = sc.schooladress;
		 this->schoolname = sc.schoolname;
		 this->master = new int(*(sc.master));
	 }

	 ~school()
	 {
		 delete master;
		 master = NULL;
		 cout << "走了析构函数" << endl;
	 }
};



int main1()
{
	int a = 8;
    auto sc=new school("东油","大庆",8);
	school sc1(*sc);
	cout << sc->schooladress << " sc" << sc->schoolname << " " << *sc->master << endl;
	cout << sc1.schooladress <<" sc1"<< sc1.schoolname << " "<<*sc1.master << endl;
	//delete sc;
    	return 0;
	system("pause");
}


