/*
Paul Miller 
Compile:
	gcc -lstdc++ inheritance_1.cpp -o inheritance_1 
	or 
	g++ inheritance_1.cpp -o inheritance_1
Goals:
	Understand class inheritance scopes.
*/
#include <iostream>

#define print(x) std::cout << x << '\n';
class C
{
	public:
		int x;
	protected:
		int y;
};

class B : public C
{
	public:
		B(int x) { this->x=x; }
		int getY() {return y;}

};

class A : public B
{
	public:
		A(int x, int y) : B(x) { this->y=y; }
		int getX() { return x; }	
};

main()
{
	A a(1,2);
	//Predict the output before compiling each line!
	//print(a.getX());
	//print(a.getY());
	//print(a.x);
	//print(a.y);
}
