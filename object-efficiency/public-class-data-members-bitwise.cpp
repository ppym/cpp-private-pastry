#include "common.h"
using namespace std;

class Point3d {
public:
	double _x;
	double _y;
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
	Point3d PA = {1.725, 0.323, 1.233};
	Point3d PB = {1.235, 1.691, 0.322};
	Point3d PC;

	for (int i=0; i < LOOP_TIME; i++)
		PC = lost_of_copies(PA, PB);

	timer.Stop();
	cout << argv[0] << "\tTime Elapsed " << timer.GetElapsedMillseconds() << "ms" <<endl;
	return 0;
}
