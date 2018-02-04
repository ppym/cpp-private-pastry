#include <iostream>
#include <stdio.h>

using namespace std;

class B1 {
public:
	B1(){}
	virtual ~B1(){}
	virtual void speakClearly(){};
	virtual B1 *clone() const {};
protected:
	float data_B1;
};

class B2 {
public:
	B2(){}
	virtual ~B2(){}
	virtual void mumble(){};
	virtual B2 *clone() const {};
protected:
	float data_B2;
};

class D: public B1, public B2 {
public:
	D(){}
	virtual ~D(){}
	virtual D*clone() const {}
protected:
	float data_d;
};

int main()
{
	D d;
}
