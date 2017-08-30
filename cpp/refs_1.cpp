/*
Paul Miller 

Compile:
	gcc -lstdc++ refs_1.cpp -o refs_1 
	or
	g++ refs_1.cpp -o refs_1

Goal:
	Try and predict the output!
*/
#include <iostream>
#define print std::cout << 
int g;

int& ref()
{
	return g;
}

int* ptr()
{
	return &g;
}
//why is this a bad idea? Check compilation log, it may give you the answer!
int& loc_ref()
{
	int i = 8;
	return i; 
}
main()
{
	int t  = ref();
	int* v = ptr();
	g = loc_ref();
	print "\n1: ";
	print g;

	t = 4;
	print "\n2: ";
	print g;

	ref() = 4;	
	print "\n3: ";
	print g;
	
	print "\n4: ";
	print *v;


	//Does any of this surprise you?
	print "\n&g: ";
	print &g;
	print "\n&t: ";
	print &t;	
	print "\nv : ";
	print v;	
	print "\nGoodbye\n";
	return 0;
}

