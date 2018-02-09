#include "common.h"
using namespace std;

class X {
public:
	X() {cout << "X::X()\n";}
	virtual ~X() { cout << "X::~X()\n"; }
	void * operator new(size_t size);
private:
	int mi;
};

void *X::operator new(size_t size)
{
	cout << "X::operator new(size_t):" << size << endl;
	return ::operator new(size); //call origin operator new
}

int main()
{
	X* px = new X();
	//within the new operator above(that is c++-built-in), compiler will do 3 steps
	//1.calculate the size of X.call the operator new function.(not new operator)
	//2.call the X constructor to initilaize the X object
	//3.return the pointer
}
