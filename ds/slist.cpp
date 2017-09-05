/*
Paul Miller

Compile:
	gcc -lstdc++ list_1.cpp -o list_1 
	or 
	g++ list_1.cpp -o list_1

Goal:
	A very minimal singly linked list implementation. 
TRY:	
 	By iterating over the list once:
		find the middle of the list (HINT: use two pointers!)
		print the nodes in reverse (HINT:recursion!)
*/

//-------------------------------------SNode Declaration-------------------------------

#include <iostream>
//forward declare list class for Snode and Siterator Usage
template <typename T>
class SList; 

//Singly linked Node, element of singly linked list
template <typename T>
class SNode
{
	public:
		SNode(T value) :value(value), p_next(0){}
		~SNode();
		//Allows SIterator and Slist have access to node data
		template <typename U>
		friend class SList; 
		template <typename U>
		friend class SIterator;
	private:
		T value;
		SNode<T>* p_next; //pointer to next node 
};
//-------------------------------------SIterator Declaration-------------------------------
//SList Iterator class to abstract node access, allows for easier usage
template <typename T>
class SIterator
{
	public:
		SIterator(): node(0){}
		SIterator(SNode<T>* node): node(node){}
		SIterator(const SIterator<T>& other): node(other.node){}
		//Two iterators are equivalent if they point to the same node
		friend bool operator==(const SIterator<T>& l,const SIterator<T>& r) {return l.node == r.node; }
		friend bool operator!=(const SIterator<T>& l,const SIterator<T>& r) {return !(l.node == r.node);}				
		//dereferance operator to get access to pointer value		
		T& operator*();
		//move to next node
		SIterator<T> operator++(); //prefix, move node and return this
		SIterator<T> operator++(int ); //postfix, save this, move node, return save
		inline bool empty() {return node == 0;}
	private:
		SNode<T> *node;
};
//-------------------------------------SList Declaration-------------------------------
//Singly-Linked list
template <typename T>
class SList
{
	public: 
		SList(): p_front(0), p_back(0), length(0) {}
		SList(const SList & other);
		~SList();
		//Basic List Functions for inserting and removing data		
		void push_front(T value);
		T pop_front();
		void push_back(T value);
		T pop_back();
		//Accessors to iterators
		inline SIterator<T> begin() const;
		inline SIterator<T> end() const;
	private:
		SNode<T> *p_front, *p_back; //pointer to front and back node
		int length;
};
//----------------------------------SNode Defs-------------------------------------------
template <typename T>
SNode<T>::~SNode()
{
	//delete next before self
	std::cout << "\nDeleting " << value; //debug, to ensure all nodes are deleted
	if(p_next) delete p_next;
}

//----------------------------------SIterator Defs-------------------------------------------
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
//----------------------------------SList Defs-------------------------------------------
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
SIterator<T> SList<T>::begin() const 
{
	return SIterator<T>(p_front);
}

template <typename T>
SIterator<T> SList<T>::end() const 
{
	if(p_back) return SIterator<T>(p_back->p_next);
	return SIterator<T>();
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
//------------------------------------------Misc Utilities-----------------------------
template <typename T>
void print(const SList<T> &list)
{
	std::cout << "\nList:";
	for(SIterator<T> it = list.begin(); it != list.end(); it++)
		std::cout << *it << ' ';
}

//Defined after main to avoid spoiling solution.
template <typename T>
void print_middle(const SList<T> &list);
template <typename T>
void print_reverse(SIterator<T> it);
//-----------------------------------------Main -------------------------------------
main()
{

	SList<int> list;

	for(int i = 0; i < 5; i++)
	{
		list.push_back(i);
		list.push_front(i+15);
		list.push_front(i+30);

	}
	for(int i = 0; i < 3; i++)
	{
		list.pop_front();
		list.pop_back();
	}
	print(list);
	print_middle(list);
	std::cout << "\nList Reverse:";
	print_reverse(list.begin());
	
	return 0;
}


//---------------------------------Solutions---------------------------------------
template <typename T>
void print_middle(const SList<T> &list)
{
	std::cout << "\nList Middle:";
	SIterator<T> mid = list.begin();  //
	/*
		Solution 1:
		The for loop moves the iterator twice before entering body,
		when the body is entered the mid only moves once. 
		So, for every two moves, mid moves once meaning mid moves 
		half as slow! Mid Starts at beginning so start it at the next.
	*/
/*
	for(SIterator<T> it = ++list.begin(); it != list.end(); ++it, ++it)//iterates 
	{
		mid++; 
	}
*/
	/*
		Another way to iterate mid half as often as the iterator.
		How could this be modified to have i start at 0?
	*/
	int i =-1; //why start at -1?
	for(SIterator<T> it = list.begin(); it != list.end(); ++it, i++) //iterates n times!
	{
		//if i is even
		if(i%2==0)
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

