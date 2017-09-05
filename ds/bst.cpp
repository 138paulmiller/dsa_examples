/*
Paul Miller

Compile:
	gcc -lstdc++ bst.cpp -o bst 
	or 
	g++ bst.cpp -o bst

Goal:
	Understand pointer based implementation of a Binary Search Tree
*/


#include <iostream>
#include <ctime>
#include <cstdlib>
template <typename T>
class Bst;
//------------------------------BNode--------------------------------------
template <typename T>
class BNode
{
public:
	BNode(T value) : value(value), p_left(0), p_right(0){}
	~BNode() {if(p_left) delete p_left; if(p_right) delete p_right;} //chain delete!
	template <typename U>
	friend class Bst;
private:
	BNode* p_left, *p_right;
	T value;
	
};

//------------------------------Bst--------------------------------------
template <typename T>
class Bst
{
private:
	BNode<T>*p_root;

public:
	Bst():p_root(0){}
	~Bst(){if(p_root) delete p_root;}
	bool insert(T value);
	bool remove(T value);
	
	void inorder() 	{ std::cout << "\nInOrder:";inorder(p_root);}
	//void postorder(){ postorder(p_root);}
	//void preorder()	{ preorder(p_root);}
	
protected:
	//------Recursion helper methods-----
	void inorder(BNode<T>* root);
	BNode<T>* insert(BNode<T>* root, T value, bool&success);
 	BNode<T>*  remove(BNode<T>* root, T value,  bool&success);	


};

template<typename T>
bool Bst<T>::insert(T value)	
{
	bool success ; 
	 p_root = insert(p_root, value, success);
	return success;	
}
template<typename T>
bool Bst<T>::remove(T value)
{
	bool success; 
	p_root = remove(p_root, value, success);	
	return success;
} 

template<typename T>
void Bst<T>::inorder(BNode<T>* root)
{
	if(root)
	{
		inorder(root->p_left);
		std::cout << root->value << ' ';
		inorder(root->p_right);
	}
}

//Returns pointer to new left
template<typename T>
BNode<T>* Bst<T>::insert(BNode<T>* root, T value, bool &success)
{
	if(root)
	{
		if(value < root->value)
			root->p_left = insert(root->p_left, value, success);
		else if(value > root->value)
			root->p_right = insert(root->p_right, value, success);
		else
			success = false;//do not insert duplicates!
	}
	else
	{
		success = true;
		root = new BNode<T>(value);
	}
	return root;
}

 

template <typename T>
BNode<T>* Bst<T>::remove(BNode<T>* root, T value, bool &success)
{

	if(root)
	{
		//Remove returns new left of right pointer
		if(value < root->value)
			root->p_left = remove(root->p_left, value, success);
		else if(value > root->value)
			root->p_right = remove(root->p_right, value, success);
		else
		{	
		//found
			success = true;
			//If 2 children switch root with  right-leftmost leaf
			if(root->p_right && root->p_left)
			{
				BNode<T>* cur = root->p_right; //go right
				BNode<T>* left_most=root, *parent=0;
				while(cur) //while not child
				{
					parent = left_most;
					left_most = cur;
					cur = cur->p_left;
				} //move left most
				//swap values
				T temp = left_most->value;
				left_most->value = root->value;
				root->value = temp; 
				//Knowing left_most has no left child, if left_most has a right pointer
				//reassign the parents right to left_mosts right
				parent->p_right == left_most? parent->p_right = left_most->p_right: parent->p_left=0; 						
				left_most->p_right = 0; //disconnect
				delete left_most;
				
			}
			else //if a leaf or single child
			{
				//If one child, cut root and return the child, which replaces the root 
				BNode<T>* child = (root->p_right? root->p_right: root->p_left); //assign to none null child
				//cut root	
				root->p_left = 0;
				root->p_right = 0;		
				delete root;
				//assign the new root be the child
				root = child; 
			}			
		}
	}
	else	//not found
		success = false;
	return root;
}


main()
{
	srand(time(0));
	Bst<int> tree;
	//Why is it useful to test this daata using random insertion and removal?
	
	for(int x = 0; x < 5; x++)
	{
		for(int i =0; i < 10; i++)
		{
			tree.insert(rand()%10);
		}
		tree.inorder();
		for(int i =0; i < 20; i++)
		{
			int x = rand()%10;
			if(tree.remove(x)) tree.inorder();
		}
	}
	return 0;
}
