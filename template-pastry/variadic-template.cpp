#include <iostream>
using namespace std;

void print() {} //for stopping infinite recursive variadic template

template <typename T>
void print(const T& arg)
{
	cout << "print<arg> " << arg << endl;
}

template <typename T, typename... Types>
void print(const T& firstArgs, const Types&... args)
{
	cout << firstArgs << endl;
	print(args...);
}


int main()
{
	print('a');
	print('a', 33, 44.0, "b");

	{
		int id = 0;
		auto f = [&id] () { cout << "id=" << id << endl; id++;};
		id = 42;
		f();
		f();
		f();
		cout << "final id=" << id << endl;
	}

	{
		int id = 1;
		auto f = [id] () mutable { cout << "id=" << id << endl; id++;};
		id = 42;
		f();
		f();
		f();
		cout << "final id=" << id << endl;
	}
	return 0;
}
