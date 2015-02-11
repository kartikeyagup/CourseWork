#include "WordCompression.h"
#include "WordDecompression.h"
#include <fstream>


void CompressFile(char* input1, char* outputname)
{
	ifstream f;
	ofstream f1;
	ofstream f2;
	f.open(input1);
	f1.open(outputname);
	f2.open("dictionary.txt");
	string inp1;
	getline(f,inp1);
	HashTable* hashed=Initialize(2101247);
	vector<int> hashed1=iterated(inp1,hashed);
	for (int c2=0; c2<2101247; c2++)
	{
		f2<<c2<<"\t" <<hashed->getKey(c2)<<"\n" ;
	}
	int limt=hashed1.size();
	for (int c1=0; c1<limt; c1++)
	{
		f1<<hashed1[c1]<<" ";
	}
	// cout <<inp1 <<endl;
}


int main(int a1, char **argv)
{
	cout <<"Starting the compression decompression program\n";
	cout <<"==============================================\n";
	cout << "\n"<<"input filename : " << argv[1] <<"\n";
	cout << "\n"<<"Compressed filename : " << argv[2] <<"\n";
	CompressFile(argv[1], argv[2]);
	return 0;
}