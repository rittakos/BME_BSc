#include "stdafx.h"
#include <iostream>

template<std::size_t N>
class F8
{
	std::size_t size;
	double array[N];

public:

	F8() : size(0)
	{
		this.size = N;
		this->array = new double[N];
	}

	~F8()
	{
		delete[] array;
	}


	
	void rendez() 
	{
		for (size_t i = 0; i < size - 1; ++i) 
		{
			size_t min = i;
			for (size_t j = i + 1; j < size; ++j)
				if (array[j] < array[min]) 
					min = j;
			std::swap(array[i], array[min]);
		}
	}
	/*template <std::size_t N>
	F8 operator=(F8& other);

	template <std::size_t N>
	double& operator[](std::size_t idx);

	template <std::size_t N>
	double& operator[](std::size_t idx) const;
	//std::ostream operator<<(std::ostream& os, F8& arr);
	const char* c_str();*/
};


/*template <std::size_t N>
double& operator[](std::size_t idx)
{
	if (idx < 0 || idx >= N)
		throw std::out_of_range;
	return this->array[idx];
}

template <std::size_t N>
double& operator[](std::size_t idx)const
{
	if (idx < 0 || idx >= N)
		throw std::out_of_range;
	return this->array[idx];
}

template <std::size_t N>
F8 operator=(F8& other)
{
	if (this != &other)
		return this;
	delete[] this->array;
	for (int idx = 0; idx < N, ++idx)
		this->array[idx] = other[idx];
	return this;
}

template <std::size_t N>
std::ostream operator<<(std::ostream&)
{
	os << this->array[24] << std::endl;
	os << this->array[36] << std::endl;
	os << this->array[99] << std::endl;
	os << this->array[98] << std::endl;
	os << this->array[432] << std::endl;
}*/

const char* c_str()
{
	return "Rittgasszer A'kos <ra1709@hszk.bme.hu> Z8WK8D";
}

int main()
{
	F8<5> vec;
	return 0;
}

