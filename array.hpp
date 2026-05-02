#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename T>
class Array {
    T* pData;
    size_t kapacitas;

    public:

    Array(size_t kapacitas) : kapacitas(kapacitas) {
        pData = new T[kapacitas];
    }

    ~Array() {
        delete[] pData;
    }

    size_t size() const {
        return kapacitas;
    }
    void resize(size_t newsize) {
        T* temp = new T[newsize];

        size_t cpy_lim = (newsize < kapacitas) ? newsize : kapacitas;
        for (size_t i = 0; i < cpy_lim; ++i) {
            temp[i] = pData[i];
        }
        delete[] pData;
        kapacitas = newsize;
        pData = temp;
    }

    T& operator[](size_t n) {
        if (n >= kapacitas || n < 0) throw "array:tulindexeles";
        return pData[n];
    }

    const T& operator[](size_t n) const {
        if (n >= kapacitas || n < 0) throw "array:tulindexeles";
        return pData[n];
    }


    void push_back(T) {

    }

};

#endif