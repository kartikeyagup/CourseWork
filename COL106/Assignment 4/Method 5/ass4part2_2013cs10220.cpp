#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	vector <string> store;
	vector <string> store1;
	for(int i=97;i<123;i++)
	{
		char v = i;
		store.push_back(string(1,v));
		store1.push_back(string(1,v));
	}
	for(int i=65;i<91;i++)
	{
		char v1 = i;
		store.push_back(string(1,v1));
		store1.push_back(string(1,v1));
	}
	store.push_back(" ");
	store.push_back(".");
	store1.push_back(" ");
	store1.push_back(".");
	ifstream file2;
	file2.open("compressed.txt");
	string line2;
	string readinitial;
	string read;
	getline(file2,line2);
	file2.close();
	istringstream fa(line2);
	ofstream file3;
	file3.open("mainoutput.txt");
	fa>>readinitial;
	string string1;
	file3 << store.at(atoi(readinitial.c_str()));
	string input = store.at(atoi(readinitial.c_str()));
	string character = input;
	int oldcode=(atoi(readinitial.c_str()));
	while(fa>>read)
	{
		int newcode=atoi(read.c_str());
		if(newcode>store.size()-1)
		{
			string1=store.at(oldcode);
			string1=string1+character;
		}
		else
			string1=store.at(newcode);
		file3 << string1;
		character=string(1,string1[0]);
		store.push_back(store.at(oldcode)+character);
		oldcode=newcode;	
	}
	file3.close();
	ifstream ofile("compressed.bin", ios::in | ios::binary);
	int a;
	string string2;
	ofile.read((char*)&a,sizeof(int));
	string character1=store1.at(a);
	ofstream file4;
	int oldcode1=a;
	int reading;
	file4.open("mainoutput2.txt");
	file4 << character1;
	while(ofile.read((char*)&reading,sizeof(int)))
	{
		int newcode1=reading;
		if(newcode1>store1.size()-1)
		{
			string2=store1.at(oldcode1);
			string2=string2+character1;
		}
		else 
		{
			string2=store1.at(newcode1);
		}
		file4 << string2;
		character1=string(1,string2[0]);
		store1.push_back(store1.at(oldcode1)+character1);
		oldcode1=newcode1;
	}
	ofile.close();
	file4.close();
}
