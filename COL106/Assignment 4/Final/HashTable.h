#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashing.h"
#include <string>
#include <utility>

using namespace std;

class HashTable
{
	public:
		HashTable(long);
		bool isFull();
		long Find(string);
		long Find2(string);
		long getSize();
		long Insert(string);
		string getKey(int);
	private:
		pair<string,int> *HashTableStored;
		long size;
		long TableSize;
};


bool checkprime(long);
long getnextprime(long);
// pair<string*,long> MakeHashTable(long);
// bool isFull(pair<string*,long>, long);
#endif