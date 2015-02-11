#include "HashTable.h"
#include <math.h>

// string Characters [54]={" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","."};

HashTable::HashTable(long TableSize1)
{
	pair<string,int> *Table=new pair<string,int>[TableSize1];
	for (int i=0; i<TableSize1-1; i++)
	{
		// cout <<i<<endl;
		if (i<=255)
		{
			char c1=i;
			string j(1,c1);
			Table[i]=pair<string,int> (j,i);
		}
		else
			Table[i]=pair<string,int> ("",0);
	}
	// Table[0]=pair<string,int> ("",0);
	HashTableStored=Table;
	TableSize=TableSize1;
	size=256;
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

bool checkprime(long in1)
{
	bool sofar=true;
	long i=2, limt= sqrt(in1);
	while (i<=limt && (sofar))
	{
		if (in1 % i==0)
			sofar=false;
		i+=1;
	}
	return sofar;
}

long getnextprime(long inp)
{
	bool done=false;
	if (inp%2==0)
		inp+=1;
	while (!done)
	{
		if (checkprime(inp))
			done=true;
		inp+=2;
	}
	return inp-2;
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
	// cout <<s1 <<"\n";
	if (this->isFull())
	{

		long t1=2*(this->TableSize);
		t1=getnextprime(t1);
		pair<string,int> *Table=new pair<string,int>[t1];
		cout <<"Rehashing done from " <<TableSize <<" to "<<t1<<endl;
		for (int i=0; i<t1;i++)
		{
			Table[i]=pair<string,int> ("",0);
		} 
		for (int i=0; i<TableSize; i++)
		{
			if (i<=255)
			{
				char c1=i;
				string j(1,c1);
				Table[i]=pair<string,int> (j,i);
			}
			else if (HashTableStored[i].first.compare("")!=0)
			{
				long value1=getHashKey(HashTableStored[i].first,t1);
				long post=value1, c1=1;
				bool done1=true;
				while (done1)
				{
					if (Table[post].first.compare("")==0)
					{
						done1=false;
						Table[post]=HashTableStored[i];
					}
					else
					{
						post=(value1 + c1*c1)%t1;
						c1+=1;
					}
				}
			}
		}
		HashTableStored=Table;
		TableSize=t1;
	}
	long hashed=getHashKey(s1,TableSize), step=1, counter= hashed;
	bool sofar=false,done=false;
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
			HashTableStored[counter]=pair<string,int> (s1,this->size);
			this->size+=1;
		}
		else
		{
			counter=(hashed +(step*step))%TableSize;
			step+=1;
		}

		if (step==TableSize && !done)
		{
			long t1=2*(this->TableSize);
			t1=getnextprime(t1);
			cout <<"Rehashing done from " <<TableSize <<" to "<<t1<<endl;
			pair<string,int> *Table=new pair<string,int>[t1];
			for (int i=0; i<t1;i++)
			{
				Table[i]=pair<string,int> ("",0);
			} 
			for (int i=0; i<TableSize; i++)
			{
				if (i<=255)
				{
					char c1=i;
					string j(1,c1);
					Table[i]=pair<string,int> (j,i);
				}
				else if (HashTableStored[i].first.compare("")!=0)
				{
					long value1=getHashKey(HashTableStored[i].first,t1);
					long post=value1, c1=1;
					bool done1=true;
					while (done1)
					{
						if (Table[post].first.compare("")==0)
						{
							done1=false;
							Table[post]=HashTableStored[i];
						}
						else
						{
							post=(value1 + c1*c1)%t1;
							c1+=1;
						}
					}
				}
			}
			HashTableStored=Table;
			TableSize=t1;

			hashed=getHashKey(s1,TableSize), step=1, counter= hashed;
		}
	}
	return counter;
}

string HashTable::getKey(int keyvalue)
{
	return HashTableStored[keyvalue].first;
}