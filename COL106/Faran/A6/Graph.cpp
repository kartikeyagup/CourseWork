#include "Graph.h"
#include <bits/stdc++.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<stack>
#include"FacebookVertex.h"
#include<unordered_map>
#include<vector>
#include<set>
//#define INT_MAX 32767

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
	//TODO
	stack<Vertex *> store;
	//vector<Vertex*> isvisited;
	unordered_map<Vertex *,bool> isvisited;
	unordered_map<Vertex *,Vertex *> path;
	//vector<Vertex*> path;
	//vector<Vertex*>* answer = new vector<Vertex*> ;
	//vector<Vertex*>* revanswer = new vector<Vertex*>;
	store.push(v1);
	//isvisited[(v1)] = 1;
	while (!store.empty())
	{
		Vertex *x = store.top();
		if(x == v2)
		{
			return true;
			/*
			Vertex *y = v2;
			while(y != v1)
			{
				revanswer->push_back(y);
				y = path[(y)];
			}
			revanswer->push_back(v1);
			for(int i = revanswer->size()-1;i>=0;i--)
			{
				answer->push_back(revanswer->at(i));
			}
			return answer;*/
		}
		else{
		store.pop();
		//x.isvisited[x] = true;  
		vector<Vertex *> xyz = neighbors(x);
		for(int i = 0 ; i < xyz.size() ; i++)
		{
			if(isvisited.find((xyz[i])) == isvisited.end())
			{
				store.push(xyz[i]);
				isvisited[(xyz[i])] = true;
				path[(xyz[i])] = x;
			}
			else if(isvisited[xyz[i]] == 0 )
			{
				store.push(xyz[i]);
				isvisited[(xyz[i])] = true;
				path[(xyz[i])] = x;
			}
			
		}
		}
	} 
	if (store.empty())
		return false;
	//TODO
	//return set of vertex pointers that make up the shortest path from v1 to v2
	//if no path exists, return NULL
	//return NULL;
}

bool Graph::isWeighted()
{
	return weighted;
}

vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{
	vector<Vertex*>* allvertices = vertices();
	unordered_map<Vertex *,int> distance;
	for (int i=0;i<allvertices->size();i++)
	{
		if (allvertices->at(i)==v1)
			distance[allvertices->at(i)] = 0;
		else
		{
			distance[allvertices->at(i)] = 300000;
		}
	}
	unordered_map<Vertex *,Vertex *> parent;
	unordered_map<Vertex *,bool> isvisited;
	set< pair<int,Vertex *> > heap;
	heap.insert(pair<int,Vertex *>(0,v1));
	while(!heap.empty())
	{
		pair<int,Vertex*> top = *(heap.begin());
		if(top.second == v2)
		{
			vector<Vertex *>* revanswer = new vector<Vertex *>;
			vector<Vertex *>* answer = new vector<Vertex *>;
			Vertex *y = v2;
			while(y != v1)
			{
				revanswer->push_back(y);
				y = parent[(y)];
			}
			revanswer->push_back(v1);
			for(int i = revanswer->size()-1;i>=0;i--)
			{
				answer->push_back(revanswer->at(i));
			}
			return answer;
		}
		heap.erase(heap.begin());
		isvisited[top.second] = 1;
		vector<Vertex *> xyz = neighbors(top.second);
		int s = xyz.size();
		for(int i = 0;i<s;i++)
		{
			if(isvisited.find(xyz[i]) == isvisited.end())
			{
				if(distance[xyz[i]]>distance[top.second]+edgeWeight(top.second,xyz[i]))
				{
					if(distance[xyz[i]] != 300000)
					{
						heap.erase(heap.find(pair<int,Vertex *>(distance[xyz[i]],xyz[i])));
					}
					distance[xyz[i]]=distance[top.second]+edgeWeight(top.second,xyz[i]);
					heap.insert(pair<int,Vertex *>(distance[xyz[i]],xyz[i]));
					parent[xyz[i]] = top.second;
				}

			}
		}
	}
	if (heap.empty())
	{
		return NULL;
	}
	return NULL;

	//TODO
	//return set of vertex pointers that make up the minimum weight path from v1 to v2
	//if no path exists, return NULL
	return NULL;
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
	queue<Vertex *> store;
	//vector<Vertex*> isvisited;
	unordered_map<Vertex *,bool> isvisited;
	unordered_map<Vertex *,Vertex *> path;
	//vector<Vertex*> path;
	vector<Vertex*>* answer = new vector<Vertex*> ;
	vector<Vertex*>* revanswer = new vector<Vertex*>;
	store.push(v1);
	isvisited[(v1)] = 1;
	while (!store.empty())
	{
		Vertex *x = store.front();
		if(x == v2)
		{
			Vertex *y = v2;
			while(y != v1)
			{
				revanswer->push_back(y);
				y = path[(y)];
			}
			revanswer->push_back(v1);
			for(int i = revanswer->size()-1;i>=0;i--)
			{
				answer->push_back(revanswer->at(i));
			}
			return answer;
		}
		else{
		store.pop();
		vector<Vertex *> xyz = neighbors(x);
		for(int i = 0 ; i < xyz.size() ; i++)
		{
			if(isvisited.find((xyz[i])) == isvisited.end())
			{
				store.push(xyz[i]);
				isvisited[(xyz[i])] = true;
				path[(xyz[i])] = x;
			}
			else if(isvisited[xyz[i]] == 0 )
			{
				store.push(xyz[i]);
				isvisited[(xyz[i])] = true;
				path[(xyz[i])] = x;
			}
			
		}
		}
	} 
	if (store.empty())
		return NULL;
	//TODO
	//return set of vertex pointers that make up the shortest path from v1 to v2
	//if no path exists, return NULL
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
