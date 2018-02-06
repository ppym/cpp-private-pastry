#include <iostream>
#include <stdio.h>

using namespace std;

//可以用于多线程传递消息实体
class CloneAble {
public:
	virtual ~CloneAble(){}
	virtual CloneAble *clone() = 0;
};

class Base : public CloneAble{
public:
	Base(){}
	virtual ~Base(){}
	Base(const Base& other){cout << "Base copy constructor" << endl;}

	Base* clone() { cout << "Base::clone()\n";
					return new Base(*this); }
	virtual void f() { cout << "Base::f()\n";}
};

class Derived : public Base {
public:
	Derived(){}
	virtual ~Derived(){}

	//显示调用基类的拷贝构造函数，否则将会调用默认构造函数
	Derived(const Derived &other):Base(other) { cout << "Derived copy constructor" << endl;}
	
	Derived *clone() { cout << "Derived::clone() \n";
						return new Derived(*this);}
	virtual void f() { cout << "Derive::f()\n";}
};

void copy_me(Base &b)
{
	cout << "copy_me(Base &)\n";
	Base *bb = b.clone();
}
#if 0
void copy_me(CloneAble *cc)
{
//	CloneAble ccc = cc->clone(); can't not alloc a virtual class
//	Base *bb = dynamic_cast<Base*>(cc->clone()); //父类转子类。转为NULL。
//	printf("%p \n",bb);
	cout << "copy_me(CloneAble *)\n";
	CloneAble *cb = cc->clone();
	cout <<"cb addr="<<(long*)cb << "cc addr=" << (long*)cc<< endl;

	Base *bb = dynamic_cast<Base *>(cb);
	if (bb) {
		cout << "copy_me(CloneAble*) base dynamic_cast successed\n";
		bb->f();
	}
	else
		cout << "copy_me(CloneAble*) base dynamic_cast failed\n";
}
#endif

void copy_me(Base *cc)
{
	cout << "copy_me(Base *)\n";
	Base *cb = cc->clone();
	cout <<"cb addr="<<(long*)cb << "cc addr=" << (long*)cc<< endl;
	cb->f();

#if 0
	Derive *bb = dynamic_cast<Derive*>(cb);
	if (bb) {
		cout << "copy_me(CloneAble*) base dynamic_cast successed\n";
		bb->f();
	}
	else
		cout << "copy_me(CloneAble*) base dynamic_cast failed\n";
#endif
}


Base *cast_test()
{
	return new Derived();
}

Derived *cast_test2()
{
	return dynamic_cast<Derived*>(new Base());
}

int main()
{
	Base b;
//	Base *pb = &b;
//	pb->f();
//	Base *pb1 = new Base();
//	pb1->f();
	Derived d;
	copy_me(&b);
	copy_me(&d);
#if 0
	copy_me(&b);
	cast_test();
	cast_test2();
#endif

}

