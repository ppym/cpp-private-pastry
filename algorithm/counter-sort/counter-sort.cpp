#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include <algorithm>
#include <iterator>

using namespace std;
using pVecInt = std::shared_ptr<std::vector<int>>;
#define CR std::cout << std::endl

pVecInt GenerateRadomVec(int num, int k)
{
	std::vector<int> vec;
	pVecInt pv = std::make_shared<std::vector<int>>(std::move(vec));
	pv->resize(num);
	for (int i=1; i<num; i++) {
		pv->operator[](i) = (rand()%k+1);
	}
	return pv;
}

void CounterSort(pVecInt A, pVecInt B, pVecInt Order, int k)
{
	pVecInt C = make_shared<std::vector<int>>();
	C->resize(A->size());
	cout << "A->size()=" << A->size() << endl;
	cout << "B->size()=" << B->size() << endl;
	for (int i=1; i<A->size(); i++) {
		(*C)[(*A)[i]]++;
	}
	std::copy(++C->begin(), C->end(), std::ostream_iterator<int>(std::cout, " ")); CR;
	for (int i=1; i<A->size(); i++) {
		(*C)[i] = (*C)[i-1] + (*C)[i];
	}
	std::copy(++C->begin(), C->end(), std::ostream_iterator<int>(std::cout, " ")); CR;
	for (int i=A->size(); i>=1; i--) {
		int locate = (*C)[(*A)[i]];
		(*B)[locate] = (*A)[i];
		(*Order)[locate] = i;
		(*C)[(*A)[i]] --;
	}
}

int main() 
{
	int size = 101;
	pVecInt pvA = GenerateRadomVec(size, 11);
	pVecInt pvB = std::make_shared<std::vector<int>>();
	pvB->resize(size);
	pVecInt pvOrder = std::make_shared<std::vector<int>>();
	pvOrder->resize(size);

	std::copy(++pvA->begin(), pvA->end(), std::ostream_iterator<int>(std::cout, " ")); CR;
	CounterSort(pvA, pvB, pvOrder, 10);
	cout << "after CS\n";
	std::copy(++pvB->begin(), pvB->end(), std::ostream_iterator<int>(std::cout, " ")); CR;
	std::copy(++pvOrder->begin(), pvOrder->end(), std::ostream_iterator<int>(std::cout, " ")); CR;
}

