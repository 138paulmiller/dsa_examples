/*
Paul Miller

Compile:
	gcc -lstdc++ templates_1.cpp -o templates_1 
	or 
	g++ templates_1.cpp -o templates_1
Goals:
	Understand templated types and an overloaded operators.
*/
#include <iostream>
template <typename A, typename B>
class Foo
{
public:
	Foo(A a, B b) : a(a), b(b) {}
	friend std::ostream& operator<<(std::ostream& out, const Foo<A, B>&foo)
	{
		//why can this function access private members of Foo? 
		// Hint: Check its qualifier.
		out << "A:(" << foo.a << "), B:(" << foo.b << ')'; 
		return out;
	}
private:
	A a;
	B b;

};

main()
{
	Foo<int, float>fooA(10, 11);
	std::cout << '\n' <<fooA;


	//Can you create an instance of Foo of type foo and int?
	//Will this compile? If so, what will be the output?
/*
	Foo<Foo<int, float>, int> fooB(fooA, 12);
	std::cout << '\n' <<fooB;
*/
	std::cout << "\nGoodbye\n";
	return 0;
}
