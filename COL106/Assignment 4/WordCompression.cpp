#include "WordCompression.h"

HashTable* Initialize(long TableSize1)
{
	return new HashTable(TableSize1);
}

long getCode(string s1,HashTable* hashed)
{
	return hashed->Insert(s1);
}

int getBest(string s1,int position,HashTable* hashed)
{
	int i=1; bool done=false; long post=0;string stringcons=s1.substr(position,1); long limt=s1.length();
	while (!done and (position+i<=limt))
	{
		long present=hashed->Find(stringcons);
		// cout <<present<<"\n";
		if (present==-1)
		{
			done=true;
		}
		else
		{
			i+=1;
			post=present;
			stringcons=s1.substr(position,i);
		}
	}
	return i;
}

long InsertInHash(string s1,int position,int till,HashTable* hashed)
{
	//int longestlen=getBest(s1,position,hashed);
	long i1= getCode(s1.substr(position,till),hashed);
	return hashed->Find(s1.substr(position,till-1));
}

int mainStep(string s1,int position,HashTable* hashed)
{
	int best=getBest(s1,position,hashed);
	// cout << "best for " << position << "\t"<<best<< "implies inserting "<< s1.substr(position,best) << "\n";
	long x1= hashed->Insert(s1.substr(position,best));
	return position + best -1;
}

vector<int> iterated(string s1,HashTable* hashed)
{
	int posini=0,limt=s1.length();
	vector<int> answer1;
	while (posini<limt)
	{
		int new1= mainStep(s1,posini,hashed);
		// cout << s1.substr(posini,new1-posini)<<"\t"<<hashed->Find(s1.substr(posini,new1-posini)) <<"\n";
		answer1.push_back(hashed->Find(s1.substr(posini,new1-posini)));
		posini=new1;
	}
	return answer1;
}