/*
Paul Miller 
Compile:
	gcc -lstdc++ class_refs_1.cpp -o class_refs_1
	or
	g++ class_refs_1.cpp -o class_refs_1
Goals:
	To understand the construction order of class instances.
*/
#include <iostream>


struct B
{
	B(int x):x(x){}
	B(const B& b): x(b.x) {std::cout << "\nB Copied!";}
	void print() {std::cout << x;}
	int x;	
};


class A
{
public:
	A(const B& b) : b(b) {}

	B& getRef() {return b;} 	
	const B& getConstRef() {return b;}   
	const B get() {return b;} 			  
	void print() { b.print(); }
	/*
		What does const mean when used after function header?
		The following will not compile! Const qualifier here is used 
		to declare the method as a const type, meaning this function
		is not allowed to modify member values!
	*/ 
	//void set(int z, int w) const {x=z; y=w;} 

	B b;
};


main()
{
	B b(1);
 	A a(b);  

	//This returns a reference but b_copy is then constructed with that reference.
	B b_copy = a.getRef();			
	
	B *b_ptr;
	B b_ref(0);
	B b_cref(0);
	
	b_ptr = &a.getRef();	
	b_ref = a.getRef();  	
	b_cref = a.getConstRef();  


	b.x = 3;
	b_ptr->x = 4;	
	b_ref.x = 7;
	a.getRef().x = 5;
	b_cref.x = 10;
	
	//What will this print?
	std::cout << "\na     :";  a.print();
	std::cout << "\nb     :";  b.print();
	std::cout << "\nb_ptr :";  b_ptr->print();
	std::cout << "\nb_ref :";  b_ref.print();
	std::cout << "\nb_cref:";  b_cref.print();

	//This might help explain why references do not always work like pointers
	std::cout << "\n&a     :" << &a;
	std::cout << "\n&a.b   :" << &(a.b);
	std::cout << "\n&b     :" << &b;
	std::cout << "\n&b_ptr :" << b_ptr;
	std::cout << "\n&b_ref :" << &b_ref;
	std::cout << "\n&b_cref:" << &b_cref;	
	std::cout << "\nGoodbye\n";	
	return 0;	

}
