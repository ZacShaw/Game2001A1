#pragma once
#include <cassert>
#include "ArrayBase.h"

/*template <class T>
class UnorderedArray
{
public:
	// Constructor
	UnorderedArray(int maxSize, int growSize = 1) :
		virtual ~UnorderedArray();
		m_array(NULL), m_maxSize(0),
		m_growSize(0), m_numElements(0)
	{
		if (size)
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];
			memset(m_array, 0, sizeof(T) * m_maxSize);

			m_growSize = ((growBy > 0) ? growBy : 0); // Ternary statement -- Glorified if-statement
		}
	}
	// Destructor
	~UnorderedArray()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}
	// Insertion
	// Fast insertion for unorderedarray -- Big-O of O(1)
	void push(T val)
	{
		assert(m_array != NULL); // Debugging purposes

		if (m_numElements >= m_maxSize)
		{
			Expand();
		}

		m_array[m_numElements] = val;
		m_numElements++;
	}
	// Deletion (2 methods)
	// Removes the last item that was inserted
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != NULL);

		if (index >= m_numElements)
		{
			return;
		}

		for (int i = index; i < m_numElements; i++)
		{
			if (i + 1 < m_numElements)
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}
	// Overload the [] operator
	T& operator[](int index)
	{
		assert(m_array != NULL && index < m_numElements);
		return m_array[index];
	}
	// Search (Linear search) -- Big-O = O(N)
	int find(T val)
	{
		assert(m_array != NULL);

		// Brute-force Search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
				return i;
		}
		return -1;
	}
	// ----------- SORTING ALGORITHMS ---------------
	// Bubble Sort -- BIG-O = O(N^2)
	void BubbleSort()
	{
		assert(m_array != NULL);

		T temp;

		for (int k = m_numElements - 1; k > 0; k--)
		{
			for (int i = 0; i < k; i++)
			{
				// Comparing 2 adjacent elements
				if (m_array[i] > m_array[i + 1])
				{
					// Swapping the elements
					temp = m_array[i];
					m_array[i] = m_array[i + 1];
					m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- BIG-O = O(N^2)
	void SelectionSort()
	{
		assert(m_array != NULL);

		T temp;
		int min = 0;

		// The lowest position to swap the smallest element to...
		for (int k = 0; k < m_numElements - 1; k++)
		{
			min = k;

			// Iterate through the array to find the smallest value
			for (int i = k + 1; i < m_numElements; i++)
			{
				if (m_array[i] < m_array[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}

			// Swapping of the lowest element with the lowest available index
			if (m_array[k] > m_array[min])
			{
				// Swap
				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- BIG-O = O(N^2)
	void InsertionSort()
	{
		assert(m_array != NULL);

		T temp;
		int i = 0;

		for (int k = 1; k < m_numElements; k++)
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an element
			// to be inserted in the correct location.
			while (i > 0 && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i - 1];
				i--;
			}

			m_array[i] = temp;
		}
	}
	// Merge Sort -- BIG-O = O(N logN)
	void MergeSort()
	{
		assert(m_array != NULL);

		T* tempArray = new T[m_numElements];
		assert(tempArray != NULL);

		MergeSort(tempArray, 0, m_numElements - 1);
		delete[] tempArray;
	}
	//------------ END SORTING ----------------------
	// Clear - Big-O = O(1)
	void erase()
	{
		m_numElements = 0;
	}
	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Recursive Merge Sort
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base case
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);
		MergeSort(tempArray, mid + 1, upperBound);

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			// Lower of the 2 values is smaller, move it to the tempArray
			if (m_array[low] < m_array[mid])
			{
				tempArray[index++] = m_array[low++];
			}
			else
			{
				tempArray[index++] = m_array[mid++];
			}
		}

		while (low <= tempMid)
		{
			tempArray[index++] = m_array[low++];
		}

		while (mid <= upper)
		{
			tempArray[index++] = m_array[mid++];
		}

		// Place the sorted tempArray into the main array in the correct location
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			m_array[tempLow + i] = tempArray[i];
		}
	}
	// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			return false;
		}

		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);

		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		delete[] m_array;
		m_array = temp;

		m_maxSize += m_growSize;

		return true;
	}
private:
	// Variables
	T* m_array;

	int m_maxSize;		// Maximum size of our array
	int m_growSize;		// Amount the array can grow
	int m_numElements;	// Number of items currently in my array.
};

template<class valueType>
UnorderedArray<valueType>::UnorderedArray(int maxSize, int growSize, bool noDuplicate)
	:ArrayBase<valueType>(maxSize, growSize), p_noDuplicate(noDuplicate)
{

}
template<class valueType>
UnorderedArray<valueType>::~UnorderedArray()
{

}

template<class valueType>
void UnordedArray<valueType>::printArray()
{
	std::cout << "Current Array Stats... \n" << "MaxSize: " << m_maxSize << " " << "GrowSize: " << m_growSize << " " << "NumElements: " << m_numElements << "\n";

	for (int i = 0; i < m_numElements; ++i)
	{
		std::cout << m_pArray[i] << " ";
	}
	std::cout << "\n\n";
}*/