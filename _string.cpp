#include "_string.h"
#include <cstring>

String::String() : pData(nullptr), len(0) {}

String::String(char c) : pData(new char[2]), len(1) {
    pData[0] = c;
    pData[1] = '\0';
}

String::String(const char* s) : pData(new char[strlen(s) + 1]), len(strlen(s)) {
    strcpy(pData, s);
}


String::String(const String& rhs) : pData(new char[rhs.size() + 1]), len(rhs.size()) {
    strcpy(pData, rhs.c_str());
}


String::~String() { 
    delete[] pData; 
    pData = nullptr; 
}


size_t String::size() const { return len; }


const char* String::c_str() const { return pData; }


String& String::operator=(const String& rhs) {
    if (*this == rhs) return *this;

    len = rhs.size();
    delete[] pData;
    pData = new char[len + 1];
    strcpy(pData, rhs.c_str());
    return *this;
}

char& String::operator[](size_t n) {
    if (n >= len || n < 0) throw "String : tulindexeles";
    return pData[n];
}


const char& String::operator[](size_t n) const {
    if (n >= len || n < 0) throw "String : tulindexeles";
    return pData[n];
}


String String::operator+(char c) {
    char temp[len + 2];
    strcpy(temp, pData);
    temp[len + 1] = c;
    String ret(temp);
    return ret;
}

String String::operator+(const String& rhs) const{
    char temp[len + rhs.size() + 1];
    strcpy(temp, pData);
    strcat(temp, rhs.c_str());
    String ret(temp);
    return ret;
}


bool String::operator==(const String& rhs) const {
    if (len == rhs.size()) {
        return (strcmp(pData, rhs.c_str()) == 0) ? true : false;
    }
    return false;
}


bool String::operator<(const String& rhs) const {
    size_t cmp_lim = (len > rhs.size()) ? rhs.size() : len;
    for (size_t i = 0; i < cmp_lim; ++i) {
        if ((*this)[i] < rhs[i]) return true;
        if ((*this)[i] > rhs[i]) return false;
    }
    return len < rhs.size();
}
