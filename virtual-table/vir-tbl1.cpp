#include <iostream>
#include <stdio.h>

using namespace std;

class B {
public:
	long ib;
	B():ib(0x0101010101010101){}
	virtual ~B(){}
};

class B1 : public virtual B {
public:
	long ib1;
	B1():ib1(0x1111111111111111){}
	virtual void fb1(){}
};

#if 1 class B2 : public virtual B {
public:
	long ib2;
	B2():ib2(0x2222222222222222){}
};

class D: public B1, public B2 {
public:
	long id;
	D():id(0x3333333333333333){}
};
#endif

int main()
{
	B1 b1;
	D d;

	printf("sizeof(B)=%ld\n",sizeof(B));
	printf("sizeof(B1)=%ld\n",sizeof(B1));
	printf("sizeof(B2)=%ld\n",sizeof(B2));
	printf("sizeof(D)=%ld\n",sizeof(D));
	//b1.ib = 0x02020202;
}
