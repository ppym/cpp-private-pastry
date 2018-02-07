#include <iostream>
using namespace std;

class Point {
public:
	Point(int x=1, int y=1):m_x(x),m_y(y) {}
	Point(const Point &rhs) {cout << "copy ctor\n"; m_x = rhs.m_x; m_y = rhs.m_y;}
	Point& operator=(const Point &rhs) { 
			cout << "= ctor\n"; 
			if (this == &rhs) return *this;
			m_x=rhs.m_x; m_y = rhs.m_y; return *this;}
	void x(int _x) { m_x=_x;}
	int x() {return m_x;}
	
	virtual int z(){ return 0.0;}
protected:
	int m_x;
	int m_y;
};

Point foobar()
{
	Point local;
	local.x(2);
	return local;
}

int main()
{
	Point m_local;
	cout << "m_local vptr=" << (long*)*(long*)&m_local << endl;
	m_local = foobar();
	cout << "m_local vptr=" << (long*)*(long*)&m_local << endl;
	cout << "m_local x()=" << m_local.x() << endl;

	//The vptr is not copied from the source object, but has to be initialized to point to the virtual table of the destination class. Therefore, a straight "memcpy" copy from source to destination is not possible.
	//https://stackoverflow.com/questions/28260322/what-does-a-non-trivial-copy-constructor-do
	Point *m_heap = new Point;
	cout << "m_heap vptr=" << (long*)*(long*)m_heap<< endl;
	cout << "m_heap x()=" << m_heap->x() << endl;
	*(long*)m_heap = 0x01010101; //destroy the vptr 
	cout << "m_heap vptr=" << (long*)*(long*)m_heap << endl;
	cout << "m_heap x()=" << m_heap->x() << endl;
	*m_heap = foobar();
	cout << "m_heap vptr=" << (long*)*(long*)m_heap<< endl;
	cout << "m_heap x()=" << m_heap->x() << endl;
	m_heap->z();
}

