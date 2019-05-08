#pragma once
//#include <map>
#include <list>
#include <unordered_map>
#include <iostream>
#include <algorithm>

//using std::map;
using std::unordered_map;
using std::list;
using std::find;
using std::advance;
using std::sort;


class HashTable
{
private:
	unordered_map<int, int> values;

	int hashfunc(int key) const
	{
		return key % 1000;
	}

	void clear()
	{
		values.clear();
	}

	int index_operator(int index) const
	{
		if (values.size() > index)
		{
			return values.at(index);
		}
		throw;
	}

	void delete_element(int index)
	{
		for (int i = index; i < size() - 1; ++i)
			values[i] = values[i + 1];

		values.erase(size() - 1);
	}

public:

	HashTable() {}

	HashTable(int size, int maxValue)
	{
		maxValue++;

		for (int i = 0; i < size; ++i)
			add(rand() % maxValue);
	}

	HashTable(const HashTable& H)
	{
		values = H.values;
	}

	HashTable(HashTable&& H)
	{
		values = H.values;
	}

	~HashTable()
	{
		clear();
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
		int start = 0;
		int k = 0;
		int prev_size = size();
		int val;
		
		//values.concat(H);
		for (int i = 0; i < H.size(); ++i)
			add(values[i]);
		//std::cout << size() << "!!!!!!!!!!!!!!!!!!";


		for (int i = position; i < prev_size + position/* + 1*/; ++i) {
			//val = values[i];
			values[i] = H.values[k];
			//values[i] = values[i + prev_size];
			//values[k + prev_size] = val;
			//values.insert(prev_size + k, val);
			//values.insert(i, H.values[k]);
			k++;
		}
		//values[0] = H.values[0];
		//int i = position;
		//for (int k = 0; k < H.size(); ++k) {
		//	//add(1);
		//	values.emplace(i, H.values[k]);
		//	i++;
		//}
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
		//std::cout << bothsize << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		//int indexA;
		//int indexB;
		//int minA;// = 999999999;
		//int minB;// = 999999999;
		int val;
		int sizeA = A.size();
		int sizeB = B.size();
		int bothsize = sizeA + sizeB;
		//std::cout << sizeA << sizeB << "!!!!!!!!!!!!!!!!!!!!!";
		//sort(A.values.cbegin(), A.values.cend());
		//sort(B.values.cbegin(), B.values.cend());
		for (int i = 0; i < sizeA - 1; ++i) {
			for (int j = 0; j < sizeA - i - 1; ++j) {
				if (A.values[j] > A.values[j + 1]) {
					val = A.values[j];
					A.values[j] = A.values[j + 1];
					A.values[j + 1] = val;
				}
			}
		}

		//DisplayHashTable(A);

		for (int i = 0; i < sizeB - 1; ++i) {
			for (int j = 0; j < sizeB - i - 1; ++j) {
				if (B.values[j] > B.values[j + 1]) {
					val = B.values[j];
					B.values[j] = B.values[j + 1];
					B.values[j + 1] = val;
				}
			}
		}

		//DisplayHashTable(B);

		int j = 0;
		int k = 0;

		for (int i = 0; i <= bothsize; ++i) {
			if (B.values[k] >= A.values[j] && j != sizeA) {
				add(A.values[j]);
				j++;
			}
			else if (k != sizeB) {
				add(B.values[k]);
				k++;
			}
		}
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
		values.insert(std::pair<int, int>(int(values.size()), value));
	}


	int size() const
	{
		return int(values.size());
	}

	unordered_map<int, int>::const_iterator begin()
	{
		return values.begin();
	}

	unordered_map<int, int>::const_iterator end()
	{
		return values.end();
	}
};