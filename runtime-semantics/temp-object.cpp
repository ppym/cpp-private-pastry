#include <iostream>
#include <string.h>
using namespace std;

class String {
	friend String operator +(const String &lhs,const String &rhs);
public:
	String(const char *str);
	String(const char *str, int len);
	~String();
	operator char*();
private:
	char *_str;
	int _len;
};

String::String(const char *str)
{
	if(str) {
		_len = strlen(str);
		_str = new char [_len+1];
		strncpy(_str, str, _len);
		_str[_len] = 0;
	}
	cout << "String::String " << (long*)_str << endl;
}

String::String(const char *str, int len)
{
	if(str) {
		_len = len;
		_str = new char [_len+1];
		strncpy(_str, str, _len);
		_str[_len] = 0;
	}
	cout << "String::String " << (long*)_str << endl;
}

String::~String()
{
	if(_str){
		cout << "String::~String " << (long*)_str << endl;
		delete _str;
		_str = NULL;
		_len = 0;
	}
}

String::operator char*()
{
	return _str;
}

String operator +(const String &lhs,const String &rhs)
{
	cout << "operator +\n";
	int len = lhs._len + rhs._len;
	char * tmp = new char[len];
	strncpy(tmp, lhs._str, lhs._len);
	strncpy(tmp+lhs._len, rhs._str, rhs._len);
	String tmpStr(tmp, len);
	delete tmp;
	return tmpStr;
}

int main()
{
	{
		String name("name");
		String version("version");

		cout << "name= " << name << endl;
		cout << "version= " << version << endl;
		const char *namever = name + version;
		//C++ 编译器产生的伪代码大概如下：
		// String tmep;
		// operator+(temp, name, version);
		// namever = temp.String::operator char*();
		// temp.String::~String();
		// 所以，namever将指向一个被释放掉的临时对象
		cout << "namever addr=" << (long*)namever << endl;
		cout << "== " << namever << endl;
	}

	{
		cout << "test ref to temp object" << endl;
		const String &space = "";
	}
}

