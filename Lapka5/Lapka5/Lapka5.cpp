#include "pch.h"
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <windows.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

void DisplayHashTable(HashTable& table)
{
	for (int i = 0; i < table.sequence.size(); ++i)
	{
		cout.width(3);
		//cout << "(" << table.sequence.at(i) << ") ";
		try {
			cout << table.values.at(table.sequence.at(i));
			//cout << table.sequence.at(i);
		}
		catch (...) {
			//cout << table.values.at(table.sequence.at(i));
		}
	}
	cout << endl;
}

int main()
{

	std::srand(unsigned(std::time(0)));

	HashTable setA(4);
	cout << "A:";
	DisplayHashTable(setA);

	HashTable setB(4);
	cout << "B:";
	DisplayHashTable(setB);

	HashTable setC(4);
	cout << "C:";
	DisplayHashTable(setC);

	HashTable setD(0); //this is for merge

	//DisplayHashTable(setA = setA|setB);
	//DisplayHashTable(setA = setA & setB);
	//DisplayHashTable(setA = setA - setC);
	//DisplayHashTable(setA = setA + setB);




	//cout << endl;
	cout << "SUBST:";
	setA.subst(setB,2);
	DisplayHashTable(setA);
	//
	//cout << "EXCL: ";
	//setA.excl(setB);
	//DisplayHashTable(setA);

	//cout << "MERGE:";
	//setD.merge(setA, setB);
	//DisplayHashTable(setD);
	//displayhashtable(setD);
	//cout << "ERASE";
	//setD.erase(2, 4);
	//DisplayHashTable(setD);
	//setA.concat(setB);
	//cout << "1:";
	//DisplayHashTable(setA);
	//setA.mul(1);
	//cout << "2:";
	//DisplayHashTable(setA);
	//setA.concat(setC);
	//cout << "3:";
	//DisplayHashTable(setA);
	//setA.excl(setB);
	//cout << "4:";
	//DisplayHashTable(setA);
	
	system("pause");

	return 0;
}
