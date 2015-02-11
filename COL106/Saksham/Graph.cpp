#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <stack>
#include "FacebookVertex.h"


#define INT_MAX 32767

using namespace std;

struct node
{
	int distance;
	Vertex* ver;
	int aindex;
};

class priorityqueue
{
private:
	int index;
	int capacity;
	node* myarray;
	node** arrayn;


public:

priorityqueue()
{
	capacity=2000;
	index=0;
	myarray = new node[2000];
	node** arrayn=new node*[2000];
	//arrayn->resize(2000);
}

void push(Vertex* val)
{cout<<"starting push\n";
	if(index==capacity)
    {
	cout <<"In if\n";
        capacity=2*capacity;
        node* myarray2;
        myarray2=new node[capacity];
        for(int j=1;j<=index;j++)
        {
            myarray2[j]=myarray[j];
        }
        myarray=myarray2;
	cout <<"Out if\n";
    }
	cout <<"Out of here\n";
    myarray[index+1].ver= val;
    myarray[index+1].distance = INT_MAX;
    	cout <<"blah\n";
	myarray[index+1].aindex=index+1;
	cout <<"blah2\n";
	cout <<val->getVertexNumber()<<"\t"<<index+1<<"\n";
	node* x1=&myarray[index+1];
	cout <<"here as well\n";	
	   arrayn[val->getVertexNumber()]= &myarray[index+1];
    index++;
    	cout <<"Here\n";
	int temp1=index;
    while( myarray[temp1].distance > myarray[temp1/2].distance && (temp1/2 >= 1))
    {
	cout <<"In while\n";
        node temp;
        temp=myarray[temp1/2];
        myarray[temp1/2]=myarray[temp1];
        myarray[temp1]=temp;
        myarray[temp1].aindex=temp1;
        myarray[temp1/2].aindex=temp1/2;
        arrayn[temp.ver->getVertexNumber()]= &myarray[temp1];
        arrayn[myarray[temp1/2].ver->getVertexNumber()]= &myarray[temp1/2];
        temp1=temp1/2;
	cout <<"Out while\n";
    }
}

node top()
{
	if(index==0)
    {
        throw "Empty Priority Queue" ;
    }
	else
    {
       return(myarray[1]);
    }
}

bool empty()
{
	return(index==0);
}

int size()
{
	return (index);
}

void pop()
{
	if(index==0)
    {
       throw "Empty Priority Queue";
    }

	else if(index==1)
    {
        index--;
    }
    else
    {
        myarray[1]=myarray[index];
        index=index-1;
        int temp2=1;
        int tem;
        node tem1;

        while(1)
        {
            if(index<2*temp2)
            {
                break;
            }

            if(index==2*temp2)
            {
                if(myarray[temp2].distance > myarray[index].distance)
                {
                    tem1=myarray[temp2];
                    myarray[temp2]=myarray[index];
                    myarray[index]=tem1;
                    myarray[temp2].aindex=temp2;
                    myarray[index].aindex=index;
                    arrayn[myarray[temp2].ver->getVertexNumber()]= &myarray[temp2];
                    arrayn[myarray[index].ver->getVertexNumber()]= &myarray[index];

                
                }
                break;
            }

            if(index>2*temp2)
            {
                if(myarray[2*temp2].distance > myarray[2*temp2+1].distance)
                {
                    tem=2*temp2+1;
                }
                else
                {
                    tem=2*temp2;
                }

                if(myarray[temp2].distance > myarray[tem].distance)
                {
                    tem1=myarray[temp2];
                    myarray[temp2]=myarray[tem];
                    myarray[tem]=tem1;
                    myarray[tem].aindex=tem;
                    myarray[temp2].aindex=temp2;
                    arrayn[myarray[temp2].ver->getVertexNumber()]= &myarray[temp2];
                    arrayn[myarray[tem].ver->getVertexNumber()]= &myarray[tem];
                    temp2=tem;
                }
                else
                {
                    break;
                }
            }
        }
    }

}

void decreaseMin(Vertex* x,int s)
{
	node* ptr1;
	int per;
	ptr1=arrayn[x->getVertexNumber()];
	ptr1->distance=s;
	per=ptr1->aindex;
	
	while(myarray[per].distance < myarray[per/2].distance && (per/2>=1))
	{
		node ptrr;
		ptrr = myarray[per];
		myarray[per]=myarray[per/2];
		myarray[per/2]=ptrr;
		myarray[per].aindex=per;
		myarray[per/2].aindex=per/2;
		per=per/2;
	}

}

int distance(Vertex* c)
{
	node* store;
	store=arrayn[c->getVertexNumber()];
	return(store->distance);
}

};


