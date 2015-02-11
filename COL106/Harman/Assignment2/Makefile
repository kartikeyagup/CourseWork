all: Main.cpp Maze.cpp misc.cpp DequeADT.h DequeSTL.cpp DequeArray.cpp Point.cpp
	g++ misc.cpp Point.cpp DequeSTL.cpp DequeArray.cpp Maze.cpp Main.cpp  

test: DequeADT.h DequeSTL.cpp DequeArray.cpp TestDeque.cpp
	g++ DequeADT.h DequeSTL.cpp DequeArray.cpp TestDeque.cpp

clean:
	rm -rf *.out *.o
