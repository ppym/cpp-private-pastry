#include <iostream>
#include <deque>
#include <assert.h>
#include <algorithm>

using namespace std;

enum BoatLocate {
	Bank1,
	Bank2,
};

struct PassAction {
	PassAction (BoatLocate boat_, int monk_, int monster_):
		boat_to(boat_), 
		monk(monk_),
		monster(monster_)
		{}
	BoatLocate boat_to;
	int monk;
	int monster;
};

struct PassAction action[] = {
	{Bank2, -1, 0},
	{Bank2, -1, -1},
	{Bank2, 0, -1},
	{Bank2, -2, 0},
	{Bank2, 0, -2},
	{Bank1, 1, 0},
	{Bank1, 1, 1},
	{Bank1, 0, 1},
	{Bank1, 2, 0},
	{Bank1, 0, 2},
};

struct RiverBank{
	int monk;
	int monster;
	bool operator == (RiverBank &other) {
		return monk == other.monk && monster == other.monster;
	}
};

struct RiverBankState {
	RiverBankState():act(action[9]){
		bank1.monk = monk_count;
		bank1.monster = monster_count;
		bank2.monk = 0;
		bank2.monster = 0;
		boat = Bank1;
	}

	static int monk_count;
	static int monster_count;

	RiverBank bank1;
	RiverBank bank2;
	BoatLocate boat;
	PassAction act;

	bool canSetAction(PassAction &action);
	bool IsValidState();

	bool operator == (RiverBankState &other) {
		return bank1 == other.bank1 && bank2 == other.bank2 && boat == other.boat;
	}
	bool isFinalStatus() {
		return bank1.monk == 0 && bank1.monster == 0 && bank2.monk == monk_count && bank2.monster == monster_count
			&& boat == Bank2;
	}
};

int RiverBankState::monk_count = 3;
int RiverBankState::monster_count = 3;

std::ostream& operator << (std::ostream &os, const BoatLocate &boat)
{
	assert (boat == Bank1 || boat == Bank2);
	os << "(" << (boat==Bank1 ? "Bank1" : "Bank2") << ")";
	return os;
}

std::ostream& operator << (std::ostream &os, const PassAction &ac)
{
	os << '[' << ac.boat_to << "," << ac.monk << "," << ac.monster << "]";
	return os;
}
std::ostream& operator << (std::ostream &os, const RiverBankState &state)
{
	os << "{" << '[' << state.bank1.monk << ',' << state.bank1.monster << "]," << '[' << state.bank2.monk << ',' << state.bank2.monster << "]," << state.boat << "}";
	return os;
}

bool RiverBankState::canSetAction(PassAction &action)
{
	if (boat == action.boat_to)
		return false;

	if (bank1.monk + action.monk < 0 || bank1.monk + action.monk > monk_count)
		return false;
	if (bank1.monster + action.monster < 0 || bank1.monster + action.monster > monster_count)
		return false;

	return true;
}

bool RiverBankState::IsValidState() 
{
	if (bank1.monk < 0 || bank1.monster < 0 || bank2.monk < 0 || bank2.monster < 0) {
		return false;
	}
	if (bank1.monk + bank2.monk < 0 || bank1.monk + bank2.monk > monk_count) {
		return false;
	}
	if (bank1.monster + bank2.monster < 0 || bank1.monster + bank2.monster > monster_count) {
		return false;
	}
	if (bank1.monk != 0 && bank1.monster > bank1.monk) {
		return false;
	}
	if (bank2.monk != 0 && bank2.monster > bank2.monk) {
		return false;
	}

	return true;
}

bool IsSearchLoop(deque<RiverBankState> &stas, RiverBankState &next)
{
	return find_if(stas.begin(), stas.end(), [&](RiverBankState &it) { return it == next;}) != stas.end();
}

void PrintResult(deque<RiverBankState> &stas)
{
	cout << endl;
	cout << "****************************" << endl;
	for (deque<RiverBankState>::iterator it = stas.begin(); it != stas.end(); it++) {
		assert (it->act.boat_to == Bank2 || it->act.boat_to == Bank1);
		if (it->act.boat_to == Bank2) {
			cout << "[bank1------>bank2]:";
			cout << '[' << it->bank1.monk << ',' << it->bank1.monster << "],[" << it->bank2.monk << "," << it->bank2.monster << "]";
			cout << '(' << it->act.monk << ',' << it->act.monster << ")-----" << endl;
		}
		if (it->act.boat_to == Bank1) {
			cout << "[bank2------>bank1]:";
			cout << '[' << it->bank1.monk << ',' << it->bank1.monster << "],[" << it->bank2.monk << "," << it->bank2.monster << "]";
			cout << '(' << it->act.monk << ',' << it->act.monster << ")-----" << endl;
		}
	}

	cout << endl;
}

bool MakeNextState(RiverBankState &curr, PassAction &ac, RiverBankState &next)
{
	if(curr.canSetAction(ac)){
		next.bank1.monk = curr.bank1.monk + ac.monk;
		next.bank1.monster = curr.bank1.monster + ac.monster;
		next.bank2.monk = curr.bank2.monk - ac.monk;
		next.bank2.monster = curr.bank2.monster - ac.monster;
		next.boat = ac.boat_to;
		next.act  = ac;
		return true;
	}

	return false;
}

void CrossRiver(deque<RiverBankState> &stas);

void DoCrossRiver(deque<RiverBankState> &stas, RiverBankState &curr, PassAction &ac)
{
	RiverBankState next;
	if (MakeNextState(curr, ac, next)) {
		if (next.IsValidState() && !IsSearchLoop(stas, next)) {
			stas.push_back(next);
			CrossRiver(stas);
			stas.pop_back();
		}
	}

}

void CrossRiver(deque<RiverBankState> &stas)
{
	RiverBankState curr = stas.back();
	if (curr.isFinalStatus()) {
		PrintResult(stas);
		return;
	}

	for (auto &ac : action) {
		DoCrossRiver(stas, curr, ac);
	}
}

int main() 
{
	deque<RiverBankState> deq_bank;
	deq_bank.push_back(RiverBankState());

	CrossRiver(deq_bank);
}

