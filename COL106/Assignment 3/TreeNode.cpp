#include <iostream>
#include "TreeNode.h"
#include <queue>
#include <utility>
using namespace std;

TreeNode::TreeNode(string s)
{
	name=s;
	left=NULL;
	right=NULL;
	top=NULL;
	previouslevel=NULL;
	depth=0;
}

string TreeNode::getName()
{
	return name;
}

TreeNode* TreeNode::getRight()
{
	return this->right;
}

TreeNode* TreeNode::getLeft()
{
	return this->left;
}

TreeNode* TreeNode::getTop()
{
	return this->top;
}

TreeNode* TreeNode::getPrevious()
{
	return this->previouslevel;
}

vector<TreeNode*> TreeNode::getNextLevel()
{
	return this->nextlevel;
}

int TreeNode::getDepth()
{
	return this->depth;
}

int TreeNode::getLengthNext()
{
	return this->nextlevel.size();
}

TreeNode* TreeNode::findElement(string elem1)
{
	TreeNode* ans=NULL;
	if (this!=NULL)
	{
		int x= this->getName().compare(elem1);
		if (x==0)
		{
			ans=this;
		}
		else if (x>0)
		{
			ans=this->getRight()->findElement(elem1);
		}
		else
		{
			ans=this->getLeft()->findElement(elem1);
		}
		
	}
	return ans;
}

TreeNode* TreeNode::getRoot()
{
	TreeNode* current=this;
	while (current->getTop() !=NULL)
	{
		current=current->getTop();
	}
	return current;
}

void TreeNode::LLTreeRotation(TreeNode* point)
{
	TreeNode* x= point;
	TreeNode* y= point->getLeft();
	TreeNode* z= point->getLeft()->getLeft();
	TreeNode* w= point->getLeft()->getRight();
	if (x->getTop() != NULL)
	{
		if (x->top->right==x)
		{
			x->top->right=y;	
		}
		else
		{
			x->top->left=y;
		}
	}
	y->top=x->top;
	y->right=x;
	x->top=y;
	x->left=w;
	if (w!=NULL)
	{	
		w->top=x;
	}
}

void TreeNode::RRTreeRotation(TreeNode* point)
{
	TreeNode* x= point;
	TreeNode* y= point->getRight();
	TreeNode* z= point->getRight()->getRight();
	TreeNode* w= point->getRight()->getLeft();
	if (x->getTop() != NULL)
	{
		if (x->top->right==x)
		{
			x->top->right=y;	
		}
		else
		{
			x->top->left=y;
		}
	}
	y->top=x->top;
	y->left=x;
	x->top=y;
	x->right=w;
	if (w!=NULL)
	{
		w->top=x;
	}
}

void TreeNode::LRTreeRotation(TreeNode* point)
{
	TreeNode* x=point;
	TreeNode* y=point->getLeft();
	TreeNode* z=y->getRight();		
	TreeNode* p=z->getLeft();
	TreeNode* q=z->getRight();
	if (x->getTop() != NULL)
	{
		if (x->top->right==x)
		{
			x->top->right=z;	
		}
		else
		{
			x->top->left=z;
		}
	}
	z->left=y;
	z->right=x;
	z->top=x->getTop();
	x->top=z;
	x->left=q;
	if (q!=NULL)
	{
		q->top=x;
	}
	y->right=p;
	y->top=z;
	if (p!=NULL)
	{
		p->top=y;
	}
}

void TreeNode::RLTreeRotation(TreeNode* point)
{
	TreeNode* x=point;
	TreeNode* y=x->getRight();
	TreeNode* z=y->getLeft();		
	TreeNode* p=z->getRight();
	TreeNode* q=z->getLeft();
	if (x->getTop() != NULL)
	{
		if (x->top->right==x)
		{
			x->top->right=z;	
		}
		else
		{
			x->top->left=z;
		}
	}
	z->right=y;
	z->left=x;
	z->top=x->getTop();
	x->top=z;
	x->right=q;
	if (q!= NULL)
	{
		q->top=x;
	}
	y->left=p;
	y->top=z;
	if (p!=NULL)
	{
		p->top=y;
	}
}

int TreeNode::getHeight()
{
	if (this==NULL)	return 0;
	else return 1 + max(this->getLeft()->getHeight(), this->getRight()->getHeight());
}

int TreeNode::checkAVL(TreeNode* point)
{
	int ll=0,lr=0,rl=0,rr=0,l=0,r=0;
	if (point->getLeft()!=NULL)
	{
		ll=point->getLeft()->getLeft()->getHeight();
		lr=point->getLeft()->getRight()->getHeight();
		l=1+max(ll,lr);
	}
	if (point->getRight()!=NULL)
	{
		rl=point->getRight()->getLeft()->getHeight();
		r=1+max(rl,rr);
	}
	if (r-l>1)
	{
		if (rr>rl) return 2;
		else return 1;
	}
	else if (l-r>1)
	{
		if (ll>lr) return -2;
		else return -1;
	}
	else return 0;
}

