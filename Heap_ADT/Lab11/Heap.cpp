
#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber = DEFAULT_MAX_HEAP_SIZE)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];

	for (int i = 0; i < size; ++i) {
		dataItems[i] = other.dataItems[i];
	}
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator= (const Heap& other)
{
	if (this != &other) {
		maxSize = other.maxSize;
		size = other.size;

		delete[] dataItems;
		dataItems = new DataType[maxSize];

		for (int i = 0; i < size; ++i) {
			dataItems[i] = other.dataItems[i];
		}
	}

	return *this;
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::~Heap()
{
	delete[] dataItems;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem)
throw (logic_error)
{
	if (isFull())
	{
		throw logic_error("Heap is full");
	}

	dataItems[size] = newDataItem;

	int curr = size;
	int parent = (curr - 1) / 2;

	while (curr > 0 && comparator(dataItems[curr].getPriority(), dataItems[parent].getPriority()))
	{
		swap(dataItems[curr], dataItems[parent]);
		curr = parent;
		parent = (curr - 1) / 2;
	}

	size++;
}

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Heap is empty");
	}
	DataType maxDataItem = dataItems[0];
	DataType lastDataItem = dataItems[--size];
	int index = 0;
	int childIndex = 2 * index + 1;
	while (childIndex < size) {
		if (childIndex + 1 < size && comp(dataItems[childIndex + 1].getPriority(), dataItems[childIndex].getPriority())) {
			++childIndex;
		}
		if (comp(lastDataItem.getPriority(), dataItems[childIndex].getPriority())) {
			break;
		}
		dataItems[index] = dataItems[childIndex];
		index = childIndex;
		childIndex = 2 * index + 1;
	}
	dataItems[index] = lastDataItem;
	return maxDataItem;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	return size == 0;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	return size == maxSize;
}

#include "show11.cpp"