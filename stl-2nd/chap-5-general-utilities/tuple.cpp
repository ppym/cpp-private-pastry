#include <iostream>
#include <functional>
#include <tuple>
using namespace std;

template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
	static void print(std::ostream& os, const std::tuple<Args...> &t) {
		os << std::get<IDX>(t) << (IDX+1==MAX ? "" : ","); //std::get<n> 编译器时候resovle
		PRINT_TUPLE<IDX+1, MAX, Args...>::print(os, t);
	}
};

//partial specialization to end the recursion.
template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
	static void print(std::ostream& os, const std::tuple<Args...>& t) {
	}
};

template <typename... Args>
std::ostream& operator << (std::ostream& os, const std::tuple<Args...> &t) //加上const支持rvalue
{
	os << "[";
	PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
	os << "]";
	return os;
}

int main()
{
	tuple<int ,double, double> t1(1, 2.0, 3.44);
	cout << std::get<0>(t1) << " ";
	cout << std::get<1>(t1) << " ";
	cout << std::get<2>(t1) << " ";
	//cout << std::get<3>(t1) << " ";
	cout << endl;

	//init with zero
	tuple<int,double,int> t2;

	auto t3 = std::make_tuple(22,33.2,34);
	get<1>(t1) = get<1>(t3);
	cout << get<1>(t1) << endl;

	t1 = t3;
	cout << std::get<0>(t1) << " ";
	cout << std::get<1>(t1) << " ";
	cout << std::get<2>(t1) << " ";
	//cout << std::get<3>(t1) << " ";
	cout << endl;

	std::string s("abc");
	auto x = std::make_tuple(s); //tuple<string>
	cout << "get<0>(x)=" << std::get<0>(x) << endl;
	std::get<0>(x) = "my";
	cout << "get<0>(x)=" << std::get<0>(x) << endl;
	
	auto y = std::make_tuple(std::ref(s));
	cout << "s=" << s << endl;
	std::get<0>(y) = "my";
	cout << "s=" << s << endl;

	//cout << "tuple_size=" << std::tuple_size<
	cout << t3 << endl;
	cout << std::make_tuple<int, double>(13,33.2);
}
