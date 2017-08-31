/*
Paul Miller
Compile:
	gcc -lstdc++ inheritance_2.cpp -o inheritance_2 
	or 
	g++ inheritance_2.cpp -o inheritance_2
Goals:
	To provide a useful example of a friend function.
	Run this program with FRIEND == false and see the output time.
	Afterwards, run this program with FRIEND == true and compare the results!
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#define FRIEND false       //Set false to true and rerun!
//Common math class seen in graphics libraries
class Vec3f
{
public:
	Vec3f(float x, float y, float z): x(x), y(y), z(z) {}
	//Normal Returns a vector that is in the same direction but scaled down such that each component is between 0-1	
	/*
		what if we had millions of vec3f instances?
		every method exists in memory for each instance. 
	 	So why not only have a single reference to a function shared by all?
		Friend functions behave like static methods in that all class instances
		share the reference to the function.
	*/	
#if FRIEND	 //based on macro definition, some portions of code will node be compiled!

	//function only compiles if friend is true
	friend const Vec3f& normalize(const Vec3f& vec3f);
#else 
	//method only compiles if friend is false
	const Vec3f& normal() 
	{ 
		return *(new Vec3f(1.0/x, 1.0/y, 1.0/z)); 
	} 
#endif
	//Friend function to output
	friend std::ostream& operator<<(std::ostream& out, const Vec3f& vec)
	{
		return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
	}

private:

	float x, y, z ;
};
#if FRIEND
const Vec3f& normalize(const Vec3f& vec)
{
	return *(new Vec3f(1.0/vec.x, 1.0/vec.y, 1.0/vec.z));
}
#endif

main()
{
	
	clock_t now;
	srand(time(0));
	const int n = 100000;
	//try with an array of objects instead of pointers, why does it not work?
	// Vec3f vecs[n]; //Hint: the compiler message may give you the answer
	Vec3f *vecs[n]; 
	
	now = clock();
	//init array
	for(int i =0; i < n; i++)
		vecs[i] = new Vec3f((float)rand()/rand(), (float)rand()/rand(), (float)rand()/rand());	
	
	//Run just to burn CPU time!
	for(int i =0; i < n; i++)
#if FRIEND
		normalize(*vecs[i]);
#else
		vecs[i]->normal();
#endif
	
	//clean up
	for(int i =0; i < n; i++)
		delete vecs[i];

	std::cout << "\nTIME: " << (float)(clock() - now)/CLOCKS_PER_SEC;   
	return 0;

}
