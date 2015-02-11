#ifndef WORDCOMPRESSION_H
#define WORDCOMPRESSION_H

#include "HashTable.h"
#include <vector>

HashTable* Initialize(long);
long getCode(string,HashTable*);
int getBest(string,int,HashTable*);
long InsertInHash(string,int,int, HashTable*);
int mainStep(string,int,HashTable*);
vector<int> iterated(string,HashTable*);
string ASCIval(int);


#endif