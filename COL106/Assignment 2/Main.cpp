
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "DequeADT.h"
//#include "DequeSTL.h"
#include "DequeSTL.cpp"
#include "DequeArray.cpp"
//#include "MazeSolver.cpp"

using namespace std;

void solve(Maze * maze, DequeADT<Point> * dq);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

	cout << "COL 106 Maze Solver" << endl;
	cout << "===================" << endl;

	if(argc != 3 && argc != 4)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile> <deque-type>" << endl;
		cout << "deque-type = 0 for stl::deque (Section 1), deque-type = 1 for user-defined deque (Section 2)" << endl;
		exit(1);
	}

        cout << endl << "input filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	DequeADT<Point> * dq;
	if(atoi(argv[2]) == 0)
	{
		dq = new DequeSTL<Point>();
	}
	else
	{
		dq = new DequeArray<Point>();
	}

	cout << endl << "solving maze .... " << endl;
	solve(maze, dq);

	maze->print();

	if(argc == 4)
	{
		cout << endl << "verifying solution .... " << endl;
		verifySolution(maze, argv[3]);
	}
}

void solve(Maze * maze, DequeADT<Point> * dq)
{
    Point ending1=maze->getEndPoint();
    dq->push_front(maze->getStartPoint());
    bool solved=0;
    while ((dq->size()>0) && (solved!=1))
    {
        Point considered=dq->front();
        dq->pop_front();
        if (ending1.isEqual(considered))
        {
            solved=1;
        }
        else if ((maze->isVisited(considered)) || (maze->isWall(considered)))
        {
            2==2;
        }
        else
        {
            maze->setVisited(considered);
            int r1=considered.getRow();
            int c1=considered.getColumn();
            int d1=ending1.distanceFrom(considered);
            Point p1= Point(r1-1,c1);
            int d2=p1.distanceFrom(ending1);
            if (d2<d1)
            {
                if (maze->isInBounds(p1))
                {
                    dq->push_front(p1);
                }
            }
            else
            {
                if (maze->isInBounds(p1))
                dq->push_back(p1);
            }
            Point p2=Point(r1+1,c1);
            int d3=ending1.distanceFrom(p2);
            if (d3<d1)
            {
                if (maze->isInBounds(p2))
                dq->push_front(p2);
            }
            else
            {
                if (maze->isInBounds(p2))
                dq->push_back(p2);
            }
            Point p3= Point(r1,c1-1);
            int d4=ending1.distanceFrom(p3);
            if (d4<d1)
            {
                if (maze->isInBounds(p3))
                dq->push_front(p3);
            }
            else
            {
                if (maze->isInBounds(p3))
                dq->push_back(p3);
            }
            Point p4=Point(r1,c1+1);
            int d5=ending1.distanceFrom(p4);
            if (d5<d1)
            {
                if (maze->isInBounds(p4))
                dq->push_front(p4);
            }
            else
            {
                if (maze->isInBounds(p4))
                dq->push_back(p4);
            }
        }
    }
}

void verifySolution(Maze * maze, std::string path)
{
	Maze * correct_solution = new Maze(path);

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
