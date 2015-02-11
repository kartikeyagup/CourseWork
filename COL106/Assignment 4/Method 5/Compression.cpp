#include "WordCompression.h"
#include "WordDecompression.h"
#include <fstream>

int getsize(int n)
{
	int j=0;
	while (n>0)
	{
		n=n/10;
		j+=1;
	}
	return j;
}


void CompressFile(char* input1, char* outputname1,char* outputname2)
{
	ifstream f;
	ofstream f1;
	ofstream f2;
	f.open(input1);
	// string ofile(outputname);
	f1.open(outputname1);
	f2.open(outputname2);
	string inp1;
	getline(f,inp1);
	cout <<"Input File Size: " <<inp1.length() <<" bytes\n";
	HashTable* hashed=Initialize(2101247);
	vector<int> hashed1=iterated(inp1,hashed);

	int limt=hashed1.size(),charsize=0, intsize=0;
	for (int c1=0; c1<limt; c1++)
	{
		string s=ASCIval(hashed1[c1]);
		// nsize+=2+int(log10(hashed1[c1]));
		f1<<hashed1[c1]<<" ";
		f2<<s;
		intsize+=1+getsize(hashed1[c1]);
		charsize+=1+s.length();
	}
	cout <<"Compressed File Size for int: " << intsize <<" bytes\n";
	cout <<"Compressed File Size for char: " << charsize <<" bytes\n";
	// cout <<inp1 <<endl;
}


int main(int a1, char **argv)
{
	cout <<"Starting the compression decompression program\n";
	cout <<"==============================================\n";
	cout << "\n"<<"input filename : " << argv[1];
	cout << "\n"<<"Compressed filename int: " << argv[2];
	cout << "\n"<<"Compressed filename char: " << argv[3] <<"\n\n";
	CompressFile(argv[1], argv[2], argv[3]);
	return 0;
}