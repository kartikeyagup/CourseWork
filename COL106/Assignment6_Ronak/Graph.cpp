#include "Graph.h"

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<stack>
#include"FacebookVertex.h"
#include<map>
#include<utility>
//#include<set>
#define iv pair<int,Vertex*>
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


/*class PriorityQueue{
	private:
		//TODO add private members here
		int counter,capacity;
		iv* pq;
		void getdouble();
		//mycomparison* a;
		

	public:
		PriorityQueue();
		void push (const iv& val);
		bool empty();
		iv top();
		void pop();
		pair<int,bool> find(const iv& val);
		void DecreasePriority(const iv& val, int f);
		int size();
		//void print();

};*/

PriorityQueue::PriorityQueue()
{
	capacity=10;
	pq= new iv[capacity];
	counter=1;
	//a=new mycomparison(destination);
	//TODO
}

void PriorityQueue::getdouble(){
	iv *p;
	int temp=capacity;
	capacity=2*capacity;
	p= new iv[capacity];
	for(int i=1;i<temp;i++){
		*(p+i)=*(pq+i);
	}
	delete [] pq;
	pq=p;
}

void PriorityQueue::push (const iv& val)
{	if(counter==capacity){
		getdouble();
		push(val);
	}
	else{
		int temp=counter;
		pq[temp]=val;
		while(temp>1){
			int x=temp/2;
			iv parent=pq[x];	
			if(parent.first > val.first){
				pq[x]=val;
				pq[temp]=parent;
				temp=temp/2;
			}
			else{
				break;
			}
		}
		counter=counter+1;
	}
	//TODO
}	
	
bool PriorityQueue::empty()
{
	return(size()==0);
	//TODO
}
	

iv PriorityQueue::top()
{
	if(empty()){
		cout<<"Empty"<<endl;
	}
	else{
		return pq[1];
	}
	//TODO
}
	
void PriorityQueue::pop()
{
	int temp=counter-1;
	if(empty()){
		cout<<"empty"<<endl;
	}
	else{
		pq[1]=pq[temp];
		counter=counter-1;
		int q=1;	
		while(2*q<counter){
			if(2*q==counter-1){
				if(pq[2*q].first > pq[q].first){
					break;
				}
				else{
					iv x=pq[2*q];
					pq[2*q]=pq[q];
					pq[q]=x;
					q=2*q;
				}
			}
			else{	
				if(pq[2*q+1].first > pq[2*q].first){
					if(pq[2*q].first > pq[q].first){
						break;
					}
					else{
						iv x=pq[2*q];
						pq[2*q]=pq[q];
						pq[q]=x;
						q=2*q;
					}		
				}
				else{
					if(pq[2*q+1].first > pq[q].first){
						break;
					}
					else{
						iv x=pq[2*q+1];
						pq[2*q+1]=pq[q];
						pq[q]=x;
						q=2*q+1;
					}
				}
			}
		}
	}
				
				
	//TODO
}
int PriorityQueue::find(Vertex* val){
	bool fin=0;
	int temp;
	for(int i=1;i<size()+1;i++){//cout<<"####"<<endl;
		if(pq[i].second==val){
			fin=1;
			temp=i;
			break;
		}
	}
	/*if(fin==0){
		return -1;
	}
	else{
		return temp;
	}*/
	return temp;
}

void PriorityQueue::DecreasePriority(int g,int f){
	//pair<int,bool> a=find(val.second);
	/*if(a.second==0){
		cout<<"not present in the pq"<<endl;
	}
	else{*/
		//cout<<"$$$"<<endl;
		int temp=g;	
		//iv value=pq[g];
		pq[g].first=f;
		while(temp>1){
			int x=temp/2;
			pair<int,Vertex*> parent;	
			parent=pq[x];
			if(pq[x].first > pq[g].first){
				pq[x]=pq[g];
				pq[temp]=parent;
				temp=temp/2;
			}
			else{
				break;
			}
		}
}
	
int PriorityQueue::size()
{
	return counter-1;
	//TODO
}


/*void PriorityQueue::print()
{
	for(int i = 1; i <=size(); i++)
	{	Point t=pq[i];
		int r= t.getRow();
		int c =t.getColumn();
		cout<<"("<<r<<","<<c<<")"<<" ";
	}
	cout<<endl;
}*/



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
	if(containsVertex(v1)==false || containsVertex(v2)==false){
		return false;
	}
	else{
		stack<Vertex*> a;
		map<Vertex*,bool> h;
		int flag=0;
		a.push(v1);
		h[v1]=1;
		while(a.empty()==false && flag==0){
			Vertex* x=a.top();
			if(x==v2){
				flag=1;
			}
			else{
				a.pop();
				//vector<Vertex*> t=neighbors(x);
				vector<Vertex*> t;
				if(isDirected()==true){
					for(int i = 0; i < adjacencyList->at(x)->size(); i++){
						if(adjacencyList->at(x)->at(i)->getSource() == x){
							t.push_back(adjacencyList->at(x)->at(i)->getDestination());
						}
					}
				}
				else{
					t=neighbors(x);
				}
				for(int i=0;i<t.size();i++){
					if(h[t[i]]==0){
						a.push(t[i]);
						h[t[i]]=1;
					}	
				}
			}
		}
		if(flag==0){
			return false;
		}
		else{
			return true;
		}
	}
	
	//TODO
}

bool Graph::isWeighted()
{
	return weighted;
}

vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{
	map<Vertex*,bool> h;
	map<Vertex*,int> weight;
	map<Vertex*,Vertex*> parent;
	//vector<Vertex*> forcost;
	int cost;
	vector<Vertex*>* finali=new vector<Vertex*>;
	vector<Vertex*>* finalo=new vector<Vertex*>;
	vector<Vertex*>* a=new vector<Vertex*>;
	a=vertices();
	int flag=0;
	if(isReachable(v1,v2)==false){
		return NULL;
	}
	else{
		PriorityQueue pqf;
		for(int i=0;i<a->size();i++){
			if(a->at(i)==v1){
				h[a->at(i)]=0;
				//weight[a->at(i)]=0;
				pqf.push(pair<int,Vertex*>(0,a->at(i)));		
			}
			else{
				h[a->at(i)]=0;
				//weight[a->at(i)]=INT_MAX;
				pqf.push(pair<int,Vertex*>(INT_MAX,a->at(i)));
			}
		}
		while(flag==0){
			//iv it=pqf.top();
			/*for(int i=1;i<pqf.size()+1;i++){
				cout<<pqf.pq[i].second->toString()<<"  ";
			}*/
			//cout<<endl;
			Vertex* x=(pqf.top()).second;
			cost=pqf.top().first;
			//forcost.push_back(x);
			//cost=weight[x];
			pqf.pop();
			h[x]=1;
			//cout<<(x==v2)<<endl;
			if(x==v2){
				Vertex* io=x;
				Vertex *p=parent[io];
				//cout<<(parent[io]==NULL)<<endl;
				//cout<<((FacebookVertex*)parent[io])->toString()<<endl;
				finali->push_back(io);
				while(io!=v1){
					//cout<<"Jk"<<endl;
					finali->push_back(p);
					io=p;
					if(io!=v1){
						p=parent[io];
					}
				}
				//finali->push_back(io);
				flag=1;
			}
			else{
				
				//vector<Vertex*> t=neighbors(x);
				//cout<<x->toString()<<" "<<cost<<endl;
				vector<Vertex*> t;
				/*if(isDirected()==true){
					for(int i = 0; i < adjacencyList->at(x)->size(); i++){
						if(adjacencyList->at(x)->at(i)->getSource() == x){
							t.push_back(adjacencyList->at(x)->at(i)->getDestination());
							//cout<<"###"<<endl;
						}
					}
				}
				else{*/
					t=neighbors(x);
				//}
				for(int i=0;i<t.size();i++){
					//cout<<"####"<<endl;
					bool z=h[t[i]];
					//if(t[i]==v2){cout<<z<<endl;}
					if(z!=1){
						//cout<<i<<endl;
						int g=pqf.find(t[i]);
						//if(t[i]==v2){cout<<g<<endl;}
						if(g>0){
						//if(t[i]==v2){cout<<(t[i]==pqf.pq[g].second)<<endl;}
						int initial_weight=pqf.pq[g].first;
						//if(t[i]==v2){cout<<initial_weight<<endl;}
						//if(t[i]==v2){cout<<cost + edgeWeight(x,t[i])<<endl;}
						if(cost + edgeWeight(x,t[i])<initial_weight){
							//weight[t[i]]=final_weight;
							//cout<<t[i]->toString()<<endl;
							//cout<<"####"<<endl;
							parent[t[i]]=x;	
							//cout<<g<<endl;
							pqf.DecreasePriority(g,cost + edgeWeight(x,t[i]));
							
											
						}
					}
						
						//cout<<"####"<<endl;
					}	
				}
				//cout<<x->toString()<<"  "<<cost<<"  "<<pqf.top().second->toString()<<endl;
			}
			
		}
		if(flag==0){
			return NULL;
		}
		else{
			int i,j;
			j=finali->size()-1;
			for( i=0;i<finali->size();i++){
				Vertex* x=finali->at(j);
				finalo->push_back(x);
				j--;
			}
			return finalo;
		}
	}
	//TODO
	//return set of vertex pointers that make up the minimum weight path from v1 to v2
	//if no path exists, return NULL
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
	vector<Vertex*>* finali=new vector<Vertex*>;
	vector<Vertex*>* finalo=new vector<Vertex*>;
	if(isReachable(v1,v2)==false){
		return NULL;
	}
	else{
		map<Vertex*,bool> h;
		map<Vertex*,Vertex*> parent;
		queue<Vertex*> a;
		int flag=0;
		a.push(v1);
		h[v1]=1;
		parent[v1]=NULL;
		
		while(a.empty()==false && flag==0){
			Vertex* x=a.front();
			if(x==v2){
				
				Vertex* io=v2;
				Vertex *p=parent[io];
				finali->push_back(io);
				
				while(io!=v1){
					finali->push_back(p);
					io=p;
					p=parent[io];
				}
				//finali->push_back(io);
				flag=1;
			}
			else{
				
				a.pop();
				//vector<Vertex*> t=neighbors(x);
				vector<Vertex*> t;
				if(isDirected()==true){
					for(int i = 0; i < adjacencyList->at(x)->size(); i++){
						if(adjacencyList->at(x)->at(i)->getSource() == x){
							t.push_back(adjacencyList->at(x)->at(i)->getDestination());
						}
					}
				}
				else{
					t=neighbors(x);
				}
				for(int i=0;i<t.size();i++){
					bool z=h[t[i]];
					if(z!=1){
						a.push(t[i]);
						h[t[i]]=1;
						parent[t[i]]=x;
					}	
				}
			}
		}
		if(flag==0){
			return NULL;
		}
		else{
			int i,j;
			j=finali->size()-1;
			for( i=0;i<finali->size();i++){
				Vertex* x=finali->at(j);
				finalo->push_back(x); 
				j--;
			}
			return finalo;
		}
	}
	
	//TODO
	//return set of vertex pointers that make up the shortest path from v1 to v2
	//if no path exists, return NULL
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
