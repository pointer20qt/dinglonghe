#include<iostream>
using namespace std;
#include<memory>


class A{
	int val;
public:
	A(int key)
	{
		val = key;
		cout << "A构造了" << endl;
	}
	int get()
	{
		return val;
	}
	~A()
	{
		cout << "A析构了" << endl;
	}
};
//引用计数类
template<class T>
class Ref{
	T*ref = nullptr;
	int _count = 0;//记录指向这个对象的指针个数
public:
	Ref(T*ptr)
	{
		ref = ptr;
		_count++;
	}
	inline void increase()
	{
		_count++;
	}
	inline void reduce()
	{
			_count--;
			if (_count == 0)//当count=0时没有指针指向这个对象，释放对象和自己；
			{
				delete ref;
				delete this;
			}
	}
	T* getobject()//获得对象
	{
		return ref;
	}
	int getcount()//获得count
	{
		return _count;
	}
};
/*
无参构造，传递指针构造，拷贝构造，移动构造，拷贝赋值，移动赋值,交换，析构函数
reset(T*)替换对象。 reset() 销毁对象
operator*() operator->()
get()获得裸指针
use_count() 获得引用计数
unique() 判断当前是否唯一  use_count()==1
operator bool() 是否关联对象
*/

//模板类实现shared_ptr智能指针
template<class T>
class d_shared_ptr
{
	Ref<T>*ref = nullptr;
public:
	d_shared_ptr() = default;
	d_shared_ptr(T*ptr)
	{
		ref = new Ref<T>(ptr);
	}
	d_shared_ptr(const d_shared_ptr<T>&temp)
	{
		ref = temp.ref;
		if (ref)
		{
			ref->increase();
		}
		
	}
	d_shared_ptr(d_shared_ptr<T>&&temp)
	{
		swap(ref,temp.ref);
	}
	d_shared_ptr& operator=(const d_shared_ptr<T>&temp)
	{
		if (ref)
		{
			ref->reduce();
		}
		ref = temp.ref;
		if (ref)
		{
			temp.ref->reduce();
		}
		return *this;
	}
	d_shared_ptr& operator=(d_shared_ptr<T>&&temp)
	{
		if (ref)
		{
			ref->reduce();
		}
		ref = temp.ref;
		temp.ref = nullptr;
		return *this;
	}
	void _swap(d_shared_ptr<T>&&temp)
	{
		swap(ref,temp.ref);
	}
	~d_shared_ptr()
	{
		if (ref)
		{
			ref->reduce();
		}
		
	}
	void reset(T*ptr=nullptr)//替换对象，如果ptr=nullptr销毁对象
	{
		if (ref)
		{
			ref->reduce();
		}
		if (ptr != nullptr)
		{
			ref = new Ref<T>(ptr);
		}
		else
		{
			ref = nullptr;
		}
	}
	T& operator*()
	{
		if (ref)
		{
			return *(ref->getobject());
		}
		else
		{
			return *((T*)nullptr);
		}
	}
	T* operator->()
	{
		if (ref)
		{
			return ref->getobject();
		}
		else
		{
			return (T*)nullptr;
		}
	}
	T* returnobject()//获得指针指向（对象）
	{
		if (ref)
		{
			return ref->getobject();
		}
		else
		{
			return (T*)nullptr;
		}
	}
	int use_count()//获得引用计数
	{
		if (ref)
		{
			return ref->getcount();
		}
		else
		{
			return 0;
		}
	}
	bool unique()// 判断当前（指针）是否唯一（指向对象）
	{
		if (ref)
		{
			return ref->getcount() == 1;
		}
		return false;
	}
	operator bool()
	{
		return ref != nullptr;
	}
};
int main()
{
	d_shared_ptr<A> ptr1(new A(2));
	d_shared_ptr<A>ptr2(move(ptr1));
	d_shared_ptr<A>ptr3 = move(ptr2);
	cout << "val:"<<ptr3->get() << endl;
	cout << "引用数："<<ptr1.use_count() << endl;
	cout << "当前是否唯一：" << ptr3.unique() << endl;
	cout << "是否关联对象：" << ptr3.operator bool() << endl;
	return 0;
	system("pause");
}