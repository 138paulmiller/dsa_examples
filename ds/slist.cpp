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
		inline bool is_empty() {return p_front == 0;} 
		//Basic List Functions for inserting and removing data	
		void insert_at(T value, int pos);	
		void push_front(T value);
		T pop_front();
		void push_back(T value);
		T pop_back();
		void swap(T a_val, T b_val);

		//Accessors to iterators
		inline SIterator<T> begin() const;
		inline SIterator<T> end() const;

	protected:
		SNode<T>* find_prev_ptr(T value);
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
SNode<T>* SList<T>::find_prev_ptr(T value)
{
	SNode<T>* temp = p_front;
	if(temp)
	{
		if(temp->value == value)
			return 0; //head
		while(temp->p_next && temp->p_next->value != value)
			temp = temp->p_next;
		//if(temp || temp->data != value)
		//	temp = 0;
	}
	return temp;
}


template <typename T>
void SList<T>::swap(T a_val, T b_val)
{
	if(is_empty()) return;
	//Pointers and cases are explicitly labled, to visualize draw it out step by step!
	SNode<T> *a_prev = find_prev_ptr(a_val),
			*b_prev = find_prev_ptr(b_val);
	SNode<T> * a, *b, *temp;
	
	if(!a_prev && a_val == p_front->value)
		a = p_front;
	else if(a_prev)
		a = a_prev->p_next;
	else
	{
		std::cout << "\nswap: A not found!";
		return ; //no a!
	}

	if(!b_prev && b_val == p_front->value)
		b = p_front;
	else if(b_prev)
		b = b_prev->p_next;
	else
	{
		std::cout << "\nswap: B not found!";
		return ; //no b!
	}
	if(b_prev)
		b_prev->p_next = a;
	if(a_prev)
		a_prev->p_next = b;

	temp = a->p_next;
	a->p_next= b->p_next;
	b->p_next = temp;
	
	//update front 
	if(a == p_front)
		p_front = b;
	else if(b == p_front)
		 p_front = a;
	if(a == p_back) 
	 	p_back = b;
	else if(b == p_back)
	 	p_back = a;
	
}

template <typename T>
void SList<T>::insert_at(T value, int pos)
{
	if (pos == 0)
	{
		push_front(value);
	}
	else if(pos == length)
	{
		push_back(value);
	}
	else if(pos < length)
	{
		
		SNode<T> * temp = p_front;
		SNode<T> *new_node = new SNode<T>(value);
		for(int i=0; i < pos-1;i++)
			temp = temp->p_next;
		new_node->p_next = temp->p_next;
		temp->p_next = new_node;
		length++;
	}

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
		length --;
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
		length --;
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
	list.insert_at(1, 0);
	list.insert_at(2, 1);
	list.insert_at(3, 1);
	list.insert_at(4, 3);
	list.insert_at(0, 0);
	list.insert_at(9, 5);
	
	print(list);
	std::cout << "\n0 <--> 4";
	list.swap(0, 4);
	print(list);
	std::cin.get();
	std::cout << "\n3 <--> 9";
	list.swap(3, 9);
	print(list);
	std::cout << "\n3 <--> 4";
	list.swap(3, 4);
	std::cin.get();

	// for(int i = 0; i < 5; i++)
	// {
	// 	list.push_back(i);
	// 	list.push_front(i+15);
	// 	list.push_front(i+30);

	// }
	// for(int i = 0; i < 3; i++)
	// {
	// 	list.pop_front();
	// 	list.pop_back();
	// }
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

