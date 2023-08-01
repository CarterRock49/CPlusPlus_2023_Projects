
#include "StackArray.h"

template <typename DataType>
StackArray<DataType>::StackArray(int maxNumber)
{
	maxSize = maxNumber;
	top = -1;
	DataType* arraystack = new DataType[maxSize];
}

template <typename DataType>
StackArray<DataType>::StackArray(const StackArray& other)
{
	maxSize = other.maxSize;
	top = -1;
	DataType* arraystack = new DataType[maxSize];
}

template <typename DataType>
StackArray<DataType>& StackArray<DataType>::operator=(const StackArray& other)
{
	for (int i = 0; i < maxSize; i++) {
		arraystack[i] = other.arraystack[i];
	}
	return this;
}

template <typename DataType>
StackArray<DataType>::~StackArray()
{
	delete[] arraystack;
}

template <typename DataType>
void StackArray<DataType>::push(const DataType& newDataItem) throw (logic_error)
{
	try {
		top++;
		arraystack[top] = newDataItem;
	} catch(logic_error) {
		cout << "\nStack overflow\n";
	}
}

template <typename DataType>
DataType StackArray<DataType>::pop() throw (logic_error)
{
	DataType temp;
	try {
		temp = arraystack[top];
		top--;
		/*
		Removes the most recently added (top) data item from the stack 
		and returns the value of the deleted item.

		I think that moving the top down is basically the same as deleting an element
		since the next time a push happens the value that was the top will be overwriten.
		*/
	}
	catch (logic_error) {
		cout << "\nStack underflow\n";
	}
	return temp;
}

template <typename DataType>
void StackArray<DataType>::clear()
{
	top = -1;
	/*
	moving the top to 0 should basically be the same a removing all the items since 
	whenever an item is added it will overwrite the previous ones
	*/
}

template <typename DataType>
bool StackArray<DataType>::isEmpty() const
{
	return top == -1;
}

template <typename DataType>
bool StackArray<DataType>::isFull() const
{
	return top == maxSize;
}

template <typename DataType>
void StackArray<DataType>::showStructure() const 

// Array implementation. Outputs the data items in a stack. If the
// stack is empty, outputs "Empty stack". This operation is intended
// for testing and debugging purposes only.

{
    if( isEmpty() ) {
	cout << "Empty stack." << endl;
    }
    else {
	int j;
	cout << "Top = " << top << endl;
	for ( j = 0 ; j < maxSize ; j++ )
	    cout << j << "\t";
	cout << endl;
	for ( j = 0 ; j <= top  ; j++ )
	{
	    if( j == top )
	    {
	        cout << '[' << dataItems[j] << ']'<< "\t"; // Identify top
	    }
	    else
	    {
		cout << dataItems[j] << "\t";
	    }
	}
	cout << endl;
    }
    cout << endl;
}