void TreeNode::InsertElement(string employer,string employee)
{
	TreeNode* root=this->getRoot();
	TreeNode* employer1=root->findElement(employer);
	root=this->getRoot();
	if (employer1==NULL)
	{
		cout <<employer << " does not exist in the tree\n";
	}
	else
	{
		TreeNode* newpoint=new TreeNode(employee);
		bool sofar=false;
		bool inserted=true;
		while (!sofar)
		{
			int compared=root->getName().compare(employee);
			if (compared==0)
			{
				cout << employee << " already exists in the tree\n";
				sofar=true;
				inserted=false;
			}
			else if(compared<0)
			{
				if (root->getLeft()==NULL)
				{
					sofar=true;
					root->left=newpoint;
					newpoint->top=root;
				}
				else
				{
					root=root->getLeft();
				}
			}
			else
			{
				if (root->getRight()==NULL)
				{
					sofar=true;
					root->right=newpoint;
					newpoint->top=root;
				}
				else
				{
					root=root->getRight();
				}
			}
		}
		if (inserted)
		{
			newpoint->previouslevel=employer1;
			employer1->nextlevel.push_back(newpoint);
			newpoint->depth = 1 + employer1->getDepth();
		}
		bool done=false;
		TreeNode* considered=employer1;
		while (!done) //&& (!balancingneeded))
		{
			if (considered==NULL)
			{
				done=true;
			}
			else
			{
				int checked= checkAVL(considered);
				if (checked==0)
				{
					considered=considered->getTop();
				}
				else
				{
					if (checked==-2)
					{
						this->LLTreeRotation(considered);
					}
					else if (checked==-1)
					{
							this->LRTreeRotation(considered);
					}
					else if (checked==1)
					{
							this->RLTreeRotation(considered);
					}
					else
					{
						this->RRTreeRotation(considered);
					}
					done=true;
				}
			}	
		}
	}
}

void TreeNode::PrintEmployees()
{
	TreeNode* root1=this;
	while (root1->getPrevious() !=NULL)
	{
		root1=root1->getPrevious();
	}
	queue<TreeNode*> q1;
    q1.push(root1);
    int presentlevel=0;
    while (!q1.empty())
    {
        TreeNode* popped=q1.front();
        q1.pop();
        if (presentlevel<popped->getDepth())
        {
            cout<<"\n";
            presentlevel+=1;
        }
        cout <<popped->getName() <<"\t";
        for (int counter=0; counter<popped->getLengthNext(); counter++)
        {
            q1.push(popped->getNextLevel()[counter]);
        }
    }
    cout<<"\n";
}
string TreeNode::LowestCommonBoss(string emp1,string emp2)
{
	TreeNode *root=this->getRoot();
	TreeNode *empnode1=root->findElement(emp1);
	root=root->getRoot();
	TreeNode *empnode2=root->findElement(emp2);
	if (empnode1==NULL) cout << emp1 << " is not in the tree\n";
	if (empnode2==NULL)	cout << emp2 << " is not in the tree\n";
	if (empnode1==NULL || empnode2==NULL) return "Incorrect Input";
	else
	{
		//Reduce complexity
		vector<string> e1,e2;
        while (empnode1->getPrevious() !=NULL)
        {
            e1.push_back(empnode1->getPrevious()->getName());
            empnode1=empnode1->getPrevious();
        }   
        while (empnode2->getPrevious() !=NULL)
        {
            e2.push_back(empnode2->getPrevious()->getName());
            empnode2=empnode2->previouslevel;
        }   
        int lim1=e1.size();
        int counter1=lim1-1;
        int lim2=e2.size();
        int counter2=lim2-1;
        bool found1=false;
        while (not(found1) && (counter1>=0) && (counter2>=0))
        {
            if (e1[counter1] != e2[counter2])
            {
                found1=true;
            }
            else
            {
        	    counter1 -=1;
            	counter2 -=1;
        	}
        }
        return e1[counter1+1]; 
	}
}

TreeNode* TreeNode::getMaxLeft(TreeNode* p1)
{
	bool done=false;
	TreeNode* position1=p1;
	if (position1->getLeft()==NULL) done=true;
	else position1=position1->getLeft();
	while (!done)
	{
		if (position1->getRight()==NULL) done=true;
		else position1=position1->getRight();
	}
	return position1;
}

