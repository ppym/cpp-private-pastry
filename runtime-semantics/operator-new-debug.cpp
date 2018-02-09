#include "common.h"
#include <stdlib.h>
using namespace std;

void *operator new(size_t size, const char *file, int line)
{
	cout << file << " " << line <<  " new size: " << size << endl;
	return ::operator new(size);
}

void operator delete(void * p, const char *file, int line)  
{  
	cout << file << " " << line << "delete " << (long*)p << endl;  
	::operator delete(p);
}  

class X {
};

#define new new(__FILE__,__LINE__)
//#define delete delete(__FILE__,__LINE__)

int main()
{
	X* px1 = new X();
	//within the new operator above(that is c++-built-in), compiler will do 3 steps
	//1.calculate the size of X.call the operator new function.(not new operator).in this example , that is void*X operator new(size_t)
	//2.call the X constructor to initilaize the X object, that is "X::X()"
	//3.return the pointer

	//within the delete operator below(that is c++-built-in), compiler will do 2 steps
	//1.call the X destructor 
	//2.call the operator delete
	delete px1;

	int *pi = new int(7);
	delete pi;
}
