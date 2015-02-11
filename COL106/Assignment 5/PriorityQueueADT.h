// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#ifndef PRIORITYQUEUEADT_H
#define PRIORITYQUEUEADT_H

#include "Point.h"

class PriorityQueueADT {
	
	public :

		/** @see Homework spec for details */
		virtual void push (const Point& val) = 0;
	
		/** @see Homework spec for details */
		virtual bool empty() = 0;
	
		/** @see Homework spec for details */
		virtual Point top() = 0;
	
		/** @see Homework spec for details */
		virtual void pop() = 0;
	
		/** @see Homework spec for details */
		virtual int size() = 0;
	
		/** @see Homework spec for details */
		/*virtual void print() = 0;*/
};

#endif
