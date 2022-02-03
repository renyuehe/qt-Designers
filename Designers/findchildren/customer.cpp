#include "customer.h"

Customer::Customer(const char* name) {
    setObjectName(name);
}
QTextStream& operator<< (QTextStream& os, const Customer& c) {
    os << c.toString();
    return os;
}


