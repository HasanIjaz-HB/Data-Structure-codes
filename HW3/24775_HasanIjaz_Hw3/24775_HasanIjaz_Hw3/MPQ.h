
#ifndef MPQ_h
#define MPQ_h

#include <vector>
using namespace std;


struct MPQitem{
	int value;
	int label;
	/*MPQitem(int x,int y)
	{
		value = x;
		label = y;
	}*/
};


class BinaryHeap
{
public:
	 BinaryHeap(int capacity)//heap constructor
		: array(capacity + 1), locations(capacity + 1), currentSize{ 0 }
	 { //since we create a node at the next available position do we really need to initialize?
		 /*for (int i = 1; i < capacity; i++)
		 {
			 MPQitem tmp(-10,0);
			 array[i] = tmp;
			 locations[i] = 0;
		 }*/
	 }

	~BinaryHeap() {}//heap destructor

	void insert(const int & value, const int & label)//inserting both value and location for element in heap array
	{
		int hole = ++currentSize;

		for (; hole > 1 && value > array[hole / 2].value; hole /= 2) {
			array[hole].value = array[hole / 2].value;
			array[hole].label = array[hole / 2].label;
			locations[array[hole].label] = hole;
		}
		array[hole].value = value;
		array[hole].label = label;
		locations[array[hole].label] = hole;//checking the condition mentioned in hw file

	}



	int remove(int & label)
	{//deleting the element at the given label from array and setting it's label to 0 so that it's not considered a part of the heap which starts from index 1
		int value = -10;
		if (!isEmpty() || locations[label] > 0) {
			value = array[locations[label]].value;//getting value from the conditioned given in hw file

			array[locations[label]].value = array[currentSize].value;//setting the value and label of to be deleted item to the last item's value and label as done for deleting MIN
			array[locations[label]].label = array[currentSize].label;
			currentSize--; //decrementing size
			percolateDown(locations[label]);//bubbling down in order to maintain heap sort and order property
			locations[label] = 0;
		}
		return value; //returning the value
	}

	bool isEmpty() const { //checking if the heap is empty
		return currentSize == 0;
	}

	const int  GetMax() const {//getting the max value stores at index 1 of heap array unless heap is empty then return 0
		if (isEmpty())
			return 0;
		return array[1].value;
	}


private:
	int currentSize; // Size of heap (Number of elements in heap

	vector<MPQitem> array;   // The heap array
	vector<int> locations;	// The second array for keeping locations

	void percolateDown(int hole)
	{	//copied from slides and the part to include labels has been added
		/**
		* Internal method to percolate down in the heap.
		* hole is the index at which the percolate begins.
		*/
		int child;
		int tmpv = array[hole].value; // tmp is the item that will
		int tmpl = array[hole].label;
		// be percolated down

		for (; hole * 2 <= currentSize; hole = child) {

			child = hole * 2;

			if (child != currentSize && array[child + 1].value > array[child].value)
				child++;  // child is the minimum of the children

			if (array[child].value > tmpv) {

				array[hole].value = array[child].value; // swap hole and min child
				array[hole].label = array[child].label;
				locations[array[hole].label] = hole;
			}
			else
				break;
		}
		array[hole].value = tmpv; // place tmp in its final position
		array[hole].label = tmpl;
		locations[array[hole].label] = hole;
	}

};

#endif