Vertex::Vertex()
{
	vertex_number = -1;
}

Vertex::Vertex(int vertex_no)
{
	vertex_number = vertex_no;
}

int Vertex::getVertexNumber()
{
	return vertex_number;
}

void Vertex::setVertexNumber(int vertex_no)
{
	vertex_number = vertex_no;
}

string Vertex::toString()
{
	string str;
	str.append("V(");
	char buf[33];
	snprintf(buf, sizeof(buf), "%d", vertex_number);
	str.append(buf);
	str.append(")");
	return str;
}



Edge::Edge(Vertex* src, Vertex* dest)
{
	source = src;
	destination = dest;
	directed = false;
	weight = 0;
}

Edge::Edge(Vertex* src, Vertex* dest, bool isDir, int wt)
{
	source = src;
	destination = dest;
	directed = isDir;
	weight = wt;
}

Vertex* Edge::getSource()
{
	return source;
}

Vertex* Edge::getDestination()
{
	return destination;
}

bool Edge::isDirected()
{
	return directed;
}

int Edge::getWeight()
{
	return weight;
}

string Edge::toString()
{
	string str;
	str.append("source : ");
	str.append(source->toString());
	str.append("\n");
	str.append("destination : ");
	str.append(destination->toString());
	str.append("\n");
	str.append("weight : ");
	char buf[33];
	snprintf(buf, sizeof(buf), "%d", weight);
	str.append(buf);
	str.append("\n");
	if(directed == true)
	{
		str.append("isDirected : true\n");
	}
	if(directed == false)
	{
		str.append("isDirected : false\n");
	}
	return str;
}

/*void Edge::setRefs(int r)
{
	refs = r;
}

int Edge::getRefs()
{
	return refs;
}*/


Graph::Graph()
{
	vertexList = new vector<Vertex*>();
	adjacencyList = new map<Vertex*, vector<Edge*>* > ();
	directed = false;
//	num_vertices = 0;
}

Graph::Graph(bool isDir, bool isWeighted)
{
	vertexList = new vector<Vertex*>();
	adjacencyList = new map<Vertex*, vector<Edge*>* > ();
	directed = isDir;
	weighted = isWeighted;
//	num_vertices = 0;
}

Graph::~Graph()
{
	clearEdges();
	clear();
}

void Graph::addVertex(Vertex* v)
{
	if(v->getVertexNumber() == -1)
	{
		v->setVertexNumber(new_vertex_ID++);
	}
//	num_vertices++;
	vertexList->push_back(v);
	vector<Edge*> * v_edge_list = new vector<Edge*>();
	adjacencyList->insert(pair<Vertex*, vector<Edge*> *>(v, v_edge_list));
}

void Graph::addEdge(Vertex* src, Vertex* dest)
{
	if(containsVertex(src) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << src->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsVertex(dest) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << dest->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsEdge(src, dest) == true)
	{
		return;
	}
	Edge* new_edge = new Edge(src, dest);
	adjacencyList->at(src)->push_back(new_edge);
	adjacencyList->at(dest)->push_back(new_edge);
//	new_edge->setRefs(2);
}

void Graph::addEdge(Vertex* src, Vertex* dest, int wt)
{
	if(containsVertex(src) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << src->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsVertex(dest) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << dest->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsEdge(src, dest) == true)
	{
		return;
	}
	Edge* new_edge = new Edge(src, dest, false, wt);
	adjacencyList->at(src)->push_back(new_edge);
	adjacencyList->at(dest)->push_back(new_edge);
//	new_edge->setRefs(2);
}

