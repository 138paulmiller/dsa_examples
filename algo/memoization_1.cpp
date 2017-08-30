/*
Paul Miller github.com/138paulmiller

Compile:
	gcc -lstdc++ -std=c++11 memoization_1.cpp -o memoization_1 
	or 
	g++ -std=c++11 memoization_1.cpp -o memoization_1
Goals:
	Examples of memoized recursion solutions to problems. 
	Makes use of static types.


*/
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
	Naive (simplified) solution to outputing the nth fibonacci number. 
		
	this solution is very slow since you are making 2 recursive calls,
	this means every call expands to 2 calls, and each of those two expand to 
	2 more calls. 
	
	The series of calls as n increases:
		n = 1, 2, 3, 4, 5, 6,  ... n
			0, 0, 2, 4, 8, 16, ... 2^(n-2)
	Lookup the graph of 2^n, and you will understand why this is such a slow algorithm.
		
*/
long fib_naive(int n) 
{
	if(n==1 || n==2) //will n ever be < 0 ? 
		return 1;
	else
		return fib_naive(n-1) + fib_naive(n-2);
} 

/*
	Memoized solution fibonacci.
		fib(5) = (fib(4)) 			+ (fib(3))
				 = (fib(3) + fib(2))+ (fib(2) + fib(1)) 
		When calling fib(4) you are finding fib(3) and fib(2). 
		But after done solving fib(4), you solve fib(3) again!
		Why not save that value of a previous solution in a lookup table?
		Let's do this using a static array 
		where the nth index is the nth solution to fib(n).
		Static keyword allows the function call to initialize the variable, 
		then all preceding function calls have access to the variable.  
	Think of Memoization as an optimization technique; used to speed up algorithm. 
	For this solution we are caching (saving) previous solutions we have seen before.
	This allows us to calculate fib(n) in O(n) time! 
Question:
	Why must this be called with the largest n first?
*/

long fib_mem(int n)
{
	static long* table = new long[n]{0}; //init all elements to 0 (c++11!)	
	if(table[n] == 0) //if never found 
		if(n==1 || n==2) //will n ever be < 0 ? 
			table[n] = 1;
		else
			table[n] = (fib_mem(n-1) + fib_mem(n-2)); //set table
	return table[n]; //return previously solved value
}

//Makes use of function pointer!
// return_type(*ptr_name)(func_arg_types, ...)
float get_duration(long(*fib_func)(int), int n)
{
	clock_t start;
	int i=n+1;
	start = clock();	
	while(--i > 0)
		std::cout << "\nfib(" << i << ")\t= " << fib_func(i);
	
	return (float)(clock() - start)/(CLOCKS_PER_SEC);

}

//Not given g++ the return type since main was already implicitly forward declared :)
main()
{

	int n = 40; //number of fib numbers to solve

	std::cout<<	"\nNaive 	Duration: " << 	get_duration(fib_naive, n);
	std::cout<<	"\nMemoized Duration: " << 	get_duration(fib_mem, n);
	std::cout << "\nGoodbye\n";
	return 0;
}
