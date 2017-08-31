/*
Paul Miller 

Compile:
	gcc -lstdc++ pointer_1.cpp -o pointer_1 
	or
	g++ pointer_1.cpp -o pointer_1

Goal:
	Try and predict the output of variables.
	When predicting, variable addresses are arbitrary. 
	Example: 
		Assume address of var = 0x0001.
		Then int * p = &var yields p = 0x0001.
	To solidify understanding draw the memory at each step! 
Note:
	Addresses vary on each execution! Why?

*/
#include <iostream>
#include <iomanip>

/*
	Preprocesser directives perform text substitution.
 Example: 
	
Note:
	#define defines a preprocessor directive known as a macro.

	For #define x 3. GCC scans through source code and replaces all instances of x with 3.
	So if source code has x + 5; and x is not defined, then since GCC will generate std::cout << 3 + 5;
	
	Macros can be passed parameters.	
	For #define f(x) test(x); GCC will substitute f(100) with test(100).

	#include <filename> replaces this line with the source code inside filename.h. 
*/

//useful macro! Macros can make coding much easier! 
#define for(x) for(int i=0; i < x; i++)

//Useful, but messy macro. This could be best defined in a function. 
//	This example is shown to show how \ must be added at the end of a 
//		line to continue the macro definition. 
#define print_ptrs(x) \
	std::cout <<  '\n'\
	<< std::right  << std::setw(20) << ' ' \
	<< std::left << x \
	<< "\n&ptr1   =" << std::setw(15) << &ptr1 << "|" 	 \
	<< "  &ptr2   =" << &ptr2 	\
	<< "\nptr1    =" << std::setw(15) << ptr1 << "|" \
	<< "  ptr2    =" << ptr2 	\
	<< "\n*ptr1   =" << std::setw(15) << *ptr1  << "|" \
	<< "  *ptr2   =" << *ptr2 	\
	<< "\npptr1   =" << std::setw(15) << pptr1  << "|" \
	<< "  pptr2   =" << pptr2 	\
	<< "\n*pptr1  =" << std::setw(15) << *pptr1 << "|" \
	<< "  *pptr2  =" << *pptr2 	\
	<< "\n**pptr1 =" << std::setw(15) << **pptr1 << "|" \
	<< "  **pptr2 =" << **pptr2 << "\n";\
	std::cin.get();

//Not given g++ the return type since main was already implicitly forward declared :)
main()
{
	//pointer pointers examples
	int * ptr1 = new int(9);
	int * ptr2 = new int(23);
	int ** pptr1 = &ptr1;
	int ** pptr2 = &ptr2;

	//print current pointer states, wheres the semicolon? (Hint: not a function!)
	print_ptrs("Initial:")
	//change state	
	pptr2 = &ptr1; 	
	print_ptrs("pptr2 = &ptr1:")
	//change state, is this a memory leak?
	*pptr1 = ptr2; 
	print_ptrs("*pptr1 = ptr2")
	//change state		
	**pptr2 = 2;
	print_ptrs("**pptr2 = 2")		

	//delete all memory currently pointed to
	delete *pptr1; //same as delete ptr2
	//delete ptr1; //why does this crash?
	return 0;
}
