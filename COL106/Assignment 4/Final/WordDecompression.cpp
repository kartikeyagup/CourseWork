#include "WordDecompression.h"

// string Characters1 [54]={" ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","."};

string* initialize(int limt)
{
	string *a1=new string[limt];
	for (int i=0; i<limt;i++)
	{	
		if (i<256) 
		{
			char c12=i;
			string j(1,c12);
			a1[i]=j;
		}
		else
			a1[i]="";
	}
	return a1;
}

// string Decompress(vector<int> v1,int limt)
// {
// 	string* array1= initialize(limt);
// 	string final="";
// 	int limt12=v1.size(), old_code=v1[0],j=256, new_code;
// 	string character=array1[old_code], s1;
// 	final+=array1[old_code];
// 	for (int i=1; i<limt12;i++)
// 	{
// 		new_code=v1[i];
// 		if (array1[new_code].compare("")==0)
// 		{
// 			s1=array1[old_code];
// 			s1 +=character;
// 			// cout <<s1<<"\t"<<old_code<<"\t"<<new_code<<endl;
// 		}
// 		else
// 		{
// 			s1=array1[new_code];
// 		}
// 		final+=s1;
// 		character=s1[0];
// 		array1[j]=array1[old_code]+character;
// 		j+=1;
// 		old_code=new_code;
// 	}
// 	return final;
// }

string Decompress(vector<int> v1,int limt)
{
	vector<string> array1;
	for (int i=0;i<256;i++)
	{
		char c12=i;
		string j(1,c12);
		array1.push_back(j);
	}
	string final="";
	int limt12=v1.size(), old_code=v1[0], new_code;
	string character=array1[old_code], s1;
	final+=array1[old_code];
	for (int i=1; i<limt12;i++)
	{
		new_code=v1[i];
		if (new_code>=array1.size())
		{
			s1=array1[old_code];
			s1 +=character;
		}
		else
		{
			s1=array1[new_code];
		}
		final+=s1;
		character=s1[0];
		array1.push_back(array1[old_code]+character);
		old_code=new_code;
	}
	return final;
}