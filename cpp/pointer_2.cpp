/*
Paul Miller 

Compile:
	gcc -lstdc++ pointer_2.cpp -o pointer_2 
	or 
	g++ pointer_2.cpp -o templates_2

Goals:
	Understand why some of the following code is allowed.
	Modify to allow user input to populate both arrays.

*/
#include <iostream>
#include <climits> //UINT_MAX
#define for(x) for(int i=0; i < x; i++)
#define print std::cout << ' ' <<  


main()
{
	int n = 10;
	int* arr = new int[n];

	for(n)
		arr[i] = (i+1)*2; //where is i coming from?

	//print *arr; //what does this print?
	for(n)
		print arr[i];  			
	print '\n';	

	//An array is just a pointer to a contiguous memory block. 
	// Each element is accessed by the offset from the pointer which is the base address.
	for(n)
		print *(arr + i);  	//arr[i] = *(arr + i)
	print '\n';	

/*  Will this work?
	for(n)
		
		print i[arr] ;		//*(arr + i) == *(i + arr), right?
*/
	delete[] arr; 
	//Why is the data still here?
	for(n)
		print arr[i];
	 //Calling delete does not literally delete!
	// Rather tells OS that the block is no longer being used and can be reaccessed. 
	return 0;
}
