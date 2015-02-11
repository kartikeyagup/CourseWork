#include "Graph.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<stack>
#include<algorithm>
#include"FacebookVertex.h"


#define INT_MAX 32767




using namespace std;

int new_vertex_ID =0;




bool compare(pair<int , Vertex*> a, pair<int, Vertex*> b)
{
	if(a.first>b.first) return true;
	else return false;
}

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
	stack<Vertex*> st;
	st.push(v1);
	int count= vertexCount();
	bool visited[count];
	fill_n(visited,count , 0);
	Vertex* s = new Vertex();
	while(st.empty()==0)
	{
		s = st.top();
		if(s==v2)
		break;
		st.pop();
		for(int i=0;i<neighbors(s).size();i++)
		{
			Vertex* neb = neighbors(s).at(i);
			int vern = neb->getVertexNumber();
			if(visited[vern]==0)
			{	
				visited[vern]=1;
				st.push(neb);
			}
		}
	}
	if(st.empty())
	 return false;
	else
	return true;
}

bool Graph::isWeighted()
{
	return weighted;
}






class PriorityQueueArray 
 {
	private:
		int capacity;
		int sizeofpq;
		pair<int , Vertex*> * arr;
		
		void percolateup(int pos);
		void percolatedown(pair<int , Vertex*>  x);
		
		

	public:
		PriorityQueueArray(int x);
		void push (const pair<int , Vertex*> & val);
		bool empty();
		pair<int , Vertex*>  top();
		void pop();
		int size();
		int* position;
		void DecreasePriority(Vertex* p , int newval);
};


PriorityQueueArray::PriorityQueueArray(int x)
{
	capacity=10;
	sizeofpq=0;
	pair<int , Vertex*> * arrp= new pair<int , Vertex*> [10];
	arr=arrp;
	int* position1= new int[x];
	position = position1;
	for(int i=0;i<x;i++) position[i] = -1 ;
}

void PriorityQueueArray::percolateup(int pos)
{
	position[arr[pos].second->getVertexNumber()]= pos;
	for(int i=pos;i>1;i/=2)
	{
		 if(arr[i/2]>arr[i]) 
		 {
		 	position[(arr[i].second)->getVertexNumber()]=i/2;
		 	position[(arr[i/2].second)->getVertexNumber()]=i;
			 swap(arr[i],arr[i/2]);
		 }	
		 else
		 {
		 	 break;
		 }
	}
}

void PriorityQueueArray::percolatedown(pair<int , Vertex*>  x)
{
	position[(x.second)->getVertexNumber()]=1;
	arr[1] = x;
	int i=1;
	while(i<=sizeofpq)
	{
		if(2*i>sizeofpq) 
		{
			arr[i]=x;
			position[(x.second)->getVertexNumber()]=i;
			break;
		}
		if(2*i==sizeofpq)
		{
			if(arr[2*i]>x)
			{
				
				arr[i]=x;
				position[(x.second)->getVertexNumber()]=i;
			}
			else 
			{
				position[(arr[2*i].second)->getVertexNumber()]=i;
				position[(arr[i].second)->getVertexNumber()]=2*i;
				swap(arr[i], arr[2*i]);
			}
			break;
		}
		else
		{
			int j;
			if(arr[2*i+1]>arr[2*i]) j=2*i;
			else j=2*i+1;
			if (arr[j]>x)
			{
				position[(x.second)->getVertexNumber()]=i;
				arr[i]=x;
				break;
			}
			else 
			{
				position[(arr[i].second)->getVertexNumber()]=j;
				position[(arr[j].second)->getVertexNumber()]=i;
				swap(arr[i],arr[j]);
				i=j;
			}
		}
	}
}


void PriorityQueueArray::push (const pair<int , Vertex*> & val)
{
	//cout<<val.second->getVertexNumber()<<" "<<position[val.second->getVertexNumber()]<<"yoagain"<<endl;
	sizeofpq+=1;
	if(sizeofpq==capacity)
	{
		pair<int , Vertex*> * arrp= new pair<int , Vertex*> [2*capacity];
		for(int i=1;i<sizeofpq;i++)
		{
			arrp[i]=arr[i];
		}
		delete[] arr;
		arr=arrp;
		capacity*=2;
	}
	arr[sizeofpq]=val;
	percolateup(sizeofpq);
	
}


void PriorityQueueArray::DecreasePriority(Vertex* p , int newval)
{
	int pos = position[p->getVertexNumber()];
	pair<int, Vertex*> pa = make_pair(newval, p);
	for(int i=0;i<10;i++)
	arr[pos]= pa; 
	percolateup(pos);
}
	
bool PriorityQueueArray::empty()
{
	if(sizeofpq==0) return true;
	else return false;
}
	
