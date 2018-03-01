#include <iostream>
#include <deque>
#include <assert.h>
#include <algorithm>

using namespace std;

enum ShipDirection {
	Bank1ToBank2,
	Bank2ToBank1,
};

struct PassAction {
	PassAction (int monk_, int monster_, ShipDirection ship_):
		monk(monk_),
		monster(monster_),
		ship(ship_) {}
	int monk;
	int monster;
	ShipDirection ship;
};

struct RiverBank{
	int monk;
	int monster;
	bool operator == (RiverBank &other) {
		return monk == other.monk && monster == other.monster;
	}
};

struct RiverBankStatus {
	RiverBankStatus():pass(PassAction(3,3,Bank2ToBank1)) {
		bank1.monk = 3;
		bank1.monster = 3;
		bank2.monk = 0;
		bank2.monster = 0;
	}
	RiverBankStatus(const RiverBankStatus &other):
		bank1(other.bank1),
		bank2(other.bank2),
		pass(other.pass) {}

	RiverBank bank1;
	RiverBank bank2;
	PassAction pass;
	void setAction(PassAction &action);
	bool operator == (RiverBankStatus &other) {
		return bank1 == other.bank1 && bank2 == other.bank2 && pass.ship == other.pass.ship;
	}
	bool isFinalStatus() {
		return bank1.monk == 0 && bank1.monster == 0 && bank2.monk == 3 && bank2.monster == 3
			&& pass.ship == Bank1ToBank2;
	}
};

std::ostream& operator << (std::ostream &os, const ShipDirection &ship)
{
	assert (ship == Bank1ToBank2 || ship == Bank2ToBank1);
	os << "(" << (ship==Bank1ToBank2 ? "Bank1ToBank2" : "Bank2ToBank1") << ")";
	return os;
}

std::ostream& operator << (std::ostream &os, const RiverBankStatus &status)
{
	os << '[' << status.bank1.monk << ',' << status.bank1.monster << "]," << '[' << status.bank2.monk << ',' << status.bank2.monster << "]," << status.pass.ship;
	return os;
}

void RiverBankStatus::setAction(PassAction &action)
{
	pass = action;
	if (action.ship == Bank1ToBank2) {
		bank1.monk -= action.monk;
		bank1.monster -= action.monster;
		bank2.monk += action.monk;
		bank2.monster += action.monster;
	}

	if (action.ship == Bank2ToBank1) {
		bank2.monk -= action.monk;
		bank2.monster -= action.monster;
		bank1.monk += action.monk;
		bank1.monster += action.monster;
	}
}

bool MonsterEatMonk(int monk, int monster, RiverBankStatus &currStatus) 
{
	assert (currStatus.pass.ship == Bank1ToBank2 || currStatus.pass.ship == Bank2ToBank1);
	if ((monk == 0 && monster == 0) || (monk + monster) > 2)
		return true;

//	cout << "MonsterEatMonk monk= " << monk << ",monster= " << monster << ",curr= " << currStatus << endl;
	if (currStatus.pass.ship == Bank2ToBank1) { //当前的船只停在bank1,下一步开往bank2
		if (monk > currStatus.bank1.monk || monster > currStatus.bank1.monster) //运过去的不能超过当前的
			return true;

		if ((currStatus.bank1.monk - monk) > 0) {
			if ((currStatus.bank2.monk + monk) > 0) 
				return ((currStatus.bank1.monster - monster) > (currStatus.bank1.monk - monk)) ||
					((currStatus.bank2.monster + monster) > (currStatus.bank2.monk + monk));
			else
				return ((currStatus.bank1.monster - monster) > (currStatus.bank1.monk - monk));
		}
		else {
			if ((currStatus.bank2.monk + monk) > 0) 
				return ((currStatus.bank2.monster + monster) > (currStatus.bank2.monk + monk));
			else
				assert(0);
		}
	}

	if (currStatus.pass.ship == Bank1ToBank2) { //当前的船只停在bank2,下一步开往bank1
		if (monk > currStatus.bank2.monk || monster > currStatus.bank2.monster) //运过去的不能超过当前的
			return true;

		if ((currStatus.bank2.monk - monk) > 0) {
			if ((currStatus.bank1.monk + monk) > 0) 
				return ((currStatus.bank2.monster - monster) > (currStatus.bank2.monk - monk)) || 
					((currStatus.bank1.monster + monster) > (currStatus.bank1.monk + monk));
			else
				return ((currStatus.bank2.monster - monster) > (currStatus.bank2.monk - monk));
		}
		else {
			if ((currStatus.bank1.monk + monk) > 0) 
				return ((currStatus.bank1.monster + monster) > (currStatus.bank1.monk + monk));
			else
				assert(0);
		}

	}
	return true;
}

bool IsSearchLoop(deque<RiverBankStatus> &stas, RiverBankStatus &next)
{
	return find_if(stas.begin(), stas.end(), [&](RiverBankStatus &it) { return it == next;}) != stas.end();
}

void PrintResult(deque<RiverBankStatus> &stas)
{
	cout << endl;
	cout << "****************************" << endl;
	for (deque<RiverBankStatus>::iterator it = stas.begin(); it != stas.end(); it++) {
		assert (it->pass.ship == Bank1ToBank2 || it->pass.ship == Bank2ToBank1);
		if (it->pass.ship == Bank1ToBank2) {
			cout << "[bank1------>bank2]:";
			cout << '[' << it->bank1.monk << ',' << it->bank1.monster << "],[" << it->bank2.monk << "," << it->bank2.monster << "]";
			cout << '(' << it->pass.monk << ',' << it->pass.monster << ")-----" << endl;
		}
		if (it->pass.ship == Bank2ToBank1) {
			cout << "[bank2------>bank1]:";
			cout << '[' << it->bank1.monk << ',' << it->bank1.monster << "],[" << it->bank2.monk << "," << it->bank2.monster << "]";
			cout << '(' << it->pass.monk << ',' << it->pass.monster << ")-----" << endl;
		}
	}

	cout << endl;
}

void CrossRiver(deque<RiverBankStatus> &stas)
{
	RiverBankStatus curr = stas.back();
	if (curr.isFinalStatus()) {
		PrintResult(stas);
		return;
	}

	for (int monk=0; monk <= 2; monk++) {
		for (int monster=0; monster <= 2; monster++) {
			if (!MonsterEatMonk(monk, monster, curr)) {
//				cout << "Pass " << monk << "," << monster << endl;
				assert (curr.pass.ship == Bank1ToBank2 || curr.pass.ship == Bank2ToBank1);
				PassAction action(monk, monster, (curr.pass.ship == Bank1ToBank2) ? Bank2ToBank1 : Bank1ToBank2);
				RiverBankStatus next(curr);
				next.setAction(action);
				if (!IsSearchLoop(stas, next)) {
//					cout << "Pass 2: next=" << next << endl;
					stas.push_back(next);
					CrossRiver(stas);
					stas.pop_back();
				}
			}
		}
	}
}

int main() 
{
	deque<RiverBankStatus> deq_bank;
	deq_bank.push_back(RiverBankStatus());

	CrossRiver(deq_bank);
}

