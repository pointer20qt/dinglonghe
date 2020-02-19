#include <iostream>
using namespace std;
#include<time.h>

/*兰話一:
作业rand练习：(练习并理解)
//怎么通过rand生成[0,a)的数
//怎么通过rand生成[a,b)的数
//怎么生成一个0~1的随机小数double
//怎么生成a~b的随机小数
//传入0到100的整数，概率性判断成功,成功返回true
//传入0到1的double，概率性判断成功，成功返回ture。

兰話一:
rand()从随机数序列中取下一个    srand(time(0)) 初始化随机数序列
*/
int true1 = 0;
int false1 = 0;
int fun1()
{
	int temp = rand() % 5 + 15;
	return temp;
}

bool fun(int n)
{
	int temp = rand()%100;
	if (temp >= n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool fun(double n)
{
	double temp = rand()/(double)(RAND_MAX);
	if (temp < n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand(time(0));

	for (int i = 0; i < 100; i++)
	{
		if (fun(0.8))
		{
			true1++;
		}
		else
		{
			false1++;
		}
	}
	cout << "成功的：" << true1 << endl;
	cout << "失败的：" << false1 << endl;
	cout << fun1() << endl;;
	return 0;
	system("pause");
}
