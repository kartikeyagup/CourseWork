#include "Graph.h"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <stack>
#include <list>
#include "FacebookVertex.h"

#define INT_MAX 32767

using namespace std;

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
	bool sofar=false;
	stack<Vertex*> s1;
	vector<Vertex*> visited;
	visited.push_back(v1);
	s1.push(v1);
	while ((!s1.empty()) && (!sofar))
	{
		Vertex* current=s1.top();
		s1.pop();
		if (current==v2)
		{
			sofar=true;
		}
		else
		{
			for(int j = 0; j < adjacencyList->at(current)->size(); j++)
			{
				Vertex* v2= adjacencyList->at(current)->at(j)->getDestination();
				Vertex* v3= adjacencyList->at(current)->at(j)->getSource();
				if (v2==current)
					v2=v3;
				bool b2=false;
				int limt=visited.size(),i=0;
				while (i<limt && !b2)
				{
					if (visited[i]==v2)
						b2=true;
					i+=1;
				}
				if (!b2)
				{
					visited.push_back(v2);
					s1.push(v2);
				}
			}
		}
	}
	return sofar;
}

bool Graph::isWeighted()
{
	return weighted;
}

class pq
{
	public:
		vector<pair<int,Vertex*> >* heap;
	
		pq();

		pair<int, Vertex*> top();
		bool empty();
		int sizeofheap();
		void pushnew(pair<int, Vertex*>);
		void popmin();
		void decreasepriority(Vertex*,int);
		int getpriority(Vertex*);
};

pq::pq()
{
	heap=new vector<pair<int,Vertex*> >;
	heap->push_back(pair<int,Vertex*> (-1234,NULL));
}

bool pq::empty()
{
	return (heap->size()==1);
}

int pq::sizeofheap()
{
	return heap->size() -1;
}

pair<int,Vertex*> pq::top()
{
	return heap->at(1);
}

int pq::getpriority(Vertex* v1)
{
	for (int i=0; i< heap->size() ;i++)
	{
		if (heap->at(i).second==v1)
			return heap->at(i).first;
	}	
}

void pq::popmin()
{
	int limt=heap->size();
	heap->at(1)=heap->at(limt-1);
	heap->erase(heap->end());
	int i=1;
	bool done=false;
	// cout <<"Starting the main of popmin\n";
	while ((i<=(limt-3)/2) && (!done))
	{
		// cout <<" In while\n";
		if (heap->at(i).first <heap->at(2*i).first)
		{
			// cout <<"In if1\n";
			if (heap->at(i).first < heap->at(2*i +1).first)
				done=true;
			else
			{
				// cout <<"In else2\n";
				pair<int, Vertex*> temp=heap->at(2*i +1);
				heap->at(2*i+1)= heap->at(i);
				heap->at(i)=temp;
				i=2*i +1; 
				// cout <<"Out else2\n";
			}
		}
		else
		{
			// cout <<"In else11\n";
			if (heap->at(2*i).first<heap->at(2*i+1).first)
			{
				// cout <<"In if21\n";
				pair<int,Vertex*> temp=heap->at(2*i);
				heap->at(2*i)=heap->at(i);
				heap->at(i)=temp;
				i=2*i;
				// cout <<"Out if21\n";
			}
			else
			{
				// cout <<"In else21\n";
				pair<int, Vertex*> temp=heap->at(2*i+1);
				heap->at(2*i+1)=heap->at(i);
				heap->at(i)=temp;
				i=2*i+1;	
				// cout <<"out else21\n";
			}		
		}
		// cout <<"Outwhile\n";
	}
	if (!done)
	{
		if (2*i==limt-2)
		{
			if (heap->at(2*i).first <= heap->at(i).first)
			{
				pair<int, Vertex*> temp= heap->at(2*i);
				heap->at(2*i)=heap->at(i);
				heap->at(i)=temp;
			}
		}
	}
}

