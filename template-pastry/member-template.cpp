#include <iostream>
using namespace std;

template <typename T>
class Myclass {
public:
	Myclass(T i):value(i){
		cout << "Myclass value=" << value << endl;
	}
	Myclass(const Myclass<T> &rhs) {
		cout << "Myclass copy ctor" << endl;
	}
	template <typename C>
	Myclass(const Myclass<C> &rhs) {	
		cout << "Myclass member template copy ctor" << endl;
	}

//	void assign (const Myclass<T> &x) {
//		cout << "member assign " << endl;
//		value = x.value;
//	}

	T getValue() const {return value;}

	template <typename C>
	void assign (const Myclass<C> &x) {
		cout << "member template assign " << endl;
		value = x.getValue();
	}

private:
	T value;
};

void f(Myclass<int> p)
{
	cout << "f(Myclass<int>" << endl;
}

void g(Myclass<double> p)
{
	cout << "g(Myclass<double>" << endl;
}

int main()
{
	Myclass<int> i(1);
	Myclass<double> d(4.2);
	
	d.assign(d);
	d.assign(i);
	f(i);
	g(i);
}
