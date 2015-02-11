#include "HashTable.h"

string Characters [54]={" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","."};

HashTable::HashTable(long TableSize1)
{
	pair<string,int> *Table=new pair<string,int>[TableSize1];
	for (int i=0; i<TableSize1-1; i++)
	{
		if (i<=53)
			Table[i+1]=pair<string,int> (Characters[i],i);
		else
			Table[i+1]=pair<string,int> ("",0);
	}
	Table[0]=pair<string,int> ("",0);
	HashTableStored=Table;
	TableSize=TableSize1;
	size=54;
}

bool HashTable::isFull()
{
	return (this->size>=this->TableSize);
}

long HashTable::getSize()
{
	return this->size;
}

long HashTable::Find(string s1)
{
	long hashed=getHashKey(s1,TableSize),counter=hashed,step=1;
	bool sofar=false,done=false;
	while (!done && (step<TableSize))
	{
		if (this->HashTableStored[counter].first.compare(s1)==0)
		{
			sofar=true;
			done=true;
		}
		else if (this->HashTableStored[counter].first.compare("")==0)
		{
			sofar=false;
			done=true;
		}
		else
		{
			counter=(hashed +(step*step))%TableSize;
			step+=1;
		}

	}
	if (sofar)
		return counter;
	else
		return -1;
}

long HashTable::Find2(string s1)
{
	long hashed=getHashKey(s1,TableSize),counter=hashed,step=1;
	bool sofar=false,done=false;
	while (!done && (step<TableSize))
	{
		if (this->HashTableStored[counter].first.compare(s1)==0)
		{
			sofar=true;
			done=true;
		}
		else if (this->HashTableStored[counter].first.compare("")==0)
		{
			sofar=false;
			done=true;
		}
		else
		{
			counter=(hashed +(step*step))%TableSize;
			step+=1;
		}

	}
	if (sofar)
		return HashTableStored[counter].second;
	else
		return -1;
}



long HashTable::Insert(string s1)
{
	long hashed=getHashKey(s1,TableSize), step=1, counter= hashed;
	bool sofar=false,done=false;
	if (this->isFull())
		done=true;
	while (!done)
	{
		if (this->HashTableStored[counter].first.compare(s1)==0)
		{
			sofar=true;
			done=true;
		}
		else if (this->HashTableStored[counter].first.compare("")==0)
		{
			sofar=false;
			done=true;
			HashTableStored[counter]=pair<string,int> (s1,this->size+1);
			this->size+=1;
		}
		else
		{
			counter=(hashed +(step*step))%TableSize;
			step+=1;
		}
	}
	return counter;
}

string HashTable::getKey(int keyvalue)
{
	return HashTableStored[keyvalue].first;
}