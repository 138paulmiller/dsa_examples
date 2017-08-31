/*
Paul Miller 

Compile:
	gcc -lstdc++ pointer_3.cpp -o pointer_3 
	or 
	g++ pointer_3.cpp -o pointer_3

Goal:
	Emphasis how data is stored and why pointers are dangerous!
*/
#include <iostream>

struct Foo
{
	int a, b, c;
};
struct Bar
{	
	int x, y;
};

//Not given g++ the return type since main was already implicitly forward declared :)
main()
{
/*
	Initialize structs using aggregate initialization
		- Aggreagate initialization works for both structs and arrays?
	Both structs and arrays provide contiguous memory. Meaning the next
		address of the next element is exactly one element over in memory.
	Example:
		Memory looks the same  for both A and B.
		struct T {int a, b, c};
		int A[3] = {1, 2, 3};
		T B = {1, 2, 3};
	    0x00 | 1 | 
	   	 |---| 
	    0x04 | 2 | 
	  	 |---| 
	    0x08 | 3 | 
*/ 
	Foo f = {1, 2, 3};
	Bar b = {4, 5}; 
	
	std::cout << "\nInitial";
	std::cout << "\nf = {" << f.a << ' ' << f.b << ' ' << f.c <<'}';
	std::cout << "\nb = {" << b.x << ' ' << b.y  << '}';
	Foo * p_fb; //foo pointer pointing to bar, f to b
	Bar * p_bf;	//bar pointer pointing to bar, b to f

	p_bf = (Bar*)&f;
	std::cout 	<< "\n\np_b = (Bar*)&f\n"
				<< "\tp_bf: "<< p_bf->x << ' ' << p_bf->y;


	p_fb = (Foo *)&b;
	std::cout 	<< "\n\np_fb = (Foo *)&b\n"
				<< "\tp_fb: "<< p_fb->a << ' ' << p_fb->b << ' ' << p_fb->c << '\n';

	//Although p_fb is pointing to b, it is changing value of f!!!!
	p_fb->c = -9;	//same as ((Foo *)&b)->c  = -9;
	std::cout << "\np_f->c = -9";
	std::cout << "\nf = {" << f.a << ' ' << f.b << ' ' << f.c <<'}';
	std::cout << "\nb = {" << b.x << ' ' << b.y  << '}';


/*
	In Memory, variables are push onto a stack. 
	Note: integers members are 4 bytes.  
	
	x: 0x00	|----| <- b 
		| 4  | 	
	y: 0x04	|----|
		| 5  | 
	a: 0x08	|----| <- f 
		| 1  | 	
	b: 0x0C	|----|
		| 2  | 
	c: 0x10	|----|
	    	| 3  |
	
	If you have a Foo pointer to b, accessing its c member 
	will access memory beyond the b structure!
		
	How struct member accessors actually work can explain this further in detail. 
		
	struct Foo 
	{
		int a, b, c; //these are labels of the memory offsets!
	};
	Foo f = { 1, 2, 3 }; 

	a: 0x00	|----| <- f 
		| 1  | 	
	b: 0x04	|----|
		| 2  | 
	c: 0x08	|----|
	    	| 3  | 

	Note: Address of f.a == address of f.
	So pointing to the address of f, if derefenced as an int the value is f.a.
	Accessing b is really just accessing the base address of f, 
	plus the size of an integer.	
	Knowing, this we can do stuff like below.
*/	
	std::cout << "\nPointer access to struct members";
	int* p_f = (int*)&f; //point to struct as its member type, int
	std::cout << "\nf = {" << *p_f << ' ' << *(p_f+1) << ' ' << *(p_f+2) <<'}';
	
	int* p_b = (int*)&b; //point to struct as its member type, int
	std::cout << "\nb = {" << *p_b << ' ' << *(p_b+1)  << '}';
	std::cout << "\nGoodbye\n";
	return 0;
}

