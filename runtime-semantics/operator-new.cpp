#include "common.h"
#include <stdlib.h>
using namespace std;

class X {
public:
	X() {cout << "X::X()\n";}
	virtual ~X() { cout << "X::~X()\n"; }
	int getMi() {return mi;}
	void * operator new(size_t size);
	void * operator new(size_t size, const std::string &str);
	void * operator new(size_t size, void *buf);
	void operator delete(void *);
private:
	int mi;
};

void *X::operator new(size_t size)
{
	cout << "X::operator new(size_t): " << size << endl;
	return ::operator new(size); //call origin operator new
}

void *X::operator new(size_t size, const std::string &str)
{
	cout << "X::operator new(size_t, const std::string&): " << size << " " << str << endl;
	return ::operator new(size); //call origin operator new
}

void *X::operator new(size_t size, void *buf)
{
	cout << "X::operator new(size_t, void*): " << size << " " << buf << endl;
	if (buf)
		return buf;
	return ::operator new(size); //call origin operator new
}

void X::operator delete(void *p)
{
	cout << "X::operator delete(void *): " << (long*)p << endl;
	::operator delete(p);
}

#if 0
//this overload function will cause infinite recursive
void *operator new(size_t size)
{
	cout << "operator new(size_t): " << size << endl;
	return ::operator new(size);
}
#endif

void *operator new(size_t size)
{
	cout << "operator new(size_t): " << size << endl;
	return malloc(size); //call origin operator new
}

int main()
{
	X* px1 = new X();
	//within the new operator above(that is c++-built-in), compiler will do 3 steps
	//1.calculate the size of X.call the operator new function.(not new operator).in this example , that is void*X operator new(size_t)
	//2.call the X constructor to initilaize the X object, that is "X::X()"
	//3.return the pointer
	px1->getMi();

	X* px2 = new ("Yes,I can") X();
	//within the new operator above(that is c++-built-in), compiler will do 3 steps
	//1.calculate the size of X.call the operator new function.in this example , that is void*X operator new(size_t, const std::string&)
	//2.call the X constructor to initilaize the X object, that is "X::X()"
	//3.return the pointer
	px2->getMi();

	char buf[sizeof(X)];
	X* px3 = new (buf) X();
	cout << "px3 addr=" << px3 << endl;

	//within the delete operator below(that is c++-built-in), compiler will do 2 steps
	//1.call the X destructor 
	//2.call the operator delete
	delete px1;
	delete px2;
	delete px3; //crash since we use stack memory

	int *pi = new int(6);
	delete pi;
}
