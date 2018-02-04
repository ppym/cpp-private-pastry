#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

class Point2d {
public:
	Point2d(float x = 0.0, float y = 0.0):_x(x),_y(y) {	}
	~Point2d(){}
protected:
	float _x, _y;
};

class Point3d : public Point2d {
public:
	friend void cross_product_friend(const Point3d &pA, Point3d &pB);
	Point3d(float x=0.0, float y=0.0, float z=0.0):
		Point2d(x,y),_z(z) {}

	inline void cross_product( const Point3d &pA, const Point3d &pB) {
		Point3d pC;
		pC._x = pA._y * pB._z - pA._z * pB._y;
		pC._y = pA._z * pB._x - pA._x * pB._z;
		pC._z = pA._x * pB._y - pA._y * pB._x;
	}

	static void cross_product_static( const Point3d &pA, const Point3d &pB) {
		Point3d pC;
		pC._x = pA._y * pB._z - pA._z * pB._y;
		pC._y = pA._z * pB._x - pA._x * pB._z;
		pC._z = pA._x * pB._y - pA._y * pB._x;
	}

	virtual void cross_product_virtual( const Point3d &pA, const Point3d &pB) {
		Point3d pC;
		pC._x = pA._y * pB._z - pA._z * pB._y;
		pC._y = pA._z * pB._x - pA._x * pB._z;
		pC._z = pA._x * pB._y - pA._y * pB._x;
	}
protected:
	float _z;
};

void cross_product_friend(const Point3d &pA, Point3d &pB)
{
	Point3d pC;
	pC._x = pA._y * pB._z - pA._z * pB._y;
	pC._y = pA._z * pB._x - pA._x * pB._z;
	pC._z = pA._x * pB._y - pA._y * pB._x;
}

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

int main()
{
	timespec tstart, tend;
	Point3d pA(1.725, 0.875, 0.478);
	Point3d pB(0.315, 0.317, 0.838);
	Point3d pC;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tstart);
	for ( long i=0; i<10000000; i++) 
		pC.cross_product(pA, pB);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tend);
	cout<<diff(tstart,tend).tv_sec<<":"<<diff(tstart,tend).tv_nsec<<endl;
#if 0
	printf("Estimated overhead: %lld ns\n",
			((int64_t) tend.tv_sec * 1000000000 + (int64_t) tend.tv_nsec
			 - ((int64_t) tstart.tv_sec * 1000000000
				 + (int64_t) tstart.tv_nsec)) / N / 10);
#endif
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tstart);
	for ( long i=0; i<10000000; i++) 
		cross_product_friend(pA, pB);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tend);
	cout<<diff(tstart,tend).tv_sec<<":"<<diff(tstart,tend).tv_nsec<<endl;
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tstart);
	for ( long i=0; i<10000000; i++) 
		Point3d::cross_product_static(pA, pB);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tend);
	cout<<diff(tstart,tend).tv_sec<<":"<<diff(tstart,tend).tv_nsec<<endl;

	Point3d *ppc = &pC;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tstart);
	for ( long i=0; i<10000000; i++) 
		ppc->cross_product_virtual(pA, pB);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tend);
	cout<<diff(tstart,tend).tv_sec<<":"<<diff(tstart,tend).tv_nsec<<endl;
	return 0;
}
