#include<iostream>
using namespace std;
#include<memory>


//���ü�����
template<class T>
class Ref{
	T*ref = nullptr;
	int _count = 0;//��¼ָ����������ָ�����
	int w_count = 0;//��¼������ָ��ĸ�����
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
			if (_count == 0)//�ͷŶ���
			{
				delete ref;
				ref = nullptr;
				if (w_count==0)//�ͷ��Լ���
				{
					delete this;
				}	
			}
	}
	inline void reduce_w()
	{
		w_count--;
		if (w_count&&_count == 0)//�ͷŶ�����Լ���
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

//ģ����ʵ��shared_ptr����ָ��
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

//ģ����ʵ��weak_ptr����ָ��
template<class T>
class d_weak_ptr{
	Ref<T>*ref=nullptr;
public:
	d_weak_ptr()
	{
		cout << "�޲�d_weak_ptr������" << endl;
	}
	d_weak_ptr(d_shared_ptr<T>& temp) 
	{
		ref=temp.ref;
		if (ref)
		{
			ref->increase_w();
			
		}
		cout << "�в�d_weak_ptr������" << endl;
	}
	~d_weak_ptr()
	{
		if (ref)
		{
			ref->reduce_w();
		}
		cout << "d_weak_ptr������" << endl;
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
	int use_count()//���ع���ö����shared_pre��������
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
	bool expired()//������ö����Ƿ��ѱ�ɾ��
	{
		if (ref)
		{
			return ref->getcount() > 0;
		}
		return false;
	}
	d_shared_ptr<T> lock()//�����������õĶ����shared_ptr
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
	void reset()//�ͷŹ�����������Ȩ
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
		cout << "������" << endl;
	}
	~Node()
	{
		cout << "������" << endl;
	}
};
int main()
{
	d_shared_ptr<Node> node1(new Node());
	d_shared_ptr<Node> node2(new Node());
	cout << node1.use_count() << endl;
	node1->_next = node2;//����d_weak_ptr�Ĺ��캯��������һ��d_weak_ptr��ʱ����
	                     //->d_shared_ptr�ġ�operator->'->d_weak_ptr��ʱ������ƶ���ֵ->��������ʱ����
	node2->_pre = node1;
	cout << node1.use_count() << endl;
	return 0;
	system("pause");
}