void pq::pushnew(pair<int,Vertex*> p12)
{
	heap->push_back(p12);
	int i= heap->size()-1;
	bool done=false;
	while ((i>1) && !done)
	{
		if (heap->at(i).first >= heap->at(i/2).first)
			done=true;
		else
		{
			pair<int,Vertex*> temp= heap->at(i);
			heap->at(i)=heap->at(i/2);
			heap->at(i/2)=temp;
			i /=2;
		}
	}
}

void pq::decreasepriority(Vertex* v1,int newp)
{
	int i=1, limt=heap->size()-1;
	bool done=false;
	while (i<=limt && !done)
	{
		if (heap->at(i).second==v1)
		{
			done=true;
			if (newp< heap->at(i).first)
				heap->at(i)=pair<int,Vertex*> (newp,v1);
			i--;
		}
		i++;
	}
	done=false;
	while ((i>1) && !done)
	{
		if (heap->at(i).first >heap->at(i/2).first)
			done=true;
		else
		{
			pair<int,Vertex*> temp= heap->at(i);
			heap->at(i)=heap->at(i/2);
			heap->at(i/2)=temp;
			i /=2;
		}
	}
}

vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{
	if (v1==v2)
	{
		vector<Vertex*>* f1= new vector<Vertex*>;
		f1->push_back(v1);
		return f1;
	}
	vector<Vertex*>* vertices1=vertices();
	const int numvert=vertices1->size();
	pair<int, Vertex*> modeprev [numvert];
	for (int i=0;i<numvert;i++)
	{
		modeprev[i]=pair<int,Vertex*> (0, NULL);	//0 stands for not epanded.
		if (vertices1->at(i)==v1)
			modeprev[i].first=1;					//1 stands for in the heap.
	}
	// list<pair<int, Vertex*> > mainlist;
	pq heap1=pq();
	heap1.pushnew(pair<int,Vertex*> (0,v1));
	// mainlist.push_front(pair<int,Vertex*> (0,v1));
	bool done=false;
	// cout <<"Starting dijkstra\n";
	while (!heap1.empty() && !done)
	{
		pair<int,Vertex*> minsofar=heap1.top();
		// for (list<pair<int,Vertex*> >:: iterator it=mainlist.begin(); it != mainlist.end(); ++it)
		// {
		// 	if (it->first<minsofar.first)
		// 		minsofar=*it;
		// }
		// cout <<"found minsofar for this\n";
		for (int i=0; i<numvert;i++)
		{
			if (vertices1->at(i)==minsofar.second)
				modeprev[i].first=2; 						//2 stands for expanded
		}
		// cout <<"Set minsofar as expanded\n";
		heap1.popmin();
		// cout <<"Popped\n";
		// mainlist.remove(minsofar);
		if (minsofar.second==v2)
		{
			done=true;
			// cout <<"Found the end\n";
		}
		else
		{
			// cout <<"In the else case\n";
			vector<Vertex*> neigh1=neighbors(minsofar.second);
			for (vector<Vertex*>::iterator it =neigh1.begin() ; it != neigh1.end(); ++it)
			{
				// cout <<"In here1\n";
				for (int j=0; j<numvert; j++)
				{
					// cout <<"In here2\n";
					if (vertices1->at(j)== *it)
					{
						// cout <<"In if1\n";
						if (modeprev[j].first==0)
						{
							// cout <<"In if2\n";
							modeprev[j].first=1;
							modeprev[j].second=minsofar.second;
							// mainlist.push_front(pair<int, Vertex*> (minsofar.first +edgeWeight(minsofar.second, *it),*it));
							heap1.pushnew(pair<int, Vertex*> (minsofar.first +edgeWeight(minsofar.second, *it),*it));
							// cout <<"Out if2\n";
						}
						else if (modeprev[j].first==1)
						{
							int p1=heap1.getpriority(*it);
							heap1.decreasepriority(*it,minsofar.first +edgeWeight(minsofar.second, *it));		
							int p2=heap1.getpriority(*it);
							if (p2<p1)
							{
								modeprev[j].second=minsofar.second; 			
							}
						}
						// cout <<"Out elseif\n";
					}
					// cout <<"Out if1\n";
				}
					// cout << "Out here2\n";
				// cout <<"Out here1\n";
			}
		}
	}
	// cout <<"Done with dijkstra's part\n";
	if (done)
	{
		vector<Vertex*>* finans=new vector<Vertex*>;
		Vertex* curr1=v2;
		finans->push_back(curr1);
		bool done1=false;
		while (!done1)
		{
			int p;
			for (int i=0; i<numvert; i++)
			{
				if (vertices1->at(i)==curr1)
					p=i;
			}
			curr1=modeprev[p].second;
			finans->push_back(curr1);
			if (curr1==v1)
				done1=true;
		}
		reverse(finans->begin(), finans->end());
		return finans;
	}
	else
		return NULL;
	//TODO
	//return set of vertex pointers that make up the minimum weight path from v1 to v2
	//if no path exists, return NULL
}

// vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
// {
// 	if (v1==v2)
// 	{
// 		vector<Vertex*>* f1= new vector<Vertex*>;
// 		f1->push_back(v1);
// 		return f1;
// 	}
// 	vector<Vertex*>* vertices1=vertices();
// 	const int numvert=vertices1->size();
// 	pair<int, Vertex*> modeprev [numvert];
// 	for (int i=0;i<numvert;i++)
// 	{
// 		modeprev[i]=pair<int,Vertex*> (0, NULL);	//0 stands for not epanded.
// 		if (vertices1->at(i)==v1)
// 			modeprev[i].first=1;					//1 stands for in the heap.
// 	}
// 	list<pair<int, Vertex*> > mainlist;

// 	mainlist.push_front(pair<int,Vertex*> (0,v1));
// 	bool done=false;
// 	// cout <<"Starting dijkstra\n";
// 	while (!mainlist.empty() && !done)
// 	{
// 		pair<int,Vertex*> minsofar=mainlist.front();
// 		for (list<pair<int,Vertex*> >:: iterator it=mainlist.begin(); it != mainlist.end(); ++it)
// 		{
// 			if (it->first<minsofar.first)
// 				minsofar=*it;
// 		}
// 		// cout <<"found minsofar for this\n";
// 		for (int i=0; i<numvert;i++)
// 		{
// 			if (vertices1->at(i)==minsofar.second)
// 				modeprev[i].first=2; 						//2 stands for expanded
// 		}
// 		// cout <<"Set minsofar as expanded\n";
// 		mainlist.remove(minsofar);
// 		if (minsofar.second==v2)
// 		{
// 			done=true;
// 			// cout <<"Found the end\n";
// 		}
// 		else
// 		{
// 			// cout <<"In the else case\n";
// 			vector<Vertex*> neigh1=neighbors(minsofar.second);
// 			for (vector<Vertex*>::iterator it =neigh1.begin() ; it != neigh1.end(); ++it)
// 			{
// 				// cout <<"In here1\n";
// 				for (int j=0; j<numvert; j++)
// 				{
// 					// cout <<"In here2\n";
// 					if (vertices1->at(j)== *it)
// 					{
// 						// cout <<"In if1\n";
// 						if (modeprev[j].first==0)
// 						{
// 							// cout <<"In if2\n";
// 							modeprev[j].first=1;
// 							modeprev[j].second=minsofar.second;
// 							mainlist.push_front(pair<int, Vertex*> (minsofar.first +edgeWeight(minsofar.second, *it),*it));
// 							// cout <<"Out if2\n";
// 						}
// 						else if (modeprev[j].first==1)
// 						{
// 							// cout << "In elseif\n";
// 							bool done2=0;
// 							list<pair<int, Vertex*> >::iterator it1=mainlist.begin();	
// 							while (!done2)
// 							{
// 								// for ( it1!= mainlist.end(); ++it1)
// 								// {
// 								// cout <<"New check\n";
// 								if (it1->second ==*it)
// 								{
// 									done2=1;
// 									// cout <<"Checking to enhance\n";
// 									if (it1->first > minsofar.first +edgeWeight(minsofar.second, *it))
// 									{
// 										// cout <<"Enhancing weight\n";
// 										mainlist.remove(*it1);
// 										modeprev[j].second=minsofar.second;
// 										mainlist.push_front(pair<int, Vertex*> ( minsofar.first+edgeWeight(minsofar.second,*it), *it));
// 										// cout <<"Done enhancing weight\n";
// 									}
// 								}
// 								it1++;
// 							}
// 							// cout <<"Out of here \n";
// 						}
// 						// cout <<"Out elseif\n";
// 					}
// 					// cout <<"Out if1\n";
// 				}
// 					// cout << "Out here2\n";
// 				// cout <<"Out here1\n";
// 			}
// 		}
// 	}
// 	// cout <<"Done with dijkstra's part\n";
// 	if (done)
// 	{
// 		vector<Vertex*>* finans=new vector<Vertex*>;
// 		Vertex* curr1=v2;
// 		finans->push_back(curr1);
// 		bool done1=false;
// 		while (!done1)
// 		{
// 			int p;
// 			for (int i=0; i<numvert; i++)
// 			{
// 				if (vertices1->at(i)==curr1)
// 					p=i;
// 			}
// 			curr1=modeprev[p].second;
// 			finans->push_back(curr1);
// 			if (curr1==v1)
// 				done1=true;
// 		}
// 		reverse(finans->begin(), finans->end());
// 		return finans;
// 	}
// 	else
// 		return NULL;
// 	//TODO
// 	//return set of vertex pointers that make up the minimum weight path from v1 to v2
// 	//if no path exists, return NULL
// }

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
	bool sofar=false;
	queue<Vertex*> s1;
	vector<Vertex*> visited;
	vector<Vertex*> previous;
	visited.push_back(v1);
	s1.push(v1);
	while ((!s1.empty()) && (!sofar))
	{
		Vertex* current=s1.front();
		s1.pop();
		if (current==v2)
		{
			sofar=true;
		}
		else
		{
			for(int j = 0; j < adjacencyList->at(current)->size(); j++)
			{
				Vertex* v2= adjacencyList->at(current)->at(j)->getDestination();
				Vertex* v3= adjacencyList->at(current)->at(j)->getSource();
				if (v2==current)
					v2=v3;
				bool b2=false;
				int limt=visited.size(),i=0;
				while (i<limt && !b2)
				{
					if (visited[i]==v2)
						b2=true;
					i+=1;
				}
				if (!b2)
				{
					visited.push_back(v2);
					previous.push_back(current);
					s1.push(v2);
				}
			}
		}
	}
	// cout <<"Done with everything1213\n";
	if (sofar)
	{
		// cout <<"In sofar\n";
		vector<Vertex*> *finans=new vector<Vertex*>;
		if (v2==v1)
		{
			// cout <<"In here\n";
			finans->push_back(v1);
			// finans->push_back(v2);
		}
		else
		{
			// cout <<"finans started\n";
			Vertex* curr1=v2;
			finans->push_back(curr1);
			bool done=false;
			// cout <<"in done\n";
			while (!done)
			{
				// cout <<"In here\n";
				int p;
				for (int i=0; i<visited.size(); i++)
				{
					// cout <<"Further in here\n";
					if (visited[i]==curr1)
						p=i;
					// cout <<"Further out here\n";
				}
				curr1=previous[p-1];
				// cout << "Here\n";
				finans->push_back(curr1);
				if (curr1==v1)
					done=true;
				// cout <<"Out here\n";
			}
		}
		return finans;
	}
	else
		return NULL;
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
