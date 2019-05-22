#pragma once
//#include <map>
#include <list>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include<vector>

//using std::map;
using namespace std;
using std::unordered_map;
using std::list;
using std::find;
using std::advance;
using std::sort;
using std::vector;
using std::max;
const int alphabet = 26;


class HashTable
{
private:
	


	int hashfunc(int key) const
	{
		return key % 1000;
	}

	

	void clear()
	{
		values.clear();
		sequence.clear();
	}

	int index_operator(int index) const
	{
		if (values.size() > index)
		{
			return values.at(index);
		}
		throw;
		//return NULL;
	}

	void delete_element(int index)
	{
		//for (int i = index; i < size() - 1; ++i)
			//values[i] = values[i + 1];

		values.erase(index);
	}

public:
	unordered_map<int, char> values;
	vector<int> sequence;
	//vector<int> sequence;

	HashTable() {}

	explicit HashTable(int size) {
		//maxValue++;
		int k = 0;
		int i = 0;
		vector<int>::iterator it;
		while (k < size) {
			if (i == alphabet) {
				i = 0;
			}
			it = find(sequence.begin(), sequence.end(), i);
			if (rand() % 2 && it == sequence.end() /*&& *(sequence.end()) != i*/) {
				add(i);
				sequence.push_back(i);
				k++;
			}
			i++;
			//k++;
		}
	}

	//HashTable(HashTable&& H) /*: values(H.values), sequence(H.sequence)*/{
	//	values = H.values;
	//	sequence = H.sequence;
	//}

	void DisplayHashTable(HashTable&& table)
	{
		for (int i = 0; i < table.size(); ++i)
		{
			cout.width(3);
			cout << table[i];
		}
		cout << endl;
	}

	HashTable(const HashTable& H) {
	
		values = H.values;
		sequence = H.sequence;
	}

	HashTable(HashTable& H) {
		clear();
	
		for (int i = 0; i < H.sequence.size(); ++i) {
			add(H.sequence.at(i));
			sequence.push_back(H.sequence.at(i));
		}
	}

	//HashTable(HashTable&& H)
	//{
	//	values = H.values;
	//}

	~HashTable()
	{
		clear();
	}

	HashTable operator|(const HashTable& B) {
		HashTable C(*this);
		return C |= B;
	}

	HashTable& operator|=(const HashTable& B) {
		HashTable C(*this);

		for (int i = 0; i < B.sequence.size(); ++i) {
			if (find(C.sequence.begin(), C.sequence.end(), B.sequence.at(i)) == C.sequence.end()) {
				add(B.sequence.at(i));
				sequence.push_back(B.sequence.at(i));
			}
		}

		return *this;
	}

	HashTable operator&(const HashTable& B) {
		HashTable C(*this);
		return C &= B;
	}

	HashTable& operator&=(const HashTable& B) {
		for (int i = 0; i < sequence.size(); ++i) {
			if (find(B.sequence.begin(), B.sequence.end(), sequence.at(i)) == B.sequence.end()) {
				delete_element(sequence.at(i));
				sequence.erase(find(sequence.begin(), sequence.end(), sequence.at(i)));
				i--;
			}
		}
		return *this;
	}

	HashTable operator-(const HashTable& B)
	{
		HashTable C(*this);
		return C -= B;
	}

	HashTable& operator-=(const HashTable& B)
	{

		for (int i = 0; i < B.sequence.size(); ++i) {
			if (find(sequence.begin(), sequence.end(), B.sequence.at(i)) != sequence.end()) {
				delete_element(B.sequence.at(i));
				sequence.erase(find(sequence.begin(), sequence.end(), B.sequence.at(i)));
				i--;
			}
		}

		return *this;
	}

	HashTable operator+(const HashTable& B)
	{
		HashTable C(*this);
		return C += B;
	}

	HashTable& operator+=(const HashTable& B)
	{
		HashTable B1(B);
		HashTable C(*this - B);
		HashTable A(B1 - *this);
		//HashTable A1(*this);
		//HashTable B1(B);
		//A = A & B1;
		//B1 = B1 - A;
		//HashTable A1(C - B);
		//HashTable A2(B1 - A);
		//*this = A1|A2;
		//*this = *this | B;
		*this = C | A;

		return *this;
	}

	HashTable& operator=(const HashTable& H)
	{
		if (this != &H)
		{
			clear();

			values = H.values;
		}

		return *this;
	}

	HashTable& operator=(HashTable&& H)
	{
		if (this != &H)
		{
			clear();
			sequence = H.sequence;
			values = H.values;
		}

		return *this;
	}

	int operator[](int index) const
	{
		try
		{
			return index_operator(index);
		}
		catch (...)
		{
			throw;
		}
	}

	void concat(HashTable H)
	{
		for (int i = 0; i < H.size(); ++i)
			add(H[i]);
	}

	void mul(int n)
	{
		for (int i = 0; i < n; ++i)
			concat(*this);
	}

	void subst(HashTable H, int position) {
		*this | H;
		sequence.clear();
		
		for (int i = 0; i < H.sequence.size(); ++i) {	
			sequence.insert(sequence.begin() + position, H.sequence.at(i));
			position++;
		}
	}

	//void DisplayHashTable(HashTable& table)
	//{
	//	for (int i = 0; i < table.size(); ++i)
	//	{
	//		std::cout.width(3);
	//		std::cout << table[i];
	//	}
	//	std::cout << std::endl;
	//}

	void merge(HashTable A, HashTable B) {
		*this = A|B;
		sequence.clear();
		for (int i = 0; i < max(A.sequence.size(), B.sequence.size()); ++i) {
			if(i < A.sequence.size())
				sequence.push_back(A.sequence.at(i));
			if (i < B.sequence.size())
				sequence.push_back(B.sequence.at(i));

		}
		std::sort(sequence.begin(), sequence.end());
	}

	void excl(HashTable H)
	{
		int begin = 0;
		int start = 0;
		int finish = 0;

		while (start < size())
		{
			for (start = begin; start < size(); ++start)
				if (values[start] == H[0])
					break;

			if (start < size())
			{
				int next = 0;
				finish = start;

				do {
					next++;
					finish++;
				} while (next < H.size() && finish < size() && H[next] == values[finish]);

				begin = finish;

				if (next == H.size())
					for (int i = start; i < finish; ++i)
						delete_element(start);
			}
		}
	}
	
	void erase(int start, int end) {
		for (int i = start; i < end; ++i)
			delete_element(start);
	}


	void add(int value)
	{
		//cout << char(value + 97);
		values.insert(std::pair<int, char>(value, char(value + 97)));
	}


	int size() const
	{
		return int(values.size());
	}

	unordered_map<int, char>::const_iterator begin()
	{
		return values.begin();
	}

	unordered_map<int, char>::const_iterator end()
	{
		return values.end();
	}
};