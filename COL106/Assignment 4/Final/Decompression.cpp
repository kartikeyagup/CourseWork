#include "WordDecompression.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(int arv1, char** args)
{
	cout <<"Starting Decompression:\n";
	cout <<"=======================\n";
	ifstream f;
	ofstream f1;
	f.open(args[1]);
	string inp1;
	getline(f,inp1);
	f1.open(args[2]);
	getline(f,inp1);
	f.close();
	istringstream kg(inp1	);
	int readvalue;
	vector<int> answer1;
	while (kg>>readvalue)
	{
		answer1.push_back(readvalue);
	}
	string finans=Decompress(answer1,2101247);
	f1 <<finans;
	cout <<"Compressed File Name: "<<args[1]<<endl;
	cout <<"Decompressed File Name: "<<args[2]<<endl;
	return 0;
}