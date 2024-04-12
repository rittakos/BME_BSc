#include "vektor.h"


std::size_t Vektor::defSize = 13;
double Vektor::defValue = 53;


Vektor::Vektor(const Vektor& vec)
{
    this->nElements = vec.nElements;
    this->pVec = new double[nElements];
    for(std::size_t idx = 0; idx < nElements; ++idx)
    {
        pVec[idx] = vec.pVec[idx];
    }
}

Vektor::~Vektor()
{
    delete[] this->pVec;
}

Vektor& Vektor::operator=(const Vektor& vec)
{
    if(this->pVec == vec.pVec)
        return *this;
    this->nElements = vec.size();
    delete[] this->pVec;
    this->pVec = new double[nElements];
    for(std::size_t idx = 0; idx < nElements; ++idx)
    {
        pVec[idx] = vec.pVec[idx];
    }
    return *this;
}

double& Vektor::operator[](std::size_t idx)
{
    if(idx >= this->nElements || idx < 0)
        throw "Z8WK8D";
    return this->pVec[idx];
}

const double& Vektor::operator[](std::size_t idx) const
{
    if(idx >= this->nElements || idx < 0)
        throw "Z8WK8D";
    return this->pVec[idx];
}

Vektor operator*(double val, const Vektor& vec)
{
    Vektor result(vec.size(), 0);
    for(std::size_t idx = 0; idx < vec.size(); ++idx)
    {
        result[idx] = vec[idx] * val;
    }
    return result;
}