void Graph::addEdge(Vertex* src, Vertex* dest, int wt, bool isDir)
{
	if(containsVertex(src) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << src->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsVertex(dest) == false)
	{
		cout << "Graph::addEdge(Vertex* src, Vertex* dest)" << endl;
		cout << "no such vertex = " << dest->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsEdge(src, dest) == true)
	{
		return;
	}
	Edge* new_edge = new Edge(src, dest, isDir, wt);
	adjacencyList->at(src)->push_back(new_edge);
//	new_edge->setRefs(1);
	if(isDir == false)
	{
		adjacencyList->at(dest)->push_back(new_edge);
//		new_edge->setRefs(1);
	}
}

void Graph::clear()
{
	while(vertexList->empty() == false)
	{
		Vertex* v = vertexList->at(0);
		removeVertex(v);
		delete(v);
	}
//	num_vertices = 0;
}

void Graph::clearEdges()
{
	for(int i = 0; i < vertexList->size(); i++)
	{
		Vertex* v = vertexList->at(i);
		int j = adjacencyList->at(v)->size()-1;
		while(adjacencyList->at(v)->empty() == false)
		{
//			cout << j << ") ";
			Edge * e = adjacencyList->at(v)->at(j);
//			cout << "deleting : " << e->toString() << endl;
/*			adjacencyList->at(i)->pop_back();
			if(e->getRefs() == 1)
			{
				delete(e);
			}
			else
			{
				e->setRefs(e->getRefs()-1);
			}*/
			removeEdge(e);
			delete(e);
			j--;
		}
	}
}

bool Graph::containsEdge(Edge* e)
{
	return containsEdge(e->getSource(), e->getDestination());
}

