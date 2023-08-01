
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
    maxSize = maxNumber;
    front = 0;
    back = 0;
    DataType* arrayqueue = new DataType[maxSize];
}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other)
{
    maxSize = other.maxSize;
    front = other.front;
    back = other.back;
    DataType* arrayqueue = new DataType[maxSize];
    for (int i = 0; i < maxSize; i++) {
        arrayqueue[i] = other.arrayqueue[i];
    }
}

template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other)
{
    for (int i = 0; i < maxSize; i++) {
        arrayqueue[i] = other.arrayqueue[i];
    }
    return this;
}

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
    delete[] arrayqueue;
}


template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
    try {
        if (back + 1 == front) {
            cout << "\nQueue is full\n";
        } else {
            arrayqueue[back] = newDataItem;
            back++;
        }
    }catch(logic_error){
        if (front == 0) {
            cout << "\nQueue is full\n";
        } else {
            back = 0;
            arrayqueue[back] = newDataItem;
            back++;
        }
    }
}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
	DataType temp;
    try {
        if (isEmpty()) {
            cout << "/nqueue is already empty/n";
        } else {
            temp = arrayqueue[front];
            front++;
        }
    } catch(logic_error) {
        front = 0;
        if (isEmpty()) {
            cout << "/nqueue is already empty/n";
        }
        else {
            temp = arrayqueue[front];
            front++;
        }
        return temp;
    }
	return temp;
}

template <typename DataType>
void QueueArray<DataType>::clear()
{
    front = 0;
    back = 0;
    //by setting the front and back to 0 again the enqueue function will overwrite any previous data as needed
}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
    return (front == back);
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
    return (back + 1 == front) || (back == maxSize && front == 0);
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
    arrayqueue[front] = newDataItem;
}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
	DataType temp;
    temp = arrayqueue[back];
	return temp;
}

template <typename DataType>
int QueueArray<DataType>::getLength() const
{
	return maxSize;
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const 
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if ( front == -1 )
       cout << "Empty queue" << endl;
    else
    {
       cout << "Front = " << front << "  Back = " << back << endl;
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       if ( back >= front )
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) && ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       else
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) || ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       cout << endl;
    }
}