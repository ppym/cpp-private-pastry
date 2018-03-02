#include <iostream>
#include <assert.h>

using namespace std;

#define UNIT_COUNT 10

struct tagPargner {
	//char *name;
	tagPargner():
		next(0),
		current(-1),
		pCount(UNIT_COUNT){
		}
	int next;
	int current;
	int pCount;
	int perfect[UNIT_COUNT];
};

typedef struct tagPargner PARTNER;

int GetPerfectPosition(PARTNER *partner, int id)
{
	assert(partner->pCount == UNIT_COUNT);

	for (int i=0; i<partner->pCount; i++) {
		if (partner->perfect[i] == id)
			return i;
	}

	return 0x7FFFFFFF;
}

int FindFreeBoy(PARTNER *partner, int count)
{
	for (int i=0; i<count; i++) {
		if (partner[i].current == -1) {
			//cout << "FindFreeBoy" << i << endl;
			return i;
		}
	}
	//cout << "FindFreeBoy -1" << endl;
	return -1;
}

bool gale_shapley(PARTNER* boys, PARTNER* girls, int count)
{
	int bid = FindFreeBoy(boys, count);
	while (bid != -1) {
		int gid = boys[bid].perfect[boys[bid].next];
		if (girls[gid].current == -1) {
			boys[bid].current = gid;
			girls[gid].current = bid;
		}
		else {
			int bpid = girls[gid].current;
			if (GetPerfectPosition(&girls[gid], bpid) >  GetPerfectPosition(&girls[gid], bid)) {
				boys[bid].current = gid;
				girls[gid].current = bid;
				boys[bpid].current = -1;
			}
		}
		boys[bid].next++;
		bid = FindFreeBoy(boys, count);
	}
}

void PrintResult(PARTNER *boys, PARTNER *girls, int count)
{
	for (int i=0; i<count; i++) {
		cout <<  "boys(" << i << "," << boys[i].current << ")" << "," << boys[i].pCount << endl;
	}
	
	for (int i=0; i<count; i++) {
		cout << "girls(" << i << "," << girls[i].current << ")" << "," << girls[i].pCount << endl;
	}
}

void PrintPerfect(PARTNER *boys, PARTNER *girls, int count)
{
	for (int i=0; i<count; i++) {
		for (int j=0; j<count; j++)
			cout << boys[i].perfect[j] << " " << endl;
		cout << endl;
	}
	cout << endl;

	for (int i=0; i<count; i++) {
		for (int j=0; j<count; j++)
			cout << girls[i].perfect[j] << " ";
		cout << endl;
	}
	cout << endl;
}

int main() 
{
	PARTNER boys[UNIT_COUNT];
	PARTNER girls[UNIT_COUNT];

	cout << sizeof(boys) << endl;
	freopen("boys.in", "r", stdin);//重定向输入流
	for (int i=0; i<UNIT_COUNT; i++){
		for (int j=0; j<UNIT_COUNT; j++) {
			scanf("%d", &boys[i].perfect[j]);
		}
	}

	freopen("girls.in", "r", stdin);//重定向输入流
	for (int i=0; i<UNIT_COUNT; i++){
		for (int j=0; j<UNIT_COUNT; j++) {
			scanf("%d", &girls[i].perfect[j]);
		}
	}
	//PrintResult(boys, girls, UNIT_COUNT);

	gale_shapley(boys, girls, UNIT_COUNT);
	//PrintPerfect(boys, girls, UNIT_COUNT);
	PrintResult(boys, girls, UNIT_COUNT);
}

