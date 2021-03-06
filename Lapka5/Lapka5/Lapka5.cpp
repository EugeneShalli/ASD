#include "pch.h"
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <windows.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
const int str = 5;

void DisplaySequence(HashTable& table) {
	//cout << endl;

	for (int i = 0; i < table.sequence.size(); ++i) {
		if (i % 35 == 0) {
			cout << endl;
		}
		cout.width(3);
		//cout << "(" << table.sequence.at(i) << ") ";
		//try {
		cout << table.values.at(table.sequence.at(i));
			//cout << table.sequence.at(i);
		//}
		//catch (...) {
			//cout << table.values.at(table.sequence.at(i));
		//}
	}
	cout << endl;
}

void DisplayHashTable(HashTable& H) {
	std::vector<int> keys;
	keys.reserve(H.values.size());
	std::vector<char> vals;
	vals.reserve(H.values.size());

	for (auto kv : H.values) {
		keys.push_back(kv.first);
		vals.push_back(kv.second);
	}

	for (int i = 0; i < alphabet; ++i) {
		if (i % str == 0) {
			cout << endl;
		}
		//cout.width(7 - (i>=10));
		//cout << "(" << keys.at(i) << ")" << H.values.at(keys.at(i));
		cout.width(7 - (i >= 10));
		cout << "(" << i << ")";
		try {
			cout << H.values.at(i);
		}
		catch (...) {
			cout << " ";
			//cout.width(7 - (i >= 10));
		}
	}
	cout << endl;
}

int main()
{

	std::srand(unsigned(std::time(0)));

	HashTable setA(4);
	cout << "A:";
	DisplaySequence(setA);
	//cout << setA.values.size() << "AAAAAAAAAAAAAAAAAAAAAAAAAA";
	HashTable setB(4);
	cout << "B:";
	DisplaySequence(setB);

	HashTable setC(4);
	cout << "C:";
	DisplaySequence(setC);

	HashTable setD(0); //this is for merge

	//setA.erase(1, 4);
	//DisplaySequence(setA);

	//setA.change(setB, 2);
	//DisplaySequence(setA);

	cout << "MERGE:";
	setA.merge(setA, setB);
	DisplaySequence(setA);

	cout << "OR: ";
	DisplayHashTable(setA = setA|setB);
	//DisplaySequence(setA = setA & setB);
	//DisplaySequence(setA = setA - setC);
	//DisplaySequence(setA = setA + setB);




	//cout << endl;
	//cout << "SUBST:";
	//setA.subst(setB,2);
	//DisplaySequence(setA);
	//
	//cout << "EXCL: ";
	//setA.excl(setB);
	//DisplaySequence(setA);

	//cout << "MERGE:";
	//setA.merge(setA, setB);
	//DisplaySequence(setA);

	//DisplaySequence(setD);
	//cout << "ERASE";
	//setD.erase(2, 4);
	//DisplaySequence(setD);
	//setA.concat(setB);
	//cout << "1:";
	//DisplaySequence(setA);
	//setA.mul(1);
	//cout << "2:";
	//DisplaySequence(setA);
	//setA.concat(setC);
	//cout << "3:";
	//DisplaySequence(setA);
	//setA.excl(setB);
	//cout << "4:";
	//DisplaySequence(setA);
	
	system("pause");

	return 0;
}
