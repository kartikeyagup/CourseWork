#include <iostream>
//#include <vector>
//#include <string>
#include "Node.h"
#include <queue>
#include <utility>
using namespace std;

//class Node
//{
    //private:
        //string name;
        //vector<Node*> *nextlevel;
        //int depth;

    //public:
        //Node();
        //Node(string);
        //vector<Node*>* getNext();
        //Node* getNextIth(int);
        //string getName();
        //void setName(string);
        //void addNext(Node*);
//};

Node::Node()
{
    name=" ";
    previouslevel=NULL;
    nextlevel = new  vector<Node*>;
    depth=-1;
}

Node::Node(string s1)
{
    name=s1;
    nextlevel=new vector<Node*>;
    previouslevel=NULL;
    depth=0;
}

vector<Node*>* Node::getNext()
{
    return nextlevel;
}

Node* Node::getNextIth(int i)
{
    return nextlevel[0][i];
}

string Node::getName()
{
    return name;
}

void Node::setName(string s1)
{
    name=s1;
}

void Node::setDepth(int l)
{
    depth=l;
}

void Node::setPreviousLevel(Node* boss)
{
    this->previouslevel=boss;
}

void Node::addNext(Node *n1)
{
    nextlevel[0].push_back(n1);
    n1->previouslevel=this;
    n1->setDepth(this->getDepth() +1);
}

int Node::getDepth()
{
    return depth;
}

int Node::getLengthLevel()
{
    return nextlevel[0].size();
}

pair<bool,Node*> Node::findElement(string elem1)
{
    bool sofar=false;
    bool done= false;
    Node* considered=NULL;
    while (not(sofar) && not(done))
    {
        if (this==NULL)
        {
            done=true;
        }
        else if (this->name==" ")
        {
            done=true;
        }
        else if (this->name==elem1)
        {
            sofar=true;
            considered=this;
        }
        else
        {
            int kart=0;
            // if (this->getLengthLevel()==0)
            // {
            //     done=true;
            // }
            while (not(sofar) && kart<this->getLengthLevel())
            {
                pair <bool,Node*> x1=this->nextlevel[0][kart]->findElement(elem1);
                // sofar=sofar || this->nextlevel[0][kart]->findElement(elem1).first;
                if (x1.first)
                {
                    sofar=true;
                    considered=x1.second;
                }
                kart+=1;
            }
            done=true;
        }
    }
    return pair<bool,Node*> (sofar,considered);
}

void Node::addElement(string employee,string employer)
{
    pair<bool, Node*> alpha= this->findElement(employer);
    // cout <<"found position for : " << employer <<"\n"; 
    if (alpha.first)
    {
        Node* emp=new Node(employee);
        alpha.second->addNext(emp);
    }
    else
    {
        cout <<"The employer: " << employer<<" does not exist in the tree.\n";
    }
}

void Node::displayNode()
{
    queue<Node*> q1;
    q1.push(this);
    int presentlevel=0;
    while (!q1.empty())
    {
        Node* popped=q1.front();
        q1.pop();
        if (presentlevel<popped->getDepth())
        {
            cout<<"\n";
            presentlevel+=1;
        }
        cout <<popped->getName() <<"\t";
        for (int counter=0; counter<popped->getLengthLevel(); counter++)
        {
            q1.push(popped->nextlevel[0][counter]);
        }
    }
    cout<<"\n";
}

string Node::findCommonBoss(string emp1, string emp2)
{
    pair<bool,Node*> position1=this->findElement(emp1);
    pair<bool,Node*> position2=this->findElement(emp2);
    if (position1.first && position2.first)
    {
        vector<string> e1,e2;
        Node* considered1=position1.second;
        while (considered1->previouslevel !=NULL)
        {
            e1.push_back(considered1->previouslevel->getName());
            considered1=considered1->previouslevel;
        }   
        e1.push_back(considered1->getName());
        // cout <<"done with e1\n";
        Node* considered2=position2.second;
        while (considered2->previouslevel !=NULL)
        {
            e2.push_back(considered2->previouslevel->getName());
            considered2=considered2->previouslevel;
        }   
        e2.push_back(considered2->getName());
        // cout << "done with e2\n";
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
            counter1 -=1;
            counter2 -=1;
        }
        return e1[counter1+1] + "\n"; 
    }
    else
    {
        if (!position1.first)
            cout << emp1 <<" is not in the tree\t";
        if (!position2.first)
            cout << emp2 <<" is not in the tree\t";
        return "Incorrect Case \n";
    
    }
    //return "abs";
}

void Node::deleteAndReplace(string toberemoved, string tobeattached)
{
    pair<bool, Node*> post1= this->findElement(toberemoved);
    pair<bool, Node*> post2= this->findElement(tobeattached);
    if ((post1.first) && (post2.first))
    {
        if (post1.second->getDepth()==post2.second->getDepth())
        {
               for (int i=0; i<post1.second->getLengthLevel();i++)
               {
                    post2.second->addNext(post1.second->getNext()[0][i]);
               }
               Node* considered=post1.second->previouslevel;
               vector<Node*> *new1= new vector<Node*>;
               int lim1= considered->getLengthLevel();
               int i=0;
               while (i<lim1)
               {
                    if (considered->nextlevel[0][i]->getName() != toberemoved )
                    {
                        new1[0].push_back(considered->nextlevel[0][i]);
                    }
                    i+=1;
               }
               considered->nextlevel=new1;
        }
        else
        {
            cout << "The level of employees entered is not same\n";
        }
    }
    else
    {
        if (!post1.first)
            cout << toberemoved << " does not exist in the tree\n";
        if (!post2.first)
            cout << tobeattached << " does not exist in the tree\n";
    }
}

int main()
{
    Node* pqr=new Node("kartikeya");
    pqr->addElement("faran","kartikeya");
    pqr->addElement("anupam", "kartikeya");
    pqr->addElement("jatin","faran");
    // cout <<"added jatin under faran\n";
    pqr->addElement("garvit","jatin");
    pqr->addElement("lakshay","jatin");
    pqr->addElement("ashish","kartikeya");
    pqr->addElement("rohan", "faran");
    pqr->displayNode();
    cout << "\n\n\n\n";
    // pqr->deleteAndReplace("jatin","rohan");
    pqr->displayNode();
    //cout << pqr->findCommonBoss("garvit","rohan");
    return 0;
}