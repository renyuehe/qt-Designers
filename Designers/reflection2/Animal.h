#pragma once
#include <QObject>

class Animal : public QObject
{
	Q_OBJECT
public:
	Animal();
    virtual void setName(QString name) = 0;
	virtual QString name() const = 0;
};