bool Graph::containsEdge(Vertex* v1, Vertex* v2)
{
	if(edge(v1, v2) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Graph::containsVertex(Vertex* v)
{
	for(int i = 0; i < vertexList->size(); i++)
	{
		if(vertexList->at(i) == v)
		{
			return true;
		}
	}
	return false;
}

int Graph::cost(vector<Vertex*> path)
{
	int cost = 0;
	Vertex* src = path[0];
	Vertex* dest = NULL;
	for(int i = 1; i < path.size(); i++)
	{
		dest = path[i];
		cost = cost + edgeWeight(src, dest);
		src = dest;
	}
	return cost;
}

int Graph::degree(Vertex* v)
{
	if(isDirected() == true)
	{
		return inDegree(v) + outDegree(v);
	}
	else
	{
		return outDegree(v);
	}
}

Edge* Graph::edge(Vertex* v1, Vertex* v2)
{
	if(containsVertex(v1) == false)
	{
		cout << "Edge* Graph::edge(Vertex* v1, Vertex* v2)" << endl;
		cout << "no such vertex = " << v1->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}

	for(int i = 0; i < adjacencyList->at(v1)->size(); i++)
	{
		if(adjacencyList->at(v1)->at(i)->getDestination() == v2)
		{
			return adjacencyList->at(v1)->at(i);
		}
		if(adjacencyList->at(v1)->at(i)->getSource() == v2
			&& adjacencyList->at(v1)->at(i)->isDirected() == false)
		{
			return adjacencyList->at(v1)->at(i);
		}
	}
	return NULL;
}

int Graph::edgeCount()
{
	return edges().size();
}

vector<Edge*> Graph::edges()
{
	vector<Edge*> edges;
	for(int i = 0; i < vertexList->size(); i++)
	{
		Vertex* src = vertexList->at(i);
		for(int j = 0; j < adjacencyList->at(src)->size(); j++)
		{
			edges.push_back(adjacencyList->at(src)->at(j));
		}
	}
	return edges;
}

int Graph::edgeWeight(Vertex *v1, Vertex *v2)
{
	Edge* e = edge(v1, v2);
	if(e == NULL)
	{
		cout << "function : int Graph::edgeWeight(Vertex v1, Vertex v2)\n";
		cout << "no edge between " << v1->toString() << " to " << v2->toString() << endl << endl;
		cout << "exiting.." << endl;exit(1);
	}
	return e->getWeight();
}

int Graph::inDegree(Vertex* v)
{
	if(containsVertex(v) == false)
	{
		cout << "int Graph::inDegree(Vertex* v)" << endl;
		cout << "no such vertex = " << v->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}

	int indegree = 0;
	for(int i = 0; i < vertexList->size(); i++)
	{
		Vertex* src = vertexList->at(i);
		if(src == v)
		{
			continue;
		}

		for(int j = 0; j < adjacencyList->at(src)->size(); j++)
		{
			if(adjacencyList->at(src)->at(j)->getDestination() == v
				|| (adjacencyList->at(src)->at(j)->getSource() == v
					&& adjacencyList->at(src)->at(j)->isDirected() == false))
			{
				indegree++;
			}
		}
	}

	return indegree;
}

bool Graph::isDirected()
{
	return directed;
}

bool Graph::isEmpty()
{
	if(vertexCount() == 0)
	{
		return true;
	}
	return false;
}

bool Graph::isReachable(Vertex* v1, Vertex* v2)				// DFS
{
	//TODO
	stack<Vertex*> vlist;
	vector<int> check(10,0);
	vlist.push(v1);
	vector<Vertex*> neighbour;
	int p=0;
	
	while(vlist.size()!=0)
    { //cout<<"r"<<endl;
        if(vlist.top()==v2)
        {
            p=1;
            break;
        }
        else
        {
            Vertex* m;
            m=vlist.top();
            vlist.pop();
            neighbour=neighbors(m);
            for(int i=0;i<neighbour.size();i++)
            {
                if(check[neighbour[i]->getVertexNumber()]==0)
                {
                    vlist.push(neighbour[i]);
                    check[neighbour[i]->getVertexNumber()]=1;
                }
            }

        }
  //cout << vlist.size();
    }

        if(p==1)
        {
            return(1);
        }
        else
        {
            return(0);
        }

}

bool Graph::isWeighted()
{
	return weighted;
}

vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{cout<<"starting\n";
	//TODO
	//return set of vertex pointers that make up the minimum weight path from v1 to v2
	//if no path exists, return NULL
	vector<Vertex*>* pro;
	cout<<"made vector\n";
	priorityqueue name ;
	cout<<"priority queue \n";
	pro = vertices();
	cout <<"Got pro\n";
	Vertex* h;
	int o;
	o=pro->size();
	int check1[o];
	Vertex** check2= new Vertex*[o];
	cout <<"Here1 \n";
	for(int m=0;m<pro->size();m++)
	{
		cout <<"Starting for\n";
		name.push((*pro)[m]);
		cout <<"pushed\n";
		check2[m]= NULL;
		cout<<"end for\n";
	}
	cout <<"Done for loop\n";
	name.decreaseMin(v1,0);
	if(!(isReachable(v1,v2)))
	{
		return NULL;
	}
	else
	{
		cout <<"In else loop\n";
		h=name.top().ver;

		while(name.top().ver!=v2)
		{
			cout <<"In while loop\n";
			vector<Vertex*> neigh;
			neigh=neighbors(h);
			name.pop();
			check1[h->getVertexNumber()]=1;
			for(int t=0;t<neigh.size();t++)
			{
				if(check1[neigh[t]->getVertexNumber()]=0)
				{
					if(name.distance(neigh[t]) > name.distance(h) + edgeWeight(neigh[t],h))
						{
							name.decreaseMin(neigh[t],name.distance(h)+edgeWeight(neigh[t],h));
							check2[neigh[t]->getVertexNumber()]=h;
						}
				}
			}
			cout <<"Out while loop\n";

		}

	vector<Vertex*> result1;
	vector<Vertex*> result;  //result
	vector<Vertex*>* pointer=new vector<Vertex*>;  
	//pointer= &result;   //pointer to result
	Vertex* ptr=v2;
	result1.push_back(v2);
	cout <<"Here\n";
	while(ptr!=v1)
	{
		cout <<"In while1\n";
		cout <<ptr->getVertexNumber()<<"\n";
		result1.push_back(check2[ptr->getVertexNumber()]);
		cout <<"pushed\n";
		ptr=check2[ptr->getVertexNumber()];
		cout <<"Out while1\n";
	}
	for(int g=0;g<result1.size();g++)
	{
		cout <<"in for\n";
		pointer->push_back(result1[result1.size()-1-g]);
		cout <<"out for\n";
	}

	return(pointer);


	}
}

//returns all nodes x, such that edge(v, x) exists
vector<Vertex*> Graph::neighbors(Vertex* v)
{
	if(containsVertex(v) == false)
	{
		cout << "vector<Vertex*> Graph::neighbors(Vertex* v)" << endl;
		cout << "no such vertex = " << v->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}

	vector<Vertex*> toBeReturned;
	for(int i = 0; i < adjacencyList->at(v)->size(); i++)
	{
		if(adjacencyList->at(v)->at(i)->getSource() == v)
		{
			toBeReturned.push_back(adjacencyList->at(v)->at(i)->getDestination());
		}
		else if(adjacencyList->at(v)->at(i)->getDestination() == v)
		{
			toBeReturned.push_back(adjacencyList->at(v)->at(i)->getSource());
		}
		else
		{
			cout << "Function : vector<Vertex*> Graph::neighbors(Vertex* v)\n";
			cout << "unrelated edge : " << adjacencyList->at(v)->at(i)->toString() << " in adjacency list of " << v->toString() << endl;
			cout << "exiting.." << endl;exit(1);
		}
	}

	return toBeReturned;
}

int Graph::outDegree(Vertex* v)
{
	if(containsVertex(v) == false)
	{
		cout << "int Graph::outDegree(Vertex* v)" << endl;
		cout << "no such vertex = " << v->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}

	return adjacencyList->at(v)->size();
}

Edge* Graph::removeEdge(Edge* e)
{
	removeEdge(e->getSource(), e->getDestination());
}

Edge* Graph::removeEdge(Vertex* v1, Vertex* v2)
{
	if(containsEdge(v1, v2) == false)
	{
		return NULL;
	}

	Edge *e = removeAdjacencyListEdge(v1, v2);
	e = removeAdjacencyListEdge(v2, v1);
	return e;
}

Edge* Graph::removeAdjacencyListEdge(Vertex* v1, Vertex* v2)
{
//	cout << "Graph::removeAdjacencyListEdge(Vertex* v1, Vertex* v2) " << v1->toString() << " " << v2->toString() << endl;
	if(containsVertex(v1) == false)
	{
		cout << "Edge* Graph::removeAdjacencyListEdge(Vertex* v1, Vertex* v2)" << endl;
		cout << "no such vertex = " << v1->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}
	if(containsVertex(v2) == false)
	{
		cout << "Edge* Graph::removeAdjacencyListEdge(Vertex* v1, Vertex* v2)" << endl;
		cout << "no such vertex = " << v2->toString() << endl;
		cout << "exiting.." << endl;exit(1);
	}

	Edge* e = NULL;
	for(int i = 0; i < adjacencyList->at(v1)->size(); i++)
	{
//		cout<<adjacencyList->at(v1)->at(i)->toString()<<endl;
		if(adjacencyList->at(v1)->at(i)->getDestination() == v2
			|| adjacencyList->at(v1)->at(i)->getSource() == v2)
		{
			e = adjacencyList->at(v1)->at(i);
			for(; i < adjacencyList->at(v1)->size()-1; i++)
			{
				adjacencyList->at(v1)->at(i) = adjacencyList->at(v1)->at(i+1);
			}
			break;
		}
	}
	if(e != NULL)
	{
		adjacencyList->at(v1)->pop_back();
	}
	return e;
}

void Graph::removeVertex(Vertex* v)
{
	/*for(int i = 0; i < adjacencyList->at(v)->size(); i++)
	{
		cout << adjacencyList->at(v)->at(i)->toString() << endl;
	}*/
	if(containsVertex(v) == false)
	{
		return;
	}

	//remove all undirected edges involving 'v'
	//remove all directed adges with 'v' as the source
	while(adjacencyList->at(v)->empty() == false)
	{
		removeEdge(adjacencyList->at(v)->at(0));
	}

	//remove all directed adges with 'v' as the destination
	for(int i = 0; i < vertexList->size(); i++)
	{
		Vertex* src = vertexList->at(i);
		if(src != v)
		{
			for(int j = 0; j < adjacencyList->at(src)->size(); j++)
			{
				if(adjacencyList->at(src)->at(j)->getDestination() == v)
				{
					removeEdge(adjacencyList->at(src)->at(j));
				}
			}
		}
	}

	adjacencyList->erase(v);

	for(int i = 0; i < vertexList->size(); i++)
	{
		if(vertexList->at(i) == v)
		{
			for(; i < vertexList->size()-1; i++)
			{
				vertexList->at(i) = vertexList->at(i+1);
			}
			break;
		}
	}
	vertexList->pop_back();
//	num_vertices--;

//	delete(v);
}

vector<Vertex*>* Graph::shortestPath(Vertex* v1, Vertex* v2)	// BFS
{
	//TODO
	//return set of vertex pointers that make up the shortest path from v1 to v2
	//if no path exists, return NULL
	if(!(isReachable(v1,v2)))
	{
		return NULL;
	}
	else
	{
		queue<Vertex*> vlist1;
		vector<Vertex*> check1(10,NULL);  //pointers of parent
		vlist1.push(v1);
		vector<int> checkv(10,0);     //check if visited
		vector<Vertex*> neighbour1;  //neighbours
		vector<Vertex*> result1;
		vector<Vertex*> result;  //result
		vector<Vertex*>* pointer=new vector<Vertex*>;  
		//pointer= &result;   //pointer to result
		Vertex* ptr;
	
			while(vlist1.size()!=0)
			{
				if(vlist1.front()==v2)
				{
					break;
				}
				else
				{
					Vertex* m1;
					m1=vlist1.front();
					vlist1.pop();
					neighbour1=neighbors(m1);
					for(int i=0;i<neighbour1.size();i++)
					{
						if(checkv[neighbour1[i]->getVertexNumber()]==0)
						{
							vlist1.push(neighbour1[i]);
							checkv[neighbour1[i]->getVertexNumber()]=1;
							check1[neighbour1[i]->getVertexNumber()]=m1;
	
						}
					}
				}
	
		}
			ptr=v2;
			result1.push_back(v2);
			while(ptr!=v1)
			{
				result1.push_back(check1[ptr->getVertexNumber()]);
				ptr=check1[ptr->getVertexNumber()];
			}
	
			for(int g=0;g<result1.size();g++)
			{
				pointer->push_back(result1[result1.size()-1-g]);
			}
	
		return pointer;
	
	}
	
}

int Graph::vertexCount()
{
	return vertexList->size();
}

vector<Vertex*>* Graph::vertices()
{
	return vertexList;
}

map<Vertex*, vector<Edge*>* >* Graph::getAdjacencyList()
{
	return adjacencyList;
}

string Graph::toString()
{
	string str;
	str.append("\n--------------------------\n\nGraph:\n\n");
	for(int i = 0; i < vertexList->size(); i++)
	{
		Vertex* v = vertexList->at(i);
		str.append(v->toString());
		str.append(" connected to\n");
		for(int j = 0; j < adjacencyList->at(v)->size(); j++)
		{
			if(v == adjacencyList->at(v)->at(j)->getSource())
			{
				str.append(adjacencyList->at(v)->at(j)->getDestination()->toString());
			}
			else if(v == adjacencyList->at(v)->at(j)->getDestination())
			{
				str.append(adjacencyList->at(v)->at(j)->getSource()->toString());
			}
			else
			{
				cout << "Function : string Graph::toString()\n";
				cout << "unrelated edge : " << adjacencyList->at(v)->at(j)->toString() << " in adjacency list of " << v->toString() << endl;
				cout << "exiting.." << endl;exit(1);
			}
			str.append(" [W=");
			char buf[32];
			sprintf(buf, "%d", adjacencyList->at(v)->at(j)->getWeight());
			str.append(buf);
			str.append("]    ");
		}
		str.append("\n\n");
	}
	return str;
}
