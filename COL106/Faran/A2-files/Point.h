// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
	private :
		int row;
		int column;
	public :
		Point() {}
		Point(int r, int c);
		int getRow();
		int getColumn();
		void setRow(int r);
		void setColumn(int c);
		bool isEqual(Point pt);
		bool isNeighbor(Point pt);
		std::string toString();
		int distanceFrom(Point pt);
};

#endif
