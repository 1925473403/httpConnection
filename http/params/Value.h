#include "HttpException.h"
#ifndef VALUE_H
#define VALUE_H
class ValueBase {
    public:
    ValueBase() {}
    virtual ~ValueBase() { }
    virtual void output(std::ostream &os) = 0;
};

template<class T>
class Value : public ValueBase {
    private:
    T m_value;
    public:
    Value(T val) : m_value(val) { }
    ~Value() { }
    T value() { return m_value; }
    void output(std::ostream &os) {
        os << m_value;
    }
};
ostream& operator<<(ostream &os, ValueBase &rhs);
#endif
