#ifndef __SIMPLE_MULTI_ARRAY_H
#define __SIMPLE_MULTI_ARRAY_H

#include <assert.h>

const unsigned simpleMultiArrayMaxDimensions = 8;

template<typename T>
class SimpleMultiArray
{
public:
	SimpleMultiArray<T>()
	{
		numberOfDimensions = 0;
		capacity = 0;
		data = 0;
	}
	SimpleMultiArray<T>(unsigned n)
	{
		numberOfDimensions = 1;
		capacity = n;
		data = new T[n];
		dimensions[0] = n;
	}
	SimpleMultiArray<T>(unsigned n0, unsigned n1)
	{
		numberOfDimensions = 2;
		capacity = n0 * n1;
		data = new T[capacity];
		dimensions[0] = n0;
		dimensions[1] = n1;
	}
	SimpleMultiArray<T>(unsigned n0, unsigned n1, unsigned n2)
	{
		numberOfDimensions = 3;
		capacity = n0 * n1 * n2;
		data = new T[capacity];
		dimensions[0] = n0;
		dimensions[1] = n1;
		dimensions[2] = n2;
	}
	~SimpleMultiArray<T>()
	{
		if (data)
			delete [] data;
	}
	unsigned getNumberOfDimensions() const { return numberOfDimensions; }
	unsigned *getDimensions() const { return dimensions; }
	T *getData() { return data; }
	unsigned size() const
	{
		if (numberOfDimensions == 0)
			return 0;

		unsigned n = 1;
		for (unsigned i = 0 ;i < numberOfDimensions; i++)
			n *= dimensions[i];
		return n;
	}
	T &operator [](unsigned i)
	{
		return data[i];
	}
	T &operator ()(unsigned i, unsigned j)
	{
		return data[i * dimensions[0] + j];
	}
	T &operator ()(unsigned i, unsigned j, unsigned k)
	{
		return data[(i * dimensions[1] + j) * dimensions[0] + k];
	}
	void resize(unsigned n)
	{
		if (capacity < n)
			grow(n);
		numberOfDimensions = 1;
		dimensions[0] = n;
	}
	void resize(unsigned n0, unsigned n1)
	{
		unsigned n = n0 * n1;
		if (capacity < n)
			grow(n);
		numberOfDimensions = 2;
		dimensions[0] = n0;
		dimensions[1] = n1;
	}
	void resize(unsigned n0, unsigned n1, unsigned n2)
	{
		unsigned n = n0 * n1 * n2;
		if (capacity < n)
			grow(n);
		numberOfDimensions = 3;
		dimensions[0] = n0;
		dimensions[1] = n1;
		dimensions[2] = n2;
	}
	void resize(unsigned nDimensions, unsigned *dims)
	{
		assert(nDimensions <= simpleMultiArrayMaxDimensions);
		unsigned n = 1;
		for (unsigned i = 0; i < nDimensions; i++)
			n *= dims[i];
		if (capacity < n)
			grow(n);
		numberOfDimensions = nDimensions;
		for (unsigned i = 0; i < nDimensions; i++)
			dimensions[i] = dims[i];
	}
protected:
	void grow(unsigned n);
	unsigned numberOfDimensions;
	unsigned dimensions[simpleMultiArrayMaxDimensions];
	unsigned capacity;
	T *data;
};

template<typename T>
void SimpleMultiArray<T>::grow(unsigned n)
{
	if (n <= capacity)
		return;

	unsigned newCapacity = n;
	if ((capacity << 1) > newCapacity)
		newCapacity = capacity << 1;

	T *newData = new T[newCapacity];

	unsigned size_ = size();
	for (unsigned i=0; i < size_; i++)
		newData[i] = data[i];

	if (capacity > 0)
		delete [] data;

	capacity = newCapacity;
	data = newData;
}

#endif
