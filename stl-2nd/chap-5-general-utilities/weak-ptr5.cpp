#include <iostream>
#include <vector>
#include <memory>
#include <pthread.h>

using namespace std;
class Person;

class Person :public enable_shared_from_this<Person> {
public:
	std::string name;
	std::shared_ptr<Person> mother;
	std::shared_ptr<Person> father;
	vector<weak_ptr<Person>> kids;
	long money;
	
	Person(const string&n,
		shared_ptr<Person> m = nullptr,
		shared_ptr<Person> f = nullptr)
	: name(n), mother(m), father(f), money(0) {}

	void setParentsAndTheirKids(shared_ptr<Person> m=nullptr, 
				shared_ptr<Person> f=nullptr) {
		mother = m;
		father = f;
		if (m != nullptr)
			m->kids.push_back(shared_from_this());
		if (f != nullptr)
			m->kids.push_back(shared_from_this());
	}
	
	void moneyInc() { money++; }
	long getMoney() { return money;}

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

shared_ptr<Person> Me;

void *thread(void* argv)
{
	int i = 0;
	while(i < 10000000) {
		Me->moneyInc();
		i++;
	}

	return NULL;
}

int main()
{
	pthread_t pid1;
	pthread_t pid2;

	Me = initFamily("pids");
	pthread_create(&pid1, NULL, thread, NULL);
	pthread_create(&pid2, NULL, thread, NULL);
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
	cout << "My total money=" << Me->getMoney() << endl;
	{
		unique_ptr<int> up1(new int(2));
		unique_ptr<int> up2;
		//	up2 = up1; //error
		up2 = std::move(up1);
		cout << *up2 << endl;
		cout << *up1 << endl;
	}
}
