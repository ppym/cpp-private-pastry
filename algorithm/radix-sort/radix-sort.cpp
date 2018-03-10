#include <iostream>
#include <iterator>
#include <cmath>
#include <array>
using namespace std;

#define CR std::cout << std::endl;
template <typename C>
void printContainer(C c)
{
	copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " ")); 
	CR;
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
	for (base=1; base<max_base; base++) {
		for (int i=0; i<10; i++) dec[i] = 0;

		cout << "==============base=" << base << endl;
		int base_cnt = pow(10, base-1);
		if (base%2) {
			for (int j=0; j<N; j++)
				dec[(C[j]/(base_cnt))%10]++;
			//copy (dec, dec+10, ostream_iterator<int>(cout, " ")); CR;
			for (int j=1; j<10; j++)
				dec[j] += dec[j-1];
			//copy (dec, dec+10, ostream_iterator<int>(cout, " ")); CR;
			for (int j=N-1; j>=0; j--) {
				int locate = dec[(C[j]/base_cnt)%10] -1;
				B[locate] = C[j];
				dec[(C[j]/base_cnt)%10]--;
				//cout << j << ": C[j]" << C[j] << " locate=" << locate << " B[locate]=" << B[locate] 
				 //<< " dec= " << dec[(C[j]/base_cnt)%10] << endl;
				//copy (B, B+10, ostream_iterator<int>(cout, " ")); CR;
			}
			//copy (B, B+10, ostream_iterator<int>(cout, " ")); CR;
		}
		else {
			for (int j=0; j<N; j++)
				dec[(B[j]/base_cnt)%10]++;
			for (int j=1; j<10; j++)
				dec[j] += dec[j-1];
			//copy (dec, dec+10, ostream_iterator<int>(cout, " ")); CR;
			for (int j=N-1; j>=0; j--) {
				int locate = dec[(B[j]/base_cnt)%10] -1;
				C[locate] = B[j];
				dec[(B[j]/base_cnt)%10]--;
			}
			//copy (C, C+10, ostream_iterator<int>(cout, " ")); CR;
		}
	}

	if ((base%2)) {
		copy(C, C+N, B);
	}
	delete C;
}

int main()
{
	int *A, *B, N=100, K=10000;
	A = new int[N];
	B = new int[N];
#if 0
	const int N=100, K=10000;
	array<int, N> A;
	array<int, N> B;
#endif
	
	for (int i=0; i<N; i++)
		A[i] = rand()%K +1;
	
	copy(A, A+N, ostream_iterator<int>(cout, " ")); CR;
	RadixSort(A, B, N, K);
	copy(B, B+N, ostream_iterator<int>(cout, " ")); CR;
	for (int i=N-1; i>0; i--){
		if (B[i] < B[i-1]) {
			cerr << "error result at[" << i << "]" << endl;
		}
	}
}
