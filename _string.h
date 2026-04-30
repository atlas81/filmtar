#ifndef STRING_H
#define STRING_H

#include <cstddef>

class String {
    char* pData;
    size_t len;

    public:
    String();

    String(char c);

    String(const char* s);

    String(const String& rhs);

    ~String();

    size_t size() const;

    const char* c_str();

    String& operator=(const String& rhs);

    char& operator[](size_t n);

    String operator+(char c);

    String operator+(const String& rhs);

    bool operator ==(const String& rhs) const;

    const bool operator<(const String& rhs) const;
};

#endif