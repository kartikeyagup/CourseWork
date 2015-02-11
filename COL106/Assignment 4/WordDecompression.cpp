#include "WordDecompression.h"

string giveString(int key1, HashTable* hashed)
{
	return hashed->getKey(key1);
}

string mergeAll(vector<int> v, HashTable* hashed)
{
	string answer="";
	int limt=v.size();
	for (int i=0; i<limt; i++)
	{
		answer=answer+giveString(v[i],hashed);
	}
	return answer;
}

