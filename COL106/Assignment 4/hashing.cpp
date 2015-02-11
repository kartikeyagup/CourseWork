#include <iostream>
#include "hashing.h"

using namespace std;

int getCharValue(string s1,int post)
{
	// cout <<s1[post] <<"\n";
	int value= (int) s1[post];
	// cout <<value <<"\n";
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

long fastpower(int base,int num, long TableSize)
{
	long answer=1, counter=1, prod=base;
	while (num>0)
	{
		if (num%2==0)
		{
			num=num/2;
			prod*=prod;
			prod=prod % TableSize;
		}
		else
		{
			num-=1;
			answer*=prod;
			answer=answer%TableSize;
		}
	}
	// cout <<answer<<endl;
	return answer;
}

long getHashKey(string s1, long TableSize)
{
	//Make change here
	int limt=s1.length(),sumchar=0;
	for (int i=0; i<limt; i++)
	{
		sumchar+=fastpower(getCharValue(s1,i),i+1,TableSize);
	}
	return fastpower(sumchar,limt,TableSize);
}