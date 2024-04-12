//
// Created by akosr on 16/04/2019.
//

#ifndef DRINKS_ARRAY_H
#define DRINKS_ARRAY_H

#include <cstddef>
#include <iostream>
#include "string5.h"

template<typename T>
class Array
{
    size_t size;
    size_t countOfDatas;
    T* data;
public:
    Array(size_t n = 1);
    ~Array();

    Array(const Array& other);
    Array& operator=(const Array& other);

    size_t GetDataSize() const;


    T& operator[](const size_t idx);
    const T& operator[](const size_t idx) const;

	bool operator==(const Array& other)
	{
		if (this->countOfDatas != other.GetDataSize())
			return false;

		for (size_t idx = 0; idx < this->countOfDatas; ++idx)
			if (!(this->data[idx] == other[idx]))
				return false;

		return true;
	}

    int Find(T& item) const;

    void Add(T item);
    //void Add(const T item);
    void Remouve(T& item);
    void reAllocate();
};



template<typename T>
Array<T>::Array(size_t n) :size(n), countOfDatas(0)
{
	/*if(this->data != NULL)
		delete[] this->data;*/
    this->data = new T[this->size];
}

template<typename T>
Array<T>::~Array()
{
    delete[] this->data;
}

template<typename T>
T& Array<T>::operator[](const size_t idx)
{
    if(idx >= this->size)
        throw std::out_of_range("");
    return this->data[idx];
}

template<typename T>
const T& Array<T>::operator[](const size_t idx) const
{
    if(idx >= this->size)
        throw std::out_of_range("");
    return this->data[idx];
}

template<typename T>
void Array<T>::reAllocate()
{
    Array<T> temp(size);
    temp = *this;
    delete[] data;
    size = temp.size * 2;
    countOfDatas = temp.countOfDatas;
    data = new T[size];
    for(size_t idx = 0; idx < temp.size; ++idx)
    {
        data[idx] = temp[idx];
    }
}

template<typename T>
void Array<T>::Add(T item)
{
    if(this->Find(item) != -1)
        return;

    if(this->countOfDatas >= this->size)
        reAllocate();

    this->data[countOfDatas] = item;
    ++countOfDatas;

}

template<typename T>
int Array<T>::Find(T& item) const
{
    for(size_t idx = 0; idx < this->countOfDatas; ++idx)
    {
        if(this->data[idx] == item)
            return (int)idx;
    }
    return -1;
}

template<typename T>
void Array<T>::Remouve(T& item)
{
    int idx = this->Find(item);
	delete item;
    if(idx == -1)
        return;

    for(size_t id = idx; id < this->countOfDatas - 1; ++id)
    {
        this->data[id] = this->data[id + 1];
    }
    --this->countOfDatas;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const Array<T>& array)
{
    if(array.GetDataSize() == 0)
        return  os;

    for(size_t idx = 0; idx < array.GetDataSize(); ++idx)
    {
        os << idx;
        os << ' ';
        os << array[idx];
        os << std::endl;
    }
    return os;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if(this->data == other.data)
        return *this;

    delete[] this->data;
    this->size = other.size;
    this->countOfDatas = other.countOfDatas;
    this->data = new T[this->size];
    for(size_t idx = 0; idx < this->size; ++idx)
    {
        this->data[idx] = other[idx];
    }
	return *this;
}

template<typename T>
size_t Array<T>::GetDataSize() const
{
    return this->countOfDatas;
}


#endif //DRINKS_ARRAY_H
