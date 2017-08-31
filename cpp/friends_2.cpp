/*
Paul Miller
Compile:
	gcc -lstdc++ inheritance_2.cpp -o inheritance_2 
	or 
	g++ inheritance_2.cpp -o inheritance_2
Goals:
	To provide a useful example of a friend function.
	Also provides a way to compile the class dependent of macro value.
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#define FRIEND false       //Set false to true and rerun!
//Common math class seen in graphics libraries
class Vec3f
{
public:
	Vec3f(float x, float y, float z): x(x), y(y), z(z) {}
	//Normal Returns a vector that is in the same direction but scaled down such that each component is between 0-1	
	/*
		Friend functions behave like static methods in that all class instances
		share the reference to the function.
	*/	
#if FRIEND	 //based on macro definition, some portions of code will node be compiled!

	//function only compiles if friend is true
	friend const Vec3f& normalize(const Vec3f& vec);
	friend float length(const Vec3f& vec);

#else 
	float length()
	{
	 	return sqrt(x*x+y*y+z*z);
	}
	//method only compiles if friend is false
	const Vec3f& normal() 
	{ 
		float len = length();
		return *(new Vec3f(x/len, y/len, z/len));
	} 
#endif


	float x, y, z ;
};
#if FRIEND
float length(const Vec3f& vec)
{
	return sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}
const Vec3f& normalize(const Vec3f& vec)
{
 	float len = length(vec);
	return *(new Vec3f(vec.x/len, vec.y/len, vec.z/len));
}

#endif

main()
{

	const int n = 10000;
	//try with an array of objects instead of pointers, why does it not work?
	// Vec3f vecs[n]; //Hint: the compiler message may give you the answer
	Vec3f *vecs[n]; 
	
	//init array
	for(int i =0; i < n; i++)
		vecs[i] = new Vec3f((float)rand()/rand(), (float)rand()/rand(), (float)rand()/rand());	
	//Run just to burn CPU time!	
#if FRIEND
	std::cout << "FRIEND";
	for(int i =0; i < n; i++)
		normalize(*vecs[i]);
#else	
	std::cout << "METHOD";
	for(int i =0; i < n; i++)
		vecs[i]->normal();
#endif
	  
	//clean up
	for(int i =0; i < n; i++)
		delete vecs[i];


	return 0;

}
