
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
   
	Point first=maze->getStartPoint();
    Point last=maze->getEndPoint();
    dq->push_front(first);

    while (dq->size()>0)
    {
 
        Point pt=dq->front();
		dq->pop_front();

        
        if ((maze->isVisited(pt))||(maze->isWall(pt)))
        {
            							// DO NOTHING
        }
        
        else if (last.isEqual(pt))
        {

		//maze->setVisited(last);
            break;  					//GOT THE END POINT
        }

        else
        {

            
            int originrow=pt.getRow();
             int origincolumn=pt.getColumn();
              int dist=last.distanceFrom(pt);
           
            Point up= Point(originrow-1,origincolumn);
             Point right=Point(originrow,origincolumn+1);
              Point left= Point(originrow,origincolumn-1);
                Point down=Point(originrow+1,origincolumn);

            
            int distup=last.distanceFrom(up);
             int distdown=last.distanceFrom(down);
              int distleft=last.distanceFrom(left);
                int distright=last.distanceFrom(right);

            
            if (distup<dist)
            {
                dq->push_front(up);
            }
            else
            {
                dq->push_back(up);
            }
            
           
            if (distdown<dist)
            {
                dq->push_front(down);
            }
            else
            {
                dq->push_back(down);
            }
            
           
            if (distleft<dist)
            {
                dq->push_front(left);
            }
            else
            {
                dq->push_back(left);
            }
            
         
            if (distright<dist)
            {
                dq->push_front(right);
            }
            else
            {
                dq->push_back(right);
            }
        
	    maze->setVisited(pt);
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
