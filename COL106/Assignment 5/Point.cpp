// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#include "Point.h"

Point::Point(int r, int c)
{
	row = r;
	column = c;
}

int Point::getRow() const
{
	return row;
}

int Point::getColumn() const
{
	return column;
}

void Point::setRow(int r)
{
	row = r;
}

void Point::setColumn(int c)
{
	column = c;
}

bool Point::isEqual(Point pt)
{
	return (this->row == pt.row && this->column == pt.column);
}

bool Point::isNeighbor(Point pt)
{
	//NOTE : maze boundaries not being checked here!!!

	//is right neighbor
	if(this->row == pt.row && this->column == pt.column - 1)
	{
		return true;
	}

	//is left neighbor
	if(this->row == pt.row && this->column == pt.column + 1)
	{
		return true;
	}

	//is top neighbor
	if(this->row == pt.row - 1 && this->column == pt.column)
	{
		return true;
	}

	//is bottom neighbor
	if(this->row == pt.row + 1 && this->column == pt.column)
	{
		return true;
	}

	return false;
}

std::string Point::toString()
{
	std::string str;
	str += "(";
	str += row;
	str += ",";
	str += column;
	str += ") ";
	return str;
}

int Point::distanceFrom(Point pt) const
{
	int x = this->column - pt.column;
	if(x < 0)
	{
		x *= -1;
	}
	int y = this->row - pt.row;
	if(y < 0)
	{
		y *= -1;
	}
	return (x+y);
}

void Point::print()
{
	std::cout << "(" << getRow() << ", " << getColumn() << ") ";
}
