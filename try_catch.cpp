#include <iostream>
using namespace std;
#include <vector>



int main()
{

	vector<int>v = {1,2,3,4,5,6};
	try
	{
		cout << v.at(6) << endl;
	}
	catch (out_of_range&e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}