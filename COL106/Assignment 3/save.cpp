#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<queue>
#include<string>
using namespace std;

int i=0;

struct node
{

	string name;
 	 int rank;
 	 int noofchildren;
 	 vector<node*> children;
 	 node* parent;
 	 int isroot;
};


 struct avlnode
 {
 	string name;
 	node* actual;
  avlnode* left, *right;
 	int ht;
 	int data;
 };

 class AVLtree
 {

 public:

 avlnode *root;

 AVLtree()
 {
 	root=NULL;
 }

 int height(avlnode *T)

 {
 	int LH,RH;
 	if(T==NULL)
 		return 0;
 	if(T->left==NULL)
 		LH=0;
 	else
 		LH=1+T->left->ht;
 	if(T->right==NULL)
 		RH=0;
 	else
 		RH=1+T->right->ht;
 	if(LH>RH)
 		return (LH);
 	else
 		return (RH);
 }

 avlnode *rotate_left(avlnode *x)

 {
 	avlnode *y;
 	y=x->right;
 	x->right=y->left;
 	y->left=x;
 	x->ht=height(x);
 	y->ht=height(y);
 	return(y);
 }

 avlnode *rotate_right(avlnode *x)

 {
 	avlnode *y;
 	y=x->left;
 	x->left=y->right;
 	y->right=x;
 	x->ht=height(x);
 	y->ht=height(y);
 	return(y);
 }
 int BF(avlnode *T)
 {

 	int LH,RH;

 	if(T==NULL)
 		return 0;
 	if(T->left==NULL)
 		LH=0;
 	else
 		LH=1+T->left->ht;
 	if(T->right==NULL)
 		RH=0;
 	else
 		RH=1+T->right->ht;
 	return(LH-RH);
 }

 avlnode *RR(avlnode *T)

 {
 	T=rotate_left(T);
 	return(T);
 }

 avlnode *LR(avlnode *T)

 {
 	T->left=rotate_left(T->left);
 	T=rotate_right(T);
 	return(T);
 }

 avlnode *RL(avlnode *T)

 {
 	T->right=rotate_right(T->right);
 	T=rotate_left(T);
 	return(T);
 }
 avlnode *LL(avlnode *T)

 {
 	T=rotate_right(T);
 	return(T);
 }

 avlnode *insert(avlnode *T,string x)
 {
 		
 	if(T==NULL)
 	{
 		T=new avlnode;
 		T->name=x;
 		T->left=NULL;
 		T->right=NULL;
 	}
 	else
 	{
 		if(x.compare(T->name))
 		{
 			T->right=insert(T->right,x);
 			if(BF(T)==-2)
 			{
 				if(x.compare((T->right)->name)>0)
 					T=RR(T);
 				else
 				 {
 				 	int LH,RH;
 				 	if(T==NULL)
 				 		return 0;
 				 	if(T->left==NULL)
 				 		LH=0;
 				 	else
 				 		LH=1+T->left->ht;
 				 	if(T->right==NULL)
 				 		RH=0;
 				 	else
 				 		RH=1+T->right->ht;
 				 }
 				T=RL(T);
 			}
 		}
 		else if(x.compare(T->name))
 		{
 			T->left=insert(T->left,x);
 			if(BF(T)==2)
 			{
 				if(x.compare((T->left)->name)<0)
 				T=LL(T);
 				else
 				T=LR(T);
 			}
 		}
 	}

 	T->ht=height(T);
 	return(T);
 }


 avlnode *delet(avlnode *T, string x)
 {
 	avlnode *p;
 	if(T==NULL)
 	return 0;
 	else
 	if(x.compare(T->name))
 	{
 		T->right=delet(T->right,x);
 		if(BF(T)==2)
 		if(BF(T->left)>=0)
 		T=LL(T);
 		else
 		T=LR(T);
 	}
 	else if(x.compare(T->name)<0)
 	{
 		T->left=delet(T->left,x);
 		if(BF(T)==-2)
 		if(BF(T->right)<=0)
 		T=RR(T);
 		else
 		T=RL(T);
 	}
 	else
 	{
 		if(T->right!=NULL)
 		{
 			p=T->right;
 			while(p->left!=NULL)
 			p=p->left;
 			T->name=p->name;
 			T->right=delet(T->right,p->name);
 			if(BF(T)==2)
 			if(BF(T->left)>=0)
 			T=LL(T);
 			else
 			T=LR(T);
 		}
 	else
 		return(T->left);
 	}

 	T->ht=height(T);
 	return(T);
 }


 int find(string s,avlnode*temp)
 {
 	if(s.compare(temp->name)==0)
 		return 0;
 	if(s.compare(temp->name)<0)
 		find(s,temp->left);
 	else
 		find(s,temp->right);
 }


 void preorder(avlnode *root)

 {
 	avlnode *T=root;
 	if(T!=NULL)
 	{
 		cout<<" \n"<<T->data<<" [BF= "<<BF(T)<<"]";
 		preorder(T->left);
 		preorder(T->right);
 	}
 }

 void inorder(avlnode *root)

 {
 	avlnode *T=root;
 	if(T!=NULL)
 	{
 		inorder(T->left);
 		cout<<" \n"<<T->data<<" [BF= "<<BF(T)<<"]";
 		inorder(T->right);
 	}
 }

 };

