all: Main.cpp Maze.cpp misc.cpp comparator.h PriorityQueueADT.h PriorityQueueSTL.cpp PriorityQueueArray.cpp Point.cpp
	g++ misc.cpp Point.cpp Maze.cpp Main.cpp  

test: comparator.h PriorityQueueADT.h Point.h Point.cpp PriorityQueueSTL.cpp PriorityQueueArray.cpp TestPriorityQueue.cpp
	g++ Point.cpp TestPriorityQueue.cpp 
	./a.out 1

clean:
	rm -rf *.out *.o
