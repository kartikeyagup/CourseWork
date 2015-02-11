// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>

class Point {
	private :
		int row;
		int column;
	public :
		Point() {}
		Point(int r, int c);
		int getRow() const;
		int getColumn() const;
		void setRow(int r);
		void setColumn(int c);
		bool isEqual(Point pt);
		bool isNeighbor(Point pt);
		std::string toString();
		int distanceFrom(Point pt) const;
		void print();
};

#endif
