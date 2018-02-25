#include <iostream>
#include <vector>
#include <algorithm>

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

int main()
{
	std::vector<Object> objCur = { {35,10},{30,40}, {60,30},{50,50},{40,35},{10,40},{25,30}};
	Bag bag(150);

	//按照重量最轻选择
	sort (objCur.begin(), objCur.end(), [] (Object o1, Object o2) { return o1.weigth < o2.weigth; });
	PrintContaiiner(objCur);

	for (Object &o : objCur) {
		if (o.status == UnSelect && (o.weigth + bag.getCurrC()) < bag.getTotalC()) {
			bag.addObject(o);
			o.status = Selected;
		}
	}
	PrintContaiiner(objCur);
	std::cout << "Bag total Contain: " << bag.getTotalC() << endl;
	std::cout << "Bag Curr Contain: " << bag.getCurrC() << endl;
	std::cout << "Bag total Price: " << bag.getTotalPrice() << endl;
}

