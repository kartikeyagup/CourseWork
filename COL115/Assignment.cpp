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
	//pair <int*, int> pr1 (ans,sofar);
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
//	vector<int*> *zeroans= new vector<int*>;
	for (int i=0; i<bits ; i++)
	{
		//cout <<"started1stloop\n";
		if ((splittedform[i].size() !=0) && (splittedform[i+1].size() != 0))
		{
			vector<pair<int*, bool> > consideredterm1=splittedform[i];
			vector<pair<int*, bool> > consideredterm2=splittedform[i+1];
			int limt1=consideredterm1.size(), limt2= consideredterm2.size(),c1=0;
			while (c1<limt1)
			{
				//int counter1=0;
				pair<int*, bool> elem1=consideredterm1[c1];
				int c2=0;
				while (c2<limt2)
				{
					pair<int*, bool> elem2=consideredterm2[c2];
					int reduced= reducible(elem1.first,elem2.first,bits);
					if (reduced>=0)
					{
						//counter1+=1;
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
				// fix the zeroterms part below, scope is wrong
				//if  (splittedform[i][c1].second==0)
				//{
				//	int limcons = zeroans.size() ;
				//	for (int pqr=0; pqr<limcons; pqr++)
				//	{
				//		int count1=0;
				//		bool sofar=1;
				//		while ((count1<limcons) && (sofar))
				//		{
				//			//int *elemcons=zeroans[count1];
				//			bool sofar1=1;
				//			int count2=0;
				//			while ((count2<bits) && (sofar1))
				//			{
				//				if (zeroans[count1][count2] != elem1.first[count2])
				//					sofar1=0;
				//				count2 +=1;
				//			}
				//			count1+=1;
				//			if (sofar1)
				//				sofar=0;
				//		}
				//		if (sofar)
				//		{
				//			zeroans.push_back(splittedform[i][c1].first);
				//		}
				//	}
				//}
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
				//for (int pqr=0; pqr<limcons; pqr++)
				int count1=0;
				bool sofar=1;
				while ((count1<limcons) && (sofar))
				{
					//int *elemcons=zeroans[count1];
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

		//bool s1=0;
		int just=0;
		int l=0;
		while (just<=bits)
		{
			l+=compared1ce.first[just].size();
			//if (compared1ce.first[just].size()!=0)
			//	s1=0;
			just+=1;
		}
		if (l==0)
			ending=1;
		else
		{
			compared1ce=compareall(compared1ce.first,compared1ce.second,bits);
		}
		//cout <<compared1ce.second.size() <<"\t" << l << "\n";
	}
	return compared1ce.second;
}

vector<int*> steptwo(vector<int*> primeimp,int* minterms, int bits, int numterms)
{
	int numimp=primeimp.size();
	bool *mintermcheck= new bool[numterms];
	bool *primeimpcheck=new bool[numimp];
	for (int i=0; i<numterms; i++)
	{
		mintermcheck[i]=0;
	}
	for (int i=0; i<numimp; i++)
	{
		primeimpcheck[i]=0;
	}
	bool **bigtickarray=new bool*[numimp];
	for (int i=0; i<numimp; i++)
	{
		bigtickarray[i]=new bool[numterms];
		for (int j=0; j<numterms; j++)
		{
			bigtickarray[i][j]=0;
		}
	}
	for (int i=0; i<numterms;i++)
	{
		int* converted=givebinary(minterms[i],bits).first;
		for (int j=0; j<numimp; j++)
		{
			bool sofar1=1;
			int count12=0;
			while (sofar1 && (count12<bits))
			{
				if ((primeimp[j][count12]!=converted[count12]) && (primeimp[j][count12]>=0))
				{
					sofar1=0;
				}
				count12+=1;
			}
			if (sofar1)
				bigtickarray[j][i]=1;
		}
	}
	for (int i=0; i<numterms; i++)
	{
		if (mintermcheck[i]==0)
		{
			int sofar=0, counter1=0,post=0;
			while (sofar<=1 && counter1<numimp)
			{
				if (bigtickarray[counter1][i])
				{
					sofar+=1;
					post=counter1;
				}
				counter1+=1;
			}
			if (sofar==1)
			{
				//mintermcheck[i]=1;
				primeimpcheck[counter1]=1;
				for (int xyz1=0; xyz1<numterms; xyz1++)
				{
					if (bigtickarray[counter1][xyz1])
						mintermcheck[xyz1]=1;
				}
			}
		}
	}
	bool doneornot=1;
	int c123=0;
	while (c123<numterms && doneornot)
	{
		doneornot=mintermcheck[c123];
		c123 +=1;
	}
	while (doneornot ==0)
	{
		//get best tick it and move on
		
		doneornot=1;
		c123=0;
		while (c123<numterms && doneornot)
		{
			doneornot=mintermcheck[c123];
			c123 +=1;
		}
	}
	return primeimp;
}


int main()
{
	//int d;
	ifstream f;
	ofstream f1; 
	f.open("input.txt");
	f1.open("output.txt");
	string rand,inp,num,temp,reader;
        int number=0,size;
        vector<string> vec;
        getline(f,inp); f1<<inp<<endl;
       	{
 		istringstream kc(inp);
 		kc>>rand;
		kc>>size;
	}
	//cout<<size<<endl;
	getline(f,inp); f1<<inp<<endl;
	getline(f,inp); f1<<inp<<endl;
	{
		istringstream kc(inp);	
		while(kc>>reader)
		{
			vec.push_back(reader);
			number++;
		}
	}
	getline(f,inp); f1<<inp<<endl;
	getline(f,inp); f1<<inp<<endl;
	{
		istringstream kc(inp);
		while(kc>>reader)
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
 	//cout <<problemstatement[0] << " size is\n";
	//pair <int*, int> p1=givebinary(5,4);
	//pair <int*, int> p2=givebinary(7,4);
	//pair <int*, int> p3=givebinary(15,4);
	//int terms[7]={0,1,2,3,7,12,15};
	//int * x1=terms;
	//vector<int*> zero2;
	//vector<pair<int*, bool> >* abc=splitterms(x1,4,7);
	//cout <<abc[4].size()<<"\n";
	//cout <<abc[1][0].first[2]<<"\n";
	//cout <<compareall(abc,zero2,4).first[4].size()<<"this was the size\n";
	//pair <vector<pair<int*,bool> >*,vector<int*> > compared1ce=compareall(abc,zero2,4);
	//compared1ce=compareall(compared1ce.first, compared1ce.second,4);
	//compared1ce=compareall(compared1ce.first, compared1ce.second,4);
	//cout << compareall(compared1ce.first,compared1ce.second, 4).first[4].size() <<"this was 2nd size\n"; 
	//int * problemstatement1= new int[512];
	//for (int pq1=0; pq1<512; pq1++)
	//{
	//	problemstatement1[pq1]=pq1;
	//}
	//size=9;
	//number=512;
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
	//cout << reducible(p1.first,p3.first,4) << "\n";
	//cout << reducible(p1.first,p2.first,4) << "\n";
	//cout << reducible(p3.first,p2.first,4) << "\n";
	//p2.second=10;
	//cout <<p2.second<<"\t"; 
	//cin >>d;
	return 0;
}
