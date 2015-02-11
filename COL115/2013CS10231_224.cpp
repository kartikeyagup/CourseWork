#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

pair<int*, int> givebinary(int x, int bits)
{
	int *ans= new int[bits];
	int sofar=0;
	for (int i=bits-1; i>=0; i--)
	{
		ans[i]=x%2;
		if (ans[i]==1)
		{
			sofar +=1;
		}
		x=x/2;
	}
	return (pair <int*, int> (ans,sofar));
}

int reducible(int *x1, int *x2, int bits)
{
	int sofar=0, position=-1;
	for (int co=0; co<bits;co++)
	{
		if (x1[co]!=x2[co])
		{
			sofar+=1;
			position=co;
		}
	}
	if (sofar==1)
		return position;
	else
		return -1;
}

vector<pair<int*, bool> >* splitterms(int* inputterms, int bits, int lenterms)
{
	vector<pair<int*,bool> > *bigans= new vector<pair<int*,bool> >[bits+1];
	for (int i=0; i<lenterms; i++)
	{
		pair<int*, int> pq= givebinary(inputterms[i],bits);
		bigans[pq.second].push_back ( pair <int*, bool> (pq.first, 0));
	}
	return bigans;	
}

pair <vector<pair<int*,bool> >*,vector<int*> > compareall(vector<pair<int*, bool> >* splittedform,vector<int*> zeroans, int bits)
{
	vector<pair<int*,bool> > *finalans= new vector<pair<int*,bool> >[bits+1];
	for (int i=0; i<bits ; i++)
	{
		if ((splittedform[i].size() !=0) && (splittedform[i+1].size() != 0))
		{
			vector<pair<int*, bool> > consideredterm1=splittedform[i];
			vector<pair<int*, bool> > consideredterm2=splittedform[i+1];
			int limt1=consideredterm1.size(), limt2= consideredterm2.size(),c1=0;
			while (c1<limt1)
			{
				pair<int*, bool> elem1=consideredterm1[c1];
				int c2=0;
				while (c2<limt2)
				{
					pair<int*, bool> elem2=consideredterm2[c2];
					int reduced= reducible(elem1.first,elem2.first,bits);
					if (reduced>=0)
					{
						splittedform[i][c1].second=1;
						splittedform[i+1][c2].second=1;
						int *num = new int[bits];
						for (int cou=0; cou<bits; cou++)
						{
							num[cou]=splittedform[i][c1].first[cou];
						}
						num[reduced]=-1;
						int lim3=finalans[i].size();
						int count1=0;
						bool sofar=1;
						while ((count1<lim3) && (sofar))
						{
							int *elemcons=finalans[i][count1].first;
							bool sofar1=1;
							int count2=0;
							while ((count2<bits) && (sofar1))
							{
								if (elemcons[count2]!=num[count2])
									sofar1=0;
								count2 +=1;
							}
							count1+=1;
							if (sofar1)
								sofar=0;
						}
						if (sofar)
						{
							finalans[i].push_back(pair <int*, bool> (num,0));
						}
					}
					c2+=1;
				}
				c1+=1;
			}
		}
	}
	for (int b12=0; b12<=bits; b12++)
	{
		int lim12=splittedform[b12].size();
		for (int x12=0; x12<lim12; x12++)
		{
			if (splittedform[b12][x12].second==0)
			{
				int limcons = zeroans.size() ;
				int count1=0;
				bool sofar=1;
				while ((count1<limcons) && (sofar))
				{
					bool sofar1=1;
					int count2=0;
					while ((count2<bits) && (sofar1))
					{
						if (zeroans[count1][count2] != splittedform[b12][x12].first[count2])
							sofar1=0;
						count2 +=1;
					}
					count1+=1;
					if (sofar1)
						sofar=0;
				}
				if (sofar)
				{
					zeroans.push_back(splittedform[b12][x12].first);
				}
			}
		}
	}
	return (pair<vector<pair<int*,bool> >*, vector<int*> > (finalans, zeroans)) ;
}

vector<int*> iteratestep1(int *arr,int bits, int len1)
{
	vector<pair<int*, bool> >* x1= splitterms(arr,bits, len1);
	vector<int*> zero1;
	pair <vector<pair<int*,bool> >*,vector<int*> > compared1ce=compareall(x1,zero1,bits);
	bool ending=0;
	while (ending==0)
	{

		int just=0;
		int l=0;
		while (just<=bits)
		{
			l+=compared1ce.first[just].size();
			just+=1;
		}
		if (l==0)
			ending=1;
		else
		{
			compared1ce=compareall(compared1ce.first,compared1ce.second,bits);
		}
	}
	return compared1ce.second;
}

int main()
{
	ifstream f;
	ofstream f1; 
	f.open("input.txt");
	f1.open("output.txt");
	string rand,inp,num,temp,reader;
        int number=0,size;
        vector<string> vec;
        getline(f,inp); f1<<inp<<endl;
       	{
 		istringstream kg(inp);
 		kg>>rand;
		kg>>size;
	}
	getline(f,inp); f1<<inp<<endl;
	getline(f,inp); f1<<inp<<endl;
	{
		istringstream kg(inp);	
		while(kg>>reader)
		{
			vec.push_back(reader);
			number++;
		}
	}
	getline(f,inp); f1<<inp<<endl;
	getline(f,inp); f1<<inp<<endl;
	{
		istringstream kg(inp);
		while(kg>>reader)
		{
			vec.push_back(reader);
			number++;
		}
	}
	int *problemstatement= new int[number];
	for (int abcd=0; abcd<number ; abcd++)
	{
		problemstatement[abcd]=atoi(vec[abcd].c_str());
	}
	f.close();
	//int * problemstatement1=new int[1024];
	//size=10;
	//number=1024;
	//for (int ko=0; ko<1024; ko++)
	//{
	//	problemstatement1[ko]=ko;
	//}
	vector<int*> iterated=iteratestep1(problemstatement,size,number);
	int numinp= iterated.size();
	f1<<".p "<<numinp<<endl;
	for (int final=0; final<numinp; final++)
	{
		for (int hk=0; hk<size; hk++)
		{
			if (iterated[final][hk]>=0)
				f1<<iterated[final][hk] ;
			else
				f1<<"-";
		}
		f1<<endl;
	}
	f1 <<".end";
	f1.close();
	return 0;
}
