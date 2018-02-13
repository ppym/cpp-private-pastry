#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Person :public enable_shared_from_this<Person> {
public:
	std::string name;
	std::shared_ptr<Person> mother;
	std::shared_ptr<Person> father;
	vector<weak_ptr<Person>> kids;
	
	Person(const string&n,
		shared_ptr<Person> m = nullptr,
		shared_ptr<Person> f = nullptr)
	: name(n), mother(m), father(f) {}

	void setParentsAndTheirKids(shared_ptr<Person> m=nullptr, 
				shared_ptr<Person> f=nullptr) {
		mother = m;
		father = f;
		if (m != nullptr)
			m->kids.push_back(shared_from_this());
		if (f != nullptr)
			m->kids.push_back(shared_from_this());
	}
	~Person() {
		cout << "~Person " << name << endl;	
	}
};

shared_ptr<Person> initFamily(const string& name)
{
	shared_ptr<Person> mom(new Person(name+"'s mom"));
	shared_ptr<Person> dad(new Person(name+"'s dad"));
	shared_ptr<Person> kid(new Person(name));
	
	kid->setParentsAndTheirKids(mom,dad);
	return kid;
}

int main()
{
	shared_ptr<Person> p = initFamily("pids");
	cout << p.use_count() << endl;
	cout << p->mother->kids[0].lock()->name << endl;
	//p = initFamily("ppp");
}
