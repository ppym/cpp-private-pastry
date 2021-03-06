#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Person {
public:
	std::string name;
	std::shared_ptr<Person> mother;
	std::shared_ptr<Person> father;
	vector<weak_ptr<Person>> kids;
	
	Person(const string&n,
		shared_ptr<Person> m = nullptr,
		shared_ptr<Person> f = nullptr)
	: name(n), mother(m), father(f) {}

	~Person() {
		cout << "~Person " << name << endl;	
	}
};

shared_ptr<Person> initFamily(const string& name)
{
	shared_ptr<Person> mom(new Person(name+"'s mom"));
	shared_ptr<Person> dad(new Person(name+"'s dad"));
	shared_ptr<Person> kid(new Person(name,mom,dad));
	
	mom->kids.push_back(kid);
	dad->kids.push_back(kid);
	return kid;
}

int main()
{
	shared_ptr<Person> p = initFamily("pids");
	cout << p.use_count() << endl;
	cout << p->mother->kids[0].lock()->name << endl;
	//p = initFamily("ppp");
}
