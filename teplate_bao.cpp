#include <iostream>
using namespace std;



void print()
{
	cout << "µÝ¹é²ð°ü½áÊø" << endl;
}
void print(const char *d2)
{
	cout << d2 << " ";
	print();
}
void print(double d1,const char*d2)
{
	cout << d1 << " ";
	print(d2);
}
void print(int f,double d1,const char* d2)
{
	cout << f << " ";
	print(d1,d2);
}

//template<class T,class...args>
//void print(T t,args... d)
//{
//	cout << t << " ";
//	print(d...);
//}

int main()
{
	print(1,3.5,"hello");
	system("pause");
	return 0;
}