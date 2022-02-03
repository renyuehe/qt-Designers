#ifndef CASEIGNORESTRING_H
#define CASEIGNORESTRING_H


#include <QList>
#include <QtAlgorithms>   // for qSort()
#include <QStringList>
#include <QDebug>

class CaseIgnoreString : public QString {
public:
    CaseIgnoreString(const QString& other = QString())
    : QString(other) {}
    bool operator<(const QString & other) const {
        return toLower() < other.toLower();
    }
    bool operator==(const QString& other) const {
        return toLower() == other.toLower();
    }
};

#endif // CASEIGNORESTRING_H
