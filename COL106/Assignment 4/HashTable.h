#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashing.h"
#include <string>
//#include <utility>

using namespace std;

class HashTable
{
	public:
		HashTable(long);
		bool isFull();
		long Find(string);
		long getSize();
		long Insert(string);
		string getKey(int);
	private:
		string* HashTableStored;
		long size;
		long TableSize;
};
// pair<string*,long> MakeHashTable(long);
// bool isFull(pair<string*,long>, long);
#endif