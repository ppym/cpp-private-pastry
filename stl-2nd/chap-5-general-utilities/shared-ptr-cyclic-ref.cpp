#include <iostream>
#include <memory>
using namespace std;

//*********************** cyclic reference *************
class B;

class A {
public:
	A() : spB(nullptr) {}
	A(std::shared_ptr<B> spb) : spB(spb) {
	}
	~A() {
		cout << "~A() " << endl;
	}
	void setspB(std::shared_ptr<B> spb) { spB = spb; }

private:
	std::shared_ptr<B> spB;
};

class B {
public:
	B() : spA(nullptr) {}
	B(std::shared_ptr<A> spa) : spA(spa) {
	}
	~B() {
		cout << "~B() " << endl;
	}
	void setspA(std::shared_ptr<A> spa) { spA = spa; }

private:
	std::shared_ptr<A> spA;
};

int main()
{
	
	{
		std::shared_ptr<A> pa(new A());
		std::shared_ptr<B> pb(new B());
		//按照对象的声明顺序析构即是说输出如下：
		//~B()
		//~A()
	}

	{
		std::shared_ptr<A> pa(new A());
		std::shared_ptr<B> pb(new B());

		pa->setspB(pb); 
		//只有A对象引用到了B对象的shared_ptr，
		//按照声明顺序释放B对象，发现B对象被A对象持有，所以use_count-1,但还释放不了B对象，因为此时还被pa所指向的A对象成员变量持有（use_count为1）
		//按照声明顺序释放A对象，析够A对象会释放了A对象成员变量的shared_ptr<B>,导致B对象use_count为0,可以释放B对象了
		//输出
		// ~A()
		// ~B()
	}

	{
		std::shared_ptr<A> pa(new A());
		std::shared_ptr<B> pb(new B());

		pb->setspA(pa); 
		//B对象引用到了A对象的shared_ptr，按照声明顺序释放B对象，也释放了B对象成员变量的shared_ptr<A>,然后pa的use_count为0,正常释放
		//输出
		// ~B()
		// ~A()
	}
	
	{
		std::shared_ptr<A> pa(new A());
		std::shared_ptr<B> pb(new B());

		pa->setspB(pb);
		pb->setspA(pa); 
		//循环引用，彼此都释放不了
	}
}

