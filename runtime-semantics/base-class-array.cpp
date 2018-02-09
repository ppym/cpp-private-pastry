#include "common.h"
using namespace std;

class Point {
public:
	Point() {cout << "Point::Point() this " << (long*)this << "\n";}
	virtual ~Point() {cout << "Point::~Point() " << (long*)this << "\n";}
};

class Point3d : public Point {
public:
	Point3d() {cout << "Point3d::Point3d() " << (long*)this << "\n";}
	virtual ~Point3d() {cout << "Point3d::~Point3d() " << (long*)this << "\n";}
};

//from standard http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf
//[expr.delet]
//"In the first alternative (delete object), if the static type of the object to be deleted is different from its dynamic
//type, the static type shall be a base class of the dynamic type of the object to be deleted and the static type
//shall have a virtual destructor or the behavior is undefined. In the second alternative (delete array) if the
//dynamic type of the object to be deleted differs from its static type, the behavior is undefined."

//stackoverflow https://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents
//https://stackoverflow.com/questions/6171814/why-is-it-undefined-behavior-to-delete-an-array-of-derived-objects-via-a-base
int main() 
{
	Point3d *ptr3d = new Point3d[10];
	Point *ptr = new Point3d[10];
	
	cout << "------- print ptr3d sizeof(Point3d)=" << sizeof(Point3d) << " -------\n";
	for (int i=0; i<10; i++)
		cout << "ptr3d[" << i << "]" << (long*)&ptr3d[i] << endl;

	cout << "------- print ptr -------\n";
	for (int i=0; i<10; i++)
		cout << "ptr[" << i << "]" << (long*)&ptr[i] << endl;

	cout << "------- delete [] ptr3d -------\n";
	delete [] ptr3d;	

	cout << "------- delete [] ptr -------\n";
	delete [] ptr;	
}

