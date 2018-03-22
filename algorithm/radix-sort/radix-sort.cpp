#include <iostream>
#include <iterator>
#include <cmath>
#include <array>
#include "../../common/timer.h"

using namespace std;

#define CR std::cout << std::endl;
template <typename C>
void printContainer(C c)
{
	copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " ")); 
	CR;
}

void RadixSortBase(int *A, int *B, int N, int base)
{
	int *C = new int[N];
	delete C;
}

void RadixSort(int *A, int *B, int N, int K)
{
	int *C = new int[N];
	int dec[10];
	int max_base=1;
	while(K=K/10) 
		max_base++;

	copy (A, A+N, C);

	int base;
	int *from, *to;
	for (base=1; base<=max_base; base++) {
		cout << "base =     " << base << endl;
		for (int i=0; i<10; i++) dec[i] = 0;

		int base_cnt = pow(10, base-1);
		if (base%2) {
			from = C;
			to = B;
		}
		else {
			from = B;
			to = C;
		}
		for (int j=0; j<N; j++)
			dec[(from[j]/(base_cnt))%10]++;
		for (int j=1; j<10; j++)
			dec[j] += dec[j-1];
		for (int j=N-1; j>=0; j--) {
			int &locate = dec[(from[j]/base_cnt)%10];
			to[locate-1] = from[j];
			locate--;
		}
	}

	if ((base%2)) {
		copy(C, C+N, B);
	}
	delete C;
}

int main()
{
	Timer timer;
	int *A, *B, N=100000, K=1000;
	A = new int[N];
	B = new int[N];

	srand(time(NULL));
	for (int i=0; i<N; i++)
		A[i] = rand()%K +1;
	
	copy(A, A+N, ostream_iterator<int>(cout, " ")); CR;
	timer.Start();
	RadixSort(A, B, N, K);
	timer.Stop();
	cout << "timer cost " << timer.GetElapsedMillseconds() << "ms" << endl;
	copy(B, B+N, ostream_iterator<int>(cout, " ")); CR;
	for (int i=N-1; i>0; i--){
		if (B[i] < B[i-1]) {
			cerr << "error result at[" << i << "] "  << B[i] << " " << B[i-1] << endl;
		}
	}
	delete A;
	delete B;
	return 0;
}
