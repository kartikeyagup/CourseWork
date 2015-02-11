
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
	Point a = maze->getEndPoint();
	Point b = maze->getStartPoint();
	if (a.isEqual(b))
	{
		maze->setVisited(b);
	}
	else
	{
		Point z = Point(b.getRow(), b.getColumn() - 1);
		Point w = Point(b.getRow(), b.getColumn() + 1);
		Point x = Point(b.getRow() - 1, b.getColumn());
		Point y = Point(b.getRow() + 1, b.getColumn());
		{
			if (maze->isInBounds(x))
			{
				if (x.distanceFrom(a) > b.distanceFrom(a))
					dq->push_back(x);
				else	
					dq->push_front(x);
			}
		}
		{
			if (maze->isInBounds(y))
			{
				if (y.distanceFrom(a) > b.distanceFrom(a))
					dq->push_back(y);
				else
					dq->push_front(y);
			}
		}
		{
			if (maze->isInBounds(z))
			{
				if (z.distanceFrom(a) > b.distanceFrom(a))
					dq->push_back(z);
				else
					dq->push_front(z);
			}
		}
		{
			if (maze->isInBounds(w))
			{
				if (w.distanceFrom(a) > b.distanceFrom(a))
					dq->push_back(w);
				else
					dq->push_front(w);
			}
		}
		while (!dq->empty())
		{
			Point m = dq->front();
			if (m.isEqual(a))
			{
				break;
			}
			else if ((maze->isVisited(m)) || (maze->isWall(m)))
			{
				dq->pop_front();
			}
			else
			{
				maze->setVisited(m);
				dq->pop_front();
				Point r = Point(m.getRow(), m.getColumn() - 1);
				Point s= Point(m.getRow(), m.getColumn() + 1);
				Point p = Point(m.getRow() - 1, m.getColumn());
				Point q = Point(m.getRow() + 1, m.getColumn());
				{

					if (maze->isInBounds(p))
					{
						if (p.distanceFrom(a) > m.distanceFrom(a))
							dq->push_back(p);
						else
							dq->push_front(p);
					}
				}
				{
					if (maze->isInBounds(q))
					{	
						if (q.distanceFrom(a) > m.distanceFrom(a))
							dq->push_back(q);
						else
							dq->push_front(q);
					}
				}
				{
					if (maze->isInBounds(r))
					{
						if (r.distanceFrom(a) > m.distanceFrom(a))
							dq->push_back(r);
						else
							dq->push_front(r);
					}
				}
				{
					if (maze->isInBounds(s))
					{
						if (s.distanceFrom(a) > m.distanceFrom(a))
							dq->push_back(s);
						else
							dq->push_front(s);
					}
				}

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
