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
	A(int a) : x(a){}
	struct B
	{
		B(int b) : y(b) {} 
		int y; 	
	}x;	
};

class D
{
	protected:
		int w; 	

	public:
		D(int b) : w(b) {} 
};

class C : public D
{
	public:
		C(int a): D(a){}
		int get() { return w; } //C can see inherited w. What if w was private?
};


main()
{
	//Why do these objects need to be called with arguments?
	//Overloading contructor, replaces default constructor!
	A a(10);
	//B b(20); //why does this not compile??
	C c(30);
	D d(40);
	 
	std::cout << "\nA    " << a.x.y; 
	//How does this work? 
	A::B b = a.x;
	std::cout << "\nA::B " << b.y; 
	std::cout << "\nC    " << c.get();
	//std::cout << "\nD: " << d.w; //why does this not compile??


//How do classes and structs differ? Would anything change if class type was changed to struct?
//Here is an example that demonstrates the only difference between the two!
// try to guess if this code will compile. If so, what will be the output?
	class F
	{
		int p;	
	}f;
	struct G
	{
		int q;
	}g;
/*
	std::cout << "\nClass : " << f.p; 
	std::cout << "\nStruct: " << g.q; 
*/	
	//Structs can contain private, protected, public members that are both functions or data types!
	std::cout << "\nGoodbye\n";

	return 0;
}
