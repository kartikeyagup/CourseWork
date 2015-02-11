#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
long int hashing(string w,long int e)
{
	long int hash = 0;
	for (unsigned int i = 0; i < w.size(); i++)
	{
		hash = ((hash*33 + w[i]) % (e));
	}
	return hash;
}
bool primecheck(long int x)
{
	if((x % 2) == 0)
		return false;
	else 
	{
		int counter=0;
		long int _t=floor(sqrt(x));
		for (long int i=3;i<=_t;i+=2)
		{
			if ((x %_t)==0)
			{
				counter=counter+1;
				break;
			}
		}
		if(counter>0)
			return false;
		else 
			return true;
	}
}

long int nextprime(long int x)
{
	if(primecheck(x))
		return x;
	else
	{
		if((x % 2)==0)
		{
			x=x+1;
			nextprime(x+2);
		}
		else
		{		
			nextprime(x+2);
		}
	}
}

ostream& binary_write(ostream& stream, const int& value)
{
   	return stream.write(reinterpret_cast<const char*>(&value), sizeof(int));
}

struct node
{
	node();
	string value;
	int code;
};
class hashtable
{
public:
	hashtable(long int m);
	void insert(string s,int code1);
	bool search(string y);
	long int find(string t);
	node *findnode(string t);
	long int size1;
	vector <node *> dictionary;
};
node::node()
{
	value="&";
}
hashtable::hashtable(long int m)
{
	for (unsigned long int i = 0; i < m; i++)
	{
		node *a = new node();
		dictionary.push_back(a);
	}
	size1=m;
}

void hashtable::insert(string s,int code1)
{
	long int t = hashing(s, size1);
	int count = 0;
	long int num=t;
	while (dictionary.at(num)->value.compare("&")!=0)
	{
		num = (t + (count*count)) % (size1);
		count++;
	}
	dictionary.at(num)->value = s;
	dictionary.at(num)->code = code1;
}

bool hashtable::search(string y)
{
	long int num = hashing(y, size1);
	if (dictionary.at(num)->value.compare(y)==0)
		return true;
	else if (dictionary.at(num)->value.compare("&")==0)
		return false;
	else
	{

		int keep = 0;
		long int counter = 1;
		long int dt=num;
		while (dictionary.at(dt)->value.compare("&")!=0)
		{
			dt = (num + (counter*counter)) % (size1);
			counter = counter+1;
			if (dictionary.at(dt)->value.compare(y)==0)
			{
				keep += 1;
				break;
			}
		}
		if (keep >0)
		{
			return true;
		}
		else
			return false;
	}
}

long int hashtable::find(string t)
{
	long int num = hashing(t, size1);
	long int dt1=num; 
	if (dictionary.at(num)->value.compare(t)==0)
		return num;
	else
	{
		int counter = 0;
		while (dictionary.at(dt1)->value.compare("&")!=0)
		{
			dt1 = (num + (counter*counter)) % (size1);
			counter = counter+1;
			if (dictionary.at(dt1)->value.compare(t)==0)
			{
				return dt1;
				break;
			}
		}
	}
}
node *hashtable::findnode(string t)
{
	long int num = hashing(t, size1);
	long int dt1=num; 
	if (dictionary.at(num)->value.compare(t)==0)
		return dictionary.at(num);
	else
	{
		int counter = 0;
		while (dictionary.at(dt1)->value.compare("&")!=0)
		{
			dt1 = (num + (counter*counter)) % (size1);
			counter = counter+1;
			if (dictionary.at(dt1)->value.compare(t)==0)
			{
				return dictionary.at(dt1);
				break;
			}
		}
	}
}



int main(int a1, char **args)
{
	if(a1>1)
	{
		ifstream file;
		file.open(args[1]);
		if(file.is_open())
		{
			string line;
			char ch = EOF;
			getline(file, line , ch);
			long int y=line.size();
			file.close();
			hashtable *xyz = new hashtable(nextprime(y)+54);
			int index=0;
			for(int i=97;i<123;i++)
			{
				char v1= i;
				xyz->insert(string(1,v1),index);
				index++;
			}
			for(int i=65;i<91;i++)
			{
				char v= i;
				xyz->insert(string(1,v),index);
				index++;
			}
			xyz->insert(" ",index);
			xyz->insert(".",index+1);
				ofstream stream("compressed.bin",ios::binary);
				ofstream ofile;
				ofile.open("compressed.txt");
				string input = string(1, line[0]);
				int index1=54;
				for (long int i = 1; i < line.size(); i++)
				{
					if((line[i]>='a' && line[i]<='z') || (line[i]>='A' && line[i]<='Z') || line[i] == '.' || line[i] == ' ')
					{
						if (xyz->search(input + line[i]) == true)
						{
							input = input + line[i];
						}
						else
						{
							node *dc=xyz->findnode(input);
							ofile << dc->code<<" ";
							binary_write(stream, xyz->findnode(input)->code); 
							xyz->insert(input + line[i],index1);
							index1++;
							input = string(1,line[i]);
						}
					}
				}	
				ofile<<xyz->findnode(input)->code;
				binary_write(stream, xyz->findnode(input)->code);
				ofile.close();
				stream.close();
				cout<<"Compression executed"<<endl;
		}
		else
		{
			cout<<"Input file not found"<<endl;
		}
	}
	else
	{
		cout<<"Please specify an input file"<<endl;
	}
}
