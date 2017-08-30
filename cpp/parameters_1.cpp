/*
Paul Miller github.com/138paulmiller

Compile:
	gcc -lstdc++ parameters_1.cpp -o parameters_1 
	or
	g++ parameters_1.cpp -o parameters_1
Goals:
	Some examples of varying parameter types.
*/
#include <iostream>

int func(size_t n)
{
	n++;
	return n;
}
int func_const(const size_t n)
{
	//n++; const makes variables READ-only!
	return n;
}
int func_ref(size_t& n)
{
	n++;
	return n;
}

int func_const_ref(const size_t& n)
{
	//n++; const makes variables READ-only! even if a reference
	return n;
}

main()
{
	const int n = 9;
	std::cout << "\nLiteral:" << func(5);
	std::cout << "\nConst n:" << func(n);
	
	int m = 3;
	std::cout << "\nLiteral:" << func_const(5);
	std::cout << "\nVar n:  " << func_const(m);
	

	//Why do these not work?
	//Can you have a reference to a literal or constant value?
	// Literal  - does not reside in memory!
	// Constant - should not be modifiable!

//	std::cout << "\nLiteral:" << func_ref(5);
//	std::cout << "\nVar n:  " << func_ref(n);


	//Allowed, since for constant reference the copy constructor is not called! It just prolongs lifetime of data
	std::cout << "\nLiteral:" << func_const_ref(5);
	std::cout << "\nVar n:  " << func_const_ref(m);
	
	return 0;
}
