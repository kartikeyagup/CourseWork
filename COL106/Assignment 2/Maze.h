// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Point.h"

using namespace std;

class Maze {

	private :
		static const char START = 'S';
		static const char END = 'E';
		static const char WALL = '#';
		static const char OPEN = ' ';
		static const char VISITED = '.';

		int numColumns;
		int numRows;
		char** squares;
		bool** visited;
		Point start;
		Point end;

		void checkIndices(Point pt);

	public :
		Maze(string filename);
		void print();

		int getNumRows();
		int getNumColumns();
		Point getStartPoint();
		Point getEndPoint();

		bool isInBounds(Point pt);
		bool isEndPoint(Point pt);
		bool isVisited(Point pt);
		void setVisited(Point pt);
		void clearVisited();
		bool isWall(Point pt);
		bool isOpen(Point pt);
};

#endif