class tree
{
public:
	 int depth;
    node*root;
    int noofemployees;
    vector <avlnode> vec;

	tree(string boss)
   {
   	noofemployees=1;
   	depth=1;
   	root=new node;
   	root->name.assign(boss);
   	root->isroot=1;
   	root->rank=1;
    avlnode v;
   	v.name.assign(boss);
   	v.actual=root;
	vec.push_back(v);
   }



	void addemployee(string name,string boss)
    {

    		int check1=1;
			for (i=0;i<noofemployees;i++)
	       {

	       	if(name.compare(vec[i].name)==0)
	       		{
	       			cout<<" An employee with the name "<<name<<" already exists"<<endl;
	       			check1=0;
		       	}	
		 	}  

	   int check=0;
	   vector <avlnode>::iterator it;
	   i=0;
	   node*val;
	    for (i=0;i<noofemployees;i++)
	     {
	       	if(boss.compare(vec[i].name)==0)
	       		{
	       			val=vec[i].actual;
	       			check=1;
	       			break;
	       		}
		 }

	    if(check==0)
	    	cout<<"There is no employee with the name "<<boss<<endl;

	     else if(check1==1)
	    {
	    	 if(val->rank==depth)	depth+=1;
	    	 noofemployees++;

			 node*temp=new node;

			 temp->name.assign(name);
	    	 temp->parent=val;
	    	 temp->noofchildren=0;
	    	 temp->rank=(val->rank +1);
			 temp->isroot=0;
	    	 val->children.push_back(temp);
	    	 val->noofchildren++;


	    	 avlnode v;
	    	 v.name=temp->name;
	    	 v.actual=temp;

	    	 vec.push_back(v);

	    }
    }



    void deleteemployee(string emp,string newboss)
    {

	   int check1=0,check2=0;
	   i=0;
	   node*emp1;
	   node*emp2;
	   vector <avlnode>::iterator it;
	    for (i=0;i<noofemployees;i++)
	       {

	       	if(emp.compare(vec[i].name)==0)
	       		{
	       			emp1=vec[i].actual;
					check1=1;
	       		}

	       	if(newboss.compare(vec[i].name)==0)
	       		{
	       			emp2=vec[i].actual;
	       			check2=1;
	       		}
	       	}

		    if(check1==0)
	    	cout<<"There is no employee with the name "<<emp<<endl;

	    	else if(check2==0)
	    	cout<<"There is no employee with the name "<<newboss<<endl;

			else if((emp1->rank)!=(emp2->rank))
			{
				cout<<"The rank of the employees should be the same "<<endl;
			}

			else
			{
				//delete the employee from the vector

			for (i=0;i<noofemployees;i++)
			{
				if(emp.compare(vec[i].name)==0)
	       		{
	       			for(int j=i+1;j<noofemployees;j++)
	       				vec[j-1]=vec[j];

					noofemployees--;
					vec.resize(noofemployees);
					break;
	       		}
			}



				int j=emp2->noofchildren;

				for (i=0;i<emp1->noofchildren;i++)
	       		{
	       			(emp1->children[i])->parent=emp2;
					emp2->children.push_back(emp1->children[i]);
	       			(emp2->noofchildren)+=1;
	       		}




				emp1->noofchildren=0;
				emp1->parent->noofchildren--;
				node*parent=emp1->parent;
				i=0;
				while(1)
				{
					if((parent->children[i])==emp1)
					{
						(parent->children).erase((parent->children).begin()+i);
						delete emp1;
						break;
					}
					i++;
				}
			}

    }