TreeNode* TreeNode::getMinRight(TreeNode* p1)
{
	bool done=false;
	TreeNode* position1=p1;
	if (position1->getRight()==NULL) done=true;
	else position1=position1->getRight();
	while (!done)
	{
		if (position1->getLeft()==NULL) done=true;
		else position1=position1->getLeft();
	}
	return position1;
}

TreeNode* TreeNode::DeleteEmployee(string deleteemp, string tomoveto)
{
	TreeNode* root=this->getRoot();
	TreeNode* positiondelete=root->findElement(deleteemp);
	root=this->getRoot();
	TreeNode* positionappend=root->findElement(tomoveto);
	TreeNode* final=this->getRoot();
	if (positiondelete==NULL) cout << deleteemp <<" is not in the tree\n";
	else if (positionappend==NULL) cout << tomoveto <<" is not in the tree\n";
	else if (positionappend->getDepth() != positiondelete->getDepth()) cout << "The 2 names are not on the same level\n"; 
	else
	{
		TreeNode* replace1=root->getMinRight(positiondelete);
		TreeNode* replace2=root->getMaxLeft(positiondelete);
		if (replace1!=NULL)
		{
			if (replace1->getTop()!=positiondelete)
			{
				replace1->getTop()->left=replace1->getRight();
				if (replace1->getRight()!=NULL) replace1->getRight()->top=replace1->getTop();
			}
			else
			{
				positiondelete->right=replace1->getRight();
				if (replace1->getRight()!=NULL) replace1->getRight()->top=replace1->getTop();
			}
			if (positiondelete->getTop()!=NULL)
			{
				if (positiondelete->getTop()->getLeft()==positiondelete) positiondelete->getTop()->left=replace1;
				else positiondelete->getTop()->right=replace1;
			}
			replace1->top=positiondelete->getTop();
			replace1->left=positiondelete->getLeft();
			replace1->right=positiondelete->getRight();
			if (replace1->getLeft()!=NULL) replace1->left->top=replace1;
			if (replace1->getRight()!=NULL) replace1->right->top=replace1;
			final=replace1;
		}
		else if(replace2!=NULL)
		{
			if (replace2->getTop()!=positiondelete)
			{
				replace2->getTop()->right=replace2->getLeft();
				if (replace2->getLeft()!=NULL) replace2->getLeft()->top=replace2->getTop();
			}
			else
			{
				positiondelete->left=replace2->getLeft();
				if (replace2->getLeft()!=NULL) replace2->getLeft()->top=replace2->getTop();
			}
			if (positiondelete->getTop()!=NULL)
			{
				if (positiondelete->getTop()->getLeft()==positiondelete) positiondelete->getTop()->left=replace2;
				else positiondelete->getTop()->right=replace2;
			}
			replace2->top=positiondelete->getTop();
			replace2->left=positiondelete->getLeft();
			replace2->right=positiondelete->getRight();
			if (replace2->getLeft()!=NULL) replace2->left->top=replace2;
			if (replace2->getRight()!=NULL) replace2->right->top=replace2;
			final=replace2;
		}
		// 	// cout << "hello2\n";
		// 	// Lots of changes here also
		// 	replace2->getTop()->right=replace2->getLeft();
		// 	replace2->getRight()->top=replace2->getTop();
		// 	if (positiondelete->getTop()!=NULL)
		// 	{	
		// 		if (positiondelete->getTop()->getLeft()==positiondelete) positiondelete->getTop()->left=replace2;
		// 		else positiondelete->getTop()->right=replace2;
		// 	}
		// 	replace2->top=positiondelete->getTop();
		// 	replace2->left=positiondelete->getLeft();
		// 	replace2->right=positiondelete->getRight();
		// 	if (replace2->getLeft()!=NULL) replace2->left->top=replace2;
		// 	if (replace2->getRight()!=NULL) replace2->right->top=replace2;
		// 	final=replace2;
		else
		{
			if (positiondelete->getTop()->getLeft()==positiondelete)
			{
				positiondelete->getTop()->left=NULL;
			}
			else positiondelete->getTop()->right=NULL;
			final=positiondelete->getTop();
		}
		// cout <<"Now moving elements" << positiondelete->getLengthNext()<<"\n";
		for (int i=0; i<positiondelete->getLengthNext();i++)
        {
        	positiondelete->nextlevel[i]->previouslevel=positionappend;
            positionappend->nextlevel.push_back(positiondelete->nextlevel[i]);
        }
        TreeNode* considered=positiondelete->getPrevious();
        // cout << "its boss had " << considered->getLengthNext() <<"\n";
        vector<TreeNode*> new1;
        for (int j=0; j<considered->getLengthNext(); j++)
        {
            if (considered->nextlevel[j]->getName() != deleteemp )
            {
                new1.push_back(considered->nextlevel[j]);
            }
        }
        considered->nextlevel=new1;
        // cout << "its boss has " << considered->getLengthNext() <<"\n";
        TreeNode* above;
        root=final->getRoot();
        // cout << root->getName() <<" is the name of the root\n";
        bool done2=false; int value1;
        while (!done2)
        {
        	// cout <<"checking for tree rotations\n";
        	above=final->getTop();
        	// cout << final->getName() <<" hello \n";
        	//final->PrintEmployees();
        	// cout <<"starting things\n";
        	value1=root->checkAVL(final);
        	//cout <<value1 <<"\n";
        	if (value1==-2) root->LLTreeRotation(final);
        	else if (value1==-1) root->LRTreeRotation(final);
        	else if (value1==1) root->RLTreeRotation(final);
        	else if (value1==2) root->RRTreeRotation(final);
        	if (above==NULL) done2=true;
        	else final=above;
        	// cout <<"done round 1\n";
        }
        // cout <<"bello\n";

	}
	// cout <<"getting out of it\n";
	return final;
}

