/*
Paul Miller

Compile:
	gcc -lstdc++ list_1.cpp -o list_1 
	or 
	g++ list_1.cpp -o list_1

Goal:
	A very minimal singly linked list implementation. 
*/

//-------------------------------------Decls-------------------------------

#include <iostream>
//forward declare list class
template <typename T>
class SList; 

//Singly linked Node, element of singly linked list
template <typename T>
class SNode
{
	public:
		SNode(T value) :value(value), p_next(0){}
		~SNode();
		template <typename U>
		friend class SList; 
		template <typename U>
		friend class SIterator;
	private:
		T value;
		SNode<T>* p_next; //pointer to next node 
};

//SList Iterator class to abstract node access
template <typename T>
class SIterator
{
	public:
		SIterator(): node(0){}
		SIterator(SNode<T>* node): node(node){}
		SIterator(const SIterator<T>& other): node(other.node){}
		//dereferance operator to get access to pointer value
		friend bool operator==(const SIterator<T>& l,const SIterator<T>& r) {return l.node == r.node;}
		friend bool operator!=(const SIterator<T>& l,const SIterator<T>& r) {return !(l.node == r.node);}				
		T& operator*();
		//move to next node
		SIterator<T> operator++(); //prefix
		SIterator<T> operator++(int ); //postfix
		inline bool empty() {return node == 0;}
	private:
		SNode<T> *node;
};

//Singly-Linked list
template <typename T>
class SList
{
	public: 
		SList(): p_front(0), p_back(0), length(0) {}
		SList(const SList & other);
		~SList();
		void push_front(T value);
		T pop_front();
		void push_back(T value);
		T pop_back();

		inline SIterator<T> begin() const 
		{
			return SIterator<T>(p_front);
		}
		inline SIterator<T> end() const 
		{
			if(p_back) return SIterator<T>(p_back->p_next);
			return SIterator<T>();
		}
	private:
		SNode<T> *p_front, *p_back; //pointer to front and back node
		int length;
};
template <typename T>
SNode<T>::~SNode()
{
	//delete next before self
	std::cout << "\nDeleting " << value; //debug, to ensure all nodes are deleted
	if(p_next) delete p_next;
}

//----------------------------------Iterator Defs-------------------------------------------
template <typename T>
T& SIterator<T>::operator*()
{
	if(node)
		return node->value;
	return *(new T()); //return default type object
}
//move to next node
template <typename T>
SIterator<T> SIterator<T>::operator++()
{
	if(node)
		node=node->p_next;
	return *this; //return current instance
} 
template <typename T>
SIterator<T> SIterator<T>::operator++(int)
{
	//save old iterator, update this then return old state
	SIterator<T> prev = *this;
	if(node)
		node=node->p_next;
	return prev; //return current instance
} 
//----------------------------------List Defs-------------------------------------------
template <typename T>
SList<T>::SList(const SList & other)
{
	delete p_front.node;
	for(SIterator<T> it = other.begin(); it != other.end(); it++)
		this->push_back(*it);		
}
template <typename T>
SList<T>::~SList()
{
	if(p_front) 
		delete p_front; 
}

template <typename T>
void SList<T>::push_front(T value)
{
	SNode<T> *new_node = new SNode<T>(value);
	//if p_front is empty so is entire list
	if(p_front == 0)
		p_front = p_back = new_node;
	else
	{
		new_node->p_next = p_front;
		p_front = new_node;
	}	
	length++;
}
template <typename T>
T SList<T>::pop_front()
{
	if(p_front)
	{
		//point to old front
		SNode<T> * temp = p_front;
		//move front to the next node
		p_front = p_front->p_next;
		//disconnect old front
		temp->p_next = 0;
		delete temp; 
	}
}
template <typename T>
void SList<T>::push_back(T value)
{
	SNode<T> *new_node = new SNode<T>(value);
	//if p_front is empty so is entire list
	if(p_back == 0)
	{	
		p_front = p_back = new_node;
	}
	else
	{
		p_back->p_next=new_node;
		p_back = new_node;
	}
	length++;
}
template <typename T>
T SList<T>::pop_back()
{
	//is there a better way to find the node before back?
	SNode<T> *temp = p_front;
	while(temp)
	{
 		//if next node is the back
		if(temp->p_next == p_back)
		{
			p_back = temp;	
			delete temp->p_next;
			temp->p_next = 0;
		}				
		temp = temp->p_next;
	}
}

template <typename T>
void print(const SList<T> &list)
{
	std::cout << "\nList:";
	for(SIterator<T> it = list.begin(); it != list.end(); it++)
		std::cout << *it << ' ';
}

template <typename T>
void print_middle(const SList<T> &list)
{
	std::cout << "\nList Middle:";
	SIterator<T> mid = list.begin(); 
	for(SIterator<T> it = list.begin(); ++it != list.end(); ++it)
	{
		mid++; 
	}
	std::cout << *mid << ' ';
}

template <typename T>
void print_reverse(SIterator<T> it)
{
	if(! it.empty())
	{
		T val = *it;
		print_reverse(++it);
		std::cout << val << ' ';
	}
}


main()
{
	//TRY:	
	// By iterating over the list once:
	//	find the middle of the list (use two pointers!)
	//	print the nodes in reverse
	SList<int> list;
	list.push_back(4);
	list.push_back(5);
	list.push_front(3);
	list.push_front(2);
	list.push_back(6);
	list.push_front(1);
	list.pop_front();
	list.pop_back();
	list.push_front(1);
	//prints
	print(list);
	print_middle(list);
	std::cout << "\nList Reverse:";
	print_reverse(list.begin());
	
	return 0;
}
