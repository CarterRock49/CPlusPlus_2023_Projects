
#include "HashTable.h"

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	copyTable(other);
}

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if (this != &other) {
		clear();
		copyTable(other);
	}
	return *this;
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	delete[] dataTable;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int index = newDataItem.hash(newDataItem.getKey()) % tableSize;
	dataTable[index].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	int index = DataType::hash(deleteKey) % tableSize;
	return dataTable[index].remove(deleteKey);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	int index = DataType::hash(searchKey) % tableSize;
	return dataTable[index].retrieve(searchKey, returnItem);
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for (int i = 0; i < tableSize; i++) {
		dataTable[i].clear();
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for (int i = 0; i < tableSize; i++)
	{
		if (!dataTable[i].isEmpty())
		{
			return false;
		}
	}
	return true;
}

#include "show10.cpp"

template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
 	// not yet implemented
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{
	tableSize = source.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	for (int i = 0; i < tableSize; ++i)
	{
		dataTable[i] = source.dataTable[i];
	}
}