void interface()
{
	int x=1;
	string CEOname, EmpBoss, NewEmp, DeleteEmp, DeleteTo, Emp1,Emp2;
	TreeNode* mainTree=new TreeNode(" ");
	while (x<6)
	{
		cout <<"Choose one of the following options: \n1 Crete new employee tree \n2 Add a new employee \n3 Remove an employee \n4 Print all Employess \n5 Get Lowest Common Boss \n6 Exit\n";
		cin >>x;
		if (x==1)
		{
			cout <<"Enter name of CEO: ";
			cin >> CEOname;
			mainTree=new TreeNode(CEOname);
		}
		else if (x==2)
		{
			cout <<"Enter Name of new Employee: ";
			cin >> NewEmp;
			cout <<"Enter Name of the person " <<NewEmp << " works under: ";
			cin >> EmpBoss;
			mainTree->InsertElement(EmpBoss, NewEmp);
		}
		else if (x==3)
		{
			cout <<"Enter Name of Employee to be deleted: ";
			cin >> DeleteEmp;
			cout <<"Enter Name of Employee under whom employees working under " <<DeleteEmp <<" have to be shifted to: ";
			cin >> DeleteTo;
			mainTree->DeleteEmployee(DeleteEmp, DeleteTo);
		}
		else if (x==4)
		{
			mainTree->PrintEmployees();
		}
		else if (x==5)
		{
			cout <<"Enter name of employee 1: ";
			cin >> Emp1;
			cout <<"Enter name of employee 2: ";
			cin >> Emp2;
			CEOname=mainTree->LowestCommonBoss(Emp1,Emp2);
			if (CEOname.compare("Incorrect Input")==0) cout <<"\n";
			else cout << CEOname <<" is the lowest common boss of " << Emp1 <<" and " << Emp2<<"\n";
		}
		else if (x==6)
		{
			cout <<"Exiting\n";
		}
		else
		{
			cout <<"Invalid input, Try again\n";
			x=1;
		}
	}
}

int main()
{
	// TreeNode* kg= new TreeNode("kartikeya");
	// // cout <<kg->getDepth() <<"\n";
	// kg->InsertElement("kartikeya","faran1");
	// // cout <<kg->getRoot()->getRight()->getName() <<" \t wowowowow \n";
	// kg->InsertElement("faran1","faran2");
	// // cout <<kg->getRoot()->getRight()->getName() <<" \t wowowowow \n";
	// kg->InsertElement("kartikeya","faran3");
	//  // cout <<kg->getRoot()->getName() <<" \t wowowowow \n";
	// kg->InsertElement("faran2","faran4");
	// // cout <<kg->getRoot()->getName() <<" \t wowowowow \n";
	// kg->InsertElement("faran3","faran5");
	// kg->InsertElement("faran5","faran8");
	// kg->InsertElement("faran5","faran7");
	// kg->InsertElement("faran3","faran6");
	// kg->InsertElement("faran7","faran10");
	// // cout <<"yellow\n";
	// kg->PrintEmployees();
	// // kg=kg->DeleteEmployee("faran3","faran1");
	// kg->InsertElement("kartikeya","faran9");
	// cout <<kg->LowestCommonBoss("faran10","faran6")<<"\n";
	// // kg->DeleteEmployee("faran1","faran9");
	// //cout <<"done deleting\n";
	// //cout <<kg->LowestCommonBoss("faran2","faran4") <<"\n";
	// // cout << kg->getLengthNext() <<"\n";
	// // cout << kg->getRight()->getHeight() <<"\n";
	// // cout << kg->checkAVL(kg) <<"\n";
	// kg->PrintEmployees();
	// cout <<"done printing\n";
	// string a="kartikeya";
	// string b="faran2";
	// string c="faran3";
	interface();
	//cout << b.compare(c) <<"\n";
	return 0;
}