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
	// (Comments are intentionally omitted from these abstract method headings,
	//  because we want you to write comments for these methods in your own
	//  words in your ArrayDeque class.)
	
	public :
		/** @see Homework spec for details */
		virtual void push_front (const value_type& val) = 0;
	
		/** @see Homework spec for details */
		virtual void push_back (const value_type& val) = 0;
	
		/** @see Homework spec for details */
		virtual void clear() = 0;
	
		/** @see Homework spec for details */
		virtual bool empty() = 0;
	
		/** @see Homework spec for details */
		virtual value_type front() = 0;
	
		/** @see Homework spec for details */
		virtual value_type back() = 0;
	
		/** @see Homework spec for details */
		virtual value_type at(int index) = 0;
	
		/** @see Homework spec for details */
		virtual void pop_front() = 0;
	
		/** @see Homework spec for details */
		virtual void pop_back() = 0;
	
		/** @see Homework spec for details */
		virtual int size() = 0;
	
		/** @see Homework spec for details */
		/*virtual void print() = 0;*/
};

#endif