pair<int , Vertex*>  PriorityQueueArray::top()
{
	if(sizeofpq!=0) return arr[1];
	else cout<<"No top element exists"<<endl;
}
	
void PriorityQueueArray::pop()
{
	if(sizeofpq>0)
	{
		pair<int , Vertex*>  x= arr[sizeofpq];
		sizeofpq-=1;
		percolatedown(x);
	}
	else
	{
		cout<<"No element to be deleted"<<endl;
	}
}
	
int PriorityQueueArray::size()
{
	return sizeofpq;
}









vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{
	
	PriorityQueueArray  st(vertexCount()) ;
	int count = vertexCount();
	Vertex* parent[count];
	int visited[count];
	for(int i=0;i<count ;i++)
	visited[i] = 0;
	int weight[count];
	for(int i=0;i<count ;i++)
	weight[i] = INT_MAX;
	pair<int , Vertex*> p = make_pair(0,v1); 
	weight[(p.second->getVertexNumber())]= 0;
	st.push(p);
	while(!st.empty())
	{
		p = st.top();
		if(p.second==v2)
		{
			break;
		}
		st.pop();
		int w= weight[p.second->getVertexNumber()];
		visited[p.second->getVertexNumber()] = 2;
		for(int i=0;i<neighbors(p.second).size();i++)
		{
			Vertex* neb = neighbors(p.second).at(i);
			int vern = neb->getVertexNumber();
			if(visited[vern]==0)
			{
				visited[vern]=1;
				parent[vern]= p.second;
				st.push(make_pair(edgeWeight(neb,p.second),neb));
				weight[vern]= edgeWeight(neb,p.second);
			}
			else
			{
				if(visited[vern]==1)
				{
					int w1 = weight[vern];
					if(w1 > w + edgeWeight(neb,p.second))
					{
						st.DecreasePriority(neb, w+edgeWeight(neb ,p.second));
						weight[vern]= w+edgeWeight(neb,p.second);
						parent[vern]= p.second;
					}
				}	
			}
		}
	}
	//TODO
	//return set of vertex pointers that make up the minimum weight path from v1 to v2
	//if no path exists, return NULL
	if(st.empty())
		return NULL;
	else
	{
		vector<Vertex*>* revv = new vector<Vertex*>;
		Vertex* s = v2;
		while(s!=v1)
		{
			revv->push_back(s);
			s = parent[(s->getVertexNumber())];
		}
		revv->push_back(v1);
		vector<Vertex*>* v = new vector<Vertex*>;
		for(int i=revv->size()-1;i>=0;i--)
		{
			v->push_back(revv->at(i));
		}
		return v;		
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
	/*queue <Vertex*> q;
	unordered_map <  Vertex*,bool> visited;
	unordered_map <  Vertex*,Vertex*> parent;
	q.push(v1);
	while(q.empty()==0)
	{
		Vertex* s;
		s=q.front();
		if(s==v2)
		break;
		q.pop();
		for(int i=0; i<neighbors(s).size() ; i++)
		{
			
			Vertex* neb = neighbors(s).at(i);		
			if(visited.find(neb)== visited.end())
			{
				visited[(neb)]=1;
				parent[(neb)]=s;
				q.push(neb);
			}
		}	
	}
	vector< Vertex*>* spath = new vector< Vertex*>();
	
	if(q.empty())
	return NULL;
	else
	{

		Vertex* s = q.front();
		cout<<((FacebookVertex*) s)->toString()<<endl;
		while(s!=v1)
		{
		
			spath->push_back(s);
			s=parent[(s)];		
		}
		spath->push_back(s);
		return spath;
	}*/	
	queue <Vertex*> q;
	int count = vertexCount();
	bool visited[count];
	fill_n(visited,count , 0);
	Vertex* parent[count];
	q.push(v1);
	while(q.empty()==0)
	{
		Vertex* s;
		s=q.front();
		if(s==v2)
		break;
		q.pop();
		for(int i=0; i<neighbors(s).size() ; i++)
		{
			
			Vertex* neb = neighbors(s).at(i);
			int vern= neb->getVertexNumber();		
			if(visited[vern]==0)
			{
				visited[vern]=1;
				parent[vern]=s;
				q.push(neb);
			}
		}	
	}
	vector< Vertex*>* spath = new vector< Vertex*>();
	
	if(q.empty())
	return NULL;
	else
	{

		Vertex* s = q.front();
		cout<<((FacebookVertex*) s)->toString()<<endl;
		while(s!=v1)
		{
		
			spath->push_back(s);
			s=parent[s->getVertexNumber()];		
		}
		spath->push_back(s);
		return spath;
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
