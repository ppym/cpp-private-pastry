#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <cstdio>

using namespace std;

template <typename T>
class Deleter {
public:
	void operator ()(T *p) { 
		cout << "Deleter p=" << (long*)p << endl;
		delete p;
	}
};

class FileDeleter {
public:
	FileDeleter(const std::string& fn) : 
		filename(fn){}
	void operator ()(std::ofstream *fp) {
		cout << "FileDeleter fp=" << (long*)fp << endl;
		fp->close();	
		std::remove(filename.c_str());
	}
	
private:
	std::string filename;
};

class FileClass {
public:
	FileClass(const std::string& fn) :
		filename(fn), 
		ofstr(std::ofstream(fn)) {}

	virtual ~FileClass() {
		cout << "~FileClass" << endl;
		ofstr.close();
		std::remove(filename.c_str());		
	}

private:
	std::string filename;
	std::ofstream ofstr;
};

int main()
{
	std::shared_ptr<std::string> pA(new std::string("aaaa"));
	std::shared_ptr<std::string> pB(new std::string("bbbb"));

	cout << *pA << endl;
	(*pA)[0] = 'A';
	cout << *pA << endl;
	std::vector<std::shared_ptr<std::string>> vecP;

	vecP.push_back(pA);
	vecP.push_back(pB);
	vecP.push_back(pB);
	vecP.push_back(pA);
	vecP.push_back(pA);
	for (auto p : vecP)
		cout << *p << endl;
		
	cout << "after push vecP:" << pA.use_count() << endl;

	{ 
		std::shared_ptr<int> p(new int(2), Deleter<int>());
		cout << *p << endl;
		std::shared_ptr<int> p_l(new int(3), [](void *p){ cout << "lambda deleter p=" << (long*)p << endl;});
		std::shared_ptr<double> p_d(new double(2), Deleter<double>());
	}

	{
		//create and open tmp file
		std::shared_ptr<std::ofstream> fp(new std::ofstream("./tmpfile.txt"), FileDeleter("./tmpfile.txt"));
		//make_shared can't be used with custom deleter
		//std::shared_ptr<std::ofstream> fp = make_shared(new std::ofstream("./tmpfile.txt"), FileDeleter("./tmpfile.txt")); 
	}
	
	{
		std::shared_ptr<FileClass> pFC(new FileClass("./tmpFileClass.txt"));
	}
}
