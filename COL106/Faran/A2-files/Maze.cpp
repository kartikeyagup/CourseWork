// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.


#include "Maze.h"
#include "misc.h"

Maze::Maze(string filename) {

	fstream f;
	char buf[5];
	string sbuf;

	f.open(filename.data(), ios::in);
	if(f == NULL)
	{
		string err_msg;
		err_msg += "opening ";
		err_msg += filename;
		err_msg += " : FAILED!";
		printAndExit(err_msg);
	}

	//read number of columns
	f >> buf;
	numColumns = atoi(buf);

	//read number of rows
	f >> buf;
	numRows = atoi(buf);

	squares = new char*[numRows];
	visited = new bool*[numRows];
	for(int i = 0; i < numRows; i++)
	{
		squares[i] = new char[numColumns];
		visited[i] = new bool[numColumns];
	}

	getline(f, sbuf);
	for(int i = 0; i < numRows; i++)
	{
		getline(f, sbuf);
		for(int j = 0; j < numColumns; j++)
		{
			squares[i][j] = sbuf[j];
			if(squares[i][j] == Maze::START)
			{
				start.setRow(i);
				start.setColumn(j);
			}
			if(squares[i][j] == Maze::END)
			{
				end.setRow(i);
				end.setColumn(j);
			}

			if(squares[i][j] == Maze::VISITED)
				visited[i][j] = true;
			else
				visited[i][j] = false;
		}
	}

	f.close();
}

void Maze::print()
{
	cout << "numRows = " << numRows << "\t\tnumColumns = " << numColumns << endl;

	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			cout << squares[i][j] << " ";
		}
		cout << endl;
	}

	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
}

int Maze::getNumRows()
{
	return numRows;
}

int Maze::getNumColumns()
{
	return numColumns;
}

Point Maze::getStartPoint()
{
	return start;
}

Point Maze::getEndPoint()
{
	return end;
}

bool Maze::isInBounds(Point pt)
{
	if(pt.getRow() >= 0 && pt.getRow() < numRows && pt.getColumn() >= 0 && pt.getColumn() < numColumns)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Maze::isEndPoint(Point pt)
{
	if(pt.getRow() == end.getRow() && pt.getColumn() == end.getColumn())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Maze::isVisited(Point pt)
{
	checkIndices(pt);
	return isInBounds(pt) && visited[pt.getRow()][pt.getColumn()];
}

void Maze::setVisited(Point pt)
{
	checkIndices(pt);
	if(isInBounds(pt))
		visited[pt.getRow()][pt.getColumn()] = true;
}

void Maze::clearVisited()
{
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			visited[i][j] = false;
		}
	}
}

bool Maze::isWall(Point pt)
{
	checkIndices(pt);
	return isInBounds(pt) && squares[pt.getRow()][pt.getColumn()] == Maze::WALL;
}

bool Maze::isOpen(Point pt)
{
	checkIndices(pt);
	return isInBounds(pt) && squares[pt.getRow()][pt.getColumn()] == Maze::OPEN;
}

void Maze::checkIndices(Point pt)
{
	if(!isInBounds(pt))
	{
		string err_msg;
		err_msg += "bad indices : row = ";
		err_msg += pt.getRow();
		err_msg += ", column = ";
		err_msg += pt.getColumn();
		printAndExit(err_msg);
	}
}
