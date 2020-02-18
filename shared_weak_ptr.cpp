#include<iostream>
using namespace std;
#include<memory>


//引用计数类
template<class T>
class Ref{
	T*ref = nullptr;
	int _count = 0;//记录指向这个对象的指针个数
	int w_count = 0;//记录弱引用指针的个数。
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
	inline void increase_w()
	{
		w_count++;
	}
	inline void reduce()
	{
			_count--;
			if (_count == 0)//释放对象；
			{
				delete ref;
				ref = nullptr;
				if (w_count==0)//释放自己；
				{
					delete this;
				}	
			}
	}
	inline void reduce_w()
	{
		w_count--;
		if (w_count&&_count == 0)//释放对象和自己；
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

//模板类实现shared_ptr智能指针
template<class T> class d_weak_ptr;
template<class T>
class d_shared_ptr
{
	friend class d_weak_ptr<T>;
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
			temp.ref->increase();
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
	T& operator* ()
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

//模板类实现weak_ptr智能指针
template<class T>
class d_weak_ptr{
	Ref<T>*ref=nullptr;
public:
	d_weak_ptr()
	{
		cout << "无参d_weak_ptr构造了" << endl;
	}
	d_weak_ptr(d_shared_ptr<T>& temp) 
	{
		ref=temp.ref;
		if (ref)
		{
			ref->increase_w();
			
		}
		cout << "有参d_weak_ptr构造了" << endl;
	}
	~d_weak_ptr()
	{
		if (ref)
		{
			ref->reduce_w();
		}
		cout << "d_weak_ptr析构了" << endl;
	}
	d_weak_ptr( d_weak_ptr<T>&& temp)
	{
		swap(ref,temp.ref);
	}
	d_weak_ptr(const d_weak_ptr<T>& temp)
	{
		ref = temp.ref;
		if (ref)
		{
			ref->increase_w();
		}
	}
	d_weak_ptr<T>& operator=(const d_weak_ptr<T>& temp)
	{
		if (ref)
		{
			ref->reduce_w();
		}
		ref = temp.ref;
		if (ref)
		{
			ref->increase_w();
		}
		return *this;
	}
	d_weak_ptr<T>& operator=(d_weak_ptr<T>&& temp)
	{
		if (ref)
		{
			ref->reduce_w();
		}
		ref = temp.ref;
		temp.ref = nullptr;
		return *this;
	}
	int use_count()//返回管理该对象的shared_pre对象数量
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
	bool expired()//检测引用对象是否已被删除
	{
		if (ref)
		{
			return ref->getcount() > 0;
		}
		return false;
	}
	d_shared_ptr<T> lock()//创建管理被引用的对象的shared_ptr
	{
		d_shared_ptr<T> temp;
		temp.ref = ref;
		if (temp.ref)
		{
			temp.ref->increase();
		}
		return temp;
	}
	void swap_w(d_weak_ptr<T>&temp)
	{
		swap(ref,temp.ref);
	}
	void reset()//释放管理对象的所有权
	{
		if (ref)
		{
			ref->reduce();
			ref = nullptr;
		}
	}
};

struct Node{

	/*d_shared_ptr<Node> _next;
	d_shared_ptr<Node> _pre;*/
	d_weak_ptr<Node> _next;
	d_weak_ptr<Node> _pre;
	Node()
	{
		cout << "构造了" << endl;
	}
	~Node()
	{
		cout << "析构了" << endl;
	}
};
int main()
{
	d_shared_ptr<Node> node1(new Node());
	d_shared_ptr<Node> node2(new Node());
	cout << node1.use_count() << endl;
	node1->_next = node2;//调用d_weak_ptr的构造函数（构造一个d_weak_ptr临时对象）
	                     //->d_shared_ptr的‘operator->'->d_weak_ptr临时对象的移动赋值->析构掉临时对象
	node2->_pre = node1;
	cout << node1.use_count() << endl;
	return 0;
	system("pause");
}