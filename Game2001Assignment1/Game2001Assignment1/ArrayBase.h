#pragma once
#define _ARRAYBASE_H
#include <cstring>
#include <iostream>

template<class valueType>
class ArrayBase
{
protected:
	valueType* m_pArray;
	int m_maxSize;
	int m_growSize;
	int m_numElements;
	bool growArray();

public:
	ArrayBase(int maxSize = 0, int growSize = 2);
	virtual ~ArrayBase();

	virtual void push(valueType value);
	void pop();
	virtual int find(valueType value) = 0;
	void erase();
	void printArray();



	int getSize() { return m_numElements; }
	int getmaxSize() { return m_maxSize; }
	int getgrowSize() { return m_growSize; }
	void setgrowSize(int growSize);


	valueType& operator[](int iIdx);

};

template<class valueType>
ArrayBase<valueType>::ArrayBase(int maxSize, int growSize)
	:m_pArray(nullptr), m_maxSize(0), m_growSize(0), m_numElements(0)
{
	if (maxSize != 0)
	{
		m_maxSize = maxSize;
		m_pArray = new valueType[m_maxSize];
		memset(m_pArray, 0, sizeof(valueType) * m_maxSize);

		m_growSize = (growSize > 0) ? growSize : 0;
	}
}

template<class valueType>
ArrayBase<valueType>::~ArrayBase()
{
	if (m_pArray != nullptr)
	{
		delete[] m_pArray;
		m_pArray = nullptr;
	}
}

template<class valueType>
void ArrayBase<valueType>::push(valueType value)
{


	if (m_numElements >= m_maxSize)
	{
		growArray();
	}

	m_pArray[m_numElements] = value;
	++m_numElements;
}

template<class valueType>
void ArrayBase<valueType>::pop()
{
	if (m_numElements > 0)
	{
		--m_numElements;
	}
}

template<class valueType>
valueType& ArrayBase<valueType>::operator[](int iIdx)
{
	return m_pArray[iIdx];
}


template<class valueType>
void ArrayBase<valueType>::erase()
{
	m_numElements = 0; //resets the array and sets array size and growth size back to 0
	m_maxSize = 0;
	m_growSize = 0;
}

template<class valueType>
void ArrayBase<valueType>::setgrowSize(int growSize)
{
	m_growSize = growSize;
}

template<class valueType>
void ArrayBase<valueType>::printArray()
{
	std::cout << "Current Array Stats... \n" << "MaxSize: " << m_maxSize << " " << "GrowSize: " << m_growSize << " " << "NumElements: " << m_numElements << "\n";

	for (int i = 0; i < m_numElements; ++i)
	{
		std::cout << m_pArray[i] << " ";
	}
	std::cout << "\n\n";
}

template<class valueType>
bool ArrayBase<valueType>::growArray()
{
	if (m_growSize <= 0)
	{
		return false;
	}

	valueType* pTemp = new valueType[m_maxSize + m_growSize];


	memcpy(pTemp, m_pArray, sizeof(valueType) * m_maxSize);

	delete[] m_pArray;
	m_pArray = pTemp;

	m_maxSize += m_growSize;
	m_growSize = m_growSize << 1;
	return true;
}