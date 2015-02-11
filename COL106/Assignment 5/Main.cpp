
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "PriorityQueueADT.h"
#include "PriorityQueueSTL.cpp"
#include "PriorityQueueArray.cpp"

using namespace std;

void solve(Maze * maze, PriorityQueueADT * pq);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

	cout << "COL 106 Maze Solver" << endl;
	cout << "===================" << endl;

	if(argc != 3 && argc != 4)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile> <priority-queue-type>" << endl;
		cout << "priority-queue-type = 0 for stl::priority-queue (Part A), priority-queue-type = 1 for user-defined priority-queue (Part B)" << endl;
		exit(1);
	}

        cout << endl << "input filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	Point destination = maze->getEndPoint();

	PriorityQueueADT * pq;
	if(atoi(argv[2]) == 0)
	{
		pq = new PriorityQueueSTL(&destination);
	}
	else
	{
		pq = new PriorityQueueArray(&destination);
	}	

	cout << endl << "solving maze .... " << endl;
	solve(maze, pq);

	maze->print();

	if(argc == 4)
	{
		cout << endl << "verifying solution .... " << endl;
		verifySolution(maze, argv[3]);
	}
}

void solve(Maze * maze, PriorityQueueADT * pq)
{
	Point ending=maze->getEndPoint();
	pq->push(maze->getStartPoint());
	bool solved=0;
	while ((pq->size()>0) && (solved!=1))
	{
		Point considered=pq->top();
		pq->pop();
		if (ending.isEqual(considered))
		{
			solved=1;
			maze->setVisited(considered);
		}
		else if ((maze->isVisited(considered)))
		{
			NULL;
		}
		else
		{
			maze->setVisited(considered);
			int r1=considered.getRow();
            int c1=considered.getColumn();
           	Point p1= Point(r1-1,c1);
           	if ((maze->isInBounds(p1)) && (maze->isWall(p1)!=1) && !(maze->isVisited(p1)))
           		pq->push(p1);
           	Point p2= Point(r1+1,c1);
           	if ((maze->isInBounds(p2)) && (maze->isWall(p2)!=1) && !(maze->isVisited(p2)))
           		pq->push(p2);
           	Point p3= Point(r1,c1-1);
           	if ((maze->isInBounds(p3)) && (maze->isWall(p3)!=1) && !(maze->isVisited(p3)))
           		pq->push(p3);
           	Point p4= Point(r1,c1+1);
           	if ((maze->isInBounds(p4)) && (maze->isWall(p4)!=1) && !(maze->isVisited(p4)))
           		pq->push(p4);
        }
	}
}

void verifySolution(Maze * maze, std::string path)
{
	Maze * correct_solution = new Maze(path);
	cout << maze->getNumRows() <<"\t"<<maze->getNumColumns()<<"\n";
	cout << correct_solution->getNumRows() <<"\t"<<correct_solution->getNumColumns()<<"\n";
	if(maze->getNumRows() != correct_solution->getNumRows() || maze->getNumColumns() != correct_solution->getNumColumns())
	{
		cout << "dimension mismatch between input and correct output mazes" << endl;
		exit(1);
	}

	for(int i = 0; i < maze->getNumRows(); i++)
	{
		for(int j = 0; j < maze->getNumColumns(); j++)
		{
			Point p;
			p.setRow(i);
			p.setColumn(j);
			if(maze->isVisited(p) != correct_solution->isVisited(p) && !p.isEqual(maze->getStartPoint()))
			{
				cout << "incorrect solution" << endl;
				cout << "mismatch at : (" << i << "," << j << ")" << endl;
				exit(0);
			}
		}
	}

	cout << "correct solution!" << endl;
}
