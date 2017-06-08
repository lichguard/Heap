#pragma once
#define Array_Offset -1

template<class T>
class MinHeap
{
	//define heap characteristics that uses Nodes
	template<class T>
	struct Node
	{
		int key; T* data;
	};

	Node<T> *arr;	  //the array that hold the values
	int size;	  //number of elements currently in the heap
	int capacity; //maximum size can reach

public:
	//allocate memory for a new heap - O(1)
	MinHeap(int capacity) : capacity(capacity), size(0), arr(new Node<T>[capacity])
	{
	}

	//delete allocated memory - O(1)
	~MinHeap()
	{
		delete[] this->arr;
	}

	//Call heapify siftdown or up - O(logk)
	void Heapify(int parent, int SIFTUP)
	{
		if (SIFTUP)
		{
			parent /= 2;
			if (!parent) return;
		}

		int left = parent * 2;
		int right = left + 1;

		// Exist(Left child) && Left child > parent  or   Exist(right child) && right child > parent
		if (((left <= this->size) && (this->arr[parent + Array_Offset].key > this->arr[left + Array_Offset].key)) ||
			((right <= this->size) && (this->arr[parent + Array_Offset].key > this->arr[right + Array_Offset].key)))
		{
			//determine which child to switch with the parent
			int childswap = ((right <= this->size) && this->arr[left + Array_Offset].key > this->arr[right + Array_Offset].key) ? right : left;

			//swap
			Node<T> tmp = this->arr[childswap + Array_Offset];
			this->arr[childswap + Array_Offset] = this->arr[parent + Array_Offset];
			this->arr[parent + Array_Offset] = tmp;

			Heapify(SIFTUP ? parent : childswap, SIFTUP);
		}
	}

	//Insert new element - O(logk)
	void InsertHeap(int key, T* data)
	{
		//prepare the new node - O(1)
		Node<T> newnode;
		newnode.key = key;
		newnode.data = data;
		//increase heap size by one  - O(1)
		this->size += 1;
		//now move the node into the heap - O(1)
		this->arr[this->size + Array_Offset] = newnode;
		//reduce heap size by 1 and call heapfiy from last element to root O(log(k))
		Heapify(this->size, 1);
	}

	int GetSize()
	{
		return size;
	}

	//Remove the root - O(logk)
	T* ExtractMin()
	{
		T* temp = this->arr[0].data;
		//overwrite the root with the last element - O(1)
		this->arr[0] = this->arr[this->size + Array_Offset];

		//reduce heap size by 1 and call heapfiy from root - down O(log(k))
		this->size -= 1;
		Heapify(1, 0);

		return temp;
	}

};
