#include<iostream>
using namespace std;
#include<memory>


class A{
	int val;
public:
	A(int key)
	{
		val = key;
		cout << "A������" << endl;
	}
	int get()
	{
		return val;
	}
	~A()
	{
		cout << "A������" << endl;
	}
};
//���ü�����
template<class T>
class Ref{
	T*ref = nullptr;
	int _count = 0;//��¼ָ����������ָ�����
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
			if (_count == 0)//��count=0ʱû��ָ��ָ����������ͷŶ�����Լ���
			{
				delete ref;
				delete this;
			}
	}
	T* getobject()//��ö���
	{
		return ref;
	}
	int getcount()//���count
	{
		return _count;
	}
};
/*
�޲ι��죬����ָ�빹�죬�������죬�ƶ����죬������ֵ���ƶ���ֵ,��������������
reset(T*)�滻���� reset() ���ٶ���
operator*() operator->()
get()�����ָ��
use_count() ������ü���
unique() �жϵ�ǰ�Ƿ�Ψһ  use_count()==1
operator bool() �Ƿ��������
*/

//ģ����ʵ��shared_ptr����ָ��
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
	void reset(T*ptr=nullptr)//�滻�������ptr=nullptr���ٶ���
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
	T* returnobject()//���ָ��ָ�򣨶���
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
	int use_count()//������ü���
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
	bool unique()// �жϵ�ǰ��ָ�룩�Ƿ�Ψһ��ָ�����
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
	cout << "��������"<<ptr1.use_count() << endl;
	cout << "��ǰ�Ƿ�Ψһ��" << ptr3.unique() << endl;
	cout << "�Ƿ��������" << ptr3.operator bool() << endl;
	return 0;
	system("pause");
}