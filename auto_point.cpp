#include <iostream>
using namespace std;
#include<memory>



class A{
public:
	int value;
	A()
	{
		cout << "构造了" << endl;
	}
	A(int n)
	{
		value = n;
		cout << "构造了" << endl;
	}
	~A()
	{
		cout << "析构了" << endl;
	}
};

template<class T>
class d_auto_ptr{
public:
	T*ptr = nullptr;
	d_auto_ptr() = default;
	d_auto_ptr(T*p)
	{
		ptr = p;
	}
	d_auto_ptr(d_auto_ptr<T>&p)
	{
		ptr = p.ptr;
		p.ptr = nullptr;
	}
	void operator=(d_auto_ptr<T>&p)
	{
		delete ptr;
		ptr = p.ptr;
		p.ptr = nullptr;
	}
	void reset(T*newptr)
	{
		delete ptr;
		ptr = newptr;
	}
	T* release()
	{
		T*temp = ptr;
		ptr = nullptr;
		return temp;
	}
	T& operator*()
	{
		return *ptr;
	}
	T* operator->()
	{
		return ptr;
	}
	T* get()
	{
		return ptr;
	}
	~d_auto_ptr()
	{
		delete ptr;
	}
};

void fun()
{
	d_auto_ptr<A> pa{new A(4)};
	d_auto_ptr<A>pa1(pa);
	d_auto_ptr<A>pa2;
	pa2 = pa1;
	cout << pa2->value << endl;
	cout << (*pa2).value << endl;
	pa2.get();

}

int main()
{
	
  // auto_ptr<A>ptr{ new A() };//只能指针出了作用域后会自动释放掉所指对象，‘{}’也可用‘（）’
	fun();
   return 0;
	system("pause");
}