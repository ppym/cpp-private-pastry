#include <iostream>
#include <typeinfo>
#include <unistd.h>

using namespace std;

class Base {
public:
	Base(int i):_i(i) {}
	virtual ~Base() { cout << "Base::~Base()\n";}
	virtual bool equal(const Base *rhs);
	void setI(int i) { _i = i;}
protected:
	int _i;
};

bool Base::equal(const Base *rhs) {
	cout << "Base::equal()\n";
	return _i == rhs->_i;
}

class Derived : public Base {
public:
	Derived(int i):Base(i-1),_i(i) {}
	virtual ~Derived() { cout << "Derived::~Derived() this=" << (long*)this << "\n";}
	virtual bool equal(const Base *rhs);

protected:
	int _i;
};

bool Derived::equal(const Base *rhs) { 
	cout << "Derived::equal() ";
	if (const Derived *dp = dynamic_cast<const Derived*>(rhs)) {
		cout << "_ii=" << _i << " rhs->ii=" << dp->_i << " _i=" << this->Base::_i << " rhs->_i=" << dp->Base::_i << "\n";
		return _i == dp->Base::_i && this->Base::_i == dp->Base::_i;
	}
	else {
		cout << "\n";
		return false;
	}
}

int main()
{
	//Base b(1);
	Derived d(2);
	Derived d2(3);

	long** pVtab = (long**)&d;
	
	typedef bool (*equalFun)(Derived*,const Base*);
	equalFun efunc = (equalFun)pVtab[0][2];
	cout << "pVtab[0]= " << (long*)pVtab[0] << "\n";
	cout << "efunc=" << (long*)efunc << endl;
	bool ret = efunc(&d,&d2);
	cout << "ret=" << ret << endl;

	const type_info &ti = typeid(d);
	cout << "typeinfo name=" << ti.name() << endl;
	type_info *tip = (type_info*)pVtab[0][-1];
	cout << "typeinfo ptr name=" << tip->name() << endl;
	
#if 0
	typedef void (*Fun)(Derived *);
	Fun func = (Fun)pVtab[0][0];
	cout << "pVtab[0]= " << (long*)pVtab[0] << "\n";
	func(&d);
	cout << "pVtab[0]= " << (long*)pVtab[0] << "\n";

#if 0	//crash because after Derived::~Devived(), the vptr have been destroy
	cout << "pVtab[0]= " << (long*)pVtab[0] << "\n";
	func = (Fun)pVtab[0][1];
	func(&d);
#endif
#endif
}
