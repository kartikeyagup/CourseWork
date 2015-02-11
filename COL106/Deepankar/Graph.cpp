#include "Graph.h"

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<stack>
#include"FacebookVertex.h"

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
	//TODO
stack<Vertex*> stackk;
int flag = 0 ;
map<Vertex*, bool> tabb;
vector<Vertex*>neigh ;
stackk.push(v1) ;
Vertex* v ;
while(!stackk.empty()){
        v = stackk.top() ;
        stackk.pop() ;
        tabb[v] = true ;
        if(v == v2){
                flag = 1 ;
                break ;
        }
        else {
                neigh = neighbors(v) ;
                for(int i = 0 ; i < neigh.size() ; i++){
                        if(!tabb[neigh[i]]){
                                stackk.push(neigh[i]);
                                tabb[neigh[i]] = true ;
                         }
                }
        }
        }
        if(flag==1){
                return true ;
        }
        else{
                return false ;
        }
}

bool Graph::isWeighted()
{
	return weighted;
}


vector<Vertex*>* Graph::minimumWeightPath(Vertex* v1, Vertex* v2)	// Dijkstra's algorithm
{
//TODO
//return set of vertex pointers that make up the minimum weight path from v1 to v2
//if no path exists, return NULL

if(isReachable(v1,v2)){

vector<Vertex*> allver = *vertices();
pair<Vertex*,int> distances[allver.size()] ; //works as heap
map<Vertex*,Vertex*> paths;
vector<Vertex*> nhb ;
vector<Vertex*>* ans = new  vector<Vertex*> ;
map<Vertex*,pair<int,int> > refrence ;
//vector<pair<Vertex*,int> > visited ;
/*for(int i = 0 ; i < allver.size();i++){
	distances[i] = pair<Vertex*,int> (allver[i],INT_MAX) ;
	refrence[allver[i]].first = i ;
	refrence[allver[i]].second = 0 ;
}
*/

Vertex* v = v1;
int siz = 0 ;
int smalldis = 0 ;

/*push v1 in heap*/
distances[siz++] = pair<Vertex*,int> (v1,0) ;
refrence[distances[siz-1].first].second = 1 ;

//percolate up
       int x = refrence[distances[siz-1].first].first ; pair<Vertex*,int> temp,child1,child2 ;
       if(x != 0) {while(distances[(x-1)/2].second > distances[x].second){
	    temp = distances[x] ;
            distances[x] = distances[(x-1)/2]  ;
            refrence[distances[x].first].first = x ;
            distances[(x-1)/2] = temp  ;
            refrence[distances[(x-1)/2].first].first = (x-1)/2 ;
            if( x-1 > 0){
                 x = (x-1)/2 ;
            }
			else{
				break;
			}
      }}
while(siz){
	v = distances[0].first ;
	smalldis = distances[0].second ;
	refrence[distances[0].first].second = 2 ;
	distances[0] = distances[siz-1] ;//pop from distances
	refrence[distances[0].first].first = 0 ;
	        x = 0 ;//Point child1;Point child2;Point temp;
            	while(1) {
 	        	    if(2*x+1 >= siz){
 	                             break ;
 		            }
			    else if(2*x+2 >= siz){
				temp = distances[x] ;
				child1 = distances[2*x+1] ;
				if( distances[x].second>child1.second){
					distances[x] = child1 ;
					refrence[distances[x].first].first = x ;
					child1 = temp ;
					refrence[distances[2*x+1].first].first = 2*x+1 ;
					x = 2*x+1 ;
				}
				else{ break ;}
			    }
			    else{
					child1 = distances[2*x+1] ;
                      			child2 = distances[2*x+2] ;
					temp = distances[x] ;
                                if( child1.second > child2.second){
									if(temp.second > child2.second){
                                        					distances[x] = child2 ;
					                                        refrence[distances[x].first].first = x ;
                                        					x =  2*x+2 ;
										distances[x] = temp ;
										refrence[distances[x].first].first = x ;
									}
									else { break ;}
                                }
                                else {
	                    	         if(temp.second > child1.second){           
										distances[x] = child1 ;	
										refrence[distances[x].first].first = x ;
                                    						x = 2*x+1 ;
										distances[x] = temp ;
										refrence[distances[x].first].first = x ;
									}
									else { break ;}
                                }
				 	}
               }
                
	  
	 siz-- ;//pop from distances
	nhb = neighbors(v);
	for(int i=0;i < nhb.size();i++){
		if(refrence[nhb[i]].second == 1 && distances[refrence[nhb[i]].first].second > (smalldis + edgeWeight(v,nhb[i]))){
			distances[refrence[nhb[i]].first].second = smalldis + edgeWeight(v,nhb[i]) ;
			//percolateup + update in map (refrence)
	        x = refrence[nhb[i]].first ;
       		while(distances[(x-1)/2].second > distances[x].second){
		    temp = distances[x] ;
	            distances[x] = distances[(x-1)/2]  ;
		    refrence[distances[(x-1)/2].first].first = x ;
        	    distances[(x-1)/2] = temp  ;
	            refrence[distances[x].first].first = (x-1)/2 ;
    	        if( x-1 > 0){
        	         x = (x-1)/2 ;
	            }
				else{
					break;
				}
      		}
			paths[nhb[i]] = v ;
		}
	
		else if(refrence[nhb[i]].second == 0 ){
			distances[siz++] = pair<Vertex*,int> (nhb[i],smalldis + edgeWeight(v,nhb[i])) ;
			refrence[nhb[i]].first = siz-1 ;
			refrence[nhb[i]].second = 1 ;
		//percolateup + update in map (refrence)
	        x = refrence[nhb[i]].first ;
       		while(distances[(x-1)/2].second > distances[x].second){
		    temp = distances[x] ;
	            distances[x] = distances[(x-1)/2]  ;
		    refrence[distances[(x-1)/2].first].first = x ;
        	    distances[(x-1)/2] = temp  ;
	            refrence[distances[x].first].first = (x-1)/2 ;
    	        if( x-1 > 0){
        	         x = (x-1)/2 ;
	            }
				else{
					break;
				}
      		}
			paths[nhb[i]] = v ;
		}
	
}
}
v = v2 ;
ans->push_back(v2) ;
while(v != v1){ 
ans->push_back(paths[v]);
cout << v->toString() <<endl;
v = paths[v] ;
cout << v->toString() <<endl;
}
return ans ;
}
else{ 
	return NULL;
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



vector<Vertex*>* Graph::shortestPath(Vertex* v1, Vertex* v2)        // BFS
{
        //TODO
        //return set of vertex pointers that make up the shortest path from v1 to v2
        //if no path exists, return NULL
queue<Vertex*> que ;
vector<Vertex*>* path = new vector<Vertex*>  ;
int flag = 0 ;
map<Vertex* , bool> table;
map<Vertex* , Vertex*> jumps ;
vector<Vertex*>neigh ;
que.push(v1) ;
Vertex* v ;
while(!que.empty()){
        v = que.front() ;
        que.pop() ;
        table[v] = true ;
        if(v == v2){
                flag = 1 ;
                break ;
        }
        else {
                neigh = neighbors(v) ;
                for(int i = 0 ; i < neigh.size() ; i++){
                        if(!table[neigh[i]]){
                                que.push(neigh[i]);
                                table[neigh[i]] = true ;
                                jumps[neigh[i]] = v ;
                        }
                }
        }
        }
        if(flag==1){
               path->push_back(v2) ;
                while(v != v1){
                        path->push_back(jumps[v]);
                        v = jumps[v] ;
                }
                return path ;
        }
        else{
                return NULL ;
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
