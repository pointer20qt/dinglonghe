#include<iostream>
using namespace std;
#include<memory>

class Node
{
public:
	int val;
	weak_ptr<Node> _next;
	weak_ptr<Node> _pre;
	/*shared_ptr<Node>  _next;
	shared_ptr<Node>  _pre;*/
	Node(int key)
	{
		val = key;
		cout << "Node构造了" << endl;
	}
	~Node()
	{
		cout << "Node析构了" << endl;
	}
};

int main()
{
	shared_ptr<Node> node1(new Node(1));
	shared_ptr<Node> node2(new Node(2));
	node1->_next = node2;
	node2->_pre = node1;
	return 0;
	system("pause");
}