#pragma once
#define _ORDREDARRAY_H_
#include "ArrayBase.h"

template<class valueType>
class OrderedArray : public ArrayBase<valueType>
{
private:
	bool p_noDuplicate;

public:
	OrderedArray(int maxSize = 0, int growSize = 2, bool noDuplicate = true);
	virtual ~OrderedArray();

	virtual void push(valueType value) override;
	virtual int find(valueType value) override;
};

template<class valueType>
OrderedArray<valueType>::OrderedArray(int maxSize, int growSize, bool noDuplicate)
	:ArrayBase<valueType>(maxSize, growSize), p_noDuplicate(noDuplicate)
{

}
template<class valueType>
OrderedArray<valueType>::~OrderedArray()
{

}



template<class valueType>
int OrderedArray<valueType>::find(valueType value)
{
	int lowerBound = 0;
	int upperBound = this->m_numElements - 1;
	int mid = 0;

	while (1)
	{
		mid = (lowerBound + upperBound) >> 1;

		if (this->m_pArray[mid] == value) //triggers only if key is found in mid
		{
			return mid;
		}
		else if (lowerBound > upperBound) //triggers if no match is found
		{
			return -1;
		}
		else
		{
			if (this->m_pArray[mid] < value) //key is found in right array
			{
				lowerBound = mid + 1;
			}
			else //key is found in left array
			{
				upperBound = mid - 1;
			}
		}
	}

	return -1;
}

template<class valueType>
void OrderedArray<valueType>::push(valueType value)
{



	if (this->find(value) != -1) //checks if number going to be added is a duplicate
	{

		return;
	}

	if (this->m_numElements >= this->m_maxSize) //creates an empty space for the value
	{
		this->growArray();
	}

	//adds value into an empty space in the array
	int i, k;
	for (i = 0; i < this->m_numElements; ++i)
	{
		if (this->m_pArray[i] > value)
		{
			break;
		}
	}

	for (k = this->m_numElements; k > i; --k)
	{
		this->m_pArray[k] = this->m_pArray[k - 1];
	}
	this->m_pArray[i] = value;
	this->m_numElements++;
}