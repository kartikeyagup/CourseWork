// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#ifndef DEQUEADT_H
#define DEQUEADT_H

/**
 * Interface Deque represents an abstract data type (ADT) for a double-ended queue.
 * A deque allows efficient insertion and removal at its front and back, combining
 * many of the benefits of stacks and queues into a single collection.
 *
 * Classes implementing Deque are generally expected to provide the operations
 * below in O(1) constant amortized runtime, except for the toString and clear
 * operations.
 */

template <class value_type>
class DequeADT {
	public :
		// push_front pushes an element to the front of the deque
        virtual void push_front (const value_type& val) = 0;

		// push_back pushes an emelemt to the back of the deque
        virtual void push_back (const value_type& val) = 0;

		// Clears the deque completely.
        virtual void clear() = 0;

		// returns 0 or 1 depending on whether the deque is empty or no
        virtual bool empty() = 0;

		//return the front most element from the deque
        virtual value_type front() = 0;

		//returns the elst elemt of the deque
        virtual value_type back() = 0;

		//returns the element at the ith index in the deque
        virtual value_type at(int index) = 0;

		//pops an element from the front of the deque
        virtual void pop_front() = 0;

		//pops an element from the back of the deque
        virtual void pop_back() = 0;

		//returns the number of elements in the deque
        virtual int size() = 0;

		/** @see Homework spec for details */
		/*virtual void print() = 0;*/
};

#endif
