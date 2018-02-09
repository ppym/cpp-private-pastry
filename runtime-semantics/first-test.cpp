#include "common.h"
using namespace std;

class Y {
public:
	Y() {cout << "Y::Y()\n";}
	~Y() {cout << "Y::~Y()\n";}

	bool operator==(const Y& rhs) { cout << "Y::operator==()\n";
					return true;}	
};

class X {
public:
	X() {cout << "X::X()\n";}
	~X() {cout << "X::~X()\n";}

	operator Y() const { Y yy; return yy;}
	X getValue() {
		X temp;
		return temp;
	}
};

int main(int argc, char *argv[])
{
	X xx;
	Y yy;
	if (yy == xx.getValue()) 
		cout << "yy == xx.getValue()\n";
	{
		cout << "switch test\n";
		X xxx;
		int i=0;
		switch (i)
		{
			case 1:
			break;
			case 2:
			break;
			//default :
			//break;
		}
		cout << "exit switch\n";
	}

	return 0;
}