    void commonboss(string emp,string newboss)
    {

	   int check1=0,check2=0;
	   i=0;
	   node*emp1;
	   node*emp2;
	   vector <avlnode>::iterator it;
	    for (it = vec.begin(); it != vec.end(); ++it,i++)
	       {

	       	if(emp.compare(vec[i].name)==0)
	       		{
	       			emp1=vec[i].actual;
					check1=1;

	       		}

	       	if(newboss.compare(vec[i].name)==0)
	       		{
	       			emp2=vec[i].actual;
	       			check2=1;

	       		}
	       	}

		    if(check1==0)
	    	cout<<"There is no employee with the name "<<emp<<endl;

	    	else if(check2==0)
	    	cout<<"There is no employee with the name "<<newboss<<endl;

			else
			{
				emp1=emp1->parent;
				emp2=emp2->parent;
				if((emp1->rank)>(emp2->rank))
				{
					while((emp2->rank)!=(emp1->rank))
					emp1=emp1->parent;
				}

				if((emp2->rank)>(emp1->rank))
				{
					while((emp2->rank)!=(emp1->rank))
					emp2=emp2->parent;
				}

				while((emp1->name).compare(emp2->name)!=0)
				{
					emp1=emp1->parent;
					emp2=emp2->parent;
				}

				cout<<"The common boss is "<<emp1->name<<endl;
			}
    }

    void display()
    {
    	queue<node*> q;
    	q.push(root);
    	int i;
    	int t=1;
    	while(!q.empty())
    	{
			node*temp=q.front();
			q.pop();
			// push all the children of temp in the queue

			for (i=0;i<temp->noofchildren; i++)
			{
				q.push(temp->children[i]);
			}
			if(temp->rank>t)
			{
				cout<<endl;
				t++;
			}
			cout<<temp->name<<" ";

	   	}

    }


};

int main()
{

	int choice;
    string ceo;
    cout<<"Enter the name of the highest ranked person in the company";
    getline(cin,ceo);
    tree t(ceo);
    string a,b;
  while(1)
  {

    cout<<endl<<"Enter your choice of operation:"<<endl;
    cout<<"Press 1 to add an employee "<<endl;
    cout<<"Press 2 to delete an existing employee "<<endl;
    cout<<"Press 3 to find the lowest common boss of two employees "<<endl;
    cout<<"Press 4 to print the names of all all employees in hierarchical order "<<endl;
    cout<<"press 5 to exit"<<endl;
    cin>>choice;

    if(choice==1)
    {
    	cout<<"enter the name of the new employee "<<endl;
    	cin>>a;
    	cout<<"enter the name of the boss "<<endl;
    	cin>>b;
    	t.addemployee(a,b);
    }

    else if(choice==2)
    {
    	cout<<"enter the employee to be deleted "<<endl;
    	cin>>a;
    	cout<<"enter the name of the new boss "<<endl;
    	cin>>b;
    	t.deleteemployee(a,b);
    }

    else if(choice==3)
    {
    	cout<<"enter the names of two employees whose common boss has to be found "<<endl;
    	cout<<"enter the name of the first employee "<<endl;
    	cin>>a;
    	cout<<"enter the name of second employee "<<endl;
    	cin>>b;
    	t.commonboss(a,b);
    }

    else if(choice==4)
    {
    	cout<<"displaying the employees of the office in hierarchical order "<<endl;
		t.display();
    }

    else if(choice==5)
    {
        break;
    }

    else
    {
        cout<<"Enter a valid number"<<endl;
    }
  }
	return 0;
}







