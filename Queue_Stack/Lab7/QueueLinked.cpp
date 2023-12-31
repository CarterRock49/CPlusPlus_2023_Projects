
#include "QueueLinked.h"

template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber = Queue<DataType>::MAX_QUEUE_SIZE)
{
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
}

template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	DataType temp;
	return temp;
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	return false;
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	DataType temp;
	return temp;
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}