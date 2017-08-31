/*
Paul Miller
Compile:
	gcc -lstdc++ inheritance_2.cpp -o inheritance_2 
	or 
	g++ inheritance_2.cpp -o inheritance_2
Goals:
	Understand class scopes in c++ as well as initialization lists.
*/
#include <iostream>


class A
{
public:
	friend int foo(int x);
	//Static function require access to static class variables but
	// static variables can be accessed from all classes!
	int get() {return x;} 
private:
//Only one instance of x will be shared for all instances of A!
	static int x; 
}; 

//Dummy class to show the size of a class object without firend function
class B
{
	int get() {return x;} 
	static int x;
};

int A::x; 	//declare an instance of x for foo to use! Only needed for 
			//friend function to have access to static the variable
int foo(int x)
{
	//What would happen if you just did x*=x? 
	//Note that local scope takes precedence!!
	return A::x=x;  //can only access A::x if x is static!
}

main()
{
	A a;
	B b;
	//what does this comparison say about the contents of the two objects?
	//Does this provide an explanation of where friend functions are defined?
	std::cout <<"\n" << sizeof(a) << "==" << sizeof(b); 
	
	std::cout << "\n" << foo(2);
	A new_a;
	std::cout << "\n" << new_a.get();
	std::cout << "\nGoodbye\n";

}
