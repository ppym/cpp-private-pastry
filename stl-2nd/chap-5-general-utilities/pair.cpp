#include <iostream>
#include <utility>
#include <functional>
using namespace std;

int main()
{
	std::string s("abccccc");
	std::string t("abdddd");
	cout << s << endl;
	cout << t << endl;
	
	auto p = std::make_pair(std::move(s), std::move(t));
	cout << "p.first=" << p.first << endl;
	cout << "p.second=" << p.second << endl;
	
	cout << "after move to pair" << endl;
	cout << s << endl;
	cout << t << endl;

	int i = 0;
	auto pp = std::make_pair(std::ref(i), std::ref(i));
	++pp.first;
	++pp.second;
	cout << "final i=" << i << endl;
}	

