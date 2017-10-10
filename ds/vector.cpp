#include <iostream>
#include <ctime>
template <typename T>
class dlist
{
private:
	
	struct dnode
	{
		dnode(T data, dnode *prev=0, dnode * next=0): data(data), prev(prev), next(next) {}
		~dnode() {if(next) delete next;}		
		T data;
		dnode *prev, *next;
	}*head, *tail;

public:
	dlist(): head(0), tail(0){}
	~dlist() {if (head) delete head; } 
	void push_front(T data)
	{
		if(head)
		{
			dnode *temp  = new dnode(data, 0, head);
			head->prev = temp;
			head = temp;
			temp = 0;
		}
		else
		{
			tail = head = new dnode(data);
		}
	}
	void push_back(T data)
	{
		if(tail)
		{
			dnode *temp  = new dnode(data, tail, 0);
			tail->next = temp;
			tail = temp;
			temp = 0;
		}
		else
		{
			tail = head = new dnode(data);
		}
	}
	T pop_front()
	{
		if(head)
		{	
			dnode *temp = head;
			head = head->next;
			if(head) //valid head
				head->prev = temp->next = 0;
			else //at end of list, popped last
				tail = 0;
			delete temp;
		}
	}
	T pop_back()
	{
		if(tail)
		{	
			dnode *temp = tail;
			tail = tail->prev;
			if(tail)
				tail->next = temp->prev = 0;
			else
				head = 0;
			delete temp;
		}
	}

	//TODO
	T remove(T data)
	{
		dnode *cur = head;
		while(cur && cur->data != data)
			cur = cur->next;
		if(cur)
		{
			//found
			if(! cur->prev ) //head
			{
				return pop_front();
			}
			else if(! cur->next ) //tail
			{
				return pop_back();
			}
			else
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				cur->next = cur->prev = 0;
				delete cur;
			}
		}			
			
	}
	T insert(int i, T value)
	{
		dnode *cur = head;
		for(; cur && i > 0 ; cur = cur->next, i--);
		if(cur)
		{

			//add node in front of cur
			dnode* temp = new dnode(value, cur->prev, cur);
			if(cur->prev)
				cur->prev->next = temp;
			else
				head = temp;
			cur->prev = temp;
			if(! temp->next) tail = temp; 
			cur = 0;
			temp = 0;
		}
		else //too far!
		{
		}
	}	
	
	void print()
	{
		std::cout << '\n';
		for(dnode *cur = head; cur; cur = cur->next)
			std::cout << cur->data << ' ';
	}
	void print_reverse()
	{
		std::cout << '\n';
		for(dnode *cur = tail; cur; cur = cur->prev)
			std::cout << cur->data << ' ';
	}
};



main()
{
	dlist<int> list;
	for(int i =0; i < 10; i++)
		list.push_back(i);
	for(int i =10; i < 20; i++)
		list.push_front(i);
	
	list.remove(0);
	list.remove(19);
	list.remove(5);
	list.remove(10);

	list.insert(2, 1000);
	list.insert(2, 2000);
	list.insert(7, 3000);

	list.insert(0, 9000);
	list.print();
	list.print_reverse();

	
	return 0;
}
