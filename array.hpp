#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include "memtrace.h"
#include <exception>


template <typename T>
class Array {
    T* pData;
    size_t db;
    size_t kapacitas;

    public:

    Array(size_t kapacitas) : db(0),kapacitas(kapacitas) {
        pData = new T[kapacitas];
    }

    ~Array() {
        delete[] pData;
    }

    size_t size() const {
        return db;
    }


    size_t kap() const {
        return kapacitas;
    }

    void resize(size_t newsize) {
        T* temp = new T[newsize];

        size_t cpy_lim = (newsize < db) ? newsize : db;
        for (size_t i = 0; i < cpy_lim; ++i) {
            temp[i] = pData[i];
        }
        delete[] pData;
        kapacitas = newsize;
        pData = temp;

        if (db > kapacitas) db = kapacitas;
    }

    T& operator[](size_t n) {
        if (n >= db || n < 0) throw std::out_of_range("array:tulindexeles");
        return pData[n];
    }

    const T& operator[](size_t n) const {
        if (n >= db || n < 0) throw std::out_of_range("array:tulindexeles");
        return pData[n];
    }


    void push_back(T& inp) {
        if (db + 1 >= kapacitas) {
            resize(kapacitas * 2);
        }
        pData[db++] = inp;
    }


    void remove(T& inp) {
        bool found = false;
        for (size_t i = 0; i < db; ++i) {
            if (found) {
                pData[i - 1] = pData[i];
            }
            if (!found && (pData[i] == inp)) {
                found = true;
            }
        }
        --db;
    }
    // a megadott indexu elemet torli a tombbol
    void remove_at(size_t idx) { 
        bool found = false;
        for (size_t i = 0; i < db; ++i) {
            if (found) {
                pData[i - 1] = pData[i];
            }
            if (!found && (i == idx)) {
                found = true;
            }
        }
        --db;
    }

};

#endif