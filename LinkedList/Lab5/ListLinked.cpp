
#include "ListLinked.h"

// ListNode member functions
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}

// List member functions

template <typename DataType>
List<DataType>::List(int ignored = 0)
{
	head = new ListNode<DataType>(ignored, NULL);
	cursor = head;
}

template <typename DataType>
List<DataType>::List(const List& other)
{
	head = other.head;
	cursor = other.cursor;
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	head = other.head;
	cursor = other.cursor;
	return this;
}

template <typename DataType>
List<DataType>::~List()
{
	clear();
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	head = new ListNode<DataType>(newDataItem, head);
	cursor = head;
}

template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	// not yet implemented
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
	this->dataItem = nodeData;
}

template <typename DataType>
void List<DataType>::clear()
{
	while (head != NULL) {
		head = head->next;
	}
}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
	if (head == NULL) {
		return true;
	}
	return false;
}

template <typename DataType>
bool List<DataType>::isFull() const
{
	if (head == NULL) {
		return false;
	}
	return true;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	cursor = head;
	while (cursor->dataItem != NULL) {
		cursor = cursor->next;
	}
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	cursor = head;
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	ListNode* cursor2;
	cursor2 = head;
	int count = 0;
	while (cursor2->dataItem != cursor->dataItem) {
		count++;
		cursor2 = cursor2->next;
	}
	if (cursor != head) {
		cursor = head;
		for (int i = 1; i < count; i++)
		{
			cursor = cursor->next;
		}
		return true;
	} else {
		return false;
	}
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if (cursor->dataItem != NULL) {
		cursor = cursor->next;
		return true;
	} else {
		return false;
	}
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	DataType t;
	t = cursor->dataItem;
	return t;
}

template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error)
{
	// not yet implemented
}

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	
}

#include "show5.cpp"

