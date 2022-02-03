#include "chStack1.h"

//default constructor for ChStack
ChStack::ChStack(): m_S(new char[DEFSIZE]),
    m_Maxlen(DEFSIZE), m_Top(EMPTY) {}


ChStack::ChStack(int size, const char str[])
        : m_Maxlen(size) {
    int i;
    assert(size > 0);
    m_S = new char[size];
    for (i = 0; i < m_Maxlen && str[i]; ++i)
        m_S[i] = str[i];
    m_Top = --i;
}
