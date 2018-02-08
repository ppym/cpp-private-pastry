#include "common.h"
using namespace std;

class Point {
};

class Point1d: public virtual Point {
public:
	Point1d(double x=0.0):_x(x){}
protected:
	double _x;
};

class Point2d: public virtual Point {
public:
	Point2d(double y=0.0):_y(y){}
protected:
	double _y;
};

class Point3d : public Point1d, public Point2d {
public:
	Point3d(double x=0.0, double y=0.0, double z=0.0):
		Point1d(x),Point2d(y),_z(z){}
protected:
	double _z;
};

Point3d lost_of_copies (Point3d a, Point3d b)
{
	Point3d pC = a;
	pC = b;
	b = a;
	return pC;
}

int main(int argc, char *argv[])
{
	Timer timer;
	timer.Start();
	Point3d PA(1.725, 0.323, 1.233);
	Point3d PB(1.235, 1.691, 0.322);
	Point3d PC;

	for (int i=0; i < LOOP_TIME; i++)
		PC = lost_of_copies(PA, PB);

	timer.Stop();
	cout << argv[0] << "\tTime Elapsed " << timer.GetElapsedMillseconds() << "ms" <<endl;
	return 0;
}
