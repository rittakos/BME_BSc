#ifndef ALAPTIPUS_HPP_INCLUDED
#define ALAPTIPUS_HPP_INCLUDED

template <typename T>
class Alaptipus
{
    T data;
public:
    Alaptipus(T t = 0) :data(t){}

    operator T&() { return data; }
    operator T() const { return data; }
    T* operator&() {   return &data; }
    const T* operator&() const {   return &data; }
    virtual ~Alaptipus() {}
};

#endif // ALAPTIPUS_HPP_INCLUDED
