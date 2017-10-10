//Paul Miller
#include <stdio.h>
class Foo
{
public:
	int x;
	//char y,z share an int sized chunk,
	char y; 
	char z;
	float w, h;
};
// Note: int is 4bytes in
//although its a char in memory
// the int sized chunk it is in it is only using 1-byte. 
//The next full chunk for an int is the next int sized chunk 
//a char here can fit in the 3-byte and can be address by the next char.

main()
{
	Foo f = (Foo){1, 'a', '#', 3.4, 5.6};
	//modify fields
	char* base = (char*)&f; //base addr of class
	printf("Diff from base to w: %x - %x =? %d", &f.w, base, (char*)(&f.w)-base);
	printf("\nx:%d\ny:%c\nz:%c\nw:%f\nh:%f\n",
		//point as a char to only have pointer+1 move one byte!
		*(int*)base, //x is start addr
		*(char*)(base+sizeof(int)), //y is one int away 
		*(char*)(base+sizeof(int)+sizeof(char)), //z is still in the second int chunk
		*(float*)(base+sizeof(int)+sizeof(int)), //w is the third chunk from base since y,z share chunk
		*(float*)(base+sizeof(float)+sizeof(float)+sizeof(int))); //sizeof float == sizeof int, but the 4th chunk over
}