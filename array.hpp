#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename T>
class Array {
    T* pData;
    size_t db;
    size_t kapacitas;

    public:

    Array();

    ~Array();

    size_t size() const;
    void resize(size_t newsize);

    T& operator[](size_t n);
};

#endif