#include "HashTable.h"

string Characters [54]={" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","."};

HashTable::HashTable(long TableSize1)
{
	string* Table=new string[TableSize1];
	for (int i=0; i<TableSize1-1; i++)
	{
		if (i<=53)
			Table[i+1]=Characters[i];
		else
			Table[i+1]="";
	}
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
	long hashed=getHashKey(s1,TableSize), counterorg= hashed, counter=hashed;
	bool sofar=false,done=false;
	hashed=1;
	while (!done)
	{
		cout <<s1 <<"\n";
		if (this->HashTableStored[counter].compare(s1)==0)
		{
			sofar=true;
			done=true;
		}
		else if (this->HashTableStored[counter].compare("")==0)
		{
			sofar=false;
			done=true;
		}
		else
		{
			counter=(counterorg +(hashed*hashed))%TableSize;
			hashed+=1;
		}

	}
	if (sofar)
		return counter;
	else
		return -1;
}

long HashTable::Insert(string s1)
{
	long hashed=getHashKey(s1,TableSize), counterorg=hashed, counter= hashed;
	bool sofar=false,done=false;
	hashed=1;
	if (this->isFull())
		done=true;
	while (!done)
	{
		if (this->HashTableStored[counter].compare(s1)==0)
		{
			sofar=true;
			done=true;
		}
		else if (this->HashTableStored[counter].compare("")==0)
		{
			sofar=false;
			done=true;
		}
		else
		{
			counter=(counterorg +(hashed*hashed))%TableSize;
			hashed+=1;
		}
	}
	HashTableStored[counter]=s1;
	if (!sofar)
		this->size+=1;
	return counter;
}

string HashTable::getKey(int keyvalue)
{
	return HashTableStored[keyvalue];
}