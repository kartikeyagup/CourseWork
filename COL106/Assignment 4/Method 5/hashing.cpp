#include <iostream>
#include "hashing.h"

using namespace std;

int getCharValue(string s1,int post)
{
	int value= (int) s1[post];
	if ((value>=97) && (value <=123))
		return (value-95);
	else if ((value>=65) && (value<=90))
		return (value-37);
	else if (value==32)
		return 1;
	else if (value==46)
		return 54;
	else
		return -1;
}

long getHashKey(string s1, long TableSize)
{
	int limt=s1.length(),sumchar=0;
	for (int i=0; i<limt; i++)
	{
		sumchar=(55*sumchar+getCharValue(s1,i))%TableSize;
	}
	return sumchar;
}