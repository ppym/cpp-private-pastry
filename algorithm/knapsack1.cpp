#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

enum SelectStatus{
	UnSelect,
	Selected,
	NoNeedSelect,
};

struct Object {
	unsigned int weigth;
	unsigned int price;
	SelectStatus status;
};

class Bag {
public:
	Bag(unsigned int c):totalC(c),currC(0), totalP(0){}
	bool addObject(const Object &o) {
		objV.push_back(o);
		currC += o.weigth;
		totalP += o.price;
		return true;
	}
	void reset() {objV.clear(); currC =0; totalP = 0;}

	unsigned int getCurrC() { return currC;}
	unsigned int getTotalC() { return totalC;}
	unsigned int getTotalPrice() { return totalP;}

private:
	std::vector<Object> objV;
	unsigned int totalC;
	unsigned int currC;
	unsigned int totalP;
};

std::ostream& operator << (std::ostream &os, const Object &o)
{
	os << '[' << o.weigth << ',' << o.price << ',' << o.status << ']';
	return os;
}

template <typename C>
void PrintContaiiner (C c)
{
	for (const auto &temp : c)
		std::cout << temp << ",";
	std::cout << std::endl;
}

template <typename C>
void PrintSelectedObject(C c)
{
	for (const auto &temp : c) {
		if (temp.status == Selected)
			std::cout << temp << ",";
	}
	std::cout << std::endl;
}

void selectByWeight(Bag &bag, std::vector<Object> &objs)
{
	//按照重量最轻选择
	sort (objs.begin(), objs.end(), [] (Object o1, Object o2) { return o1.weigth < o2.weigth; });

	for (Object &o : objs) {
		if (o.status == UnSelect && (o.weigth + bag.getCurrC()) <= bag.getTotalC()) {
			bag.addObject(o);
			o.status = Selected;
		}
	}
}
	
void selectByPrice(Bag &bag, std::vector<Object> &objs)
{
	sort (objs.begin(), objs.end(), [] (Object o1, Object o2) { return o1.price >= o2.price; });

	for (Object &o : objs) {
		if (o.status == UnSelect && (o.weigth + bag.getCurrC()) <= bag.getTotalC()) {
			bag.addObject(o);
			o.status = Selected;
		}
	}
}

void selectByDensity(Bag &bag, std::vector<Object> &objs)
{
	sort (objs.begin(), objs.end(), [] (Object o1, Object o2) { return (double)o1.price/o1.weigth >= (double)o2.price/o2.weigth; });

	for (Object &o : objs) {
		if (o.status == UnSelect && (o.weigth + bag.getCurrC()) <= bag.getTotalC()) {
			bag.addObject(o);
			o.status = Selected;
		}
	}
}

int main(int argc, char *argv[])
{
	std::vector<Object> objCur = { {35,10},{30,40}, {60,30},{50,50},{40,35},{10,40},{25,30}};
	Bag bag(150);
	{
		std::vector<Object> objs(objCur);

		selectByWeight(bag, objs);
		PrintContaiiner(objs);
		std::cout << "Bag selece Result[" << bag.getTotalC() << ',' << bag.getCurrC() << ',' << bag.getTotalPrice() << ']' << endl;
	}

	{
		std::vector<Object> objs(objCur);
		bag.reset();

		selectByPrice(bag, objs);
		PrintContaiiner(objs);
		std::cout << "Bag selece Result[" << bag.getTotalC() << ',' << bag.getCurrC() << ',' << bag.getTotalPrice() << ']' << endl;
	}

	{
		std::vector<Object> objs(objCur);
		bag.reset();

		selectByDensity(bag, objCur);
		PrintContaiiner(objCur);
		std::cout << "Bag selece Result[" << bag.getTotalC() << ',' << bag.getCurrC() << ',' << bag.getTotalPrice() << ']' << endl;
	}
	return 0;
}

